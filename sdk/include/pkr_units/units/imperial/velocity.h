#pragma once
#include <string_view>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/velocity_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial velocity units
struct miles_per_hour_t final : public details::unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"miles per hour"};
    static constexpr std::string_view symbol{"mph"};
    static constexpr std::wstring_view w_symbol{L"mph"};
    static constexpr std::u8string_view u8_symbol{u8"mph"};
};

struct feet_per_second_t final : public details::unit_t<double, std::ratio<3048, 10000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<3048, 10000>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"feet per second"};
    static constexpr std::string_view symbol{"ft/s"};
    static constexpr std::wstring_view w_symbol{L"ft\u00b7s\u207b\u00b9"};
    static constexpr std::u8string_view u8_symbol{u8"ft\u00b7s\u207b\u00b9"};
};

struct inches_per_second_t final : public details::unit_t<double, std::ratio<254, 10000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<254, 10000>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"inches per second"};
    static constexpr std::string_view symbol{"in/s"};
    static constexpr std::wstring_view w_symbol{L"in\u00b7s\u207b\u00b9"};
    static constexpr std::u8string_view u8_symbol{u8"in\u00b7s\u207b\u00b9"};
};

struct knots_t final : public details::unit_t<double, std::ratio<1852, 3600>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1852, 3600>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"knots"};
    static constexpr std::string_view symbol{"kn"};
    static constexpr std::wstring_view w_symbol{L"kn"};
    static constexpr std::u8string_view u8_symbol{u8"kn"};
};

// ============================================================================
// Most derived unit type specializations for imperial velocity units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1609344, 3600000>, velocity_dimension>
{
    using type = miles_per_hour_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<3048, 10000>, velocity_dimension>
{
    using type = feet_per_second_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<254, 10000>, velocity_dimension>
{
    using type = inches_per_second_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1852, 3600>, velocity_dimension>
{
    using type = knots_t;
};

} // namespace PKR_UNITS_NAMESPACE
