#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/volume_decl.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Volume units (cubic meter and derived)
// Base unit: cubic meter (m³)

struct cubic_meter_t final : public details::unit_t<double, std::ratio<1, 1>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, volume_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"cubic meter"};
    static constexpr std::string_view symbol{"m³"};
    static constexpr std::wstring_view w_symbol{L"m³"};
    static constexpr std::u8string_view u8_symbol{u8"m³"};
};

struct cubic_kilometer_t final : public details::unit_t<double, std::ratio<1000000000, 1>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, volume_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"cubic kilometer"};
    static constexpr std::string_view symbol{"km³"};
    static constexpr std::wstring_view w_symbol{L"km³"};
    static constexpr std::u8string_view u8_symbol{u8"km³"};
};

struct cubic_centimeter_t final : public details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"cubic centimeter"};
    static constexpr std::string_view symbol{"cm³"};
    static constexpr std::wstring_view w_symbol{L"cm³"};
    static constexpr std::u8string_view u8_symbol{u8"cm³"};
};

struct cubic_millimeter_t final : public details::unit_t<double, std::ratio<1, 1000000000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, volume_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"cubic millimeter"};
    static constexpr std::string_view symbol{"mm³"};
    static constexpr std::wstring_view w_symbol{L"mm³"};
    static constexpr std::u8string_view u8_symbol{u8"mm³"};
};

struct liter_t final : public details::unit_t<double, std::ratio<1, 1000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, volume_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"liter"};
    static constexpr std::string_view symbol{"L"};
    static constexpr std::wstring_view w_symbol{L"L"};
    static constexpr std::u8string_view u8_symbol{u8"L"};
};

struct milliliter_t final : public details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliliter"};
    static constexpr std::string_view symbol{"mL"};
    static constexpr std::wstring_view w_symbol{L"mL"};
    static constexpr std::u8string_view u8_symbol{u8"mL"};
};

} // PKR_UNITS_NAMESPACE