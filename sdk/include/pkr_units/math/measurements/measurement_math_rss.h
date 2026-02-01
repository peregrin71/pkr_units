#pragma once

#define PKR_UNITS_DETAIL_IS_RSS(x) PKR_UNITS_DETAIL_IS_RSS_IMPL(x)
#define PKR_UNITS_DETAIL_IS_RSS_IMPL(x) PKR_UNITS_DETAIL_IS_RSS_##x
#define PKR_UNITS_DETAIL_IS_RSS_rss 1
#define PKR_UNITS_DETAIL_IS_RSS_linear 0

#ifndef PKR_UNITS_MEASUREMENT_UNCERTAINTY_STRATEGY
#define PKR_UNITS_MEASUREMENT_UNCERTAINTY_STRATEGY rss
#elif PKR_UNITS_DETAIL_IS_RSS(PKR_UNITS_MEASUREMENT_UNCERTAINTY_STRATEGY) != 1
#error "Multiple measurement_math strategy headers included in the same translation unit."
#endif

#undef PKR_UNITS_DETAIL_IS_RSS
#undef PKR_UNITS_DETAIL_IS_RSS_IMPL
#undef PKR_UNITS_DETAIL_IS_RSS_rss
#undef PKR_UNITS_DETAIL_IS_RSS_linear

#include <cmath>
#include <type_traits>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/math/unit/unit_math.h>
#include <pkr_units/measurements/measurement.h>
#include <pkr_units/units/dimensionless/scalar.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Basic Arithmetic Functions (RSS uncertainty propagation for multiply/divide)
// ============================================================================

// Addition with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto add_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = a.unit_value() + b.unit_value();
    auto result_uncertainty = std::sqrt(a.uncertainty() * a.uncertainty() + b.uncertainty() * b.uncertainty());
    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty}};
}

// Subtraction with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto subtract_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = a.unit_value() - b.unit_value();
    auto result_uncertainty = std::sqrt(a.uncertainty() * a.uncertainty() + b.uncertainty() * b.uncertainty());
    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty}};
}

// Square function with uncertainty propagation
// For f(x) = x^2, the relative uncertainty df/f = 2 *
template <typename UnitT>
constexpr auto square_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto x = measurement.unit_value();
    auto result_value = x * x;

    auto relative_uncertainty = 2.0 * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using ResultUnitT = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
}

// Sum of squares helper (x^2 + y^2 + z^2) for measurements of the same unit type
// Uses constexpr RSS operations where available
template <typename UnitT>
constexpr auto sum_of_squares_rss(
    const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& x,
    const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& y,
    const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& z)
{
    return add_rss(add_rss(square_rss(x), square_rss(y)), square_rss(z));
}

// Multiplication with uncertainty propagation (RSS for relative uncertainties)
// These values MUST not be correlated. Do not use multiply_rss(a, a) for squaring;
// use square_rss(a) instead, as squaring requires correlated uncertainty propagation.
template <typename UnitT1, typename UnitT2>
auto multiply_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = (a.unit_value() * b.unit_value()).to_si();
    using result_type = decltype(result_value);

    auto rel_uncertainty1 = a.relative_uncertainty().value();
    auto rel_uncertainty2 = b.relative_uncertainty().value();
    auto total_rel_uncertainty = std::sqrt(rel_uncertainty1 * rel_uncertainty1 + rel_uncertainty2 * rel_uncertainty2);
    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Overload for multiplying measurement by scalar (zero uncertainty)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto multiply_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& a, T b)
{
    auto result_value = a.unit_value() * b;
    auto result_uncertainty = UnitT{a.uncertainty() * std::abs(static_cast<double>(b))};
    return PKR_UNITS_NAMESPACE::measurement_t<UnitT>{result_value, result_uncertainty};
}

// Overload for multiplying scalar by measurement (zero uncertainty)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto multiply_rss(T a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& b)
{
    auto result_value = a * b.unit_value();
    auto result_uncertainty = UnitT{b.uncertainty() * std::abs(static_cast<double>(a))};
    return PKR_UNITS_NAMESPACE::measurement_t<UnitT>{result_value, result_uncertainty};
}

// Division with uncertainty propagation (RSS for relative uncertainties)
template <typename UnitT1, typename UnitT2>
constexpr auto divide_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = (a.unit_value() / b.unit_value()).to_si();
    using result_type = decltype(result_value);

    auto rel_uncertainty1 = a.relative_uncertainty().value();
    auto rel_uncertainty2 = b.relative_uncertainty().value();
    auto total_rel_uncertainty = std::sqrt(rel_uncertainty1 * rel_uncertainty1 + rel_uncertainty2 * rel_uncertainty2);
    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Overload for dividing measurement by scalar (zero uncertainty)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto divide_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& a, T b)
{
    auto result_value = a.unit_value() / b;
    auto result_uncertainty = UnitT{a.uncertainty() / std::abs(static_cast<double>(b))};
    return PKR_UNITS_NAMESPACE::measurement_t<UnitT>{result_value, result_uncertainty};
}

