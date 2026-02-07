#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>
#include <sstream>
#include <iostream>
#include <format>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>
#include <pkr_units/units/math/unit_math.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// measurement_lin_t: A measurement class with linear uncertainty propagation
// ============================================================================
// This class wraps unit_t types and provides automatic uncertainty propagation
// through arithmetic operations using linear (worst-case) uncertainty combination
// for conservative error estimates.
//
// Uncertainty Combination Strategy (Linear/Worst-Case):
// - Addition/Subtraction: Ïƒ_total = Ïƒâ‚ + Ïƒâ‚‚
// - Multiplication/Division: relative uncertainties add linearly
// - Powers: relative uncertainties scale by the power factor (fully correlated)

namespace details
{

struct is_measurement_lin_t_tag
{
};

} // namespace details

template <typename T>
concept is_measurement_lin_c = std::is_base_of_v<details::is_measurement_lin_t_tag, T>;

template <is_pkr_unit_c UnitT>
class measurement_lin_t : public details::is_measurement_lin_t_tag
{
private:
    UnitT m_value;       // The measured value with units
    UnitT m_uncertainty; // Uncertainty as same unit type

public:
    // Default constructor
    constexpr measurement_lin_t() = default;

    // Construction: uncertainty must be compatible unit type
    constexpr measurement_lin_t(UnitT value, UnitT uncertainty)
        : m_value(value)
        , m_uncertainty(uncertainty)
    {
        // Ensure uncertainty is non-negative
        if (uncertainty.value() < 0)
        {
            m_uncertainty = UnitT{0};
        }
    }

    // Construction from raw values (convenience constructor)
    constexpr measurement_lin_t(typename UnitT::value_type value, typename UnitT::value_type uncertainty)
        : m_value(UnitT{value})
        , m_uncertainty(UnitT{uncertainty})
    {
        // Ensure uncertainty is non-negative
        if (uncertainty < 0)
        {
            m_uncertainty = UnitT{0};
        }
    }

    // Copy constructor
    constexpr measurement_lin_t(const measurement_lin_t&) = default;

    // Move constructor
    constexpr measurement_lin_t(measurement_lin_t&&) = default;

    // Copy assignment
    constexpr measurement_lin_t& operator=(const measurement_lin_t&) = default;

    // Move assignment
    constexpr measurement_lin_t& operator=(measurement_lin_t&&) = default;

    // ============================================================================
    // Arithmetic Operations with Linear Uncertainty Propagation
    // ============================================================================

    // Addition: uncertainties add linearly (worst-case)
    // Ïƒ_total = Ïƒâ‚ + Ïƒâ‚‚
    // Requires: OtherUnitT must be a PKR unit with same dimensions as UnitT
    // Result type: UnitT (LHS type, consistent with unit math convention)
    template <typename OtherUnitT>
        requires is_pkr_unit_c<OtherUnitT> && same_dimensions_c<UnitT, OtherUnitT>
    constexpr auto operator+(const measurement_lin_t<OtherUnitT>& other) const
    {
        // Values add using existing unit_t arithmetic
        // unit_t addition returns LHS type: UnitT + OtherUnitT -> UnitT
        auto result_value = m_value + other.unit_value();

        // Uncertainties add linearly
        // Convert other's uncertainty to LHS unit type
        auto uncertainty1_value = m_uncertainty.value();
        auto uncertainty2_value = UnitT{other.unit_uncertainty()}.value();

        // Calculate total uncertainty (linear addition)
        auto total_uncertainty_value = uncertainty1_value + uncertainty2_value;

        return measurement_lin_t<UnitT>{result_value, UnitT{total_uncertainty_value}};
    }

    // Subtraction: uncertainties add linearly (worst-case)
    // Ïƒ_total = Ïƒâ‚ + Ïƒâ‚‚
    // Requires: OtherUnitT must be a PKR unit with same dimensions as UnitT
    // Result type: UnitT (LHS type, consistent with unit math convention)
    template <typename OtherUnitT>
        requires is_pkr_unit_c<OtherUnitT> && same_dimensions_c<UnitT, OtherUnitT>
    constexpr auto operator-(const measurement_lin_t<OtherUnitT>& other) const
    {
        // Values subtract using existing unit_t arithmetic
        // unit_t subtraction returns LHS type: UnitT - OtherUnitT -> UnitT
        auto result_value = m_value - other.unit_value();

        // Uncertainties add linearly
        // Convert other's uncertainty to LHS unit type
        auto uncertainty1_value = m_uncertainty.value();
        auto uncertainty2_value = UnitT{other.unit_uncertainty()}.value();

        // Calculate total uncertainty (linear addition)
        auto total_uncertainty_value = uncertainty1_value + uncertainty2_value;

        return measurement_lin_t<UnitT>{result_value, UnitT{total_uncertainty_value}};
    }

