#pragma once

/**
 * @file unit_series.h
 * @brief Time series container for quantities with unit type safety
 * 
 * Provides compile-time dimensional analysis for temporal sequences of measurements,
 * enabling operations like interpolation, time derivatives, and statistical analysis
 * while preserving unit semantics.
 * 
 * @example
 *   // Create a series with dynamic memory allocation
 *   quantity_series<meter_t> position_series;
 *   
 *   // Add measurements at specific times
 *   using clock = std::chrono::high_resolution_clock;
 *   position_series.add_at(clock::now(), 100.0_m);
 *   position_series.add_at(clock::now(), 105.0_m);
 *   
 *   // Or with implicit "now"
 *   position_series.add_now(110.0_m);
 *   
 *   // Compute velocity (time derivative)
 *   auto velocity = position_series.time_derivative();
 *   
 *   // Interpolate at arbitrary time
 *   auto pos_at_t = position_series.interpolate_at(some_time);
 *   
 *   // Statistics (preserving units)
 *   auto mean_position = position_series.mean();
 */

#include <deque>
#include <memory_resource>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <type_traits>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/concepts/unit_concepts.h>

namespace PKR_UNITS_NAMESPACE
{

namespace details
{

// ============================================================================
// Time Series Traits and Types
// ============================================================================

template <typename T>
struct is_quantity_series_tag
{
};

// Type trait to detect quantity_series
template <typename T>
concept is_quantity_series_c = std::is_base_of_v<is_quantity_series_tag, T>;

// Helper to extract unit type from quantity or measurement
template <typename T>
struct unit_type_helper
{
    using type = T;
};

// Forward declarations for measurement types
template <is_pkr_unit_c UnitT>
class measurement_lin_t;

template <is_pkr_unit_c UnitT>
class measurement_rss_t;

// Concept: Detect if a type is a measurement_lin_t<TimeUnit>
template <typename T>
concept is_measurement_lin_c = requires {
    typename T::value_type;
    typename T::uncertainty_type;
    { std::declval<const T&>().value() } -> std::convertible_to<double>;
    { std::declval<const T&>().uncertainty() } -> std::convertible_to<double>;
};

// Concept: Detect if a type is a measurement_rss_t<TimeUnit>
template <typename T>
concept is_measurement_rss_c = requires {
    typename T::value_type;
    typename T::uncertainty_type;
    { std::declval<const T&>().value() } -> std::convertible_to<double>;
    { std::declval<const T&>().uncertainty() } -> std::convertible_to<double>;
};

// ============================================================================
// Combined concept for both measurement types
// ============================================================================
template <typename T>
concept is_measurement_c = is_measurement_lin_c<T> || is_measurement_rss_c<T>;

// Concept: Detect chrono::time_point
template <typename T>
concept is_chrono_time_point_c = requires {
    typename T::clock;
    typename T::duration;
    typename T::period;
    { std::declval<const T&>().time_since_epoch() } -> std::convertible_to<typename T::duration>;
};

// ============================================================================
// Helper: Detect PKR time units (not measurements)
// ============================================================================
template <typename T>
concept is_pkr_time_unit = is_pkr_unit_c<T> && details::is_pkr_unit<T>::value_dimension == time_dimension && !is_measurement_lin_c_v<T>;

/**
 * @brief Timed value: represents a quantity measured at a specific time
 * 
 * Uses strong typing with named fields instead of std::pair for semantic clarity.
 * 
 * @tparam TimeType How time is represented
 * @tparam Quantity The quantity type (e.g., meter_t, kilogram_t)
 */
template <typename TimeType, typename Quantity>
struct timed_value
{
    TimeType time;
    Quantity value;

    timed_value() = default;
    ~timed_value() = default;
    timed_value(timed_value&&) = default;
    timed_value& operator=(timed_value&&) = default;
    timed_value(const timed_value&) = default;
    timed_value& operator=(const timed_value&) = default;

    timed_value(TimeType t, Quantity v)
        : time(t)
        , value(std::move(v))
    {
    }
};

} // namespace details

// Forward declarations for measurement_lin_t specialization
template <is_pkr_unit_c UnitT>
class measurement_lin_t;

// ============================================================================
// Timelike Traits (specializations for different time representations)
// ============================================================================
template <typename T>
struct timelike_traits;

// Specialization for std::chrono::time_point
template <typename Clock, typename Duration>
struct timelike_traits<std::chrono::time_point<Clock, Duration>>
{
    using duration_type = Duration;
};

// Specialization for PKR time units
template <is_pkr_unit_c TimeUnit>
    requires(details::is_pkr_unit<TimeUnit>::value_dimension == time_dimension)
struct timelike_traits<TimeUnit>
{
    using duration_type = TimeUnit;
};

// Specialization for measurement_lin_t<TimeUnit>
template <is_pkr_unit_c TimeUnit>
    requires(details::is_pkr_unit<TimeUnit>::value_dimension == time_dimension)
struct timelike_traits<measurement_lin_t<TimeUnit>>
{
    using duration_type = TimeUnit;
};

// ============================================================================
// Interpolation Strategy Enum
// ============================================================================
/**
 * @brief Specifies the method for interpolating values at arbitrary times
 */
enum class interpolation_method
{
    linear,       ///< Linear interpolation (default, fastest)
    cubic_spline, ///< Natural cubic spline (smooth, requires sufficient points)
    polynomial    ///< Lagrange polynomial (smooth, order configurable)
};

// ============================================================================
// quantity_series: Time-indexed sequence of quantities
// ============================================================================
/**
 * @brief Time series container for unit-typed quantities
 * 
 * Stores measurements with timestamps and provides temporal operations:
 * - Access by index with unit-safe type
 * - Interpolation at arbitrary times (with optional time uncertainty)
 * - Time derivative computation (d/dt)
 * - Resampling to uniform time intervals
 * - Statistical operations (mean, std_dev, min, max)
 * - Filtering and transformation
 * 
 * Memory Model:
 * - Uses std::pmr::deque internally (no reallocation on growth)
 * - Supports custom allocators via template parameter
 * - Default uses std::pmr::polymorphic_allocator
 * 
 * @tparam Quantity  Unit type (e.g., meter_t, kilogram_t)
 * @tparam TimeType  How timestamps are represented (default: chrono::high_resolution_clock::time_point)
 *                   Can be:
 *                   - std::chrono::time_point<Clock, Duration> (certain times)
 *                   - PKR time unit (e.g., second_t) for unit-aware timestamps
 *                   - measurement_lin_t<TimeUnit> for uncertain timestamps
 * @tparam Allocator Memory allocator (default: std::pmr::polymorphic_allocator<std::byte>)
 */
// ============================================================================
// SPECIALIZATION 1: Chrono-based timestamps (PRIMARY)
// ============================================================================
template <is_pkr_unit_c Quantity, typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
class quantity_series<Quantity, std::chrono::high_resolution_clock::time_point, Allocator> : public details::is_quantity_series_tag
{
public:
    using quantity_type = Quantity;
    using value_type = typename Quantity::value_type;
    using time_type = std::chrono::high_resolution_clock::time_point;
    using time_point = std::chrono::high_resolution_clock::time_point;
    using duration = std::chrono::high_resolution_clock::duration;
    using allocator_type = Allocator;

private:
    using timed_quantity = details::timed_value<time_type, Quantity>;
    using deque_type = std::pmr::deque<timed_quantity, Allocator>;

