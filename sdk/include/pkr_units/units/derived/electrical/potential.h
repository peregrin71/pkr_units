#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Electric potential dimension
inline constexpr dimension_t electric_potential_dimension{2, 1, -3, -1, 0, 0, 0};

// Electric potential units (Volt and derived)
struct volt_t final : public details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_potential_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"volt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"V"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"V"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"V"};
};

struct kilovolt_t final : public details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_potential_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilovolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kV"};
};

struct megavolt_t final : public details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_potential_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megavolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MV"};
};

struct millivolt_t final : public details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_potential_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millivolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mV"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mV"};
};

struct microvolt_t final : public details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_potential_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microvolt"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uV"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5V"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5V"};
};

// ============================================================================
// Most derived unit type specializations for electric potential units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, electric_potential_dimension>
{
    using type = volt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, electric_potential_dimension>
{
    using type = kilovolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, electric_potential_dimension>
{
    using type = megavolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, electric_potential_dimension>
{
    using type = millivolt_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, electric_potential_dimension>
{
    using type = microvolt_t;
};

} // namespace PKR_UNITS_NAMESPACE
