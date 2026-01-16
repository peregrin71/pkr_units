// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Density dimension: kg·m⁻³
inline constexpr dimension_t density_v{.mass = 1, .length = -3};

} // namespace si
