#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/unit.h"
#include "../impl/common/dimension.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Force dimension: kg·m·s⁻² (M·L·T⁻²)
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0};

// Pressure dimension: kg·m⁻¹·s⁻² (M·L⁻¹·T⁻²)
inline constexpr dimension_t pressure_dimension{1, -1, -2, 0, 0, 0, 0};

// Energy dimension: kg·m²·s⁻² (M·L²·T⁻²)
inline constexpr dimension_t energy_dimension{1, 2, -2, 0, 0, 0, 0};

// Power dimension: kg·m²·s⁻³ (M·L²·T⁻³)
inline constexpr dimension_t power_dimension{1, 2, -3, 0, 0, 0, 0};

// Base unit: Newton (N) = kg·m·s⁻²
using namespace_force_units_detail = int; // Force namespace detail

struct newton final : public details::unit_t<double, std::ratio<1, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"newton"};
    static constexpr std::string_view symbol{"N"};
    static constexpr std::wstring_view w_symbol{L"N"};
    static constexpr std::u8string_view u8_symbol{u8"N"};
};

struct kilonewton final : public details::unit_t<double, std::ratio<1000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilonewton"};
    static constexpr std::string_view symbol{"kN"};
    static constexpr std::wstring_view w_symbol{L"kN"};
    static constexpr std::u8string_view u8_symbol{u8"kN"};
};

struct meganewton final : public details::unit_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"meganewton"};
    static constexpr std::string_view symbol{"MN"};
    static constexpr std::wstring_view w_symbol{L"MN"};
    static constexpr std::u8string_view u8_symbol{u8"MN"};
};

struct micronewton final : public details::unit_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micronewton"};
    static constexpr std::string_view symbol{"µN"};
    static constexpr std::wstring_view w_symbol{L"µN"};
    static constexpr std::u8string_view u8_symbol{u8"µN"};
};

struct millinewton final : public details::unit_t<double, std::ratio<1, 1000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millinewton"};
    static constexpr std::string_view symbol{"mN"};
    static constexpr std::wstring_view w_symbol{L"mN"};
    static constexpr std::u8string_view u8_symbol{u8"mN"};
};

struct nanonewton final : public details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanonewton"};
    static constexpr std::string_view symbol{"nN"};
    static constexpr std::wstring_view w_symbol{L"nN"};
    static constexpr std::u8string_view u8_symbol{u8"nN"};
};

// Pressure units (Pascal and derived)
// Base unit: Pascal (Pa) = kg·m⁻¹·s⁻²

struct pascal final : public details::unit_t<double, std::ratio<1, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pascal"};
    static constexpr std::string_view symbol{"Pa"};
    static constexpr std::wstring_view w_symbol{L"Pa"};
    static constexpr std::u8string_view u8_symbol{u8"Pa"};
};

struct kilopascal final : public details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilopascal"};
    static constexpr std::string_view symbol{"kPa"};
    static constexpr std::wstring_view w_symbol{L"kPa"};
    static constexpr std::u8string_view u8_symbol{u8"kPa"};
};

struct megapascal final : public details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megapascal"};
    static constexpr std::string_view symbol{"MPa"};
    static constexpr std::wstring_view w_symbol{L"MPa"};
    static constexpr std::u8string_view u8_symbol{u8"MPa"};
};

struct micropascal final : public details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micropascal"};
    static constexpr std::string_view symbol{"µPa"};
    static constexpr std::wstring_view w_symbol{L"µPa"};
    static constexpr std::u8string_view u8_symbol{u8"µPa"};
};

struct millipascal final : public details::unit_t<double, std::ratio<1, 1000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millipascal"};
    static constexpr std::string_view symbol{"mPa"};
    static constexpr std::wstring_view w_symbol{L"mPa"};
    static constexpr std::u8string_view u8_symbol{u8"mPa"};
};

struct nanopascal final : public details::unit_t<double, std::ratio<1, 1000000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanopascal"};
    static constexpr std::string_view symbol{"nPa"};
    static constexpr std::wstring_view w_symbol{L"nPa"};
    static constexpr std::u8string_view u8_symbol{u8"nPa"};
};

struct bar final : public details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"bar"};
    static constexpr std::string_view symbol{"bar"};
    static constexpr std::wstring_view w_symbol{L"bar"};
    static constexpr std::u8string_view u8_symbol{u8"bar"};
};

struct atmosphere final : public details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"atmosphere"};
    static constexpr std::string_view symbol{"atm"};
    static constexpr std::wstring_view w_symbol{L"atm"};
    static constexpr std::u8string_view u8_symbol{u8"atm"};
};

struct psi final : public details::unit_t<double, std::ratio<6894757, 1000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<6894757, 1000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"psi"};
    static constexpr std::string_view symbol{"psi"};
    static constexpr std::wstring_view w_symbol{L"psi"};
    static constexpr std::u8string_view u8_symbol{u8"psi"};
};

// Energy units (Joule and derived)
// Base unit: Joule (J) = kg·m²·s⁻²

