// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Imperial and nautical velocity units
using miles_per_hour = unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>;
using knots = unit_t<double, std::ratio<1852, 3600>, velocity_dimension>;
using feet_per_second = unit_t<double, std::ratio<3048, 10000>, velocity_dimension>;

} // PKR_SI_NAMESPACE


