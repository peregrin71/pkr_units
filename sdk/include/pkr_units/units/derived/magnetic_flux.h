#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Magnetic flux dimension: kg·m²·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_dimension{2, 1, -2, -1, 0, 0, 0, 0};

// Magnetic flux density dimension: kg·s⁻²·A⁻¹
inline constexpr dimension_t magnetic_flux_density_dimension{0, 1, -2, -1, 0, 0, 0, 0};

// Magnetic flux quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux = details::unit_t<type_t, ratio_t, magnetic_flux_dimension>;

// Magnetic flux density quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using magnetic_flux_density = details::unit_t<type_t, ratio_t, magnetic_flux_density_dimension>;

// Magnetic flux units (Weber and derived)
// Base unit: Weber (Wb) = kg·m²·s⁻²·A⁻¹

struct weber_t final : public details::unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, magnetic_flux_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"weber"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Wb"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Wb"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Wb"};
};

struct milliweber_t final : public details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"milliweber"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mWb"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mWb"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mWb"};
};

struct microweber_t final : public details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microweber"};

    [[maybe_unused]] static constexpr std::string_view symbol{"uWb"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5Wb"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5Wb"};
};

struct nanoweber_t final : public details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanoweber"};

    [[maybe_unused]] static constexpr std::string_view symbol{"nWb"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nWb"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nWb"};
};

struct kiloweber_t final : public details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kiloweber"};

    [[maybe_unused]] static constexpr std::string_view symbol{"kWb"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kWb"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kWb"};
};

// Magnetic flux density units (Tesla and derived)
// Base unit: Tesla (T) = kg·s⁻²·A⁻¹

struct tesla_t final : public details::unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"tesla"};

    [[maybe_unused]] static constexpr std::string_view symbol{"T"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"T"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"T"};
};

struct millitesla_t final : public details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millitesla"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mT"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mT"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mT"};
};

struct microtesla_t final : public details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microtesla"};

    [[maybe_unused]] static constexpr std::string_view symbol{"uT"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5T"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5T"};
};

struct nanotesla_t final : public details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanotesla"};

    [[maybe_unused]] static constexpr std::string_view symbol{"nT"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nT"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nT"};
};

struct kilotesla_t final : public details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilotesla"};

    [[maybe_unused]] static constexpr std::string_view symbol{"kT"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kT"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kT"};
};

struct megatesla_t final : public details::unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megatesla"};

    [[maybe_unused]] static constexpr std::string_view symbol{"MT"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MT"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MT"};
};

// ============================================================================
// Most derived unit type specializations for magnetic flux units
// ============================================================================

// Magnetic flux units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using type = weber_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using type = milliweber_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using type = microweber_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using type = nanoweber_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using type = kiloweber_t;
};

// Magnetic flux density units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using type = tesla_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using type = millitesla_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using type = microtesla_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using type = nanotesla_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using type = kilotesla_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using type = megatesla_t;
};

} // namespace PKR_UNITS_NAMESPACE
