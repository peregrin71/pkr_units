#pragma once

#include <cmath>
#include <type_traits>
#include "../impl/namespace_config.h"
#include "../impl/decls/unit_t_decl.h"
#include "../impl/concepts/unit_concepts.h"
#include "../units/unit_math.h"

PKR_UNITS_BEGIN_NAMESPACE
{

namespace math {

// ============================================================================
// Basic Arithmetic Functions (wrappers for measurement_t operations)
// ============================================================================

// Addition with uncertainty propagation
template<typename UnitT1, typename UnitT2>
constexpr auto add(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b) {
    return a + b;
}

// Subtraction with uncertainty propagation
template<typename UnitT1, typename UnitT2>
constexpr auto subtract(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b) {
    return a - b;
}

// Multiplication with uncertainty propagation
template<typename UnitT1, typename UnitT2>
constexpr auto multiply(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b) {
    return a * b;
}

// Division with uncertainty propagation
template<typename UnitT1, typename UnitT2>
constexpr auto divide(const PKR_UNITS_NAMESPACE::measurement_t<UnitT1>& a, const PKR_UNITS_NAMESPACE::measurement_t<UnitT2>& b) {
    return a / b;
}

// ============================================================================
// Mathematical Functions with Uncertainty Propagation
// ============================================================================

// Square root with uncertainty propagation
// For f(x) = √x, the relative uncertainty δf/f = (1/2) * δx/x
template<typename UnitT>
constexpr auto sqrt(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    // Use math::sqrt for the value
    auto result_value = math::sqrt(measurement.unit_value());

    // Calculate uncertainty propagation: δ(√x) = (1/2) * (δx / x) * √x
    auto relative_uncertainty = measurement.relative_uncertainty().value() / 2.0;
    auto result_uncertainty_value = result_value.value() * relative_uncertainty;

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Exponential function with uncertainty propagation
// For f(x) = e^x, the relative uncertainty δf/f = δx (since x must be dimensionless)
template<typename UnitT>
constexpr auto exp(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    // Use math::exp for the value
    auto result_value = math::exp(measurement.unit_value());

    // For exp(x), uncertainty propagation: δ(exp(x)) = exp(x) * δx
    // Since x is dimensionless, δx is absolute uncertainty
    auto result_uncertainty_value = result_value.value() * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Natural logarithm with uncertainty propagation
// For f(x) = ln(x), the relative uncertainty δf/f = δx/x
template<typename UnitT>
constexpr auto log(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    // Use math::log for the value
    auto result_value = math::log(measurement.unit_value());

    // For log(x), uncertainty propagation: δ(ln(x)) = δx/x
    // Result is dimensionless, so uncertainty is absolute
    auto result_uncertainty_value = measurement.relative_uncertainty().value();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Power function with uncertainty propagation
// For f(x) = x^n, the relative uncertainty δf/f = |n| * δx/x
template<typename UnitT, typename ExpUnitT>
constexpr auto pow(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& base, const PKR_UNITS_NAMESPACE::measurement_t<ExpUnitT>& exponent) {
    // Use math::pow for the value
    auto result_value = math::pow(base.unit_value(), exponent.unit_value());

    // Uncertainty propagation for power function: δ(x^n) = |n| * x^(n-1) * δx + x^n * ln(x) * δn
    // Relative uncertainty: δf/f = |n| * δx/x + δn * ln(x)
    auto rel_uncertainty_base = base.relative_uncertainty().value();
    auto rel_uncertainty_exp = exponent.relative_uncertainty().value();
    auto exponent_value = exponent.value();

    auto ln_base = std::log(base.value());
    auto total_rel_uncertainty = std::abs(exponent_value) * rel_uncertainty_base +
                                rel_uncertainty_exp * ln_base;

    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Power function with scalar exponent (dimensionless)
template<typename UnitT>
constexpr auto pow(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& base, double exponent) {
    // Use math::pow for the value (create dimensionless exponent)
    auto dimensionless_exp = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{exponent};
    auto result_value = math::pow(base.unit_value(), dimensionless_exp);

    // Uncertainty propagation: δ(x^n) = |n| * x^(n-1) * δx
    // Relative uncertainty: δf/f = |n| * δx/x
    auto rel_uncertainty_base = base.relative_uncertainty().value();
    auto total_rel_uncertainty = std::abs(exponent) * rel_uncertainty_base;

    auto result_uncertainty_value = result_value.value() * total_rel_uncertainty;

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Sine function with uncertainty propagation
// For f(x) = sin(x), the uncertainty δf = |cos(x)| * δx
// Only works on angle units (dimensionless in angle sense)
template<typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
constexpr auto sin(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    // Use std::sin for the value (angle input in radians)
    auto result_value = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{std::sin(measurement.value())};

    // Uncertainty propagation: δ(sin(x)) = |cos(x)| * δx
    auto cos_x = std::cos(measurement.value());
    auto result_uncertainty_value = std::abs(cos_x) * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Cosine function with uncertainty propagation
// For f(x) = cos(x), the uncertainty δf = |sin(x)| * δx
// Only works on angle units (dimensionless in angle sense)
template<typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
constexpr auto cos(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    // Use std::cos for the value (angle input in radians)
    auto result_value = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{std::cos(measurement.value())};

    // Uncertainty propagation: δ(cos(x)) = |sin(x)| * δx
    auto sin_x = std::sin(measurement.value());
    auto result_uncertainty_value = std::abs(sin_x) * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// Tangent function with uncertainty propagation
// For f(x) = tan(x), the relative uncertainty δf/f = (1/cos²(x)) * δx/x
// Only works on angle units (dimensionless in angle sense)
template<typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_angle_unit_c<UnitT>
constexpr auto tan(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    // Use std::tan for the value (angle input in radians)
    auto result_value = PKR_UNITS_NAMESPACE::details::unit_t<double, std::ratio<1>, PKR_UNITS_NAMESPACE::scalar_dimension>{std::tan(measurement.value())};

    // Uncertainty propagation: δ(tan(x)) = sec²(x) * δx = (1/cos²(x)) * δx
    auto cos_x = std::cos(measurement.value());
    auto sec_squared = 1.0 / (cos_x * cos_x);
    auto result_uncertainty_value = sec_squared * measurement.uncertainty();

    using result_type = decltype(result_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{result_value, result_type{result_uncertainty_value}};
}

// ============================================================================
// Utility Functions
// ============================================================================

// Get combined uncertainty estimate in the same units as the measurement
// This is a convenience method that returns the uncertainty value
template<typename UnitT>
constexpr auto combined_uncertainty(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    return measurement.uncertainty();
}

// Get relative uncertainty as a percentage
template<typename UnitT>
constexpr double relative_uncertainty_percent(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    return measurement.relative_uncertainty().value() * 100.0;
}

// Normalize a measurement to its canonical SI form
template<typename UnitT>
constexpr auto normalize(const PKR_UNITS_NAMESPACE::measurement_t<UnitT>& measurement) {
    auto normalized_value = math::normalize(measurement.value());
    auto normalized_uncertainty = math::normalize(measurement.uncertainty());

    using result_type = decltype(normalized_value);
    return PKR_UNITS_NAMESPACE::measurement_t<result_type>{normalized_value, normalized_uncertainty};
}

} // namespace math

} // namespace PKR_UNITS_NAMESPACE