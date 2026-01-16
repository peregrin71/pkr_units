// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

namespace si
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
inline constexpr dimension_t length_v{.length = 1};
inline constexpr dimension_t mass_v{.mass = 1};
inline constexpr dimension_t time_v{.time = 1};
inline constexpr dimension_t frequency_v{.time = -1};

} // namespace si






