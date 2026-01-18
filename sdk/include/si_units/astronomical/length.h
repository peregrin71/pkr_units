#pragma once

#include "../impl/common/length_def.h"
#include "../impl/namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Astronomical units
using micron = details::unit_t<double, std::micro, details::length_dimension>;                   // 1 micron = 1 micrometer
using angstrom = details::unit_t<double, std::ratio<1, 10000000000>, details::length_dimension>; // 1 angstrom = 0.0000000001 meter
using au = details::unit_t<double, std::ratio<149597870700, 1>, details::length_dimension>;             // 1 AU = 149,597,870,700 meter (exact)
using light_year = details::unit_t<double, std::ratio<94607304725808000, 1>, details::length_dimension>; // 1 light-year ≈ 9.4607 × 10^15 meter
using parsec = details::unit_t<double, std::ratio<30856775814913673, 1>, details::length_dimension>;     // 1 parsec ≈ 3.0857 × 10^16 meter

} // PKR_SI_NAMESPACE


