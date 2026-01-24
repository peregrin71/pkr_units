#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Power dimension: kg·m²·s⁻³ (M·L²·T⁻³)
inline constexpr dimension_t power_dimension{2, 1, -3, 0, 0, 0, 0, 0};

// Power units (Watt and derived)
// Base unit: Watt (W) = kg·m²·s⁻³

struct watt_t final : public details::unit_t<double, std::ratio<1, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"watt"};
    static constexpr std::string_view symbol{"W"};
    static constexpr std::wstring_view w_symbol{L"W"};
    static constexpr std::u8string_view u8_symbol{u8"W"};
};

struct kilowatt_t final : public details::unit_t<double, std::ratio<1000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilowatt"};
    static constexpr std::string_view symbol{"kW"};
    static constexpr std::wstring_view w_symbol{L"kW"};
    static constexpr std::u8string_view u8_symbol{u8"kW"};
};

struct megawatt_t final : public details::unit_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megawatt"};
    static constexpr std::string_view symbol{"MW"};
    static constexpr std::wstring_view w_symbol{L"MW"};
    static constexpr std::u8string_view u8_symbol{u8"MW"};
};

struct gigawatt_t final : public details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigawatt"};
    static constexpr std::string_view symbol{"GW"};
    static constexpr std::wstring_view w_symbol{L"GW"};
    static constexpr std::u8string_view u8_symbol{u8"GW"};
};

struct microwatt_t final : public details::unit_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microwatt"};
    static constexpr std::string_view symbol{"uW"};
    static constexpr std::wstring_view w_symbol{L"µW"};
    static constexpr std::u8string_view u8_symbol{u8"µW"};
};

struct milliwatt_t final : public details::unit_t<double, std::ratio<1, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliwatt"};
    static constexpr std::string_view symbol{"mW"};
    static constexpr std::wstring_view w_symbol{L"mW"};
    static constexpr std::u8string_view u8_symbol{u8"mW"};
};

struct nanowatt_t final : public details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanowatt"};
    static constexpr std::string_view symbol{"nW"};
    static constexpr std::wstring_view w_symbol{L"nW"};
    static constexpr std::u8string_view u8_symbol{u8"nW"};
};

struct horsepower_t final : public details::unit_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"horsepower"};
    static constexpr std::string_view symbol{"hp"};
    static constexpr std::wstring_view w_symbol{L"hp"};
    static constexpr std::u8string_view u8_symbol{u8"hp"};
};

// Power units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, power_dimension>
{
    using type = watt_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, power_dimension>
{
    using type = kilowatt_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using type = megawatt_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using type = gigawatt_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using type = microwatt_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, power_dimension>
{
    using type = milliwatt_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using type = nanowatt_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using type = horsepower_t;
};

} // PKR_UNITS_NAMESPACE








