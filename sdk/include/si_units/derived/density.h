#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Density dimension: kg·m⁻³
inline constexpr dimension_t density_dimension{.mass = 1, .length = -3};

// Density quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using density = unit_t<type_t, ratio_t, density_dimension>;

// Density units (mass per volume)

// Base unit: kilogram per cubic meter (kg/m³)
struct kilogram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilogram_per_cubic_meter"};
    static constexpr std::string_view symbol{"kg/m³"};
    static constexpr std::wstring_view w_symbol{L"kg/m³"};
    static constexpr std::u8string_view u8_symbol{u8"kg/m³"};
};

struct gram_per_cubic_meter final : public unit_t<double, std::ratio<1, 1000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_cubic_meter"};
    static constexpr std::string_view symbol{"g/m³"};
    static constexpr std::wstring_view w_symbol{L"g/m³"};
    static constexpr std::u8string_view u8_symbol{u8"g/m³"};
};

struct gram_per_cubic_centimeter final : public unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_cubic_centimeter"};
    static constexpr std::string_view symbol{"g/cm³"};
    static constexpr std::wstring_view w_symbol{L"g/cm³"};
    static constexpr std::u8string_view u8_symbol{u8"g/cm³"};
};

struct gram_per_milliliter final : public unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_milliliter"};
    static constexpr std::string_view symbol{"g/mL"};
    static constexpr std::wstring_view w_symbol{L"g/mL"};
    static constexpr std::u8string_view u8_symbol{u8"g/mL"};
};

struct kilogram_per_liter final : public unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilogram_per_liter"};
    static constexpr std::string_view symbol{"kg/L"};
    static constexpr std::wstring_view w_symbol{L"kg/L"};
    static constexpr std::u8string_view u8_symbol{u8"kg/L"};
};

struct gram_per_liter final : public unit_t<double, std::ratio<1, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_liter"};
    static constexpr std::string_view symbol{"g/L"};
    static constexpr std::wstring_view w_symbol{L"g/L"};
    static constexpr std::u8string_view u8_symbol{u8"g/L"};
};

struct milligram_per_cubic_centimeter final : public unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milligram_per_cubic_centimeter"};
    static constexpr std::string_view symbol{"mg/cm³"};
    static constexpr std::wstring_view w_symbol{L"mg/cm³"};
    static constexpr std::u8string_view u8_symbol{u8"mg/cm³"};
};

struct milligram_per_milliliter final : public unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milligram_per_milliliter"};
    static constexpr std::string_view symbol{"mg/mL"};
    static constexpr std::wstring_view w_symbol{L"mg/mL"};
    static constexpr std::u8string_view u8_symbol{u8"mg/mL"};
};

// Imperial density units
struct pound_per_cubic_inch final : public unit_t<double, std::ratio<27679904, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<27679904, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound_per_cubic_inch"};
    static constexpr std::string_view symbol{"lb/in³"};
    static constexpr std::wstring_view w_symbol{L"lb/in³"};
    static constexpr std::u8string_view u8_symbol{u8"lb/in³"};
};

struct pound_per_cubic_foot final : public unit_t<double, std::ratio<16018, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<16018, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound_per_cubic_foot"};
    static constexpr std::string_view symbol{"lb/ft³"};
    static constexpr std::wstring_view w_symbol{L"lb/ft³"};
    static constexpr std::u8string_view u8_symbol{u8"lb/ft³"};
};

struct pound_per_gallon final : public unit_t<double, std::ratio<119826, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<119826, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound_per_gallon"};
    static constexpr std::string_view symbol{"lb/gal"};
    static constexpr std::wstring_view w_symbol{L"lb/gal"};
    static constexpr std::u8string_view u8_symbol{u8"lb/gal"};
};

struct ounce_per_cubic_inch final : public unit_t<double, std::ratio<1729994, 1000000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1729994, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ounce_per_cubic_inch"};
    static constexpr std::string_view symbol{"oz/in³"};
    static constexpr std::wstring_view w_symbol{L"oz/in³"};
    static constexpr std::u8string_view u8_symbol{u8"oz/in³"};
};

struct ounce_per_fluid_ounce final : public unit_t<double, std::ratio<33814, 1000>, density_dimension>
{
    using _base = unit_t<double, std::ratio<33814, 1000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ounce_per_fluid_ounce"};
    static constexpr std::string_view symbol{"oz/fl oz"};
    static constexpr std::wstring_view w_symbol{L"oz/fl oz"};
    static constexpr std::u8string_view u8_symbol{u8"oz/fl oz"};
};

// Other common density units
struct ton_per_cubic_meter final : public unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ton_per_cubic_meter"};
    static constexpr std::string_view symbol{"t/m³"};
    static constexpr std::wstring_view w_symbol{L"t/m³"};
    static constexpr std::u8string_view u8_symbol{u8"t/m³"};
};

struct atomic_mass_unit_per_cubic_angstrom final : public unit_t<double, std::ratio<166054, 1>, density_dimension>
{
    using _base = unit_t<double, std::ratio<166054, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"atomic_mass_unit_per_cubic_angstrom"};
    static constexpr std::string_view symbol{"u/Ų"};
    static constexpr std::wstring_view w_symbol{L"u/Ų"};
    static constexpr std::u8string_view u8_symbol{u8"u/Ų"};
};

} // PKR_SI_NAMESPACE








