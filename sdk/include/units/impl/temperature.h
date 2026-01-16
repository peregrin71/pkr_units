// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
// Temperature quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using temperature = unit_t<type_t, ratio_t, temperature_dimension>;

// Strong type for kelvin (SI base unit)
struct kelvin : public unit_t<double, std::ratio<1, 1>, temperature_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, temperature_dimension>;
    using _base::_base;
};

// Metric temperature prefixes (strong types)
struct attokelvin : public unit_t<double, std::atto, temperature_dimension>
{
    using _base = unit_t<double, std::atto, temperature_dimension>;
    using _base::_base;
};

struct femtokelvin : public unit_t<double, std::femto, temperature_dimension>
{
    using _base = unit_t<double, std::femto, temperature_dimension>;
    using _base::_base;
};

struct picokelvin : public unit_t<double, std::pico, temperature_dimension>
{
    using _base = unit_t<double, std::pico, temperature_dimension>;
    using _base::_base;
};

struct nanokelvin : public unit_t<double, std::nano, temperature_dimension>
{
    using _base = unit_t<double, std::nano, temperature_dimension>;
    using _base::_base;
};

struct microkelvin : public unit_t<double, std::micro, temperature_dimension>
{
    using _base = unit_t<double, std::micro, temperature_dimension>;
    using _base::_base;
};

struct millikelvin : public unit_t<double, std::milli, temperature_dimension>
{
    using _base = unit_t<double, std::milli, temperature_dimension>;
    using _base::_base;
};

struct centikelvin : public unit_t<double, std::centi, temperature_dimension>
{
    using _base = unit_t<double, std::centi, temperature_dimension>;
    using _base::_base;
};

struct decikelvin : public unit_t<double, std::deci, temperature_dimension>
{
    using _base = unit_t<double, std::deci, temperature_dimension>;
    using _base::_base;
};

struct decakelvin : public unit_t<double, std::deca, temperature_dimension>
{
    using _base = unit_t<double, std::deca, temperature_dimension>;
    using _base::_base;
};

struct hectokelvin : public unit_t<double, std::hecto, temperature_dimension>
{
    using _base = unit_t<double, std::hecto, temperature_dimension>;
    using _base::_base;
};

struct kilokelvin : public unit_t<double, std::kilo, temperature_dimension>
{
    using _base = unit_t<double, std::kilo, temperature_dimension>;
    using _base::_base;
};

struct megakelvin : public unit_t<double, std::mega, temperature_dimension>
{
    using _base = unit_t<double, std::mega, temperature_dimension>;
    using _base::_base;
};

} // namespace si
