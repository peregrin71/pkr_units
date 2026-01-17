// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Dimension struct for dimensional analysis (C++20 as NTTP)
// TODO : model if a value in a dimension can be negative or not
struct dimension_t
{
    int length = 0;         //meter (m)
    int mass = 0;           //kilogram (kg)
    int time = 0;           //second (s)
    int current = 0;        //ampere (A)
    int temperature = 0;    //kelvin (K)
    int amount = 0;         //mole (mol)
    int intensity = 0;      //candela (cd)

    constexpr bool operator==(const dimension_t&) const = default;
};

// Common dimension constants
inline constexpr dimension_t scalar{};
inline constexpr dimension_t length_dimension{.length = 1};
inline constexpr dimension_t mass_dimension{.mass = 1};
inline constexpr dimension_t time_dimension{.time = 1};
inline constexpr dimension_t current_dimension{.current = 1};
inline constexpr dimension_t temperature_dimension{.temperature = 1};
inline constexpr dimension_t amount_dimension{.amount = 1};
inline constexpr dimension_t intensity_dimension{.intensity = 1};
inline constexpr dimension_t frequency_dimension{.time = -1};

PKR_SI_NAMESPACE_END








