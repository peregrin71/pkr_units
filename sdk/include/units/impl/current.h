// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
// Current quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using current = unit_t<type_t, ratio_t, current_dimension>;

// Strong type for ampere (SI base unit)
struct ampere : public unit_t<double, std::ratio<1, 1>, current_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, current_dimension>;
    using _base::_base;
};

// Metric current prefixes (strong types)
struct attoampere : public unit_t<double, std::atto, current_dimension>
{
    using _base = unit_t<double, std::atto, current_dimension>;
    using _base::_base;
};

struct femtoampere : public unit_t<double, std::femto, current_dimension>
{
    using _base = unit_t<double, std::femto, current_dimension>;
    using _base::_base;
};

struct picoampere : public unit_t<double, std::pico, current_dimension>
{
    using _base = unit_t<double, std::pico, current_dimension>;
    using _base::_base;
};

struct nanoampere : public unit_t<double, std::nano, current_dimension>
{
    using _base = unit_t<double, std::nano, current_dimension>;
    using _base::_base;
};

struct microampere : public unit_t<double, std::micro, current_dimension>
{
    using _base = unit_t<double, std::micro, current_dimension>;
    using _base::_base;
};

struct milliampere : public unit_t<double, std::milli, current_dimension>
{
    using _base = unit_t<double, std::milli, current_dimension>;
    using _base::_base;
};

struct centiampere : public unit_t<double, std::centi, current_dimension>
{
    using _base = unit_t<double, std::centi, current_dimension>;
    using _base::_base;
};

struct deciampere : public unit_t<double, std::deci, current_dimension>
{
    using _base = unit_t<double, std::deci, current_dimension>;
    using _base::_base;
};

struct decaampere : public unit_t<double, std::deca, current_dimension>
{
    using _base = unit_t<double, std::deca, current_dimension>;
    using _base::_base;
};

struct hectoampere : public unit_t<double, std::hecto, current_dimension>
{
    using _base = unit_t<double, std::hecto, current_dimension>;
    using _base::_base;
};

struct kiloampere : public unit_t<double, std::kilo, current_dimension>
{
    using _base = unit_t<double, std::kilo, current_dimension>;
    using _base::_base;
};

struct megaampere : public unit_t<double, std::mega, current_dimension>
{
    using _base = unit_t<double, std::mega, current_dimension>;
    using _base::_base;
};

} // namespace si
