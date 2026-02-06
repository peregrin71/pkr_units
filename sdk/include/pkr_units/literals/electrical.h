#pragma once

#include <pkr_units/units/derived/electrical/charge.h>
#include <pkr_units/units/derived/electrical/potential.h>
#include <pkr_units/units/derived/electrical/resistance.h>
#include <pkr_units/units/derived/electrical/capacitance.h>
#include <pkr_units/units/derived/electrical/inductance.h>
#include <pkr_units/units/derived/electrical/conductance.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Electric charge unit literals
constexpr coulomb_t<double> operator""_C(long double value) noexcept
{
    return coulomb_t<double>{static_cast<double>(value)};
}

constexpr kilocoulomb_t<double> operator""_kC(long double value) noexcept
{
    return kilocoulomb_t<double>{static_cast<double>(value)};
}

constexpr millicoulomb_t<double> operator""_mC(long double value) noexcept
{
    return millicoulomb_t<double>{static_cast<double>(value)};
}

constexpr microcoulomb_t<double> operator""_uC(long double value) noexcept
{
    return microcoulomb_t<double>{static_cast<double>(value)};
}

constexpr nanocoulomb_t<double> operator""_nC(long double value) noexcept
{
    return nanocoulomb_t<double>{static_cast<double>(value)};
}

constexpr picocoulomb_t<double> operator""_pC(long double value) noexcept
{
    return picocoulomb_t<double>{static_cast<double>(value)};
}

// Electric potential unit literals
constexpr volt_t<double> operator""_V(long double value) noexcept
{
    return volt_t<double>{static_cast<double>(value)};
}

constexpr kilovolt_t<double> operator""_kV(long double value) noexcept
{
    return kilovolt_t<double>{static_cast<double>(value)};
}

constexpr megavolt_t<double> operator""_MV(long double value) noexcept
{
    return megavolt_t<double>{static_cast<double>(value)};
}

constexpr millivolt_t<double> operator""_mV(long double value) noexcept
{
    return millivolt_t<double>{static_cast<double>(value)};
}

constexpr microvolt_t<double> operator""_uV(long double value) noexcept
{
    return microvolt_t<double>{static_cast<double>(value)};
}

// Electric resistance unit literals
constexpr ohm_t<double> operator""_ohm(long double value) noexcept
{
    return ohm_t<double>{static_cast<double>(value)};
}

constexpr kiloohm_t<double> operator""_kohm(long double value) noexcept
{
    return kiloohm_t<double>{static_cast<double>(value)};
}

constexpr megaohm_t<double> operator""_Mohm(long double value) noexcept
{
    return megaohm_t<double>{static_cast<double>(value)};
}

constexpr gigaohm_t<double> operator""_Gohm(long double value) noexcept
{
    return gigaohm_t<double>{static_cast<double>(value)};
}

constexpr milliohm_t<double> operator""_mohm(long double value) noexcept
{
    return milliohm_t<double>{static_cast<double>(value)};
}

constexpr microohm_t<double> operator""_uohm(long double value) noexcept
{
    return microohm_t<double>{static_cast<double>(value)};
}

// Capacitance unit literals
constexpr farad_t<double> operator""_F(long double value) noexcept
{
    return farad_t<double>{static_cast<double>(value)};
}

constexpr millifarad_t<double> operator""_mF(long double value) noexcept
{
    return millifarad_t<double>{static_cast<double>(value)};
}

constexpr microfarad_t<double> operator""_uF(long double value) noexcept
{
    return microfarad_t<double>{static_cast<double>(value)};
}

constexpr nanofarad_t<double> operator""_nF(long double value) noexcept
{
    return nanofarad_t<double>{static_cast<double>(value)};
}

constexpr picofarad_t<double> operator""_pF(long double value) noexcept
{
    return picofarad_t<double>{static_cast<double>(value)};
}

// Inductance unit literals
constexpr henry_t<double> operator""_H(long double value) noexcept
{
    return henry_t<double>{static_cast<double>(value)};
}

constexpr millihenry_t<double> operator""_mH(long double value) noexcept
{
    return millihenry_t<double>{static_cast<double>(value)};
}

constexpr microhenry_t<double> operator""_uH(long double value) noexcept
{
    return microhenry_t<double>{static_cast<double>(value)};
}

constexpr nanohenry_t<double> operator""_nH(long double value) noexcept
{
    return nanohenry_t<double>{static_cast<double>(value)};
}

// Conductance unit literals
constexpr siemens_t<double> operator""_S(long double value) noexcept
{
    return siemens_t<double>{static_cast<double>(value)};
}

constexpr millisiemens_t<double> operator""_mS(long double value) noexcept
{
    return millisiemens_t<double>{static_cast<double>(value)};
}

constexpr microsiemens_t<double> operator""_uS(long double value) noexcept
{
    return microsiemens_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