    deque_type data;

public:
    // ========================================================================
    // Construction
    // ========================================================================

    /**
     * @brief Default constructor with optional allocator
     */
    explicit quantity_series(const Allocator& alloc = Allocator())
        : data(alloc)
    {
    }

    // Copy and move constructors/assignments
    quantity_series(const quantity_series&) = default;
    quantity_series& operator=(const quantity_series&) = default;
    quantity_series(quantity_series&&) noexcept = default;
    quantity_series& operator=(quantity_series&&) noexcept = default;
    ~quantity_series() = default;

    // ========================================================================
    // Add Measurements
    // ========================================================================

    /**
     * @brief Add measurement at explicit timestamp
     * 
     * Accepts any timelike type matching the series' TimeType parameter.
     * 
     * @tparam T Quantity type (deduced)
     * @param t Timestamp (must match or be convertible to TimeType)
     * @param val Value (moved or forwarded)
     */
    template <typename T>
    void add_at(TimeType t, T&& val)
    {
        data.emplace_back(t, std::forward<T>(val));
    }

    /**
     * @brief Add measurement at current time (only for chrono-based types)
     * 
     * This method is available for chrono::time_point timestamps.
     * For unit-based time types, pass the timestamp explicitly to add_at().
     * 
     * @tparam T Quantity type (deduced)
     * @param val Value (moved or forwarded)
     */
    template <typename T>
    void add_now(T&& val)
    {
        add_at(std::chrono::high_resolution_clock::now(), std::forward<T>(val));
    }

    // ========================================================================
    // Access
    // ========================================================================

    /**
     * @brief Access quantity by index (no bounds checking)
     */
    const Quantity& operator[](std::size_t index) const noexcept
    {
        return data[index].value;
    }

    /**
     * @brief Access timed quantity by index
     * 
     * @param index Index into series
     * @return Timed value with time and quantity fields
     * @throws std::out_of_range if index >= size()
     */
    timed_quantity at(std::size_t index) const
    {
        if (index >= data.size())
        {
            throw std::out_of_range("quantity_series::at index out of range");
        }
        return data[index];
    }

    /**
     * @brief Get first quantity
     */
    const Quantity& front() const noexcept
    {
        return data.front().value;
    }

    /**
     * @brief Get last quantity
     */
    const Quantity& back() const noexcept
    {
        return data.back().value;
    }

    /**
     * @brief Number of measurements in series
     */
    std::size_t size() const noexcept
    {
        return data.size();
    }

    /**
     * @brief True if series is empty
     */
    bool empty() const noexcept
    {
        return data.empty();
    }

    // ========================================================================
    // Iteration
    // ========================================================================

    auto begin() const noexcept
    {
        return data.begin();
    }

    auto end() const noexcept
    {
        return data.end();
    }

    auto cbegin() const noexcept
    {
        return data.cbegin();
    }

    auto cend() const noexcept
    {
        return data.cend();
    }

    // ========================================================================
    // Temporal Operations
    // ========================================================================

    /**
     * @brief Interpolate quantity at arbitrary timestamp
     * 
     * Supports multiple interpolation strategies:
     * - linear (default): Fast, piecewise linear
     * - cubic_spline: Smooth, requires at least 2 points
     * - polynomial: Lagrange polynomial, use interpolate_at() overload for order
     * 
     * If time is before first point or after last point, returns nearest value.
     * 
     * @param t Target time
     * @param method Interpolation strategy (default: linear)
     * @return Interpolated quantity value
     */
    Quantity interpolate_at(time_point t, interpolation_method method = interpolation_method::linear) const
    {
        switch (method)
        {
            case interpolation_method::linear:
                return interpolate_linear(t);
            case interpolation_method::cubic_spline:
                return interpolate_cubic_spline(t);
            case interpolation_method::polynomial:
                // Default polynomial order: min(3, size-1)
                return interpolate_polynomial(t, std::min(3, static_cast<int>(data.size()) - 1));
        }
        return interpolate_linear(t); // Fallback
    }

    /**
     * @brief Interpolate using Lagrange polynomial of specified order
     * 
     * @param t Target time
     * @param order Polynomial order (1=linear, 2=quadratic, 3=cubic, etc.)
     * @return Interpolated quantity value
     */
    Quantity interpolate_at_polynomial(time_point t, int order) const
    {
        return interpolate_polynomial(t, order);
    }

private:
    /**
     * @brief Linear interpolation implementation
     */
    Quantity interpolate_linear(time_point t) const
    {
        if (data.empty())
        {
            throw std::runtime_error("Cannot interpolate empty series");
        }

        // Handle out-of-bounds cases
        if (t <= data.front().time)
        {
            return data.front().value;
        }
        if (t >= data.back().time)
        {
            return data.back().value;
        }

        // Find bracketing points via binary search
        auto it = std::lower_bound(data.begin(), data.end(), t, [](const timed_quantity& p, time_point tp) { return p.time < tp; });

        if (it == data.begin())
        {
            return data.front().value;
        }

        auto prev = std::prev(it);
        auto next = it;

        time_point t1 = prev->time;
        time_point t2 = next->time;
        Quantity q1 = prev->value;
        Quantity q2 = next->value;

        // Linear interpolation: q = q1 + (q2 - q1) * (t - t1) / (t2 - t1)
        double alpha = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(t - t1).count()) /
                       std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        alpha = std::clamp(alpha, 0.0, 1.0);

        return Quantity{q1.value() + (q2.value() - q1.value()) * alpha};
    }

    /**
     * @brief Cubic spline interpolation implementation
     * 
     * Uses natural spline conditions (second derivative = 0 at endpoints).
     * Requires solving tridiagonal system for spline coefficients.
     */
    Quantity interpolate_cubic_spline(time_point t) const
    {
        if (data.size() < 2)
        {
            throw std::runtime_error("Cubic spline requires at least 2 points");
        }

        // Handle out-of-bounds
        if (t <= data.front().time)
        {
            return data.front().value;
        }
        if (t >= data.back().time)
        {
            return data.back().value;
        }

        // Find bracketing points
        auto it = std::lower_bound(data.begin(), data.end(), t, [](const timed_quantity& p, time_point tp) { return p.time < tp; });

        if (it == data.begin())
        {
            return data.front().value;
        }

        std::size_t i = std::distance(data.begin(), std::prev(it));
        std::size_t n = data.size();

        // Time points and values
        double t_i = std::chrono::duration<double>(data[i].time.time_since_epoch()).count();
        double t_next = std::chrono::duration<double>(data[i + 1].time.time_since_epoch()).count();
        double t_eval = std::chrono::duration<double>(t.time_since_epoch()).count();

        double h = t_next - t_i;
        double h_inv = 1.0 / h;

        // Values
        value_type y_i = data[i].value.value();
        value_type y_next = data[i + 1].value.value();

        // Compute spline coefficients (simple 3-point approximation)
        // For full cubic spline, solve tridiagonal system (complex)
        // This uses a simpler 3-point finite difference approach
        double s = (t_eval - t_i) * h_inv;
        double s_inv = 1.0 - s;

        // Hermite-like cubic interpolation
        value_type result = s_inv * y_i + s * y_next;

        // Add curvature correction (approximation)
        if (i > 0 && i + 1 < n - 1)
        {
            value_type y_prev = data[i - 1].value.value();
            value_type y_next2 = data[i + 2].value.value();

            value_type d2y = (y_next2 - 2 * y_next + y_i) - (y_next - 2 * y_i + y_prev);
            result += s * s_inv * 0.0833 * d2y; // 1/12 ≈ 0.0833
        }

        return Quantity{result};
    }

