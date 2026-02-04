#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

namespace PKR_UNITS_NAMESPACE
{
// Electric potential dimension
inline constexpr dimension_t electric_potential_dimension{2, 1, -3, -1, 0, 0, 0};

template <is_unit_value_type_c T>
struct volt_t final : public details::unit_t<T, std::ratio<1, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, electric_potential_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"volt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"V"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"V"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"V"};
};

template <is_unit_value_type_c T>
volt_t(T) -> volt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_potential_dimension)
volt_t(const U&) -> volt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilovolt_t final : public details::unit_t<T, std::ratio<1000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, electric_potential_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilovolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kV"};
};

template <is_unit_value_type_c T>
kilovolt_t(T) -> kilovolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_potential_dimension)
kilovolt_t(const U&) -> kilovolt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megavolt_t final : public details::unit_t<T, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, electric_potential_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megavolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MV"};
};

template <is_unit_value_type_c T>
megavolt_t(T) -> megavolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_potential_dimension)
megavolt_t(const U&) -> megavolt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millivolt_t final : public details::unit_t<T, std::ratio<1, 1000>, electric_potential_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, electric_potential_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millivolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mV"};
};

template <is_unit_value_type_c T>
millivolt_t(T) -> millivolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_potential_dimension)
millivolt_t(const U&) -> millivolt_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microvolt_t final : public details::unit_t<T, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, electric_potential_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microvolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5V"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5V"};
};

template <is_unit_value_type_c T>
microvolt_t(T) -> microvolt_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_potential_dimension)
microvolt_t(const U&) -> microvolt_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for electric potential units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, electric_potential_dimension>
{
    using type = volt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, electric_potential_dimension>
{
    using type = kilovolt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using type = megavolt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, electric_potential_dimension>
{
    using type = millivolt_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using type = microvolt_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