struct joule final : public details::unit_t<double, std::ratio<1, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"joule"};
    static constexpr std::string_view symbol{"J"};
    static constexpr std::wstring_view w_symbol{L"J"};
    static constexpr std::u8string_view u8_symbol{u8"J"};
};

struct kilojoule final : public details::unit_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilojoule"};
    static constexpr std::string_view symbol{"kJ"};
    static constexpr std::wstring_view w_symbol{L"kJ"};
    static constexpr std::u8string_view u8_symbol{u8"kJ"};
};

struct megajoule final : public details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megajoule"};
    static constexpr std::string_view symbol{"MJ"};
    static constexpr std::wstring_view w_symbol{L"MJ"};
    static constexpr std::u8string_view u8_symbol{u8"MJ"};
};

struct gigajoule final : public details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigajoule"};
    static constexpr std::string_view symbol{"GJ"};
    static constexpr std::wstring_view w_symbol{L"GJ"};
    static constexpr std::u8string_view u8_symbol{u8"GJ"};
};

struct microjoule final : public details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microjoule"};
    static constexpr std::string_view symbol{"µJ"};
    static constexpr std::wstring_view w_symbol{L"µJ"};
    static constexpr std::u8string_view u8_symbol{u8"µJ"};
};

struct millijoule final : public details::unit_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millijoule"};
    static constexpr std::string_view symbol{"mJ"};
    static constexpr std::wstring_view w_symbol{L"mJ"};
    static constexpr std::u8string_view u8_symbol{u8"mJ"};
};

struct nanojoule final : public details::unit_t<double, std::ratio<1, 1000000000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanojoule"};
    static constexpr std::string_view symbol{"nJ"};
    static constexpr std::wstring_view w_symbol{L"nJ"};
    static constexpr std::u8string_view u8_symbol{u8"nJ"};
};

struct calorie final : public details::unit_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<4184, 1000>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"calorie"};
    static constexpr std::string_view symbol{"cal"};
    static constexpr std::wstring_view w_symbol{L"cal"};
    static constexpr std::u8string_view u8_symbol{u8"cal"};
};

struct kilocalorie final : public details::unit_t<double, std::ratio<4184, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<4184, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilocalorie"};
    static constexpr std::string_view symbol{"kcal"};
    static constexpr std::wstring_view w_symbol{L"kcal"};
    static constexpr std::u8string_view u8_symbol{u8"kcal"};
};

struct watt_hour final : public details::unit_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"watt_hour"};
    static constexpr std::string_view symbol{"Wh"};
    static constexpr std::wstring_view w_symbol{L"Wh"};
    static constexpr std::u8string_view u8_symbol{u8"Wh"};
};

struct kilowatt_hour final : public details::unit_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilowatt_hour"};
    static constexpr std::string_view symbol{"kWh"};
    static constexpr std::wstring_view w_symbol{L"kWh"};
    static constexpr std::u8string_view u8_symbol{u8"kWh"};
};

// Power units (Watt and derived)
// Base unit: Watt (W) = kg·m²·s⁻³

struct watt final : public details::unit_t<double, std::ratio<1, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"watt"};
    static constexpr std::string_view symbol{"W"};
    static constexpr std::wstring_view w_symbol{L"W"};
    static constexpr std::u8string_view u8_symbol{u8"W"};
};

struct kilowatt final : public details::unit_t<double, std::ratio<1000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilowatt"};
    static constexpr std::string_view symbol{"kW"};
    static constexpr std::wstring_view w_symbol{L"kW"};
    static constexpr std::u8string_view u8_symbol{u8"kW"};
};

struct megawatt final : public details::unit_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megawatt"};
    static constexpr std::string_view symbol{"MW"};
    static constexpr std::wstring_view w_symbol{L"MW"};
    static constexpr std::u8string_view u8_symbol{u8"MW"};
};

struct gigawatt final : public details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigawatt"};
    static constexpr std::string_view symbol{"GW"};
    static constexpr std::wstring_view w_symbol{L"GW"};
    static constexpr std::u8string_view u8_symbol{u8"GW"};
};

struct microwatt final : public details::unit_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microwatt"};
    static constexpr std::string_view symbol{"µW"};
    static constexpr std::wstring_view w_symbol{L"µW"};
    static constexpr std::u8string_view u8_symbol{u8"µW"};
};

struct milliwatt final : public details::unit_t<double, std::ratio<1, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliwatt"};
    static constexpr std::string_view symbol{"mW"};
    static constexpr std::wstring_view w_symbol{L"mW"};
    static constexpr std::u8string_view u8_symbol{u8"mW"};
};

struct nanowatt final : public details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanowatt"};
    static constexpr std::string_view symbol{"nW"};
    static constexpr std::wstring_view w_symbol{L"nW"};
    static constexpr std::u8string_view u8_symbol{u8"nW"};
};

struct horsepower final : public details::unit_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"horsepower"};
    static constexpr std::string_view symbol{"hp"};
    static constexpr std::wstring_view w_symbol{L"hp"};
    static constexpr std::u8string_view u8_symbol{u8"hp"};
};

}  // namespace PKR_UNITS_NAMESPACE








