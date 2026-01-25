#pragma once

#include <ratio>
#include "../dimension.h"
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Acceleration dimension
inline constexpr dimension_t acceleration_v{1, 0, -2, 0, 0, 0, 0, 0};

// Acceleration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using acceleration_unit_t = details::unit_t<type_t, ratio_t, acceleration_v>;
}  // namespace PKR_UNITS_NAMESPACE






