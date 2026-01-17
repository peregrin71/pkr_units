// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>

PKR_SI_BEGIN_NAMESPACE
{
// Forward declare or include the detail constants
#include <si_units/derived/magnetic_flux/details/magnetic_flux_units.h>
#include "../namespace_config.h"
// Magnetic flux units (Weber and derived)
// Base unit: Weber (Wb) = kg·m²·s⁻²·A⁻¹
using weber = unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>;
using milliweber = unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>;
using microweber = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>;
using nanoweber = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>;
using kiloweber = unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>;

// Magnetic flux density units (Tesla and derived)
// Base unit: Tesla (T) = kg·s⁻²·A⁻¹
using tesla = unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>;
using millitesla = unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>;
using microtesla = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>;
using nanotesla = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>;
using kilotesla = unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>;
using megatesla = unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>;

} // PKR_SI_NAMESPACE








