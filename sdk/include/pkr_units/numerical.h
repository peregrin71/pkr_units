#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/unit_impl.h>
#include <cmath>
#include <functional>

namespace PKR_UNITS_NAMESPACE
{

namespace numerical
{

// ============================================================================
// Numerically stable unit operations (return unit_t types, not named units)
// ============================================================================

// Stable addition - returns unit_t with canonical ratio for numerical stability
template <details::pkr_unit_concept T1, details::pkr_unit_concept T2>
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
        // Return in canonical ratio to preserve numerical stability
        value_type canonical_sum = details::add_canonical<value_type, ratio1, ratio2>(lhs.value(), rhs.value());
        return details::unit_t<value_type, std::ratio<1, 1>, dim>{canonical_sum};
    }
}

// Stable subtraction - returns unit_t with canonical ratio
template <details::pkr_unit_concept T1, details::pkr_unit_concept T2>
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
        // Return in canonical ratio to preserve numerical stability
        value_type canonical_diff = details::subtract_canonical<value_type, ratio1, ratio2>(lhs.value(), rhs.value());
        return details::unit_t<value_type, std::ratio<1, 1>, dim>{canonical_diff};
    }
}

// Stable multiplication - returns unit_t with combined ratio
template <details::pkr_unit_concept T1, details::pkr_unit_concept T2>
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
template <details::pkr_unit_concept T1, details::pkr_unit_concept T2>
constexpr auto stable_divide(const T1& lhs, const T2& rhs)
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

    if ((rhs.value() < static_cast<value_type>(0) ? -rhs.value() : rhs.value()) == static_cast<value_type>(0))
    {
        throw std::invalid_argument("Division by zero in stable_divide");
    }

    return details::unit_t<value_type, combined_ratio, combined_dim>{lhs.value() / rhs.value()};
}

// ============================================================================
// Unit-aware transcendental functions
// ============================================================================

// exp() - only works on dimensionless units (all dimensions zero)
template <details::pkr_unit_concept T>
constexpr auto exp(const T& x) noexcept
{
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;
    static_assert(
        dim.length == 0 && dim.mass == 0 && dim.time == 0 && dim.current == 0 && dim.temperature == 0 && dim.amount == 0 && dim.intensity == 0 &&
            dim.angle == 0,
        "exp() only works on dimensionless units");
    return T{std::exp(x.value())};
}

// log() - returns dimensionless unit (log of dimensionless input)
template <details::pkr_unit_concept T>
constexpr auto log(const T& x)
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
template <details::pkr_unit_concept T>
constexpr auto sqrt(const T& x)
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using ratio = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;

    // Square root of ratio
    using sqrt_ratio = std::ratio<ratio::num, ratio::den * 2>;

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

// ============================================================================
// Numerical methods
// ============================================================================

// Newton-Raphson method for finding roots
template <typename UnitT, typename Function, typename Derivative>
UnitT newton_raphson(UnitT initial_guess, Function f, Derivative df, double tolerance = 1e-10, int max_iterations = 100)
{
    UnitT x = initial_guess;
    for (int i = 0; i < max_iterations; ++i)
    {
        auto fx = f(x);
        auto dfx = df(x);
        auto delta = stable_divide(fx, dfx);
        x = stable_subtract(x, delta);

        if (std::abs(delta.value()) < tolerance)
        {
            break;
        }
    }
    return x;
}

// Runge-Kutta 4th order for ODEs dy/dx = f(x,y)
template <typename TimeUnit, typename StateUnit, typename RHS>
StateUnit runge_kutta_step(RHS f, TimeUnit x, StateUnit y, TimeUnit h)
{
    auto k1 = f(x, y);
    auto half_h = stable_divide(h, 2.0);
    auto k2 = f(stable_add(x, half_h), stable_add(y, stable_multiply(half_h, k1)));
    auto k3 = f(stable_add(x, half_h), stable_add(y, stable_multiply(half_h, k2)));
    auto k4 = f(stable_add(x, h), stable_add(y, stable_multiply(h, k3)));

    // y + h/6*(k1 + 2*k2 + 2*k3 + k4)
    auto two = 2.0;
    auto six = 6.0;
    auto sum = stable_add(stable_add(k1, stable_multiply(two, k2)), stable_add(stable_multiply(two, k3), k4));
    return stable_add(y, stable_multiply(stable_divide(h, six), sum));
}

} // namespace numerical

} // namespace PKR_UNITS_NAMESPACE
