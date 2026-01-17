// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <chrono>
#include <si_units/impl/details/si_unit.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Convert from std::chrono::duration to si_unit with time dimension
template<typename rep, typename period>
constexpr unit_t<rep, period, time_v> from_chrono(const std::chrono::duration<rep, period>& duration) noexcept
{
    return unit_t<rep, period, time_v>(duration.count());
}

// Convert from si_unit with time dimension to std::chrono::duration
template<typename type_t, typename ratio_t>
    requires (ratio_t::num >= 0) && (ratio_t::den >= 0)
constexpr std::chrono::duration<type_t, ratio_t> to_chrono(const unit_t<type_t, ratio_t, time_v>& time_unit) noexcept
{
    return std::chrono::duration<type_t, ratio_t>(time_unit.value());
}

/*
    constexpr si_unit<long long, std::ratio<1>, time_v> operator"" _s_si(long long seconds) noexcept
    {
        return si_unit<long long, std::ratio<1>, time_v>(seconds);
    }

    constexpr si_unit<long long, std::milli, time_v> operator"" _ms_si(long long milliseconds) noexcept
    {
        return si_unit<long long, std::milli, time_v>(milliseconds);
    }

    constexpr si_unit<long long, std::micro, time_v> operator"" _us_si(long long microseconds) noexcept
    {
        return si_unit<long long, std::micro, time_v>(microseconds);
    }

    constexpr si_unit<long long, std::nano, time_v> operator"" _ns_si(long long nanoseconds) noexcept
    {
        return si_unit<long long, std::nano, time_v>(nanoseconds);
    }

    constexpr si_unit<long long, std::ratio<60>, time_v> operator"" _min_si(long long minutes) noexcept
    {
        return si_unit<long long, std::ratio<60>, time_v>(minutes);
    }

    constexpr si_unit<long long, std::ratio<3600>, time_v> operator"" _h_si(long long hours) noexcept
    {
        return si_unit<long long, std::ratio<3600>, time_v>(hours);
    }
*/

} // namespace details

} // PKR_SI_NAMESPACE








