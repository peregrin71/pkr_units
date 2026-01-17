#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/velocity/details/velocity_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Velocity units (length per time)
// Base unit: meter per second (m/s)

// SI metric velocity units
using meter_per_second = unit_t<double, std::ratio<1, 1>, velocity_dimension>;
using kilometer_per_hour = unit_t<double, std::ratio<5, 18>, velocity_dimension>;  // 1 km/h = 5/18 m/s
using centimeter_per_second = unit_t<double, std::ratio<1, 100>, velocity_dimension>;
using millimeter_per_second = unit_t<double, std::ratio<1, 1000>, velocity_dimension>;
using kilometer_per_second = unit_t<double, std::ratio<1000, 1>, velocity_dimension>;

// Imperial velocity units
using miles_per_hour = unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>;  // 1 mph ≈ 0.44704 m/s
using feet_per_second = unit_t<double, std::ratio<3048, 10000>, velocity_dimension>;  // 1 ft/s = 0.3048 m/s
using inches_per_second = unit_t<double, std::ratio<254, 10000>, velocity_dimension>;  // 1 in/s = 0.0254 m/s

// Maritime velocity units
using knots = unit_t<double, std::ratio<1852, 3600>, velocity_dimension>;  // 1 knot = 1852/3600 m/s

} // PKR_SI_NAMESPACE








