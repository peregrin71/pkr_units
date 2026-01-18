#pragma once

#include <si_units/impl/details/si_unit.h>
#include <si_units/impl/details/dimension.h>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Magnetic flux dimension: kg·m²·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_dimension{.mass = 1, .length = 2, .time = -2, .current = -1};

// Magnetic flux density dimension: kg·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_density_dimension{.mass = 1, .time = -2, .current = -1};

// Magnetic flux quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux = unit_t<type_t, ratio_t, magnetic_flux_dimension>;

// Magnetic flux density quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux_density = unit_t<type_t, ratio_t, magnetic_flux_density_dimension>;

// Magnetic flux units (Weber and derived)
// Base unit: Weber (Wb) = kg·m²·s⁻²·A⁻¹

struct weber final : public unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"weber"};
    static constexpr std::string_view symbol{"Wb"};
    static constexpr std::wstring_view w_symbol{L"Wb"};
    static constexpr std::u8string_view u8_symbol{u8"Wb"};
};

struct milliweber final : public unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliweber"};
    static constexpr std::string_view symbol{"mWb"};
    static constexpr std::wstring_view w_symbol{L"mWb"};
    static constexpr std::u8string_view u8_symbol{u8"mWb"};
};

struct microweber final : public unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microweber"};
    static constexpr std::string_view symbol{"µWb"};
    static constexpr std::wstring_view w_symbol{L"µWb"};
    static constexpr std::u8string_view u8_symbol{u8"µWb"};
};

struct nanoweber final : public unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanoweber"};
    static constexpr std::string_view symbol{"nWb"};
    static constexpr std::wstring_view w_symbol{L"nWb"};
    static constexpr std::u8string_view u8_symbol{u8"nWb"};
};

struct kiloweber final : public unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kiloweber"};
    static constexpr std::string_view symbol{"kWb"};
    static constexpr std::wstring_view w_symbol{L"kWb"};
    static constexpr std::u8string_view u8_symbol{u8"kWb"};
};

// Magnetic flux density units (Tesla and derived)
// Base unit: Tesla (T) = kg·s⁻²·A⁻¹

struct tesla final : public unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"tesla"};
    static constexpr std::string_view symbol{"T"};
    static constexpr std::wstring_view w_symbol{L"T"};
    static constexpr std::u8string_view u8_symbol{u8"T"};
};

struct millitesla final : public unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millitesla"};
    static constexpr std::string_view symbol{"mT"};
    static constexpr std::wstring_view w_symbol{L"mT"};
    static constexpr std::u8string_view u8_symbol{u8"mT"};
};

struct microtesla final : public unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microtesla"};
    static constexpr std::string_view symbol{"µT"};
    static constexpr std::wstring_view w_symbol{L"µT"};
    static constexpr std::u8string_view u8_symbol{u8"µT"};
};

struct nanotesla final : public unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanotesla"};
    static constexpr std::string_view symbol{"nT"};
    static constexpr std::wstring_view w_symbol{L"nT"};
    static constexpr std::u8string_view u8_symbol{u8"nT"};
};

struct kilotesla final : public unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilotesla"};
    static constexpr std::string_view symbol{"kT"};
    static constexpr std::wstring_view w_symbol{L"kT"};
    static constexpr std::u8string_view u8_symbol{u8"kT"};
};

struct megatesla final : public unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megatesla"};
    static constexpr std::string_view symbol{"MT"};
    static constexpr std::wstring_view w_symbol{L"MT"};
    static constexpr std::u8string_view u8_symbol{u8"MT"};
};

} // PKR_SI_NAMESPACE








