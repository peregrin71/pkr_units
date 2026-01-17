#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Pressure dimension
inline constexpr dimension_t pressure_dimension{-1, 1, -2, 0, 0, 0, 0};

// Pressure units (Pascal and derived)
// Base unit: Pascal (Pa) = kg·m⁻¹·s⁻²
using pascal = unit_t<double, std::ratio<1, 1>, pressure_dimension>;
using hectopascal = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
using kilopascal = unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
using megapascal = unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
using micropascal = unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
using millibar = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
using bar = unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
using atmosphere = unit_t<double, std::ratio<101325, 1>, pressure_dimension>;
using psi = unit_t<double, std::ratio<6894757293, 1000000000>, pressure_dimension>;

} // PKR_SI_NAMESPACE


