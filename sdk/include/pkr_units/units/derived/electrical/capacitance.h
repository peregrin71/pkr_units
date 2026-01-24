#pragma once

#include <pkr_units/impl/unit_impl.h>
#include "../../../../../impl/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Capacitance dimension
inline constexpr dimension_t capacitance_v{-2, -1, 4, 2, 0, 0, 0, 0};

// Strong type for farad (SI base unit)
struct farad final : public details::unit_t<double, std::ratio<1, 1>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, capacitance_v>;
    using _base::_base;
    const std::string_view name{"farad"};
    const std::string_view symbol{"F"};
    const std::wstring_view w_symbol{L"F"};
    const std::u8string_view u8_symbol{u8"F"};
};

// Strong type for millifarad
struct millifarad final : public details::unit_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, capacitance_v>;
    using _base::_base;
    const std::string_view name{"millifarad"};
    const std::string_view symbol{"mF"};
    const std::wstring_view w_symbol{L"mF"};
    const std::u8string_view u8_symbol{u8"mF"};
};

// Strong type for microfarad
struct microfarad final : public details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>;
    using _base::_base;
    const std::string_view name{"microfarad"};
    const std::string_view symbol{"µF"};
    const std::wstring_view w_symbol{L"µF"};
    const std::u8string_view u8_symbol{u8"µF"};
};

// Strong type for nanofarad
struct nanofarad final : public details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>;
    using _base::_base;
    const std::string_view name{"nanofarad"};
    const std::string_view symbol{"nF"};
    const std::wstring_view w_symbol{L"nF"};
    const std::u8string_view u8_symbol{u8"nF"};
};

// Strong type for picofarad
struct picofarad final : public details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>;
    using _base::_base;
    const std::string_view name{"picofarad"};
    const std::string_view symbol{"pF"};
    const std::wstring_view w_symbol{L"pF"};
    const std::u8string_view u8_symbol{u8"pF"};
};

} // PKR_UNITS_NAMESPACE








