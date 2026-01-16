// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Electric potential dimension
inline constexpr dimension_t electric_potential_dimension{2, 1, -3, -1, 0, 0, 0};

// Electric potential units (Volt and derived)
// Base unit: Volt (V) = kg·m²·s⁻³·A⁻¹
using volt = unit_t<double, std::ratio<1, 1>, electric_potential_dimension>;
using kilovolt = unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>;
using megavolt = unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>;
using millivolt = unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>;
using microvolt = unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>;

} // namespace si
