#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Energy dimension: kg·m²·s⁻² (M·L²·T⁻²)
inline constexpr dimension_t energy_dimension{2, 1, -2, 0, 0, 0, 0, 0};

// Energy units (Joule and derived)
// Base unit: Joule (J) = kg·m²·s⁻²

struct joule_t final : public details::unit_t<double, std::ratio<1, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"joule"};
    static constexpr std::string_view symbol{"J"};
    static constexpr std::wstring_view w_symbol{L"J"};
    static constexpr std::u8string_view u8_symbol{u8"J"};
};

struct kilojoule_t final : public details::unit_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilojoule"};
    static constexpr std::string_view symbol{"kJ"};
    static constexpr std::wstring_view w_symbol{L"kJ"};
    static constexpr std::u8string_view u8_symbol{u8"kJ"};
};

struct megajoule_t final : public details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megajoule"};
    static constexpr std::string_view symbol{"MJ"};
    static constexpr std::wstring_view w_symbol{L"MJ"};
    static constexpr std::u8string_view u8_symbol{u8"MJ"};
};

struct gigajoule_t final : public details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigajoule"};
    static constexpr std::string_view symbol{"GJ"};
    static constexpr std::wstring_view w_symbol{L"GJ"};
    static constexpr std::u8string_view u8_symbol{u8"GJ"};
};

struct microjoule_t final : public details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microjoule"};
    static constexpr std::string_view symbol{"uJ"};
    static constexpr std::wstring_view w_symbol{L"µJ"};
    static constexpr std::u8string_view u8_symbol{u8"µJ"};
};

struct millijoule_t final : public details::unit_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millijoule"};
    static constexpr std::string_view symbol{"mJ"};
    static constexpr std::wstring_view w_symbol{L"mJ"};
    static constexpr std::u8string_view u8_symbol{u8"mJ"};
};

struct nanojoule_t final : public details::unit_t<double, std::ratio<1, 1000000000>, energy_dimension>
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

// Energy units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, energy_dimension>
{
    using type = joule_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using type = kilojoule_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using type = megajoule_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using type = gigajoule_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using type = microjoule_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using type = millijoule_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, energy_dimension>
{
    using type = nanojoule_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    using type = calorie;
};

template<>
struct details::named_unit_type_t<double, std::ratio<4184, 1>, energy_dimension>
{
    using type = kilocalorie;
};

template<>
struct details::named_unit_type_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using type = watt_hour;
};

template<>
struct details::named_unit_type_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using type = kilowatt_hour;
};

} // PKR_UNITS_NAMESPACE








