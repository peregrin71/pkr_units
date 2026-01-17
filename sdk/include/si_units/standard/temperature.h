#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Temperature quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using temperature = unit_t<type_t, ratio_t, temperature_dimension>;

// Strong type for kelvin (SI base unit)
struct kelvin final : public unit_t<double, std::ratio<1, 1>, temperature_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, temperature_dimension>;
    using _base::_base;
};

// Metric temperature prefixes (strong types)
struct attokelvin final : public unit_t<double, std::atto, temperature_dimension>
{
    using _base = unit_t<double, std::atto, temperature_dimension>;
    using _base::_base;
};

struct femtokelvin final : public unit_t<double, std::femto, temperature_dimension>
{
    using _base = unit_t<double, std::femto, temperature_dimension>;
    using _base::_base;
};

struct picokelvin final : public unit_t<double, std::pico, temperature_dimension>
{
    using _base = unit_t<double, std::pico, temperature_dimension>;
    using _base::_base;
};

struct nanokelvin final : public unit_t<double, std::nano, temperature_dimension>
{
    using _base = unit_t<double, std::nano, temperature_dimension>;
    using _base::_base;
};

struct microkelvin final : public unit_t<double, std::micro, temperature_dimension>
{
    using _base = unit_t<double, std::micro, temperature_dimension>;
    using _base::_base;
};

struct millikelvin final : public unit_t<double, std::milli, temperature_dimension>
{
    using _base = unit_t<double, std::milli, temperature_dimension>;
    using _base::_base;
};

struct centikelvin final : public unit_t<double, std::centi, temperature_dimension>
{
    using _base = unit_t<double, std::centi, temperature_dimension>;
    using _base::_base;
};

struct decikelvin final : public unit_t<double, std::deci, temperature_dimension>
{
    using _base = unit_t<double, std::deci, temperature_dimension>;
    using _base::_base;
};

struct decakelvin final : public unit_t<double, std::deca, temperature_dimension>
{
    using _base = unit_t<double, std::deca, temperature_dimension>;
    using _base::_base;
};

struct hectokelvin final : public unit_t<double, std::hecto, temperature_dimension>
{
    using _base = unit_t<double, std::hecto, temperature_dimension>;
    using _base::_base;
};

struct kilokelvin final : public unit_t<double, std::kilo, temperature_dimension>
{
    using _base = unit_t<double, std::kilo, temperature_dimension>;
    using _base::_base;
};

struct megakelvin final : public unit_t<double, std::mega, temperature_dimension>
{
    using _base = unit_t<double, std::mega, temperature_dimension>;
    using _base::_base;
};

PKR_SI_NAMESPACE_END


