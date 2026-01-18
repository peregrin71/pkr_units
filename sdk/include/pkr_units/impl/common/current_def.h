#pragma once

#include <ratio>
#include "dimension.h"
#include "unit_t_def.h"

namespace PKR_UNITS_NAMESPACE
{
// Current dimension
inline constexpr dimension_t current_dimension{.current = 1};

// Current quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using current_unit_t = details::unit_t<type_t, ratio_t, current_dimension>;
}  // namespace PKR_UNITS_NAMESPACE