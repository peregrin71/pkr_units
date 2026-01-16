// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"

namespace si
{
// Intensity quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using intensity = unit_t<type_t, ratio_t, intensity_dimension>;

// Strong type for candela (SI base unit)
struct candela final : public unit_t<double, std::ratio<1, 1>, intensity_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, intensity_dimension>;
    using _base::_base;
};

// Metric intensity prefixes (strong types)
struct attocandela final : public unit_t<double, std::atto, intensity_dimension>
{
    using _base = unit_t<double, std::atto, intensity_dimension>;
    using _base::_base;
};

struct femtocandela final : public unit_t<double, std::femto, intensity_dimension>
{
    using _base = unit_t<double, std::femto, intensity_dimension>;
    using _base::_base;
};

struct picocandela final : public unit_t<double, std::pico, intensity_dimension>
{
    using _base = unit_t<double, std::pico, intensity_dimension>;
    using _base::_base;
};

struct nanocandela final : public unit_t<double, std::nano, intensity_dimension>
{
    using _base = unit_t<double, std::nano, intensity_dimension>;
    using _base::_base;
};

struct microcandela final : public unit_t<double, std::micro, intensity_dimension>
{
    using _base = unit_t<double, std::micro, intensity_dimension>;
    using _base::_base;
};

struct millicandela final : public unit_t<double, std::milli, intensity_dimension>
{
    using _base = unit_t<double, std::milli, intensity_dimension>;
    using _base::_base;
};

struct centicandela final : public unit_t<double, std::centi, intensity_dimension>
{
    using _base = unit_t<double, std::centi, intensity_dimension>;
    using _base::_base;
};

struct decicandela final : public unit_t<double, std::deci, intensity_dimension>
{
    using _base = unit_t<double, std::deci, intensity_dimension>;
    using _base::_base;
};

struct decacandela final : public unit_t<double, std::deca, intensity_dimension>
{
    using _base = unit_t<double, std::deca, intensity_dimension>;
    using _base::_base;
};

struct hectocandela final : public unit_t<double, std::hecto, intensity_dimension>
{
    using _base = unit_t<double, std::hecto, intensity_dimension>;
    using _base::_base;
};

struct kilocandela final : public unit_t<double, std::kilo, intensity_dimension>
{
    using _base = unit_t<double, std::kilo, intensity_dimension>;
    using _base::_base;
};

struct megacandela final : public unit_t<double, std::mega, intensity_dimension>
{
    using _base = unit_t<double, std::mega, intensity_dimension>;
    using _base::_base;
};

} // namespace si


