#pragma once

#define PKR_UNITS_DETAIL_IS_LINEAR(x) PKR_UNITS_DETAIL_IS_LINEAR_IMPL(x)
#define PKR_UNITS_DETAIL_IS_LINEAR_IMPL(x) PKR_UNITS_DETAIL_IS_LINEAR_##x
#define PKR_UNITS_DETAIL_IS_LINEAR_linear 1
#define PKR_UNITS_DETAIL_IS_LINEAR_rss 0

#ifndef PKR_UNITS_MEASUREMENT_UNCERTAINTY_STRATEGY
#define PKR_UNITS_MEASUREMENT_UNCERTAINTY_STRATEGY linear
#elif PKR_UNITS_DETAIL_IS_LINEAR(PKR_UNITS_MEASUREMENT_UNCERTAINTY_STRATEGY) != 1
#error "Multiple measurement_math strategy headers included in the same translation unit."
#endif

#undef PKR_UNITS_DETAIL_IS_LINEAR
#undef PKR_UNITS_DETAIL_IS_LINEAR_IMPL
#undef PKR_UNITS_DETAIL_IS_LINEAR_linear
#undef PKR_UNITS_DETAIL_IS_LINEAR_rss

#include <cmath>
#include <type_traits>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/math/unit/unit_math.h>
#include <pkr_units/units/dimensionless/scalar.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Basic Arithmetic Functions (wrappers for measurement_t operations)
// ============================================================================

// Addition with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto add_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = a.unit_value() + b.unit_value();
    auto result_uncertainty = a.uncertainty() + b.uncertainty();
    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty}};
}

// Subtraction with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto subtract_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = a.unit_value() - b.unit_value();
    auto result_uncertainty = a.uncertainty() + b.uncertainty();
    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty}};
}

// Multiplication with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto multiply_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = (a.unit_value() * b.unit_value()).in_base_si_units();
    using result_type = decltype(result_value);

    auto rel_uncertainty = a.relative_uncertainty().value() + b.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * rel_uncertainty;

    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Division with uncertainty propagation
template <typename UnitT1, typename UnitT2>
constexpr auto divide_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b)
{
    auto result_value = (a.unit_value() / b.unit_value()).in_base_si_units();
    using result_type = decltype(result_value);

    auto rel_uncertainty = a.relative_uncertainty().value() + b.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * rel_uncertainty;

    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Overload for multiplying measurement by scalar (zero uncertainty)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto multiply_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& a, T b)
{
    auto result_value = a.unit_value() * b;
    auto result_uncertainty = UnitT{a.uncertainty() * std::abs(static_cast<double>(b))};
    return PKR_UNITS_NAMESPACE::measurement_t<UnitT>{result_value, result_uncertainty};
}

// Overload for multiplying scalar by measurement (zero uncertainty)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto multiply_lin(T a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& b)
{
    auto result_value = a * b.unit_value();
    auto result_uncertainty = UnitT{b.uncertainty() * std::abs(static_cast<double>(a))};
    return PKR_UNITS_NAMESPACE::measurement_t<UnitT>{result_value, result_uncertainty};
}

// Overload for dividing measurement by scalar (zero uncertainty)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto divide_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& a, T b)
{
    auto result_value = a.unit_value() / b;
    auto result_uncertainty = UnitT{a.uncertainty() / std::abs(static_cast<double>(b))};
    return PKR_UNITS_NAMESPACE::measurement_t<UnitT>{result_value, result_uncertainty};
}

// Overload for dividing scalar by measurement (zero uncertainty for scalar)
template <typename UnitT, typename T>
    requires std::is_arithmetic_v<T> || PKR_UNITS_NAMESPACE::is_base_pkr_unit_c<T>
auto divide_lin(T a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& b)
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
// For f(x) = √x, the absolute uncertainty δf = (1/2) * (δx / √x)
template <typename UnitT>
    requires pkr_unit_can_take_square_root_c<details::is_pkr_unit<UnitT>::value_dimension>
