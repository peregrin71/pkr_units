#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/density/details/density_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Density quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using density = unit_t<type_t, ratio_t, density_dimension>;

// Density units (mass per volume)

// Base unit: kilogram per cubic meter (kg/m³)
struct kilogram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, density_dimension>;
    using _base::_base;
};

struct gram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, density_dimension>;
    using _base::_base;
};

struct gram_per_cubic_centimeter final : public unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
};

struct gram_per_milliliter final : public unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
};

struct kilogram_per_liter final : public unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
};

struct gram_per_liter final : public unit_t<double, std::ratio<1, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, density_dimension>;
    using _base::_base;
};

struct milligram_per_cubic_centimeter final : public unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
};

struct milligram_per_milliliter final : public unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
};

// Imperial density units
struct pound_per_cubic_inch final : public unit_t<double, std::ratio<27679904, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<27679904, 1000000>, density_dimension>;
    using _base::_base;
};

struct pound_per_cubic_foot final : public unit_t<double, std::ratio<16018, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<16018, 1000000>, density_dimension>;
    using _base::_base;
};

struct pound_per_gallon final : public unit_t<double, std::ratio<119826, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<119826, 1000000>, density_dimension>;
    using _base::_base;
};

struct ounce_per_cubic_inch final : public unit_t<double, std::ratio<1729994, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1729994, 1000000>, density_dimension>;
    using _base::_base;
};

struct ounce_per_fluid_ounce final : public unit_t<double, std::ratio<33814, 1000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<33814, 1000>, density_dimension>;
    using _base::_base;
};

// Other common density units
struct ton_per_cubic_meter final : public unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
};

struct atomic_mass_unit_per_cubic_angstrom final : public unit_t<double, std::ratio<166054, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<166054, 1>, density_dimension>;
    using _base::_base;
};

} // PKR_SI_NAMESPACE








