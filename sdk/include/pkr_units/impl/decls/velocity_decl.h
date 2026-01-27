#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Velocity dimension
inline constexpr dimension_t velocity_dimension{.length = 1, .time = -1};

// Velocity quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using velocity_unit_t = details::unit_t<type_t, ratio_t, velocity_dimension>;
} // namespace PKR_UNITS_NAMESPACE