auto sqrt_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    // Use sqrt for the value
    auto result_value = sqrt(measurement.unit_value());

    // Calculate uncertainty propagation: δ(√x) = (1/2) * (δx / √x)
    auto result_uncertainty_value = measurement.uncertainty() / (2.0 * std::sqrt(measurement.value()));

    return PKR_UNITS_NAMESPACE::measurement_t<decltype(result_value)>{result_value, decltype(result_value){result_uncertainty_value}};
}

// Cube function with uncertainty propagation (f(x) = x^3)
// For f(x) = x^3, the relative uncertainty df/f = 3 * dx/x
template <typename UnitT>
auto cube_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
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
// This is fully correlated (not additive linear) unlike multiplication of independent values
// Usage: pow_lin<2>(measurement) for squaring, pow_lin<3>(measurement) for cubing, etc.
template <int N, typename UnitT>
constexpr auto pow_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    // Use unit pow function which correctly handles dimensions
    auto result_value = pow<N>(measurement.unit_value());

    // For fully correlated uncertainty: relative_uncertainty(x^N) = |N| * relative_uncertainty(x)
    auto relative_uncertainty = static_cast<double>(std::abs(N)) * measurement.relative_uncertainty().value();
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using ResultUnitT = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<ResultUnitT>{result_value, ResultUnitT{result_uncertainty_value}};
}

// Sine function with uncertainty propagation
// For f(x) = sin(x), the uncertainty δf = |cos(x)| * δx
// Only works on angle units (dimensionless in angle sense)
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto sin_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    // Use std::sin for the value (angle input in radians)
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::sin(measurement.value())};

    // Uncertainty propagation: δ(sin(x)) = |cos(x)| * δx
    auto cos_x = std::cos(measurement.value());
    auto result_uncertainty_value = std::abs(cos_x) * measurement.uncertainty();

    return PKR_UNITS_NAMESPACE::measurement_t<PKR_UNITS_NAMESPACE::scalar_t>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// Cosine function with uncertainty propagation
// For f(x) = cos(x), the uncertainty δf = |sin(x)| * δx
// Only works on angle units (dimensionless in angle sense)
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto cos_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    // Use std::cos for the value (angle input in radians)
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::cos(measurement.value())};

    // Uncertainty propagation: δ(cos(x)) = |sin(x)| * δx
    auto sin_x = std::sin(measurement.value());
    auto result_uncertainty_value = std::abs(sin_x) * measurement.uncertainty();

    return PKR_UNITS_NAMESPACE::measurement_t<PKR_UNITS_NAMESPACE::scalar_t>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// Tangent function with uncertainty propagation
// For f(x) = tan(x), the relative uncertainty δf/f = (1/cos²(x)) * δx/x
// Only works on angle units (dimensionless in angle sense)
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
auto tan_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    // Use std::tan for the value (angle input in radians)
    auto result_value = PKR_UNITS_NAMESPACE::scalar_t{std::tan(measurement.value())};

    // Uncertainty propagation: δ(tan(x)) = sec²(x) * δx = (1/cos²(x)) * δx
    auto cos_x = std::cos(measurement.value());
    auto sec_squared = 1.0 / (cos_x * cos_x);
    auto result_uncertainty_value = sec_squared * measurement.uncertainty();

    return PKR_UNITS_NAMESPACE::measurement_t<PKR_UNITS_NAMESPACE::scalar_t>{result_value, PKR_UNITS_NAMESPACE::scalar_t{result_uncertainty_value}};
}

// ============================================================================
// Utility Functions
// ============================================================================

// Get combined uncertainty estimate in the same units as the measurement
// This is a convenience method that returns the uncertainty value
template <typename UnitT>
constexpr auto combined_uncertainty_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    return measurement.uncertainty();
}

// Get relative uncertainty as a percentage
template <typename UnitT>
constexpr double relative_uncertainty_percent_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    return measurement.relative_uncertainty().value() * 100.0;
}

// Normalize a measurement to its canonical SI form
template <typename UnitT>
constexpr auto normalize_lin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement)
{
    auto normalized_value = measurement.value().in_base_si_units();
    auto normalized_uncertainty = measurement.uncertainty().in_base_si_units();

    using result_type = decltype(normalized_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{normalized_value, normalized_uncertainty};
}

} // namespace PKR_UNITS_NAMESPACE
