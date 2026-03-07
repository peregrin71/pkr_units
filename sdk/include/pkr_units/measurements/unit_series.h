#pragma once

/**
 * @file unit_series.h
 * @brief Time series container for measurements with uncertainty
 * 
 * Extends quantity_series to propagate uncertainty through temporal operations.
 * Provides compile-time dimensional analysis for measurement sequences while
 * tracking uncertainty bounds.
 * 
 * @example
 *   // Create a measurement series
 *   measurement_series<meter_t> position_series;
 *   
 *   // Add measurements with explicit uncertainty
 *   position_series.add_at(t1, measurement(100.0_m, 0.1_m));
 *   position_series.add_at(t2, measurement(105.0_m, 0.1_m));
 *   position_series.add_now(measurement(110.0_m, 0.15_m));
 *   
 *   // Mean preserves uncertainty
 *   auto mean_pos = position_series.mean();  // measurement<meter_t>
 *   
 *   // Statistics include uncertainty propagation
 *   auto [min_val, min_uncert] = position_series.min_with_uncertainty();
 */

#include <pkr_units/units/unit_series.h>
#include <pkr_units/measurements/decl/measurement_lin_decl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/concepts/unit_concepts.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <stdexcept>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// measurement_series: Time series with uncertainty propagation
// ============================================================================
/**
 * @brief Time series container for measurements with uncertainty
 * 
 * Specializes quantity_series for measurement<Quantity> types, enabling automatic
 * uncertainty propagation through temporal operations.
 * 
 * Inherits all quantity_series operations:
 * - Interpolation at arbitrary times
 * - Time derivatives (with uncertainty)
 * - Resampling
 * - Filtering and smoothing
 * - Statistical analysis (mean, std_dev, min, max with uncertainties)
 * 
 * Additionally provides measurement-specific methods:
 * - uncertainty_bounds() - returns min/max with uncertainty envelopes
 * - Measurement-aware filtering and smoothing
 * 
 * @tparam Quantity Unit type (e.g., meter_t, kilogram_t)
 * @tparam Allocator Memory allocator (default: std::pmr::polymorphic_allocator<std::byte>)
 */
template <is_pkr_unit_c Quantity, typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
class measurement_series : public quantity_series<measurement_lin_t<Quantity>, Allocator>
{
private:
    using base_type = quantity_series<measurement_lin_t<Quantity>, Allocator>;
    using measurement_type = measurement_lin_t<Quantity>;

public:
    using quantity_type = Quantity;
    using value_type = typename Quantity::value_type;
    using time_point = typename base_type::time_point;
    using duration = typename base_type::duration;
    using allocator_type = Allocator;

    // ========================================================================
    // Construction
    // ========================================================================

    /**
     * @brief Default constructor with optional allocator
     */
    explicit measurement_series(const Allocator& alloc = Allocator())
        : base_type(alloc)
    {
    }

    // Inherit copy/move semantics from base
    measurement_series(const measurement_series&) = default;
    measurement_series& operator=(const measurement_series&) = default;
    measurement_series(measurement_series&&) noexcept = default;
    measurement_series& operator=(measurement_series&&) noexcept = default;

    ~measurement_series() = default;

    // ========================================================================
    // Add Measurements
    // ========================================================================

    /**
     * @brief Add measurement with uncertainty at explicit timestamp
     * 
     * @param t Timestamp
     * @param val Measurement with uncertainty
     */
    void add_at(time_point t, measurement_type val)
    {
        base_type::add_at(t, std::move(val));
    }

    /**
     * @brief Add measurement with uncertainty at current time
     * 
     * @param val Measurement with uncertainty
     */
    void add_now(measurement_type val)
    {
        base_type::add_now(std::move(val));
    }

    // ========================================================================
    // Access (Measurement-aware)
    // ========================================================================

    /**
     * @brief Access measurement by index
     */
    const measurement_type& operator[](std::size_t index) const noexcept
    {
        return base_type::operator[](index);
    }

    /**
     * @brief Access measurement and timestamp by index
     */
    std::pair<time_point, measurement_type> at(std::size_t index) const
    {
        return base_type::at(index);
    }

    /**
     * @brief Get first measurement
     */
    const measurement_type& front() const noexcept
    {
        return base_type::front();
    }

    /**
     * @brief Get last measurement
     */
    const measurement_type& back() const noexcept
    {
        return base_type::back();
    }

    // ========================================================================
    // Statistics with Uncertainty
    // ========================================================================

    /**
     * @brief Mean measurement (with propagated uncertainty)
     * 
     * The uncertainty in the mean is std_dev / sqrt(N) for N measurements.
     * Uses linear uncertainty propagation.
     */
    measurement_type mean() const
    {
        if (this->empty())
        {
            throw std::runtime_error("Cannot compute mean of empty series");
        }

        value_type sum = 0;
        value_type sum_sq = 0; // Sum of squared uncertainties
        std::size_t n = this->size();

        for (const auto& [t, m] : *this)
        {
            sum += m.value().value();
            sum_sq += m.uncertainty().value() * m.uncertainty().value();
        }

        value_type mean_value = sum / static_cast<value_type>(n);
        // Uncertainty in mean: sqrt(sum of squared uncertainties) / N
        value_type mean_uncertainty = std::sqrt(sum_sq) / static_cast<value_type>(n);

        return measurement_type(Quantity{mean_value}, Quantity{mean_uncertainty});
    }

