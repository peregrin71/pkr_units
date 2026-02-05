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
constexpr attokelvin_t<double> operator""_aK(long double value) noexcept
{
    return attokelvin_t<double>{static_cast<double>(value)};
}

constexpr femtokelvin_t<double> operator""_fK(long double value) noexcept
{
    return femtokelvin_t<double>{static_cast<double>(value)};
}

constexpr picokelvin_t<double> operator""_pK(long double value) noexcept
{
    return picokelvin_t<double>{static_cast<double>(value)};
}

constexpr nanokelvin_t<double> operator""_nK(long double value) noexcept
{
    return nanokelvin_t<double>{static_cast<double>(value)};
}

constexpr microkelvin_t<double> operator""_uK(long double value) noexcept
{
    return microkelvin_t<double>{static_cast<double>(value)};
}

constexpr millikelvin_t<double> operator""_mK(long double value) noexcept
{
    return millikelvin_t<double>{static_cast<double>(value)};
}

constexpr centikelvin_t<double> operator""_cK(long double value) noexcept
{
    return centikelvin_t<double>{static_cast<double>(value)};
}

constexpr decikelvin_t<double> operator""_dK(long double value) noexcept
{
    return decikelvin_t<double>{static_cast<double>(value)};
}

constexpr kelvin_t<double> operator""_K(long double value) noexcept
{
    return kelvin_t<double>{static_cast<double>(value)};
}

constexpr decakelvin_t<double> operator""_daK(long double value) noexcept
{
    return decakelvin_t<double>{static_cast<double>(value)};
}

constexpr hectokelvin_t<double> operator""_hK(long double value) noexcept
{
    return hectokelvin_t<double>{static_cast<double>(value)};
}

constexpr kilokelvin_t<double> operator""_kK(long double value) noexcept
{
    return kilokelvin_t<double>{static_cast<double>(value)};
}

constexpr megakelvin_t<double> operator""_MK(long double value) noexcept
{
    return megakelvin_t<double>{static_cast<double>(value)};
}

constexpr gigakelvin_t<double> operator""_GK(long double value) noexcept
{
    return gigakelvin_t<double>{static_cast<double>(value)};
}

constexpr terakelvin_t<double> operator""_TK(long double value) noexcept
{
    return terakelvin_t<double>{static_cast<double>(value)};
}

constexpr petakelvin_t<double> operator""_PK(long double value) noexcept
{
    return petakelvin_t<double>{static_cast<double>(value)};
}

constexpr exakelvin_t<double> operator""_EK(long double value) noexcept
{
    return exakelvin_t<double>{static_cast<double>(value)};
}

// Affine temperature literals
constexpr celsius_t<double> operator""_degC(long double value) noexcept
{
    return celsius_t<double>{static_cast<double>(value)};
}

constexpr fahrenheit_t<double> operator""_degF(long double value) noexcept
{
    return fahrenheit_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
