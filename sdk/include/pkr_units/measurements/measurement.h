#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>
#include <sstream>
#include <iostream>
#include <format>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/math/unit/unit_math.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// measurement_t: A class for tracking measurements with uncertainties
// ============================================================================
// This class wraps unit_t types and provides automatic uncertainty propagation
// through arithmetic operations using dimensional analysis.

struct is_measurement_t_tag
{
};

template<typename T>
concept is_measurement_c = std::is_base_of_v<is_measurement_t_tag, T>;

template <typename UnitT>
class measurement_t : public is_measurement_t_tag
{
private:
    using stored_unit_t = std::remove_cv_t<UnitT>;
    stored_unit_t m_value;       // The measured value with units
    stored_unit_t m_uncertainty; // Uncertainty as same unit type

public:
    // Type aliases
    using value_type = stored_unit_t;
    using uncertainty_type = stored_unit_t;

    // Default constructor
    constexpr measurement_t() = default;

    // Construction: uncertainty must be compatible unit type
    constexpr measurement_t(stored_unit_t value, stored_unit_t uncertainty)
        : m_value(value)
        , m_uncertainty(uncertainty)
    {
        // Ensure uncertainty is non-negative
        if (uncertainty.value() < 0)
        {
            m_uncertainty = stored_unit_t{0};
        }
    }

    // Construction from raw values (convenience constructor)
    constexpr measurement_t(typename stored_unit_t::value_type value, typename stored_unit_t::value_type uncertainty)
        : m_value(stored_unit_t{value})
        , m_uncertainty(stored_unit_t{uncertainty})
    {
        // Ensure uncertainty is non-negative
        if (uncertainty < 0)
        {
            m_uncertainty = stored_unit_t{0};
        }
    }

    // Copy constructor
    constexpr measurement_t(const measurement_t&) = default;

    // Move constructor
    constexpr measurement_t(measurement_t&&) = default;

    // Copy assignment
    constexpr measurement_t& operator=(const measurement_t&) = default;

    // Move assignment
    constexpr measurement_t& operator=(measurement_t&&) = default;

    // ============================================================================
    // Arithmetic Operations with Uncertainty Propagation
    // ============================================================================

    // Addition: uncertainties combine in quadrature (RSS)
    template <typename OtherUnitT>
    constexpr auto operator+(const measurement_t<OtherUnitT>& other) const
    {
        // Values add using existing unit_t arithmetic
        auto result_value = (m_value + other.unit_value()).in_base_si_units();

        // Uncertainties combine in quadrature: σ_total = √(σ₁² + σ₂²)
        using result_type = decltype(result_value);

        // Convert both uncertainties to result units
        auto uncertainty1_converted = result_type{m_uncertainty};
        auto uncertainty2_converted = result_type{other.unit_uncertainty()};

        // Calculate uncertainty magnitude (dimensionless values)
        auto u1_squared = uncertainty1_converted.value() * uncertainty1_converted.value();
        auto u2_squared = uncertainty2_converted.value() * uncertainty2_converted.value();
        auto total_uncertainty_value = std::sqrt(u1_squared + u2_squared);

        return measurement_t<result_type>{result_value, result_type{total_uncertainty_value}};
    }

    // Subtraction: uncertainties combine in quadrature (RSS)
    template <typename OtherUnitT>
    constexpr auto operator-(const measurement_t<OtherUnitT>& other) const
    {
        // Values subtract using existing unit_t arithmetic
        auto result_value = (m_value - other.unit_value()).in_base_si_units();

        // Uncertainties combine in quadrature: σ_total = √(σ₁² + σ₂²)
        using result_type = decltype(result_value);

        // Convert both uncertainties to result units
        auto uncertainty1_converted = result_type{m_uncertainty};
        auto uncertainty2_converted = result_type{other.unit_uncertainty()};

        // Calculate uncertainty magnitude (dimensionless values)
        auto u1_squared = uncertainty1_converted.value() * uncertainty1_converted.value();
        auto u2_squared = uncertainty2_converted.value() * uncertainty2_converted.value();
        auto total_uncertainty_value = std::sqrt(u1_squared + u2_squared);

        return measurement_t<result_type>{result_value, result_type{total_uncertainty_value}};
    }

