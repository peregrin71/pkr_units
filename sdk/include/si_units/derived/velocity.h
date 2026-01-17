#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/velocity/details/velocity_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Velocity quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using velocity = unit_t<type_t, ratio_t, velocity_dimension>;

// SI metric velocity units

// Base unit: meter per second (m/s)
struct meter_per_second final : public unit_t<double, std::ratio<1, 1>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, velocity_dimension>;
    using _base::_base;
};

// Other SI velocity units
struct kilometer_per_hour final : public unit_t<double, std::ratio<5, 18>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<5, 18>, velocity_dimension>;
    using _base::_base;
};

struct centimeter_per_second final : public unit_t<double, std::ratio<1, 100>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<1, 100>, velocity_dimension>;
    using _base::_base;
};

struct millimeter_per_second final : public unit_t<double, std::ratio<1, 1000>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, velocity_dimension>;
    using _base::_base;
};

struct kilometer_per_second final : public unit_t<double, std::ratio<1000, 1>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, velocity_dimension>;
    using _base::_base;
};

// Imperial velocity units
struct miles_per_hour final : public unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>;
    using _base::_base;
};

struct feet_per_second final : public unit_t<double, std::ratio<3048, 10000>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<3048, 10000>, velocity_dimension>;
    using _base::_base;
};

struct inches_per_second final : public unit_t<double, std::ratio<254, 10000>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<254, 10000>, velocity_dimension>;
    using _base::_base;
};

// Maritime velocity units
struct knots final : public unit_t<double, std::ratio<1852, 3600>, velocity_dimension>
{
    using _base = unit_t<double, std::ratio<1852, 3600>, velocity_dimension>;
    using _base::_base;
};

} // PKR_SI_NAMESPACE








