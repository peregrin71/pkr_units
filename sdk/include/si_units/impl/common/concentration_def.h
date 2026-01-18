#pragma once

#include "unit.h"

PKR_SI_BEGIN_NAMESPACE
{

// Mass concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_concentration_unit_t = details::unit_t<type_t, ratio_t, details::mass_concentration_v>;

// Molar concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using molar_concentration_unit_t = details::unit_t<type_t, ratio_t, details::molar_concentration_v>;

PKR_SI_NAMESPACE_END
