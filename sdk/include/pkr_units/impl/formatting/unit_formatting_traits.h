#pragma once

#include <array>
#include <string>

// Format buffer size configuration
#ifndef PKR_UNITS_FORMAT_BUFFER_SIZE
#define PKR_UNITS_FORMAT_BUFFER_SIZE 4096
#endif

namespace PKR_UNITS_NAMESPACE
{
// Forward declare dimension_t for use in function signatures
struct dimension_t;
} // namespace PKR_UNITS_NAMESPACE

namespace PKR_UNITS_NAMESPACE::impl
{

// ============================================================================
// Static format buffer storage - truly shared across all character types
// ============================================================================
// Non-templated base that holds the single unified byte buffer
struct format_buffer_storage
{
    static constexpr std::size_t buffer_size = PKR_UNITS_FORMAT_BUFFER_SIZE;

    static std::array<std::byte, buffer_size>& get_data()
    {
        static std::array<std::byte, buffer_size> s_data{};
        return s_data;
    }
};

// ============================================================================
// Static format buffer for use in formatting operations
// Uses a single unified byte buffer for all character types to minimize memory
// ============================================================================
template <typename CharT>
struct format_buffer
{
    static constexpr std::size_t buffer_size = format_buffer_storage::buffer_size;
    static constexpr std::size_t max_chars = buffer_size / sizeof(CharT);

    std::size_t byte_length = 0; // Track length in bytes for this instance

    constexpr CharT* begin()
    {
        return reinterpret_cast<CharT*>(format_buffer_storage::get_data().data());
    }

    constexpr CharT* end()
    {
        return reinterpret_cast<CharT*>(format_buffer_storage::get_data().data()) + (byte_length / sizeof(CharT));
    }

    constexpr const CharT* begin() const
    {
        return reinterpret_cast<const CharT*>(format_buffer_storage::get_data().data());
    }

    constexpr const CharT* end() const
    {
        return reinterpret_cast<const CharT*>(format_buffer_storage::get_data().data()) + (byte_length / sizeof(CharT));
    }

    constexpr void clear()
    {
        byte_length = 0;
    }

    constexpr void push_back(CharT c)
    {
        if (byte_length + sizeof(CharT) <= buffer_size)
        {
            *reinterpret_cast<CharT*>(format_buffer_storage::get_data().data() + byte_length) = c;
            byte_length += sizeof(CharT);
        }
    }

    constexpr void append(std::basic_string_view<CharT> sv)
    {
        for (CharT c : sv)
            push_back(c);
    }

    constexpr std::basic_string_view<CharT> view() const
    {
        return std::basic_string_view<CharT>(reinterpret_cast<const CharT*>(format_buffer_storage::get_data().data()), byte_length / sizeof(CharT));
    }
};

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
        return "-";
    }

    static constexpr std::string_view superscript_caret()
    {
        return "^";
    }

    static constexpr std::string_view separator()
    {
        return "*";
    }

    static constexpr std::string_view multiply_sign()
    {
        return "x";
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
        return u8"\u207B";
    }

    static constexpr std::u8string_view superscript_caret()
    {
        return u8"";
    }

    static constexpr std::u8string_view separator()
    {
        return u8"\u00B7";
    }

    static constexpr std::u8string_view multiply_sign()
    {
        return u8"\u00D7";
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
        return L"\u207B";
    }

    static constexpr std::wstring_view superscript_caret()
    {
        return L"";
    }

    static constexpr std::wstring_view separator()
    {
        return L"\u00B7";
    }

    static constexpr std::wstring_view multiply_sign()
    {
        return L"\u00D7";
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
            return "0";
        case 1:
            return "1";
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        case 9:
            return "9";
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
            return u8"\u2070";
        case 1:
            return u8"\u00B9";
        case 2:
            return u8"\u00B2";
        case 3:
            return u8"\u00B3";
        case 4:
            return u8"\u2074";
        case 5:
            return u8"\u2075";
        case 6:
            return u8"\u2076";
        case 7:
            return u8"\u2077";
        case 8:
            return u8"\u2078";
        case 9:
            return u8"\u2079";
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
            return L"\u2070";
        case 1:
            return L"\u00B9";
        case 2:
            return L"\u00B2";
        case 3:
            return L"\u00B3";
        case 4:
            return L"\u2074";
        case 5:
            return L"\u2075";
        case 6:
            return L"\u2076";
        case 7:
            return L"\u2077";
        case 8:
            return L"\u2078";
        case 9:
            return L"\u2079";
        default:
            return L"";
    }
}

