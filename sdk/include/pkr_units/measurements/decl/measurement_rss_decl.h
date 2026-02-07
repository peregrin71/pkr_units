#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>
#include <cassert>
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
// measurement_rss_t: A measurement class with RSS uncertainty propagation
// ============================================================================
// This class wraps unit_t types and provides automatic uncertainty propagation
// through arithmetic operations using RSS (Root Sum of Squares) for combining
// uncertainties from independent sources.
//
// Uncertainty Combination Strategy (RSS):
// - Addition/Subtraction: Ïƒ_total = âˆš(Ïƒâ‚Â² + Ïƒâ‚‚Â²)
// - Multiplication/Division: relative uncertainties combine as RSS
// - Powers: relative uncertainties scale by the power factor (fully correlated)

namespace details
{

struct is_measurement_rss_t_tag
{
};

} // namespace details

template <typename T>
concept is_measurement_rss_c = std::is_base_of_v<details::is_measurement_rss_t_tag, T>;

template <is_pkr_unit_c UnitT>
class measurement_rss_t : public details::is_measurement_rss_t_tag
{
private:
    UnitT m_value;       // The measured value with units
    UnitT m_uncertainty; // Uncertainty as same unit type

public:
    // Default constructor
    constexpr measurement_rss_t() = default;

    // Construction: uncertainty must be compatible unit type
    constexpr measurement_rss_t(UnitT value, UnitT uncertainty)
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
    constexpr measurement_rss_t(typename UnitT::value_type value, typename UnitT::value_type uncertainty)
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
    constexpr measurement_rss_t(const measurement_rss_t&) = default;

    // Move constructor
    constexpr measurement_rss_t(measurement_rss_t&&) = default;

    // Copy assignment
    constexpr measurement_rss_t& operator=(const measurement_rss_t&) = default;

    // Move assignment
    constexpr measurement_rss_t& operator=(measurement_rss_t&&) = default;

    // ============================================================================
    // Arithmetic Operations with RSS Uncertainty Propagation
    // ============================================================================

    // Addition: uncertainties combine in quadrature (RSS)
    // Ïƒ_total = âˆš(Ïƒâ‚Â² + Ïƒâ‚‚Â²)
    // Requires: OtherUnitT must be a PKR unit with same dimensions as UnitT
    // Result type: UnitT (LHS type, consistent with unit math convention)
    template <typename OtherUnitT>
        requires is_pkr_unit_c<OtherUnitT> && same_dimensions_c<UnitT, OtherUnitT>
    constexpr auto operator+(const measurement_rss_t<OtherUnitT>& other) const
    {
        // Values add using existing unit_t arithmetic
        // unit_t addition returns LHS type: UnitT + OtherUnitT -> UnitT
        auto result_value = m_value + other.unit_value();

        // Uncertainties combine in quadrature: Ïƒ_total = âˆš(Ïƒâ‚Â² + Ïƒâ‚‚Â²)
        // Convert other's uncertainty to LHS unit type for comparison
        auto uncertainty1_value = m_uncertainty.value();
        auto uncertainty2_value = UnitT{other.unit_uncertainty()}.value();

        // Calculate total uncertainty
        auto u1_squared = uncertainty1_value * uncertainty1_value;
        auto u2_squared = uncertainty2_value * uncertainty2_value;
        auto total_uncertainty_value = std::sqrt(u1_squared + u2_squared);

        return measurement_rss_t<UnitT>{result_value, UnitT{total_uncertainty_value}};
    }

    // Subtraction: uncertainties combine in quadrature (RSS)
    // Ïƒ_total = âˆš(Ïƒâ‚Â² + Ïƒâ‚‚Â²)
    // Requires: OtherUnitT must be a PKR unit with same dimensions as UnitT
    // Result type: UnitT (LHS type, consistent with unit math convention)
    template <typename OtherUnitT>
        requires is_pkr_unit_c<OtherUnitT> && same_dimensions_c<UnitT, OtherUnitT>
    constexpr auto operator-(const measurement_rss_t<OtherUnitT>& other) const
    {
        // Values subtract using existing unit_t arithmetic
        // unit_t subtraction returns LHS type: UnitT - OtherUnitT -> UnitT
        auto result_value = m_value - other.unit_value();

        // Uncertainties combine in quadrature: Ïƒ_total = âˆš(Ïƒâ‚Â² + Ïƒâ‚‚Â²)
        // Convert other's uncertainty to LHS unit type for comparison
        auto uncertainty1_value = m_uncertainty.value();
        auto uncertainty2_value = UnitT{other.unit_uncertainty()}.value();

        // Calculate total uncertainty
        auto u1_squared = uncertainty1_value * uncertainty1_value;
        auto u2_squared = uncertainty2_value * uncertainty2_value;
        auto total_uncertainty_value = std::sqrt(u1_squared + u2_squared);

        return measurement_rss_t<UnitT>{result_value, UnitT{total_uncertainty_value}};
    }

