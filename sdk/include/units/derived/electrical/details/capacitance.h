// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Capacitance dimension
inline constexpr dimension_t capacitance_v{-2, -1, 4, 2, 0, 0, 0};

// Capacitance units (Farad and derived)
// Base unit: Farad (F) = kg⁻¹·m⁻²·s⁴·A²
using farad = unit_t<double, std::ratio<1, 1>, capacitance_v>;
using millifarad = unit_t<double, std::ratio<1, 1000>, capacitance_v>;
using microfarad = unit_t<double, std::ratio<1, 1000000>, capacitance_v>;
using nanofarad = unit_t<double, std::ratio<1, 1000000000>, capacitance_v>;
using picofarad = unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>;

} // namespace si
