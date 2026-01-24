#pragma once

#include <pkr_units/impl/unit.h>
#include "../../../../../impl/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Density dimension: kg·m⁻³
inline constexpr dimension_t density_dimension{.mass = 1, .length = -3};

} // PKR_UNITS_NAMESPACE








