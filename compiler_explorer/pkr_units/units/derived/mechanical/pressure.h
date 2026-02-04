#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

namespace PKR_UNITS_NAMESPACE
{
// Pressure dimension: kg·m⁻¹·s⁻² (M·L⁻¹·T⁻²)
inline constexpr dimension_t pressure_dimension{-1, 1, -2, 0, 0, 0, 0, 0};

// Pressure units (Pascal and derived)
// Base unit: Pascal (Pa) = kg·m⁻¹·s⁻²
template <is_unit_value_type_c T>
struct pascal_t final : public details::unit_t<T, std::ratio<1, 1>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"pascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pa"};
};

template <is_unit_value_type_c T>
pascal_t(T) -> pascal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
pascal_t(const U&) -> pascal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilopascal_t final : public details::unit_t<T, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilopascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kPa"};
};

template <is_unit_value_type_c T>
kilopascal_t(T) -> kilopascal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
kilopascal_t(const U&) -> kilopascal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct hectopascal_t final : public details::unit_t<T, std::ratio<100, 1>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectopascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hPa"};
};

template <is_unit_value_type_c T>
hectopascal_t(T) -> hectopascal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
hectopascal_t(const U&) -> hectopascal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megapascal_t final : public details::unit_t<T, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megapascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MPa"};
};

template <is_unit_value_type_c T>
megapascal_t(T) -> megapascal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
megapascal_t(const U&) -> megapascal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct micropascal_t final : public details::unit_t<T, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"micropascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5Pa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5Pa"};
};

template <is_unit_value_type_c T>
micropascal_t(T) -> micropascal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
micropascal_t(const U&) -> micropascal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millipascal_t final : public details::unit_t<T, std::ratio<1, 1000>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millipascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mPa"};
};

template <is_unit_value_type_c T>
millipascal_t(T) -> millipascal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
millipascal_t(const U&) -> millipascal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanopascal_t final : public details::unit_t<T, std::ratio<1, 1000000000>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanopascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nPa"};
};

template <is_unit_value_type_c T>
nanopascal_t(T) -> nanopascal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
nanopascal_t(const U&) -> nanopascal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct bar_t final : public details::unit_t<T, std::ratio<100000, 1>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"bar"};
    [[maybe_unused]] static constexpr std::string_view symbol{"bar"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"bar"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"bar"};
};

template <is_unit_value_type_c T>
bar_t(T) -> bar_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
bar_t(const U&) -> bar_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct atmosphere_t final : public details::unit_t<T, std::ratio<101325, 1>, pressure_dimension>
{
    using _base = details::unit_t<T, std::ratio<101325, 1>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"atmosphere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"atm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"atm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"atm"};
};

template <is_unit_value_type_c T>
atmosphere_t(T) -> atmosphere_t<T>;

// Pressure units
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, pressure_dimension>
{
    using type = pascal_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, pressure_dimension>
{
    using type = kilopascal_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<100, 1>, pressure_dimension>
{
    using type = hectopascal_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, pressure_dimension>
{
    using type = megapascal_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, pressure_dimension>
{
    using type = micropascal_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, pressure_dimension>
{
    using type = millipascal_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, pressure_dimension>
{
    using type = nanopascal_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<100000, 1>, pressure_dimension>
{
    using type = bar_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<101325, 1>, pressure_dimension>
{
    using type = atmosphere_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
