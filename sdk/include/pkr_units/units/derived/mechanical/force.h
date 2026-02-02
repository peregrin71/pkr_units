#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Force dimension: kg·m·s⁻² (M·L·T⁻²)
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0, 0};

// Base unit: Newton (N) = kg·m·s⁻²
using namespace_force_units_detail = int; // Force namespace detail

struct newton_t final : public details::unit_t<double, std::ratio<1, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, force_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"newton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"N"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"N"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"N"};
};

struct kilonewton_t final : public details::unit_t<double, std::ratio<1000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilonewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kN"};
};

struct meganewton_t final : public details::unit_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"meganewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MN"};
};

struct micronewton_t final : public details::unit_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"micronewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5N"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5N"};
};

struct millinewton_t final : public details::unit_t<double, std::ratio<1, 1000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millinewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mN"};
};

struct nanonewton_t final : public details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, force_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanonewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nN"};
};

// Force units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, force_dimension>
{
    using type = newton_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, force_dimension>
{
    using type = kilonewton_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, force_dimension>
{
    using type = meganewton_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, force_dimension>
{
    using type = micronewton_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, force_dimension>
{
    using type = millinewton_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, force_dimension>
{
    using type = nanonewton_t;
};

} // namespace PKR_UNITS_NAMESPACE
