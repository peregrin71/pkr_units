#pragma once

#include "../../impl/namespace_config.h"
#include "../../impl/unit_impl.h"
#include "../../impl/decls/acceleration_decl.h"
#include "../../impl/dimension.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for meter per second squared (SI base unit)
struct meter_per_second_squared_t final : public details::unit_t<double, std::ratio<1, 1>, acceleration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, acceleration_v>;
    using _base::_base;
    static constexpr std::string_view name{"meter per second squared"};
    static constexpr std::string_view symbol{"m/s^2"};
    static constexpr std::wstring_view w_symbol{L"m/s²"};
    static constexpr std::u8string_view u8_symbol{u8"m/s²"};
};

// Strong type for centimeter per second squared
struct centimeter_per_second_squared_t final : public details::unit_t<double, std::ratio<1, 100>, acceleration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 100>, acceleration_v>;
    using _base::_base;
    static constexpr std::string_view name{"centimeter per second squared"};
    static constexpr std::string_view symbol{"cm/s^2"};
    static constexpr std::wstring_view w_symbol{L"cm/s²"};
    static constexpr std::u8string_view u8_symbol{u8"cm/s²"};
};

// Strong type for millimeter per second squared
struct millimeter_per_second_squared_t final : public details::unit_t<double, std::ratio<1, 1000>, acceleration_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, acceleration_v>;
    using _base::_base;
    static constexpr std::string_view name{"millimeter per second squared"};
    static constexpr std::string_view symbol{"mm/s^2"};
    static constexpr std::wstring_view w_symbol{L"mm/s²"};
    static constexpr std::u8string_view u8_symbol{u8"mm/s²"};
};

// Strong type for kilometer per second squared
struct kilometer_per_second_squared_t final : public details::unit_t<double, std::ratio<1000, 1>, acceleration_v>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, acceleration_v>;
    using _base::_base;
    static constexpr std::string_view name{"kilometer per second squared"};
    static constexpr std::string_view symbol{"km/s^2"};
    static constexpr std::wstring_view w_symbol{L"km/s²"};
    static constexpr std::u8string_view u8_symbol{u8"km/s²"};
};

// Standard gravity (g) - Strong type
// 1 g = 9.80665 m/s² (exact definition)
// Simplified ratio: ratio<980665, 100000> for practical use
struct standard_gravity_t final : public details::unit_t<double, std::ratio<980665, 100000>, acceleration_v>
{
    using _base = details::unit_t<double, std::ratio<980665, 100000>, acceleration_v>;
    using _base::_base;
    static constexpr std::string_view name{"standard gravity"};
    static constexpr std::string_view symbol{"g"};
    static constexpr std::wstring_view w_symbol{L"g"};
    static constexpr std::u8string_view u8_symbol{u8"g"};
};

// ============================================================================
// Most derived unit type specializations for acceleration units
// ============================================================================

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, acceleration_v>
{
    using type = meter_per_second_squared_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 100>, acceleration_v>
{
    using type = centimeter_per_second_squared_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, acceleration_v>
{
    using type = millimeter_per_second_squared_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, acceleration_v>
{
    using type = kilometer_per_second_squared_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<980665, 100000>, acceleration_v>
{
    using type = standard_gravity_t;
};

} // PKR_UNITS_NAMESPACE














