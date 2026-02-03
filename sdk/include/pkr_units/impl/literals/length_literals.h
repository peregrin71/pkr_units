#pragma once

#include <pkr_units/units/base/length.h>
#include <pkr_units/units/astronomical/length.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric length prefix literals
constexpr attometer_t<double> operator""_am(long double value) noexcept
{
    return attometer_t<double>{static_cast<double>(value)};
} 

constexpr femtometer_t<double> operator""_fm(long double value) noexcept
{
    return femtometer_t<double>{static_cast<double>(value)};
} 

constexpr picometer_t<double> operator""_pm(long double value) noexcept
{
    return picometer_t<double>{static_cast<double>(value)};
} 

constexpr nanometer_t<double> operator""_nm(long double value) noexcept
{
    return nanometer_t<double>{static_cast<double>(value)};
} 

constexpr micrometer_t<double> operator""_um(long double value) noexcept
{
    return micrometer_t<double>{static_cast<double>(value)};
} 

constexpr millimeter_t<double> operator""_mm(long double value) noexcept
{
    return millimeter_t<double>{static_cast<double>(value)};
} 

constexpr centimeter_t<double> operator""_cm(long double value) noexcept
{
    return centimeter_t<double>{static_cast<double>(value)};
} 

constexpr decimeter_t<double> operator""_dm(long double value) noexcept
{
    return decimeter_t<double>{static_cast<double>(value)};
} 

constexpr meter_t<double> operator""_m(long double value) noexcept
{
    return meter_t<double>{static_cast<double>(value)};
} 

constexpr kilometer_t<double> operator""_km(long double value) noexcept
{
    return kilometer_t<double>{static_cast<double>(value)};
} 

constexpr megameter_t<double> operator""_Mm(long double value) noexcept
{
    return megameter_t<double>{static_cast<double>(value)};
} 

constexpr gigameter_t<double> operator""_Gm(long double value) noexcept
{
    return gigameter_t<double>{static_cast<double>(value)};
} 

constexpr terameter_t<double> operator""_Tm(long double value) noexcept
{
    return terameter_t<double>{static_cast<double>(value)};
} 

constexpr petameter_t<double> operator""_Pm(long double value) noexcept
{
    return petameter_t<double>{static_cast<double>(value)};
} 

constexpr exameter_t<double> operator""_Em(long double value) noexcept
{
    return exameter_t<double>{static_cast<double>(value)};
} 

// Astronomical length literals
constexpr angstrom_t<double> operator""_angstrom(long double value) noexcept
{
    return angstrom_t<double>{static_cast<double>(value)};
}

constexpr au_t<double> operator""_au(long double value) noexcept
{
    return au_t<double>{static_cast<double>(value)};
}

constexpr light_year_t<double> operator""_ly(long double value) noexcept
{
    return light_year_t<double>{static_cast<double>(value)};
}

constexpr parsec_t<double> operator""_pc(long double value) noexcept
{
    return parsec_t<double>{static_cast<double>(value)};
}  

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
