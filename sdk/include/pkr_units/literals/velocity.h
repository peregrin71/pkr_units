#pragma once

#include <pkr_units/units/derived/velocity.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Velocity unit literals
constexpr meter_per_second_t<double> operator""_mps(long double value) noexcept
{
    return meter_per_second_t<double>{static_cast<double>(value)};
}

constexpr kilometer_per_hour_t<double> operator""_kmph(long double value) noexcept
{
    return kilometer_per_hour_t<double>{static_cast<double>(value)};
}

constexpr centimeter_per_second_t<double> operator""_cmps(long double value) noexcept
{
    return centimeter_per_second_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
