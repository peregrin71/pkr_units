#pragma once

#include <ratio>
#include "../dimension.h"
#include "unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// Mass concentration dimension: kg·m⁻³
inline constexpr dimension_t mass_concentration_v{ -3, 1, 0, 0, 0, 0, 0, 0};

// Molar concentration dimension: mol·m⁻³
inline constexpr dimension_t molar_concentration_v{ -3, 0, 0, 0, 0, 1, 0, 0};

// Mass concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_concentration_unit_t = details::unit_t<type_t, ratio_t, mass_concentration_v>;

// Molar concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using molar_concentration_unit_t = details::unit_t<type_t, ratio_t, molar_concentration_v>;
}  // namespace PKR_UNITS_NAMESPACE





