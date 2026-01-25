#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/mass_decl.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Imperial mass units
using grain = details::unit_t<double, std::ratio<64799, 1000000000>, mass_dimension>;      // 1 grain = 0.00006479891 kg
using dram = details::unit_t<double, std::ratio<1771845, 1000000000>, mass_dimension>;      // 1 dram (avoirdupois) = 0.001771845 kg
using ounce = details::unit_t<double, std::ratio<28349523, 1000000000>, mass_dimension>;    // 1 ounce = 0.028349523 kg
using pound = details::unit_t<double, std::ratio<453592370, 1000000000>, mass_dimension>;   // 1 pound = 0.45359237 kg
using stone = details::unit_t<double, std::ratio<6350293180, 1000000000>, mass_dimension>;  // 1 stone = 6.35029318 kg
using hundredweight = details::unit_t<double, std::ratio<50802345, 1000000>, mass_dimension>; // 1 cwt (short) = 50.80234544 kg
using us_ton = details::unit_t<double, std::ratio<907184740, 1000000000>, mass_dimension>;     // 1 short ton = 907.18474 kg
using long_ton = details::unit_t<double, std::ratio<1016046909, 1000000000>, mass_dimension>; // 1 long ton = 1016.0469088 kg

} // PKR_UNITS_NAMESPACE








