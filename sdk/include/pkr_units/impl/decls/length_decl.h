#pragma once

#include <ratio>
#include "dimension.h"
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Length dimension
inline constexpr dimension_t length_dimension{.length = 1};

// Length quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length_unit_t = details::unit_t<type_t, ratio_t, length_dimension>;
}  // namespace PKR_UNITS_NAMESPACE





