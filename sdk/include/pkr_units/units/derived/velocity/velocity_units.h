#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Velocity dimension
inline constexpr dimension_t velocity_dimension{1, 0, -1, 0, 0, 0, 0, 0};

// Velocity quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using velocity = details::unit_t<type_t, ratio_t, velocity_dimension>;

// Strong type for meter per second (SI base unit)
struct meter_per_second final : public details::unit_t<double, std::ratio<1, 1>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"meter per second"};
    static constexpr std::string_view symbol{"m/s"};
    static constexpr std::wstring_view w_symbol{L"m/s"};
    static constexpr std::u8string_view u8_symbol{u8"m/s"};
};

// Strong type for kilometer per hour
struct kilometer_per_hour final : public details::unit_t<double, std::ratio<5, 18>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<5, 18>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilometer per hour"};
    static constexpr std::string_view symbol{"km/h"};
    static constexpr std::wstring_view w_symbol{L"km/h"};
    static constexpr std::u8string_view u8_symbol{u8"km/h"};
};

// Strong type for centimeter per second
struct centimeter_per_second final : public details::unit_t<double, std::ratio<1, 100>, velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 100>, velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centimeter per second"};
    static constexpr std::string_view symbol{"cm/s"};
    static constexpr std::wstring_view w_symbol{L"cm/s"};
    static constexpr std::u8string_view u8_symbol{u8"cm/s"};
};

} // PKR_UNITS_NAMESPACE









