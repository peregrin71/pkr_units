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
    static constexpr std::string_view name{"newton"};
    static constexpr std::string_view symbol{"N"};
    static constexpr std::wstring_view w_symbol{L"N"};
    static constexpr std::u8string_view u8_symbol{u8"N"};
};

struct kilonewton final : public unit_t<double, std::ratio<1000, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilonewton"};
    static constexpr std::string_view symbol{"kN"};
    static constexpr std::wstring_view w_symbol{L"kN"};
    static constexpr std::u8string_view u8_symbol{u8"kN"};
};

struct meganewton final : public unit_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"meganewton"};
    static constexpr std::string_view symbol{"MN"};
    static constexpr std::wstring_view w_symbol{L"MN"};
    static constexpr std::u8string_view u8_symbol{u8"MN"};
};

    static constexpr std::string_view name{"micronewton"};
    static constexpr std::string_view symbol{"µN"};
    static constexpr std::wstring_view w_symbol{L"µN"};
    static constexpr std::u8string_view u8_symbol{u8"µN"};
struct micronewton final : public unit_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"millinewton"};
    static constexpr std::string_view symbol{"mN"};
    static constexpr std::wstring_view w_symbol{L"mN"};
    static constexpr std::u8string_view u8_symbol{u8"mN"};
struct millinewton final : public unit_t<double, std::ratio<1, 1000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"nanonewton"};
    static constexpr std::string_view symbol{"nN"};
    static constexpr std::wstring_view w_symbol{L"nN"};
    static constexpr std::u8string_view u8_symbol{u8"nN"};
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
    static constexpr std::string_view name{"pascal"};
    static constexpr std::string_view symbol{"Pa"};
    static constexpr std::wstring_view w_symbol{L"Pa"};
    static constexpr std::u8string_view u8_symbol{u8"Pa"};
};

struct hectopascal final : public unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectopascal"};
    static constexpr std::string_view symbol{"hPa"};
    static constexpr std::wstring_view w_symbol{L"hPa"};
    static constexpr std::u8string_view u8_symbol{u8"hPa"};
};

struct kilopascal final : public unit_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilopascal"};
    static constexpr std::string_view symbol{"kPa"};
    static constexpr std::wstring_view w_symbol{L"kPa"};
    static constexpr std::u8string_view u8_symbol{u8"kPa"};
};

    static constexpr std::string_view name{"megapascal"};
    static constexpr std::string_view symbol{"MPa"};
    static constexpr std::wstring_view w_symbol{L"MPa"};
    static constexpr std::u8string_view u8_symbol{u8"MPa"};
struct megapascal final : public unit_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"micropascal"};
    static constexpr std::string_view symbol{"µPa"};
    static constexpr std::wstring_view w_symbol{L"µPa"};
    static constexpr std::u8string_view u8_symbol{u8"µPa"};
struct micropascal final : public unit_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"millibar"};
    static constexpr std::string_view symbol{"mbar"};
    static constexpr std::wstring_view w_symbol{L"mbar"};
    static constexpr std::u8string_view u8_symbol{u8"mbar"};
struct millibar final : public unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    static constexpr std::string_view name{"bar"};
    static constexpr std::string_view symbol{"bar"};
    static constexpr std::wstring_view w_symbol{L"bar"};
    static constexpr std::u8string_view u8_symbol{u8"bar"};
    using _base = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
};

struct bar final : public unit_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    static constexpr std::string_view name{"atmosphere"};
    static constexpr std::string_view symbol{"atm"};
    static constexpr std::wstring_view w_symbol{L"atm"};
    static constexpr std::u8string_view u8_symbol{u8"atm"};
    using _base = unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;
};

struct atmosphere final : public unit_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    static constexpr std::string_view name{"psi"};
    static constexpr std::string_view symbol{"psi"};
    static constexpr std::wstring_view w_symbol{L"psi"};
    static constexpr std::u8string_view u8_symbol{u8"psi"};
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
    static constexpr std::string_view name{"joule"};
    static constexpr std::string_view symbol{"J"};
    static constexpr std::wstring_view w_symbol{L"J"};
    static constexpr std::u8string_view u8_symbol{u8"J"};
};

struct kilojoule final : public unit_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilojoule"};
    static constexpr std::string_view symbol{"kJ"};
    static constexpr std::wstring_view w_symbol{L"kJ"};
    static constexpr std::u8string_view u8_symbol{u8"kJ"};
};

struct megajoule final : public unit_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megajoule"};
    static constexpr std::string_view symbol{"MJ"};
    static constexpr std::wstring_view w_symbol{L"MJ"};
    static constexpr std::u8string_view u8_symbol{u8"MJ"};
};

    static constexpr std::string_view name{"gigajoule"};
    static constexpr std::string_view symbol{"GJ"};
    static constexpr std::wstring_view w_symbol{L"GJ"};
    static constexpr std::u8string_view u8_symbol{u8"GJ"};
struct gigajoule final : public unit_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"millijoule"};
    static constexpr std::string_view symbol{"mJ"};
    static constexpr std::wstring_view w_symbol{L"mJ"};
    static constexpr std::u8string_view u8_symbol{u8"mJ"};
