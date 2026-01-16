// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>

namespace si
{

// Imperial and other non-SI length units
using inch = unit_t<double, std::ratio<254, 10000>, length_v>;         // 1 inch = 0.0254 meter
using mil = unit_t<double, std::ratio<254, 10000000>, length_v>;       // 1 mil = 0.0000254 meter
using foot = unit_t<double, std::ratio<3048, 10000>, length_v>;        // 1 foot = 0.3048 meter
using yard = unit_t<double, std::ratio<9144, 10000>, length_v>;        // 1 yard = 0.9144 meter
using fathom = unit_t<double, std::ratio<18288, 10000>, length_v>;     // 1 fathom = 1.8288 meter
using rod = unit_t<double, std::ratio<50292, 10000>, length_v>;        // 1 rod = 5.0292 meter
using chain = unit_t<double, std::ratio<201168, 10000>, length_v>;     // 1 chain = 20.1168 meter
using furlong = unit_t<double, std::ratio<201168, 1000>, length_v>;    // 1 furlong = 201.168 meter
using mile = unit_t<double, std::ratio<1609344, 1000>, length_v>;      // 1 mile = 1609.344 meter
using nautical_mile = unit_t<double, std::ratio<1852, 1>, length_v>;   // 1 nautical mile = 1852 meter
using micron = unit_t<double, std::micro, length_v>;                   // 1 micron = 1 micrometer
using angstrom = unit_t<double, std::ratio<1, 10000000000>, length_v>; // 1 angstrom = 0.0000000001 meter

// Astronomical units
using au = unit_t<double, std::ratio<149597870700, 1>, length_v>;             // 1 AU = 149,597,870,700 meter (exact)
using light_year = unit_t<double, std::ratio<94607304725808000, 1>, length_v>; // 1 light-year ≈ 9.4607 × 10^15 meter
using parsec = unit_t<double, std::ratio<30856775814913673, 1>, length_v>;     // 1 parsec ≈ 3.0857 × 10^16 meter

} // namespace si
