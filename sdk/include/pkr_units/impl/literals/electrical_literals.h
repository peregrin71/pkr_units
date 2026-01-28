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
constexpr coulomb_t operator"" _C(long double value) noexcept
{
    return coulomb_t{static_cast<double>(value)};
}

constexpr kilocoulomb_t operator"" _kC(long double value) noexcept
{
    return kilocoulomb_t{static_cast<double>(value)};
}

constexpr millicoulomb_t operator"" _mC(long double value) noexcept
{
    return millicoulomb_t{static_cast<double>(value)};
}

constexpr microcoulomb_t operator"" _uC(long double value) noexcept
{
    return microcoulomb_t{static_cast<double>(value)};
}

constexpr nanocoulomb_t operator"" _nC(long double value) noexcept
{
    return nanocoulomb_t{static_cast<double>(value)};
}

constexpr picocoulomb_t operator"" _pC(long double value) noexcept
{
    return picocoulomb_t{static_cast<double>(value)};
}

// Electric potential unit literals
constexpr volt_t operator"" _V(long double value) noexcept
{
    return volt_t{static_cast<double>(value)};
}

constexpr kilovolt_t operator"" _kV(long double value) noexcept
{
    return kilovolt_t{static_cast<double>(value)};
}

constexpr megavolt_t operator"" _MV(long double value) noexcept
{
    return megavolt_t{static_cast<double>(value)};
}

constexpr millivolt_t operator"" _mV(long double value) noexcept
{
    return millivolt_t{static_cast<double>(value)};
}

constexpr microvolt_t operator"" _uV(long double value) noexcept
{
    return microvolt_t{static_cast<double>(value)};
}

// Electric resistance unit literals
constexpr ohm_t operator"" _ohm(long double value) noexcept
{
    return ohm_t{static_cast<double>(value)};
}

constexpr kilohm_t operator"" _kohm(long double value) noexcept
{
    return kilohm_t{static_cast<double>(value)};
}

constexpr megohm_t operator"" _Mohm(long double value) noexcept
{
    return megohm_t{static_cast<double>(value)};
}

constexpr gigohm_t operator"" _Gohm(long double value) noexcept
{
    return gigohm_t{static_cast<double>(value)};
}

constexpr milliohm_t operator"" _mohm(long double value) noexcept
{
    return milliohm_t{static_cast<double>(value)};
}

constexpr microohm_t operator"" _uohm(long double value) noexcept
{
    return microohm_t{static_cast<double>(value)};
}

// Capacitance unit literals
constexpr farad_t operator"" _F(long double value) noexcept
{
    return farad_t{static_cast<double>(value)};
}

constexpr millifarad_t operator"" _mF(long double value) noexcept
{
    return millifarad_t{static_cast<double>(value)};
}

constexpr microfarad_t operator"" _uF(long double value) noexcept
{
    return microfarad_t{static_cast<double>(value)};
}

constexpr nanofarad_t operator"" _nF(long double value) noexcept
{
    return nanofarad_t{static_cast<double>(value)};
}

constexpr picofarad_t operator"" _pF(long double value) noexcept
{
    return picofarad_t{static_cast<double>(value)};
}

// Inductance unit literals
constexpr henry_t operator"" _H(long double value) noexcept
{
    return henry_t{static_cast<double>(value)};
}

constexpr millihenry_t operator"" _mH(long double value) noexcept
{
    return millihenry_t{static_cast<double>(value)};
}

constexpr microhenry_t operator"" _uH(long double value) noexcept
{
    return microhenry_t{static_cast<double>(value)};
}

constexpr nanohenry_t operator"" _nH(long double value) noexcept
{
    return nanohenry_t{static_cast<double>(value)};
}

// Conductance unit literals
constexpr siemens_t operator"" _S(long double value) noexcept
{
    return siemens_t{static_cast<double>(value)};
}

constexpr millisiemens_t operator"" _mS(long double value) noexcept
{
    return millisiemens_t{static_cast<double>(value)};
}

constexpr microsiemens_t operator"" _uS(long double value) noexcept
{
    return microsiemens_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
