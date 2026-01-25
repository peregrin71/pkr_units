#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/velocity_decl.h>
#include <pkr_units/impl/dimension.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for meter per second (SI base unit)
struct meter_per_second_t final : public details::unit_t<double, std::ratio<1, 1>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"meter per second"};
    static constexpr std::string_view symbol{"m/s"};
    static constexpr std::wstring_view w_symbol{L"m/s"};
    static constexpr std::u8string_view u8_symbol{u8"m/s"};
};

// Strong type for kilometer per hour
struct kilometer_per_hour_t final : public details::unit_t<double, std::ratio<5, 18>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<5, 18>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilometer per hour"};
    static constexpr std::string_view symbol{"km/h"};
    static constexpr std::wstring_view w_symbol{L"km/h"};
    static constexpr std::u8string_view u8_symbol{u8"km/h"};
};

// Strong type for centimeter per second
struct centimeter_per_second_t final : public details::unit_t<double, std::ratio<1, 100>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 100>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centimeter per second"};
    static constexpr std::string_view symbol{"cm/s"};
    static constexpr std::wstring_view w_symbol{L"cm/s"};
    static constexpr std::u8string_view u8_symbol{u8"cm/s"};
};

// Strong type for millimeter per second
struct millimeter_per_second_t final : public details::unit_t<double, std::ratio<1, 1000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millimeter per second"};
    static constexpr std::string_view symbol{"mm/s"};
    static constexpr std::wstring_view w_symbol{L"mm/s"};
    static constexpr std::u8string_view u8_symbol{u8"mm/s"};
};

// Strong type for kilometer per second
struct kilometer_per_second_t final : public details::unit_t<double, std::ratio<1000, 1>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilometer per second"};
    static constexpr std::string_view symbol{"km/s"};
    static constexpr std::wstring_view w_symbol{L"km/s"};
    static constexpr std::u8string_view u8_symbol{u8"km/s"};
};

// Strong type for miles per hour
struct miles_per_hour_t final : public details::unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1609344, 3600000>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"miles per hour"};
    static constexpr std::string_view symbol{"mph"};
    static constexpr std::wstring_view w_symbol{L"mph"};
    static constexpr std::u8string_view u8_symbol{u8"mph"};
};

// Strong type for feet per second
struct feet_per_second_t final : public details::unit_t<double, std::ratio<3048, 10000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<3048, 10000>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"feet per second"};
    static constexpr std::string_view symbol{"ft/s"};
    static constexpr std::wstring_view w_symbol{L"ft/s"};
    static constexpr std::u8string_view u8_symbol{u8"ft/s"};
};

// Strong type for inches per second
struct inches_per_second_t final : public details::unit_t<double, std::ratio<254, 10000>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<254, 10000>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"inches per second"};
    static constexpr std::string_view symbol{"in/s"};
    static constexpr std::wstring_view w_symbol{L"in/s"};
    static constexpr std::u8string_view u8_symbol{u8"in/s"};
};

// Strong type for knots
struct knots_t final : public details::unit_t<double, std::ratio<1852, 3600>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1852, 3600>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"knots"};
    static constexpr std::string_view symbol{"kn"};
    static constexpr std::wstring_view w_symbol{L"kn"};
    static constexpr std::u8string_view u8_symbol{u8"kn"};
};

// Aliases without _t suffix for convenience
using meter_per_second = meter_per_second_t;
using kilometer_per_hour = kilometer_per_hour_t;
using centimeter_per_second = centimeter_per_second_t;
using millimeter_per_second = millimeter_per_second_t;
using kilometer_per_second = kilometer_per_second_t;
using miles_per_hour = miles_per_hour_t;
using feet_per_second = feet_per_second_t;
using inches_per_second = inches_per_second_t;
using knots = knots_t;

// ============================================================================
// Most derived unit type specializations for velocity units
// ============================================================================

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, velocity_dimension>
{
    using type = meter_per_second_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<5, 18>, velocity_dimension>
{
    using type = kilometer_per_hour_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 100>, velocity_dimension>
{
    using type = centimeter_per_second_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, velocity_dimension>
{
    using type = millimeter_per_second_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, velocity_dimension>
{
    using type = kilometer_per_second_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1609344, 3600000>, velocity_dimension>
{
    using type = miles_per_hour_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<3048, 10000>, velocity_dimension>
{
    using type = feet_per_second_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<254, 10000>, velocity_dimension>
{
    using type = inches_per_second_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1852, 3600>, velocity_dimension>
{
    using type = knots_t;
};

} // PKR_UNITS_NAMESPACE















