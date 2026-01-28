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
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/units/unit_math.h>

namespace PKR_UNITS_NAMESPACE
{

namespace math
{

// ============================================================================
// Basic Arithmetic Functions (RSS uncertainty propagation for multiply/divide)
// ============================================================================

// Addition with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto add_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    return a + b;
}

// Subtraction with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto subtract_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    return a - b;
}

// Square function with uncertainty propagation
// For f(x) = x^2, the relative uncertainty df/f = 2 *
template <typename UnitT>
constexpr auto square_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = math::square(measurement.unit_value());

    auto relative_uncertainty = 2.0 * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Multiplication with uncertainty propagation (RSS for relative uncertainties)
// These values MUST not be correlated. Do not use multiply_rss(a, a) for squaring;
// use square_rss(a) instead, as squaring requires correlated uncertainty propagation.
template <typename UnitT1, typename UnitT2>
auto multiply_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = (a.unit_value() * b.unit_value()).in_base_si_units();
    using result_type = decltype(result_value);

    auto rel_uncertainty1 = a.relative_uncertainty().value();
    auto rel_uncertainty2 = b.relative_uncertainty().value();
    auto total_rel_uncertainty = std::sqrt(rel_uncertainty1 * rel_uncertainty1 + rel_uncertainty2 * rel_uncertainty2);
    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Overload for multiplying measurement by scalar (zero uncertainty)
template <typename UnitT>
auto multiply_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& a, const PKR_UNITS_NAMESPACE::is_unit_value_type_c auto& b)
{
    using scalar_unit_t = PKR_UNITS_NAMESPACE::details::unit_t<std::decay_t<decltype(b)>, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>;
    auto scalar_b = PKR_UNITS_NAMESPACE::measurement_t<scalar_unit_t>{b, 0.0};
    return multiply_rss(a, scalar_b);
}

// Overload for multiplying scalar by measurement (zero uncertainty)
template <typename UnitT>
auto multiply_rss(const PKR_UNITS_NAMESPACE::is_unit_value_type_c auto& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& b)
{
    using scalar_unit_t = PKR_UNITS_NAMESPACE::details::unit_t<std::decay_t<decltype(a)>, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>;
    auto scalar_a = PKR_UNITS_NAMESPACE::measurement_t<scalar_unit_t>{a, 0.0};
    return multiply_rss(scalar_a, b);
}

// Division with uncertainty propagation (RSS for relative uncertainties)
template <typename UnitT1, typename UnitT2>
constexpr auto divide_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = (a.unit_value() / b.unit_value()).in_base_si_units();
    using result_type = decltype(result_value);

    auto rel_uncertainty1 = a.relative_uncertainty().value();
    auto rel_uncertainty2 = b.relative_uncertainty().value();
    auto total_rel_uncertainty = std::sqrt(rel_uncertainty1 * rel_uncertainty1 + rel_uncertainty2 * rel_uncertainty2);
    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// ============================================================================
// Mathematical Functions with Uncertainty Propagation
// ============================================================================

// Square root with uncertainty propagation
// For f(x) = sqrt(x), the relative uncertainty df/f = (1/2) * dx/x
template <typename UnitT>
constexpr auto sqrt_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = math::sqrt(measurement.unit_value());

    auto relative_uncertainty = measurement.relative_uncertainty().value() / 2.0;
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Exponential function with uncertainty propagation
// For f(x) = e^x, the relative uncertainty df/f = dx (since x must be dimensionless)
template <typename UnitT>
constexpr auto exp_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = math::exp(measurement.unit_value());
    auto result_uncertainty_value = result_value.value() * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Natural logarithm with uncertainty propagation
// For f(x) = ln(x), the relative uncertainty df/f = dx/x
template <typename UnitT>
constexpr auto log_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = math::log(measurement.unit_value());
    auto result_uncertainty_value = measurement.relative_uncertainty().value();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Power function with uncertainty propagation
// For f(x) = x^n, the relative uncertainty df/f = |n| * dx/x and dn * ln(x)
template <typename UnitT, typename ExpUnitT>
constexpr auto pow_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& base, const PKR_UNITS_NAMESPACE::measurement_t<ExpUnitT>& exponent)
{
    auto result_value = math::pow(base.unit_value(), exponent.unit_value());

    auto rel_uncertainty_base = base.relative_uncertainty().value();
    auto rel_uncertainty_exp = exponent.relative_uncertainty().value();
    auto exponent_value = exponent.value();

    auto ln_base = std::log(base.value());
    auto term_base = std::abs(exponent_value) * rel_uncertainty_base;
    auto term_exp = rel_uncertainty_exp * ln_base;
    auto total_rel_uncertainty = std::sqrt(term_base * term_base + term_exp * term_exp);

    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Power function with scalar exponent (dimensionless)
template <typename UnitT>
constexpr auto pow(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& base, double exponent)
{
    auto dimensionless_exp = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{exponent};
    auto result_value = math::pow(base.unit_value(), dimensionless_exp);

    auto rel_uncertainty_base = base.relative_uncertainty().value();
    auto total_rel_uncertainty = std::abs(exponent) * rel_uncertainty_base;
    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Sine function with uncertainty propagation
// For f(x) = sin(x), the uncertainty df = |cos(x)| * dx
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>

constexpr auto sin_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{std::sin(measurement.value())};

    auto cos_x = std::cos(measurement.value());
    auto result_uncertainty_value = std::abs(cos_x) * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Cosine function with uncertainty propagation
// For f(x) = cos(x), the uncertainty df = |sin(x)| * dx
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>

constexpr auto cos(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{std::cos(measurement.value())};

    auto sin_x = std::sin(measurement.value());
    auto result_uncertainty_value = std::abs(sin_x) * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Tangent function with uncertainty propagation
// For f(x) = tan(x), the relative uncertainty df/f = (1/cos^2(x)) * dx/x
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>

constexpr auto tan_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto result_value = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{std::tan(measurement.value())};

    auto cos_x = std::cos(measurement.value());
    auto sec_squared = 1.0 / (cos_x * cos_x);
    auto result_uncertainty_value = sec_squared * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
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
constexpr auto normalize_rss(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto normalized_value = math::normalize(measurement.value());
    auto normalized_uncertainty = math::normalize(measurement.uncertainty());

    using result_type = decltype(normalized_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{normalized_value, normalized_uncertainty};
}

} // namespace math

} // namespace PKR_UNITS_NAMESPACE
