#pragma once

#include <ratio>
#include <string_view>

namespace si::formatting::helpers
{

// ============================================================================
// ASCII Prefix Conversion
// ============================================================================

template<typename Ratio>
constexpr std::string_view get_ascii_prefix()
{
    if constexpr (std::is_same_v<Ratio, std::atto>)
        return "a";
    if constexpr (std::is_same_v<Ratio, std::femto>)
        return "f";
    if constexpr (std::is_same_v<Ratio, std::pico>)
        return "p";
    if constexpr (std::is_same_v<Ratio, std::nano>)
        return "n";
    if constexpr (std::is_same_v<Ratio, std::micro>)
        return "u";
    if constexpr (std::is_same_v<Ratio, std::milli>)
        return "m";
    if constexpr (std::is_same_v<Ratio, std::centi>)
        return "c";
    if constexpr (std::is_same_v<Ratio, std::deci>)
        return "d";
    if constexpr (std::is_same_v<Ratio, std::ratio<1, 1>>)
        return "";
    if constexpr (std::is_same_v<Ratio, std::deca>)
        return "da";
    if constexpr (std::is_same_v<Ratio, std::hecto>)
        return "h";
    if constexpr (std::is_same_v<Ratio, std::kilo>)
        return "k";
    if constexpr (std::is_same_v<Ratio, std::mega>)
        return "M";
    if constexpr (std::is_same_v<Ratio, std::giga>)
        return "G";
    if constexpr (std::is_same_v<Ratio, std::tera>)
        return "T";
    if constexpr (std::is_same_v<Ratio, std::peta>)
        return "P";
    if constexpr (std::is_same_v<Ratio, std::exa>)
        return "E";
    return "";
}

// ============================================================================
// Unicode Prefix Conversion (UTF-8)
// ============================================================================

template<typename Ratio>
constexpr std::u8string_view get_unicode_prefix()
{
    if constexpr (std::is_same_v<Ratio, std::atto>)
        return u8"a";
    if constexpr (std::is_same_v<Ratio, std::femto>)
        return u8"f";
    if constexpr (std::is_same_v<Ratio, std::pico>)
        return u8"p";
    if constexpr (std::is_same_v<Ratio, std::nano>)
        return u8"n";
    if constexpr (std::is_same_v<Ratio, std::micro>)
        return u8"μ";
    if constexpr (std::is_same_v<Ratio, std::milli>)
        return u8"m";
    if constexpr (std::is_same_v<Ratio, std::centi>)
        return u8"c";
    if constexpr (std::is_same_v<Ratio, std::deci>)
        return u8"d";
    if constexpr (std::is_same_v<Ratio, std::ratio<1, 1>>)
        return u8"";
    if constexpr (std::is_same_v<Ratio, std::deca>)
        return u8"da";
    if constexpr (std::is_same_v<Ratio, std::hecto>)
        return u8"h";
    if constexpr (std::is_same_v<Ratio, std::kilo>)
        return u8"k";
    if constexpr (std::is_same_v<Ratio, std::mega>)
        return u8"M";
    if constexpr (std::is_same_v<Ratio, std::giga>)
        return u8"G";
    if constexpr (std::is_same_v<Ratio, std::tera>)
        return u8"T";
    if constexpr (std::is_same_v<Ratio, std::peta>)
        return u8"P";
    if constexpr (std::is_same_v<Ratio, std::exa>)
        return u8"E";
    return u8"";
}

// ============================================================================
// Wide Character Prefix Conversion
// ============================================================================

template<typename Ratio>
constexpr std::wstring_view get_wide_prefix()
{
    if constexpr (std::is_same_v<Ratio, std::atto>)
        return L"a";
    if constexpr (std::is_same_v<Ratio, std::femto>)
        return L"f";
    if constexpr (std::is_same_v<Ratio, std::pico>)
        return L"p";
    if constexpr (std::is_same_v<Ratio, std::nano>)
        return L"n";
    if constexpr (std::is_same_v<Ratio, std::micro>)
        return L"μ";
    if constexpr (std::is_same_v<Ratio, std::milli>)
        return L"m";
    if constexpr (std::is_same_v<Ratio, std::centi>)
        return L"c";
    if constexpr (std::is_same_v<Ratio, std::deci>)
        return L"d";
    if constexpr (std::is_same_v<Ratio, std::ratio<1, 1>>)
        return L"";
    if constexpr (std::is_same_v<Ratio, std::deca>)
        return L"da";
    if constexpr (std::is_same_v<Ratio, std::hecto>)
        return L"h";
    if constexpr (std::is_same_v<Ratio, std::kilo>)
        return L"k";
    if constexpr (std::is_same_v<Ratio, std::mega>)
        return L"M";
    if constexpr (std::is_same_v<Ratio, std::giga>)
        return L"G";
    if constexpr (std::is_same_v<Ratio, std::tera>)
        return L"T";
    if constexpr (std::is_same_v<Ratio, std::peta>)
        return L"P";
    if constexpr (std::is_same_v<Ratio, std::exa>)
        return L"E";
    return L"";
}

} // namespace si::formatting::helpers
