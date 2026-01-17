#pragma once

#include <format>
#include <string>
#include <string_view>
#include <si_units/impl/details/si_unit.h>
#include <si_units/standard/amount.h>

namespace std
{

// ============================================================================
// ASCII Formatter for Amount of Substance Units (char / std::string)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::amount_dimension>::dimension_type, si::amount_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::amount_dimension>, char>
{
    std::formatter<type_t, char> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::amount_dimension>& unit, FormatContext& ctx) const
    {
        auto out = m_value_formatter.format(unit.value(), ctx);
        auto prefix = get_ascii_prefix<ratio_t>();
        return std::format_to(out, " {}mol", prefix);
    }

private:
    template<typename ratio_t>
    static constexpr std::string_view get_ascii_prefix()
    {
        if constexpr (std::is_same_v<ratio_t, std::nano>)
            return "n";
        if constexpr (std::is_same_v<ratio_t, std::micro>)
            return "u";
        if constexpr (std::is_same_v<ratio_t, std::milli>)
            return "m";
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 1>>)
            return "";
        if constexpr (std::is_same_v<ratio_t, std::kilo>)
            return "k";
        return "";
    }
};

// ============================================================================
// Unicode Formatter for Amount of Substance Units (char8_t / std::u8string)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::amount_dimension>::dimension_type, si::amount_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::amount_dimension>, char8_t>
{
    std::formatter<type_t, char8_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::amount_dimension>& unit, FormatContext& ctx) const
    {
        auto out = m_value_formatter.format(unit.value(), ctx);
        auto prefix = get_unicode_prefix<ratio_t>();
        return std::format_to(out, u8" {}mol", prefix);
    }

private:
    template<typename ratio_t>
    static constexpr std::u8string_view get_unicode_prefix()
    {
        if constexpr (std::is_same_v<ratio_t, std::nano>)
            return u8"n";
        if constexpr (std::is_same_v<ratio_t, std::micro>)
            return u8"μ";
        if constexpr (std::is_same_v<ratio_t, std::milli>)
            return u8"m";
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 1>>)
            return u8"";
        if constexpr (std::is_same_v<ratio_t, std::kilo>)
            return u8"k";
        return u8"";
    }
};

// ============================================================================
// Wide Character Formatter for Amount of Substance Units (wchar_t / std::wstring)
// ============================================================================

template<typename type_t, typename ratio_t>
requires std::is_same_v<typename si::unit_t<type_t, ratio_t, si::amount_dimension>::dimension_type, si::amount_dimension>
struct formatter<si::unit_t<type_t, ratio_t, si::amount_dimension>, wchar_t>
{
    std::formatter<type_t, wchar_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, si::amount_dimension>& unit, FormatContext& ctx) const
    {
        auto out = m_value_formatter.format(unit.value(), ctx);
        auto prefix = get_wide_prefix<ratio_t>();
        return std::format_to(out, L" {}mol", prefix);
    }

private:
    template<typename ratio_t>
    static constexpr std::wstring_view get_wide_prefix()
    {
        if constexpr (std::is_same_v<ratio_t, std::nano>)
            return L"n";
        if constexpr (std::is_same_v<ratio_t, std::micro>)
            return L"μ";
        if constexpr (std::is_same_v<ratio_t, std::milli>)
            return L"m";
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 1>>)
            return L"";
        if constexpr (std::is_same_v<ratio_t, std::kilo>)
            return L"k";
        return L"";
    }
};

} // namespace std
