#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Energy dimension: kg·m²·s⁻² (M·L²·T⁻²)
inline constexpr dimension_t energy_dimension{2, 1, -2, 0, 0, 0, 0, 0};

// Energy units (Joule and derived)
// Base unit: Joule (J) = kg·m²·s⁻²

struct joule_t final : public details::unit_t<double, std::ratio<1, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"joule"};

    [[maybe_unused]] static constexpr std::string_view symbol{"J"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"J"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"J"};
};

struct kilojoule_t final : public details::unit_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilojoule"};

    [[maybe_unused]] static constexpr std::string_view symbol{"kJ"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kJ"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kJ"};
};

struct megajoule_t final : public details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megajoule"};

    [[maybe_unused]] static constexpr std::string_view symbol{"MJ"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MJ"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MJ"};
};

struct gigajoule_t final : public details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigajoule"};

    [[maybe_unused]] static constexpr std::string_view symbol{"GJ"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GJ"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GJ"};
};

struct microjoule_t final : public details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microjoule"};

    [[maybe_unused]] static constexpr std::string_view symbol{"uJ"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5J"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5J"};
};

struct millijoule_t final : public details::unit_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millijoule"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mJ"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mJ"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mJ"};
};

struct nanojoule_t final : public details::unit_t<double, std::ratio<1, 1000000000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanojoule"};

    [[maybe_unused]] static constexpr std::string_view symbol{"nJ"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nJ"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nJ"};
};

struct calorie_t final : public details::unit_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<4184, 1000>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"calorie"};

    [[maybe_unused]] static constexpr std::string_view symbol{"cal"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cal"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cal"};
};

struct kilocalorie_t final : public details::unit_t<double, std::ratio<4184, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<4184, 1>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilocalorie"};

    [[maybe_unused]] static constexpr std::string_view symbol{"kcal"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kcal"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kcal"};
};

struct watt_hour_t final : public details::unit_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600, 1>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"watt_hour"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Wh"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Wh"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Wh"};
};

struct kilowatt_hour_t final : public details::unit_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600000, 1>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilowatt_hour"};

    [[maybe_unused]] static constexpr std::string_view symbol{"kWh"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kWh"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kWh"};
};

// Electronvolt-based units
// 1 eV = 1.602176634e-19 J (exact). Ratio chosen to fit std::ratio limits.
struct electronvolt_t final : public details::unit_t<double, std::ratio<1, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 6241509074460762607>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"electronvolt"};

    [[maybe_unused]] static constexpr std::string_view symbol{"eV"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"eV"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"eV"};
};

struct kiloelectronvolt_t final : public details::unit_t<double, std::ratio<1000, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 6241509074460762607>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kiloelectronvolt"};

    [[maybe_unused]] static constexpr std::string_view symbol{"keV"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"keV"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"keV"};
};

struct megaelectronvolt_t final : public details::unit_t<double, std::ratio<1000000, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 6241509074460762607>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megaelectronvolt"};

    [[maybe_unused]] static constexpr std::string_view symbol{"MeV"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MeV"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MeV"};
};

struct gigaelectronvolt_t final : public details::unit_t<double, std::ratio<1000000000, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 6241509074460762607>, energy_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigaelectronvolt"};

    [[maybe_unused]] static constexpr std::string_view symbol{"GeV"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GeV"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GeV"};
};

// Energy units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, energy_dimension>
{
    using type = joule_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using type = kilojoule_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using type = megajoule_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using type = gigajoule_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using type = microjoule_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using type = millijoule_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, energy_dimension>
{
    using type = nanojoule_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    using type = calorie_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<4184, 1>, energy_dimension>
{
    using type = kilocalorie_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using type = watt_hour_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using type = kilowatt_hour_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 6241509074460762607>, energy_dimension>
{
    using type = electronvolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 6241509074460762607>, energy_dimension>
{
    using type = kiloelectronvolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 6241509074460762607>, energy_dimension>
{
    using type = megaelectronvolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000000, 6241509074460762607>, energy_dimension>
{
    using type = gigaelectronvolt_t;
};

} // namespace PKR_UNITS_NAMESPACE
