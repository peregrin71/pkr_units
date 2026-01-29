#pragma once

#include <ratio>
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/angle_decl.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// HMS hour angle.
// 24h = 360 degrees, so 1h = 15 degrees = pi/12 radians.
// Ratio uses the same pi approximation as degree_t (15 * 1745329/100000000).
struct hms_archour_t final : public details::unit_t<double, std::ratio<26179935, 100000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<26179935, 100000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hms_archour"};
    static constexpr std::string_view symbol{"h"};
    static constexpr std::wstring_view w_symbol{L"ʰ"};
    static constexpr std::u8string_view u8_symbol{u8"h"};
};

// HMS minute (1/60 archour).
struct hms_arcminute_t final : public details::unit_t<double, std::ratio<26179935, 6000000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<26179935, 6000000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hms_arcminute"};
    static constexpr std::string_view symbol{"m"};
    static constexpr std::wstring_view w_symbol{L"ᵐ"};
    static constexpr std::u8string_view u8_symbol{u8"ᵐ"};
};

// HMS second (1/3600 archour).
struct hms_arcsecond_t final : public details::unit_t<double, std::ratio<26179935, 360000000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<26179935, 360000000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hms_arcsecond"};
    static constexpr std::string_view symbol{"s"};
    static constexpr std::wstring_view w_symbol{L"ˢ"};
    static constexpr std::u8string_view u8_symbol{u8"ˢ"};
};

// DMS degree (formatting-only).
struct dms_degree_t final : public details::unit_t<double, std::ratio<1745329, 100000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1745329, 100000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"dms_degree"};
    static constexpr std::string_view symbol{"deg"};
    static constexpr std::wstring_view w_symbol{L"°"};
    static constexpr std::u8string_view u8_symbol{u8"deg"};
};

// DMS arcminute (formatting-only).
struct dms_arcminute_t final : public details::unit_t<double, std::ratio<1745329, 6000000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1745329, 6000000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"dms_arcminute"};
    static constexpr std::string_view symbol{"m"};
    static constexpr std::wstring_view w_symbol{L"ᵐ"};
    static constexpr std::u8string_view u8_symbol{u8"ᵐ"};
};

// DMS arcsecond (formatting-only).
struct dms_arcsecond_t final : public details::unit_t<double, std::ratio<1745329, 360000000000>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1745329, 360000000000>, angle_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"dms_arcsecond"};
    static constexpr std::string_view symbol{"s"};
    static constexpr std::wstring_view w_symbol{L"ˢ"};
    static constexpr std::u8string_view u8_symbol{u8"ˢ"};
};

// HMS formatting type (hour/minute/second components).
// Uses a canonical ratio to allow conversion from any angle unit.
struct hms_angle_t final : public details::unit_t<double, std::ratio<1, 1>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, angle_dimension>;
    using _base::_base;
};

// DMS formatting type (degree/minute/second components).
// Uses a canonical ratio to allow conversion from any angle unit.
struct dms_angle_t final : public details::unit_t<double, std::ratio<1, 1>, angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, angle_dimension>;
    using _base::_base;
};

// ============================================================================
// No most derived_unit_type_t specializations needed for formatting-only units.
// ============================================================================

} // namespace PKR_UNITS_NAMESPACE
