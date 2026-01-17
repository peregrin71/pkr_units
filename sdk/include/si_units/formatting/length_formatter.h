#pragma once

#include <format>
#include <string>
#include <string_view>
#include <si_units/impl/details/si_unit.h>
#include <si_units/standard/length.h>

namespace std
{

// ============================================================================
// ASCII Formatter for Length Units (char / std::string)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::length_dimension>::dimension_type, si::length_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::length_dimension>, char>
{
    std::formatter<type_t, char> m_value_formatter;
    std::string_view m_fill;
    std::string_view m_align;
    std::string_view m_sign;
    std::string_view m_zero;
    int m_width = 0;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = m_value_formatter.parse(ctx);
        return it;
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::length_dimension>& unit, FormatContext& ctx) const
    {
        // Format the numeric value first
        auto out = m_value_formatter.format(unit.value(), ctx);
        
        // Append space and unit symbol with prefix
        auto prefix = get_ascii_prefix<ratio_t>();
        return std::format_to(out, " {}m", prefix);
    }

private:
    template<typename ratio_t>
    static constexpr std::string_view get_ascii_prefix()
    {
        if constexpr (std::is_same_v<ratio_t, std::atto>)
            return "a";
        if constexpr (std::is_same_v<ratio_t, std::femto>)
            return "f";
        if constexpr (std::is_same_v<ratio_t, std::pico>)
            return "p";
        if constexpr (std::is_same_v<ratio_t, std::nano>)
            return "n";
        if constexpr (std::is_same_v<ratio_t, std::micro>)
            return "u";
        if constexpr (std::is_same_v<ratio_t, std::milli>)
            return "m";
        if constexpr (std::is_same_v<ratio_t, std::centi>)
            return "c";
        if constexpr (std::is_same_v<ratio_t, std::deci>)
            return "d";
        if constexpr (std::is_same_v<ratio_t, std::deca>)
            return "da";
        if constexpr (std::is_same_v<ratio_t, std::hecto>)
            return "h";
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 1>>)
            return "";
        if constexpr (std::is_same_v<ratio_t, std::kilo>)
            return "k";
        if constexpr (std::is_same_v<ratio_t, std::mega>)
            return "M";
        if constexpr (std::is_same_v<ratio_t, std::giga>)
            return "G";
        if constexpr (std::is_same_v<ratio_t, std::tera>)
            return "T";
        if constexpr (std::is_same_v<ratio_t, std::peta>)
            return "P";
        if constexpr (std::is_same_v<ratio_t, std::exa>)
            return "E";
        return "";
    }
};

// ============================================================================
// Unicode Formatter for Length Units (char8_t / std::u8string)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::length_dimension>::dimension_type, si::length_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::length_dimension>, char8_t>
{
    std::formatter<type_t, char8_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = m_value_formatter.parse(ctx);
        return it;
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::length_dimension>& unit, FormatContext& ctx) const
    {
        // Format the numeric value first
        auto out = m_value_formatter.format(unit.value(), ctx);
        
        // Append space and unit symbol with prefix (using Unicode for micro)
        auto prefix = get_unicode_prefix<ratio_t>();
        return std::format_to(out, u8" {}m", prefix);
    }

private:
    template<typename ratio_t>
    static constexpr std::u8string_view get_unicode_prefix()
    {
        if constexpr (std::is_same_v<ratio_t, std::atto>)
            return u8"a";
        if constexpr (std::is_same_v<ratio_t, std::femto>)
            return u8"f";
        if constexpr (std::is_same_v<ratio_t, std::pico>)
            return u8"p";
        if constexpr (std::is_same_v<ratio_t, std::nano>)
            return u8"n";
        if constexpr (std::is_same_v<ratio_t, std::micro>)
            return u8"μ";
        if constexpr (std::is_same_v<ratio_t, std::milli>)
            return u8"m";
        if constexpr (std::is_same_v<ratio_t, std::centi>)
            return u8"c";
        if constexpr (std::is_same_v<ratio_t, std::deci>)
            return u8"d";
        if constexpr (std::is_same_v<ratio_t, std::deca>)
            return u8"da";
        if constexpr (std::is_same_v<ratio_t, std::hecto>)
            return u8"h";
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 1>>)
            return u8"";
        if constexpr (std::is_same_v<ratio_t, std::kilo>)
            return u8"k";
        if constexpr (std::is_same_v<ratio_t, std::mega>)
            return u8"M";
        if constexpr (std::is_same_v<ratio_t, std::giga>)
            return u8"G";
        if constexpr (std::is_same_v<ratio_t, std::tera>)
            return u8"T";
        if constexpr (std::is_same_v<ratio_t, std::peta>)
            return u8"P";
        if constexpr (std::is_same_v<ratio_t, std::exa>)
            return u8"E";
        return u8"";
    }
};

// ============================================================================
// Wide Character Formatter for Length Units (wchar_t / std::wstring)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::length_dimension>::dimension_type, si::length_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::length_dimension>, wchar_t>
{
    std::formatter<type_t, wchar_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = m_value_formatter.parse(ctx);
        return it;
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::length_dimension>& unit, FormatContext& ctx) const
    {
        // Format the numeric value first
        auto out = m_value_formatter.format(unit.value(), ctx);
        
        // Append space and unit symbol with prefix (using Unicode for micro)
        auto prefix = get_wide_prefix<ratio_t>();
        return std::format_to(out, L" {}m", prefix);
    }

private:
    template<typename ratio_t>
    static constexpr std::wstring_view get_wide_prefix()
    {
        if constexpr (std::is_same_v<ratio_t, std::atto>)
            return L"a";
        if constexpr (std::is_same_v<ratio_t, std::femto>)
            return L"f";
        if constexpr (std::is_same_v<ratio_t, std::pico>)
            return L"p";
        if constexpr (std::is_same_v<ratio_t, std::nano>)
            return L"n";
        if constexpr (std::is_same_v<ratio_t, std::micro>)
            return L"μ";
        if constexpr (std::is_same_v<ratio_t, std::milli>)
            return L"m";
        if constexpr (std::is_same_v<ratio_t, std::centi>)
            return L"c";
        if constexpr (std::is_same_v<ratio_t, std::deci>)
            return L"d";
        if constexpr (std::is_same_v<ratio_t, std::deca>)
            return L"da";
        if constexpr (std::is_same_v<ratio_t, std::hecto>)
            return L"h";
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 1>>)
            return L"";
        if constexpr (std::is_same_v<ratio_t, std::kilo>)
            return L"k";
        if constexpr (std::is_same_v<ratio_t, std::mega>)
            return L"M";
        if constexpr (std::is_same_v<ratio_t, std::giga>)
            return L"G";
        if constexpr (std::is_same_v<ratio_t, std::tera>)
            return L"T";
        if constexpr (std::is_same_v<ratio_t, std::peta>)
            return L"P";
        if constexpr (std::is_same_v<ratio_t, std::exa>)
            return L"E";
        return L"";
    }
};

} // namespace std
