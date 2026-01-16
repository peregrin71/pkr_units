// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "length.h"

namespace si::si_literals
{
    // Metric length prefix literals
    constexpr si::length<double, std::atto> operator"" _am(long double value) noexcept
    {
        return si::length<double, std::atto>{static_cast<double>(value});
    }

    constexpr si::length<double, std::femto> operator"" _fm(long double value) noexcept
    {
        return si::length<double, std::femto>{static_cast<double>(value});
    }

    constexpr si::length<double, std::pico> operator"" _pm(long double value) noexcept
    {
        return si::length<double, std::pico>{static_cast<double>(value});
    }

    constexpr si::length<double, std::nano> operator"" _nm(long double value) noexcept
    {
        return si::length<double, std::nano>{static_cast<double>(value});
    }

    constexpr si::length<double, std::micro> operator"" _um(long double value) noexcept
    {
        return si::length<double, std::micro>{static_cast<double>(value});
    }

    constexpr si::length<double, std::milli> operator"" _mm(long double value) noexcept
    {
        return si::length<double, std::milli>{static_cast<double>(value});
    }

    constexpr si::length<double, std::centi> operator"" _cm(long double value) noexcept
    {
        return si::length<double, std::centi>{static_cast<double>(value});
    }

    constexpr si::length<double, std::deci> operator"" _dm(long double value) noexcept
    {
        return si::length<double, std::deci>{static_cast<double>(value});
    }

    constexpr si::length<double, std::deca> operator"" _dam(long double value) noexcept
    {
        return si::length<double, std::deca>{static_cast<double>(value});
    }

    constexpr si::length<double, std::hecto> operator"" _hm(long double value) noexcept
    {
        return si::length<double, std::hecto>{static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<1, 1>> operator"" _m(long double value) noexcept
    {
        return si::length<double, std::ratio<1, 1>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::kilo> operator"" _km(long double value) noexcept
    {
        return si::length<double, std::kilo>{static_cast<double>(value});
    }

    constexpr si::length<double, std::mega> operator"" _Mm(long double value) noexcept
    {
        return si::length<double, std::mega>{static_cast<double>(value});
    }

    constexpr si::length<double, std::giga> operator"" _Gm(long double value) noexcept
    {
        return si::length<double, std::giga>{static_cast<double>(value});
    }

    constexpr si::length<double, std::tera> operator"" _Tm(long double value) noexcept
    {
        return si::length<double, std::tera>{static_cast<double>(value});
    }

    constexpr si::length<double, std::peta> operator"" _Pm(long double value) noexcept
    {
        return si::length<double, std::peta>{static_cast<double>(value});
    }

    constexpr si::length<double, std::exa> operator"" _Em(long double value) noexcept
    {
        return si::length<double, std::exa>{static_cast<double>(value});
    }

    // Imperial length literals
    constexpr si::length<double, std::ratio<254, 10000>> operator"" _in(long double value) noexcept
    {
        return si::length<double, std::ratio<254, 10000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<254, 10000000>> operator"" _mil(long double value) noexcept
    {
        return si::length<double, std::ratio<254, 10000000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<3048, 10000>> operator"" _ft(long double value) noexcept
    {
        return si::length<double, std::ratio<3048, 10000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<9144, 10000>> operator"" _yd(long double value) noexcept
    {
        return si::length<double, std::ratio<9144, 10000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<18288, 10000>> operator"" _fathom(long double value) noexcept
    {
        return si::length<double, std::ratio<18288, 10000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<50292, 10000>> operator"" _rod(long double value) noexcept
    {
        return si::length<double, std::ratio<50292, 10000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<201168, 10000>> operator"" _chain(long double value) noexcept
    {
        return si::length<double, std::ratio<201168, 10000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<201168, 1000>> operator"" _furlong(long double value) noexcept
    {
        return si::length<double, std::ratio<201168, 1000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<1609344, 1000>> operator"" _mi(long double value) noexcept
    {
        return si::length<double, std::ratio<1609344, 1000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<1852, 1>> operator"" _nmi(long double value) noexcept
    {
        return si::length<double, std::ratio<1852, 1>>(static_cast<double>(value});
    }

    // Astronomical and other units
    constexpr si::length<double, std::ratio<1, 10000000000>> operator"" _angstrom(long double value) noexcept
    {
        return si::length<double, std::ratio<1, 10000000000>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<149597870700, 1>> operator"" _au(long double value) noexcept
    {
        return si::length<double, std::ratio<149597870700, 1>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<9460730472580800, 1>> operator"" _ly(long double value) noexcept
    {
        return si::length<double, std::ratio<9460730472580800, 1>>(static_cast<double>(value});
    }

    constexpr si::length<double, std::ratio<30856775814913673, 1>> operator"" _pc(long double value) noexcept
    {
        return si::length<double, std::ratio<30856775814913673, 1>>(static_cast<double>(value});
    }
};









