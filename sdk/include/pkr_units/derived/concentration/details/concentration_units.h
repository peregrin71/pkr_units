#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../../../../impl/common/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Mass concentration dimension: kg·m⁻³
inline constexpr dimension_t mass_concentration_v{.mass = 1, .length = -3};

// Molar concentration dimension: mol·m⁻³
inline constexpr dimension_t molar_concentration_v{.amount = 1, .length = -3};

} // PKR_UNITS_NAMESPACE


