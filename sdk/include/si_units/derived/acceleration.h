#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/acceleration/details/acceleration_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Acceleration units (length per time squared)
// Base unit: meter per second squared (m/s²)

// SI metric acceleration units
using meter_per_second_squared = unit_t<double, std::ratio<1, 1>, acceleration_v>;
using centimeter_per_second_squared = unit_t<double, std::ratio<1, 100>, acceleration_v>;
using millimeter_per_second_squared = unit_t<double, std::ratio<1, 1000>, acceleration_v>;
using kilometer_per_second_squared = unit_t<double, std::ratio<1000, 1>, acceleration_v>;

// Standard gravity (g)
// 1 g = 9.80665 m/s² (exact definition)
using standard_gravity = unit_t<double, std::ratio<980665, 100000>, acceleration_v>;

// Imperial acceleration units
using feet_per_second_squared = unit_t<double, std::ratio<3048, 10000>, acceleration_v>;  // 1 ft/s² = 0.3048 m/s²
using inches_per_second_squared = unit_t<double, std::ratio<254, 10000>, acceleration_v>;  // 1 in/s² = 0.0254 m/s²

} // PKR_SI_NAMESPACE








