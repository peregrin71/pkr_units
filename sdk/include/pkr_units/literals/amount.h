#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/amount.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric amount prefix literals
constexpr attomole_t<double> operator""_amol(long double value) noexcept
{
    return attomole_t<double>{static_cast<double>(value)};
}

constexpr femtomole_t<double> operator""_fmol(long double value) noexcept
{
    return femtomole_t<double>{static_cast<double>(value)};
}

constexpr picomole_t<double> operator""_pmol(long double value) noexcept
{
    return picomole_t<double>{static_cast<double>(value)};
}

constexpr nanomole_t<double> operator""_nmol(long double value) noexcept
{
    return nanomole_t<double>{static_cast<double>(value)};
}

constexpr micromole_t<double> operator""_umol(long double value) noexcept
{
    return micromole_t<double>{static_cast<double>(value)};
}

constexpr millimole_t<double> operator""_mmol(long double value) noexcept
{
    return millimole_t<double>{static_cast<double>(value)};
}

constexpr centimole_t<double> operator""_cmol(long double value) noexcept
{
    return centimole_t<double>{static_cast<double>(value)};
}

constexpr decimole_t<double> operator""_dmol(long double value) noexcept
{
    return decimole_t<double>{static_cast<double>(value)};
}

constexpr mole_t<double> operator""_mol(long double value) noexcept
{
    return mole_t<double>{static_cast<double>(value)};
}

constexpr decamole_t<double> operator""_damol(long double value) noexcept
{
    return decamole_t<double>{static_cast<double>(value)};
}

constexpr hectomole_t<double> operator""_hmol(long double value) noexcept
{
    return hectomole_t<double>{static_cast<double>(value)};
}

constexpr kilomole_t<double> operator""_kmol(long double value) noexcept
{
    return kilomole_t<double>{static_cast<double>(value)};
}

constexpr megamole_t<double> operator""_Mmol(long double value) noexcept
{
    return megamole_t<double>{static_cast<double>(value)};
}

constexpr gigamole_t<double> operator""_Gmol(long double value) noexcept
{
    return gigamole_t<double>{static_cast<double>(value)};
}

constexpr teramole_t<double> operator""_Tmol(long double value) noexcept
{
    return teramole_t<double>{static_cast<double>(value)};
}

constexpr petamole_t<double> operator""_Pmol(long double value) noexcept
{
    return petamole_t<double>{static_cast<double>(value)};
}

constexpr examole_t<double> operator""_Emol(long double value) noexcept
{
    return examole_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
