#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Mass concentration dimension: kg·m⁻³
inline constexpr dimension_t mass_concentration_v{.mass = 1, .length = -3};

// Molar concentration dimension: mol·m⁻³
inline constexpr dimension_t molar_concentration_v{.amount = 1, .length = -3};

} // PKR_SI_NAMESPACE


