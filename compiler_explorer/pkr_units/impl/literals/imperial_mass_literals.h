#pragma once

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/imperial/mass.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial mass literals
constexpr grain_t<double> operator""_gr(long double value) noexcept
{
    return grain_t<double>{static_cast<double>(value)};
}

constexpr ounce_t<double> operator""_oz(long double value) noexcept
{
    return ounce_t<double>{static_cast<double>(value)};
}

constexpr pound_t<double> operator""_lb(long double value) noexcept
{
    return pound_t<double>{static_cast<double>(value)};
}

constexpr stone_t<double> operator""_st(long double value) noexcept
{
    return stone_t<double>{static_cast<double>(value)};
}

constexpr us_ton_t<double> operator""_short_ton(long double value) noexcept
{
    return us_ton_t<double>{static_cast<double>(value)};
}

constexpr long_ton_t<double> operator""_long_ton(long double value) noexcept
{
    return long_ton_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