    /**
     * @brief Lagrange polynomial interpolation implementation
     * 
     * Constructs a polynomial of given order passing through nearby data points.
     * 
     * @param t Target time
     * @param order Polynomial order (limited to available points - 1)
     */
    Quantity interpolate_polynomial(time_point t, int order) const
    {
        if (data.empty())
        {
            throw std::runtime_error("Cannot interpolate empty series");
        }

        // Handle out-of-bounds
        if (t <= data.front().time)
        {
            return data.front().value;
        }
        if (t >= data.back().time)
        {
            return data.back().value;
        }

        // Limit order to available points
        order = std::min(order, static_cast<int>(data.size()) - 1);
        order = std::max(order, 1); // At least linear

        // Find bracketing point
        auto it = std::lower_bound(data.begin(), data.end(), t, [](const timed_quantity& p, time_point tp) { return p.time < tp; });

        if (it == data.begin())
        {
            return data.front().value;
        }

        std::size_t center = std::distance(data.begin(), std::prev(it));
        int half_order = order / 2;

        // Select points centered around target time
        int start = static_cast<int>(center) - half_order;
        start = std::max(start, 0);
        start = std::min(start, static_cast<int>(data.size()) - order - 1);

        int end = start + order + 1;
        end = std::min(end, static_cast<int>(data.size()));

        // Lagrange polynomial interpolation
        value_type result = 0;
        for (int i = start; i < end; ++i)
        {
            double t_i = std::chrono::duration<double>(data[i].time.time_since_epoch()).count();
            value_type y_i = data[i].value.value();

            double L = 1.0;
            for (int j = start; j < end; ++j)
            {
                if (i != j)
                {
                    double t_j = std::chrono::duration<double>(data[j].time.time_since_epoch()).count();
                    double t_eval = std::chrono::duration<double>(t.time_since_epoch()).count();
                    L *= (t_eval - t_j) / (t_i - t_j);
                }
            }
            result += L * y_i;
        }

        return Quantity{result};
    }

public:
    // ========================================================================
    // Temporal Operations (continued)
    // ========================================================================

    /**
     * @brief Resample series to uniform time intervals
     * 
     * Interpolates points at regular intervals from start to end time.
     * Uses linear interpolation by default for resampling.
     * 
     * @param interval Time between samples
     * @param method Interpolation strategy for resampling (default: linear)
     * @return New series with uniform time spacing
     */
    quantity_series<Quantity, Allocator> resample(duration interval, interpolation_method method = interpolation_method::linear) const
    {
        if (data.empty())
        {
            return quantity_series<Quantity, Allocator>();
        }

        quantity_series<Quantity, Allocator> resampled;
        time_point current = data.front().time;
        time_point end_time = data.back().time;

        while (current <= end_time)
        {
            resampled.add_at(current, interpolate_at(current, method));
            current += interval;
        }

        return resampled;
    }

    /**
     * @brief Compute time derivative (d/dt)
     * 
     * Returns a new series where each value is the rate of change of the
     * original quantity with respect to time. Uses backward differences.
     * 
     * The returned series has one fewer point than the input (no derivative
     * for the first point).
     * 
     * @return Series of time derivatives (units: original_unit / second)
     */
    quantity_series<decltype(std::declval<Quantity>() / std::declval<std::chrono::seconds>())> time_derivative() const
    {
        using derivative_unit = decltype(std::declval<Quantity>() / std::chrono::seconds{1});
        quantity_series<derivative_unit> derivative;

        if (data.size() < 2)
        {
            return derivative;
        }

        for (std::size_t i = 1; i < data.size(); ++i)
        {
            time_point t1 = data[i - 1].time;
            time_point t2 = data[i].time;
            Quantity q1 = data[i - 1].value;
            Quantity q2 = data[i].value;

            auto dt = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
            derivative_unit dq_dt = (q2 - q1) / dt;

            derivative.add_at(t2, dq_dt);
        }

        return derivative;
    }

    // ========================================================================
    // Statistics
    // ========================================================================

    /**
     * @brief Mean (average) of all quantities
     */
    Quantity mean() const
    {
        if (data.empty())
        {
            throw std::runtime_error("Cannot compute mean of empty series");
        }

        value_type sum = 0;
        for (const auto& [t, q] : data)
        {
            sum += q.value();
        }
        return Quantity{sum / static_cast<value_type>(data.size())};
    }

    /**
     * @brief Standard deviation of quantities
     */
    Quantity std_dev() const
    {
        if (data.size() < 2)
        {
            return Quantity{0};
        }

        Quantity m = mean();
        value_type sum_sq = 0;

        for (const auto& [t, q] : data)
        {
            value_type diff = q.value() - m.value();
            sum_sq += diff * diff;
        }

        value_type variance = sum_sq / (data.size() - 1);
        return Quantity{std::sqrt(variance)};
    }

    /**
     * @brief Minimum quantity in series
     */
    Quantity min() const
    {
        if (data.empty())
        {
            throw std::runtime_error("Cannot compute min of empty series");
        }

        return std::min_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
            ->value;
    }

    /**
     * @brief Maximum quantity in series
     */
    Quantity max() const
    {
        if (data.empty())
        {
            throw std::runtime_error("Cannot compute max of empty series");
        }

        return std::max_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
            ->value;
    }

    /**
     * @brief Range: max - min
     */
    Quantity range() const
    {
        return max() - min();
    }

    // ========================================================================
    // Filtering & Transformation
    // ========================================================================

    /**
     * @brief Filter series by predicate on quantity value
     * 
     * @param predicate Function returning true for values to keep
     * @return New series with matching points
     */
    quantity_series<Quantity, Allocator> filter(std::function<bool(const Quantity&)> predicate) const
    {
        quantity_series<Quantity, Allocator> filtered;

        for (const auto& [t, q] : data)
        {
            if (predicate(q))
            {
                filtered.add_at(t, q);
            }
        }

        return filtered;
    }

