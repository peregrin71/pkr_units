#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Power dimension: kg·m²·s⁻³ (M·L²·T⁻³)
inline constexpr dimension_t power_dimension{2, 1, -3, 0, 0, 0, 0, 0};

// Power units (Watt and derived)
// Base unit: Watt (W) = kg·m²·s⁻³

struct watt_t final : public details::unit_t<double, std::ratio<1, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, power_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"watt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"W"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W"};
};

struct kilowatt_t final : public details::unit_t<double, std::ratio<1000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, power_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilowatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kW"};
};

struct megawatt_t final : public details::unit_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, power_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megawatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MW"};
};

struct gigawatt_t final : public details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, power_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigawatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GW"};
};

struct microwatt_t final : public details::unit_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, power_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microwatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5W"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5W"};
};

struct milliwatt_t final : public details::unit_t<double, std::ratio<1, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, power_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"milliwatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mW"};
};

struct nanowatt_t final : public details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, power_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanowatt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nW"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nW"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nW"};
};

// Power units
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, power_dimension>
{
    using type = watt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, power_dimension>
{
    using type = kilowatt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, power_dimension>
{
    using type = megawatt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000000, 1>, power_dimension>
{
    using type = gigawatt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, power_dimension>
{
    using type = microwatt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, power_dimension>
{
    using type = milliwatt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, power_dimension>
{
    using type = nanowatt_t;
};

} // namespace PKR_UNITS_NAMESPACE