    /**
     * @brief Standard deviation (with propagated uncertainty)
     * 
     * The uncertainty in std_dev depends on the higher moments of the distribution.
     * This provides a conservative estimate.
     */
    measurement_type std_dev() const
    {
        if (this->size() < 2)
        {
            return measurement_type(Quantity{0}, Quantity{0});
        }

        auto m = mean();
        value_type sum_sq = 0;
        value_type sum_uncert_sq = 0;

        for (const auto& [t, meas] : *this)
        {
            value_type diff = meas.value().value() - m.value().value();
            sum_sq += diff * diff;

            // Uncertainty propagation in (x - mean)^2
            // d(x^2)/dx = 2x, so uncertainty scales by 2|diff|
            value_type uncert = 2.0 * std::abs(diff) * meas.uncertainty().value();
            sum_uncert_sq += uncert * uncert;
        }

        value_type n = static_cast<value_type>(this->size());
        value_type variance = sum_sq / (n - 1);
        value_type std_dev_val = std::sqrt(variance);

        // Uncertainty in std_dev
        value_type std_dev_uncert = std::sqrt(sum_uncert_sq) / (2.0 * n);

        return measurement_type(Quantity{std_dev_val}, Quantity{std_dev_uncert});
    }

    /**
     * @brief Minimum measurement
     */
    measurement_type min() const
    {
        if (this->empty())
        {
            throw std::runtime_error("Cannot compute min of empty series");
        }

        return std::min_element(this->begin(), this->end(), [](const auto& a, const auto& b) { return a.second.value().value() < b.second.value().value(); })
            ->second;
    }

    /**
     * @brief Maximum measurement
     */
    measurement_type max() const
    {
        if (this->empty())
        {
            throw std::runtime_error("Cannot compute max of empty series");
        }

        return std::max_element(this->begin(), this->end(), [](const auto& a, const auto& b) { return a.second.value().value() < b.second.value().value(); })
            ->second;
    }

    /**
     * @brief Uncertainty bounds: (min_value - uncertainty, max_value + uncertainty)
     * 
     * Returns the lower and upper confidence bounds across the entire series.
     */
    std::pair<Quantity, Quantity> uncertainty_bounds() const
    {
        if (this->empty())
        {
            throw std::runtime_error("Cannot compute bounds of empty series");
        }

        auto min_meas = min();
        auto max_meas = max();

        Quantity lower = min_meas.value() - min_meas.uncertainty();
        Quantity upper = max_meas.value() + max_meas.uncertainty();

        return {lower, upper};
    }

    // ========================================================================
    // Filtering & Transformation (Measurement-aware)
    // ========================================================================

    /**
     * @brief Filter by measurement value (predicate ignores uncertainty)
     * 
     * @param predicate Function on (const measurement_type&)
     * @return New measurement series with matching points
     */
    measurement_series<Quantity, Allocator> filter(std::function<bool(const measurement_type&)> predicate) const
    {
        measurement_series<Quantity, Allocator> filtered;

        for (const auto& [t, meas] : *this)
        {
            if (predicate(meas))
            {
                filtered.add_at(t, meas);
            }
        }

        return filtered;
    }

    /**
     * @brief Moving average smoothing (propagates uncertainties)
     * 
     * Uncertainties are combined linearly through the window.
     * 
     * @param window_size Number of points in window
     * @return New smoothed measurement series
     */
    measurement_series<Quantity, Allocator> smooth(std::size_t window_size) const
    {
        if (window_size < 1)
        {
            throw std::invalid_argument("window_size must be >= 1");
        }
        if (this->empty())
        {
            return measurement_series<Quantity, Allocator>();
        }

        measurement_series<Quantity, Allocator> smoothed;

        for (std::size_t i = 0; i < this->size(); ++i)
        {
            std::size_t start = (i > window_size - 1) ? (i - window_size + 1) : 0;
            std::size_t end = i + 1;

            value_type sum = 0;
            value_type sum_uncert = 0;

            for (std::size_t j = start; j < end; ++j)
            {
                auto meas = (*this)[j];
                sum += meas.value().value();
                sum_uncert += meas.uncertainty().value(); // Linear combination
            }

            value_type n = static_cast<value_type>(end - start);
            value_type avg = sum / n;
            value_type avg_uncert = sum_uncert / n;

            smoothed.add_at(this->begin()[i]->first, measurement_type(Quantity{avg}, Quantity{avg_uncert}));
        }

        return smoothed;
    }

    /**
     * @brief Decimate series (keep every Nth point)
     * 
     * @param ratio Keep every ratio-th point (must be >= 1)
     * @return New decimated measurement series
     */
    measurement_series<Quantity, Allocator> decimate(std::size_t ratio) const
    {
        if (ratio < 1)
        {
            throw std::invalid_argument("ratio must be >= 1");
        }

        measurement_series<Quantity, Allocator> decimated;

        for (std::size_t i = 0; i < this->size(); i += ratio)
        {
            auto [t, meas] = this->at(i);
            decimated.add_at(t, meas);
        }

        return decimated;
    }

    /**
     * @brief Extract time-range subset
     * 
     * @param start Start time (inclusive)
     * @param end End time (inclusive)
     * @return New measurement series with points in [start, end]
     */
    measurement_series<Quantity, Allocator> slice(time_point start, time_point end) const
    {
        if (start > end)
        {
            throw std::invalid_argument("start time must be <= end time");
        }

        measurement_series<Quantity, Allocator> sliced;

        for (const auto& [t, meas] : *this)
        {
            if (t >= start && t <= end)
            {
                sliced.add_at(t, meas);
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
        base_type::clear();
    }

    /**
     * @brief Get allocator
     */
    allocator_type get_allocator() const noexcept
    {
        return base_type::get_allocator();
    }
};

} // namespace PKR_UNITS_NAMESPACE
