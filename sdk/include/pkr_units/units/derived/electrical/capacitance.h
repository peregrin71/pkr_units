#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Capacitance dimension
inline constexpr dimension_t capacitance_v{-2, -1, 4, 2, 0, 0, 0, 0};

// Capacitance units (Farad and derived)
struct farad_t final : public details::unit_t<double, std::ratio<1, 1>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"farad"};
    static constexpr std::string_view symbol{"F"};
    static constexpr std::wstring_view w_symbol{L"F"};
    static constexpr std::u8string_view u8_symbol{u8"F"};
};

struct millifarad_t final : public details::unit_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"millifarad"};
    static constexpr std::string_view symbol{"mF"};
    static constexpr std::wstring_view w_symbol{L"mF"};
    static constexpr std::u8string_view u8_symbol{u8"mF"};
};

struct microfarad_t final : public details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"microfarad"};
    static constexpr std::string_view symbol{"uF"};
    static constexpr std::wstring_view w_symbol{L"\u00b5F"};
    static constexpr std::u8string_view u8_symbol{u8"\u00b5F"};
};

struct nanofarad_t final : public details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"nanofarad"};
    static constexpr std::string_view symbol{"nF"};
    static constexpr std::wstring_view w_symbol{L"nF"};
    static constexpr std::u8string_view u8_symbol{u8"nF"};
};

struct picofarad_t final : public details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000000>, capacitance_v>;
    using _base::_base;
    static constexpr std::string_view name{"picofarad"};
    static constexpr std::string_view symbol{"pF"};
    static constexpr std::wstring_view w_symbol{L"pF"};
    static constexpr std::u8string_view u8_symbol{u8"pF"};
};

// ============================================================================
// Most derived unit type specializations for capacitance units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, capacitance_v>
{
    using type = farad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, capacitance_v>
{
    using type = millifarad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, capacitance_v>
{
    using type = microfarad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000>, capacitance_v>
{
    using type = nanofarad_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000000000>, capacitance_v>
{
    using type = picofarad_t;
};

} // namespace PKR_UNITS_NAMESPACE