    // Multiplication: relative uncertainties add
    template <typename OtherUnitT>
    constexpr auto operator*(const measurement_t<OtherUnitT>& other) const
    {
        // Values multiply using existing unit_t arithmetic
        auto result_value = (m_value * other.unit_value()).in_base_si_units();

        // Relative uncertainties add: δ(a×b)/(a×b) = δa/a + δb/b
        using result_type = decltype(result_value);
        auto rel_uncertainty1 = relative_uncertainty().value();       // dimensionless
        auto rel_uncertainty2 = other.relative_uncertainty().value(); // dimensionless

        auto total_rel_uncertainty = rel_uncertainty1 + rel_uncertainty2;
        auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

        return measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
    }

    // Division: relative uncertainties add
    template <typename OtherUnitT>
    constexpr auto operator/(const measurement_t<OtherUnitT>& other) const
    {
        // Values divide using existing unit_t arithmetic
        auto result_value = (m_value / other.unit_value()).in_base_si_units();

        // Relative uncertainties add: δ(a/b)/(a/b) = δa/a + δb/b
        using result_type = decltype(result_value);
        auto rel_uncertainty1 = relative_uncertainty().value();       // dimensionless
        auto rel_uncertainty2 = other.relative_uncertainty().value(); // dimensionless

        auto total_rel_uncertainty = rel_uncertainty1 + rel_uncertainty2;
        auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

        return measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
    }

    // Unary negation
    constexpr measurement_t operator-() const noexcept
    {
        return measurement_t{-m_value, m_uncertainty};
    }

    // ============================================================================
    // Accessors
    // ============================================================================

    // Get the measured value as raw double (convenience)
    constexpr auto value() const
    {
        return m_value.value();
    }

    // Get the uncertainty as raw double (convenience)
    constexpr auto uncertainty() const
    {
        return m_uncertainty.value();
    }

    // Get the measured value with units
    constexpr const stored_unit_t& unit_value() const
    {
        return m_value;
    }

    // Get the uncertainty with units
    constexpr const stored_unit_t& unit_uncertainty() const
    {
        return m_uncertainty;
    }

    // Get relative uncertainty (dimensionless)
    constexpr auto relative_uncertainty() const
    {
        // Special case: if value is zero, treat relative uncertainty as 0 to avoid NaN/inf.
        // Using NaN/inf would require additional checks across the math pipeline and add overhead.
        if (m_value.value() == static_cast<typename stored_unit_t::value_type>(0))
        {
            using result_type = decltype(m_uncertainty / m_value);
            return result_type{static_cast<typename stored_unit_t::value_type>(0)};
        }
        return m_uncertainty / m_value;
    }