    // Multiplication: relative uncertainties add linearly (worst-case)
    // Î´(aÃ—b)/(aÃ—b) = Î´a/a + Î´b/b
    // Special case: if multiplying by self (m * m), use fully correlated approach (doubled relative uncertainty)
    template <typename OtherUnitT>
    constexpr auto operator*(const measurement_lin_t<OtherUnitT>& other) const
    {
        // Values multiply using existing unit_t arithmetic
        auto result_value = (m_value * other.unit_value()).in_base_si_units();
        using result_type = decltype(result_value);

        // Compute first relative uncertainty (always needed)
        auto rel_uncertainty1 = relative_uncertainty().value();

        // Detect self-multiplication only when types match
        if constexpr (std::is_same_v<UnitT, OtherUnitT>)
        {
            if (this == reinterpret_cast<const measurement_lin_t<UnitT>*>(&other))
            {
                // This is m * m (fully correlated) - relative uncertainty doubles
                auto result_uncertainty_value = result_value.value() * (2.0 * rel_uncertainty1);
                return measurement_lin_t<result_type>{result_value, result_type{result_uncertainty_value}};
            }
        }

        // Relative uncertainties add linearly for worst-case
        auto rel_uncertainty2 = other.relative_uncertainty().value();
        auto total_rel_uncertainty = rel_uncertainty1 + rel_uncertainty2;
        auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

        return measurement_lin_t<result_type>{result_value, result_type{result_uncertainty_value}};
    }

    // Division: relative uncertainties add linearly (worst-case)
    // Î´(a/b)/(a/b) = Î´a/a + Î´b/b
    // Special case: if dividing by self (m / m), result is 1 with zero uncertainty
    template <typename OtherUnitT>
    constexpr auto operator/(const measurement_lin_t<OtherUnitT>& other) const
    {
        // Values divide using existing unit_t arithmetic
        auto result_value = (m_value / other.unit_value()).in_base_si_units();
        using result_type = decltype(result_value);

        // Detect self-division only when types match
        if constexpr (std::is_same_v<UnitT, OtherUnitT>)
        {
            if (this == reinterpret_cast<const measurement_lin_t<UnitT>*>(&other))
            {
                // Result is dimensionless 1.0 with zero uncertainty
                return measurement_lin_t<result_type>{result_type{1.0}, result_type{0.0}};
            }
        }

        // Relative uncertainties add linearly for worst-case
        auto rel_uncertainty1 = relative_uncertainty().value();       // dimensionless
        auto rel_uncertainty2 = other.relative_uncertainty().value(); // dimensionless

        auto total_rel_uncertainty = rel_uncertainty1 + rel_uncertainty2;
        auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

        return measurement_lin_t<result_type>{result_value, result_type{result_uncertainty_value}};
    }

    // Unary negation
    constexpr measurement_lin_t operator-() const noexcept
    {
        return measurement_lin_t{-m_value, m_uncertainty};
    }

    // ============================================================================
    // Accessors
    // ============================================================================

    // Get the measured value as raw value (convenience)
    constexpr auto value() const
    {
        return m_value.value();
    }

    // Get the uncertainty as raw value (convenience)
    constexpr auto uncertainty() const
    {
        return m_uncertainty.value();
    }

    // Get the measured value with units
    constexpr const UnitT& unit_value() const
    {
        return m_value;
    }

    // Get the uncertainty with units
    constexpr const UnitT& unit_uncertainty() const
    {
        return m_uncertainty;
    }

    // Get relative uncertainty (dimensionless)
    constexpr auto relative_uncertainty() const
    {
        // Special case: if value is zero, treat relative uncertainty as 0 to avoid NaN/inf.
        if (m_value.value() == static_cast<typename UnitT::value_type>(0))
        {
            using result_type = decltype(m_uncertainty / m_value);
            return result_type{static_cast<typename UnitT::value_type>(0)};
        }
        return m_uncertainty / m_value;
    }

    // Get combined uncertainty estimate in the same units as the measurement
    constexpr const UnitT& combined_uncertainty() const
    {
        return m_uncertainty;
    }

    // ============================================================================
    // Utility Functions
    // ============================================================================

    // Check if measurement is valid (non-zero uncertainty)
    constexpr bool is_valid() const
    {
        return m_uncertainty.value() >= 0;
    }

