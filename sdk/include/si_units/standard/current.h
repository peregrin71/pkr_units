// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Current quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using current = unit_t<type_t, ratio_t, current_dimension>;

// Strong type for ampere (SI base unit)
struct ampere final : public unit_t<double, std::ratio<1, 1>, current_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, current_dimension>;
    using _base::_base;
};

// Metric current prefixes (strong types)
struct attoampere final : public unit_t<double, std::atto, current_dimension>
{
    using _base = unit_t<double, std::atto, current_dimension>;
    using _base::_base;
};

struct femtoampere final : public unit_t<double, std::femto, current_dimension>
{
    using _base = unit_t<double, std::femto, current_dimension>;
    using _base::_base;
};

struct picoampere final : public unit_t<double, std::pico, current_dimension>
{
    using _base = unit_t<double, std::pico, current_dimension>;
    using _base::_base;
};

struct nanoampere final : public unit_t<double, std::nano, current_dimension>
{
    using _base = unit_t<double, std::nano, current_dimension>;
    using _base::_base;
};

struct microampere final : public unit_t<double, std::micro, current_dimension>
{
    using _base = unit_t<double, std::micro, current_dimension>;
    using _base::_base;
};

struct milliampere final : public unit_t<double, std::milli, current_dimension>
{
    using _base = unit_t<double, std::milli, current_dimension>;
    using _base::_base;
};

struct centiampere final : public unit_t<double, std::centi, current_dimension>
{
    using _base = unit_t<double, std::centi, current_dimension>;
    using _base::_base;
};

struct deciampere final : public unit_t<double, std::deci, current_dimension>
{
    using _base = unit_t<double, std::deci, current_dimension>;
    using _base::_base;
};

struct decaampere final : public unit_t<double, std::deca, current_dimension>
{
    using _base = unit_t<double, std::deca, current_dimension>;
    using _base::_base;
};

struct hectoampere final : public unit_t<double, std::hecto, current_dimension>
{
    using _base = unit_t<double, std::hecto, current_dimension>;
    using _base::_base;
};

struct kiloampere final : public unit_t<double, std::kilo, current_dimension>
{
    using _base = unit_t<double, std::kilo, current_dimension>;
    using _base::_base;
};

struct megaampere final : public unit_t<double, std::mega, current_dimension>
{
    using _base = unit_t<double, std::mega, current_dimension>;
    using _base::_base;
};

PKR_SI_NAMESPACE_END


