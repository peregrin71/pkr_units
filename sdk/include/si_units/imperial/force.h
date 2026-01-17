#pragma once

#include <si_units/impl/details/si_unit.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Imperial force units
using poundal = unit_t<double, std::ratio<45359237, 1000000000>, force_dimension>;  // 1 pdl = 0.138255 N
using pound_force = unit_t<double, std::ratio<4448222, 1000000>, force_dimension>;  // 1 lbf ≈ 4.448 N

} // PKR_SI_NAMESPACE


