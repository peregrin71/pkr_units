#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/density_decl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Density units (mass per volume)

// Base unit: kilogram per cubic meter (kg/m³)
struct kilogram_per_cubic_meter_t final : public details::unit_t<double, std::ratio<1, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilogram_per_cubic_meter"};
    static constexpr std::string_view symbol{"kg/m^3"};
    static constexpr std::wstring_view w_symbol{L"kg·m⁻³"};
    static constexpr std::u8string_view u8_symbol{u8"kg·m⁻³"};
};

struct gram_per_cubic_meter_t final : public details::unit_t<double, std::ratio<1, 1000>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_cubic_meter"};
    static constexpr std::string_view symbol{"g/m^3"};
    static constexpr std::wstring_view w_symbol{L"g·m⁻³"};
    static constexpr std::u8string_view u8_symbol{u8"g·m⁻³"};
};

struct gram_per_cubic_centimeter_t final : public details::unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_cubic_centimeter"};
    static constexpr std::string_view symbol{"g/cm^3"};
    static constexpr std::wstring_view w_symbol{L"g·cm⁻³"};
    static constexpr std::u8string_view u8_symbol{u8"g·cm⁻³"};
};

struct gram_per_milliliter_t final : public details::unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_milliliter"};
    static constexpr std::string_view symbol{"g/mL"};
    static constexpr std::wstring_view w_symbol{L"g·mL⁻¹"};
    static constexpr std::u8string_view u8_symbol{u8"g·mL⁻¹"};
};

struct kilogram_per_liter_t final : public details::unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilogram_per_liter"};
    static constexpr std::string_view symbol{"kg/L"};
    static constexpr std::wstring_view w_symbol{L"kg·L⁻¹"};
    static constexpr std::u8string_view u8_symbol{u8"kg·L⁻¹"};
};

struct gram_per_liter_t final : public details::unit_t<double, std::ratio<1, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram_per_liter"};
    static constexpr std::string_view symbol{"g/L"};
    static constexpr std::wstring_view w_symbol{L"g·L⁻¹"};
    static constexpr std::u8string_view u8_symbol{u8"g·L⁻¹"};
};

struct milligram_per_cubic_centimeter_t final : public details::unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milligram_per_cubic_centimeter"};
    static constexpr std::string_view symbol{"mg/cm^3"};
    static constexpr std::wstring_view w_symbol{L"mg·cm⁻³"};
    static constexpr std::u8string_view u8_symbol{u8"mg·cm⁻³"};
};

struct milligram_per_milliliter_t final : public details::unit_t<double, std::ratio<1000, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milligram_per_milliliter"};
    static constexpr std::string_view symbol{"mg/mL"};
    static constexpr std::wstring_view w_symbol{L"mg·mL⁻¹"};
    static constexpr std::u8string_view u8_symbol{u8"mg·mL⁻¹"};
};

// Other common density units
struct ton_per_cubic_meter_t final : public details::unit_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ton_per_cubic_meter"};
    static constexpr std::string_view symbol{"t/m^3"};
    static constexpr std::wstring_view w_symbol{L"t·m⁻³"};
    static constexpr std::u8string_view u8_symbol{u8"t·m⁻³"};
};

struct atomic_mass_unit_per_cubic_angstrom_t final : public details::unit_t<double, std::ratio<166054, 1>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<166054, 1>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"atomic_mass_unit_per_cubic_angstrom"};
    static constexpr std::string_view symbol{"u/A^3"};
    static constexpr std::wstring_view w_symbol{L"u·Å⁻³"};
    static constexpr std::u8string_view u8_symbol{u8"u·Å⁻³"};
};

// ============================================================================
// Most derived unit type specializations for density units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, density_dimension>
{
    using type = kilogram_per_cubic_meter_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, density_dimension>
{
    using type = gram_per_cubic_meter_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, density_dimension>
{
    using type = gram_per_cubic_centimeter_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, density_dimension>
{
    using type = kilogram_per_liter_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<166054, 1>, density_dimension>
{
    using type = atomic_mass_unit_per_cubic_angstrom_t;
};

} // namespace PKR_UNITS_NAMESPACE