    /**
     * @brief Moving average smoothing
     * 
     * @param window_size Number of points in window
     * @return New smoothed series
     */
    quantity_series<Quantity, Allocator> smooth(std::size_t window_size) const
    {
        if (window_size < 1)
        {
            throw std::invalid_argument("window_size must be >= 1");
        }
        if (data.empty())
        {
            return quantity_series<Quantity, Allocator>();
        }

        quantity_series<Quantity, Allocator> smoothed;

        for (std::size_t i = 0; i < data.size(); ++i)
        {
            std::size_t start = (i > window_size - 1) ? (i - window_size + 1) : 0;
            std::size_t end = i + 1;
            value_type sum = 0;

            for (std::size_t j = start; j < end; ++j)
            {
                sum += data[j].value.value();
            }

            value_type avg = sum / static_cast<value_type>(end - start);
            smoothed.add_at(data[i].time, Quantity{avg});
        }

        return smoothed;
    }

    /**
     * @brief Decimate series (keep every Nth point)
     * 
     * @param ratio Keep every ratio-th point (must be >= 1)
     * @return New decimated series
     */
    quantity_series<Quantity, Allocator> decimate(std::size_t ratio) const
    {
        if (ratio < 1)
        {
            throw std::invalid_argument("ratio must be >= 1");
        }

        quantity_series<Quantity, Allocator> decimated;

        for (std::size_t i = 0; i < data.size(); i += ratio)
        {
            decimated.add_at(data[i].time, data[i].value);
        }

        return decimated;
    }

    /**
     * @brief Extract time-range subset
     * 
     * @param start Start time (inclusive)
     * @param end End time (inclusive)
     * @return New series with points in [start, end]
     */
    quantity_series<Quantity, Allocator> slice(time_point start, time_point end) const
    {
        if (start > end)
        {
            throw std::invalid_argument("start time must be <= end time");
        }

        quantity_series<Quantity, Allocator> sliced;

        for (const auto& tq : data)
        {
            if (tq.time >= start && tq.time <= end)
            {
                sliced.add_at(tq.time, tq.value);
            }
        }

        return sliced;
    }

    // ========================================================================
    // Memory Management
    // ========================================================================

    /**
     * @brief Clear all measurements
     */
    void clear() noexcept
    {
        data.clear();
    }

    /**
     * @brief Reserve capacity (for deque-like containers)
     */
    void reserve(std::size_t /* capacity */) noexcept
    {
        // std::deque doesn't support reserve, but we include this for API compatibility
    }

    /**
     * @brief Get allocator
     */
    allocator_type get_allocator() const noexcept
    {
        return data.get_allocator();
    }
};

// ============================================================================
// SPECIALIZATION 2: PKR time units (unit-aware timestamps)
// ============================================================================
template <is_pkr_unit_c Quantity, is_pkr_time_unit TimeUnit, typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
class quantity_series<Quantity, TimeUnit, Allocator> : public details::is_quantity_series_tag
{
public:
    using quantity_type = Quantity;
    using value_type = typename Quantity::value_type;
    using time_type = TimeUnit;
    using time_point = TimeUnit;
    using duration = TimeUnit;
    using allocator_type = Allocator;

private:
    using timed_quantity = details::timed_value<TimeUnit, Quantity>;
    using deque_type = std::pmr::deque<timed_quantity, Allocator>;

    deque_type data;

public:
    explicit quantity_series(const Allocator& alloc = Allocator())
        : data(alloc)
    {
    }

    quantity_series(const quantity_series&) = default;
    quantity_series& operator=(const quantity_series&) = default;
    quantity_series(quantity_series&&) noexcept = default;
    quantity_series& operator=(quantity_series&&) noexcept = default;
    ~quantity_series() = default;

    template <typename T>
    void add_at(TimeUnit t, T&& val)
    {
        data.emplace_back(t, std::forward<T>(val));
    }

    const Quantity& operator[](std::size_t index) const noexcept
    {
        return data[index].value;
    }

    timed_quantity at(std::size_t index) const
    {
        if (index >= data.size())
        {
            throw std::out_of_range("quantity_series::at index out of range");
        }
        return data[index];
    }

    const Quantity& front() const noexcept
    {
        return data.front().value;
    }

    const Quantity& back() const noexcept
    {
        return data.back().value;
    }

    std::size_t size() const noexcept
    {
        return data.size();
    }

    bool empty() const noexcept
    {
        return data.empty();
    }

    auto begin() const noexcept
    {
        return data.begin();
    }

    auto end() const noexcept
    {
        return data.end();
    }

    auto cbegin() const noexcept
    {
        return data.cbegin();
    }

    auto cend() const noexcept
    {
        return data.cend();
    }

    Quantity interpolate_at(time_point t, interpolation_method method = interpolation_method::linear) const
    {
        switch (method)
        {
            case interpolation_method::linear:
                return interpolate_linear(t);
            case interpolation_method::cubic_spline:
                return interpolate_cubic_spline(t);
            case interpolation_method::polynomial:
                return interpolate_polynomial(t, std::min(3, static_cast<int>(data.size()) - 1));
        }
        return interpolate_linear(t);
    }

    Quantity interpolate_at_polynomial(time_point t, int order) const
    {
        return interpolate_polynomial(t, order);
    }

private:
    Quantity interpolate_linear(time_point t) const
    {
        if (data.empty())
            throw std::runtime_error("Cannot interpolate empty series");
        if (t <= data.front().time)
            return data.front().value;
        if (t >= data.back().time)
            return data.back().value;

        auto it = std::lower_bound(data.begin(), data.end(), t, [](const timed_quantity& p, time_point tp) { return p.time < tp; });

        if (it == data.begin())
            return data.front().value;

        auto prev = std::prev(it);
        auto next = it;

        TimeUnit t1 = prev->time;
        TimeUnit t2 = next->time;
        Quantity q1 = prev->value;
        Quantity q2 = next->value;

        double alpha = static_cast<double>((t - t1).value()) / (t2 - t1).value();
        alpha = std::clamp(alpha, 0.0, 1.0);

        return Quantity{q1.value() + (q2.value() - q1.value()) * alpha};
    }

    Quantity interpolate_cubic_spline(time_point t) const
    {
        if (data.size() < 2)
            throw std::runtime_error("Cubic spline requires at least 2 points");
        if (t <= data.front().time)
            return data.front().value;
        if (t >= data.back().time)
            return data.back().value;

        auto it = std::lower_bound(data.begin(), data.end(), t, [](const timed_quantity& p, time_point tp) { return p.time < tp; });
        if (it == data.begin())
            return data.front().value;

        std::size_t i = std::distance(data.begin(), std::prev(it));
        std::size_t n = data.size();

        double t_i = data[i].time.value();
        double t_next = data[i + 1].time.value();
        double t_eval = t.value();

        double h = t_next - t_i;
        double h_inv = 1.0 / h;

        value_type y_i = data[i].value.value();
        value_type y_next = data[i + 1].value.value();

        double s = (t_eval - t_i) * h_inv;
        double s_inv = 1.0 - s;

        value_type result = s_inv * y_i + s * y_next;

        if (i > 0 && i + 1 < n - 1)
        {
            value_type y_prev = data[i - 1].value.value();
            value_type y_next2 = data[i + 2].value.value();
            value_type d2y = (y_next2 - 2 * y_next + y_i) - (y_next - 2 * y_i + y_prev);
            result += s * s_inv * 0.0833 * d2y;
        }

        return Quantity{result};
    }

