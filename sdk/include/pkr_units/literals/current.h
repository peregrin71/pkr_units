#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/current.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric current prefix literals
constexpr attoampere_t<double> operator""_aA(long double value) noexcept
{
    return attoampere_t<double>{static_cast<double>(value)};
}

constexpr femtoampere_t<double> operator""_fA(long double value) noexcept
{
    return femtoampere_t<double>{static_cast<double>(value)};
}

constexpr picoampere_t<double> operator""_pA(long double value) noexcept
{
    return picoampere_t<double>{static_cast<double>(value)};
}

constexpr nanoampere_t<double> operator""_nA(long double value) noexcept
{
    return nanoampere_t<double>{static_cast<double>(value)};
}

constexpr microampere_t<double> operator""_uA(long double value) noexcept
{
    return microampere_t<double>{static_cast<double>(value)};
}

constexpr milliampere_t<double> operator""_mA(long double value) noexcept
{
    return milliampere_t<double>{static_cast<double>(value)};
}

constexpr centiampere_t<double> operator""_cA(long double value) noexcept
{
    return centiampere_t<double>{static_cast<double>(value)};
}

constexpr deciampere_t<double> operator""_dA(long double value) noexcept
{
    return deciampere_t<double>{static_cast<double>(value)};
}

constexpr ampere_t<double> operator""_A(long double value) noexcept
{
    return ampere_t<double>{static_cast<double>(value)};
}

constexpr decaampere_t<double> operator""_daA(long double value) noexcept
{
    return decaampere_t<double>{static_cast<double>(value)};
}

constexpr hectoampere_t<double> operator""_hA(long double value) noexcept
{
    return hectoampere_t<double>{static_cast<double>(value)};
}

constexpr kiloampere_t<double> operator""_kA(long double value) noexcept
{
    return kiloampere_t<double>{static_cast<double>(value)};
}

constexpr megaampere_t<double> operator""_MA(long double value) noexcept
{
    return megaampere_t<double>{static_cast<double>(value)};
}

constexpr gigaampere_t<double> operator""_GA(long double value) noexcept
{
    return gigaampere_t<double>{static_cast<double>(value)};
}

constexpr teraampere_t<double> operator""_TA(long double value) noexcept
{
    return teraampere_t<double>{static_cast<double>(value)};
}

constexpr petaampere_t<double> operator""_PA(long double value) noexcept
{
    return petaampere_t<double>{static_cast<double>(value)};
}

constexpr exaampere_t<double> operator""_EA(long double value) noexcept
{
    return exaampere_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
