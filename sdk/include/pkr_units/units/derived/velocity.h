#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/velocity_decl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for meter per second (SI base unit)
struct meter_per_second_t final : public details::unit_t<double, std::ratio<1, 1>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, velocity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"meter per second"};

    [[maybe_unused]] static constexpr std::string_view symbol{"m/s"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u00b7s\u207b\u00b9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u00b7s\u207b\u00b9"};

};

// Strong type for kilometer per hour
struct kilometer_per_hour_t final : public details::unit_t<double, std::ratio<5, 18>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<5, 18>, velocity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilometer per hour"};

    [[maybe_unused]] static constexpr std::string_view symbol{"km/h"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00b7h\u207b\u00b9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km\u00b7h\u207b\u00b9"};

};

// Strong type for centimeter per second
struct centimeter_per_second_t final : public details::unit_t<double, std::ratio<1, 100>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 100>, velocity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centimeter per second"};

    [[maybe_unused]] static constexpr std::string_view symbol{"cm/s"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm\u00b7s\u207b\u00b9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm\u00b7s\u207b\u00b9"};

};

// Strong type for millimeter per second
struct millimeter_per_second_t final : public details::unit_t<double, std::ratio<1, 1000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, velocity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millimeter per second"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mm/s"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm\u00b7s\u207b\u00b9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm\u00b7s\u207b\u00b9"};

};

// Strong type for kilometer per second
struct kilometer_per_second_t final : public details::unit_t<double, std::ratio<1000, 1>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, velocity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilometer per second"};

    [[maybe_unused]] static constexpr std::string_view symbol{"km/s"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00b7s\u207b\u00b9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km·s⁻¹"};

};

// ============================================================================
// Most derived unit type specializations for velocity units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, velocity_dimension>
{
    using type = meter_per_second_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<5, 18>, velocity_dimension>
{
    using type = kilometer_per_hour_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 100>, velocity_dimension>
{
    using type = centimeter_per_second_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, velocity_dimension>
{
    using type = millimeter_per_second_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, velocity_dimension>
{
    using type = kilometer_per_second_t;
};

} // namespace PKR_UNITS_NAMESPACE
