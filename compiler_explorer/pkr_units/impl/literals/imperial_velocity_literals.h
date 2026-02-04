#pragma once

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/imperial/velocity.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial velocity literals
constexpr miles_per_hour_t operator""_mph(long double value) noexcept
{
    return miles_per_hour_t{static_cast<double>(value)};
}

constexpr knots_t operator""_kt(long double value) noexcept
{
    return knots_t{static_cast<double>(value)};
}

constexpr feet_per_second_t operator""_fps(long double value) noexcept
{
    return feet_per_second_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
