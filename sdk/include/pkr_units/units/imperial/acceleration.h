#pragma once

#include <pkr_units/impl/unit_impl.h>
#include "../namespace_config.h"
#include "../../impl/decls/acceleration_decl.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Imperial acceleration units
using feet_per_second_squared = unit_t<double, std::ratio<3048, 10000>, acceleration_v>;

} // PKR_UNITS_NAMESPACE








