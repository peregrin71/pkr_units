#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{
// Constexpr power function for compile-time exponentiation
constexpr intmax_t constexpr_pow(intmax_t base, unsigned int exp) noexcept
{
    if (exp == 0)
        return 1;

    intmax_t result = 1;
    for (unsigned int i = 0; i < exp; ++i)
    {
        result *= base;
    }
    return result;
}

// power_of<Unit, Power> - Represents a unit raised to a power
// Usage:
//   power_of<seconds, 2>     → seconds squared (m/s²)
//   power_of<seconds, -1>    → 1/second (frequency)
//   power_of<seconds, -2>    → 1/second squared (jerk denominator)
//
// Examples:
//   si_cast<meters, per<power_of<seconds, 2>>>(value)     // m/s²
//   si_cast<meters, per<power_of<seconds, -1>>>(value)    // m⋅s
//   si_cast<kilograms, per<power_of<meters, 3>>>(value)   // kg/m³
template <typename unit_type, int power_v>
struct power_of
{
    static_assert(details::is_pkr_unit<unit_type>::value, "power_of requires an si_unit type");

    using unit_traits = details::is_pkr_unit<unit_type>;
    using value_type = typename unit_traits::value_type;
    using source_ratio = typename unit_traits::ratio_type;
    static constexpr dimension_t source_dim = unit_traits::value_dimension;

    // Compute powered dimension by multiplying all exponents by power
    static constexpr dimension_t powered_dim{
        .length = static_cast<signed char>(source_dim.length * power_v),
        .mass = static_cast<signed char>(source_dim.mass * power_v),
        .time = static_cast<signed char>(source_dim.time * power_v),
        .current = static_cast<signed char>(source_dim.current * power_v),
        .temperature = static_cast<signed char>(source_dim.temperature * power_v),
        .amount = static_cast<signed char>(source_dim.amount * power_v),
        .intensity = static_cast<signed char>(source_dim.intensity * power_v),
        .angle = static_cast<signed char>(source_dim.angle * power_v)};

    // Compute powered ratio: (num/den)^power = num^power / den^power
    // For negative powers, swap numerator and denominator
    static constexpr intmax_t powered_num = (power_v >= 0) ? constexpr_pow(source_ratio::num, static_cast<unsigned int>(power_v))
                                                           : constexpr_pow(source_ratio::den, static_cast<unsigned int>(-power_v));

    static constexpr intmax_t powered_den = (power_v >= 0) ? constexpr_pow(source_ratio::den, static_cast<unsigned int>(power_v))
                                                           : constexpr_pow(source_ratio::num, static_cast<unsigned int>(-power_v));

    // The resulting ratio (automatically reduced by std::ratio)
    using powered_ratio = std::ratio<powered_num, powered_den>;

    // The resulting unit type - can be used directly in si_cast
    using type = details::unit_t<value_type, powered_ratio, powered_dim>;
};

// Convenience alias to get the unit type from power_of
template <typename unit_type, int power_v>
using power_of_t = typename power_of<unit_type, power_v>::type;

// Deprecated: Use power_of instead of Pow
// The old name was confusing due to case-sensitivity with the pow() function
template <typename unit_type, int power_v>
using Pow [[deprecated("Use power_of<unit_type, power_v> instead of Pow<unit_type, power_v>")]] = power_of<unit_type, power_v>;

// Legacy alias for backward compatibility
template <typename unit_type, int power_v>
using Pow_t [[deprecated("Use power_of_t<unit_type, power_v> instead of Pow_t<unit_type, power_v>")]] = power_of_t<unit_type, power_v>;

// Special case: make power_of itself act like a unit for use in si_cast
// This allows: si_cast<meters, per<power_of<seconds, 2>>>(value)
template <typename unit_type, int power_v>
struct details::is_pkr_unit<power_of<unit_type, power_v>> : std::true_type
{
    static constexpr bool value = true;
    using value_type = typename power_of<unit_type, power_v>::value_type;
    using ratio_type = typename power_of<unit_type, power_v>::powered_ratio;
    static constexpr dimension_t value_dimension = power_of<unit_type, power_v>::powered_dim;
};

} // namespace PKR_UNITS_NAMESPACE
