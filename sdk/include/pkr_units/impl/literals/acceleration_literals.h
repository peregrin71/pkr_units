#pragma once

#include <pkr_units/units/derived/acceleration.h>
#include <pkr_units/units/imperial/acceleration.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Acceleration unit literals
constexpr meter_per_second_squared_t operator"" _mps2(long double value) noexcept
{
    return meter_per_second_squared_t{static_cast<double>(value)};
}

constexpr centimeter_per_second_squared_t operator"" _cms2(long double value) noexcept
{
    return centimeter_per_second_squared_t{static_cast<double>(value)};
}

constexpr millimeter_per_second_squared_t operator"" _mms2(long double value) noexcept
{
    return millimeter_per_second_squared_t{static_cast<double>(value)};
}

constexpr feet_per_second_squared_t operator"" _fts2(long double value) noexcept
{
    return feet_per_second_squared_t{static_cast<double>(value)};
}

constexpr standard_gravity_t operator"" _g(long double value) noexcept
{
    return standard_gravity_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
