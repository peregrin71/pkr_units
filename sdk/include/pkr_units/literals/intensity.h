#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/intensity.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric intensity prefix literals
constexpr attocandela_t<double> operator""_acd(long double value) noexcept
{
    return attocandela_t<double>{static_cast<double>(value)};
}

constexpr femtocandela_t<double> operator""_fcd(long double value) noexcept
{
    return femtocandela_t<double>{static_cast<double>(value)};
}

constexpr picocandela_t<double> operator""_pcd(long double value) noexcept
{
    return picocandela_t<double>{static_cast<double>(value)};
}

constexpr nanocandela_t<double> operator""_ncd(long double value) noexcept
{
    return nanocandela_t<double>{static_cast<double>(value)};
}

constexpr microcandela_t<double> operator""_ucd(long double value) noexcept
{
    return microcandela_t<double>{static_cast<double>(value)};
}

constexpr millicandela_t<double> operator""_mcd(long double value) noexcept
{
    return millicandela_t<double>{static_cast<double>(value)};
}

constexpr centicandela_t<double> operator""_ccd(long double value) noexcept
{
    return centicandela_t<double>{static_cast<double>(value)};
}

constexpr decicandela_t<double> operator""_dcd(long double value) noexcept
{
    return decicandela_t<double>{static_cast<double>(value)};
}

constexpr candela_t<double> operator""_cd(long double value) noexcept
{
    return candela_t<double>{static_cast<double>(value)};
}

constexpr decacandela_t<double> operator""_dacd(long double value) noexcept
{
    return decacandela_t<double>{static_cast<double>(value)};
}

constexpr hectocandela_t<double> operator""_hcd(long double value) noexcept
{
    return hectocandela_t<double>{static_cast<double>(value)};
}

constexpr kilocandela_t<double> operator""_kcd(long double value) noexcept
{
    return kilocandela_t<double>{static_cast<double>(value)};
}

constexpr megacandela_t<double> operator""_Mcd(long double value) noexcept
{
    return megacandela_t<double>{static_cast<double>(value)};
}

constexpr gigacandela_t<double> operator""_Gcd(long double value) noexcept
{
    return gigacandela_t<double>{static_cast<double>(value)};
}

constexpr teracandela_t<double> operator""_Tcd(long double value) noexcept
{
    return teracandela_t<double>{static_cast<double>(value)};
}

constexpr petacandela_t<double> operator""_Pcd(long double value) noexcept
{
    return petacandela_t<double>{static_cast<double>(value)};
}

constexpr exacandela_t<double> operator""_Ecd(long double value) noexcept
{
    return exacandela_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
