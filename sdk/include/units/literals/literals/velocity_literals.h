// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "velocity.h"

namespace si::si_literals
{
    // Velocity unit literals
    constexpr si::meters_per_second operator"" _mps(long double value) noexcept
    {
        return si::meters_per_second(static_cast<double>(value));
    }

    constexpr si::kilometers_per_hour operator"" _kmph(long double value) noexcept
    {
        return si::kilometers_per_hour(static_cast<double>(value));
    }

    constexpr si::miles_per_hour operator"" _mph(long double value) noexcept
    {
        return si::miles_per_hour(static_cast<double>(value));
    }

    constexpr si::knots operator"" _kt(long double value) noexcept
    {
        return si::knots(static_cast<double>(value));
    }

    constexpr si::centimeters_per_second operator"" _cmps(long double value) noexcept
    {
        return si::centimeters_per_second(static_cast<double>(value));
    }

    constexpr si::feet_per_second operator"" _fps(long double value) noexcept
    {
        return si::feet_per_second(static_cast<double>(value));
    }

} // namespace si::si_literals






