#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Area dimension
inline constexpr dimension_t area_dimension{.length = 2};

// Area quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using area_unit_t = details::unit_t<type_t, ratio_t, area_dimension>;
} // namespace PKR_UNITS_NAMESPACE
