// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
// Length quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length = unit_t<type_t, ratio_t, length_dimension>;

using meter = unit_t<double, std::ratio<1, 1>, length_dimension>;

// Metric length prefixes
using attometer = unit_t<double, std::atto, length_dimension>;
using femtometer = unit_t<double, std::femto, length_dimension>;
using picometer = unit_t<double, std::pico, length_dimension>;
using nanometer = unit_t<double, std::nano, length_dimension>;
using micrometer = unit_t<double, std::micro, length_dimension>;
using millimeter = unit_t<double, std::milli, length_dimension>;
using centimeter = unit_t<double, std::centi, length_dimension>;
using decimeter = unit_t<double, std::deci, length_dimension>;
using decameter = unit_t<double, std::deca, length_dimension>;
using hectometer = unit_t<double, std::hecto, length_dimension>;
using kilometer = unit_t<double, std::kilo, length_dimension>;
using megameter = unit_t<double, std::mega, length_dimension>;
using gigameter = unit_t<double, std::giga, length_dimension>;
using terameter = unit_t<double, std::tera, length_dimension>;
using petameter = unit_t<double, std::peta, length_dimension>;
using exameter = unit_t<double, std::exa, length_dimension>;

} // namespace si






