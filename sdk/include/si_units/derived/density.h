// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/density/details/density_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Density units (mass per volume)
// Base unit: kilogram per cubic meter (kg/m³)
using kilogram_per_cubic_meter = unit_t<double, std::ratio<1, 1>, density_dimension>;
using gram_per_cubic_meter = unit_t<double, std::ratio<1, 1000>, density_dimension>;
using gram_per_cubic_centimeter = unit_t<double, std::ratio<1000000, 1>, density_dimension>;  // 1 g/cm³ = 1000 kg/m³
using gram_per_milliliter = unit_t<double, std::ratio<1000000, 1>, density_dimension>;  // 1 g/mL = 1000 kg/m³
using kilogram_per_liter = unit_t<double, std::ratio<1000, 1>, density_dimension>;  // 1 kg/L = 1000 kg/m³
using gram_per_liter = unit_t<double, std::ratio<1, 1>, density_dimension>;  // 1 g/L = 1 kg/m³
using milligram_per_cubic_centimeter = unit_t<double, std::ratio<1000, 1>, density_dimension>;  // 1 mg/cm³ = 1000 kg/m³
using milligram_per_milliliter = unit_t<double, std::ratio<1000, 1>, density_dimension>;  // 1 mg/mL = 1000 kg/m³

// Imperial density units
using pound_per_cubic_inch = unit_t<double, std::ratio<27679904, 1000000>, density_dimension>;  // 1 lb/in³ ≈ 27679.9 kg/m³
using pound_per_cubic_foot = unit_t<double, std::ratio<16018, 1000000>, density_dimension>;  // 1 lb/ft³ ≈ 16.018 kg/m³
using pound_per_gallon = unit_t<double, std::ratio<119826, 1000000>, density_dimension>;  // 1 lb/gal ≈ 119.826 kg/m³
using ounce_per_cubic_inch = unit_t<double, std::ratio<1729994, 1000000>, density_dimension>;  // 1 oz/in³ ≈ 1729.99 kg/m³
using ounce_per_fluid_ounce = unit_t<double, std::ratio<33814, 1000>, density_dimension>;  // 1 oz/fl oz ≈ 33814 kg/m³

// Other common density units
using ton_per_cubic_meter = unit_t<double, std::ratio<1000000, 1>, density_dimension>;  // 1 t/m³ = 1000 kg/m³
using atomic_mass_unit_per_cubic_angstrom = unit_t<double, std::ratio<166054, 1>, density_dimension>;  // ≈ 166.054 kg/m³

} // PKR_SI_NAMESPACE








