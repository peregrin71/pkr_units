// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>

namespace si
{

// Imperial and nautical velocity units
using miles_per_hour = unit_t<double, std::ratio<1609344, 3600000>, velocity_v>;
using knots = unit_t<double, std::ratio<1852, 3600>, velocity_v>;
using feet_per_second = unit_t<double, std::ratio<3048, 10000>, velocity_v>;

} // namespace si
