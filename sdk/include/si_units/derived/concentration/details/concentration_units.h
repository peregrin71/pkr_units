// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>

namespace si
{

// Mass concentration dimension: kg·m⁻³
inline constexpr dimension_t mass_concentration_v{.mass = 1, .length = -3};

// Molar concentration dimension: mol·m⁻³
inline constexpr dimension_t molar_concentration_v{.amount = 1, .length = -3};

} // namespace si


