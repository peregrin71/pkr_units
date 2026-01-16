// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
    // Time unit type aliases
    // SI base unit
    using seconds = unit_t<double, std::ratio<1>, time_dimension>;
    
    // Metric prefixes
    using milliseconds = unit_t<double, std::milli, time_dimension>;
    using microseconds = unit_t<double, std::micro, time_dimension>;
    using nanoseconds = unit_t<double, std::nano, time_dimension>;
    using picoseconds = unit_t<double, std::pico, time_dimension>;
    
    // Common units
    using minutes = unit_t<double, std::ratio<60>, time_dimension>;
    using hours = unit_t<double, std::ratio<3600>, time_dimension>;
    using days = unit_t<double, std::ratio<86400>, time_dimension>;
    using weeks = unit_t<double, std::ratio<604800>, time_dimension>;

    // Template alias for generic time quantity
    template<typename type_t, typename ratio_t>
    using time = unit_t<type_t, ratio_t, time_dimension>;

} // namespace si






