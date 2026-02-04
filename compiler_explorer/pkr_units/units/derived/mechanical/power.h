#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

namespace PKR_UNITS_NAMESPACE
{
// Power dimension: kg·m²·s⁻³ (M·L²·T⁻³)
inline constexpr dimension_t power_dimension{2, 1, -3, 0, 0, 0, 0, 0};

// Power units (Watt and derived)
// Base unit: Watt (W) = kg·m²·s⁻³
template <is_unit_value_type_c T>
struct watt_t final : public details::unit_t<T, std::ratio<1, 1>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"watt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"W"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W"};
};

template <is_unit_value_type_c T>
watt_t(T) -> watt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
watt_t(const U&) -> watt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilowatt_t final : public details::unit_t<T, std::ratio<1000, 1>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilowatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kW"};
};

template <is_unit_value_type_c T>
kilowatt_t(T) -> kilowatt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
kilowatt_t(const U&) -> kilowatt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megawatt_t final : public details::unit_t<T, std::ratio<1000000, 1>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megawatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MW"};
};

template <is_unit_value_type_c T>
megawatt_t(T) -> megawatt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
megawatt_t(const U&) -> megawatt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gigawatt_t final : public details::unit_t<T, std::ratio<1000000000, 1>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigawatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GW"};
};

template <is_unit_value_type_c T>
gigawatt_t(T) -> gigawatt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
gigawatt_t(const U&) -> gigawatt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microwatt_t final : public details::unit_t<T, std::ratio<1, 1000000>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microwatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5W"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5W"};
};

template <is_unit_value_type_c T>
microwatt_t(T) -> microwatt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
microwatt_t(const U&) -> microwatt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct milliwatt_t final : public details::unit_t<T, std::ratio<1, 1000>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milliwatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mW"};
};

template <is_unit_value_type_c T>
milliwatt_t(T) -> milliwatt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
milliwatt_t(const U&) -> milliwatt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanowatt_t final : public details::unit_t<T, std::ratio<1, 1000000000>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanowatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nW"};
};

template <is_unit_value_type_c T>
nanowatt_t(T) -> nanowatt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
nanowatt_t(const U&) -> nanowatt_t<typename details::is_pkr_unit<U>::value_type>;

// Power units
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, power_dimension>
{
    using type = watt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, power_dimension>
{
    using type = kilowatt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, power_dimension>
{
    using type = megawatt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000000, 1>, power_dimension>
{
    using type = gigawatt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, power_dimension>
{
    using type = microwatt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, power_dimension>
{
    using type = milliwatt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, power_dimension>
{
    using type = nanowatt_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
