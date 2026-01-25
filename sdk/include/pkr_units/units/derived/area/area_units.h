#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/area_decl.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Area units (square meter and derived)
// Base unit: square meter (m²)

struct square_meter_t final : public details::unit_t<double, std::ratio<1, 1>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square meter"};
    static constexpr std::string_view symbol{"m²"};
    static constexpr std::wstring_view w_symbol{L"m²"};
    static constexpr std::u8string_view u8_symbol{u8"m²"};
};

struct square_kilometer_t final : public details::unit_t<double, std::ratio<1000000, 1>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square kilometer"};
    static constexpr std::string_view symbol{"km²"};
    static constexpr std::wstring_view w_symbol{L"km²"};
    static constexpr std::u8string_view u8_symbol{u8"km²"};
};

struct square_centimeter_t final : public details::unit_t<double, std::ratio<1, 10000>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10000>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square centimeter"};
    static constexpr std::string_view symbol{"cm²"};
    static constexpr std::wstring_view w_symbol{L"cm²"};
    static constexpr std::u8string_view u8_symbol{u8"cm²"};
};

struct square_millimeter_t final : public details::unit_t<double, std::ratio<1, 1000000>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square millimeter"};
    static constexpr std::string_view symbol{"mm²"};
    static constexpr std::wstring_view w_symbol{L"mm²"};
    static constexpr std::u8string_view u8_symbol{u8"mm²"};
};

} // PKR_UNITS_NAMESPACE