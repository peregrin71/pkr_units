// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>

namespace si
{

// Imperial force units
using poundal = unit_t<double, std::ratio<45359237, 1000000000>, force_dimension>;  // 1 pdl = 0.138255 N
using pound_force = unit_t<double, std::ratio<4448222, 1000000>, force_dimension>;  // 1 lbf ≈ 4.448 N

} // namespace si