// ============================================================================
// Base unit symbols for dimension formatting
// ============================================================================
// Canonical dimension order: mass, length, time, current, temperature, amount, intensity, angle, star_angle

template <typename CharT>
inline constexpr std::basic_string_view<CharT> base_unit_symbols[] = {
    std::basic_string_view<CharT>{}, // mass (kg)
    std::basic_string_view<CharT>{}, // length (m)
    std::basic_string_view<CharT>{}, // time (s)
    std::basic_string_view<CharT>{}, // current (A)
    std::basic_string_view<CharT>{}, // temperature (K)
    std::basic_string_view<CharT>{}, // amount (mol)
    std::basic_string_view<CharT>{}, // intensity (cd)
    std::basic_string_view<CharT>{}, // angle (rad)
    std::basic_string_view<CharT>{}  // star_angle (sr)
};

// Specialization for char
template <>
inline constexpr std::basic_string_view<char> base_unit_symbols<char>[] = {"kg", "m", "s", "A", "K", "mol", "cd", "rad", "sr"};

// Specialization for wchar_t
template <>
inline constexpr std::basic_string_view<wchar_t> base_unit_symbols<wchar_t>[] = {L"kg", L"m", L"s", L"A", L"K", L"mol", L"cd", L"rad", L"sr"};

// Specialization for char8_t
template <>
inline constexpr std::basic_string_view<char8_t> base_unit_symbols<char8_t>[] = {u8"kg", u8"m", u8"s", u8"A", u8"K", u8"mol", u8"cd", u8"rad", u8"sr"};

// Helper to get superscript exponent string using lookup tables
template <typename CharT>
std::basic_string<CharT> superscript_exponent(int exp)
{
    if (exp == 0)
        return std::basic_string<CharT>{};

    bool negative = exp < 0;
    int abs_exp = negative ? -exp : exp;
    std::basic_string<CharT> s;

    // Always add caret first (empty for wchar_t)
    s += char_traits_dispatch<CharT>::superscript_caret();

    // Add minus sign for negative exponents
    if (negative)
        s += char_traits_dispatch<CharT>::superscript_minus();

    // Convert digits using lookup table (no branching)
    std::string digit_str = std::to_string(abs_exp);
    for (char c : digit_str)
    {
        int digit_idx = c - '0';
        s += superscript_digit_lookup<CharT>(digit_idx);
    }

    return s;
}

// ============================================================================
// Dimension symbol building
// ============================================================================
// Build dimension symbol string from dimension_t
// Produces canonical form: M·L·T·I·Θ·N·J·A·Ω with negative exponents

template <typename CharT>
inline std::basic_string<CharT> build_dimension_symbol(const PKR_UNITS_NAMESPACE::dimension_t& dim)
{
    std::basic_string<CharT> result;

    // Canonical dimension order: mass, length, time, current, temperature, amount, intensity, angle, star_angle
    const int dims[] = {dim.mass, dim.length, dim.time, dim.current, dim.temperature, dim.amount, dim.intensity, dim.angle, dim.star_angle};
    const auto& symbols = base_unit_symbols<CharT>;

    // Process all dimensions in canonical order
    for (int i = 0; i < 9; ++i)
    {
        if (dims[i] != 0)
        {
            if (!result.empty())
                result += char_traits_dispatch<CharT>::separator();

            result += symbols[i];
            if (dims[i] != 1)
                result += superscript_exponent<CharT>(dims[i]);
        }
    }

    if (result.empty())
        return std::basic_string<CharT>{};

    return result;
}

} // namespace PKR_UNITS_NAMESPACE::impl
