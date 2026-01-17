#pragma once

#include <format>
#include <string_view>
#include <si_units/impl/details/si_unit.h>
#include <si_units/derived/velocity/details/velocity_units.h>

PKR_SI_BEGIN_NAMESPACE {
namespace formatting {

// ============================================================================
// Helper to deduce velocity unit components from ratio using specialization
// ============================================================================

// Primary template - unknown ratios default to m/s
template<typename VelocityRatio, typename CharType = char>
struct velocity_unit_deducer;

// ASCII specializations
template<> struct velocity_unit_deducer<std::ratio<1, 1>, char> {
    static constexpr std::string_view length_unit = "m";
    static constexpr std::string_view time_unit = "s";
};

template<> struct velocity_unit_deducer<std::ratio<5, 18>, char> {
    static constexpr std::string_view length_unit = "km";
    static constexpr std::string_view time_unit = "h";
};

template<> struct velocity_unit_deducer<std::ratio<1, 100>, char> {
    static constexpr std::string_view length_unit = "cm";
    static constexpr std::string_view time_unit = "s";
};

template<> struct velocity_unit_deducer<std::ratio<1, 1000>, char> {
    static constexpr std::string_view length_unit = "mm";
    static constexpr std::string_view time_unit = "s";
};

template<> struct velocity_unit_deducer<std::ratio<1000, 1>, char> {
    static constexpr std::string_view length_unit = "km";
    static constexpr std::string_view time_unit = "s";
};

// UTF-8 specializations
template<> struct velocity_unit_deducer<std::ratio<1, 1>, char8_t> {
    static constexpr std::u8string_view length_unit = u8"m";
    static constexpr std::u8string_view time_unit = u8"s";
};

template<> struct velocity_unit_deducer<std::ratio<5, 18>, char8_t> {
    static constexpr std::u8string_view length_unit = u8"km";
    static constexpr std::u8string_view time_unit = u8"h";
};

template<> struct velocity_unit_deducer<std::ratio<1, 100>, char8_t> {
    static constexpr std::u8string_view length_unit = u8"cm";
    static constexpr std::u8string_view time_unit = u8"s";
};

template<> struct velocity_unit_deducer<std::ratio<1, 1000>, char8_t> {
    static constexpr std::u8string_view length_unit = u8"mm";
    static constexpr std::u8string_view time_unit = u8"s";
};

template<> struct velocity_unit_deducer<std::ratio<1000, 1>, char8_t> {
    static constexpr std::u8string_view length_unit = u8"km";
    static constexpr std::u8string_view time_unit = u8"s";
};

// Wide character specializations
template<> struct velocity_unit_deducer<std::ratio<1, 1>, wchar_t> {
    static constexpr std::wstring_view length_unit = L"m";
    static constexpr std::wstring_view time_unit = L"s";
};

template<> struct velocity_unit_deducer<std::ratio<5, 18>, wchar_t> {
    static constexpr std::wstring_view length_unit = L"km";
    static constexpr std::wstring_view time_unit = L"h";
};

template<> struct velocity_unit_deducer<std::ratio<1, 100>, wchar_t> {
    static constexpr std::wstring_view length_unit = L"cm";
    static constexpr std::wstring_view time_unit = L"s";
};

template<> struct velocity_unit_deducer<std::ratio<1, 1000>, wchar_t> {
    static constexpr std::wstring_view length_unit = L"mm";
    static constexpr std::wstring_view time_unit = L"s";
};

template<> struct velocity_unit_deducer<std::ratio<1000, 1>, wchar_t> {
    static constexpr std::wstring_view length_unit = L"km";
    static constexpr std::wstring_view time_unit = L"s";
};

// Primary template specializations for unknown ratios - fallback to m/s
template<typename Ratio>
struct velocity_unit_deducer<Ratio, char> {
    static constexpr std::string_view length_unit = "m";
    static constexpr std::string_view time_unit = "s";
};

template<typename Ratio>
struct velocity_unit_deducer<Ratio, char8_t> {
    static constexpr std::u8string_view length_unit = u8"m";
    static constexpr std::u8string_view time_unit = u8"s";
};

template<typename Ratio>
struct velocity_unit_deducer<Ratio, wchar_t> {
    static constexpr std::wstring_view length_unit = L"m";
    static constexpr std::wstring_view time_unit = L"s";
};

} // namespace formatting
} // PKR_SI_NAMESPACE

