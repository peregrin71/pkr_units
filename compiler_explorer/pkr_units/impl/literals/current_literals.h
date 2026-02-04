#pragma once

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/current.h"

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric current prefix literals
constexpr attoampere_t operator""_aA(long double value) noexcept
{
    return attoampere_t{static_cast<double>(value)};
}

constexpr femtoampere_t operator""_fA(long double value) noexcept
{
    return femtoampere_t{static_cast<double>(value)};
}

constexpr picoampere_t operator""_pA(long double value) noexcept
{
    return picoampere_t{static_cast<double>(value)};
}

constexpr nanoampere_t operator""_nA(long double value) noexcept
{
    return nanoampere_t{static_cast<double>(value)};
}

constexpr microampere_t operator""_uA(long double value) noexcept
{
    return microampere_t{static_cast<double>(value)};
}

constexpr milliampere_t operator""_mA(long double value) noexcept
{
    return milliampere_t{static_cast<double>(value)};
}

constexpr centiampere_t operator""_cA(long double value) noexcept
{
    return centiampere_t{static_cast<double>(value)};
}

constexpr deciampere_t operator""_dA(long double value) noexcept
{
    return deciampere_t{static_cast<double>(value)};
}

constexpr ampere_t operator""_A(long double value) noexcept
{
    return ampere_t{static_cast<double>(value)};
}

constexpr decaampere_t operator""_daA(long double value) noexcept
{
    return decaampere_t{static_cast<double>(value)};
}

constexpr hectoampere_t operator""_hA(long double value) noexcept
{
    return hectoampere_t{static_cast<double>(value)};
}

constexpr kiloampere_t operator""_kA(long double value) noexcept
{
    return kiloampere_t{static_cast<double>(value)};
}

constexpr megaampere_t operator""_MA(long double value) noexcept
{
    return megaampere_t{static_cast<double>(value)};
}

constexpr gigaampere_t operator""_GA(long double value) noexcept
{
    return gigaampere_t{static_cast<double>(value)};
}

constexpr teraampere_t operator""_TA(long double value) noexcept
{
    return teraampere_t{static_cast<double>(value)};
}

constexpr petaampere_t operator""_PA(long double value) noexcept
{
    return petaampere_t{static_cast<double>(value)};
}

constexpr exaampere_t operator""_EA(long double value) noexcept
{
    return exaampere_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
