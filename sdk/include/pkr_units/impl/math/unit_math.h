#pragma once

#include <cmath>
#include "../namespace_config.h"
#include "../decls/unit_t_decl.h"

PKR_UNITS_BEGIN_NAMESPACE

// ============================================================================
// Math functions for unit_t types
// ============================================================================
// Provides mathematical operations that work with unit_t types, including
// automatic ratio conversion and dimensional analysis.

namespace math {

// ============================================================================
// Basic Arithmetic Functions
// ============================================================================

// Addition with automatic ratio conversion
template<typename T, typename Ratio1, dimension_t Dim, typename Ratio2>
constexpr auto add(const unit_t<T, Ratio1, Dim>& a, const unit_t<T, Ratio2, Dim>& b) {
    return a + b;
}

// Subtraction with automatic ratio conversion
template<typename T, typename Ratio1, dimension_t Dim, typename Ratio2>
constexpr auto subtract(const unit_t<T, Ratio1, Dim>& a, const unit_t<T, Ratio2, Dim>& b) {
    return a - b;
}

// Multiplication (combines dimensions)
template<typename T, typename Ratio1, dimension_t Dim1, typename Ratio2, dimension_t Dim2>
constexpr auto multiply(const unit_t<T, Ratio1, Dim1>& a, const unit_t<T, Ratio2, Dim2>& b) {
    return a * b;
}

// Division (combines dimensions)
template<typename T, typename Ratio1, dimension_t Dim1, typename Ratio2, dimension_t Dim2>
constexpr auto divide(const unit_t<T, Ratio1, Dim1>& a, const unit_t<T, Ratio2, Dim2>& b) {
    return a / b;
}

// ============================================================================
// Scalar Operations
// ============================================================================

// Multiply unit_t by scalar
template<typename T, typename Ratio, dimension_t Dim>
constexpr auto multiply_scalar(const unit_t<T, Ratio, Dim>& a, T scalar) {
    return a * scalar;
}

// Divide unit_t by scalar
template<typename T, typename Ratio, dimension_t Dim>
constexpr auto divide_scalar(const unit_t<T, Ratio, Dim>& a, T scalar) {
    return a / scalar;
}

// ============================================================================
// Mathematical Functions
// ============================================================================

// Square root with dimensional analysis
// sqrt(unit_t) produces a unit_t with half the dimensional exponents
template<typename T, typename Ratio, dimension_t Dim>
constexpr auto sqrt(const unit_t<T, Ratio, Dim>& a) {
    // For dimensional analysis, we need to handle the exponents
    // This is a simplified implementation - full version would need
    // compile-time dimensional exponent manipulation

    using result_ratio = Ratio;  // Simplified - should compute sqrt of ratio
    constexpr dimension_t result_dim = {
        Dim.length / 2,      // Integer division for now
        Dim.mass / 2,        // Full implementation needs fractional handling
        Dim.time / 2,
        Dim.current / 2,
        Dim.temperature / 2,
        Dim.amount / 2,
        Dim.intensity / 2,
        Dim.angle / 2
    };

    return unit_t<T, result_ratio, result_dim>{std::sqrt(a.value())};
}

// Exponential function (result is dimensionless)
template<typename T, typename Ratio, dimension_t Dim>
constexpr auto exp(const unit_t<T, Ratio, Dim>& a) {
    static_assert(Dim.length == 0 && Dim.mass == 0 && Dim.time == 0 &&
                  Dim.current == 0 && Dim.temperature == 0 && Dim.amount == 0 &&
                  Dim.intensity == 0 && Dim.angle == 0,
                  "exp() requires dimensionless input");
    return unit_t<T, std::ratio<1>, scalar_dimension>{std::exp(a.value())};
}

// Natural logarithm (result is dimensionless)
template<typename T, typename Ratio, dimension_t Dim>
constexpr auto log(const unit_t<T, Ratio, Dim>& a) {
    static_assert(Dim.length == 0 && Dim.mass == 0 && Dim.time == 0 &&
                  Dim.current == 0 && Dim.temperature == 0 && Dim.amount == 0 &&
                  Dim.intensity == 0 && Dim.angle == 0,
                  "log() requires dimensionless input");
    return unit_t<T, std::ratio<1>, scalar_dimension>{std::log(a.value())};
}

// Power function (exponent must be dimensionless)
template<typename T, typename Ratio, dimension_t Dim, typename ExpT, typename ExpRatio>
constexpr auto pow(const unit_t<T, Ratio, Dim>& base, const unit_t<ExpT, ExpRatio, scalar_dimension>& exponent) {
    // This would need full dimensional exponent manipulation
    // Simplified implementation for now
    return unit_t<T, Ratio, Dim>{std::pow(base.value(), exponent.value())};
}

} // namespace math

PKR_UNITS_END_NAMESPACE
