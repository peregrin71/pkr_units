#pragma once

#include <pkr_units/units/derived/acceleration.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Acceleration unit literals
constexpr meter_per_second_squared_t<double> operator""_mps2(long double value) noexcept
{
    return meter_per_second_squared_t<double>{static_cast<double>(value)};
}

constexpr centimeter_per_second_squared_t<double> operator""_cms2(long double value) noexcept
{
    return centimeter_per_second_squared_t<double>{static_cast<double>(value)};
}

constexpr millimeter_per_second_squared_t<double> operator""_mms2(long double value) noexcept
{
    return millimeter_per_second_squared_t<double>{static_cast<double>(value)};
}

constexpr standard_gravity_t<double> operator""_g_earth(long double value) noexcept
{
    return standard_gravity_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
