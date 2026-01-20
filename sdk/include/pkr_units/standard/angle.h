#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/unit.h"
#include "../impl/common/angle_def.h"
#include "../impl/common/dimension.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for radian (SI base unit for plane angle)
struct radian_t final : public details::unit_t<double, std::ratio<1, 1>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"radian"};
    static constexpr std::string_view symbol{"rad"};
    static constexpr std::wstring_view w_symbol{L"rad"};
    static constexpr std::u8string_view u8_symbol{u8"rad"};
};

// Strong type for degree
// 1 degree = π/180 radians ≈ 0.0174533 radians
// Ratio: 1745329/100000000 (scaled to avoid floating point)
struct degree_t final : public details::unit_t<double, std::ratio<1745329, 100000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1745329, 100000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"degree"};
    static constexpr std::string_view symbol{"°"};
    static constexpr std::wstring_view w_symbol{L"°"};
    static constexpr std::u8string_view u8_symbol{u8"°"};
};

// Strong type for gradian (also called gon)
// 1 gradian = π/200 radians ≈ 0.0157080 radians
// Ratio: 1570796/100000000 (scaled to avoid floating point)
struct gradian_t final : public details::unit_t<double, std::ratio<1570796, 100000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1570796, 100000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gradian"};
    static constexpr std::string_view symbol{"gon"};
    static constexpr std::wstring_view w_symbol{L"gon"};
    static constexpr std::u8string_view u8_symbol{u8"gon"};
};

// ============================================================================
// Most derived unit type specializations
// ============================================================================

template<>
struct details::most_derived_unit_type<double, std::ratio<1, 1>, angle_dimension>
{
    using type = radian_t;
};

template<>
struct details::most_derived_unit_type<double, std::ratio<1745329, 100000000>, angle_dimension>
{
    using type = degree_t;
};

template<>
struct details::most_derived_unit_type<double, std::ratio<1570796, 100000000>, angle_dimension>
{
    using type = gradian_t;
};

}  // namespace PKR_UNITS_NAMESPACE
