#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Pressure dimension
inline constexpr dimension_t pressure_dimension{-1, 1, -2, 0, 0, 0, 0};

// Strong type for pascal (SI base unit)
struct pascal final : public unit_t<double, std::ratio<1, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"pascal"};
    constexpr std::string_view symbol{"Pa"};
    constexpr std::wstring_view w_symbol{L"Pa"};
    constexpr std::u8string_view u8_symbol{u8"Pa"};
};

// Strong type for hectopascal
struct hectopascal final : public unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"hectopascal"};
    constexpr std::string_view symbol{"hPa"};
    constexpr std::wstring_view w_symbol{L"hPa"};
    constexpr std::u8string_view u8_symbol{u8"hPa"};
};

// Strong type for kilopascal
struct kilopascal final : public unit_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilopascal"};
    constexpr std::string_view symbol{"kPa"};
    constexpr std::wstring_view w_symbol{L"kPa"};
    constexpr std::u8string_view u8_symbol{u8"kPa"};
};

// Strong type for megapascal
struct megapascal final : public unit_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"megapascal"};
    constexpr std::string_view symbol{"MPa"};
    constexpr std::wstring_view w_symbol{L"MPa"};
    constexpr std::u8string_view u8_symbol{u8"MPa"};
};

// Strong type for micropascal
struct micropascal final : public unit_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"micropascal"};
    constexpr std::string_view symbol{"µPa"};
    constexpr std::wstring_view w_symbol{L"µPa"};
    constexpr std::u8string_view u8_symbol{u8"µPa"};
};

// Strong type for millibar
struct millibar final : public unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"millibar"};
    constexpr std::string_view symbol{"mbar"};
    constexpr std::wstring_view w_symbol{L"mbar"};
    constexpr std::u8string_view u8_symbol{u8"mbar"};
};

// Strong type for bar
struct bar final : public unit_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"bar"};
    constexpr std::string_view symbol{"bar"};
    constexpr std::wstring_view w_symbol{L"bar"};
    constexpr std::u8string_view u8_symbol{u8"bar"};
};

// Strong type for atmosphere
struct atmosphere final : public unit_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<101325, 1>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"atmosphere"};
    constexpr std::string_view symbol{"atm"};
    constexpr std::wstring_view w_symbol{L"atm"};
    constexpr std::u8string_view u8_symbol{u8"atm"};
};

// Strong type for psi (pounds per square inch)
struct psi final : public unit_t<double, std::ratio<6894757293, 1000000000>, pressure_dimension>
{
    using _base = unit_t<double, std::ratio<6894757293, 1000000000>, pressure_dimension>;
    using _base::_base;
    constexpr std::string_view name{"psi"};
    constexpr std::string_view symbol{"psi"};
    constexpr std::wstring_view w_symbol{L"psi"};
    constexpr std::u8string_view u8_symbol{u8"psi"};
};

} // PKR_SI_NAMESPACE