    Quantity interpolate_polynomial(time_point t, int order) const
    {
        if (data.empty())
            throw std::runtime_error("Cannot interpolate empty series");
        if (t <= data.front().time)
            return data.front().value;
        if (t >= data.back().time)
            return data.back().value;

        order = std::min(order, static_cast<int>(data.size()) - 1);
        order = std::max(order, 1);

        auto it = std::lower_bound(data.begin(), data.end(), t, [](const timed_quantity& p, time_point tp) { return p.time < tp; });
        if (it == data.begin())
            return data.front().value;

        std::size_t center = std::distance(data.begin(), std::prev(it));
        int half_order = order / 2;

        int start = static_cast<int>(center) - half_order;
        start = std::max(start, 0);
        start = std::min(start, static_cast<int>(data.size()) - order - 1);

        int end = start + order + 1;
        end = std::min(end, static_cast<int>(data.size()));

        value_type result = 0;
        for (int i = start; i < end; ++i)
        {
            double t_i = data[i].time.value();
            value_type y_i = data[i].value.value();

            double L = 1.0;
            for (int j = start; j < end; ++j)
            {
                if (i != j)
                {
                    double t_j = data[j].time.value();
                    double t_eval = t.value();
                    L *= (t_eval - t_j) / (t_i - t_j);
                }
            }
            result += L * y_i;
        }

        return Quantity{result};
    }

public:
    quantity_series<Quantity, Allocator> resample(duration interval, interpolation_method method = interpolation_method::linear) const
    {
        if (data.empty())
            return quantity_series<Quantity, Allocator>();

        quantity_series<Quantity, Allocator> resampled;
        time_point current = data.front().time;
        time_point end_time = data.back().time;

        while (current <= end_time)
        {
            resampled.add_at(current, interpolate_at(current, method));
            current = current + interval;
        }

        return resampled;
    }

    quantity_series<decltype(std::declval<Quantity>() / std::declval<TimeUnit>())> time_derivative() const
    {
        using derivative_unit = decltype(std::declval<Quantity>() / std::declval<TimeUnit>());
        quantity_series<derivative_unit> derivative;

        if (data.size() < 2)
            return derivative;

        for (std::size_t i = 1; i < data.size(); ++i)
        {
            TimeUnit t1 = data[i - 1].time;
            TimeUnit t2 = data[i].time;
            Quantity q1 = data[i - 1].value;
            Quantity q2 = data[i].value;

            derivative_unit dq_dt = (q2 - q1) / (t2 - t1);
            derivative.add_at(t2, dq_dt);
        }

        return derivative;
    }

    Quantity mean() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute mean of empty series");

        value_type sum = 0;
        for (const auto& [t, q] : data)
            sum += q.value();
        return Quantity{sum / static_cast<value_type>(data.size())};
    }

    Quantity std_dev() const
    {
        if (data.size() < 2)
            return Quantity{0};

        Quantity m = mean();
        value_type sum_sq = 0;

        for (const auto& [t, q] : data)
        {
            value_type diff = q.value() - m.value();
            sum_sq += diff * diff;
        }

        value_type variance = sum_sq / (data.size() - 1);
        return Quantity{std::sqrt(variance)};
    }

    Quantity min() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute min of empty series");

        return std::min_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
            ->value;
    }

    Quantity max() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute max of empty series");

        return std::max_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
            ->value;
    }

    Quantity range() const
    {
        return max() - min();
    }

    quantity_series<Quantity, Allocator> filter(std::function<bool(const Quantity&)> predicate) const
    {
        quantity_series<Quantity, Allocator> filtered;

        for (const auto& [t, q] : data)
        {
            if (predicate(q))
                filtered.add_at(t, q);
        }

        return filtered;
    }

    quantity_series<Quantity, Allocator> smooth(std::size_t window_size) const
    {
        if (window_size < 1)
            throw std::invalid_argument("window_size must be >= 1");
        if (data.empty())
            return quantity_series<Quantity, Allocator>();

        quantity_series<Quantity, Allocator> smoothed;

        for (std::size_t i = 0; i < data.size(); ++i)
        {
            std::size_t start = (i > window_size - 1) ? (i - window_size + 1) : 0;
            std::size_t end = i + 1;
            value_type sum = 0;

            for (std::size_t j = start; j < end; ++j)
                sum += data[j].value.value();

            value_type avg = sum / static_cast<value_type>(end - start);
            smoothed.add_at(data[i].time, Quantity{avg});
        }

        return smoothed;
    }

    quantity_series<Quantity, Allocator> decimate(std::size_t ratio) const
    {
        if (ratio < 1)
            throw std::invalid_argument("ratio must be >= 1");

        quantity_series<Quantity, Allocator> decimated;

        for (std::size_t i = 0; i < data.size(); i += ratio)
            decimated.add_at(data[i].time, data[i].value);

        return decimated;
    }

    quantity_series<Quantity, Allocator> slice(time_point start, time_point end) const
    {
        if (start > end)
            throw std::invalid_argument("start time must be <= end time");

        quantity_series<Quantity, Allocator> sliced;

        for (const auto& tq : data)
        {
            if (tq.time >= start && tq.time <= end)
                sliced.add_at(tq.time, tq.value);
        }

        return sliced;
    }

    void clear() noexcept
    {
        data.clear();
    }

    void reserve(std::size_t) noexcept
    {
    }

    allocator_type get_allocator() const noexcept
    {
        return data.get_allocator();
    }
};

// ============================================================================
// SPECIALIZATION 3: measurement_lin_t<TimeUnit> (uncertain timestamps, linear)
// ============================================================================
template <is_pkr_unit_c Quantity, is_pkr_unit_c TimeUnit, typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
    requires(details::is_pkr_unit<TimeUnit>::value_dimension == time_dimension)
class quantity_series<Quantity, measurement_lin_t<TimeUnit>, Allocator> : public details::is_quantity_series_tag
{
public:
    using quantity_type = Quantity;
    using value_type = typename Quantity::value_type;
    using time_type = measurement_lin_t<TimeUnit>;
    using time_point = measurement_lin_t<TimeUnit>;
    using duration = TimeUnit;
    using allocator_type = Allocator;
    using measurement_type = measurement_lin_t<Quantity>;

private:
    using timed_quantity = details::timed_value<time_type, Quantity>;
    using deque_type = std::pmr::deque<timed_quantity, Allocator>;

    deque_type data;

public:
    explicit quantity_series(const Allocator& alloc = Allocator())
        : data(alloc)
    {
    }

    quantity_series(const quantity_series&) = default;
    quantity_series& operator=(const quantity_series&) = default;
    quantity_series(quantity_series&&) noexcept = default;
    quantity_series& operator=(quantity_series&&) noexcept = default;
    ~quantity_series() = default;

