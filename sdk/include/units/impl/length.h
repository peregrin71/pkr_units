// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
// Length quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length = unit_t<type_t, ratio_t, length_v>;

using meter = unit_t<double, std::ratio<1, 1>, length_v>;

// Metric length prefixes
using attometer = unit_t<double, std::atto, length_v>;
using femtometer = unit_t<double, std::femto, length_v>;
using picometer = unit_t<double, std::pico, length_v>;
using nanometer = unit_t<double, std::nano, length_v>;
using micrometer = unit_t<double, std::micro, length_v>;
using millimeter = unit_t<double, std::milli, length_v>;
using centimeter = unit_t<double, std::centi, length_v>;
using decimeter = unit_t<double, std::deci, length_v>;
using decameter = unit_t<double, std::deca, length_v>;
using hectometer = unit_t<double, std::hecto, length_v>;
using kilometer = unit_t<double, std::kilo, length_v>;
using megameter = unit_t<double, std::mega, length_v>;
using gigameter = unit_t<double, std::giga, length_v>;
using terameter = unit_t<double, std::tera, length_v>;
using petameter = unit_t<double, std::peta, length_v>;
using exameter = unit_t<double, std::exa, length_v>;
using light_year = unit_t<double, std::ratio<9460730472580800, 1>, length_v>; // 1 light-year = 9,460,730,472,580,800 meter
using parsec = unit_t<double, std::ratio<30856775814913673, 1>, length_v>;    // 1 parsec ≈ 30,856,775,814,913,673 meter

} // namespace si






