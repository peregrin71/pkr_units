#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../../../../impl/common/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Capacitance dimension
inline constexpr dimension_t capacitance_v{-2, -1, 4, 2, 0, 0, 0};

// Strong type for farad (SI base unit)
struct farad final : public unit_t<double, std::ratio<1, 1>, capacitance_v>
{
    using _base = unit_t<double, std::ratio<1, 1>, capacitance_v>;
    using _base::_base;
    constexpr std::string_view name{"farad"};
    constexpr std::string_view symbol{"F"};
    constexpr std::wstring_view w_symbol{L"F"};
    constexpr std::u8string_view u8_symbol{u8"F"};
};

// Strong type for millifarad
struct millifarad final : public unit_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using _base = unit_t<double, std::ratio<1, 1000>, capacitance_v>;
    using _base::_base;
    constexpr std::string_view name{"millifarad"};
    constexpr std::string_view symbol{"mF"};
    constexpr std::wstring_view w_symbol{L"mF"};
    constexpr std::u8string_view u8_symbol{u8"mF"};
};

// Strong type for microfarad
struct microfarad final : public unit_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, capacitance_v>;
    using _base::_base;
    constexpr std::string_view name{"microfarad"};
    constexpr std::string_view symbol{"µF"};
    constexpr std::wstring_view w_symbol{L"µF"};
    constexpr std::u8string_view u8_symbol{u8"µF"};
};

// Strong type for nanofarad
struct nanofarad final : public unit_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, capacitance_v>;
    using _base::_base;
    constexpr std::string_view name{"nanofarad"};
    constexpr std::string_view symbol{"nF"};
    constexpr std::wstring_view w_symbol{L"nF"};
    constexpr std::u8string_view u8_symbol{u8"nF"};
};

// Strong type for picofarad
struct picofarad final : public unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>;
    using _base::_base;
    constexpr std::string_view name{"picofarad"};
    constexpr std::string_view symbol{"pF"};
    constexpr std::wstring_view w_symbol{L"pF"};
    constexpr std::u8string_view u8_symbol{u8"pF"};
};

} // PKR_UNITS_NAMESPACE


