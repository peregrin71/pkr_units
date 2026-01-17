#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Length quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length = unit_t<type_t, ratio_t, length_dimension>;

// Strong type for meter (SI base unit)
struct meter final : public unit_t<double, std::ratio<1, 1>, length_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, length_dimension>;
    using _base::_base;
};

// Metric length prefixes (strong types)
struct attometer final : public unit_t<double, std::atto, length_dimension>
{
    using _base = unit_t<double, std::atto, length_dimension>;
    using _base::_base;
};

struct femtometer final : public unit_t<double, std::femto, length_dimension>
{
    using _base = unit_t<double, std::femto, length_dimension>;
    using _base::_base;
};

struct picometer final : public unit_t<double, std::pico, length_dimension>
{
    using _base = unit_t<double, std::pico, length_dimension>;
    using _base::_base;
};

struct nanometer final : public unit_t<double, std::nano, length_dimension>
{
    using _base = unit_t<double, std::nano, length_dimension>;
    using _base::_base;
};

struct micrometer final : public unit_t<double, std::micro, length_dimension>
{
    using _base = unit_t<double, std::micro, length_dimension>;
    using _base::_base;
};

struct millimeter final : public unit_t<double, std::milli, length_dimension>
{
    using _base = unit_t<double, std::milli, length_dimension>;
    using _base::_base;
};

struct centimeter final : public unit_t<double, std::centi, length_dimension>
{
    using _base = unit_t<double, std::centi, length_dimension>;
    using _base::_base;
};

struct decimeter final : public unit_t<double, std::deci, length_dimension>
{
    using _base = unit_t<double, std::deci, length_dimension>;
    using _base::_base;
};

struct decameter final : public unit_t<double, std::deca, length_dimension>
{
    using _base = unit_t<double, std::deca, length_dimension>;
    using _base::_base;
};

struct hectometer final : public unit_t<double, std::hecto, length_dimension>
{
    using _base = unit_t<double, std::hecto, length_dimension>;
    using _base::_base;
};

struct kilometer final : public unit_t<double, std::kilo, length_dimension>
{
    using _base = unit_t<double, std::kilo, length_dimension>;
    using _base::_base;
};

struct megameter final : public unit_t<double, std::mega, length_dimension>
{
    using _base = unit_t<double, std::mega, length_dimension>;
    using _base::_base;
};

struct gigameter final : public unit_t<double, std::giga, length_dimension>
{
    using _base = unit_t<double, std::giga, length_dimension>;
    using _base::_base;
};

struct terameter final : public unit_t<double, std::tera, length_dimension>
{
    using _base = unit_t<double, std::tera, length_dimension>;
    using _base::_base;
};

struct petameter final : public unit_t<double, std::peta, length_dimension>
{
    using _base = unit_t<double, std::peta, length_dimension>;
    using _base::_base;
};

struct exameter final : public unit_t<double, std::exa, length_dimension>
{
    using _base = unit_t<double, std::exa, length_dimension>;
    using _base::_base;
};

PKR_SI_NAMESPACE_END








