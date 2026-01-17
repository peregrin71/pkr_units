#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Velocity dimension
inline constexpr dimension_t velocity_dimension{1, 0, -1, 0, 0, 0, 0};

// Velocity quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using velocity = unit_t<type_t, ratio_t, velocity_dimension>;

// SI base: meters per second (m/s)
using meters_per_second = unit_t<double, std::ratio<1, 1>, velocity_dimension>;

// Metric: kilometers per hour
// 1 km/h = 1000 m / 3600 s = ratio<1000, 3600> = ratio<5, 18> m/s
using kilometers_per_hour = unit_t<double, std::ratio<5, 18>, velocity_dimension>;

// Metric centimeters per second
using centimeters_per_second = unit_t<double, std::ratio<1, 100>, velocity_dimension>;

} // PKR_SI_NAMESPACE


