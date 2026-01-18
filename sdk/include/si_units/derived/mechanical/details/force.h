#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Force dimension
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0};

// Strong type for newton (SI base unit)
struct newton final : public unit_t<double, std::ratio<1, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, force_dimension>;
    using _base::_base;
    constexpr std::string_view name{"newton"};
    constexpr std::string_view symbol{"N"};
    constexpr std::wstring_view w_symbol{L"N"};
    constexpr std::u8string_view u8_symbol{u8"N"};
};

// Strong type for kilonewton
struct kilonewton final : public unit_t<double, std::ratio<1000, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilonewton"};
    constexpr std::string_view symbol{"kN"};
    constexpr std::wstring_view w_symbol{L"kN"};
    constexpr std::u8string_view u8_symbol{u8"kN"};
};

// Strong type for meganewton
struct meganewton final : public unit_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;
    constexpr std::string_view name{"meganewton"};
    constexpr std::string_view symbol{"MN"};
    constexpr std::wstring_view w_symbol{L"MN"};
    constexpr std::u8string_view u8_symbol{u8"MN"};
};

// Strong type for micronewton
struct micronewton final : public unit_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;
    constexpr std::string_view name{"micronewton"};
    constexpr std::string_view symbol{"µN"};
    constexpr std::wstring_view w_symbol{L"µN"};
    constexpr std::u8string_view u8_symbol{u8"µN"};
};

// Strong type for millinewton
struct millinewton final : public unit_t<double, std::ratio<1, 1000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;
    constexpr std::string_view name{"millinewton"};
    constexpr std::string_view symbol{"mN"};
    constexpr std::wstring_view w_symbol{L"mN"};
    constexpr std::u8string_view u8_symbol{u8"mN"};
};

// Strong type for nanonewton
struct nanonewton final : public unit_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, force_dimension>;
    using _base::_base;
    constexpr std::string_view name{"nanonewton"};
    constexpr std::string_view symbol{"nN"};
    constexpr std::wstring_view w_symbol{L"nN"};
    constexpr std::u8string_view u8_symbol{u8"nN"};
};

} // PKR_SI_NAMESPACE