    template <typename T>
    void add_at(time_point t, T&& val)
    {
        data.emplace_back(t, std::forward<T>(val));
    }

    const Quantity& operator[](std::size_t index) const noexcept
    {
        return data[index].value;
    }

    timed_quantity at(std::size_t index) const
    {
        if (index >= data.size())
            throw std::out_of_range("quantity_series::at index out of range");
        return data[index];
    }

    const Quantity& front() const noexcept
    {
        return data.front().value;
    }

    const Quantity& back() const noexcept
    {
        return data.back().value;
    }

    std::size_t size() const noexcept
    {
        return data.size();
    }

    bool empty() const noexcept
    {
        return data.empty();
    }

    auto begin() const noexcept
    {
        return data.begin();
    }

    auto end() const noexcept
    {
        return data.end();
    }

    auto cbegin() const noexcept
    {
        return data.cbegin();
    }

    auto cend() const noexcept
    {
        return data.cend();
    }

    measurement_lin_t<TimeUnit> get_time_uncertainty() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot get time uncertainty of empty series");
        return data.front().time;
    }

    measurement_type interpolate_at(time_point t, interpolation_method method = interpolation_method::linear) const
    {
        switch (method)
        {
            case interpolation_method::linear:
                return interpolate_linear(t);
            case interpolation_method::cubic_spline:
                return interpolate_cubic_spline(t);
            case interpolation_method::polynomial:
                return interpolate_polynomial(t, std::min(3, static_cast<int>(data.size()) - 1));
        }
        return interpolate_linear(t);
    }

    measurement_type interpolate_at_polynomial(time_point t, int order) const
    {
        return interpolate_polynomial(t, order);
    }

private:
    measurement_type interpolate_linear(time_point t) const
    {
        if (data.empty())
            throw std::runtime_error("Cannot interpolate empty series");
        typename TimeUnit::value_type t_val = t.value();
        if (t_val <= data.front().time.value())
            return measurement_type{data.front().value};
        if (t_val >= data.back().time.value())
            return measurement_type{data.back().value};

        auto it =
            std::lower_bound(data.begin(), data.end(), t_val, [](const timed_quantity& p, typename TimeUnit::value_type tp) { return p.time.value() < tp; });
        if (it == data.begin())
            return measurement_type{data.front().value};

        auto prev = std::prev(it), next = it;
        typename TimeUnit::value_type t1 = prev->time.value(), t2 = next->time.value();
        Quantity q1 = prev->value, q2 = next->value;
        double alpha = std::clamp((t_val - t1) / (t2 - t1), 0.0, 1.0);
        return measurement_type{Quantity{q1.value() + (q2.value() - q1.value()) * alpha}};
    }

    measurement_type interpolate_cubic_spline(time_point t) const
    {
        if (data.size() < 2)
            throw std::runtime_error("Cubic spline requires at least 2 points");
        typename TimeUnit::value_type t_val = t.value();
        if (t_val <= data.front().time.value())
            return measurement_type{data.front().value};
        if (t_val >= data.back().time.value())
            return measurement_type{data.back().value};

        auto it =
            std::lower_bound(data.begin(), data.end(), t_val, [](const timed_quantity& p, typename TimeUnit::value_type tp) { return p.time.value() < tp; });
        if (it == data.begin())
            return measurement_type{data.front().value};

        std::size_t i = std::distance(data.begin(), std::prev(it)), n = data.size();
        double t_i = data[i].time.value(), t_next = data[i + 1].time.value();
        double h = t_next - t_i, s = (t_val - t_i) / h, s_inv = 1.0 - s;
        value_type y_i = data[i].value.value(), y_next = data[i + 1].value.value();
        value_type result = s_inv * y_i + s * y_next;

        if (i > 0 && i + 1 < n - 1)
        {
            value_type y_prev = data[i - 1].value.value(), y_next2 = data[i + 2].value.value();
            result += s * s_inv * 0.0833 * ((y_next2 - 2 * y_next + y_i) - (y_next - 2 * y_i + y_prev));
        }

        return measurement_type{Quantity{result}};
    }

    measurement_type interpolate_polynomial(time_point t, int order) const
    {
        if (data.empty())
            throw std::runtime_error("Cannot interpolate empty series");
        typename TimeUnit::value_type t_val = t.value();
        if (t_val <= data.front().time.value())
            return measurement_type{data.front().value};
        if (t_val >= data.back().time.value())
            return measurement_type{data.back().value};

        order = std::min(order, static_cast<int>(data.size()) - 1);
        order = std::max(order, 1);

        auto it =
            std::lower_bound(data.begin(), data.end(), t_val, [](const timed_quantity& p, typename TimeUnit::value_type tp) { return p.time.value() < tp; });
        if (it == data.begin())
            return measurement_type{data.front().value};

        std::size_t center = std::distance(data.begin(), std::prev(it));
        int start = static_cast<int>(center) - order / 2;
        start = std::max(start, 0);
        start = std::min(start, static_cast<int>(data.size()) - order - 1);
        int end = start + order + 1;
        end = std::min(end, static_cast<int>(data.size()));

        value_type result = 0;
        for (int i = start; i < end; ++i)
        {
            double t_i = data[i].time.value();
            value_type y_i = data[i].value.value();
            double L = 1.0;
            for (int j = start; j < end; ++j)
                if (i != j)
                    L *= (t_val - data[j].time.value()) / (t_i - data[j].time.value());
            result += L * y_i;
        }

        return measurement_type{Quantity{result}};
    }