    // Get the value with uncertainty as a string representation
    std::string to_string() const
    {
        std::stringstream ss;
        ss << m_value.value() << " +/- " << m_uncertainty.value();
        return ss.str();
    }
};

// ============================================================================
// Free Functions for measurement_lin_t
// ============================================================================

// Comparison operators
template <typename UnitT>
constexpr bool operator==(const measurement_lin_t<UnitT>& lhs, const measurement_lin_t<UnitT>& rhs)
{
    return lhs.unit_value() == rhs.unit_value() && lhs.unit_uncertainty() == rhs.unit_uncertainty();
}

template <typename UnitT>
constexpr bool operator!=(const measurement_lin_t<UnitT>& lhs, const measurement_lin_t<UnitT>& rhs)
{
    return !(lhs == rhs);
}

// Output stream operator
template <typename UnitT>
std::ostream& operator<<(std::ostream& os, const measurement_lin_t<UnitT>& measurement)
{
    using stored_t = std::remove_cv_t<UnitT>;
    os << measurement.value() << " +/- " << measurement.uncertainty() << " " << stored_t::symbol;
    return os;
}

// Scalar operations (multiplication with scalars)
template <typename UnitT, typename T>
    requires(std::is_arithmetic_v<T> || pkr::units::is_base_pkr_unit_c<T>)
auto operator*(const measurement_lin_t<UnitT>& lhs, T rhs)
{
    return measurement_lin_t<UnitT>(lhs.value() * rhs, lhs.uncertainty() * std::abs(rhs));
}

template <typename T, typename UnitT>
    requires(std::is_arithmetic_v<T> || pkr::units::is_base_pkr_unit_c<T>)
auto operator*(T lhs, const measurement_lin_t<UnitT>& rhs)
{
    return rhs * lhs;
}

// Scalar operations (division)
template <typename UnitT, typename T>
    requires(std::is_arithmetic_v<T> || pkr::units::is_base_pkr_unit_c<T>)
auto operator/(const measurement_lin_t<UnitT>& lhs, T rhs)
{
    return measurement_lin_t<UnitT>(lhs.value() / rhs, lhs.uncertainty() / std::abs(rhs));
}

template <typename T, typename UnitT>
    requires is_unit_value_type_c<T>
auto operator/(T lhs, const measurement_lin_t<UnitT>& rhs)
{
    // For scalar / measurement, result is measurement with inverse unit
    using stored_t = std::remove_cv_t<UnitT>;
    using value_type = typename details::is_pkr_unit<stored_t>::value_type;
    using ratio_type = typename details::is_pkr_unit<stored_t>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<stored_t>::value_dimension;
    constexpr dimension_t inv_dim{-dim.length, -dim.mass, -dim.time, -dim.current, -dim.temperature, -dim.amount, -dim.intensity, -dim.angle};
    using inv_ratio = std::ratio_divide<std::ratio<1, 1>, ratio_type>;
    using InvUnit = details::unit_t<value_type, inv_ratio, inv_dim>;
    return measurement_lin_t<InvUnit>(lhs / rhs.value(), lhs * rhs.uncertainty() / (rhs.value() * rhs.value()));
}

// ============================================================================
// Linear-specific mathematical functions
// ============================================================================

// Square function with uncertainty propagation (fully correlated)
// For f(x) = x^2, the relative uncertainty df/f = 2 * dx/x
template <typename UnitT>
constexpr auto square_lin(const measurement_lin_t<UnitT>& measurement)
{
    auto x = measurement.unit_value();
    auto result_value = x * x;

    auto relative_uncertainty = 2.0 * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using ResultUnitT = decltype(result_value);
    return measurement_lin_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
}

// Sum of squares helper (x^2 + y^2 + z^2) for measurements of the same unit type
template <typename UnitT>
constexpr auto sum_of_squares_lin(const measurement_lin_t<UnitT>& x, const measurement_lin_t<UnitT>& y, const measurement_lin_t<UnitT>& z)
{
    auto x_sq = square_lin(x);
    auto y_sq = square_lin(y);
    auto z_sq = square_lin(z);
    auto xy_sum = x_sq + y_sq;
    return xy_sum + z_sq;
}

// Square root with uncertainty propagation
// For f(x) = sqrt(x), the relative uncertainty df/f = (1/2) * dx/x
template <typename UnitT>
    requires pkr_unit_can_take_square_root_c<details::is_pkr_unit<UnitT>::value_dimension>
constexpr auto sqrt_lin(const measurement_lin_t<UnitT>& measurement)
{
    auto result_value = sqrt(measurement.unit_value());

    auto relative_uncertainty = measurement.relative_uncertainty().value() / 2.0;
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    return measurement_lin_t<decltype(result_value)>{result_value, decltype(result_value){result_uncertainty_value}};
}

