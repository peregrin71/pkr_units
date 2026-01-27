#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/acceleration_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial acceleration units
using feet_per_second_squared = details::unit_t<double, std::ratio<3048, 10000>, acceleration_v>;

} // namespace PKR_UNITS_NAMESPACE