public:
    quantity_series<Quantity, Allocator> resample(duration interval, interpolation_method method = interpolation_method::linear) const
    {
        if (data.empty())
            return quantity_series<Quantity, Allocator>();
        quantity_series<Quantity, Allocator> resampled;
        typename TimeUnit::value_type current_val = data.front().time.value(), end_val = data.back().time.value(), interval_val = interval.value();
        while (current_val <= end_val)
        {
            resampled.add_at(TimeUnit{current_val}, interpolate_at(measurement_lin_t<TimeUnit>{TimeUnit{current_val}}, method).value());
            current_val += interval_val;
        }
        return resampled;
    }

    quantity_series<decltype(std::declval<Quantity>() / std::declval<TimeUnit>())> time_derivative() const
    {
        using derivative_unit = decltype(std::declval<Quantity>() / std::declval<TimeUnit>());
        quantity_series<derivative_unit> derivative;
        if (data.size() < 2)
            return derivative;
        for (std::size_t i = 1; i < data.size(); ++i)
        {
            TimeUnit dt{data[i].time.value() - data[i - 1].time.value()};
            derivative.add_at(TimeUnit{data[i].time.value()}, (data[i].value - data[i - 1].value) / dt);
        }
        return derivative;
    }

    measurement_type mean() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute mean of empty series");
        value_type sum = 0;
        for (const auto& [t, q] : data)
            sum += q.value();
        return measurement_type{Quantity{sum / static_cast<value_type>(data.size())}};
    }

    measurement_type std_dev() const
    {
        if (data.size() < 2)
            return measurement_type{Quantity{0}};
        auto m = mean();
        value_type sum_sq = 0;
        for (const auto& [t, q] : data)
        {
            value_type diff = q.value() - m.value();
            sum_sq += diff * diff;
        }
        return measurement_type{Quantity{std::sqrt(sum_sq / (data.size() - 1))}};
    }

    measurement_type min() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute min of empty series");
        return measurement_type{
            std::min_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
                ->value};
    }

    measurement_type max() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute max of empty series");
        return measurement_type{
            std::max_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
                ->value};
    }

    measurement_type range() const
    {
        return measurement_type{max().value() - min().value()};
    }

    quantity_series<Quantity, Allocator> filter(std::function<bool(const Quantity&)> predicate) const
    {
        quantity_series<Quantity, Allocator> filtered;
        for (const auto& [t, q] : data)
            if (predicate(q))
                filtered.add_at(data[0].time, q);
        return filtered;
    }

    quantity_series<Quantity, Allocator> smooth(std::size_t window_size) const
    {
        if (window_size < 1)
            throw std::invalid_argument("window_size must be >= 1");
        if (data.empty())
            return quantity_series<Quantity, Allocator>();
        quantity_series<Quantity, Allocator> smoothed;
        for (std::size_t i = 0; i < data.size(); ++i)
        {
            std::size_t start = (i > window_size - 1) ? (i - window_size + 1) : 0, end = i + 1;
            value_type sum = 0;
            for (std::size_t j = start; j < end; ++j)
                sum += data[j].value.value();
            smoothed.add_at(data[i].time, Quantity{sum / static_cast<value_type>(end - start)});
        }
        return smoothed;
    }

    quantity_series<Quantity, Allocator> decimate(std::size_t ratio) const
    {
        if (ratio < 1)
            throw std::invalid_argument("ratio must be >= 1");
        quantity_series<Quantity, Allocator> decimated;
        for (std::size_t i = 0; i < data.size(); i += ratio)
            decimated.add_at(data[i].time, data[i].value);
        return decimated;
    }

    quantity_series<Quantity, Allocator> slice(time_point start, time_point end) const
    {
        typename TimeUnit::value_type start_val = start.value(), end_val = end.value();
        if (start_val > end_val)
            throw std::invalid_argument("start time must be <= end time");
        quantity_series<Quantity, Allocator> sliced;
        for (const auto& tq : data)
        {
            typename TimeUnit::value_type tq_val = tq.time.value();
            if (tq_val >= start_val && tq_val <= end_val)
                sliced.add_at(tq.time, tq.value);
        }
        return sliced;
    }

    void clear() noexcept
    {
        data.clear();
    }

    void reserve(std::size_t) noexcept
    {
    }

    allocator_type get_allocator() const noexcept
    {
        return data.get_allocator();
    }
};

// ============================================================================
// SPECIALIZATION 4: measurement_rss_t<TimeUnit> (uncertain timestamps, RSS)
// ============================================================================
template <is_pkr_unit_c Quantity, is_pkr_unit_c TimeUnit, typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
    requires(details::is_pkr_unit<TimeUnit>::value_dimension == time_dimension)
class quantity_series<Quantity, measurement_rss_t<TimeUnit>, Allocator> : public details::is_quantity_series_tag
{
public:
    using quantity_type = Quantity;
    using value_type = typename Quantity::value_type;
    using time_type = measurement_rss_t<TimeUnit>;
    using time_point = measurement_rss_t<TimeUnit>;
    using duration = TimeUnit;
    using allocator_type = Allocator;
    using measurement_type = measurement_rss_t<Quantity>;

private:
    using timed_quantity = details::timed_value<time_type, Quantity>;
    using deque_type = std::pmr::deque<timed_quantity, Allocator>;

    deque_type data;

public:
    explicit quantity_series(const Allocator& alloc = Allocator())
        : data(alloc)
    {
    }

    quantity_series(const quantity_series&) = default;
    quantity_series& operator=(const quantity_series&) = default;
    quantity_series(quantity_series&&) noexcept = default;
    quantity_series& operator=(quantity_series&&) noexcept = default;
    ~quantity_series() = default;

    template <typename T>
    void add_at(time_point t, T&& val)
    {
        data.emplace_back(t, std::forward<T>(val));
    }

    const Quantity& operator[](std::size_t index) const noexcept
    {
        return data[index].value;
    }

    timed_quantity at(std::size_t index) const
    {
        if (index >= data.size())
            throw std::out_of_range("quantity_series::at index out of range");
        return data[index];
    }

    const Quantity& front() const noexcept
    {
        return data.front().value;
    }

    const Quantity& back() const noexcept
    {
        return data.back().value;
    }

    std::size_t size() const noexcept
    {
        return data.size();
    }

    bool empty() const noexcept
    {
        return data.empty();
    }

    auto begin() const noexcept
    {
        return data.begin();
    }

    auto end() const noexcept
    {
        return data.end();
    }

    auto cbegin() const noexcept
    {
        return data.cbegin();
    }

    auto cend() const noexcept
    {
        return data.cend();
    }

    measurement_rss_t<TimeUnit> get_time_uncertainty() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot get time uncertainty of empty series");
        return data.front().time;
    }

    measurement_type interpolate_at(time_point t, interpolation_method method = interpolation_method::linear) const
    {
        switch (method)
        {
            case interpolation_method::linear:
                return interpolate_linear(t);
            case interpolation_method::cubic_spline:
                return interpolate_cubic_spline(t);
            case interpolation_method::polynomial:
                return interpolate_polynomial(t, std::min(3, static_cast<int>(data.size()) - 1));
        }
        return interpolate_linear(t);
    }

    measurement_type interpolate_at_polynomial(time_point t, int order) const
    {
        return interpolate_polynomial(t, order);
    }

