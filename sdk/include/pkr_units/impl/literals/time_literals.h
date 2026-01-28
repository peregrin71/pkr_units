#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/time.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric time prefix literals
constexpr attosecond_t operator""_as(long double value) noexcept
{
    return attosecond_t{static_cast<double>(value)};
}

constexpr femtosecond_t operator""_fs(long double value) noexcept
{
    return femtosecond_t{static_cast<double>(value)};
}

constexpr picosecond_t operator""_ps(long double value) noexcept
{
    return picosecond_t{static_cast<double>(value)};
}

constexpr nanosecond_t operator""_ns(long double value) noexcept
{
    return nanosecond_t{static_cast<double>(value)};
}

constexpr microsecond_t operator""_us(long double value) noexcept
{
    return microsecond_t{static_cast<double>(value)};
}

constexpr millisecond_t operator""_ms(long double value) noexcept
{
    return millisecond_t{static_cast<double>(value)};
}

constexpr centisecond_t operator""_cs(long double value) noexcept
{
    return centisecond_t{static_cast<double>(value)};
}

constexpr decisecond_t operator""_ds(long double value) noexcept
{
    return decisecond_t{static_cast<double>(value)};
}

constexpr second_t operator""_s(long double value) noexcept
{
    return second_t{static_cast<double>(value)};
}

constexpr decasecond_t operator""_das(long double value) noexcept
{
    return decasecond_t{static_cast<double>(value)};
}

constexpr hectosecond_t operator""_hs(long double value) noexcept
{
    return hectosecond_t{static_cast<double>(value)};
}

constexpr kilosecond_t operator""_ks(long double value) noexcept
{
    return kilosecond_t{static_cast<double>(value)};
}

constexpr megasecond_t operator""_Ms(long double value) noexcept
{
    return megasecond_t{static_cast<double>(value)};
}

constexpr gigasecond_t operator""_Gs(long double value) noexcept
{
    return gigasecond_t{static_cast<double>(value)};
}

constexpr terasecond_t operator""_Ts(long double value) noexcept
{
    return terasecond_t{static_cast<double>(value)};
}

constexpr petasecond_t operator""_Ps(long double value) noexcept
{
    return petasecond_t{static_cast<double>(value)};
}

constexpr exasecond_t operator""_Es(long double value) noexcept
{
    return exasecond_t{static_cast<double>(value)};
}

constexpr hour_t operator""_h(long double value) noexcept
{
    return hour_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
