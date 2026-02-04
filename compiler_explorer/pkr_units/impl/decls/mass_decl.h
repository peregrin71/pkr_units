#pragma once

#include <ratio>
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Mass dimension
inline constexpr dimension_t mass_dimension{0, 1, 0, 0, 0, 0, 0, 0};

// Mass quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_unit_t = details::unit_t<type_t, ratio_t, mass_dimension>;
} // namespace PKR_UNITS_NAMESPACE
