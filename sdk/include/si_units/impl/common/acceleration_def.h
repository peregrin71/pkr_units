#pragma once

#include "unit.h"

PKR_SI_BEGIN_NAMESPACE
{

// Acceleration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using acceleration_unit_t = details::unit_t<type_t, ratio_t, details::acceleration_v>;

PKR_SI_NAMESPACE_END
