#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for radian (SI base unit for plane angle)
template <is_unit_value_type_c T>
struct radian_t final : public unit_t<T, std::ratio<1, 1>, angle_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"radian"};
    [[maybe_unused]] static constexpr std::string_view symbol{"rad"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"rad"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"rad"};
};

template <is_unit_value_type_c T>
radian_t(T) -> radian_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
radian_t(const U&) -> radian_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for degree (plane angle)
template <is_unit_value_type_c T>
struct degree_t final : public unit_t<T, std::ratio<1745329, 100000000>, angle_dimension>
{
    using _base = unit_t<T, std::ratio<1745329, 100000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"degree"};
    [[maybe_unused]] static constexpr std::string_view symbol{"deg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00B0"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00B0"};
};

template <is_unit_value_type_c T>
degree_t(T) -> degree_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
degree_t(const U&) -> degree_t<typename details::is_pkr_unit<U>::value_type>;

// Strong type for gradian (plane angle unit, also called gon)
template <is_unit_value_type_c T>
struct gradian_t final : public unit_t<T, std::ratio<1570796, 100000000>, angle_dimension>
{
    using _base = unit_t<T, std::ratio<1570796, 100000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gradian"};
    [[maybe_unused]] static constexpr std::string_view symbol{"grad"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"gon"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"gon"};
};

template <is_unit_value_type_c T>
gradian_t(T) -> gradian_t<T>;

// ============================================================================
// Most derived unit type specializations
// ============================================================================
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, angle_dimension>
{
    using type = radian_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1745329, 100000000>, angle_dimension>
{
    using type = degree_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1570796, 100000000>, angle_dimension>
{
    using type = gradian_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
