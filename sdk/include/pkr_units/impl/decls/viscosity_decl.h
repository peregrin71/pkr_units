#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Dynamic viscosity dimension: kg·m^-1·s^-1
inline constexpr dimension_t dynamic_viscosity_dimension{ -1, 1, -1, 0, 0, 0, 0, 0 };

// Kinematic viscosity dimension: m^2·s^-1
inline constexpr dimension_t kinematic_viscosity_dimension{ 2, 0, -1, 0, 0, 0, 0, 0 };

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using dynamic_viscosity_unit_t = details::unit_t<type_t, ratio_t, dynamic_viscosity_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using kinematic_viscosity_unit_t = details::unit_t<type_t, ratio_t, kinematic_viscosity_dimension>;
} // namespace PKR_UNITS_NAMESPACE
