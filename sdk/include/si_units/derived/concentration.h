// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/concentration/details/concentration_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
{
// Mass concentration units (mass per volume)
// Base unit: kilogram per cubic meter (kg/m³)
using kilogram_per_cubic_meter = unit_t<double, std::ratio<1, 1>, mass_concentration_v>;
using gram_per_cubic_meter = unit_t<double, std::ratio<1, 1000>, mass_concentration_v>;
using gram_per_liter = unit_t<double, std::ratio<1, 1>, mass_concentration_v>;  // 1 g/L = 1 kg/m³
using milligram_per_liter = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;  // 1 mg/L = 1 g/m³
using milligram_per_cubic_meter = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;
using microgram_per_liter = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;
using microgram_per_cubic_meter = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;

// Parts per million (by mass) - ppm
// 1 ppm = 1 mg/kg ≈ 1 μg/g (for aqueous solutions, approximately 1 μg/mL)
using parts_per_million = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;

// Parts per billion (by mass) - ppb
using parts_per_billion = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;

// Molar concentration units (amount of substance per volume)
// Base unit: mole per cubic meter (mol/m³)
using mole_per_cubic_meter = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
using mole_per_liter = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;  // 1 mol/L = 1000 mol/m³
using molar = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;  // 1 M = 1 mol/L
using millimolar = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;  // 1 mM = 1 mol/m³
using micromolar = unit_t<double, std::ratio<1, 1000>, molar_concentration_v>;
using nanomolar = unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>;
using picomolar = unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>;
using mole_per_cubic_centimeter = unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>;  // 1 mol/cm³ = 10⁹ mol/m³
using mole_per_milliliter = unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>;  // 1 mol/mL = 10⁹ mol/m³

// Osmolarity units (moles of osmotically active particles per liter)
using osmole_per_liter = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;  // 1 osmol/L = 1000 osmol/m³
using milliosmole_per_liter = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;  // 1 mOsmol/L = 1 osmol/m³

} // PKR_SI_NAMESPACE








