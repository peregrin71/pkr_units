// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"

namespace si
{
// Amount quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using amount = unit_t<type_t, ratio_t, amount_dimension>;

// Strong type for mole (SI base unit)
struct mole : public unit_t<double, std::ratio<1, 1>, amount_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, amount_dimension>;
    using _base::_base;
};

// Metric amount prefixes (strong types)
struct attomole : public unit_t<double, std::atto, amount_dimension>
{
    using _base = unit_t<double, std::atto, amount_dimension>;
    using _base::_base;
};

struct femtomole : public unit_t<double, std::femto, amount_dimension>
{
    using _base = unit_t<double, std::femto, amount_dimension>;
    using _base::_base;
};

struct picomole : public unit_t<double, std::pico, amount_dimension>
{
    using _base = unit_t<double, std::pico, amount_dimension>;
    using _base::_base;
};

struct nanomole : public unit_t<double, std::nano, amount_dimension>
{
    using _base = unit_t<double, std::nano, amount_dimension>;
    using _base::_base;
};

struct micromole : public unit_t<double, std::micro, amount_dimension>
{
    using _base = unit_t<double, std::micro, amount_dimension>;
    using _base::_base;
};

struct millimole : public unit_t<double, std::milli, amount_dimension>
{
    using _base = unit_t<double, std::milli, amount_dimension>;
    using _base::_base;
};

struct centimole : public unit_t<double, std::centi, amount_dimension>
{
    using _base = unit_t<double, std::centi, amount_dimension>;
    using _base::_base;
};

struct decimole : public unit_t<double, std::deci, amount_dimension>
{
    using _base = unit_t<double, std::deci, amount_dimension>;
    using _base::_base;
};

struct decamole : public unit_t<double, std::deca, amount_dimension>
{
    using _base = unit_t<double, std::deca, amount_dimension>;
    using _base::_base;
};

struct hectomole : public unit_t<double, std::hecto, amount_dimension>
{
    using _base = unit_t<double, std::hecto, amount_dimension>;
    using _base::_base;
};

struct kilomole : public unit_t<double, std::kilo, amount_dimension>
{
    using _base = unit_t<double, std::kilo, amount_dimension>;
    using _base::_base;
};

struct megamole : public unit_t<double, std::mega, amount_dimension>
{
    using _base = unit_t<double, std::mega, amount_dimension>;
    using _base::_base;
};

} // namespace si


