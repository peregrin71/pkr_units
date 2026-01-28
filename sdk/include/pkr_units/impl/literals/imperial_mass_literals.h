#pragma once

#include <pkr_units/units/imperial/mass.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial mass literals
constexpr grain_t operator"" _gr(long double value) noexcept
{
    return grain_t{static_cast<double>(value)};
}

constexpr ounce_t operator"" _oz(long double value) noexcept
{
    return ounce_t{static_cast<double>(value)};
}

constexpr pound_t operator"" _lb(long double value) noexcept
{
    return pound_t{static_cast<double>(value)};
}

constexpr stone_t operator"" _st(long double value) noexcept
{
    return stone_t{static_cast<double>(value)};
}

constexpr us_ton_t operator"" _short_ton(long double value) noexcept
{
    return us_ton_t{static_cast<double>(value)};
}

constexpr long_ton_t operator"" _long_ton(long double value) noexcept
{
    return long_ton_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
