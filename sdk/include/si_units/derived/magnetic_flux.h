#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/magnetic_flux/details/magnetic_flux_units.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Magnetic flux quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux = unit_t<type_t, ratio_t, magnetic_flux_dimension>;

// Magnetic flux density quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux_density = unit_t<type_t, ratio_t, magnetic_flux_density_dimension>;

// Magnetic flux units (Weber and derived)
// Base unit: Weber (Wb) = kg·m²·s⁻²·A⁻¹

struct weber final : public unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>;
    using _base::_base;
};

struct milliweber final : public unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>;
    using _base::_base;
};

struct microweber final : public unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>;
    using _base::_base;
};

struct nanoweber final : public unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>;
    using _base::_base;
};

struct kiloweber final : public unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>;
    using _base::_base;
};

// Magnetic flux density units (Tesla and derived)
// Base unit: Tesla (T) = kg·s⁻²·A⁻¹

struct tesla final : public unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
};

struct millitesla final : public unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>;
    using _base::_base;
};

struct microtesla final : public unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>;
    using _base::_base;
};

struct nanotesla final : public unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>;
    using _base::_base;
};

struct kilotesla final : public unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
};

struct megatesla final : public unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
};

} // PKR_SI_NAMESPACE








