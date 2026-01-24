#pragma once

#include <pkr_units/impl/unit_impl.h>
#include "../../../../../impl/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Power dimension
inline constexpr dimension_t power_dimension{2, 1, -3, 0, 0, 0, 0};

// Strong type for watt (SI base unit)
struct watt final : public unit_t<double, std::ratio<1, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"watt"};
    constexpr std::string_view symbol{"W"};
    constexpr std::wstring_view w_symbol{L"W"};
    constexpr std::u8string_view u8_symbol{u8"W"};
};

// Strong type for kilowatt
struct kilowatt final : public unit_t<double, std::ratio<1000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilowatt"};
    constexpr std::string_view symbol{"kW"};
    constexpr std::wstring_view w_symbol{L"kW"};
    constexpr std::u8string_view u8_symbol{u8"kW"};
};

// Strong type for megawatt
struct megawatt final : public unit_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"megawatt"};
    constexpr std::string_view symbol{"MW"};
    constexpr std::wstring_view w_symbol{L"MW"};
    constexpr std::u8string_view u8_symbol{u8"MW"};
};

// Strong type for gigawatt
struct gigawatt final : public unit_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"gigawatt"};
    constexpr std::string_view symbol{"GW"};
    constexpr std::wstring_view w_symbol{L"GW"};
    constexpr std::u8string_view u8_symbol{u8"GW"};
};

// Strong type for milliwatt
struct milliwatt final : public unit_t<double, std::ratio<1, 1000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"milliwatt"};
    constexpr std::string_view symbol{"mW"};
    constexpr std::wstring_view w_symbol{L"mW"};
    constexpr std::u8string_view u8_symbol{u8"mW"};
};

// Strong type for microwatt
struct microwatt final : public unit_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"microwatt"};
    constexpr std::string_view symbol{"µW"};
    constexpr std::wstring_view w_symbol{L"µW"};
    constexpr std::u8string_view u8_symbol{u8"µW"};
};

// Strong type for nanowatt
struct nanowatt final : public unit_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"nanowatt"};
    constexpr std::string_view symbol{"nW"};
    constexpr std::wstring_view w_symbol{L"nW"};
    constexpr std::u8string_view u8_symbol{u8"nW"};
};

// Strong type for horsepower
struct horsepower final : public unit_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using _base = unit_t<double, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;
    constexpr std::string_view name{"horsepower"};
    constexpr std::string_view symbol{"hp"};
    constexpr std::wstring_view w_symbol{L"hp"};
    constexpr std::u8string_view u8_symbol{u8"hp"};
};

} // PKR_UNITS_NAMESPACE








