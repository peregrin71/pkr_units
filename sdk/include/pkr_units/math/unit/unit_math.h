#pragma once

#include <cmath>
#include <functional>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/dimensionless/scalar.h>


namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Math functions for unit_t types
// ============================================================================
// Provides mathematical operations that work with unit_t types, including
// automatic ratio conversion, dimensional analysis, and numerical stability

// ============================================================================
// Basic Arithmetic Functions
// ============================================================================

// Addition with automatic ratio conversion
template <typename T, typename Ratio1, dimension_t Dim, typename Ratio2>
constexpr auto add(const details::unit_t<T, Ratio1, Dim>& a, const details::unit_t<T, Ratio2, Dim>& b)
{
    return a + b;
}

// Subtraction with automatic ratio conversion
template <typename T, typename Ratio1, dimension_t Dim, typename Ratio2>
constexpr auto subtract(const details::unit_t<T, Ratio1, Dim>& a, const details::unit_t<T, Ratio2, Dim>& b)
{
    return a - b;
}

// Multiplication (combines dimensions)
template <typename T, typename Ratio1, dimension_t Dim1, typename Ratio2, dimension_t Dim2>
constexpr auto multiply(const details::unit_t<T, Ratio1, Dim1>& a, const details::unit_t<T, Ratio2, Dim2>& b)
{
    return a * b;
}

// Division (combines dimensions)
template <typename T, typename Ratio1, dimension_t Dim1, typename Ratio2, dimension_t Dim2>
constexpr auto divide(const details::unit_t<T, Ratio1, Dim1>& a, const details::unit_t<T, Ratio2, Dim2>& b)
{
    return a / b;
}

// ============================================================================
// Scalar Operations
// ============================================================================

// Multiply unit_t by scalar
template <typename T, typename Ratio, dimension_t Dim>
constexpr auto multiply_scalar(const details::unit_t<T, Ratio, Dim>& a, T scalar)
{
    return a * scalar;
}

// Divide unit_t by scalar
template <typename T, typename Ratio, dimension_t Dim>
constexpr auto divide_scalar(const details::unit_t<T, Ratio, Dim>& a, T scalar)
{
    return a / scalar;
}

// ============================================================================
// Numerically Stable Operations (work with named units)
// ============================================================================

// Stable addition - returns unit_t with canonical ratio for numerical stability
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>
constexpr auto stable_add(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<T1>::value_type;
    constexpr auto dim = details::is_pkr_unit<T1>::value_dimension;
    using ratio1 = typename details::is_pkr_unit<T1>::ratio_type;
    using ratio2 = typename details::is_pkr_unit<T2>::ratio_type;

    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        return T1{lhs.value() + rhs.value()};
    }
    else
    {
        // Convert rhs to lhs ratio and add
        value_type converted_rhs = details::convert_ratio_to<value_type, ratio2, ratio1>(rhs.value());
        return T1{lhs.value() + converted_rhs};
    }
}

// Stable subtraction - returns unit_t with canonical ratio
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>
constexpr auto stable_subtract(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<T1>::value_type;
    constexpr auto dim = details::is_pkr_unit<T1>::value_dimension;
    using ratio1 = typename details::is_pkr_unit<T1>::ratio_type;
    using ratio2 = typename details::is_pkr_unit<T2>::ratio_type;

    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        return T1{lhs.value() - rhs.value()};
    }
    else
    {
        // Convert rhs to lhs ratio and subtract
        value_type converted_rhs = details::convert_ratio_to<value_type, ratio2, ratio1>(rhs.value());
        return T1{lhs.value() - converted_rhs};
    }
}

// Stable multiplication - returns unit_t with combined ratio
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
constexpr auto stable_multiply(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<T1>::value_type;
    using ratio1 = typename details::is_pkr_unit<T1>::ratio_type;
    using ratio2 = typename details::is_pkr_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<T2>::value_dimension;

    using combined_ratio = std::ratio_multiply<ratio1, ratio2>;

    constexpr dimension_t combined_dim{
        .length = dim1.length + dim2.length,
        .mass = dim1.mass + dim2.mass,
        .time = dim1.time + dim2.time,
        .current = dim1.current + dim2.current,
        .temperature = dim1.temperature + dim2.temperature,
        .amount = dim1.amount + dim2.amount,
        .intensity = dim1.intensity + dim2.intensity,
        .angle = dim1.angle + dim2.angle};

    return details::unit_t<value_type, combined_ratio, combined_dim>{lhs.value() * rhs.value()};
}

