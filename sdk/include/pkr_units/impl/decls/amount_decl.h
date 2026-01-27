#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Amount dimension
inline constexpr dimension_t amount_dimension{0, 0, 0, 0, 0, 1, 0, 0};

// Amount quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using amount_unit_t = details::unit_t<type_t, ratio_t, amount_dimension>;
} // namespace PKR_UNITS_NAMESPACE
