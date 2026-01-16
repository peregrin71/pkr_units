// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>

namespace si
{

// Inductance dimension
inline constexpr dimension_t inductance_dimension{2, 1, -2, -2, 0, 0, 0};

// Inductance units (Henry and derived)
// Base unit: Henry (H) = kg·m²·s⁻²·A⁻²
using henry = unit_t<double, std::ratio<1, 1>, inductance_dimension>;
using millihenry = unit_t<double, std::ratio<1, 1000>, inductance_dimension>;
using microhenry = unit_t<double, std::ratio<1, 1000000>, inductance_dimension>;
using nanohenry = unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>;

} // namespace si


