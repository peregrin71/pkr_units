// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
// Mass quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass = unit_t<type_t, ratio_t, mass_dimension>;

using kilogram = unit_t<double, std::ratio<1, 1>, mass_dimension>;
using gram = unit_t<double, std::ratio<1, 1000>, mass_dimension>; // 1 gram = 0.001 kilogram

// Metric mass prefixes (applied to gram units)
using attogram = unit_t<double, std::ratio<1, 1000000000000000000>, mass_dimension>;
using femtogram = unit_t<double, std::ratio<1, 1000000000000000>, mass_dimension>;
using picogram = unit_t<double, std::ratio<1, 1000000000000>, mass_dimension>;
using nanogram = unit_t<double, std::ratio<1, 1000000000>, mass_dimension>;
using microgram = unit_t<double, std::ratio<1, 1000000>, mass_dimension>;
using milligram = unit_t<double, std::ratio<1, 1000000>, mass_dimension>;
using centigram = unit_t<double, std::ratio<1, 100000>, mass_dimension>;
using decigram = unit_t<double, std::ratio<1, 10000>, mass_dimension>;
using decagram = unit_t<double, std::ratio<1, 100>, mass_dimension>;
using hectogram = unit_t<double, std::ratio<1, 10>, mass_dimension>;
using megagram = unit_t<double, std::ratio<1000, 1>, mass_dimension>;
using gigagram = unit_t<double, std::ratio<1000000, 1>, mass_dimension>;
using teragram = unit_t<double, std::ratio<1000000000, 1>, mass_dimension>;
using petagram = unit_t<double, std::ratio<1000000000000, 1>, mass_dimension>;
using exagram = unit_t<double, std::ratio<1000000000000000, 1>, mass_dimension>;

// Common metric mass units
using metric_ton = unit_t<double, std::mega, mass_dimension>;      // 1 metric ton = 1,000 kg

} // namespace si






