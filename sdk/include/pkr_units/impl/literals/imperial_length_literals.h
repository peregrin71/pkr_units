#pragma once

#include <pkr_units/units/imperial/length.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial length literals
constexpr inch_t operator""_in(long double value) noexcept
{
    return inch_t{static_cast<double>(value)};
}

constexpr foot_t operator""_ft(long double value) noexcept
{
    return foot_t{static_cast<double>(value)};
}

constexpr yard_t operator""_yd(long double value) noexcept
{
    return yard_t{static_cast<double>(value)};
}

constexpr mile_t operator""_mi(long double value) noexcept
{
    return mile_t{static_cast<double>(value)};
}

constexpr nautical_mile_t operator""_nmi(long double value) noexcept
{
    return nautical_mile_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
