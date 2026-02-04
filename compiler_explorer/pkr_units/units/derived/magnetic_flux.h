#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

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
template <is_unit_value_type_c T>
struct weber_t final : public details::unit_t<T, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, magnetic_flux_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"weber"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Wb"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Wb"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Wb"};
};

template <is_unit_value_type_c T>
weber_t(T) -> weber_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_dimension)
weber_t(const U&) -> weber_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct milliweber_t final : public details::unit_t<T, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, magnetic_flux_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"milliweber"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mWb"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mWb"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mWb"};
};

template <is_unit_value_type_c T>
milliweber_t(T) -> milliweber_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_dimension)
milliweber_t(const U&) -> milliweber_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microweber_t final : public details::unit_t<T, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, magnetic_flux_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microweber"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uWb"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5Wb"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5Wb"};
};

template <is_unit_value_type_c T>
microweber_t(T) -> microweber_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_dimension)
microweber_t(const U&) -> microweber_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanoweber_t final : public details::unit_t<T, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, magnetic_flux_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanoweber"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nWb"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nWb"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nWb"};
};

template <is_unit_value_type_c T>
nanoweber_t(T) -> nanoweber_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_dimension)
nanoweber_t(const U&) -> nanoweber_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kiloweber_t final : public details::unit_t<T, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, magnetic_flux_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kiloweber"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kWb"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kWb"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kWb"};
};

template <is_unit_value_type_c T>
kiloweber_t(T) -> kiloweber_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_dimension)
kiloweber_t(const U&) -> kiloweber_t<typename details::is_pkr_unit<U>::value_type>;

// Magnetic flux density units (Tesla and derived)
// Base unit: Tesla (T) = kg·s⁻²·A⁻¹
template <is_unit_value_type_c T>
struct tesla_t final : public details::unit_t<T, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, magnetic_flux_density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"tesla"};
    [[maybe_unused]] static constexpr std::string_view symbol{"T"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"T"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"T"};
};

template <is_unit_value_type_c T>
tesla_t(T) -> tesla_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_density_dimension)
tesla_t(const U&) -> tesla_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millitesla_t final : public details::unit_t<T, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, magnetic_flux_density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millitesla"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mT"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mT"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mT"};
};

template <is_unit_value_type_c T>
millitesla_t(T) -> millitesla_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_density_dimension)
millitesla_t(const U&) -> millitesla_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microtesla_t final : public details::unit_t<T, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, magnetic_flux_density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microtesla"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uT"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5T"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5T"};
};

template <is_unit_value_type_c T>
microtesla_t(T) -> microtesla_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_density_dimension)
microtesla_t(const U&) -> microtesla_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanotesla_t final : public details::unit_t<T, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanotesla"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nT"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nT"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nT"};
};

template <is_unit_value_type_c T>
nanotesla_t(T) -> nanotesla_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_density_dimension)
nanotesla_t(const U&) -> nanotesla_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilotesla_t final : public details::unit_t<T, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilotesla"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kT"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kT"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kT"};
};

template <is_unit_value_type_c T>
kilotesla_t(T) -> kilotesla_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_density_dimension)
kilotesla_t(const U&) -> kilotesla_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct megatesla_t final : public details::unit_t<T, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, magnetic_flux_density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megatesla"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MT"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MT"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MT"};
};

// ============================================================================
// Most derived unit type specializations for magnetic flux units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, magnetic_flux_dimension>
{
    using type = weber_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, magnetic_flux_dimension>
{
    using type = milliweber_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, magnetic_flux_dimension>
{
    using type = microweber_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, magnetic_flux_dimension>
{
    using type = nanoweber_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, magnetic_flux_dimension>
{
    using type = kiloweber_t<T>;
};

// Magnetic flux density units
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, magnetic_flux_density_dimension>
{
    using type = tesla_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, magnetic_flux_density_dimension>
{
    using type = millitesla_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, magnetic_flux_density_dimension>
{
    using type = microtesla_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, magnetic_flux_density_dimension>
{
    using type = nanotesla_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, magnetic_flux_density_dimension>
{
    using type = kilotesla_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, magnetic_flux_density_dimension>
{
    using type = megatesla_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
