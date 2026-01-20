#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../../../../impl/common/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Electric resistance dimension
inline constexpr dimension_t electric_resistance_dimension{2, 1, -3, -2, 0, 0, 0, 0};

// Strong type for ohm (SI base unit)
struct ohm final : public unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"ohm"};
    constexpr std::string_view symbol{"Ω"};
    constexpr std::wstring_view w_symbol{L"Ω"};
    constexpr std::u8string_view u8_symbol{u8"Ω"};
};

// Strong type for kilohm
struct kilohm final : public unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilohm"};
    constexpr std::string_view symbol{"kΩ"};
    constexpr std::wstring_view w_symbol{L"kΩ"};
    constexpr std::u8string_view u8_symbol{u8"kΩ"};
};

// Strong type for megohm
struct megohm final : public unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"megohm"};
    constexpr std::string_view symbol{"MΩ"};
    constexpr std::wstring_view w_symbol{L"MΩ"};
    constexpr std::u8string_view u8_symbol{u8"MΩ"};
};

// Strong type for gigohm
struct gigohm final : public unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"gigohm"};
    constexpr std::string_view symbol{"GΩ"};
    constexpr std::wstring_view w_symbol{L"GΩ"};
    constexpr std::u8string_view u8_symbol{u8"GΩ"};
};

// Strong type for milliohm
struct milliohm final : public unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"milliohm"};
    constexpr std::string_view symbol{"mΩ"};
    constexpr std::wstring_view w_symbol{L"mΩ"};
    constexpr std::u8string_view u8_symbol{u8"mΩ"};
};

// Strong type for microohm
struct microohm final : public unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"microohm"};
    constexpr std::string_view symbol{"µΩ"};
    constexpr std::wstring_view w_symbol{L"µΩ"};
    constexpr std::u8string_view u8_symbol{u8"µΩ"};
};

} // PKR_UNITS_NAMESPACE


