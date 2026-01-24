#pragma once

#include <pkr_units/units/base/length.h>
#include <pkr_units/units/imperial/length.h>
#include <pkr_units/units/astronomical/length.h>
#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

namespace si_literals
{
    // Metric length prefix literals
    constexpr attometer_t operator"" _am(long double value) noexcept
    {
        return attometer_t{static_cast<double>(value)};
    }

    constexpr femtometer_t operator"" _fm(long double value) noexcept
    {
        return femtometer_t{static_cast<double>(value)};
    }

    constexpr picometer_t operator"" _pm(long double value) noexcept
    {
        return picometer_t{static_cast<double>(value)};
    }

    constexpr nanometer_t operator"" _nm(long double value) noexcept
    {
        return nanometer_t{static_cast<double>(value)};
    }

    constexpr micrometer_t operator"" _um(long double value) noexcept
    {
        return micrometer_t{static_cast<double>(value)};
    }

    constexpr millimeter_t operator"" _mm(long double value) noexcept
    {
        return millimeter_t{static_cast<double>(value)};
    }

    constexpr centimeter_t operator"" _cm(long double value) noexcept
    {
        return centimeter_t{static_cast<double>(value)};
    }

    constexpr decimeter_t operator"" _dm(long double value) noexcept
    {
        return decimeter_t{static_cast<double>(value)};
    }

    constexpr meter_t operator"" _m(long double value) noexcept
    {
        return meter_t{static_cast<double>(value)};
    }

    constexpr kilometer_t operator"" _km(long double value) noexcept
    {
        return kilometer_t{static_cast<double>(value)};
    }

    constexpr megameter_t operator"" _Mm(long double value) noexcept
    {
        return megameter_t{static_cast<double>(value)};
    }

    constexpr gigameter_t operator"" _Gm(long double value) noexcept
    {
        return gigameter_t{static_cast<double>(value)};
    }

    constexpr terameter_t operator"" _Tm(long double value) noexcept
    {
        return terameter_t{static_cast<double>(value)};
    }

    constexpr petameter_t operator"" _Pm(long double value) noexcept
    {
        return petameter_t{static_cast<double>(value)};
    }

    constexpr exameter_t operator"" _Em(long double value) noexcept
    {
        return exameter_t{static_cast<double>(value)};
    }

    // Imperial length literals
    constexpr inch_t operator"" _in(long double value) noexcept
    {
        return inch_t{static_cast<double>(value)};
    }

    constexpr foot_t operator"" _ft(long double value) noexcept
    {
        return foot_t{static_cast<double>(value)};
    }

    constexpr yard_t operator"" _yd(long double value) noexcept
    {
        return yard_t{static_cast<double>(value)};
    }

    constexpr mile_t operator"" _mi(long double value) noexcept
    {
        return mile_t{static_cast<double>(value)};
    }

    constexpr nautical_mile_t operator"" _nmi(long double value) noexcept
    {
        return nautical_mile_t{static_cast<double>(value)};
    }

    // Astronomical length literals
    constexpr angstrom_t operator"" _angstrom(long double value) noexcept
    {
        return angstrom_t{static_cast<double>(value)};
    }

    constexpr au_t operator"" _au(long double value) noexcept
    {
        return au_t{static_cast<double>(value)};
    }

    constexpr light_year_t operator"" _ly(long double value) noexcept
    {
        return light_year_t{static_cast<double>(value)};
    }

    constexpr parsec_t operator"" _pc(long double value) noexcept
    {
        return parsec_t{static_cast<double>(value)};
    }

} // namespace si_literals

} // PKR_UNITS_NAMESPACE

















