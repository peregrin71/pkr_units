#pragma once

#include "../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Dimension struct for dimensional analysis (C++20 as NTTP)
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

// Dimensionless (scalar) dimension - default constructed with all zeros
inline constexpr dimension_t scalar_dimension{};

}  // namespace PKR_UNITS_NAMESPACE











