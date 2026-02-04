#pragma once
#include <ratio>
#include <string_view>
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/angle_decl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/unit_t_decl.h"

namespace PKR_UNITS_NAMESPACE
{
// HMS hour angle.
// 24h = 360 degrees, so 1h = 15 degrees = pi/12 radians.
// Ratio uses the same pi approximation as degree_t (15 * 1745329/100000000).
template <is_unit_value_type_c T>
struct hms_archour_t final : public details::unit_t<T, std::ratio<26179935, 100000000>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<26179935, 100000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hms_archour"};
    [[maybe_unused]] static constexpr std::string_view symbol{"h"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ʰ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"h"};
};

template <is_unit_value_type_c T>
hms_archour_t(T) -> hms_archour_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
hms_archour_t(const U&) -> hms_archour_t<typename details::is_pkr_unit<U>::value_type>;

// HMS minute (1/60 archour).
template <is_unit_value_type_c T>
struct hms_arcminute_t final : public details::unit_t<T, std::ratio<26179935, 6000000000>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<26179935, 6000000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hms_arcminute"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ᵐ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ᵐ"};
};

template <is_unit_value_type_c T>
hms_arcminute_t(T) -> hms_arcminute_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
hms_arcminute_t(const U&) -> hms_arcminute_t<typename details::is_pkr_unit<U>::value_type>;

// HMS second (1/3600 archour).
template <is_unit_value_type_c T>
struct hms_arcsecond_t final : public details::unit_t<T, std::ratio<26179935, 360000000000>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<26179935, 360000000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hms_arcsecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ˢ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ˢ"};
};

template <is_unit_value_type_c T>
hms_arcsecond_t(T) -> hms_arcsecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
hms_arcsecond_t(const U&) -> hms_arcsecond_t<typename details::is_pkr_unit<U>::value_type>;

// DMS degree (formatting-only).
template <is_unit_value_type_c T>
struct dms_degree_t final : public details::unit_t<T, std::ratio<1745329, 100000000>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<1745329, 100000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"dms_degree"};
    [[maybe_unused]] static constexpr std::string_view symbol{"deg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"°"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"deg"};
};

template <is_unit_value_type_c T>
dms_degree_t(T) -> dms_degree_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
dms_degree_t(const U&) -> dms_degree_t<typename details::is_pkr_unit<U>::value_type>;

// DMS arcminute (formatting-only).
template <is_unit_value_type_c T>
struct dms_arcminute_t final : public details::unit_t<T, std::ratio<1745329, 6000000000>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<1745329, 6000000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"dms_arcminute"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ᵐ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ᵐ"};
};

template <is_unit_value_type_c T>
dms_arcminute_t(T) -> dms_arcminute_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
dms_arcminute_t(const U&) -> dms_arcminute_t<typename details::is_pkr_unit<U>::value_type>;

// DMS arcsecond (formatting-only).
template <is_unit_value_type_c T>
struct dms_arcsecond_t final : public details::unit_t<T, std::ratio<1745329, 360000000000>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<1745329, 360000000000>, angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"dms_arcsecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ˢ"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ˢ"};
};

template <is_unit_value_type_c T>
dms_arcsecond_t(T) -> dms_arcsecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
dms_arcsecond_t(const U&) -> dms_arcsecond_t<typename details::is_pkr_unit<U>::value_type>;

// HMS formatting type (hour/minute/second components).
// Uses a canonical ratio to allow conversion from any angle unit.
template <is_unit_value_type_c T>
struct hms_angle_t final : public details::unit_t<T, std::ratio<1, 1>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, angle_dimension>;
    using _base::_base;
};

template <is_unit_value_type_c T>
hms_angle_t(T) -> hms_angle_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
hms_angle_t(const U&) -> hms_angle_t<typename details::is_pkr_unit<U>::value_type>;

// DMS formatting type (degree/minute/second components).
// Uses a canonical ratio to allow conversion from any angle unit.
template <is_unit_value_type_c T>
struct dms_angle_t final : public details::unit_t<T, std::ratio<1, 1>, angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, angle_dimension>;
    using _base::_base;
};

template <is_unit_value_type_c T>
dms_angle_t(T) -> dms_angle_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == angle_dimension)
dms_angle_t(const U&) -> dms_angle_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// No most derived_unit_type_t specializations needed for formatting-only units.
// ============================================================================
} // namespace PKR_UNITS_NAMESPACE