// Stable division - returns unit_t with combined ratio
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
constexpr auto stable_divide(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<T1>::value_type;
    using ratio1 = typename details::is_pkr_unit<T1>::ratio_type;
    using ratio2 = typename details::is_pkr_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<T2>::value_dimension;

    using combined_ratio = std::ratio_divide<ratio1, ratio2>;

    constexpr dimension_t combined_dim{
        .length = dim1.length - dim2.length,
        .mass = dim1.mass - dim2.mass,
        .time = dim1.time - dim2.time,
        .current = dim1.current - dim2.current,
        .temperature = dim1.temperature - dim2.temperature,
        .amount = dim1.amount - dim2.amount,
        .intensity = dim1.intensity - dim2.intensity,
        .angle = dim1.angle - dim2.angle};

    return details::unit_t<value_type, combined_ratio, combined_dim>{lhs.value() / rhs.value()};
}

// ============================================================================
// Mathematical Functions
// ============================================================================

// Square root with dimensional analysis
// sqrt(unit_t) produces a unit_t with half the dimensional exponents
template <typename T, typename Ratio, dimension_t Dim>
    requires pkr_unit_can_take_square_root_c<Dim>
auto sqrt(const details::unit_t<T, Ratio, Dim>& a)
{
    // For dimensional analysis, we need to handle the exponents
    // This is a simplified implementation - full version would need
    // compile-time dimensional exponent manipulation

    using result_ratio = Ratio; // Simplified - should compute sqrt of ratio
    constexpr dimension_t result_dim = {
        Dim.length / 2, // Integer division for now
        Dim.mass / 2,   // Full implementation needs fractional handling
        Dim.time / 2,
        Dim.current / 2,
        Dim.temperature / 2,
        Dim.amount / 2,
        Dim.intensity / 2,
        Dim.angle / 2};

    return details::unit_t<T, result_ratio, result_dim>{std::sqrt(a.value())};
}

// Square function with dimensional analysis
// square(unit_t) produces a unit_t with double the dimensional exponents
template <typename T, typename Ratio, dimension_t Dim>
constexpr auto square(const details::unit_t<T, Ratio, Dim>& a)
{
    // For dimensional analysis, we need to handle the exponents
    // This is a simplified implementation - full version would need
    // compile-time dimensional exponent manipulation

    using result_ratio = Ratio; // Simplified - should compute square of ratio
    constexpr dimension_t result_dim = {
        Dim.length * 2, Dim.mass * 2, Dim.time * 2, Dim.current * 2, Dim.temperature * 2, Dim.amount * 2, Dim.intensity * 2, Dim.angle * 2};

    return details::unit_t<T, result_ratio, result_dim>{a.value() * a.value()};
}

// Cube function with dimensional analysis
// cube(unit_t) produces a unit_t with triple the dimensional exponents
template <typename T, typename Ratio, dimension_t Dim>
constexpr auto cube(const details::unit_t<T, Ratio, Dim>& a)
{
    using result_ratio = Ratio;
    constexpr dimension_t result_dim = {
        Dim.length * 3, Dim.mass * 3, Dim.time * 3, Dim.current * 3, Dim.temperature * 3, Dim.amount * 3, Dim.intensity * 3, Dim.angle * 3};

    return details::unit_t<T, result_ratio, result_dim>{a.value() * a.value() * a.value()};
}

// Exponential function (result is dimensionless)
template <typename T, typename Ratio, dimension_t Dim>
auto exp(const details::unit_t<T, Ratio, Dim>& a)
{
    static_assert(
        Dim.length == 0 && Dim.mass == 0 && Dim.time == 0 && Dim.current == 0 && Dim.temperature == 0 && Dim.amount == 0 && Dim.intensity == 0 &&
            Dim.angle == 0,
        "exp() requires dimensionless input");
    return details::unit_t<T, std::ratio<1>, scalar_dimension>{std::exp(a.value())};
}

// Natural logarithm (result is dimensionless)
template <typename T, typename Ratio, dimension_t Dim>
auto log(const details::unit_t<T, Ratio, Dim>& a)
{
    static_assert(
        Dim.length == 0 && Dim.mass == 0 && Dim.time == 0 && Dim.current == 0 && Dim.temperature == 0 && Dim.amount == 0 && Dim.intensity == 0 &&
            Dim.angle == 0,
        "log() requires dimensionless input");
    return details::unit_t<T, std::ratio<1>, scalar_dimension>{std::log(a.value())};
}

// Power function (exponent must be dimensionless)
template <typename T, typename Ratio, dimension_t Dim, typename ExpT, typename ExpRatio>
auto pow(const details::unit_t<T, Ratio, Dim>& base, const details::unit_t<ExpT, ExpRatio, scalar_dimension>& exponent)
{
    // This would need full dimensional exponent manipulation
    // Simplified implementation for now
    return details::unit_t<T, Ratio, Dim>{std::pow(base.value(), exponent.value())};
}

// Compile-time power function with integer exponent (for measurement math)
// Usage: pow<2>(meter) for squaring, pow<-1>(meter) for reciprocal, etc.
// Returns the most specific derived unit type for the powered dimensions, or unit_t if no specialization exists

