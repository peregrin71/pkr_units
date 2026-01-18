#pragma once

#include <ratio>
#include "dimension.h"
#include "unit_t_def.h"

namespace PKR_UNITS_NAMESPACE
{
// Amount dimension
inline constexpr dimension_t amount_dimension{.amount = 1};

// Amount quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using amount_unit_t = details::unit_t<type_t, ratio_t, amount_dimension>;
}  // namespace PKR_UNITS_NAMESPACE