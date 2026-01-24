#pragma once

#include "../../../impl/unit_impl.h"
#include "../../../impl/dimension.h"
#include "../../../impl/namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Power dimension
inline constexpr dimension_t power_dimension{2, 1, -3, 0, 0, 0, 0};

// Strong type for watt (SI base unit)
struct watt final : public details::unit_t<double, std::ratio<1, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"watt"};
    static constexpr std::string_view symbol{"W"};
    static constexpr std::wstring_view w_symbol{L"W"};
    static constexpr std::u8string_view u8_symbol{u8"W"};
};

// Strong type for kilowatt
struct kilowatt final : public details::unit_t<double, std::ratio<1000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilowatt"};
    static constexpr std::string_view symbol{"kW"};
    static constexpr std::wstring_view w_symbol{L"kW"};
    static constexpr std::u8string_view u8_symbol{u8"kW"};
};

// Strong type for megawatt
struct megawatt final : public details::unit_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megawatt"};
    static constexpr std::string_view symbol{"MW"};
    static constexpr std::wstring_view w_symbol{L"MW"};
    static constexpr std::u8string_view u8_symbol{u8"MW"};
};

// Strong type for gigawatt
struct gigawatt final : public details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigawatt"};
    static constexpr std::string_view symbol{"GW"};
    static constexpr std::wstring_view w_symbol{L"GW"};
    static constexpr std::u8string_view u8_symbol{u8"GW"};
};

// Strong type for milliwatt
struct milliwatt final : public details::unit_t<double, std::ratio<1, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliwatt"};
    static constexpr std::string_view symbol{"mW"};
    static constexpr std::wstring_view w_symbol{L"mW"};
    static constexpr std::u8string_view u8_symbol{u8"mW"};
};

// Strong type for microwatt
struct microwatt final : public details::unit_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microwatt"};
    static constexpr std::string_view symbol{"uW"};
    static constexpr std::wstring_view w_symbol{L"µW"};
    static constexpr std::u8string_view u8_symbol{u8"µW"};
};

// Strong type for nanowatt
struct nanowatt final : public details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanowatt"};
    static constexpr std::string_view symbol{"nW"};
    static constexpr std::wstring_view w_symbol{L"nW"};
    static constexpr std::u8string_view u8_symbol{u8"nW"};
};

// Strong type for horsepower
struct horsepower final : public details::unit_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"horsepower"};
    static constexpr std::string_view symbol{"hp"};
    static constexpr std::wstring_view w_symbol{L"hp"};
    static constexpr std::u8string_view u8_symbol{u8"hp"};
};

} // PKR_UNITS_NAMESPACE