// Base template - default for any N (requires specialization for actual ratios)
template <int N, typename T, typename Ratio, dimension_t Dim>
auto pow(const details::unit_t<T, Ratio, Dim>& base)
{
    // For general case, compute powered dimensions
    constexpr dimension_t powered_dim{
        .length = static_cast<signed char>(Dim.length * N),
        .mass = static_cast<signed char>(Dim.mass * N),
        .time = static_cast<signed char>(Dim.time * N),
        .current = static_cast<signed char>(Dim.current * N),
        .temperature = static_cast<signed char>(Dim.temperature * N),
        .amount = static_cast<signed char>(Dim.amount * N),
        .intensity = static_cast<signed char>(Dim.intensity * N),
        .angle = static_cast<signed char>(Dim.angle * N)};

    // For ratio<1,1>, the powered ratio is also ratio<1,1>
    if constexpr (std::is_same_v<Ratio, std::ratio<1, 1>>)
    {
        using result_type = typename details::derived_unit_type_t<T, std::ratio<1, 1>, powered_dim>::type;
        
        if constexpr (N == 0)
            return result_type{1.0};
        else if constexpr (N == 1)
            return result_type{base.value()};
        else if constexpr (N > 0)
        {
            T result = base.value();
            for (int i = 1; i < N; ++i)
                result *= base.value();
            return result_type{result};
        }
        else // N < 0
        {
            T result = 1.0 / base.value();
            for (int i = 1; i < -N; ++i)
                result /= base.value();
            return result_type{result};
        }
    }
    else
    {
        // For other ratios, just return generic unit_t (specializations would be needed for derived types)
        using result_type = details::unit_t<T, Ratio, powered_dim>;
        
        if constexpr (N == 0)
            return result_type{1.0};
        else if constexpr (N == 1)
            return result_type{base.value()};
        else if constexpr (N > 0)
        {
            T result = base.value();
            for (int i = 1; i < N; ++i)
                result *= base.value();
            return result_type{result};
        }
        else // N < 0
        {
            T result = 1.0 / base.value();
            for (int i = 1; i < -N; ++i)
                result /= base.value();
            return result_type{result};
        }
    }
}

// ============================================================================
// Unit-aware transcendental functions (work with named units)
// ============================================================================

// exp() - only works on dimensionless units (all dimensions zero)
template <is_pkr_unit_c T>
auto exp(const T& x) noexcept
{
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;
    static_assert(
        dim.length == 0 && dim.mass == 0 && dim.time == 0 && dim.current == 0 && dim.temperature == 0 && dim.amount == 0 && dim.intensity == 0 &&
            dim.angle == 0,
        "exp() only works on dimensionless units");
    return T{std::exp(x.value())};
}

// log() - returns dimensionless unit (log of dimensionless input)
template <is_pkr_unit_c T>
auto log(const T& x)
{
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;
    static_assert(
        dim.length == 0 && dim.mass == 0 && dim.time == 0 && dim.current == 0 && dim.temperature == 0 && dim.amount == 0 && dim.intensity == 0 &&
            dim.angle == 0,
        "log() only works on dimensionless units");
    if (x.value() <= 0)
    {
        throw std::invalid_argument("log of non-positive value");
    }
    // Return a dimensionless unit (all dimensions zero)
    return details::unit_t<typename details::is_pkr_unit<T>::value_type, std::ratio<1, 1>, dimension_t{}>{std::log(x.value())};
}

// sqrt() - returns unit with square root dimensions
template <is_pkr_unit_c T>
auto sqrt(const T& x)
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using ratio = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;

    // Square root of ratio - ratio does not change, only value and dimensions
    using sqrt_ratio = ratio;

    // Square root of dimensions (divide by 2)
    constexpr dimension_t sqrt_dim{
        .length = dim.length / 2,
        .mass = dim.mass / 2,
        .time = dim.time / 2,
        .current = dim.current / 2,
        .temperature = dim.temperature / 2,
        .amount = dim.amount / 2,
        .intensity = dim.intensity / 2,
        .angle = dim.angle / 2};

    if (x.value() < 0)
    {
        throw std::invalid_argument("sqrt of negative value");
    }

    return details::unit_t<value_type, sqrt_ratio, sqrt_dim>{std::sqrt(x.value())};
}

// Normalize a unit_t to its canonical SI form (ratio 1/1)
template <is_pkr_unit_c T>
constexpr auto normalize(const T& unit) noexcept
{
    return unit.in_base_si_units();
}

// ============================================================================
// Trigonometric Functions (return dimensionless for angle inputs)
// ============================================================================

// Sine function - only works on angle units
template <is_angle_unit_c T>
auto sin(const T& angle) noexcept
{
    return scalar_t{std::sin(angle.value())};
}

// Cosine function - only works on angle units
template <is_angle_unit_c T>
auto cos(const T& angle) noexcept
{
    return scalar_t{std::cos(angle.value())};
}

// Tangent function - only works on angle units
template <is_angle_unit_c T>
auto tan(const T& angle) noexcept
{
    return scalar_t{std::tan(angle.value())};
}

} // namespace PKR_UNITS_NAMESPACE
