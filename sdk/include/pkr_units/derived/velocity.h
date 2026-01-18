#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/unit.h"
#include "../impl/common/velocity_def.h"
#include "../impl/common/dimension.h"

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

} // PKR_UNITS_NAMESPACE








