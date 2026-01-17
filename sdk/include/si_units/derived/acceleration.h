#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Acceleration dimension
inline constexpr dimension_t acceleration_v{1, 0, -2, 0, 0, 0, 0};

// Acceleration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using acceleration = unit_t<type_t, ratio_t, acceleration_v>;

// SI metric acceleration units

// Base unit: meter per second squared (m/s²)
struct meter_per_second_squared final : public unit_t<double, std::ratio<1, 1>, acceleration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, acceleration_v>;
    using _base::_base;
};

struct centimeter_per_second_squared final : public unit_t<double, std::ratio<1, 100>, acceleration_v>
{
    using _base = unit_t<double, std::ratio<1, 100>, acceleration_v>;
    using _base::_base;
};

struct millimeter_per_second_squared final : public unit_t<double, std::ratio<1, 1000>, acceleration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000>, acceleration_v>;
    using _base::_base;
};

struct kilometer_per_second_squared final : public unit_t<double, std::ratio<1000, 1>, acceleration_v>
{
    using _base = unit_t<double, std::ratio<1000, 1>, acceleration_v>;
    using _base::_base;
};

// Standard gravity (g) - 1 g = 9.80665 m/s² (exact definition)
struct standard_gravity final : public unit_t<double, std::ratio<980665, 100000>, acceleration_v>
{
    using _base = unit_t<double, std::ratio<980665, 100000>, acceleration_v>;
    using _base::_base;
};

// Imperial acceleration units
struct feet_per_second_squared final : public unit_t<double, std::ratio<3048, 10000>, acceleration_v>
{
    using _base = unit_t<double, std::ratio<3048, 10000>, acceleration_v>;
    using _base::_base;
};

struct inches_per_second_squared final : public unit_t<double, std::ratio<254, 10000>, acceleration_v>
{
    using _base = unit_t<double, std::ratio<254, 10000>, acceleration_v>;
    using _base::_base;
};

} // PKR_SI_NAMESPACE