    // Multiplication: relative uncertainties combine in quadrature (RSS)
    // For uncorrelated variables: Î´(aÃ—b)/(aÃ—b) = âˆš((Î´a/a)Â² + (Î´b/b)Â²)
    // Special case: if multiplying by self (m * m), use fully correlated approach (squared())
    template <typename OtherUnitT>
    constexpr auto operator*(const measurement_rss_t<OtherUnitT>& other) const
    {
        // Values multiply using existing unit_t arithmetic
        auto result_value = (m_value * other.unit_value()).in_base_si_units();
        using result_type = decltype(result_value);

        // Compute first relative uncertainty (always needed)
        auto rel_uncertainty1 = relative_uncertainty().value();

        // Detect self-multiplication only when types match
        if constexpr (std::is_same_v<UnitT, OtherUnitT>)
        {
            if (this == reinterpret_cast<const measurement_rss_t<UnitT>*>(&other))
            {
                // This is m * m (fully correlated) - use square approach
                auto result_uncertainty_value = result_value.value() * (2.0 * rel_uncertainty1);
                return measurement_rss_t<result_type>{result_value, result_type{result_uncertainty_value}};
            }
        }

        // Relative uncertainties combine in quadrature for uncorrelated values
        auto rel_uncertainty2 = other.relative_uncertainty().value();
        auto total_rel_uncertainty = std::sqrt(rel_uncertainty1 * rel_uncertainty1 + rel_uncertainty2 * rel_uncertainty2);
        auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

        return measurement_rss_t<result_type>{result_value, result_type{result_uncertainty_value}};
    }

    // Division: relative uncertainties combine in quadrature (RSS)
    // For uncorrelated variables: Î´(a/b)/(a/b) = âˆš((Î´a/a)Â² + (Î´b/b)Â²)
    // Special case: if dividing by self (m / m), result is 1 with zero uncertainty
    template <typename OtherUnitT>
    constexpr auto operator/(const measurement_rss_t<OtherUnitT>& other) const
    {
        // Values divide using existing unit_t arithmetic
        auto result_value = (m_value / other.unit_value()).in_base_si_units();
        using result_type = decltype(result_value);

        // Detect self-division only when types match
        if constexpr (std::is_same_v<UnitT, OtherUnitT>)
        {
            if (this == reinterpret_cast<const measurement_rss_t<UnitT>*>(&other))
            {
                // Result is dimensionless 1.0 with zero uncertainty
                return measurement_rss_t<result_type>{result_type{1.0}, result_type{0.0}};
            }
        }

        // Relative uncertainties combine in quadrature for uncorrelated values
        auto rel_uncertainty1 = relative_uncertainty().value();       // dimensionless
        auto rel_uncertainty2 = other.relative_uncertainty().value(); // dimensionless

        auto total_rel_uncertainty = std::sqrt(rel_uncertainty1 * rel_uncertainty1 + rel_uncertainty2 * rel_uncertainty2);
        auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

        return measurement_rss_t<result_type>{result_value, result_type{result_uncertainty_value}};
    }