// Cube function with uncertainty propagation (fully correlated)
// For f(x) = x^3, the relative uncertainty df/f = 3 * dx/x
template <typename UnitT>
constexpr auto cube_lin(const measurement_lin_t<UnitT>& measurement)
{
    auto x = measurement.unit_value();
    auto result_value = x * x * x;

    auto relative_uncertainty = 3.0 * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using ResultUnitT = decltype(result_value);
    return measurement_lin_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
}

// Power function with compile-time integer exponent (fully correlated)
// For f(x) = x^N, the relative uncertainty df/f = |N| * dx/x
template <int N, typename UnitT>
constexpr auto pow_lin(const measurement_lin_t<UnitT>& measurement)
{
    auto result_value = pow<N>(measurement.unit_value());

    // For fully correlated uncertainty: relative_uncertainty(x^N) = |N| * relative_uncertainty(x)
    auto relative_uncertainty = static_cast<typename UnitT::value_type>(std::abs(N)) * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using ResultUnitT = decltype(result_value);
    return measurement_lin_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
}

// Trigonometric functions with uncertainty propagation
// For f(x) = sin(x), the uncertainty df = |cos(x)| * dx
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto sin_lin(const measurement_lin_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::sin(measurement.value())};

    auto cos_x = std::cos(measurement.value());
    auto result_uncertainty_value = std::abs(cos_x) * measurement.uncertainty();

    return measurement_lin_t<PKR_UNITS_NAMESPACE::scalar_t<typename UnitT::value_type>>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// For f(x) = cos(x), the uncertainty df = |sin(x)| * dx
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto cos_lin(const measurement_lin_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::cos(measurement.value())};

    auto sin_x = std::sin(measurement.value());
    auto result_uncertainty_value = std::abs(sin_x) * measurement.uncertainty();

    return measurement_lin_t<PKR_UNITS_NAMESPACE::scalar_t<typename UnitT::value_type>>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// For f(x) = tan(x), the uncertainty df = secÂ²(x) * dx
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto tan_lin(const measurement_lin_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::tan(measurement.value())};

    auto cos_x = std::cos(measurement.value());
    auto sec_squared = 1.0 / (cos_x * cos_x);
    auto result_uncertainty_value = sec_squared * measurement.uncertainty();

    return measurement_lin_t<PKR_UNITS_NAMESPACE::scalar_t<typename UnitT::value_type>>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// ============================================================================
// Utility Functions
// ============================================================================

template <typename UnitT>
constexpr auto combined_uncertainty_lin(const measurement_lin_t<UnitT>& measurement)
{
    return measurement.uncertainty();
}

template <typename UnitT>
constexpr typename UnitT::value_type relative_uncertainty_percent_lin(const measurement_lin_t<UnitT>& measurement)
{
    return measurement.relative_uncertainty().value() * 100.0;
}

} // namespace PKR_UNITS_NAMESPACE

// ============================================================================
// std::formatter specialization for measurement_lin_t
// ============================================================================
namespace std
{

template <typename UnitT, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::measurement_lin_t<UnitT>, CharT>
{
    using stored_t = std::remove_cv_t<UnitT>;
    std::formatter<typename stored_t::value_type, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::measurement_lin_t<UnitT>& measurement, FormatContext& ctx) const
    {
        auto out = ctx.out();

        // Format the value part using the value formatter (which handles format specifiers)
        out = value_formatter.format(measurement.value(), ctx);

        // Add uncertainty with appropriate Â± symbol using dispatch traits
        auto pm_symbol = PKR_UNITS_NAMESPACE::impl::char_traits_dispatch<CharT>::plus_minus();
        out = std::copy(pm_symbol.begin(), pm_symbol.end(), out);
        out = value_formatter.format(measurement.uncertainty(), ctx);

        // Add unit symbol
        *out++ = static_cast<CharT>(' ');
        if constexpr (std::is_same_v<CharT, char>)
            return std::copy(stored_t::symbol.begin(), stored_t::symbol.end(), out);
        else if constexpr (std::is_same_v<CharT, char8_t>)
            return std::copy(stored_t::u8_symbol.begin(), stored_t::u8_symbol.end(), out);
        else if constexpr (std::is_same_v<CharT, wchar_t>)
            return std::copy(stored_t::w_symbol.begin(), stored_t::w_symbol.end(), out);
        else
        {
            for (char ch : stored_t::symbol)
                *out++ = static_cast<CharT>(ch);
            return out;
        }
    }
};

} // namespace std
