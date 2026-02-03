#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/acceleration_decl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for meter per second squared (SI base unit)
template <is_unit_value_type_c T>
struct meter_per_second_squared_t final : public details::unit_t<T, std::ratio<1, 1>, acceleration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, acceleration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"meter per second squared"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m/s²"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u00B7s\u207B\u00B2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u00B7s\u207B\u00B2"};
};

template <is_unit_value_type_c T>
meter_per_second_squared_t(T) -> meter_per_second_squared_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == acceleration_v)
meter_per_second_squared_t(const U&) -> meter_per_second_squared_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for centimeter per second squared
template <is_unit_value_type_c T>
struct centimeter_per_second_squared_t final : public details::unit_t<T, std::ratio<1, 100>, acceleration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 100>, acceleration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centimeter per second squared"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cm/s²"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm\u00B7s\u207B\u00B2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm\u00B7s\u207B\u00B2"};
};

template <is_unit_value_type_c T>
centimeter_per_second_squared_t(T) -> centimeter_per_second_squared_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == acceleration_v)
centimeter_per_second_squared_t(const U&) -> centimeter_per_second_squared_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for millimeter per second squared
template <is_unit_value_type_c T>
struct millimeter_per_second_squared_t final : public details::unit_t<T, std::ratio<1, 1000>, acceleration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, acceleration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millimeter per second squared"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mm/s²"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm\u00B7s\u207B\u00B2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm\u00B7s\u207B\u00B2"};
};

template <is_unit_value_type_c T>
millimeter_per_second_squared_t(T) -> millimeter_per_second_squared_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == acceleration_v)
millimeter_per_second_squared_t(const U&) -> millimeter_per_second_squared_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for kilometer per second squared
template <is_unit_value_type_c T>
struct kilometer_per_second_squared_t final : public details::unit_t<T, std::ratio<1000, 1>, acceleration_v>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, acceleration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilometer per second squared"};
    [[maybe_unused]] static constexpr std::string_view symbol{"km/s²"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00B7s\u207B\u00B2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km\u00B7s\u207B\u00B2"};
};

template <is_unit_value_type_c T>
kilometer_per_second_squared_t(T) -> kilometer_per_second_squared_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == acceleration_v)
kilometer_per_second_squared_t(const U&) -> kilometer_per_second_squared_t<typename details::is_pkr_unit<U>::value_type>;

// Standard gravity (g) - Strong type
// 1 g = 9.80665 m/s² (exact definition)
// Simplified ratio: ratio<980665, 100000> for practical use
template <is_unit_value_type_c T>
struct standard_gravity_t final : public details::unit_t<T, std::ratio<980665, 100000>, acceleration_v>
{
    using _base = details::unit_t<T, std::ratio<980665, 100000>, acceleration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"standard gravity"};
    [[maybe_unused]] static constexpr std::string_view symbol{"g"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"g"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"g"};
};

template <is_unit_value_type_c T>
standard_gravity_t(T) -> standard_gravity_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == acceleration_v)
standard_gravity_t(const U&) -> standard_gravity_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for acceleration units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, acceleration_v>
{
    using type = meter_per_second_squared_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 100>, acceleration_v>
{
    using type = centimeter_per_second_squared_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, acceleration_v>
{
    using type = millimeter_per_second_squared_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, acceleration_v>
{
    using type = kilometer_per_second_squared_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<980665, 100000>, acceleration_v>
{
    using type = standard_gravity_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
