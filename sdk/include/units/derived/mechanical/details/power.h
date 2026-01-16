// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Power dimension
inline constexpr dimension_t power_dimension{2, 1, -3, 0, 0, 0, 0};

// Power units (Watt and derived)
// Base unit: Watt (W) = kg·m²·s⁻³
using watt = unit_t<double, std::ratio<1, 1>, power_dimension>;
using kilowatt = unit_t<double, std::ratio<1000, 1>, power_dimension>;
using megawatt = unit_t<double, std::ratio<1000000, 1>, power_dimension>;
using gigawatt = unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
using milliwatt = unit_t<double, std::ratio<1, 1000>, power_dimension>;
using microwatt = unit_t<double, std::ratio<1, 1000000>, power_dimension>;
using nanowatt = unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
using horsepower = unit_t<double, std::ratio<745700, 1000>, power_dimension>;

} // namespace si
