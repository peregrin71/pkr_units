#pragma once

#include "../../../impl/unit_impl.h"
#include "../../../impl/dimension.h"
#include "../../../impl/namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Pressure dimension
inline constexpr dimension_t pressure_dimension{-1, 1, -2, 0, 0, 0, 0};

// Strong type for pascal (SI base unit)
struct pascal final : public details::unit_t<double, std::ratio<1, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pascal"};
    static constexpr std::string_view symbol{"Pa"};
    static constexpr std::wstring_view w_symbol{L"Pa"};
    static constexpr std::u8string_view u8_symbol{u8"Pa"};
};

// Strong type for hectopascal
struct hectopascal final : public details::unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectopascal"};
    static constexpr std::string_view symbol{"hPa"};
    static constexpr std::wstring_view w_symbol{L"hPa"};
    static constexpr std::u8string_view u8_symbol{u8"hPa"};
};

// Strong type for kilopascal
struct kilopascal final : public details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilopascal"};
    static constexpr std::string_view symbol{"kPa"};
    static constexpr std::wstring_view w_symbol{L"kPa"};
    static constexpr std::u8string_view u8_symbol{u8"kPa"};
};

// Strong type for megapascal
struct megapascal final : public details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megapascal"};
    static constexpr std::string_view symbol{"MPa"};
    static constexpr std::wstring_view w_symbol{L"MPa"};
    static constexpr std::u8string_view u8_symbol{u8"MPa"};
};

// Strong type for micropascal
struct micropascal final : public details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micropascal"};
    static constexpr std::string_view symbol{"uPa"};
    static constexpr std::wstring_view w_symbol{L"µPa"};
    static constexpr std::u8string_view u8_symbol{u8"µPa"};
};

// Strong type for millibar
struct millibar final : public details::unit_t<double, std::ratio<100, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millibar"};
    static constexpr std::string_view symbol{"mbar"};
    static constexpr std::wstring_view w_symbol{L"mbar"};
    static constexpr std::u8string_view u8_symbol{u8"mbar"};
};

// Strong type for bar
struct bar final : public details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<100000, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"bar"};
    static constexpr std::string_view symbol{"bar"};
    static constexpr std::wstring_view w_symbol{L"bar"};
    static constexpr std::u8string_view u8_symbol{u8"bar"};
};

// Strong type for atmosphere
struct atmosphere final : public details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<101325, 1>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"atmosphere"};
    static constexpr std::string_view symbol{"atm"};
    static constexpr std::wstring_view w_symbol{L"atm"};
    static constexpr std::u8string_view u8_symbol{u8"atm"};
};

// Strong type for psi (pounds per square inch)
struct psi final : public details::unit_t<double, std::ratio<6894757293, 1000000000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<6894757293, 1000000000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"psi"};
    static constexpr std::string_view symbol{"psi"};
    static constexpr std::wstring_view w_symbol{L"psi"};
    static constexpr std::u8string_view u8_symbol{u8"psi"};
};

} // PKR_UNITS_NAMESPACE








