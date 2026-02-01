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
    static constexpr std::string_view name{"pascal"};
    static constexpr std::string_view symbol{"Pa"};
    static constexpr std::wstring_view w_symbol{L"Pa"};
    static constexpr std::u8string_view u8_symbol{u8"Pa"};
};

struct kilopascal_t final : public details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilopascal"};
    static constexpr std::string_view symbol{"kPa"};
    static constexpr std::wstring_view w_symbol{L"kPa"};
    static constexpr std::u8string_view u8_symbol{u8"kPa"};
};

struct hectopascal_t final : public details::unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectopascal"};
    static constexpr std::string_view symbol{"hPa"};
    static constexpr std::wstring_view w_symbol{L"hPa"};
    static constexpr std::u8string_view u8_symbol{u8"hPa"};
};

struct megapascal_t final : public details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megapascal"};
    static constexpr std::string_view symbol{"MPa"};
    static constexpr std::wstring_view w_symbol{L"MPa"};
    static constexpr std::u8string_view u8_symbol{u8"MPa"};
};

struct micropascal_t final : public details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micropascal"};
    static constexpr std::string_view symbol{"uPa"};
    static constexpr std::wstring_view w_symbol{L"\u00b5Pa"};
    static constexpr std::u8string_view u8_symbol{u8"\u00b5Pa"};
};

struct millipascal_t final : public details::unit_t<double, std::ratio<1, 1000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millipascal"};
    static constexpr std::string_view symbol{"mPa"};
    static constexpr std::wstring_view w_symbol{L"mPa"};
    static constexpr std::u8string_view u8_symbol{u8"mPa"};
};

struct nanopascal_t final : public details::unit_t<double, std::ratio<1, 1000000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanopascal"};
    static constexpr std::string_view symbol{"nPa"};
    static constexpr std::wstring_view w_symbol{L"nPa"};
    static constexpr std::u8string_view u8_symbol{u8"nPa"};
};

struct bar_t final : public details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"bar"};
    static constexpr std::string_view symbol{"bar"};
    static constexpr std::wstring_view w_symbol{L"bar"};
    static constexpr std::u8string_view u8_symbol{u8"bar"};
};

struct atmosphere_t final : public details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"atmosphere"};
    static constexpr std::string_view symbol{"atm"};
    static constexpr std::wstring_view w_symbol{L"atm"};
    static constexpr std::u8string_view u8_symbol{u8"atm"};
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
