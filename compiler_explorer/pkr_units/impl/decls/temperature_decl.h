#pragma once

#include <ratio>
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Temperature dimension
inline constexpr dimension_t temperature_dimension{0, 0, 0, 0, 1, 0, 0, 0};

// Temperature quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using temperature_unit_t = details::unit_t<type_t, ratio_t, temperature_dimension>;
} // namespace PKR_UNITS_NAMESPACE
