#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Area units (square meter and derived)
// Base unit: square meter (m^2)
template <is_unit_value_type_c T>
struct square_meter_t final : public details::unit_t<T, std::ratio<1, 1>, area_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, area_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"square meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m^2"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u00b2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u00b2"};
};

template <is_unit_value_type_c T>
square_meter_t(T) -> square_meter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == area_dimension)
square_meter_t(const U&) -> square_meter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct square_kilometer_t final : public details::unit_t<T, std::ratio<1000000, 1>, area_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, area_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"square kilometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"km^2"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00b2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km\u00b2"};
};

template <is_unit_value_type_c T>
square_kilometer_t(T) -> square_kilometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == area_dimension)
square_kilometer_t(const U&) -> square_kilometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct square_centimeter_t final : public details::unit_t<T, std::ratio<1, 10000>, area_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 10000>, area_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"square centimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cm^2"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm\u00b2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm\u00b2"};
};

template <is_unit_value_type_c T>
square_centimeter_t(T) -> square_centimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == area_dimension)
square_centimeter_t(const U&) -> square_centimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct square_millimeter_t final : public details::unit_t<T, std::ratio<1, 1000000>, area_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, area_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"square millimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mm^2"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm\u00b2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm\u00b2"};
};

template <is_unit_value_type_c T>
square_millimeter_t(T) -> square_millimeter_t<T>;
} // namespace PKR_UNITS_NAMESPACE
