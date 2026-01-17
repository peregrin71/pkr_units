#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Mass quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass = unit_t<type_t, ratio_t, mass_dimension>;

// Strong type for kilogram (SI base unit for mass)
// NOTE: Kilogram is the base SI unit, not gram (unlike length where meter is base)
struct kilogram final : public unit_t<double, std::ratio<1, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, mass_dimension>;
    using _base::_base;
};

// Metric mass prefixes (applied relative to kilogram)
// All mass units are defined relative to kilogram (ratio 1/1) as the base
struct attogram final : public unit_t<double, std::ratio<1, 1000000000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000000000>, mass_dimension>;
    using _base::_base;
};

struct femtogram final : public unit_t<double, std::ratio<1, 1000000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000000>, mass_dimension>;
    using _base::_base;
};

struct picogram final : public unit_t<double, std::ratio<1, 1000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000>, mass_dimension>;
    using _base::_base;
};

struct nanogram final : public unit_t<double, std::ratio<1, 1000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000>, mass_dimension>;
    using _base::_base;
};

struct microgram final : public unit_t<double, std::ratio<1, 1000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_dimension>;
    using _base::_base;
};

struct milligram final : public unit_t<double, std::ratio<1, 1000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_dimension>;
    using _base::_base;
};

struct centigram final : public unit_t<double, std::ratio<1, 100000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 100000>, mass_dimension>;
    using _base::_base;
};

struct decigram final : public unit_t<double, std::ratio<1, 10000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 10000>, mass_dimension>;
    using _base::_base;
};

// gram is 1/1000 of kilogram
struct gram final : public unit_t<double, std::ratio<1, 1000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, mass_dimension>;
    using _base::_base;
};

struct decagram final : public unit_t<double, std::ratio<1, 100>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 100>, mass_dimension>;
    using _base::_base;
};

struct hectogram final : public unit_t<double, std::ratio<1, 10>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 10>, mass_dimension>;
    using _base::_base;
};

// Larger mass units
struct megagram final : public unit_t<double, std::ratio<1000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, mass_dimension>;
    using _base::_base;
};

struct gigagram final : public unit_t<double, std::ratio<1000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, mass_dimension>;
    using _base::_base;
};

struct teragram final : public unit_t<double, std::ratio<1000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, mass_dimension>;
    using _base::_base;
};

struct petagram final : public unit_t<double, std::ratio<1000000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000000, 1>, mass_dimension>;
    using _base::_base;
};

struct exagram final : public unit_t<double, std::ratio<1000000000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000000000, 1>, mass_dimension>;
    using _base::_base;
};

// Common aliases
using metric_ton = megagram;  // 1 metric ton = 1,000 kg (same as megagram)

PKR_SI_NAMESPACE_END








