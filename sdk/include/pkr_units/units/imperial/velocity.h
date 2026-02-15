#pragma once
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Imperial velocity units
template <is_unit_value_type_c T>
struct miles_per_hour_t final : public details::unit_t<T, std::ratio<1609344, 3600000>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1609344, 3600000>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"miles per hour"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mph"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mph"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mph"};
};

template <is_unit_value_type_c T>
miles_per_hour_t(T) -> miles_per_hour_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
miles_per_hour_t(const U&) -> miles_per_hour_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct feet_per_second_t final : public details::unit_t<T, std::ratio<3048, 10000>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<3048, 10000>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"feet per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ft/s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ft\u00b7s\u207b\u00b9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ft\u00b7s\u207b\u00b9"};
};

template <is_unit_value_type_c T>
feet_per_second_t(T) -> feet_per_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
feet_per_second_t(const U&) -> feet_per_second_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct inches_per_second_t final : public details::unit_t<T, std::ratio<254, 10000>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<254, 10000>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"inches per second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"in/s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"in\u00b7s\u207b\u00b9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"in\u00b7s\u207b\u00b9"};
};

template <is_unit_value_type_c T>
inches_per_second_t(T) -> inches_per_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
inches_per_second_t(const U&) -> inches_per_second_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct knots_t final : public details::unit_t<T, std::ratio<1852, 3600>, velocity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1852, 3600>, velocity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"knots"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kn"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kn"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kn"};
};

template <is_unit_value_type_c T>
knots_t(T) -> knots_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == velocity_dimension)
knots_t(const U&) -> knots_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for imperial velocity units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1609344, 3600000>, velocity_dimension>
{
    using type = miles_per_hour_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<3048, 10000>, velocity_dimension>
{
    using type = feet_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<254, 10000>, velocity_dimension>
{
    using type = inches_per_second_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1852, 3600>, velocity_dimension>
{
    using type = knots_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
