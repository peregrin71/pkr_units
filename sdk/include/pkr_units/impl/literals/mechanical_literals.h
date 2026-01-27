#pragma once

#include <pkr_units/units/derived/mechanical/force.h>
#include <pkr_units/units/derived/mechanical/pressure.h>
#include <pkr_units/units/derived/mechanical/energy.h>
#include <pkr_units/units/derived/mechanical/power.h>
#include <pkr_units/impl/namespace_config.h>

namespace si::si_literals
{
// Force unit literals
constexpr si::newton operator"" _N(long double value) noexcept
{
        return si::newton{static_cast<double>(value});
}

constexpr si::kilonewton operator"" _kN(long double value) noexcept
{
        return si::kilonewton{static_cast<double>(value});
}

constexpr si::meganewton operator"" _MN(long double value) noexcept
{
        return si::meganewton{static_cast<double>(value});
}

constexpr si::millinewton operator"" _mN(long double value) noexcept
{
        return si::millinewton{static_cast<double>(value});
}

constexpr si::micronewton operator"" _uN(long double value) noexcept
{
        return si::micronewton{static_cast<double>(value});
}

constexpr si::nanonewton operator"" _nN(long double value) noexcept
{
        return si::nanonewton{static_cast<double>(value});
}

// Pressure unit literals
constexpr si::pascal operator"" _Pa(long double value) noexcept
{
        return si::pascal{static_cast<double>(value});
}

constexpr si::kilopascal operator"" _kPa(long double value) noexcept
{
        return si::kilopascal{static_cast<double>(value});
}

constexpr si::megapascal operator"" _MPa(long double value) noexcept
{
        return si::megapascal{static_cast<double>(value});
}

constexpr si::hectopascal operator"" _hPa(long double value) noexcept
{
        return si::hectopascal{static_cast<double>(value});
}

constexpr si::bar operator"" _bar(long double value) noexcept
{
        return si::bar{static_cast<double>(value});
}

constexpr si::atmosphere operator"" _atm(long double value) noexcept
{
        return si::atmosphere{static_cast<double>(value});
}

constexpr si::psi operator"" _psi(long double value) noexcept
{
        return si::psi{static_cast<double>(value});
}

// Energy unit literals
constexpr si::joule operator"" _J(long double value) noexcept
{
        return si::joule{static_cast<double>(value});
}

constexpr si::kilojoule operator"" _kJ(long double value) noexcept
{
        return si::kilojoule{static_cast<double>(value});
}

constexpr si::megajoule operator"" _MJ(long double value) noexcept
{
        return si::megajoule{static_cast<double>(value});
}

constexpr si::gigajoule operator"" _GJ(long double value) noexcept
{
        return si::gigajoule{static_cast<double>(value});
}

constexpr si::millijoule operator"" _mJ(long double value) noexcept
{
        return si::millijoule{static_cast<double>(value});
}

constexpr si::microjoule operator"" _uJ(long double value) noexcept
{
        return si::microjoule{static_cast<double>(value});
}

constexpr si::calorie operator"" _cal(long double value) noexcept
{
        return si::calorie{static_cast<double>(value});
}

constexpr si::kilocalorie operator"" _kcal(long double value) noexcept
{
        return si::kilocalorie{static_cast<double>(value});
}

constexpr si::watthour operator"" _Wh(long double value) noexcept
{
        return si::watthour{static_cast<double>(value});
}

constexpr si::kilowatthour operator"" _kWh(long double value) noexcept
{
        return si::kilowatthour{static_cast<double>(value});
}

constexpr si::electronvolt operator"" _eV(long double value) noexcept
{
        return si::electronvolt{static_cast<double>(value});
}

constexpr si::kiloelectronvolt operator"" _keV(long double value) noexcept
{
        return si::kiloelectronvolt{static_cast<double>(value});
}

constexpr si::megaelectronvolt operator"" _MeV(long double value) noexcept
{
        return si::megaelectronvolt{static_cast<double>(value});
}

constexpr si::gigaelectronvolt operator"" _GeV(long double value) noexcept
{
        return si::gigaelectronvolt{static_cast<double>(value});
}

// Power unit literals
constexpr si::watt operator"" _W(long double value) noexcept
{
        return si::watt{static_cast<double>(value});
}

constexpr si::kilowatt operator"" _kW(long double value) noexcept
{
        return si::kilowatt{static_cast<double>(value});
}

constexpr si::megawatt operator"" _MW(long double value) noexcept
{
        return si::megawatt{static_cast<double>(value});
}

constexpr si::gigawatt operator"" _GW(long double value) noexcept
{
        return si::gigawatt{static_cast<double>(value});
}

constexpr si::milliwatt operator"" _mW(long double value) noexcept
{
        return si::milliwatt{static_cast<double>(value});
}

constexpr si::microwatt operator"" _uW(long double value) noexcept
{
        return si::microwatt{static_cast<double>(value});
}

constexpr si::nanowatt operator"" _nW(long double value) noexcept
{
        return si::nanowatt{static_cast<double>(value});
}

constexpr si::horsepower operator"" _hp(long double value) noexcept
{
        return si::horsepower{static_cast<double>(value});
}

} // namespace si::si_literals
