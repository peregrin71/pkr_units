#pragma once

#include <pkr_units/units/derived/mechanical/force.h>
#include <pkr_units/units/derived/mechanical/pressure.h>
#include <pkr_units/units/derived/mechanical/energy.h>
#include <pkr_units/units/derived/mechanical/power.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Force unit literals
constexpr newton_t<double> operator""_N(long double value) noexcept
{
    return newton_t<double>{static_cast<double>(value)};
}

constexpr kilonewton_t<double> operator""_kN(long double value) noexcept
{
    return kilonewton_t<double>{static_cast<double>(value)};
}

constexpr meganewton_t<double> operator""_MN(long double value) noexcept
{
    return meganewton_t<double>{static_cast<double>(value)};
}

constexpr millinewton_t<double> operator""_mN(long double value) noexcept
{
    return millinewton_t<double>{static_cast<double>(value)};
}

constexpr micronewton_t<double> operator""_uN(long double value) noexcept
{
    return micronewton_t<double>{static_cast<double>(value)};
}

constexpr nanonewton_t<double> operator""_nN(long double value) noexcept
{
    return nanonewton_t<double>{static_cast<double>(value)};
}

// Pressure unit literals
constexpr pascal_t<double> operator""_Pa(long double value) noexcept
{
    return pascal_t<double>{static_cast<double>(value)};
}

constexpr kilopascal_t<double> operator""_kPa(long double value) noexcept
{
    return kilopascal_t<double>{static_cast<double>(value)};
}

constexpr megapascal_t<double> operator""_MPa(long double value) noexcept
{
    return megapascal_t<double>{static_cast<double>(value)};
}

constexpr hectopascal_t<double> operator""_hPa(long double value) noexcept
{
    return hectopascal_t<double>{static_cast<double>(value)};
}

constexpr bar_t<double> operator""_bar(long double value) noexcept
{
    return bar_t<double>{static_cast<double>(value)};
}

constexpr atmosphere_t<double> operator""_atm(long double value) noexcept
{
    return atmosphere_t<double>{static_cast<double>(value)};
}

// Energy unit literals
constexpr joule_t<double> operator""_J(long double value) noexcept
{
    return joule_t<double>{static_cast<double>(value)};
}

constexpr kilojoule_t<double> operator""_kJ(long double value) noexcept
{
    return kilojoule_t<double>{static_cast<double>(value)};
}

constexpr megajoule_t<double> operator""_MJ(long double value) noexcept
{
    return megajoule_t<double>{static_cast<double>(value)};
}

constexpr gigajoule_t<double> operator""_GJ(long double value) noexcept
{
    return gigajoule_t<double>{static_cast<double>(value)};
}

constexpr millijoule_t<double> operator""_mJ(long double value) noexcept
{
    return millijoule_t<double>{static_cast<double>(value)};
}

constexpr microjoule_t<double> operator""_uJ(long double value) noexcept
{
    return microjoule_t<double>{static_cast<double>(value)};
}

constexpr calorie_t<double> operator""_cal(long double value) noexcept
{
    return calorie_t<double>{static_cast<double>(value)};
}

constexpr kilocalorie_t<double> operator""_kcal(long double value) noexcept
{
    return kilocalorie_t<double>{static_cast<double>(value)};
}

constexpr watt_hour_t<double> operator""_Wh(long double value) noexcept
{
    return watt_hour_t<double>{static_cast<double>(value)};
}

constexpr kilowatt_hour_t<double> operator""_kWh(long double value) noexcept
{
    return kilowatt_hour_t<double>{static_cast<double>(value)};
}

constexpr electronvolt_t<double> operator""_eV(long double value) noexcept
{
    return electronvolt_t<double>{static_cast<double>(value)};
}

constexpr kiloelectronvolt_t<double> operator""_keV(long double value) noexcept
{
    return kiloelectronvolt_t<double>{static_cast<double>(value)};
}

constexpr megaelectronvolt_t<double> operator""_MeV(long double value) noexcept
{
    return megaelectronvolt_t<double>{static_cast<double>(value)};
}

constexpr gigaelectronvolt_t<double> operator""_GeV(long double value) noexcept
{
    return gigaelectronvolt_t<double>{static_cast<double>(value)};
}

// Power unit literals
constexpr watt_t<double> operator""_W(long double value) noexcept
{
    return watt_t<double>{static_cast<double>(value)};
}

constexpr kilowatt_t<double> operator""_kW(long double value) noexcept
{
    return kilowatt_t<double>{static_cast<double>(value)};
}

constexpr megawatt_t<double> operator""_MW(long double value) noexcept
{
    return megawatt_t<double>{static_cast<double>(value)};
}

constexpr gigawatt_t<double> operator""_GW(long double value) noexcept
{
    return gigawatt_t<double>{static_cast<double>(value)};
}

constexpr milliwatt_t<double> operator""_mW(long double value) noexcept
{
    return milliwatt_t<double>{static_cast<double>(value)};
}

constexpr microwatt_t<double> operator""_uW(long double value) noexcept
{
    return microwatt_t<double>{static_cast<double>(value)};
}

constexpr nanowatt_t<double> operator""_nW(long double value) noexcept
{
    return nanowatt_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
