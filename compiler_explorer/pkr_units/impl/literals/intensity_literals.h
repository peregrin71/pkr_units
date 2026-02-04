#pragma once

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/intensity.h"

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric intensity prefix literals
constexpr attocandela_t operator""_acd(long double value) noexcept
{
    return attocandela_t{static_cast<double>(value)};
}

constexpr femtocandela_t operator""_fcd(long double value) noexcept
{
    return femtocandela_t{static_cast<double>(value)};
}

constexpr picocandela_t operator""_pcd(long double value) noexcept
{
    return picocandela_t{static_cast<double>(value)};
}

constexpr nanocandela_t operator""_ncd(long double value) noexcept
{
    return nanocandela_t{static_cast<double>(value)};
}

constexpr microcandela_t operator""_ucd(long double value) noexcept
{
    return microcandela_t{static_cast<double>(value)};
}

constexpr millicandela_t operator""_mcd(long double value) noexcept
{
    return millicandela_t{static_cast<double>(value)};
}

constexpr centicandela_t operator""_ccd(long double value) noexcept
{
    return centicandela_t{static_cast<double>(value)};
}

constexpr decicandela_t operator""_dcd(long double value) noexcept
{
    return decicandela_t{static_cast<double>(value)};
}

constexpr candela_t operator""_cd(long double value) noexcept
{
    return candela_t{static_cast<double>(value)};
}

constexpr decacandela_t operator""_dacd(long double value) noexcept
{
    return decacandela_t{static_cast<double>(value)};
}

constexpr hectocandela_t operator""_hcd(long double value) noexcept
{
    return hectocandela_t{static_cast<double>(value)};
}

constexpr kilocandela_t operator""_kcd(long double value) noexcept
{
    return kilocandela_t{static_cast<double>(value)};
}

constexpr megacandela_t operator""_Mcd(long double value) noexcept
{
    return megacandela_t{static_cast<double>(value)};
}

constexpr gigacandela_t operator""_Gcd(long double value) noexcept
{
    return gigacandela_t{static_cast<double>(value)};
}

constexpr teracandela_t operator""_Tcd(long double value) noexcept
{
    return teracandela_t{static_cast<double>(value)};
}

constexpr petacandela_t operator""_Pcd(long double value) noexcept
{
    return petacandela_t{static_cast<double>(value)};
}

constexpr exacandela_t operator""_Ecd(long double value) noexcept
{
    return exacandela_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
