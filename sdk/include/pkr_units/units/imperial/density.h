#pragma once
#include <string_view>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/density_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial density units
struct pound_per_cubic_inch_t final : public details::unit_t<double, std::ratio<27679904, 1000000>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<27679904, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound_per_cubic_inch"};
    static constexpr std::string_view symbol{"lb/in^3"};
    static constexpr std::wstring_view w_symbol{L"lb\u00b7in\u207b\u00b3"};
    static constexpr std::u8string_view u8_symbol{u8"lb\u00b7in\u207b\u00b3"};
};

struct pound_per_cubic_foot_t final : public details::unit_t<double, std::ratio<16018, 1000000>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<16018, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound_per_cubic_foot"};
    static constexpr std::string_view symbol{"lb/ft^3"};
    static constexpr std::wstring_view w_symbol{L"lb\u00b7ft\u207b\u00b3"};
    static constexpr std::u8string_view u8_symbol{u8"lb\u00b7ft\u207b\u00b3"};
};

struct pound_per_gallon_t final : public details::unit_t<double, std::ratio<119826, 1000000>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<119826, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound_per_gallon"};
    static constexpr std::string_view symbol{"lb/gal"};
    static constexpr std::wstring_view w_symbol{L"lb\u00b7gal\u207b\u00b9"};
    static constexpr std::u8string_view u8_symbol{u8"lb\u00b7gal\u207b\u00b9"};
};

struct ounce_per_cubic_inch_t final : public details::unit_t<double, std::ratio<1729994, 1000000>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1729994, 1000000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ounce_per_cubic_inch"};
    static constexpr std::string_view symbol{"oz/in^3"};
    static constexpr std::wstring_view w_symbol{L"oz\u00b7in\u207b\u00b3"};
    static constexpr std::u8string_view u8_symbol{u8"oz\u00b7in\u207b\u00b3"};
};

struct ounce_per_fluid_ounce_t final : public details::unit_t<double, std::ratio<33814, 1000>, density_dimension>
{
    using _base = details::unit_t<double, std::ratio<33814, 1000>, density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ounce_per_fluid_ounce"};
    static constexpr std::string_view symbol{"oz/fl oz"};
    static constexpr std::wstring_view w_symbol{L"oz\u00b7fl oz\u207b\u00b9"};
    static constexpr std::u8string_view u8_symbol{u8"oz\u00b7fl oz\u207b\u00b9"};
};

// ============================================================================
// Most derived unit type specializations for imperial density units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<27679904, 1000000>, density_dimension>
{
    using type = pound_per_cubic_inch_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<16018, 1000000>, density_dimension>
{
    using type = pound_per_cubic_foot_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<119826, 1000000>, density_dimension>
{
    using type = pound_per_gallon_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1729994, 1000000>, density_dimension>
{
    using type = ounce_per_cubic_inch_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<33814, 1000>, density_dimension>
{
    using type = ounce_per_fluid_ounce_t;
};

} // namespace PKR_UNITS_NAMESPACE
