// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>

namespace si
{

// Astronomical units
using micron = unit_t<double, std::micro, length_dimension>;                   // 1 micron = 1 micrometer
using angstrom = unit_t<double, std::ratio<1, 10000000000>, length_dimension>; // 1 angstrom = 0.0000000001 meter
using au = unit_t<double, std::ratio<149597870700, 1>, length_dimension>;             // 1 AU = 149,597,870,700 meter (exact)
using light_year = unit_t<double, std::ratio<94607304725808000, 1>, length_dimension>; // 1 light-year ≈ 9.4607 × 10^15 meter
using parsec = unit_t<double, std::ratio<30856775814913673, 1>, length_dimension>;     // 1 parsec ≈ 3.0857 × 10^16 meter

} // namespace si


