#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Volume units (cubic meter and derived)
// Base unit: cubic meter (m^3)
template <is_unit_value_type_c T>
struct cubic_meter_t final : public unit_t<T, std::ratio<1, 1>, volume_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1>, volume_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"cubic meter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m\u00b3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u00b3"};
};

template <is_unit_value_type_c T>
cubic_meter_t(T) -> cubic_meter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == volume_dimension)
cubic_meter_t(const U&) -> cubic_meter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct cubic_kilometer_t final : public unit_t<T, std::ratio<1000000000, 1>, volume_dimension>
{
    using _base = unit_t<T, std::ratio<1000000000, 1>, volume_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"cubic kilometer"};
    [[maybe_unused]] static constexpr std::string_view symbol{"km\u00b3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"km\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"km\u00b3"};
};

template <is_unit_value_type_c T>
cubic_kilometer_t(T) -> cubic_kilometer_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == volume_dimension)
cubic_kilometer_t(const U&) -> cubic_kilometer_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct cubic_centimeter_t final : public unit_t<T, std::ratio<1, 1000000>, volume_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1000000>, volume_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"cubic centimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cm\u00b3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cm\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cm\u00b3"};
};

template <is_unit_value_type_c T>
cubic_centimeter_t(T) -> cubic_centimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == volume_dimension)
cubic_centimeter_t(const U&) -> cubic_centimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct cubic_millimeter_t final : public unit_t<T, std::ratio<1, 1000000000>, volume_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1000000000>, volume_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"cubic millimeter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mm\u00b3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mm\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mm\u00b3"};
};

template <is_unit_value_type_c T>
cubic_millimeter_t(T) -> cubic_millimeter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == volume_dimension)
cubic_millimeter_t(const U&) -> cubic_millimeter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct liter_t final : public unit_t<T, std::ratio<1, 1000>, volume_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1000>, volume_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"liter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"L"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"L"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"L"};
};

template <is_unit_value_type_c T>
liter_t(T) -> liter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == volume_dimension)
liter_t(const U&) -> liter_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct milliliter_t final : public unit_t<T, std::ratio<1, 1000000>, volume_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1000000>, volume_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milliliter"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mL"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mL"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mL"};
};

template <is_unit_value_type_c T>
milliliter_t(T) -> milliliter_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == volume_dimension)
milliliter_t(const U&) -> milliliter_t<typename details::is_pkr_unit<U>::value_type>;
} // namespace PKR_UNITS_NAMESPACE