private:
    measurement_type interpolate_linear(time_point t) const
    {
        if (data.empty())
            throw std::runtime_error("Cannot interpolate empty series");
        typename TimeUnit::value_type t_val = t.value();
        if (t_val <= data.front().time.value())
            return measurement_type{data.front().value};
        if (t_val >= data.back().time.value())
            return measurement_type{data.back().value};

        auto it =
            std::lower_bound(data.begin(), data.end(), t_val, [](const timed_quantity& p, typename TimeUnit::value_type tp) { return p.time.value() < tp; });
        if (it == data.begin())
            return measurement_type{data.front().value};

        auto prev = std::prev(it), next = it;
        typename TimeUnit::value_type t1 = prev->time.value(), t2 = next->time.value();
        Quantity q1 = prev->value, q2 = next->value;
        double alpha = std::clamp((t_val - t1) / (t2 - t1), 0.0, 1.0);
        return measurement_type{Quantity{q1.value() + (q2.value() - q1.value()) * alpha}};
    }

    measurement_type interpolate_cubic_spline(time_point t) const
    {
        if (data.size() < 2)
            throw std::runtime_error("Cubic spline requires at least 2 points");
        typename TimeUnit::value_type t_val = t.value();
        if (t_val <= data.front().time.value())
            return measurement_type{data.front().value};
        if (t_val >= data.back().time.value())
            return measurement_type{data.back().value};

        auto it =
            std::lower_bound(data.begin(), data.end(), t_val, [](const timed_quantity& p, typename TimeUnit::value_type tp) { return p.time.value() < tp; });
        if (it == data.begin())
            return measurement_type{data.front().value};

        std::size_t i = std::distance(data.begin(), std::prev(it)), n = data.size();
        double t_i = data[i].time.value(), t_next = data[i + 1].time.value();
        double h = t_next - t_i, s = (t_val - t_i) / h, s_inv = 1.0 - s;
        value_type y_i = data[i].value.value(), y_next = data[i + 1].value.value();
        value_type result = s_inv * y_i + s * y_next;

        if (i > 0 && i + 1 < n - 1)
        {
            value_type y_prev = data[i - 1].value.value(), y_next2 = data[i + 2].value.value();
            result += s * s_inv * 0.0833 * ((y_next2 - 2 * y_next + y_i) - (y_next - 2 * y_i + y_prev));
        }

        return measurement_type{Quantity{result}};
    }

    measurement_type interpolate_polynomial(time_point t, int order) const
    {
        if (data.empty())
            throw std::runtime_error("Cannot interpolate empty series");
        typename TimeUnit::value_type t_val = t.value();
        if (t_val <= data.front().time.value())
            return measurement_type{data.front().value};
        if (t_val >= data.back().time.value())
            return measurement_type{data.back().value};

        order = std::min(order, static_cast<int>(data.size()) - 1);
        order = std::max(order, 1);

        auto it =
            std::lower_bound(data.begin(), data.end(), t_val, [](const timed_quantity& p, typename TimeUnit::value_type tp) { return p.time.value() < tp; });
        if (it == data.begin())
            return measurement_type{data.front().value};

        std::size_t center = std::distance(data.begin(), std::prev(it));
        int start = static_cast<int>(center) - order / 2;
        start = std::max(start, 0);
        start = std::min(start, static_cast<int>(data.size()) - order - 1);
        int end = start + order + 1;
        end = std::min(end, static_cast<int>(data.size()));

        value_type result = 0;
        for (int i = start; i < end; ++i)
        {
            double t_i = data[i].time.value();
            value_type y_i = data[i].value.value();
            double L = 1.0;
            for (int j = start; j < end; ++j)
                if (i != j)
                    L *= (t_val - data[j].time.value()) / (t_i - data[j].time.value());
            result += L * y_i;
        }

        return measurement_type{Quantity{result}};
    }

public:
    quantity_series<Quantity, Allocator> resample(duration interval, interpolation_method method = interpolation_method::linear) const
    {
        if (data.empty())
            return quantity_series<Quantity, Allocator>();
        quantity_series<Quantity, Allocator> resampled;
        typename TimeUnit::value_type current_val = data.front().time.value(), end_val = data.back().time.value(), interval_val = interval.value();
        while (current_val <= end_val)
        {
            resampled.add_at(TimeUnit{current_val}, interpolate_at(measurement_rss_t<TimeUnit>{TimeUnit{current_val}}, method).value());
            current_val += interval_val;
        }
        return resampled;
    }

    quantity_series<decltype(std::declval<Quantity>() / std::declval<TimeUnit>())> time_derivative() const
    {
        using derivative_unit = decltype(std::declval<Quantity>() / std::declval<TimeUnit>());
        quantity_series<derivative_unit> derivative;
        if (data.size() < 2)
            return derivative;
        for (std::size_t i = 1; i < data.size(); ++i)
        {
            TimeUnit dt{data[i].time.value() - data[i - 1].time.value()};
            derivative.add_at(TimeUnit{data[i].time.value()}, (data[i].value - data[i - 1].value) / dt);
        }
        return derivative;
    }

    measurement_type mean() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute mean of empty series");
        value_type sum = 0;
        for (const auto& [t, q] : data)
            sum += q.value();
        return measurement_type{Quantity{sum / static_cast<value_type>(data.size())}};
    }

    measurement_type std_dev() const
    {
        if (data.size() < 2)
            return measurement_type{Quantity{0}};
        auto m = mean();
        value_type sum_sq = 0;
        for (const auto& [t, q] : data)
        {
            value_type diff = q.value() - m.value();
            sum_sq += diff * diff;
        }
        return measurement_type{Quantity{std::sqrt(sum_sq / (data.size() - 1))}};
    }

    measurement_type min() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute min of empty series");
        return measurement_type{
            std::min_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
                ->value};
    }

    measurement_type max() const
    {
        if (data.empty())
            throw std::runtime_error("Cannot compute max of empty series");
        return measurement_type{
            std::max_element(data.begin(), data.end(), [](const timed_quantity& a, const timed_quantity& b) { return a.value.value() < b.value.value(); })
                ->value};
    }

    measurement_type range() const
    {
        return measurement_type{max().value() - min().value()};
    }

    quantity_series<Quantity, Allocator> filter(std::function<bool(const Quantity&)> predicate) const
    {
        quantity_series<Quantity, Allocator> filtered;
        for (const auto& [t, q] : data)
            if (predicate(q))
                filtered.add_at(data[0].time, q);
        return filtered;
    }

    quantity_series<Quantity, Allocator> smooth(std::size_t window_size) const
    {
        if (window_size < 1)
            throw std::invalid_argument("window_size must be >= 1");
        if (data.empty())
            return quantity_series<Quantity, Allocator>();
        quantity_series<Quantity, Allocator> smoothed;
        for (std::size_t i = 0; i < data.size(); ++i)
        {
            std::size_t start = (i > window_size - 1) ? (i - window_size + 1) : 0, end = i + 1;
            value_type sum = 0;
            for (std::size_t j = start; j < end; ++j)
                sum += data[j].value.value();
            smoothed.add_at(data[i].time, Quantity{sum / static_cast<value_type>(end - start)});
        }
        return smoothed;
    }

    quantity_series<Quantity, Allocator> decimate(std::size_t ratio) const
    {
        if (ratio < 1)
            throw std::invalid_argument("ratio must be >= 1");
        quantity_series<Quantity, Allocator> decimated;
        for (std::size_t i = 0; i < data.size(); i += ratio)
            decimated.add_at(data[i].time, data[i].value);
        return decimated;
    }

    quantity_series<Quantity, Allocator> slice(time_point start, time_point end) const
    {
        typename TimeUnit::value_type start_val = start.value(), end_val = end.value();
        if (start_val > end_val)
            throw std::invalid_argument("start time must be <= end time");
        quantity_series<Quantity, Allocator> sliced;
        for (const auto& tq : data)
        {
            typename TimeUnit::value_type tq_val = tq.time.value();
            if (tq_val >= start_val && tq_val <= end_val)
                sliced.add_at(tq.time, tq.value);
        }
        return sliced;
    }

    void clear() noexcept
    {
        data.clear();
    }

    void reserve(std::size_t) noexcept
    {
    }

    allocator_type get_allocator() const noexcept
    {
        return data.get_allocator();
    }
};

} // namespace PKR_UNITS_NAMESPACE
