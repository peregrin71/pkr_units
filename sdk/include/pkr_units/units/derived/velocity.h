#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for meter per second (SI base unit)
template <is_unit_value_type_c T>
struct meter_per_second_t final : public details::unit_t<T, std::ratio<1, 1>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"meter per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m/s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u00B7s\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u00B7s\u207B\u00B9"};
};

template <is_unit_value_type_c T>
meter_per_second_t(T) -> meter_per_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
meter_per_second_t(const U&) -> meter_per_second_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for kilometer per hour
template <is_unit_value_type_c T>
struct kilometer_per_hour_t final : public details::unit_t<T, std::ratio<5, 18>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<5, 18>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilometer per hour"};
    [[maybe_unused]] static constexpr std::string_view symbol{"km/h"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00B7h\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km\u00B7h\u207B\u00B9"};
};

template <is_unit_value_type_c T>
kilometer_per_hour_t(T) -> kilometer_per_hour_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
kilometer_per_hour_t(const U&) -> kilometer_per_hour_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for centimeter per second
template <is_unit_value_type_c T>
struct centimeter_per_second_t final : public details::unit_t<T, std::ratio<1, 100>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 100>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centimeter per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cm/s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm\u00B7s\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm\u00B7s\u207B\u00B9"};
};

template <is_unit_value_type_c T>
centimeter_per_second_t(T) -> centimeter_per_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
centimeter_per_second_t(const U&) -> centimeter_per_second_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for millimeter per second
template <is_unit_value_type_c T>
struct millimeter_per_second_t final : public details::unit_t<T, std::ratio<1, 1000>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millimeter per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mm/s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm\u00B7s\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm\u00B7s\u207B\u00B9"};
};

template <is_unit_value_type_c T>
millimeter_per_second_t(T) -> millimeter_per_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
millimeter_per_second_t(const U&) -> millimeter_per_second_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for kilometer per second
template <is_unit_value_type_c T>
struct kilometer_per_second_t final : public details::unit_t<T, std::ratio<1000, 1>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilometer per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"km/s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00B7s\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km\u00B7s\u207B\u00B9"};
};

template <is_unit_value_type_c T>
kilometer_per_second_t(T) -> kilometer_per_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
kilometer_per_second_t(const U&) -> kilometer_per_second_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for velocity units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, velocity_dimension>
{
    using type = meter_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<5, 18>, velocity_dimension>
{
    using type = kilometer_per_hour_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 100>, velocity_dimension>
{
    using type = centimeter_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, velocity_dimension>
{
    using type = millimeter_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, velocity_dimension>
{
    using type = kilometer_per_second_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
