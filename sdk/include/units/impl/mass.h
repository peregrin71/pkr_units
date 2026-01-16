// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
// Mass quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass = unit_t<type_t, ratio_t, mass_v>;

using kilogram = unit_t<double, std::ratio<1, 1>, mass_v>;
using gram = unit_t<double, std::ratio<1, 1000>, mass_v>; // 1 gram = 0.001 kilogram

// Metric mass prefixes (applied to gram units)
using attogram = unit_t<double, std::ratio<1, 1000000000000000000>, mass_v>;
using femtogram = unit_t<double, std::ratio<1, 1000000000000000>, mass_v>;
using picogram = unit_t<double, std::ratio<1, 1000000000000>, mass_v>;
using nanogram = unit_t<double, std::ratio<1, 1000000000>, mass_v>;
using microgram = unit_t<double, std::ratio<1, 1000000>, mass_v>;
using milligram = unit_t<double, std::ratio<1, 1000000>, mass_v>;
using centigram = unit_t<double, std::ratio<1, 100000>, mass_v>;
using decigram = unit_t<double, std::ratio<1, 10000>, mass_v>;
using decagram = unit_t<double, std::ratio<1, 100>, mass_v>;
using hectogram = unit_t<double, std::ratio<1, 10>, mass_v>;
using megagram = unit_t<double, std::ratio<1000, 1>, mass_v>;
using gigagram = unit_t<double, std::ratio<1000000, 1>, mass_v>;
using teragram = unit_t<double, std::ratio<1000000000, 1>, mass_v>;
using petagram = unit_t<double, std::ratio<1000000000000, 1>, mass_v>;
using exagram = unit_t<double, std::ratio<1000000000000000, 1>, mass_v>;

// Common metric mass units
using metric_ton = unit_t<double, std::mega, mass_v>;      // 1 metric ton = 1,000 kg

} // namespace si






