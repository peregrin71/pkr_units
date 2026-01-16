// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>

namespace si
{

// CGS (Gaussian) magnetic units
// Gauss (CGS unit for magnetic flux density)
// 1 Gauss = 10⁻⁴ Tesla
using gauss = unit_t<double, std::ratio<1, 10000>, magnetic_flux_density_dimension>;

} // namespace si


