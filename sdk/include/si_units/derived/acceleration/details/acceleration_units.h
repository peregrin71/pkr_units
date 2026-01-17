// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Acceleration dimension
inline constexpr dimension_t acceleration_v{1, 0, -2, 0, 0, 0, 0};

// Acceleration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using acceleration = unit_t<type_t, ratio_t, acceleration_v>;

// SI base: meters per second squared (m/s²)
using meters_per_second_squared = unit_t<double, std::ratio<1, 1>, acceleration_v>;

// Standard gravity (g)
// 1 g = 9.80665 m/s² (exact definition)
// Simplified ratio: ratio<980665, 100000> for practical use
using standard_gravity = unit_t<double, std::ratio<980665, 100000>, acceleration_v>;

// Metric: centimeters per second squared
using centimeters_per_second_squared = unit_t<double, std::ratio<1, 100>, acceleration_v>;

// Metric: millimeters per second squared
using millimeters_per_second_squared = unit_t<double, std::ratio<1, 1000>, acceleration_v>;

} // PKR_SI_NAMESPACE