struct millijoule final : public unit_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"microjoule"};
    static constexpr std::string_view symbol{"µJ"};
    static constexpr std::wstring_view w_symbol{L"µJ"};
    static constexpr std::u8string_view u8_symbol{u8"µJ"};
struct microjoule final : public unit_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    static constexpr std::string_view name{"calorie"};
    static constexpr std::string_view symbol{"cal"};
    static constexpr std::wstring_view w_symbol{L"cal"};
    static constexpr std::u8string_view u8_symbol{u8"cal"};
    using _base = unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;
};

struct calorie final : public unit_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    static constexpr std::string_view name{"kilocalorie"};
    static constexpr std::string_view symbol{"kcal"};
    static constexpr std::wstring_view w_symbol{L"kcal"};
    static constexpr std::u8string_view u8_symbol{u8"kcal"};
    using _base = unit_t<double, std::ratio<4184, 1000>, energy_dimension>;
    using _base::_base;
};

struct kilocalorie final : public unit_t<double, std::ratio<4184, 1>, energy_dimension>
{
    static constexpr std::string_view name{"watthour"};
    static constexpr std::string_view symbol{"Wh"};
    static constexpr std::wstring_view w_symbol{L"Wh"};
    static constexpr std::u8string_view u8_symbol{u8"Wh"};
    using _base = unit_t<double, std::ratio<4184, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilowatthour"};
    static constexpr std::string_view symbol{"kWh"};
    static constexpr std::wstring_view w_symbol{L"kWh"};
    static constexpr std::u8string_view u8_symbol{u8"kWh"};
};

struct watthour final : public unit_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<3600, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"electronvolt"};
    static constexpr std::string_view symbol{"eV"};
    static constexpr std::wstring_view w_symbol{L"eV"};
    static constexpr std::u8string_view u8_symbol{u8"eV"};
};

struct kilowatthour final : public unit_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<3600000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kiloelectronvolt"};
    static constexpr std::string_view symbol{"keV"};
    static constexpr std::wstring_view w_symbol{L"keV"};
    static constexpr std::u8string_view u8_symbol{u8"keV"};
};

    static constexpr std::string_view name{"megaelectronvolt"};
    static constexpr std::string_view symbol{"MeV"};
    static constexpr std::wstring_view w_symbol{L"MeV"};
    static constexpr std::u8string_view u8_symbol{u8"MeV"};
struct electronvolt final : public unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"gigaelectronvolt"};
    static constexpr std::string_view symbol{"GeV"};
    static constexpr std::wstring_view w_symbol{L"GeV"};
    static constexpr std::u8string_view u8_symbol{u8"GeV"};
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
    static constexpr std::string_view name{"watt"};
    static constexpr std::string_view symbol{"W"};
    static constexpr std::wstring_view w_symbol{L"W"};
    static constexpr std::u8string_view u8_symbol{u8"W"};
};

struct kilowatt final : public unit_t<double, std::ratio<1000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilowatt"};
    static constexpr std::string_view symbol{"kW"};
    static constexpr std::wstring_view w_symbol{L"kW"};
    static constexpr std::u8string_view u8_symbol{u8"kW"};
};

    static constexpr std::string_view name{"megawatt"};
    static constexpr std::string_view symbol{"MW"};
    static constexpr std::wstring_view w_symbol{L"MW"};
    static constexpr std::u8string_view u8_symbol{u8"MW"};
struct megawatt final : public unit_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;
};

    static constexpr std::string_view name{"gigawatt"};
    static constexpr std::string_view symbol{"GW"};
    static constexpr std::wstring_view w_symbol{L"GW"};
    static constexpr std::u8string_view u8_symbol{u8"GW"};
struct gigawatt final : public unit_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    static constexpr std::string_view name{"milliwatt"};
    static constexpr std::string_view symbol{"mW"};
    static constexpr std::wstring_view w_symbol{L"mW"};
    static constexpr std::u8string_view u8_symbol{u8"mW"};
    using _base = unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;
};

struct milliwatt final : public unit_t<double, std::ratio<1, 1000>, power_dimension>
{
    static constexpr std::string_view name{"microwatt"};
    static constexpr std::string_view symbol{"µW"};
    static constexpr std::wstring_view w_symbol{L"µW"};
    static constexpr std::u8string_view u8_symbol{u8"µW"};
    using _base = unit_t<double, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;
};

struct microwatt final : public unit_t<double, std::ratio<1, 1000000>, power_dimension>
{
    static constexpr std::string_view name{"nanowatt"};
    static constexpr std::string_view symbol{"nW"};
    static constexpr std::wstring_view w_symbol{L"nW"};
    static constexpr std::u8string_view u8_symbol{u8"nW"};
    using _base = unit_t<double, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;
};

struct nanowatt final : public unit_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    static constexpr std::string_view name{"horsepower"};
    static constexpr std::string_view symbol{"hp"};
    static constexpr std::wstring_view w_symbol{L"hp"};
    static constexpr std::u8string_view u8_symbol{u8"hp"};
    using _base = unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;
};

struct horsepower final : public unit_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;
};

} // PKR_SI_NAMESPACE








