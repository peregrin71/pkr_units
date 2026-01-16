// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
    // Time unit type aliases
    // SI base unit
    using seconds = unit_t<double, std::ratio<1>, time_v>;
    
    // Metric prefixes
    using milliseconds = unit_t<double, std::milli, time_v>;
    using microseconds = unit_t<double, std::micro, time_v>;
    using nanoseconds = unit_t<double, std::nano, time_v>;
    using picoseconds = unit_t<double, std::pico, time_v>;
    
    // Common units
    using minutes = unit_t<double, std::ratio<60>, time_v>;
    using hours = unit_t<double, std::ratio<3600>, time_v>;
    using days = unit_t<double, std::ratio<86400>, time_v>;
    using weeks = unit_t<double, std::ratio<604800>, time_v>;

    // Template alias for generic time quantity
    template<typename type_t, typename ratio_t>
    using time = unit_t<type_t, ratio_t, time_v>;

} // namespace si






