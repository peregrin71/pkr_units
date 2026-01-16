// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <units/impl/details/si_unit.h>
#include <units/impl/details/dimension.h>

namespace si
{

// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_v{.current = 1, .time = 1};

// Electric charge units (Coulomb and derived)
// Base unit: Coulomb (C) = A·s
using coulomb = unit_t<double, std::ratio<1, 1>, electric_charge_v>;
using kilocoulomb = unit_t<double, std::ratio<1000, 1>, electric_charge_v>;
using millicoulomb = unit_t<double, std::ratio<1, 1000>, electric_charge_v>;
using microcoulomb = unit_t<double, std::ratio<1, 1000000>, electric_charge_v>;
using nanocoulomb = unit_t<double, std::ratio<1, 1000000000>, electric_charge_v>;
using picocoulomb = unit_t<double, std::ratio<1, 1000000000000>, electric_charge_v>;

} // namespace si
