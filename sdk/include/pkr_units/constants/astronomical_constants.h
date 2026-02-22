#pragma once

#include <ratio>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/si_units.h>

namespace PKR_UNITS_NAMESPACE
{

namespace details
{

// Solar mass in kilograms (CODATA-ish / astronomical canon)
template <typename T>
constexpr T solar_mass_kg()
{
    return static_cast<T>(1.989e30);
}

} // namespace details

namespace constants
{

// Public constants
constexpr auto solar_mass_kg = details::solar_mass_kg<double>();

// Convenience unit-typed value
constexpr auto solar_mass = pkr::units::kilogram_t(solar_mass_kg);

// Gravitational constant (G) as a value and typed unit
namespace details
{
template <typename T>
constexpr T gravitational_constant_value()
{
    return static_cast<T>(6.67430e-11);
}
} // namespace details

constexpr auto gravitational_constant_value = details::gravitational_constant_value<double>();

// Gravitational constant dimension and unit typedef: m^3·kg^-1·s^-2
inline constexpr dimension_t gravitational_constant_dimension{3, -1, -2, 0, 0, 0, 0, 0};

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using gravitational_constant_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, gravitational_constant_dimension>;

// Unit-typed gravitational constant (SI)
constexpr auto gravitational_constant = gravitational_constant_unit_t<>{gravitational_constant_value};

} // namespace constants

} // namespace PKR_UNITS_NAMESPACE
