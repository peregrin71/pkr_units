#pragma once

#include "../../../impl/unit_impl.h"
#include "../../../impl/dimension.h"
#include "../../../impl/namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Energy dimension
inline constexpr dimension_t energy_dimension{2, 1, -2, 0, 0, 0, 0};

// Strong type for joule (SI base unit)
struct joule final : public details::unit_t<double, std::ratio<1, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"joule"};
    const std::string_view symbol{"J"};
    const std::wstring_view w_symbol{L"J"};
    const std::u8string_view u8_symbol{u8"J"};
};

// Strong type for kilojoule
struct kilojoule final : public details::unit_t<double, std::ratio<1000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"kilojoule"};
    const std::string_view symbol{"kJ"};
    const std::wstring_view w_symbol{L"kJ"};
    const std::u8string_view u8_symbol{u8"kJ"};
};

// Strong type for megajoule
struct megajoule final : public details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"megajoule"};
    const std::string_view symbol{"MJ"};
    const std::wstring_view w_symbol{L"MJ"};
    const std::u8string_view u8_symbol{u8"MJ"};
};

// Strong type for gigajoule
struct gigajoule final : public details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"gigajoule"};
    const std::string_view symbol{"GJ"};
    const std::wstring_view w_symbol{L"GJ"};
    const std::u8string_view u8_symbol{u8"GJ"};
};

// Strong type for millijoule
struct millijoule final : public details::unit_t<double, std::ratio<1, 1000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"millijoule"};
    const std::string_view symbol{"mJ"};
    const std::wstring_view w_symbol{L"mJ"};
    const std::u8string_view u8_symbol{u8"mJ"};
};

// Strong type for microjoule
struct microjoule final : public details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"microjoule"};
    const std::string_view symbol{"uJ"};
    const std::wstring_view w_symbol{L"µJ"};
    const std::u8string_view u8_symbol{u8"µJ"};
};

// Strong type for calorie
struct calorie final : public details::unit_t<double, std::ratio<4184, 1000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<4184, 1000>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"calorie"};
    const std::string_view symbol{"cal"};
    const std::wstring_view w_symbol{L"cal"};
    const std::u8string_view u8_symbol{u8"cal"};
};

// Strong type for kilocalorie
struct kilocalorie final : public details::unit_t<double, std::ratio<4184, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<4184, 1>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"kilocalorie"};
    const std::string_view symbol{"kcal"};
    const std::wstring_view w_symbol{L"kcal"};
    const std::u8string_view u8_symbol{u8"kcal"};
};

// Strong type for watthour
struct watthour final : public details::unit_t<double, std::ratio<3600, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600, 1>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"watthour"};
    const std::string_view symbol{"Wh"};
    const std::wstring_view w_symbol{L"Wh"};
    const std::u8string_view u8_symbol{u8"Wh"};
};

// Strong type for kilowatthour
struct kilowatthour final : public details::unit_t<double, std::ratio<3600000, 1>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600000, 1>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"kilowatthour"};
    const std::string_view symbol{"kWh"};
    const std::wstring_view w_symbol{L"kWh"};
    const std::u8string_view u8_symbol{u8"kWh"};
};

// Strong type for electronvolt
struct electronvolt final : public details::unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<80108, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"electronvolt"};
    const std::string_view symbol{"eV"};
    const std::wstring_view w_symbol{L"eV"};
    const std::u8string_view u8_symbol{u8"eV"};
};

// Strong type for kiloelectronvolt
struct kiloelectronvolt final : public details::unit_t<double, std::ratio<80108000, 500000000000000000LL>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<80108000, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"kiloelectronvolt"};
    const std::string_view symbol{"keV"};
    const std::wstring_view w_symbol{L"keV"};
    const std::u8string_view u8_symbol{u8"keV"};
};

// Strong type for megaelectronvolt
struct megaelectronvolt final : public details::unit_t<double, std::ratio<80108000000, 500000000000000000LL>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<80108000000, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"megaelectronvolt"};
    const std::string_view symbol{"MeV"};
    const std::wstring_view w_symbol{L"MeV"};
    const std::u8string_view u8_symbol{u8"MeV"};
};

// Strong type for gigaelectronvolt
struct gigaelectronvolt final : public details::unit_t<double, std::ratio<80108000000000LL, 500000000000000000LL>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<80108000000000LL, 500000000000000000LL>, energy_dimension>;
    using _base::_base;
    const std::string_view name{"gigaelectronvolt"};
    const std::string_view symbol{"GeV"};
    const std::wstring_view w_symbol{L"GeV"};
    const std::u8string_view u8_symbol{u8"GeV"};
};

} // PKR_UNITS_NAMESPACE








