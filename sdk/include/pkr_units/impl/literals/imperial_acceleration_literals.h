#pragma once

#include <pkr_units/units/imperial/acceleration.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial acceleration literals
constexpr feet_per_second_squared_t operator""_fts2(long double value) noexcept
{
    return feet_per_second_squared_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
