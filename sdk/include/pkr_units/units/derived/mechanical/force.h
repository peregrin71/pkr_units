#pragma once

#include "../../../impl/unit_impl.h"
#include "../../../impl/dimension.h"
#include "../../../impl/namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Force dimension
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0};

// Strong type for newton (SI base unit)
struct newton final : public details::unit_t<double, std::ratio<1, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, force_dimension>;
    using _base::_base;
    const std::string_view name{"newton"};
    const std::string_view symbol{"N"};
    const std::wstring_view w_symbol{L"N"};
    const std::u8string_view u8_symbol{u8"N"};
};

// Strong type for kilonewton
struct kilonewton final : public details::unit_t<double, std::ratio<1000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;
    const std::string_view name{"kilonewton"};
    const std::string_view symbol{"kN"};
    const std::wstring_view w_symbol{L"kN"};
    const std::u8string_view u8_symbol{u8"kN"};
};

// Strong type for meganewton
struct meganewton final : public details::unit_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;
    const std::string_view name{"meganewton"};
    const std::string_view symbol{"MN"};
    const std::wstring_view w_symbol{L"MN"};
    const std::u8string_view u8_symbol{u8"MN"};
};

// Strong type for micronewton
struct micronewton final : public details::unit_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;
    const std::string_view name{"micronewton"};
    const std::string_view symbol{"uN"};
    const std::wstring_view w_symbol{L"µN"};
    const std::u8string_view u8_symbol{u8"µN"};
};

// Strong type for millinewton
struct millinewton final : public details::unit_t<double, std::ratio<1, 1000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;
    const std::string_view name{"millinewton"};
    const std::string_view symbol{"mN"};
    const std::wstring_view w_symbol{L"mN"};
    const std::u8string_view u8_symbol{u8"mN"};
};

// Strong type for nanonewton
struct nanonewton final : public details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>;
    using _base::_base;
    const std::string_view name{"nanonewton"};
    const std::string_view symbol{"nN"};
    const std::wstring_view w_symbol{L"nN"};
    const std::u8string_view u8_symbol{u8"nN"};
};

} // PKR_UNITS_NAMESPACE