    // Unary negation
    constexpr measurement_rss_t operator-() const noexcept
    {
        return measurement_rss_t{-m_value, m_uncertainty};
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
    // Member API: RSS-specific math helpers
    // ============================================================================

    // Squared (fully correlated): f(x) = x^2, relative uncertainty = 2 * dx/x
    constexpr auto squared() const
    {
        auto x = unit_value();
        auto result_value = x * x;

        auto rel_unc = 2.0 * relative_uncertainty().value();
        auto result_uncertainty_value = result_value.value() * rel_unc;

        using ResultUnitT = decltype(result_value);
        return measurement_rss_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
    }

    // Cube (fully correlated): f(x) = x^3, relative uncertainty = 3 * dx/x
    constexpr auto cubed() const
    {
        auto x = unit_value();
        auto result_value = x * x * x;

        auto rel_unc = 3.0 * relative_uncertainty().value();
        auto result_uncertainty_value = result_value.value() * rel_unc;

        using ResultUnitT = decltype(result_value);
        return measurement_rss_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
    }

    // Power with compile-time integer exponent N (fully correlated)
    template <int N>
    constexpr auto pow() const
    {
        static_assert(N >= 0, "measurement_rss_t::pow<N>: N must be non-negative (use reciprocal for negative powers)");

        auto result_value = PKR_UNITS_NAMESPACE::pow<N>(unit_value());

        auto rel_unc = static_cast<typename UnitT::value_type>(N) * relative_uncertainty().value();
        auto result_uncertainty_value = result_value.value() * rel_unc;

        using ResultUnitT = decltype(result_value);
        return measurement_rss_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
    }

    // Square root: requires the unit type supports square root
    template <typename U = UnitT>
        requires pkr_unit_can_take_square_root_c<details::is_pkr_unit<U>::value_dimension>
    constexpr auto sqrt() const
    {
        auto result_value = PKR_UNITS_NAMESPACE::sqrt(unit_value());

        auto rel_unc = relative_uncertainty().value() / 2.0;
        auto result_uncertainty_value = result_value.value() * rel_unc;

        return measurement_rss_t<decltype(result_value)>{result_value, decltype(result_value){result_uncertainty_value}};
    }

    // Trigonometric helpers (angle types only)
    template <typename U = UnitT>
        requires PKR_UNITS_NAMESPACE::is_angle_unit_c<U>
    auto sin() const
    {
        auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::sin(value())};

        auto cos_x = std::cos(value());
        auto result_uncertainty_value = std::abs(cos_x) * uncertainty();

        return measurement_rss_t<PKR_UNITS_NAMESPACE::scalar_t<typename UnitT::value_type>>{
            result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
    }

    template <typename U = UnitT>
        requires PKR_UNITS_NAMESPACE::is_angle_unit_c<U>
    auto cos() const
    {
        auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::cos(value())};

        auto sin_x = std::sin(value());
        auto result_uncertainty_value = std::abs(sin_x) * uncertainty();

        return measurement_rss_t<PKR_UNITS_NAMESPACE::scalar_t<typename UnitT::value_type>>{
            result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
    }

    template <typename U = UnitT>
        requires PKR_UNITS_NAMESPACE::is_angle_unit_c<U>
    auto tan() const
    {
        auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::tan(value())};

        auto cos_x = std::cos(value());
        auto sec_squared = 1.0 / (cos_x * cos_x);
        auto result_uncertainty_value = sec_squared * uncertainty();

        return measurement_rss_t<PKR_UNITS_NAMESPACE::scalar_t<typename UnitT::value_type>>{
            result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
    }

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
// Free Functions for measurement_rss_t
// ============================================================================

// Comparison operators
template <typename UnitT>
constexpr bool operator==(const measurement_rss_t<UnitT>& lhs, const measurement_rss_t<UnitT>& rhs)
{
    return lhs.unit_value() == rhs.unit_value() && lhs.unit_uncertainty() == rhs.unit_uncertainty();
}

template <typename UnitT>
constexpr bool operator!=(const measurement_rss_t<UnitT>& lhs, const measurement_rss_t<UnitT>& rhs)
{
    return !(lhs == rhs);
}

// Output stream operator
template <typename UnitT>
std::ostream& operator<<(std::ostream& os, const measurement_rss_t<UnitT>& measurement)
{
    using stored_t = std::remove_cv_t<UnitT>;
    os << measurement.value() << " +/- " << measurement.uncertainty() << " " << stored_t::symbol;
    return os;
}

// Scalar operations (multiplication with scalars)
template <typename UnitT, typename T>
    requires(std::is_arithmetic_v<T> || pkr::units::is_base_pkr_unit_c<T>)
auto operator*(const measurement_rss_t<UnitT>& lhs, T rhs)
{
    return measurement_rss_t<UnitT>(lhs.value() * rhs, lhs.uncertainty() * std::abs(rhs));
}

template <typename T, typename UnitT>
    requires(std::is_arithmetic_v<T> || pkr::units::is_base_pkr_unit_c<T>)
auto operator*(T lhs, const measurement_rss_t<UnitT>& rhs)
{
    return rhs * lhs;
}

// Scalar operations (division)
template <typename UnitT, typename T>
    requires(std::is_arithmetic_v<T> || pkr::units::is_base_pkr_unit_c<T>)
auto operator/(const measurement_rss_t<UnitT>& lhs, T rhs)
{
    return measurement_rss_t<UnitT>(lhs.value() / rhs, lhs.uncertainty() / std::abs(rhs));
}

template <typename T, typename UnitT>
    requires is_unit_value_type_c<T>
auto operator/(T lhs, const measurement_rss_t<UnitT>& rhs)
{
    // For scalar / measurement, result is measurement with inverse unit
    using stored_t = std::remove_cv_t<UnitT>;
    using value_type = typename details::is_pkr_unit<stored_t>::value_type;
    using ratio_type = typename details::is_pkr_unit<stored_t>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<stored_t>::value_dimension;
    constexpr dimension_t inv_dim{-dim.length, -dim.mass, -dim.time, -dim.current, -dim.temperature, -dim.amount, -dim.intensity, -dim.angle};
    using inv_ratio = std::ratio_divide<std::ratio<1, 1>, ratio_type>;
    using InvUnit = details::unit_t<value_type, inv_ratio, inv_dim>;
    return measurement_rss_t<InvUnit>(lhs / rhs.value(), lhs * rhs.uncertainty() / (rhs.value() * rhs.value()));
}

// ============================================================================
// Utility Functions
// ============================================================================

template <typename UnitT>
constexpr auto combined_uncertainty_rss(const measurement_rss_t<UnitT>& measurement)
{
    return measurement.uncertainty();
}

template <typename UnitT>
constexpr typename UnitT::value_type relative_uncertainty_percent_rss(const measurement_rss_t<UnitT>& measurement)
{
    return measurement.relative_uncertainty().value() * 100.0;
}

} // namespace PKR_UNITS_NAMESPACE

// ============================================================================
// std::formatter specialization for measurement_rss_t
// ============================================================================
namespace std
{

template <typename UnitT, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::measurement_rss_t<UnitT>, CharT>
{
    using stored_t = std::remove_cv_t<UnitT>;
    std::formatter<typename stored_t::value_type, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::measurement_rss_t<UnitT>& measurement, FormatContext& ctx) const
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
