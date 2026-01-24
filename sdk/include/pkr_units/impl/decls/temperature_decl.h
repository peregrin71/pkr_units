#pragma once

#include <ratio>
#include "dimension.h"
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Temperature dimension
inline constexpr dimension_t temperature_dimension{.temperature = 1};

// Temperature quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using temperature_unit_t = details::unit_t<type_t, ratio_t, temperature_dimension>;
}  // namespace PKR_UNITS_NAMESPACE





