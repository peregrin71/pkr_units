#pragma once

#include <pkr_units/units/derived/velocity.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Velocity unit literals
constexpr meter_per_second_t operator"" _mps(long double value) noexcept
{
    return meter_per_second_t{static_cast<double>(value)};
}

constexpr kilometer_per_hour_t operator"" _kmph(long double value) noexcept
{
    return kilometer_per_hour_t{static_cast<double>(value)};
}

constexpr miles_per_hour_t operator"" _mph(long double value) noexcept
{
    return miles_per_hour_t{static_cast<double>(value)};
}

constexpr knots_t operator"" _kt(long double value) noexcept
{
    return knots_t{static_cast<double>(value)};
}

constexpr centimeter_per_second_t operator"" _cmps(long double value) noexcept
{
    return centimeter_per_second_t{static_cast<double>(value)};
}

constexpr feet_per_second_t operator"" _fps(long double value) noexcept
{
    return feet_per_second_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
