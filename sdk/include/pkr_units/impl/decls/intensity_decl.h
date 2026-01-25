#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Intensity dimension
inline constexpr dimension_t intensity_dimension{.intensity = 1};

// Intensity quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using intensity_unit_t = details::unit_t<type_t, ratio_t, intensity_dimension>;
}  // namespace PKR_UNITS_NAMESPACE





