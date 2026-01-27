#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Magnetic flux dimension: kg·m²·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_dimension{2, 1, -2, -1, 0, 0, 0, 0};

// Magnetic flux density dimension: kg·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_density_dimension{0, 1, -2, -1, 0, 0, 0, 0};

} // namespace PKR_UNITS_NAMESPACE
