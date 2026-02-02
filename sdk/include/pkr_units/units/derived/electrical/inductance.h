#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Inductance dimension
inline constexpr dimension_t inductance_dimension{2, 1, -2, -2, 0, 0, 0};

// Inductance units (Henry and derived)
struct henry_t final : public details::unit_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, inductance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"henry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"H"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"H"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"H"};
};

struct millihenry_t final : public details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millihenry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mH"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mH"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mH"};
};

struct microhenry_t final : public details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microhenry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uH"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5H"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5H"};
};

struct nanohenry_t final : public details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanohenry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nH"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nH"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nH"};
};

// ============================================================================
// Most derived unit type specializations for inductance units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using type = henry_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using type = millihenry_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using type = microhenry_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using type = nanohenry_t;
};

} // namespace PKR_UNITS_NAMESPACE
