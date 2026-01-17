#pragma once

#include <si_units/impl/details/si_unit.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Imperial acceleration units
using feet_per_second_squared = unit_t<double, std::ratio<3048, 10000>, acceleration_v>;

} // PKR_SI_NAMESPACE


