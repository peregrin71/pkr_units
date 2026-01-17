// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "acceleration.h"
#include "../../namespace_config.h"

namespace si::si_literals
{
    // Acceleration unit literals
    constexpr si::meters_per_second_squared operator"" _mps2(long double value) noexcept
    {
        return si::meters_per_second_squared{static_cast<double>(value});
    }

    constexpr si::centimeters_per_second_squared operator"" _cms2(long double value) noexcept
    {
        return si::centimeters_per_second_squared{static_cast<double>(value});
    }

    constexpr si::millimeters_per_second_squared operator"" _mms2(long double value) noexcept
    {
        return si::millimeters_per_second_squared{static_cast<double>(value});
    }

    constexpr si::feet_per_second_squared operator"" _fts2(long double value) noexcept
    {
        return si::feet_per_second_squared{static_cast<double>(value});
    }

    constexpr si::standard_gravity operator"" _g(long double value) noexcept
    {
        return si::standard_gravity{static_cast<double>(value});
    }

PKR_SI_NAMESPACE_END::si_literals










