#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_dimension{.current = 1, .time = 1};

// Electric charge units (Coulomb and derived)
// Base unit: Coulomb (C) = A·s
using coulomb = unit_t<double, std::ratio<1, 1>, electric_charge_dimension>;
using kilocoulomb = unit_t<double, std::ratio<1000, 1>, electric_charge_dimension>;
using millicoulomb = unit_t<double, std::ratio<1, 1000>, electric_charge_dimension>;
using microcoulomb = unit_t<double, std::ratio<1, 1000000>, electric_charge_dimension>;
using nanocoulomb = unit_t<double, std::ratio<1, 1000000000>, electric_charge_dimension>;
using picocoulomb = unit_t<double, std::ratio<1, 1000000000000>, electric_charge_dimension>;

} // PKR_SI_NAMESPACE