    // Get combined uncertainty estimate in the same units as the measurement
    constexpr const stored_unit_t& combined_uncertainty() const
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
// Free Functions for measurement_t
// ============================================================================

// Comparison operators
template <typename UnitT>
constexpr bool operator==(const measurement_t<UnitT>& lhs, const measurement_t<UnitT>& rhs)
{
    return lhs.unit_value() == rhs.unit_value() && lhs.unit_uncertainty() == rhs.unit_uncertainty();
}

template <typename UnitT>
constexpr bool operator!=(const measurement_t<UnitT>& lhs, const measurement_t<UnitT>& rhs)
{
    return !(lhs == rhs);
}

// Output stream operator
template <typename UnitT>
std::ostream& operator<<(std::ostream& os, const measurement_t<UnitT>& measurement)
{
    using stored_t = std::remove_cv_t<UnitT>;
    os << measurement.value() << " +/- " << measurement.uncertainty() << " " << stored_t::symbol;
    return os;
}

// Scalar operations
template <typename UnitT, typename T>
requires (std::is_arithmetic_v<T> || pkr::units::is_pkr_unit_c<T>)
auto operator*(const measurement_t<UnitT>& lhs, T rhs) {
    return measurement_t<UnitT>(lhs.value() * rhs, lhs.uncertainty() * std::abs(rhs));
}

template <typename T, typename UnitT>
requires (std::is_arithmetic_v<T> || pkr::units::is_pkr_unit_c<T>)
auto operator*(T lhs, const measurement_t<UnitT>& rhs) {
    return rhs * lhs;
}

template <typename UnitT, typename T>
requires (std::is_arithmetic_v<T> || pkr::units::is_pkr_unit_c<T>)
auto operator/(const measurement_t<UnitT>& lhs, T rhs) {
    return measurement_t<UnitT>(lhs.value() / rhs, lhs.uncertainty() / std::abs(rhs));
}

template <typename T, typename UnitT>
requires is_unit_value_type_c<T>
auto operator/(T lhs, const measurement_t<UnitT>& rhs) {
    // For scalar / measurement, result is measurement with inverse unit
    using stored_t = std::remove_cv_t<UnitT>;
    using value_type = typename details::is_pkr_unit<stored_t>::value_type;
    using ratio_type = typename details::is_pkr_unit<stored_t>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<stored_t>::value_dimension;
    constexpr dimension_t inv_dim{
        -dim.length, -dim.mass, -dim.time, -dim.current, -dim.temperature, -dim.amount, -dim.intensity, -dim.angle
    };
    using inv_ratio = std::ratio_divide<std::ratio<1>, ratio_type>;
    using InvUnit = details::unit_t<value_type, inv_ratio, inv_dim>;
    return measurement_t<InvUnit>(lhs / rhs.value(), lhs * rhs.uncertainty() / (rhs.value() * rhs.value()));
}

} // namespace PKR_UNITS_NAMESPACE

// std::formatter specialization for measurement_t
namespace std
{

template <typename UnitT, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::measurement_t<UnitT>, CharT>
{
    using stored_t = std::remove_cv_t<UnitT>;
    std::formatter<typename stored_t::value_type, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement, FormatContext& ctx) const
    {
        auto out = ctx.out();

        // Format the value part using the value formatter (which handles format specifiers)
        out = value_formatter.format(measurement.value(), ctx);

        // Add uncertainty with appropriate ± symbol, also using the value formatter
        if constexpr (std::is_same_v<CharT, char>)
        {
            out = std::format_to(out, " +/- ");
            out = value_formatter.format(measurement.uncertainty(), ctx);
        }
        else if constexpr (std::is_same_v<CharT, char8_t>)
        {
            // For UTF-8, use ± symbol
            out = std::format_to(out, u8" \u00B1 ");
            out = value_formatter.format(measurement.uncertainty(), ctx);
        }
        else if constexpr (std::is_same_v<CharT, char16_t>)
        {
            // For UTF-16, use ± symbol
            out = std::format_to(out, u" \u00B1 ");
            out = value_formatter.format(measurement.uncertainty(), ctx);
        }
        else if constexpr (std::is_same_v<CharT, char32_t>)
        {
            // For UTF-32, use ± symbol
            out = std::format_to(out, U" \u00B1 ");
            out = value_formatter.format(measurement.uncertainty(), ctx);
        }
        else
        {
            // For wide char (wchar_t), use ± symbol
            out = std::format_to(out, L" \u00B1 ");
            out = value_formatter.format(measurement.uncertainty(), ctx);
        }

        // Add unit symbol
        *out++ = static_cast<CharT>(' ');
        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::copy(stored_t::symbol.begin(), stored_t::symbol.end(), out);
        }
        else if constexpr (std::is_same_v<CharT, char8_t>)
        {
            return std::copy(stored_t::u8_symbol.begin(), stored_t::u8_symbol.end(), out);
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::copy(stored_t::w_symbol.begin(), stored_t::w_symbol.end(), out);
        }
        else
        {
            for (char ch : stored_t::symbol)
            {
                *out++ = static_cast<CharT>(ch);
            }
            return out;
        }
    }
};

} // namespace std
