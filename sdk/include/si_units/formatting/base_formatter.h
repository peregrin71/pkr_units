#pragma once

#include <format>
#include <string>
#include <string_view>

namespace si::formatting
{

/// Helper template to extract ratio information for unit prefix determination
template<typename ratio_t>
struct ratio_info;

/// Specialization for SI metric prefixes
template<>
struct ratio_info<std::atto>
{
    static constexpr std::string_view ascii_prefix = "a";
    static constexpr std::string_view unicode_prefix = "a";
    static constexpr std::wstring_view wide_prefix = L"a";
};

template<>
struct ratio_info<std::femto>
{
    static constexpr std::string_view ascii_prefix = "f";
    static constexpr std::string_view unicode_prefix = "f";
    static constexpr std::wstring_view wide_prefix = L"f";
};

template<>
struct ratio_info<std::pico>
{
    static constexpr std::string_view ascii_prefix = "p";
    static constexpr std::string_view unicode_prefix = "p";
    static constexpr std::wstring_view wide_prefix = L"p";
};

template<>
struct ratio_info<std::nano>
{
    static constexpr std::string_view ascii_prefix = "n";
    static constexpr std::string_view unicode_prefix = "n";
    static constexpr std::wstring_view wide_prefix = L"n";
};

template<>
struct ratio_info<std::micro>
{
    static constexpr std::string_view ascii_prefix = "u";
    static constexpr std::string_view unicode_prefix = "μ";
    static constexpr std::wstring_view wide_prefix = L"μ";
};

template<>
struct ratio_info<std::milli>
{
    static constexpr std::string_view ascii_prefix = "m";
    static constexpr std::string_view unicode_prefix = "m";
    static constexpr std::wstring_view wide_prefix = L"m";
};

template<>
struct ratio_info<std::centi>
{
    static constexpr std::string_view ascii_prefix = "c";
    static constexpr std::string_view unicode_prefix = "c";
    static constexpr std::wstring_view wide_prefix = L"c";
};

template<>
struct ratio_info<std::deci>
{
    static constexpr std::string_view ascii_prefix = "d";
    static constexpr std::string_view unicode_prefix = "d";
    static constexpr std::wstring_view wide_prefix = L"d";
};

template<>
struct ratio_info<std::deca>
{
    static constexpr std::string_view ascii_prefix = "da";
    static constexpr std::string_view unicode_prefix = "da";
    static constexpr std::wstring_view wide_prefix = L"da";
};

template<>
struct ratio_info<std::hecto>
{
    static constexpr std::string_view ascii_prefix = "h";
    static constexpr std::string_view unicode_prefix = "h";
    static constexpr std::wstring_view wide_prefix = L"h";
};

template<>
struct ratio_info<std::ratio<1, 1>>
{
    static constexpr std::string_view ascii_prefix = "";
    static constexpr std::string_view unicode_prefix = "";
    static constexpr std::wstring_view wide_prefix = L"";
};

template<>
struct ratio_info<std::kilo>
{
    static constexpr std::string_view ascii_prefix = "k";
    static constexpr std::string_view unicode_prefix = "k";
    static constexpr std::wstring_view wide_prefix = L"k";
};

template<>
struct ratio_info<std::mega>
{
    static constexpr std::string_view ascii_prefix = "M";
    static constexpr std::string_view unicode_prefix = "M";
    static constexpr std::wstring_view wide_prefix = L"M";
};

template<>
struct ratio_info<std::giga>
{
    static constexpr std::string_view ascii_prefix = "G";
    static constexpr std::string_view unicode_prefix = "G";
    static constexpr std::wstring_view wide_prefix = L"G";
};

template<>
struct ratio_info<std::tera>
{
    static constexpr std::string_view ascii_prefix = "T";
    static constexpr std::string_view unicode_prefix = "T";
    static constexpr std::wstring_view wide_prefix = L"T";
};

template<>
struct ratio_info<std::peta>
{
    static constexpr std::string_view ascii_prefix = "P";
    static constexpr std::string_view unicode_prefix = "P";
    static constexpr std::wstring_view wide_prefix = L"P";
};

template<>
struct ratio_info<std::exa>
{
    static constexpr std::string_view ascii_prefix = "E";
    static constexpr std::string_view unicode_prefix = "E";
    static constexpr std::wstring_view wide_prefix = L"E";
};

/// Base formatter structure for units
/// Handles formatting of unit values with proper prefixes and unit symbols
template<typename CharT, typename Unit>
struct unit_formatter_base
{
    using char_type = CharT;
    using string_type = std::basic_string<CharT>;
    using string_view_type = std::basic_string_view<CharT>;

    /// Parse format specification (delegated to value formatter)
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx);

    /// Format the unit value
    template<typename FormatContext>
    auto format(const Unit& unit, FormatContext& ctx) const;

    /// Get the unit symbol in the appropriate character type
    static string_view_type get_unit_symbol();

    /// Get the unit prefix in the appropriate character type
    template<typename ratio_t>
    static string_view_type get_prefix();

    /// Get the base unit symbol without prefix
    template<typename ratio_t>
    static string_view_type get_base_unit_symbol();

protected:
    std::basic_formatter<typename Unit::value_type, CharT> m_value_formatter;
};

} // namespace si::formatting
