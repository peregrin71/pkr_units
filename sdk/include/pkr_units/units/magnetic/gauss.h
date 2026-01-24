#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// CGS (Gaussian) magnetic units
// Gauss (CGS unit for magnetic flux density)
// 1 Gauss = 10⁻⁴ Tesla
using gauss = details::unit_t<double, std::ratio<1, 10000>, magnetic_flux_density_dimension>;

} // PKR_UNITS_NAMESPACE








