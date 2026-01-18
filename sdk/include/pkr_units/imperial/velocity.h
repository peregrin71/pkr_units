#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../namespace_config.h"
#include "../impl/common/velocity_def.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Imperial and nautical velocity units
using miles_per_hour = unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>;
using knots = unit_t<double, std::ratio<1852, 3600>, velocity_dimension>;
using feet_per_second = unit_t<double, std::ratio<3048, 10000>, velocity_dimension>;

} // PKR_UNITS_NAMESPACE


