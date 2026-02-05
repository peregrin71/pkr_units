#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/time.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric time prefix literals
constexpr attosecond_t<double> operator""_as(long double value) noexcept
{
    return attosecond_t<double>{static_cast<double>(value)};
}

constexpr femtosecond_t<double> operator""_fs(long double value) noexcept
{
    return femtosecond_t<double>{static_cast<double>(value)};
}

constexpr picosecond_t<double> operator""_ps(long double value) noexcept
{
    return picosecond_t<double>{static_cast<double>(value)};
}

constexpr nanosecond_t<double> operator""_ns(long double value) noexcept
{
    return nanosecond_t<double>{static_cast<double>(value)};
}

constexpr microsecond_t<double> operator""_us(long double value) noexcept
{
    return microsecond_t<double>{static_cast<double>(value)};
}

constexpr millisecond_t<double> operator""_ms(long double value) noexcept
{
    return millisecond_t<double>{static_cast<double>(value)};
}

constexpr centisecond_t<double> operator""_cs(long double value) noexcept
{
    return centisecond_t<double>{static_cast<double>(value)};
}

constexpr decisecond_t<double> operator""_ds(long double value) noexcept
{
    return decisecond_t<double>{static_cast<double>(value)};
}

constexpr second_t<double> operator""_s(long double value) noexcept
{
    return second_t<double>{static_cast<double>(value)};
}

constexpr decasecond_t<double> operator""_das(long double value) noexcept
{
    return decasecond_t<double>{static_cast<double>(value)};
}

constexpr hectosecond_t<double> operator""_hs(long double value) noexcept
{
    return hectosecond_t<double>{static_cast<double>(value)};
}

constexpr kilosecond_t<double> operator""_ks(long double value) noexcept
{
    return kilosecond_t<double>{static_cast<double>(value)};
}

constexpr megasecond_t<double> operator""_Ms(long double value) noexcept
{
    return megasecond_t<double>{static_cast<double>(value)};
}

constexpr gigasecond_t<double> operator""_Gs(long double value) noexcept
{
    return gigasecond_t<double>{static_cast<double>(value)};
}

constexpr terasecond_t<double> operator""_Ts(long double value) noexcept
{
    return terasecond_t<double>{static_cast<double>(value)};
}

constexpr petasecond_t<double> operator""_Ps(long double value) noexcept
{
    return petasecond_t<double>{static_cast<double>(value)};
}

constexpr exasecond_t<double> operator""_Es(long double value) noexcept
{
    return exasecond_t<double>{static_cast<double>(value)};
}

constexpr minute_t<double> operator""_min(long double value) noexcept
{
    return minute_t<double>{static_cast<double>(value)};
}

constexpr hour_t<double> operator""_h(long double value) noexcept
{
    return hour_t<double>{static_cast<double>(value)};
}

constexpr day_t<double> operator""_d(long double value) noexcept
{
    return day_t<double>{static_cast<double>(value)};
}

constexpr week_t<double> operator""_wk(long double value) noexcept
{
    return week_t<double>{static_cast<double>(value)};
}

constexpr month_t<double> operator""_mo(long double value) noexcept
{
    return month_t<double>{static_cast<double>(value)};
}

constexpr year_t<double> operator""_yr(long double value) noexcept
{
    return year_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
