#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Force dimension
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0};

// Pressure dimension
inline constexpr dimension_t pressure_dimension{-1, 1, -2, 0, 0, 0, 0};

// Energy dimension
inline constexpr dimension_t energy_dimension{2, 1, -2, 0, 0, 0, 0};

// Power dimension
inline constexpr dimension_t power_dimension{2, 1, -3, 0, 0, 0, 0};

// Force units (Newton and derived)
// Base unit: Newton (N) = kg·m·s⁻²
using namespace_force_units_detail = int; // Force namespace detail

struct newton final : public unit_t<double, std::ratio<1, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, force_dimension>;
    using _base::_base;
};

struct kilonewton final : public unit_t<double, std::ratio<1000, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;
};

struct meganewton final : public unit_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;
};

struct micronewton final : public unit_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;
};

struct millinewton final : public unit_t<double, std::ratio<1, 1000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;
};

struct nanonewton final : public unit_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, force_dimension>;
    using _base::_base;
};

// Pressure units (Pascal and derived)
// Base unit: Pascal (Pa) = kg·m⁻¹·s⁻²

struct pascal final : public unit_t<double, std::ratio<1, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, pressure_dimension>;
    using _base::_base;
};

struct hectopascal final : public unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
};

struct kilopascal final : public unit_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;
};

struct megapascal final : public unit_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;
};

struct micropascal final : public unit_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;
};

struct millibar final : public unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
};

struct bar final : public unit_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;
};

struct atmosphere final : public unit_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<101325, 1>, pressure_dimension>;
    using _base::_base;
};

struct psi final : public unit_t<double, std::ratio<6894757293, 1000000000>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<6894757293, 1000000000>, pressure_dimension>;
    using _base::_base;
};

// Energy units (Joule and derived)
// Base unit: Joule (J) = kg·m²·s⁻²

struct joule final : public unit_t<double, std::ratio<1, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, energy_dimension>;
    using _base::_base;
};

struct kilojoule final : public unit_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;
};

struct megajoule final : public unit_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;
};

struct gigajoule final : public unit_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;
};

struct millijoule final : public unit_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;
};

struct microjoule final : public unit_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;
};

struct calorie final : public unit_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<4184, 1000>, energy_dimension>;
    using _base::_base;
};

struct kilocalorie final : public unit_t<double, std::ratio<4184, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<4184, 1>, energy_dimension>;
    using _base::_base;
};

struct watthour final : public unit_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<3600, 1>, energy_dimension>;
    using _base::_base;
};

struct kilowatthour final : public unit_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<3600000, 1>, energy_dimension>;
    using _base::_base;
};

struct electronvolt final : public unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
};

struct kiloelectronvolt final : public unit_t<double, std::ratio<80108000, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108000, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
};

struct megaelectronvolt final : public unit_t<double, std::ratio<80108000000, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108000000, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
};

struct gigaelectronvolt final : public unit_t<double, std::ratio<80108000000000LL, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108000000000LL, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
};

// Power units (Watt and derived)
// Base unit: Watt (W) = kg·m²·s⁻³

struct watt final : public unit_t<double, std::ratio<1, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, power_dimension>;
    using _base::_base;
};

struct kilowatt final : public unit_t<double, std::ratio<1000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;
};

struct megawatt final : public unit_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;
};

struct gigawatt final : public unit_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;
};

struct milliwatt final : public unit_t<double, std::ratio<1, 1000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;
};

struct microwatt final : public unit_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;
};

struct nanowatt final : public unit_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;
};

struct horsepower final : public unit_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;
};

} // PKR_SI_NAMESPACE








