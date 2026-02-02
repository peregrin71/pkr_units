#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/volume_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Volume units (cubic meter and derived)
// Base unit: cubic meter (m^3)

struct cubic_meter_t final : public details::unit_t<double, std::ratio<1, 1>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, volume_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"cubic meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u00b3"};
};

struct cubic_kilometer_t final : public details::unit_t<double, std::ratio<1000000000, 1>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, volume_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"cubic kilometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"km^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km\u00b3"};
};

struct cubic_centimeter_t final : public details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"cubic centimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cm^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm\u00b3"};
};

struct cubic_millimeter_t final : public details::unit_t<double, std::ratio<1, 1000000000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, volume_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"cubic millimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mm^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm\u00b3"};
};

struct liter_t final : public details::unit_t<double, std::ratio<1, 1000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, volume_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"liter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"L"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"L"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"L"};
};

struct milliliter_t final : public details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, volume_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"milliliter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mL"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mL"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mL"};
};

} // namespace PKR_UNITS_NAMESPACE
