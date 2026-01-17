#pragma once

#include <format>
#include <string>
#include <string_view>
#include <si_units/impl/details/si_unit.h>
#include <si_units/standard/temperature.h>

namespace std
{

// ============================================================================
// ASCII Formatter for Temperature Units (char / std::string)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::temperature_dimension>::dimension_type, si::temperature_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::temperature_dimension>, char>
{
    std::formatter<type_t, char> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::temperature_dimension>& unit, FormatContext& ctx) const
    {
        auto out = m_value_formatter.format(unit.value(), ctx);
        // Temperature uses K (Kelvin) as the base unit
        return std::format_to(out, " K");
    }
};

// ============================================================================
// Unicode Formatter for Temperature Units (char8_t / std::u8string)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::temperature_dimension>::dimension_type, si::temperature_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::temperature_dimension>, char8_t>
{
    std::formatter<type_t, char8_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::temperature_dimension>& unit, FormatContext& ctx) const
    {
        auto out = m_value_formatter.format(unit.value(), ctx);
        // Temperature uses K (Kelvin) as the base unit
        return std::format_to(out, u8" K");
    }
};

// ============================================================================
// Wide Character Formatter for Temperature Units (wchar_t / std::wstring)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::temperature_dimension>::dimension_type, si::temperature_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::temperature_dimension>, wchar_t>
{
    std::formatter<type_t, wchar_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::temperature_dimension>& unit, FormatContext& ctx) const
    {
        auto out = m_value_formatter.format(unit.value(), ctx);
        // Temperature uses K (Kelvin) as the base unit
        return std::format_to(out, L" K");
    }
};

} // namespace std