namespace std
{

// ============================================================================
// Velocity Formatter - ASCII (char)
// ============================================================================

template<typename type_t, typename ratio_t>
struct formatter<si::unit_t<type_t, ratio_t, si::velocity_dimension>, char>
{
    std::formatter<type_t, char> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::velocity_dimension>& unit, FormatContext& ctx) const
    {
        using deducer = si::formatting::velocity_unit_deducer<ratio_t, char>;
        
        // Check if this is a known ratio - if not, convert to m/s
        constexpr bool is_known_ratio = 
            std::is_same_v<ratio_t, std::ratio<1, 1>> ||
            std::is_same_v<ratio_t, std::ratio<5, 18>> ||
            std::is_same_v<ratio_t, std::ratio<1, 100>> ||
            std::is_same_v<ratio_t, std::ratio<1, 1000>> ||
            std::is_same_v<ratio_t, std::ratio<1000, 1>>;
        
        if constexpr (is_known_ratio) {
            auto out = m_value_formatter.format(unit.value(), ctx);
            return std::format_to(out, " {}/{}", deducer::length_unit, deducer::time_unit);
        } else {
            // Convert unknown ratio to meters per second
            type_t mps_value = unit.value() * static_cast<type_t>(ratio_t::num) / static_cast<type_t>(ratio_t::den);
            auto out = m_value_formatter.format(mps_value, ctx);
            return std::format_to(out, " {}/{}", deducer::length_unit, deducer::time_unit);
        }
    }
};

// ============================================================================
// Velocity Formatter - UTF-8 (char8_t)
// ============================================================================

template<typename type_t, typename ratio_t>
struct formatter<si::unit_t<type_t, ratio_t, si::velocity_dimension>, char8_t>
{
    std::formatter<type_t, char8_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::velocity_dimension>& unit, FormatContext& ctx) const
    {
        using deducer = si::formatting::velocity_unit_deducer<ratio_t, char8_t>;
        
        // Check if this is a known ratio - if not, convert to m/s
        constexpr bool is_known_ratio = 
            std::is_same_v<ratio_t, std::ratio<1, 1>> ||
            std::is_same_v<ratio_t, std::ratio<5, 18>> ||
            std::is_same_v<ratio_t, std::ratio<1, 100>> ||
            std::is_same_v<ratio_t, std::ratio<1, 1000>> ||
            std::is_same_v<ratio_t, std::ratio<1000, 1>>;
        
        if constexpr (is_known_ratio) {
            auto out = m_value_formatter.format(unit.value(), ctx);
            return std::format_to(out, u8" {}/{}", deducer::length_unit, deducer::time_unit);
        } else {
            // Convert unknown ratio to meters per second
            type_t mps_value = unit.value() * static_cast<type_t>(ratio_t::num) / static_cast<type_t>(ratio_t::den);
            auto out = m_value_formatter.format(mps_value, ctx);
            return std::format_to(out, u8" {}/{}", deducer::length_unit, deducer::time_unit);
        }
    }
};

// ============================================================================
// Velocity Formatter - Wide Character (wchar_t)
// ============================================================================

template<typename type_t, typename ratio_t>
struct formatter<si::unit_t<type_t, ratio_t, si::velocity_dimension>, wchar_t>
{
    std::formatter<type_t, wchar_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::velocity_dimension>& unit, FormatContext& ctx) const
    {
        using deducer = si::formatting::velocity_unit_deducer<ratio_t, wchar_t>;
        
        // Check if this is a known ratio - if not, convert to m/s
        constexpr bool is_known_ratio = 
            std::is_same_v<ratio_t, std::ratio<1, 1>> ||
            std::is_same_v<ratio_t, std::ratio<5, 18>> ||
            std::is_same_v<ratio_t, std::ratio<1, 100>> ||
            std::is_same_v<ratio_t, std::ratio<1, 1000>> ||
            std::is_same_v<ratio_t, std::ratio<1000, 1>>;
        
        if constexpr (is_known_ratio) {
            auto out = m_value_formatter.format(unit.value(), ctx);
            return std::format_to(out, L" {}/{}", deducer::length_unit, deducer::time_unit);
        } else {
            // Convert unknown ratio to meters per second
            type_t mps_value = unit.value() * static_cast<type_t>(ratio_t::num) / static_cast<type_t>(ratio_t::den);
            auto out = m_value_formatter.format(mps_value, ctx);
            return std::format_to(out, L" {}/{}", deducer::length_unit, deducer::time_unit);
        }
    }
};

} // namespace std


