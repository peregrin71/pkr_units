// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Magnetic flux dimension: kg·m²·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_dimension{.mass = 1, .length = 2, .time = -2, .current = -1};

// Magnetic flux density dimension: kg·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_density_dimension{.mass = 1, .time = -2, .current = -1};

} // namespace si
