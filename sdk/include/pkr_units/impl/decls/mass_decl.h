#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Mass dimension
inline constexpr dimension_t mass_dimension{.mass = 1};

// Mass quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_unit_t = details::unit_t<type_t, ratio_t, mass_dimension>;
}  // namespace PKR_UNITS_NAMESPACE





