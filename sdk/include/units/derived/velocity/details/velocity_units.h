// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Velocity dimension
inline constexpr dimension_t velocity_v{1, 0, -1, 0, 0, 0, 0};

// Velocity quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using velocity = unit_t<type_t, ratio_t, velocity_v>;

// SI base: meters per second (m/s)
using meters_per_second = unit_t<double, std::ratio<1, 1>, velocity_v>;

// Metric: kilometers per hour
// 1 km/h = 1000 m / 3600 s = ratio<1000, 3600> = ratio<5, 18> m/s
using kilometers_per_hour = unit_t<double, std::ratio<5, 18>, velocity_v>;

// Metric centimeters per second
using centimeters_per_second = unit_t<double, std::ratio<1, 100>, velocity_v>;

} // namespace si
