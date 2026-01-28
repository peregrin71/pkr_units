#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/area_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Area units (square meter and derived)
// Base unit: square meter (m^2)

struct square_meter_t final : public details::unit_t<double, std::ratio<1, 1>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square meter"};
    static constexpr std::string_view symbol{"m^2"};
    static constexpr std::wstring_view w_symbol{L"m^2"};
    static constexpr std::u8string_view u8_symbol{u8"m^2"};
};

struct square_kilometer_t final : public details::unit_t<double, std::ratio<1000000, 1>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square kilometer"};
    static constexpr std::string_view symbol{"km^2"};
    static constexpr std::wstring_view w_symbol{L"km^2"};
    static constexpr std::u8string_view u8_symbol{u8"km^2"};
};

struct square_centimeter_t final : public details::unit_t<double, std::ratio<1, 10000>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10000>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square centimeter"};
    static constexpr std::string_view symbol{"cm^2"};
    static constexpr std::wstring_view w_symbol{L"cm^2"};
    static constexpr std::u8string_view u8_symbol{u8"cm^2"};
};

struct square_millimeter_t final : public details::unit_t<double, std::ratio<1, 1000000>, area_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, area_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"square millimeter"};
    static constexpr std::string_view symbol{"mm^2"};
    static constexpr std::wstring_view w_symbol{L"mm^2"};
    static constexpr std::u8string_view u8_symbol{u8"mm^2"};
};

} // namespace PKR_UNITS_NAMESPACE