// Overload for dividing scalar by measurement (zero uncertainty for scalar)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto divide_rss(T a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& b)
{
    auto result_value = a / b.unit_value();
    auto result_relative_uncertainty = b.relative_uncertainty();
    auto result_uncertainty_value = decltype(result_value){result_relative_uncertainty.value() * std::abs(result_value.value())};
    return PKR_UNITS_NAMESPACE::measurement_t<decltype(result_value)>{result_value, result_uncertainty_value};
}

// ============================================================================
// Mathematical Functions with Uncertainty Propagation
// ============================================================================

// Square root with uncertainty propagation
// For f(x) = sqrt(x), the relative uncertainty df/f = (1/2) * dx/x
template <typename UnitT>
    requires pkr_unit_can_take_square_root_c<details::is_pkr_unit<UnitT>::value_dimension>
constexpr auto sqrt_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = sqrt(measurement.unit_value());

    auto relative_uncertainty = measurement.relative_uncertainty().value() / 2.0;
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    return PKR_UNITS_NAMESPACE::measurement_t<decltype(result_value)>{result_value, decltype(result_value){result_uncertainty_value}};
}

// Cube function with uncertainty propagation (f(x) = x^3)
// For f(x) = x^3, the relative uncertainty df/f = 3 * dx/x
template <typename UnitT>
constexpr auto cube_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto x = measurement.unit_value();
    auto result_value = x * x * x;

    auto relative_uncertainty = 3.0 * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using ResultUnitT = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
}

// Power function with compile-time integer exponent and fully correlated uncertainty propagation
// For f(x) = x^N (integer N, compile-time), the relative uncertainty df/f = |N| * dx/x
// This is fully correlated (not RSS) unlike multiplication of independent values
// Usage: pow_rss<2>(measurement) for squaring, pow_rss<3>(measurement) for cubing, etc.
template <int N, typename UnitT>
constexpr auto pow_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    // Use unit pow function which correctly handles dimensions
    auto result_value = pow<N>(measurement.unit_value());

    // For fully correlated uncertainty: relative_uncertainty(x^N) = |N| * relative_uncertainty(x)
    auto relative_uncertainty = static_cast<double>(std::abs(N)) * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using ResultUnitT = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
}

// Note: exp/log functions are intentionally not provided for measurements
// to avoid incorrect dimensional or uncertainty handling. Use `pow_rss` for
// integer-power needs or convert to unit types and apply unit math functions explicitly.

// Sine function with uncertainty propagation
// For f(x) = sin(x), the uncertainty df = |cos(x)| * dx
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto sin_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::sin(measurement.value())};

    auto cos_x = std::cos(measurement.value());
    auto result_uncertainty_value = std::abs(cos_x) * measurement.uncertainty();

    return PKR_UNITS_NAMESPACE::measurement_t<PKR_UNITS_NAMESPACE::scalar_t>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// Cosine function with uncertainty propagation
// For f(x) = cos(x), the uncertainty df = |sin(x)| * dx
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto cos_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::cos(measurement.value())};

    auto sin_x = std::sin(measurement.value());
    auto result_uncertainty_value = std::abs(sin_x) * measurement.uncertainty();

    return PKR_UNITS_NAMESPACE::measurement_t<PKR_UNITS_NAMESPACE::scalar_t>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// Tangent function with uncertainty propagation
// For f(x) = tan(x), the relative uncertainty df/f = (1/cos^2(x)) * dx/x
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto tan_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::tan(measurement.value())};

    auto cos_x = std::cos(measurement.value());
    auto sec_squared = 1.0 / (cos_x * cos_x);
    auto result_uncertainty_value = sec_squared * measurement.uncertainty();

    return PKR_UNITS_NAMESPACE::measurement_t<PKR_UNITS_NAMESPACE::scalar_t>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// ============================================================================
// Utility Functions
// ============================================================================

template <typename UnitT>
constexpr auto combined_uncertainty_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    return measurement.uncertainty();
}

template <typename UnitT>
constexpr double relative_uncertainty_percent_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    return measurement.relative_uncertainty().value() * 100.0;
}

template <typename UnitT>
constexpr auto in_base_si_units_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto normalized_value = measurement.value().in_base_si_units();
    auto normalized_uncertainty = measurement.uncertainty().in_base_si_units();

    return PKR_UNITS_NAMESPACE::measurement_t<UnitT>{normalized_value, normalized_uncertainty};
}

} // namespace PKR_UNITS_NAMESPACE
