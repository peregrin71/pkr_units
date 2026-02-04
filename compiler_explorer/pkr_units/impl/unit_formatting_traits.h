#pragma once

#include <array>

namespace PKR_UNITS_NAMESPACE::impl
{

// ============================================================================
// Character type dispatch traits for constexpr string selection
// ============================================================================
// Provides a unified interface for character-type-specific strings
// Used to eliminate repeated if-constexpr chains across the codebase

template <typename CharT>
struct char_traits_dispatch;

// Specialization for char
template <>
struct char_traits_dispatch<char>
{
    static constexpr std::string_view plus_minus()
    {
        return " +/- ";
    }

    static constexpr std::string_view superscript_minus()
    {
        return "⁻";
    }

    static constexpr std::string_view superscript_caret()
    {
        return "^";
    }

    static constexpr std::string_view separator()
    {
        return "·";
    }
};

// Specialization for char8_t
template <>
struct char_traits_dispatch<char8_t>
{
    static constexpr std::u8string_view plus_minus()
    {
        return u8" \u00B1 ";
    }

    static constexpr std::u8string_view superscript_minus()
    {
        return u8"⁻";
    }

    static constexpr std::u8string_view superscript_caret()
    {
        return u8"^";
    }

    static constexpr std::u8string_view separator()
    {
        return u8"·";
    }
};

// Specialization for wchar_t
template <>
struct char_traits_dispatch<wchar_t>
{
    static constexpr std::wstring_view plus_minus()
    {
        return L" \u00B1 ";
    }

    static constexpr std::wstring_view superscript_minus()
    {
        return L"⁻";
    }

    static constexpr std::wstring_view superscript_caret()
    {
        return L"^";
    }

    static constexpr std::wstring_view separator()
    {
        return L"·";
    }
};

// ============================================================================
// Superscript digit lookup for exponent formatting
// ============================================================================
// Provides constexpr lookup tables for converting digits to superscript characters

template <typename CharT>
constexpr std::basic_string_view<CharT> superscript_digit_lookup(int digit);

template <>
constexpr std::basic_string_view<char> superscript_digit_lookup<char>(int digit)
{
    switch (digit)
    {
        case 0:
            return "⁰";
        case 1:
            return "¹";
        case 2:
            return "²";
        case 3:
            return "³";
        case 4:
            return "⁴";
        case 5:
            return "⁵";
        case 6:
            return "⁶";
        case 7:
            return "⁷";
        case 8:
            return "⁸";
        case 9:
            return "⁹";
        default:
            return "";
    }
}

template <>
constexpr std::basic_string_view<char8_t> superscript_digit_lookup<char8_t>(int digit)
{
    switch (digit)
    {
        case 0:
            return u8"⁰";
        case 1:
            return u8"¹";
        case 2:
            return u8"²";
        case 3:
            return u8"³";
        case 4:
            return u8"⁴";
        case 5:
            return u8"⁵";
        case 6:
            return u8"⁶";
        case 7:
            return u8"⁷";
        case 8:
            return u8"⁸";
        case 9:
            return u8"⁹";
        default:
            return u8"";
    }
}

template <>
constexpr std::basic_string_view<wchar_t> superscript_digit_lookup<wchar_t>(int digit)
{
    switch (digit)
    {
        case 0:
            return L"⁰";
        case 1:
            return L"¹";
        case 2:
            return L"²";
        case 3:
            return L"³";
        case 4:
            return L"⁴";
        case 5:
            return L"⁵";
        case 6:
            return L"⁶";
        case 7:
            return L"⁷";
        case 8:
            return L"⁸";
        case 9:
            return L"⁹";
        default:
            return L"";
    }
}

} // namespace PKR_UNITS_NAMESPACE::impl
