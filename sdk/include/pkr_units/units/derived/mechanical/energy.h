#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Energy dimension: kgÂ·mÂ²Â·sâ»Â² (MÂ·LÂ²Â·Tâ»Â²)
inline constexpr dimension_t energy_dimension{2, 1, -2, 0, 0, 0, 0, 0};

// Energy units (Joule and derived)
// Base unit: Joule (J) = kgÂ·mÂ²Â·sâ»Â²
template <is_unit_value_type_c T>
struct joule_t final : public details::unit_t<T, std::ratio<1, 1>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"joule"};
    [[maybe_unused]] static constexpr std::string_view symbol{"J"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"J"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"J"};
};

template <is_unit_value_type_c T>
joule_t(T) -> joule_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
joule_t(const U&) -> joule_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilojoule_t final : public details::unit_t<T, std::ratio<1000, 1>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilojoule"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kJ"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kJ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kJ"};
};

template <is_unit_value_type_c T>
kilojoule_t(T) -> kilojoule_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
kilojoule_t(const U&) -> kilojoule_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megajoule_t final : public details::unit_t<T, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megajoule"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MJ"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MJ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MJ"};
};

template <is_unit_value_type_c T>
megajoule_t(T) -> megajoule_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
megajoule_t(const U&) -> megajoule_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gigajoule_t final : public details::unit_t<T, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigajoule"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GJ"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GJ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GJ"};
};

template <is_unit_value_type_c T>
gigajoule_t(T) -> gigajoule_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
gigajoule_t(const U&) -> gigajoule_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microjoule_t final : public details::unit_t<T, std::ratio<1, 1000000>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microjoule"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uJ"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5J"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5J"};
};

template <is_unit_value_type_c T>
microjoule_t(T) -> microjoule_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
microjoule_t(const U&) -> microjoule_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millijoule_t final : public details::unit_t<T, std::ratio<1, 1000>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millijoule"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mJ"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mJ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mJ"};
};

template <is_unit_value_type_c T>
millijoule_t(T) -> millijoule_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
millijoule_t(const U&) -> millijoule_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanojoule_t final : public details::unit_t<T, std::ratio<1, 1000000000>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanojoule"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nJ"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nJ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nJ"};
};

template <is_unit_value_type_c T>
nanojoule_t(T) -> nanojoule_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
nanojoule_t(const U&) -> nanojoule_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct calorie_t final : public details::unit_t<T, std::ratio<4184, 1000>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<4184, 1000>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"calorie"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cal"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cal"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cal"};
};

template <is_unit_value_type_c T>
calorie_t(T) -> calorie_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
calorie_t(const U&) -> calorie_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilocalorie_t final : public details::unit_t<T, std::ratio<4184, 1>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<4184, 1>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilocalorie"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kcal"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kcal"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kcal"};
};

template <is_unit_value_type_c T>
kilocalorie_t(T) -> kilocalorie_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
kilocalorie_t(const U&) -> kilocalorie_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct watt_hour_t final : public details::unit_t<T, std::ratio<3600, 1>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<3600, 1>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"watt_hour"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Wh"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Wh"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Wh"};
};

template <is_unit_value_type_c T>
watt_hour_t(T) -> watt_hour_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
watt_hour_t(const U&) -> watt_hour_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilowatt_hour_t final : public details::unit_t<T, std::ratio<3600000, 1>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<3600000, 1>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilowatt_hour"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kWh"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kWh"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kWh"};
};

template <is_unit_value_type_c T>
kilowatt_hour_t(T) -> kilowatt_hour_t<T>;

// Electronvolt-based units
// 1 eV = 1.602176634e-19 J (exact). Ratio chosen to fit std::ratio limits.
template <is_unit_value_type_c T>
struct electronvolt_t final : public details::unit_t<T, std::ratio<1, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 6241509074460762607>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"electronvolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"eV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"eV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"eV"};
};

template <is_unit_value_type_c T>
electronvolt_t(T) -> electronvolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
electronvolt_t(const U&) -> electronvolt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kiloelectronvolt_t final : public details::unit_t<T, std::ratio<1000, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 6241509074460762607>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kiloelectronvolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"keV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"keV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"keV"};
};

template <is_unit_value_type_c T>
kiloelectronvolt_t(T) -> kiloelectronvolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
kiloelectronvolt_t(const U&) -> kiloelectronvolt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megaelectronvolt_t final : public details::unit_t<T, std::ratio<1000000, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 6241509074460762607>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megaelectronvolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MeV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MeV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MeV"};
};

template <is_unit_value_type_c T>
megaelectronvolt_t(T) -> megaelectronvolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
megaelectronvolt_t(const U&) -> megaelectronvolt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gigaelectronvolt_t final : public details::unit_t<T, std::ratio<1000000000, 6241509074460762607>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000000, 6241509074460762607>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigaelectronvolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GeV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GeV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GeV"};
};

template <is_unit_value_type_c T>
gigaelectronvolt_t(T) -> gigaelectronvolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
gigaelectronvolt_t(const U&) -> gigaelectronvolt_t<typename details::is_pkr_unit<U>::value_type>;

// Energy units
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, energy_dimension>
{
    using type = joule_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, energy_dimension>
{
    using type = kilojoule_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, energy_dimension>
{
    using type = megajoule_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000000, 1>, energy_dimension>
{
    using type = gigajoule_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, energy_dimension>
{
    using type = microjoule_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, energy_dimension>
{
    using type = millijoule_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, energy_dimension>
{
    using type = nanojoule_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<4184, 1000>, energy_dimension>
{
    using type = calorie_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<4184, 1>, energy_dimension>
{
    using type = kilocalorie_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<3600, 1>, energy_dimension>
{
    using type = watt_hour_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<3600000, 1>, energy_dimension>
{
    using type = kilowatt_hour_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 6241509074460762607>, energy_dimension>
{
    using type = electronvolt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 6241509074460762607>, energy_dimension>
{
    using type = kiloelectronvolt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 6241509074460762607>, energy_dimension>
{
    using type = megaelectronvolt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000000, 6241509074460762607>, energy_dimension>
{
    using type = gigaelectronvolt_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
