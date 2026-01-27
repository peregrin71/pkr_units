#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/derived/mechanical/force.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial force units
using poundal = details::unit_t<double, std::ratio<45359237, 1000000000>, force_dimension>; // 1 pdl = 0.138255 N
using pound_force = details::unit_t<double, std::ratio<4448222, 1000000>, force_dimension>; // 1 lbf ≈ 4.448 N

} // namespace PKR_UNITS_NAMESPACE
