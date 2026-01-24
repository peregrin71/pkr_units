#pragma once

#include <pkr_units/impl/unit_impl.h>
#include "../../../../../impl/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Inductance dimension
inline constexpr dimension_t inductance_dimension{2, 1, -2, -2, 0, 0, 0, 0};

// Strong type for henry (SI base unit)
struct henry final : public unit_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, inductance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"henry"};
    constexpr std::string_view symbol{"H"};
    constexpr std::wstring_view w_symbol{L"H"};
    constexpr std::u8string_view u8_symbol{u8"H"};
};

// Strong type for millihenry
struct millihenry final : public unit_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, inductance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"millihenry"};
    constexpr std::string_view symbol{"mH"};
    constexpr std::wstring_view w_symbol{L"mH"};
    constexpr std::u8string_view u8_symbol{u8"mH"};
};

// Strong type for microhenry
struct microhenry final : public unit_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, inductance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"microhenry"};
    constexpr std::string_view symbol{"µH"};
    constexpr std::wstring_view w_symbol{L"µH"};
    constexpr std::u8string_view u8_symbol{u8"µH"};
};

// Strong type for nanohenry
struct nanohenry final : public unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>;
    using _base::_base;
    constexpr std::string_view name{"nanohenry"};
    constexpr std::string_view symbol{"nH"};
    constexpr std::wstring_view w_symbol{L"nH"};
    constexpr std::u8string_view u8_symbol{u8"nH"};
};

} // PKR_UNITS_NAMESPACE








