// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Energy dimension
inline constexpr dimension_t energy_dimension{2, 1, -2, 0, 0, 0, 0};

// Energy units (Joule and derived)
// Base unit: Joule (J) = kg·m²·s⁻²
using joule = unit_t<double, std::ratio<1, 1>, energy_dimension>;
using kilojoule = unit_t<double, std::ratio<1000, 1>, energy_dimension>;
using megajoule = unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
using gigajoule = unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
using millijoule = unit_t<double, std::ratio<1, 1000>, energy_dimension>;
using microjoule = unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
using calorie = unit_t<double, std::ratio<4184, 1000>, energy_dimension>;
using kilocalorie = unit_t<double, std::ratio<4184, 1>, energy_dimension>;
using watthour = unit_t<double, std::ratio<3600, 1>, energy_dimension>;
using kilowatthour = unit_t<double, std::ratio<3600000, 1>, energy_dimension>;
using electronvolt = unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>;
using kiloelectronvolt = unit_t<double, std::ratio<80108000, 500000000000000000LL>, energy_dimension>;
using megaelectronvolt = unit_t<double, std::ratio<80108000000, 500000000000000000LL>, energy_dimension>;
using gigaelectronvolt = unit_t<double, std::ratio<80108000000000LL, 500000000000000000LL>, energy_dimension>;

} // namespace si
