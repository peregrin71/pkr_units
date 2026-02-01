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
constexpr newton_t operator""_N(long double value) noexcept
{
    return newton_t{static_cast<double>(value)};
}

constexpr kilonewton_t operator""_kN(long double value) noexcept
{
    return kilonewton_t{static_cast<double>(value)};
}

constexpr meganewton_t operator""_MN(long double value) noexcept
{
    return meganewton_t{static_cast<double>(value)};
}

constexpr millinewton_t operator""_mN(long double value) noexcept
{
    return millinewton_t{static_cast<double>(value)};
}

constexpr micronewton_t operator""_uN(long double value) noexcept
{
    return micronewton_t{static_cast<double>(value)};
}

constexpr nanonewton_t operator""_nN(long double value) noexcept
{
    return nanonewton_t{static_cast<double>(value)};
}

// Pressure unit literals
constexpr pascal_t operator""_Pa(long double value) noexcept
{
    return pascal_t{static_cast<double>(value)};
}

constexpr kilopascal_t operator""_kPa(long double value) noexcept
{
    return kilopascal_t{static_cast<double>(value)};
}

constexpr megapascal_t operator""_MPa(long double value) noexcept
{
    return megapascal_t{static_cast<double>(value)};
}

constexpr hectopascal_t operator""_hPa(long double value) noexcept
{
    return hectopascal_t{static_cast<double>(value)};
}

constexpr bar_t operator""_bar(long double value) noexcept
{
    return bar_t{static_cast<double>(value)};
}

constexpr atmosphere_t operator""_atm(long double value) noexcept
{
    return atmosphere_t{static_cast<double>(value)};
}

// Energy unit literals
constexpr joule_t operator""_J(long double value) noexcept
{
    return joule_t{static_cast<double>(value)};
}

constexpr kilojoule_t operator""_kJ(long double value) noexcept
{
    return kilojoule_t{static_cast<double>(value)};
}

constexpr megajoule_t operator""_MJ(long double value) noexcept
{
    return megajoule_t{static_cast<double>(value)};
}

constexpr gigajoule_t operator""_GJ(long double value) noexcept
{
    return gigajoule_t{static_cast<double>(value)};
}

constexpr millijoule_t operator""_mJ(long double value) noexcept
{
    return millijoule_t{static_cast<double>(value)};
}

constexpr microjoule_t operator""_uJ(long double value) noexcept
{
    return microjoule_t{static_cast<double>(value)};
}

constexpr calorie_t operator""_cal(long double value) noexcept
{
    return calorie_t{static_cast<double>(value)};
}

constexpr kilocalorie_t operator""_kcal(long double value) noexcept
{
    return kilocalorie_t{static_cast<double>(value)};
}

constexpr watt_hour_t operator""_Wh(long double value) noexcept
{
    return watt_hour_t{static_cast<double>(value)};
}

constexpr kilowatt_hour_t operator""_kWh(long double value) noexcept
{
    return kilowatt_hour_t{static_cast<double>(value)};
}

constexpr electronvolt_t operator""_eV(long double value) noexcept
{
    return electronvolt_t{static_cast<double>(value)};
}

constexpr kiloelectronvolt_t operator""_keV(long double value) noexcept
{
    return kiloelectronvolt_t{static_cast<double>(value)};
}

constexpr megaelectronvolt_t operator""_MeV(long double value) noexcept
{
    return megaelectronvolt_t{static_cast<double>(value)};
}

constexpr gigaelectronvolt_t operator""_GeV(long double value) noexcept
{
    return gigaelectronvolt_t{static_cast<double>(value)};
}

// Power unit literals
constexpr watt_t operator""_W(long double value) noexcept
{
    return watt_t{static_cast<double>(value)};
}

constexpr kilowatt_t operator""_kW(long double value) noexcept
{
    return kilowatt_t{static_cast<double>(value)};
}

constexpr megawatt_t operator""_MW(long double value) noexcept
{
    return megawatt_t{static_cast<double>(value)};
}

constexpr gigawatt_t operator""_GW(long double value) noexcept
{
    return gigawatt_t{static_cast<double>(value)};
}

constexpr milliwatt_t operator""_mW(long double value) noexcept
{
    return milliwatt_t{static_cast<double>(value)};
}

constexpr microwatt_t operator""_uW(long double value) noexcept
{
    return microwatt_t{static_cast<double>(value)};
}

constexpr nanowatt_t operator""_nW(long double value) noexcept
{
    return nanowatt_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
