// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"

namespace si
{
// Length quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length = unit_t<type_t, ratio_t, length_dimension>;

// Strong type for meter (SI base unit)
struct meter : public unit_t<double, std::ratio<1, 1>, length_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, length_dimension>;
    using _base::_base;
};

// Metric length prefixes (strong types)
struct attometer : public unit_t<double, std::atto, length_dimension>
{
    using _base = unit_t<double, std::atto, length_dimension>;
    using _base::_base;
};

struct femtometer : public unit_t<double, std::femto, length_dimension>
{
    using _base = unit_t<double, std::femto, length_dimension>;
    using _base::_base;
};

struct picometer : public unit_t<double, std::pico, length_dimension>
{
    using _base = unit_t<double, std::pico, length_dimension>;
    using _base::_base;
};

struct nanometer : public unit_t<double, std::nano, length_dimension>
{
    using _base = unit_t<double, std::nano, length_dimension>;
    using _base::_base;
};

struct micrometer : public unit_t<double, std::micro, length_dimension>
{
    using _base = unit_t<double, std::micro, length_dimension>;
    using _base::_base;
};

struct millimeter : public unit_t<double, std::milli, length_dimension>
{
    using _base = unit_t<double, std::milli, length_dimension>;
    using _base::_base;
};

struct centimeter : public unit_t<double, std::centi, length_dimension>
{
    using _base = unit_t<double, std::centi, length_dimension>;
    using _base::_base;
};

struct decimeter : public unit_t<double, std::deci, length_dimension>
{
    using _base = unit_t<double, std::deci, length_dimension>;
    using _base::_base;
};

struct decameter : public unit_t<double, std::deca, length_dimension>
{
    using _base = unit_t<double, std::deca, length_dimension>;
    using _base::_base;
};

struct hectometer : public unit_t<double, std::hecto, length_dimension>
{
    using _base = unit_t<double, std::hecto, length_dimension>;
    using _base::_base;
};

struct kilometer : public unit_t<double, std::kilo, length_dimension>
{
    using _base = unit_t<double, std::kilo, length_dimension>;
    using _base::_base;
};

struct megameter : public unit_t<double, std::mega, length_dimension>
{
    using _base = unit_t<double, std::mega, length_dimension>;
    using _base::_base;
};

struct gigameter : public unit_t<double, std::giga, length_dimension>
{
    using _base = unit_t<double, std::giga, length_dimension>;
    using _base::_base;
};

struct terameter : public unit_t<double, std::tera, length_dimension>
{
    using _base = unit_t<double, std::tera, length_dimension>;
    using _base::_base;
};

struct petameter : public unit_t<double, std::peta, length_dimension>
{
    using _base = unit_t<double, std::peta, length_dimension>;
    using _base::_base;
};

struct exameter : public unit_t<double, std::exa, length_dimension>
{
    using _base = unit_t<double, std::exa, length_dimension>;
    using _base::_base;
};

} // namespace si








