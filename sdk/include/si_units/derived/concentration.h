#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/concentration/details/concentration_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Mass concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_concentration = unit_t<type_t, ratio_t, mass_concentration_v>;

// Molar concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using molar_concentration = unit_t<type_t, ratio_t, molar_concentration_v>;

// Mass concentration units (mass per volume)

// Base unit: kilogram per cubic meter (kg/m³)
struct kilogram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, mass_concentration_v>;
    using _base::_base;
};

struct gram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000>, mass_concentration_v>;
    using _base::_base;
};

struct gram_per_liter final : public unit_t<double, std::ratio<1, 1>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, mass_concentration_v>;
    using _base::_base;
};

struct milligram_per_liter final : public unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;
    using _base::_base;
};

struct milligram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;
    using _base::_base;
};

struct microgram_per_liter final : public unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;
    using _base::_base;
};

struct microgram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;
    using _base::_base;
};

// Parts per million (by mass) - ppm
struct parts_per_million final : public unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;
    using _base::_base;
};

// Parts per billion (by mass) - ppb
struct parts_per_billion final : public unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;
    using _base::_base;
};

// Molar concentration units (amount of substance per volume)

// Base unit: mole per cubic meter (mol/m³)
struct mole_per_cubic_meter final : public unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
};

struct mole_per_liter final : public unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
};

struct molar final : public unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
};

struct millimolar final : public unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
};

struct micromolar final : public unit_t<double, std::ratio<1, 1000>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000>, molar_concentration_v>;
    using _base::_base;
};

struct nanomolar final : public unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>;
    using _base::_base;
};

struct picomolar final : public unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>;
    using _base::_base;
};

struct mole_per_cubic_centimeter final : public unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>;
    using _base::_base;
};

struct mole_per_milliliter final : public unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>;
    using _base::_base;
};

// Osmolarity units (moles of osmotically active particles per liter)
struct osmole_per_liter final : public unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
};

struct milliosmole_per_liter final : public unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
};

} // PKR_SI_NAMESPACE








