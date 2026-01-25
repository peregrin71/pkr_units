#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Force dimension: kg·m·s⁻² (M·L·T⁻²)
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0, 0};

// Base unit: Newton (N) = kg·m·s⁻²
using namespace_force_units_detail = int; // Force namespace detail

struct newton_t final : public details::unit_t<double, std::ratio<1, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"newton"};
    static constexpr std::string_view symbol{"N"};
    static constexpr std::wstring_view w_symbol{L"N"};
    static constexpr std::u8string_view u8_symbol{u8"N"};
};

struct kilonewton_t final : public details::unit_t<double, std::ratio<1000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilonewton"};
    static constexpr std::string_view symbol{"kN"};
    static constexpr std::wstring_view w_symbol{L"kN"};
    static constexpr std::u8string_view u8_symbol{u8"kN"};
};

struct meganewton_t final : public details::unit_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"meganewton"};
    static constexpr std::string_view symbol{"MN"};
    static constexpr std::wstring_view w_symbol{L"MN"};
    static constexpr std::u8string_view u8_symbol{u8"MN"};
};

struct micronewton_t final : public details::unit_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micronewton"};
    static constexpr std::string_view symbol{"uN"};
    static constexpr std::wstring_view w_symbol{L"µN"};
    static constexpr std::u8string_view u8_symbol{u8"µN"};
};

struct millinewton_t final : public details::unit_t<double, std::ratio<1, 1000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millinewton"};
    static constexpr std::string_view symbol{"mN"};
    static constexpr std::wstring_view w_symbol{L"mN"};
    static constexpr std::u8string_view u8_symbol{u8"mN"};
};

struct nanonewton_t final : public details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanonewton"};
    static constexpr std::string_view symbol{"nN"};
    static constexpr std::wstring_view w_symbol{L"nN"};
    static constexpr std::u8string_view u8_symbol{u8"nN"};
};

// Force units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, force_dimension>
{
    using type = newton_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, force_dimension>
{
    using type = kilonewton_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using type = meganewton_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using type = micronewton_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, force_dimension>
{
    using type = millinewton_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using type = nanonewton_t;
};

} // PKR_UNITS_NAMESPACE








