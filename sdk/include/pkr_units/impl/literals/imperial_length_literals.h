#pragma once

#include <pkr_units/units/imperial/length.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial length literals
constexpr inch_t<double> operator""_in(long double value) noexcept
{
    return inch_t<double>{static_cast<double>(value)};
}

constexpr foot_t<double> operator""_ft(long double value) noexcept
{
    return foot_t<double>{static_cast<double>(value)};
}

constexpr yard_t<double> operator""_yd(long double value) noexcept
{
    return yard_t<double>{static_cast<double>(value)};
}

constexpr mile_t<double> operator""_mi(long double value) noexcept
{
    return mile_t<double>{static_cast<double>(value)};
}

constexpr nautical_mile_t<double> operator""_nmi(long double value) noexcept
{
    return nautical_mile_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
