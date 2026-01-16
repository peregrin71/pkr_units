// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>

namespace si
{

// Electric resistance dimension
inline constexpr dimension_t electric_resistance_dimension{2, 1, -3, -2, 0, 0, 0};

// Electric resistance units (Ohm and derived)
// Base unit: Ohm (Ω) = kg·m²·s⁻³·A⁻²
using ohm = unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>;
using kilohm = unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>;
using megohm = unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>;
using gigohm = unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>;
using milliohm = unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>;
using microohm = unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>;

} // namespace si


