#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/concentration_def.h"
#include <si_units/impl/details/dimension.h>

PKR_SI_BEGIN_NAMESPACE
{

// Mass concentration dimension: kg·m⁻³
inline constexpr dimension_t mass_concentration_v{.mass = 1, .length = -3};

// Molar concentration dimension: mol·m⁻³
inline constexpr dimension_t molar_concentration_v{.amount = 1, .length = -3};

// Mass concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_concentration_unit_t = unit_t<type_t, ratio_t, mass_concentration_v>;

// Molar concentration quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using molar_concentration_unit_t = unit_t<type_t, ratio_t, molar_concentration_v>;

// Mass concentration units (mass per volume)

// Base unit: kilogram per cubic meter (kg/m³)
struct kilogram_per_cubic_meter_t final : public unit_t<double, std::ratio<1, 1>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"kilogram_per_cubic_meter"};
    static constexpr std::string_view symbol{"kg/m^3"};
    static constexpr std::wstring_view w_symbol{L"kg/m³"};
    static constexpr std::u8string_view u8_symbol{u8"kg/m³"};
};

struct gram_per_cubic_meter_t final : public unit_t<double, std::ratio<1, 1000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_cubic_meter"};
    static constexpr std::string_view symbol{"g/m³"};
    static constexpr std::wstring_view w_symbol{L"g/m³"};
    static constexpr std::u8string_view u8_symbol{u8"g/m³"};
};

struct gram_per_liter_t final : public unit_t<double, std::ratio<1, 1>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_liter"};
    static constexpr std::string_view symbol{"g/L"};
    static constexpr std::wstring_view w_symbol{L"g/L"};
    static constexpr std::u8string_view u8_symbol{u8"g/L"};
};

struct milligram_per_liter_t final : public unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"milligram_per_liter"};
    static constexpr std::string_view symbol{"mg/L"};
    static constexpr std::wstring_view w_symbol{L"mg/L"};
    static constexpr std::u8string_view u8_symbol{u8"mg/L"};
};

struct milligram_per_cubic_meter_t final : public unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"milligram_per_cubic_meter"};
    static constexpr std::string_view symbol{"mg/m³"};
    static constexpr std::wstring_view w_symbol{L"mg/m³"};
    static constexpr std::u8string_view u8_symbol{u8"mg/m³"};
};

struct microgram_per_liter_t final : public unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"microgram_per_liter"};
    static constexpr std::string_view symbol{"µg/L"};
    static constexpr std::wstring_view w_symbol{L"µg/L"};
    static constexpr std::u8string_view u8_symbol{u8"µg/L"};
};

struct microgram_per_cubic_meter_t final : public unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"microgram_per_cubic_meter"};
    static constexpr std::string_view symbol{"µg/m³"};
    static constexpr std::wstring_view w_symbol{L"µg/m³"};
    static constexpr std::u8string_view u8_symbol{u8"µg/m³"};
};

// Parts per million (by mass) - ppm
struct parts_per_million_t final : public unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"parts_per_million"};
    static constexpr std::string_view symbol{"ppm"};
    static constexpr std::wstring_view w_symbol{L"ppm"};
    static constexpr std::u8string_view u8_symbol{u8"ppm"};
};

// Parts per billion (by mass) - ppb
struct parts_per_billion_t final : public unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"parts_per_billion"};
    static constexpr std::string_view symbol{"ppb"};
    static constexpr std::wstring_view w_symbol{L"ppb"};
    static constexpr std::u8string_view u8_symbol{u8"ppb"};
};

// Molar concentration units (amount of substance per volume)

// Base unit: mole per cubic meter (mol/m³)
struct mole_per_cubic_meter final : public unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_cubic_meter"};
    static constexpr std::string_view symbol{"mol/m^3"};
    static constexpr std::wstring_view w_symbol{L"mol/m³"};
    static constexpr std::u8string_view u8_symbol{u8"mol/m³"};
};

struct mole_per_liter final : public unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_liter"};
    static constexpr std::string_view symbol{"mol/L"};
    static constexpr std::wstring_view w_symbol{L"mol/L"};
    static constexpr std::u8string_view u8_symbol{u8"mol/L"};
};

struct molar final : public unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"molar"};
    static constexpr std::string_view symbol{"M"};
    static constexpr std::wstring_view w_symbol{L"M"};
    static constexpr std::u8string_view u8_symbol{u8"M"};
};

struct millimolar final : public unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"millimolar"};
    static constexpr std::string_view symbol{"mM"};
    static constexpr std::wstring_view w_symbol{L"mM"};
    static constexpr std::u8string_view u8_symbol{u8"mM"};
};

struct micromolar final : public unit_t<double, std::ratio<1, 1000>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"micromolar"};
    static constexpr std::string_view symbol{"µM"};
    static constexpr std::wstring_view w_symbol{L"µM"};
    static constexpr std::u8string_view u8_symbol{u8"µM"};
};

struct nanomolar final : public unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"nanomolar"};
    static constexpr std::string_view symbol{"nM"};
    static constexpr std::wstring_view w_symbol{L"nM"};
    static constexpr std::u8string_view u8_symbol{u8"nM"};
};

struct picomolar final : public unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"picomolar"};
    static constexpr std::string_view symbol{"pM"};
    static constexpr std::wstring_view w_symbol{L"pM"};
    static constexpr std::u8string_view u8_symbol{u8"pM"};
};

struct mole_per_cubic_centimeter final : public unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_cubic_centimeter"};
    static constexpr std::string_view symbol{"mol/cm³"};
    static constexpr std::wstring_view w_symbol{L"mol/cm³"};
    static constexpr std::u8string_view u8_symbol{u8"mol/cm³"};
};

struct mole_per_milliliter final : public unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"mole_per_milliliter"};
    static constexpr std::string_view symbol{"mol/mL"};
    static constexpr std::wstring_view w_symbol{L"mol/mL"};
    static constexpr std::u8string_view u8_symbol{u8"mol/mL"};
};

// Osmolarity units (moles of osmotically active particles per liter)
struct osmole_per_liter final : public unit_t<double, std::ratio<1000, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1000, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"osmole_per_liter"};
    static constexpr std::string_view symbol{"Osm/L"};
    static constexpr std::wstring_view w_symbol{L"Osm/L"};
    static constexpr std::u8string_view u8_symbol{u8"Osm/L"};
};

struct milliosmole_per_liter final : public unit_t<double, std::ratio<1, 1>, molar_concentration_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, molar_concentration_v>;
    using _base::_base;
    static constexpr std::string_view name{"milliosmole_per_liter"};
    static constexpr std::string_view symbol{"mOsm/L"};
    static constexpr std::wstring_view w_symbol{L"mOsm/L"};
    static constexpr std::u8string_view u8_symbol{u8"mOsm/L"};
};

} // PKR_SI_NAMESPACE








