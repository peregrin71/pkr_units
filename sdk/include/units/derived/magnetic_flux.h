// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>

namespace si
{
// Forward declare or include the detail constants
#include <units/derived/magnetic_flux/details/magnetic_flux_units.h>
// Magnetic flux units (Weber and derived)
// Base unit: Weber (Wb) = kg·m²·s⁻²·A⁻¹
using weber = unit_t<double, std::ratio<1, 1>, magnetic_flux_v>;
using milliweber = unit_t<double, std::ratio<1, 1000>, magnetic_flux_v>;
using microweber = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_v>;
using nanoweber = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_v>;
using kiloweber = unit_t<double, std::ratio<1000, 1>, magnetic_flux_v>;

// Magnetic flux density units (Tesla and derived)
// Base unit: Tesla (T) = kg·s⁻²·A⁻¹
using tesla = unit_t<double, std::ratio<1, 1>, magnetic_flux_density_v>;
using millitesla = unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_v>;
using microtesla = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_v>;
using nanotesla = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_v>;
using kilotesla = unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_v>;
using megatesla = unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_v>;

} // namespace si






