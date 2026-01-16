// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"

namespace si
{
// Time quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using time = unit_t<type_t, ratio_t, time_dimension>;

// Strong type for second (SI base unit)
struct second : public unit_t<double, std::ratio<1, 1>, time_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, time_dimension>;
    using _base::_base;
};

// Metric time prefixes (strong types)
struct attosecond : public unit_t<double, std::atto, time_dimension>
{
    using _base = unit_t<double, std::atto, time_dimension>;
    using _base::_base;
};

struct femtosecond : public unit_t<double, std::femto, time_dimension>
{
    using _base = unit_t<double, std::femto, time_dimension>;
    using _base::_base;
};

struct picosecond : public unit_t<double, std::pico, time_dimension>
{
    using _base = unit_t<double, std::pico, time_dimension>;
    using _base::_base;
};

struct nanosecond : public unit_t<double, std::nano, time_dimension>
{
    using _base = unit_t<double, std::nano, time_dimension>;
    using _base::_base;
};

struct microsecond : public unit_t<double, std::micro, time_dimension>
{
    using _base = unit_t<double, std::micro, time_dimension>;
    using _base::_base;
};

struct millisecond : public unit_t<double, std::milli, time_dimension>
{
    using _base = unit_t<double, std::milli, time_dimension>;
    using _base::_base;
};

struct centisecond : public unit_t<double, std::centi, time_dimension>
{
    using _base = unit_t<double, std::centi, time_dimension>;
    using _base::_base;
};

struct decisecond : public unit_t<double, std::deci, time_dimension>
{
    using _base = unit_t<double, std::deci, time_dimension>;
    using _base::_base;
};

struct decasecond : public unit_t<double, std::deca, time_dimension>
{
    using _base = unit_t<double, std::deca, time_dimension>;
    using _base::_base;
};

struct hectosecond : public unit_t<double, std::hecto, time_dimension>
{
    using _base = unit_t<double, std::hecto, time_dimension>;
    using _base::_base;
};

struct kilosecond : public unit_t<double, std::kilo, time_dimension>
{
    using _base = unit_t<double, std::kilo, time_dimension>;
    using _base::_base;
};

struct megasecond : public unit_t<double, std::mega, time_dimension>
{
    using _base = unit_t<double, std::mega, time_dimension>;
    using _base::_base;
};

} // namespace si








