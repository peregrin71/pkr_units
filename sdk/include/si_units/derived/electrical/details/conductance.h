// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Conductance dimension: S = A²·s³·kg⁻¹·m⁻²
inline constexpr dimension_t conductance_dimension{.length = -2, .mass = -1, .time = 3, .current = 2};

// Conductance units (Siemens and derived)
// Base unit: Siemens (S) = kg⁻¹·m⁻²·s³·A²
using siemens = unit_t<double, std::ratio<1, 1>, conductance_dimension>;
using millisiemens = unit_t<double, std::ratio<1, 1000>, conductance_dimension>;
using microsiemens = unit_t<double, std::ratio<1, 1000000>, conductance_dimension>;

} // PKR_SI_NAMESPACE


