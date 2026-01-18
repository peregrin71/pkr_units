#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../namespace_config.h"
#include "../impl/common/acceleration_def.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Imperial acceleration units
using feet_per_second_squared = unit_t<double, std::ratio<3048, 10000>, acceleration_v>;

} // PKR_UNITS_NAMESPACE


