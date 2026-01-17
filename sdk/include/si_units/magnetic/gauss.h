#pragma once

#include <si_units/impl/details/si_unit.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// CGS (Gaussian) magnetic units
// Gauss (CGS unit for magnetic flux density)
// 1 Gauss = 10⁻⁴ Tesla
using gauss = unit_t<double, std::ratio<1, 10000>, magnetic_flux_density_dimension>;

} // PKR_SI_NAMESPACE


