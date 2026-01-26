#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Magnetic flux dimension: kg·m²·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_dimension{2, 1, -2, -1, 0, 0, 0, 0};

// Magnetic flux density dimension: kg·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_density_dimension{0, 1, -2, -1, 0, 0, 0, 0};

// Magnetic flux quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux = details::unit_t<type_t, ratio_t, magnetic_flux_dimension>;

// Magnetic flux density quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux_density = details::unit_t<type_t, ratio_t, magnetic_flux_density_dimension>;

// Magnetic flux units (Weber and derived)
// Base unit: Weber (Wb) = kg·m²·s⁻²·A⁻¹

struct weber_t final : public details::unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"weber"};
    static constexpr std::string_view symbol{"Wb"};
    static constexpr std::wstring_view w_symbol{L"Wb"};
    static constexpr std::u8string_view u8_symbol{u8"Wb"};
};

struct milliweber_t final : public details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliweber"};
    static constexpr std::string_view symbol{"mWb"};
    static constexpr std::wstring_view w_symbol{L"mWb"};
    static constexpr std::u8string_view u8_symbol{u8"mWb"};
};

struct microweber_t final : public details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microweber"};
    static constexpr std::string_view symbol{"uWb"};
    static constexpr std::wstring_view w_symbol{L"µWb"};
    static constexpr std::u8string_view u8_symbol{u8"µWb"};
};

struct nanoweber_t final : public details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanoweber"};
    static constexpr std::string_view symbol{"nWb"};
    static constexpr std::wstring_view w_symbol{L"nWb"};
    static constexpr std::u8string_view u8_symbol{u8"nWb"};
};

struct kiloweber_t final : public details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kiloweber"};
    static constexpr std::string_view symbol{"kWb"};
    static constexpr std::wstring_view w_symbol{L"kWb"};
    static constexpr std::u8string_view u8_symbol{u8"kWb"};
};

// Magnetic flux density units (Tesla and derived)
// Base unit: Tesla (T) = kg·s⁻²·A⁻¹

struct tesla_t final : public details::unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"tesla"};
    static constexpr std::string_view symbol{"T"};
    static constexpr std::wstring_view w_symbol{L"T"};
    static constexpr std::u8string_view u8_symbol{u8"T"};
};

struct millitesla_t final : public details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millitesla"};
    static constexpr std::string_view symbol{"mT"};
    static constexpr std::wstring_view w_symbol{L"mT"};
    static constexpr std::u8string_view u8_symbol{u8"mT"};
};

struct microtesla_t final : public details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microtesla"};
    static constexpr std::string_view symbol{"uT"};
    static constexpr std::wstring_view w_symbol{L"µT"};
    static constexpr std::u8string_view u8_symbol{u8"µT"};
};

struct nanotesla_t final : public details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanotesla"};
    static constexpr std::string_view symbol{"nT"};
    static constexpr std::wstring_view w_symbol{L"nT"};
    static constexpr std::u8string_view u8_symbol{u8"nT"};
};

struct kilotesla_t final : public details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilotesla"};
    static constexpr std::string_view symbol{"kT"};
    static constexpr std::wstring_view w_symbol{L"kT"};
    static constexpr std::u8string_view u8_symbol{u8"kT"};
};

struct megatesla_t final : public details::unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megatesla"};
    static constexpr std::string_view symbol{"MT"};
    static constexpr std::wstring_view w_symbol{L"MT"};
    static constexpr std::u8string_view u8_symbol{u8"MT"};
};

// ============================================================================
// Most derived unit type specializations for magnetic flux units
// ============================================================================

// Magnetic flux units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using type = weber_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using type = milliweber_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using type = microweber_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using type = nanoweber_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using type = kiloweber_t;
};

// Magnetic flux density units
template<>
struct details::named_unit_type_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using type = tesla_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using type = millitesla_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using type = microtesla_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using type = nanotesla_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using type = kilotesla_t;
};

template<>
struct details::named_unit_type_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using type = megatesla_t;
};

} // PKR_UNITS_NAMESPACE















