#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../../../../impl/common/dimension.h"
#include "../../../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Energy dimension
inline constexpr dimension_t energy_dimension{2, 1, -2, 0, 0, 0, 0};

// Strong type for joule (SI base unit)
struct joule final : public unit_t<double, std::ratio<1, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"joule"};
    constexpr std::string_view symbol{"J"};
    constexpr std::wstring_view w_symbol{L"J"};
    constexpr std::u8string_view u8_symbol{u8"J"};
};

// Strong type for kilojoule
struct kilojoule final : public unit_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilojoule"};
    constexpr std::string_view symbol{"kJ"};
    constexpr std::wstring_view w_symbol{L"kJ"};
    constexpr std::u8string_view u8_symbol{u8"kJ"};
};

// Strong type for megajoule
struct megajoule final : public unit_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"megajoule"};
    constexpr std::string_view symbol{"MJ"};
    constexpr std::wstring_view w_symbol{L"MJ"};
    constexpr std::u8string_view u8_symbol{u8"MJ"};
};

// Strong type for gigajoule
struct gigajoule final : public unit_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"gigajoule"};
    constexpr std::string_view symbol{"GJ"};
    constexpr std::wstring_view w_symbol{L"GJ"};
    constexpr std::u8string_view u8_symbol{u8"GJ"};
};

// Strong type for millijoule
struct millijoule final : public unit_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"millijoule"};
    constexpr std::string_view symbol{"mJ"};
    constexpr std::wstring_view w_symbol{L"mJ"};
    constexpr std::u8string_view u8_symbol{u8"mJ"};
};

// Strong type for microjoule
struct microjoule final : public unit_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"microjoule"};
    constexpr std::string_view symbol{"µJ"};
    constexpr std::wstring_view w_symbol{L"µJ"};
    constexpr std::u8string_view u8_symbol{u8"µJ"};
};

// Strong type for calorie
struct calorie final : public unit_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<4184, 1000>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"calorie"};
    constexpr std::string_view symbol{"cal"};
    constexpr std::wstring_view w_symbol{L"cal"};
    constexpr std::u8string_view u8_symbol{u8"cal"};
};

// Strong type for kilocalorie
struct kilocalorie final : public unit_t<double, std::ratio<4184, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<4184, 1>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilocalorie"};
    constexpr std::string_view symbol{"kcal"};
    constexpr std::wstring_view w_symbol{L"kcal"};
    constexpr std::u8string_view u8_symbol{u8"kcal"};
};

// Strong type for watthour
struct watthour final : public unit_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<3600, 1>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"watthour"};
    constexpr std::string_view symbol{"Wh"};
    constexpr std::wstring_view w_symbol{L"Wh"};
    constexpr std::u8string_view u8_symbol{u8"Wh"};
};

// Strong type for kilowatthour
struct kilowatthour final : public unit_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<3600000, 1>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kilowatthour"};
    constexpr std::string_view symbol{"kWh"};
    constexpr std::wstring_view w_symbol{L"kWh"};
    constexpr std::u8string_view u8_symbol{u8"kWh"};
};

// Strong type for electronvolt
struct electronvolt final : public unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"electronvolt"};
    constexpr std::string_view symbol{"eV"};
    constexpr std::wstring_view w_symbol{L"eV"};
    constexpr std::u8string_view u8_symbol{u8"eV"};
};

// Strong type for kiloelectronvolt
struct kiloelectronvolt final : public unit_t<double, std::ratio<80108000, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108000, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"kiloelectronvolt"};
    constexpr std::string_view symbol{"keV"};
    constexpr std::wstring_view w_symbol{L"keV"};
    constexpr std::u8string_view u8_symbol{u8"keV"};
};

// Strong type for megaelectronvolt
struct megaelectronvolt final : public unit_t<double, std::ratio<80108000000, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108000000, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"megaelectronvolt"};
    constexpr std::string_view symbol{"MeV"};
    constexpr std::wstring_view w_symbol{L"MeV"};
    constexpr std::u8string_view u8_symbol{u8"MeV"};
};

// Strong type for gigaelectronvolt
struct gigaelectronvolt final : public unit_t<double, std::ratio<80108000000000LL, 500000000000000000LL>, energy_dimension>
{
    using _base = unit_t<double, std::ratio<80108000000000LL, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    constexpr std::string_view name{"gigaelectronvolt"};
    constexpr std::string_view symbol{"GeV"};
    constexpr std::wstring_view w_symbol{L"GeV"};
    constexpr std::u8string_view u8_symbol{u8"GeV"};
};

} // PKR_UNITS_NAMESPACE


