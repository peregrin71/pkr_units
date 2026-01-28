#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/temperature.h>
#include <pkr_units/units/temperature/celsius.h>
#include <pkr_units/units/temperature/fahrenheit.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric temperature prefix literals
constexpr attokelvin_t operator""_aK(long double value) noexcept
{
    return attokelvin_t{static_cast<double>(value)};
}

constexpr femtokelvin_t operator""_fK(long double value) noexcept
{
    return femtokelvin_t{static_cast<double>(value)};
}

constexpr picokelvin_t operator""_pK(long double value) noexcept
{
    return picokelvin_t{static_cast<double>(value)};
}

constexpr nanokelvin_t operator""_nK(long double value) noexcept
{
    return nanokelvin_t{static_cast<double>(value)};
}

constexpr microkelvin_t operator""_uK(long double value) noexcept
{
    return microkelvin_t{static_cast<double>(value)};
}

constexpr millikelvin_t operator""_mK(long double value) noexcept
{
    return millikelvin_t{static_cast<double>(value)};
}

constexpr centikelvin_t operator""_cK(long double value) noexcept
{
    return centikelvin_t{static_cast<double>(value)};
}

constexpr decikelvin_t operator""_dK(long double value) noexcept
{
    return decikelvin_t{static_cast<double>(value)};
}

constexpr kelvin_t operator""_K(long double value) noexcept
{
    return kelvin_t{static_cast<double>(value)};
}

constexpr decakelvin_t operator""_daK(long double value) noexcept
{
    return decakelvin_t{static_cast<double>(value)};
}

constexpr hectokelvin_t operator""_hK(long double value) noexcept
{
    return hectokelvin_t{static_cast<double>(value)};
}

constexpr kilokelvin_t operator""_kK(long double value) noexcept
{
    return kilokelvin_t{static_cast<double>(value)};
}

constexpr megakelvin_t operator""_MK(long double value) noexcept
{
    return megakelvin_t{static_cast<double>(value)};
}

constexpr gigakelvin_t operator""_GK(long double value) noexcept
{
    return gigakelvin_t{static_cast<double>(value)};
}

constexpr terakelvin_t operator""_TK(long double value) noexcept
{
    return terakelvin_t{static_cast<double>(value)};
}

constexpr petakelvin_t operator""_PK(long double value) noexcept
{
    return petakelvin_t{static_cast<double>(value)};
}

constexpr exakelvin_t operator""_EK(long double value) noexcept
{
    return exakelvin_t{static_cast<double>(value)};
}

// Affine temperature literals
constexpr celsius_t operator""_C(long double value) noexcept
{
    return celsius_t{static_cast<double>(value)};
}

constexpr fahrenheit_t operator""_F(long double value) noexcept
{
    return fahrenheit_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
