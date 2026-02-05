#pragma once

#include <pkr_units/units/imperial/velocity.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial velocity literals
constexpr miles_per_hour_t<double> operator""_mph(long double value) noexcept
{
    return miles_per_hour_t<double>{static_cast<double>(value)};
}

constexpr knots_t<double> operator""_kt(long double value) noexcept
{
    return knots_t<double>{static_cast<double>(value)};
}

constexpr feet_per_second_t<double> operator""_fps(long double value) noexcept
{
    return feet_per_second_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
