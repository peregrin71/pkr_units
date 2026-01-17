// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Force dimension
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0};

// Force units (Newton and derived)
// Base unit: Newton (N) = kg·m·s⁻²
using newton = unit_t<double, std::ratio<1, 1>, force_dimension>;
using kilonewton = unit_t<double, std::ratio<1000, 1>, force_dimension>;
using meganewton = unit_t<double, std::ratio<1000000, 1>, force_dimension>;
using micronewton = unit_t<double, std::ratio<1, 1000000>, force_dimension>;
using millinewton = unit_t<double, std::ratio<1, 1000>, force_dimension>;
using nanonewton = unit_t<double, std::ratio<1, 1000000000>, force_dimension>;

} // PKR_SI_NAMESPACE


