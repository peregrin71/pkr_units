#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Josephson constant dimension: A·s²·kg⁻¹·m⁻² (Hz/V)
inline constexpr dimension_t josephson_dimension{-2, -1, 2, 1, 0, 0, 0, 0};

// Josephson constant quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using josephson_unit_t = details::unit_t<type_t, ratio_t, josephson_dimension>;
}  // namespace PKR_UNITS_NAMESPACE