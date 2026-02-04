#pragma once

#include <ratio>
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Length dimension
inline constexpr dimension_t length_dimension{1, 0, 0, 0, 0, 0, 0, 0};

// Length quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length_unit_t = details::unit_t<type_t, ratio_t, length_dimension>;
} // namespace PKR_UNITS_NAMESPACE
