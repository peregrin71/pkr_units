#pragma once

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/amount.h"

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric amount prefix literals
constexpr attomole_t operator""_amol(long double value) noexcept
{
    return attomole_t{static_cast<double>(value)};
}

constexpr femtomole_t operator""_fmol(long double value) noexcept
{
    return femtomole_t{static_cast<double>(value)};
}

constexpr picomole_t operator""_pmol(long double value) noexcept
{
    return picomole_t{static_cast<double>(value)};
}

constexpr nanomole_t operator""_nmol(long double value) noexcept
{
    return nanomole_t{static_cast<double>(value)};
}

constexpr micromole_t operator""_umol(long double value) noexcept
{
    return micromole_t{static_cast<double>(value)};
}

constexpr millimole_t operator""_mmol(long double value) noexcept
{
    return millimole_t{static_cast<double>(value)};
}

constexpr centimole_t operator""_cmol(long double value) noexcept
{
    return centimole_t{static_cast<double>(value)};
}

constexpr decimole_t operator""_dmol(long double value) noexcept
{
    return decimole_t{static_cast<double>(value)};
}

constexpr mole_t operator""_mol(long double value) noexcept
{
    return mole_t{static_cast<double>(value)};
}

constexpr decamole_t operator""_damol(long double value) noexcept
{
    return decamole_t{static_cast<double>(value)};
}

constexpr hectomole_t operator""_hmol(long double value) noexcept
{
    return hectomole_t{static_cast<double>(value)};
}

constexpr kilomole_t operator""_kmol(long double value) noexcept
{
    return kilomole_t{static_cast<double>(value)};
}

constexpr megamole_t operator""_Mmol(long double value) noexcept
{
    return megamole_t{static_cast<double>(value)};
}

constexpr gigamole_t operator""_Gmol(long double value) noexcept
{
    return gigamole_t{static_cast<double>(value)};
}

constexpr teramole_t operator""_Tmol(long double value) noexcept
{
    return teramole_t{static_cast<double>(value)};
}

constexpr petamole_t operator""_Pmol(long double value) noexcept
{
    return petamole_t{static_cast<double>(value)};
}

constexpr examole_t operator""_Emol(long double value) noexcept
{
    return examole_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
