#pragma once

#include <pkr_units/impl/unit_impl.h>
#include "../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Imperial mass units
using grain = unit_t<double, std::ratio<64799, 1000000000>, mass_v>;      // 1 grain = 0.00006479891 kg
using dram = unit_t<double, std::ratio<1771845, 1000000000>, mass_v>;      // 1 dram (avoirdupois) = 0.001771845 kg
using ounce = unit_t<double, std::ratio<28349523, 1000000000>, mass_v>;    // 1 ounce = 0.028349523 kg
using pound = unit_t<double, std::ratio<453592370, 1000000000>, mass_v>;   // 1 pound = 0.45359237 kg
using stone = unit_t<double, std::ratio<6350293180, 1000000000>, mass_v>;  // 1 stone = 6.35029318 kg
using hundredweight = unit_t<double, std::ratio<50802345, 1000000>, mass_v>; // 1 cwt (short) = 50.80234544 kg
using us_ton = unit_t<double, std::ratio<907184740, 1000000000>, mass_v>;     // 1 short ton = 907.18474 kg
using long_ton = unit_t<double, std::ratio<1016046909, 1000000000>, mass_v>; // 1 long ton = 1016.0469088 kg

} // PKR_UNITS_NAMESPACE








