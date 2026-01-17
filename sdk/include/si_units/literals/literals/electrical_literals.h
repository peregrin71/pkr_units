// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "electrical.h"
#include "../../namespace_config.h"

namespace si::si_literals
{
    // Electric charge unit literals
    constexpr si::coulomb operator"" _C(long double value) noexcept
    {
        return si::coulomb{static_cast<double>(value});
    }

    constexpr si::kilocoulomb operator"" _kC(long double value) noexcept
    {
        return si::kilocoulomb{static_cast<double>(value});
    }

    constexpr si::millicoulomb operator"" _mC(long double value) noexcept
    {
        return si::millicoulomb{static_cast<double>(value});
    }

    constexpr si::microcoulomb operator"" _uC(long double value) noexcept
    {
        return si::microcoulomb{static_cast<double>(value});
    }

    constexpr si::nanocoulomb operator"" _nC(long double value) noexcept
    {
        return si::nanocoulomb{static_cast<double>(value});
    }

    constexpr si::picocoulomb operator"" _pC(long double value) noexcept
    {
        return si::picocoulomb{static_cast<double>(value});
    }

    // Electric potential unit literals
    constexpr si::volt operator"" _V(long double value) noexcept
    {
        return si::volt{static_cast<double>(value});
    }

    constexpr si::kilovolt operator"" _kV(long double value) noexcept
    {
        return si::kilovolt{static_cast<double>(value});
    }

    constexpr si::megavolt operator"" _MV(long double value) noexcept
    {
        return si::megavolt{static_cast<double>(value});
    }

    constexpr si::millivolt operator"" _mV(long double value) noexcept
    {
        return si::millivolt{static_cast<double>(value});
    }

    constexpr si::microvolt operator"" _uV(long double value) noexcept
    {
        return si::microvolt{static_cast<double>(value});
    }

    // Electric resistance unit literals
    constexpr si::ohm operator"" _ohm(long double value) noexcept
    {
        return si::ohm{static_cast<double>(value});
    }

    constexpr si::kilohm operator"" _kohm(long double value) noexcept
    {
        return si::kilohm{static_cast<double>(value});
    }

    constexpr si::megohm operator"" _Mohm(long double value) noexcept
    {
        return si::megohm{static_cast<double>(value});
    }

    constexpr si::gigohm operator"" _Gohm(long double value) noexcept
    {
        return si::gigohm{static_cast<double>(value});
    }

    constexpr si::milliohm operator"" _mohm(long double value) noexcept
    {
        return si::milliohm{static_cast<double>(value});
    }

    constexpr si::microohm operator"" _uohm(long double value) noexcept
    {
        return si::microohm{static_cast<double>(value});
    }

    // Capacitance unit literals
    constexpr si::farad operator"" _F(long double value) noexcept
    {
        return si::farad{static_cast<double>(value});
    }

    constexpr si::millifarad operator"" _mF(long double value) noexcept
    {
        return si::millifarad{static_cast<double>(value});
    }

    constexpr si::microfarad operator"" _uF(long double value) noexcept
    {
        return si::microfarad{static_cast<double>(value});
    }

    constexpr si::nanofarad operator"" _nF(long double value) noexcept
    {
        return si::nanofarad{static_cast<double>(value});
    }

    constexpr si::picofarad operator"" _pF(long double value) noexcept
    {
        return si::picofarad{static_cast<double>(value});
    }

    // Inductance unit literals
    constexpr si::henry operator"" _H(long double value) noexcept
    {
        return si::henry{static_cast<double>(value});
    }

    constexpr si::millihenry operator"" _mH(long double value) noexcept
    {
        return si::millihenry{static_cast<double>(value});
    }

    constexpr si::microhenry operator"" _uH(long double value) noexcept
    {
        return si::microhenry{static_cast<double>(value});
    }

    constexpr si::nanohenry operator"" _nH(long double value) noexcept
    {
        return si::nanohenry{static_cast<double>(value});
    }

    // Conductance unit literals
    constexpr si::siemens operator"" _S(long double value) noexcept
    {
        return si::siemens{static_cast<double>(value});
    }

    constexpr si::millisiemens operator"" _mS(long double value) noexcept
    {
        return si::millisiemens{static_cast<double>(value});
    }

    constexpr si::microsiemens operator"" _uS(long double value) noexcept
    {
        return si::microsiemens{static_cast<double>(value});
    }

PKR_SI_NAMESPACE_END::si_literals










