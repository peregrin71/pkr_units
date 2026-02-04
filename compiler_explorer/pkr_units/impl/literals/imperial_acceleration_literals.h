#pragma once

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/imperial/acceleration.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial acceleration literals
constexpr feet_per_second_squared_t<double> operator""_fts2(long double value) noexcept
{
    return feet_per_second_squared_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
