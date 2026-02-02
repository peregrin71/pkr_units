#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Electric resistance dimension
inline constexpr dimension_t electric_resistance_dimension{2, 1, -3, -2, 0, 0, 0};

// Electric resistance units (Ohm and derived)
struct ohm_t final : public details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, electric_resistance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"ohm"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ohm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u03a9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u03a9"};
};

struct kiloohm_t final : public details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000, 1>, electric_resistance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kiloohm"};

    [[maybe_unused]] static constexpr std::string_view symbol{"kohm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"k\u03a9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"k\u03a9"};
};

struct megaohm_t final : public details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megaohm"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Mohm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"M\u03a9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"M\u03a9"};
};

struct gigaohm_t final : public details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigaohm"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Gohm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"G\u03a9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"G\u03a9"};
};

struct milliohm_t final : public details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, electric_resistance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"milliohm"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mohm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u03a9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u03a9"};
};

struct microohm_t final : public details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microohm"};

    [[maybe_unused]] static constexpr std::string_view symbol{"uohm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5\u03a9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5\u03a9"};
};

// ============================================================================
// Most derived unit type specializations for electric resistance units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, electric_resistance_dimension>
{
    using type = ohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000, 1>, electric_resistance_dimension>
{
    using type = kiloohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000, 1>, electric_resistance_dimension>
{
    using type = megaohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1000000000, 1>, electric_resistance_dimension>
{
    using type = gigaohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, electric_resistance_dimension>
{
    using type = milliohm_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, electric_resistance_dimension>
{
    using type = microohm_t;
};

} // namespace PKR_UNITS_NAMESPACE
