#pragma once

#include <ratio>
#include "dimension.h"
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Density dimension: kg·m⁻³
inline constexpr dimension_t density_dimension{.mass = 1, .length = -3};

// Density quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using density_unit_t = details::unit_t<type_t, ratio_t, density_dimension>;
}  // namespace PKR_UNITS_NAMESPACE






