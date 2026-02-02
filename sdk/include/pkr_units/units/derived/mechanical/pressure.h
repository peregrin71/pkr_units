#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Pressure dimension: kg·m⁻¹·s⁻² (M·L⁻¹·T⁻²)
inline constexpr dimension_t pressure_dimension{-1, 1, -2, 0, 0, 0, 0, 0};

// Pressure units (Pascal and derived)
// Base unit: Pascal (Pa) = kg·m⁻¹·s⁻²

struct pascal_t final : public details::unit_t<double, std::ratio<1, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"pascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pa"};
};

struct kilopascal_t final : public details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilopascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kPa"};
};

struct hectopascal_t final : public details::unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectopascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hPa"};
};

struct megapascal_t final : public details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megapascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MPa"};
};

struct micropascal_t final : public details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"micropascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5Pa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5Pa"};
};

struct millipascal_t final : public details::unit_t<double, std::ratio<1, 1000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millipascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mPa"};
};

struct nanopascal_t final : public details::unit_t<double, std::ratio<1, 1000000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanopascal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nPa"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nPa"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nPa"};
};

struct bar_t final : public details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"bar"};
    [[maybe_unused]] static constexpr std::string_view symbol{"bar"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"bar"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"bar"};
};

struct atmosphere_t final : public details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"atmosphere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"atm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"atm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"atm"};
};

// Pressure units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, pressure_dimension>
{
    using type = pascal_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using type = kilopascal_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using type = hectopascal_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using type = megapascal_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using type = micropascal_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, pressure_dimension>
{
    using type = millipascal_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, pressure_dimension>
{
    using type = nanopascal_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    using type = bar_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    using type = atmosphere_t;
};

} // namespace PKR_UNITS_NAMESPACE
