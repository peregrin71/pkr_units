#pragma once

#include <ratio>
#include "dimension.h"
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Time dimension
inline constexpr dimension_t time_dimension{.time = 1};

// Time quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using time_unit_t = details::unit_t<type_t, ratio_t, time_dimension>;
}  // namespace PKR_UNITS_NAMESPACE





