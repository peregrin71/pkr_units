// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "details/si_unit.h"
#include "details/dimension.h"

namespace si
{
// Mass quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass = unit_t<type_t, ratio_t, mass_dimension>;

// Strong type for kilogram (SI base unit for mass)
// NOTE: Kilogram is the base SI unit, not gram (unlike length where meter is base)
struct kilogram : public unit_t<double, std::ratio<1, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, mass_dimension>;
    using _base::_base;
};

// Metric mass prefixes (applied relative to kilogram)
// All mass units are defined relative to kilogram (ratio 1/1) as the base
struct attogram : public unit_t<double, std::ratio<1, 1000000000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000000000>, mass_dimension>;
    using _base::_base;
};

struct femtogram : public unit_t<double, std::ratio<1, 1000000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000000>, mass_dimension>;
    using _base::_base;
};

struct picogram : public unit_t<double, std::ratio<1, 1000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000>, mass_dimension>;
    using _base::_base;
};

struct nanogram : public unit_t<double, std::ratio<1, 1000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000>, mass_dimension>;
    using _base::_base;
};

struct microgram : public unit_t<double, std::ratio<1, 1000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_dimension>;
    using _base::_base;
};

struct milligram : public unit_t<double, std::ratio<1, 1000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_dimension>;
    using _base::_base;
};

struct centigram : public unit_t<double, std::ratio<1, 100000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 100000>, mass_dimension>;
    using _base::_base;
};

struct decigram : public unit_t<double, std::ratio<1, 10000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 10000>, mass_dimension>;
    using _base::_base;
};

// gram is 1/1000 of kilogram
struct gram : public unit_t<double, std::ratio<1, 1000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, mass_dimension>;
    using _base::_base;
};

struct decagram : public unit_t<double, std::ratio<1, 100>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 100>, mass_dimension>;
    using _base::_base;
};

struct hectogram : public unit_t<double, std::ratio<1, 10>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 10>, mass_dimension>;
    using _base::_base;
};

// Larger mass units
struct megagram : public unit_t<double, std::ratio<1000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, mass_dimension>;
    using _base::_base;
};

struct gigagram : public unit_t<double, std::ratio<1000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, mass_dimension>;
    using _base::_base;
};

struct teragram : public unit_t<double, std::ratio<1000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, mass_dimension>;
    using _base::_base;
};

struct petagram : public unit_t<double, std::ratio<1000000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000000, 1>, mass_dimension>;
    using _base::_base;
};

struct exagram : public unit_t<double, std::ratio<1000000000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000000000, 1>, mass_dimension>;
    using _base::_base;
};

// Common aliases
using metric_ton = megagram;  // 1 metric ton = 1,000 kg (same as megagram)

} // namespace si






