// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Pressure dimension
inline constexpr dimension_t pressure_v{-1, 1, -2, 0, 0, 0, 0};

// Pressure units (Pascal and derived)
// Base unit: Pascal (Pa) = kg·m⁻¹·s⁻²
using pascal = unit_t<double, std::ratio<1, 1>, pressure_v>;
using hectopascal = unit_t<double, std::ratio<100, 1>, pressure_v>;
using kilopascal = unit_t<double, std::ratio<1000, 1>, pressure_v>;
using megapascal = unit_t<double, std::ratio<1000000, 1>, pressure_v>;
using micropascal = unit_t<double, std::ratio<1, 1000000>, pressure_v>;
using millibar = unit_t<double, std::ratio<100, 1>, pressure_v>;
using bar = unit_t<double, std::ratio<100000, 1>, pressure_v>;
using atmosphere = unit_t<double, std::ratio<101325, 1>, pressure_v>;
using psi = unit_t<double, std::ratio<6894757293, 1000000000>, pressure_v>;

} // namespace si
