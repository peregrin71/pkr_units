#pragma once

#include "../namespace_config.h"

PKR_SI_DETAILS_BEGIN_NAMESPACE

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

PKR_SI_DETAILS_END_NAMESPACE









