#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Dimension struct for dimensional analysis (C++20 as NTTP)
// ============================================================================
//
// 8-Dimensional SI System:
// - Standard 7 SI base units (length, mass, time, current, temperature, amount, intensity)
// - Extended with plane angle (radians) as 8th dimension for type-safe rotational mechanics
//
// See design.md § 1.4 for rationale on adding angle to the standard SI system.
struct dimension_t
{
    int length = 0;      // meter (m)
    int mass = 0;        // kilogram (kg)
    int time = 0;        // second (s)
    int current = 0;     // ampere (A)
    int temperature = 0; // kelvin (K)
    int amount = 0;      // mole (mol)
    int intensity = 0;   // candela (cd)
    int angle = 0;       // radian (rad) - plane angle [NON-STANDARD SI EXTENSION]

    constexpr bool operator==(const dimension_t&) const = default;
};

// Dimensionless (scalar) dimension - default constructed with all zeros
inline constexpr dimension_t scalar_dimension{0, 0, 0, 0, 0, 0, 0, 0};

// ============================================================================
// Dimension symbol building for formatting
// ============================================================================

// Base unit symbols in canonical dimension order: mass, length, time, current, temperature, amount, intensity, angle
template <typename CharT>
inline constexpr std::basic_string_view<CharT> base_unit_symbols[] = {
    std::basic_string_view<CharT>{}, // mass (kg)
    std::basic_string_view<CharT>{}, // length (m)
    std::basic_string_view<CharT>{}, // time (s)
    std::basic_string_view<CharT>{}, // current (A)
    std::basic_string_view<CharT>{}, // temperature (K)
    std::basic_string_view<CharT>{}, // amount (mol)
    std::basic_string_view<CharT>{}, // intensity (cd)
    std::basic_string_view<CharT>{}  // angle (rad)
};

// Specialization for char
template <>
inline constexpr std::basic_string_view<char> base_unit_symbols<char>[] = {"kg", "m", "s", "A", "K", "mol", "cd", "rad"};

// Specialization for wchar_t
template <>
inline constexpr std::basic_string_view<wchar_t> base_unit_symbols<wchar_t>[] = {L"kg", L"m", L"s", L"A", L"K", L"mol", L"cd", L"rad"};

// Specialization for char8_t
template <>
inline constexpr std::basic_string_view<char8_t> base_unit_symbols<char8_t>[] = {u8"kg", u8"m", u8"s", u8"A", u8"K", u8"mol", u8"cd", u8"rad"};

// Helper to get superscript exponent string
template <typename CharT>
std::basic_string<CharT> superscript_exponent(int exp)
{
    if (exp == 0) return std::basic_string<CharT>{};
    bool negative = exp < 0;
    int abs_exp = negative ? -exp : exp;
    std::basic_string<CharT> s;
    if (negative) {
        if constexpr (std::is_same_v<CharT, char>) s += "⁻";
        else if constexpr (std::is_same_v<CharT, char8_t>) s += u8"⁻";
        else if constexpr (std::is_same_v<CharT, wchar_t>) s += L"⁻";
        else s += "-";
    } else {
        s += "^";
    }
    std::string digit_str = std::to_string(abs_exp);
    for (char c : digit_str) {
        if constexpr (std::is_same_v<CharT, char>) {
            if (c == '0') s += "⁰";
            else if (c == '1') s += "¹";
            else if (c == '2') s += "²";
            else if (c == '3') s += "³";
            else if (c == '4') s += "⁴";
            else if (c == '5') s += "⁵";
            else if (c == '6') s += "⁶";
            else if (c == '7') s += "⁷";
            else if (c == '8') s += "⁸";
            else if (c == '9') s += "⁹";
        } else if constexpr (std::is_same_v<CharT, char8_t>) {
            if (c == '0') s += u8"⁰";
            else if (c == '1') s += u8"¹";
            else if (c == '2') s += u8"²";
            else if (c == '3') s += u8"³";
            else if (c == '4') s += u8"⁴";
            else if (c == '5') s += u8"⁵";
            else if (c == '6') s += u8"⁶";
            else if (c == '7') s += u8"⁷";
            else if (c == '8') s += u8"⁸";
            else if (c == '9') s += u8"⁹";
        } else if constexpr (std::is_same_v<CharT, wchar_t>) {
            if (c == '0') s += L"⁰";
            else if (c == '1') s += L"¹";
            else if (c == '2') s += L"²";
            else if (c == '3') s += L"³";
            else if (c == '4') s += L"⁴";
            else if (c == '5') s += L"⁵";
            else if (c == '6') s += L"⁶";
            else if (c == '7') s += L"⁷";
            else if (c == '8') s += L"⁸";
            else if (c == '9') s += L"⁹";
        } else {
            s += c;
        }
    }
    return s;
}

// Build dimension symbol string from dimension_t
// Produces canonical form: M·L·T·I·Θ·N·J·A with negative exponents
template <typename CharT>
std::basic_string<CharT> build_dimension_symbol(const dimension_t& dim)
{
    std::basic_string<CharT> result;

    // Canonical dimension order: mass, length, time, current, temperature, amount, intensity, angle
    const int dims[] = {dim.mass, dim.length, dim.time, dim.current, dim.temperature, dim.amount, dim.intensity, dim.angle};
    const auto& symbols = base_unit_symbols<CharT>;

    // Process all dimensions in canonical order
    for (int i = 0; i < 8; ++i)
    {
        if (dims[i] != 0)
        {
            if (!result.empty())
            {
                // Middle dot (·) separator
                if constexpr (std::is_same_v<CharT, char>)
                    result += "·";
                else if constexpr (std::is_same_v<CharT, char8_t>)
                    result += u8"·";
                else if constexpr (std::is_same_v<CharT, wchar_t>)
                    result += L"·";
                else
                    result += "·";
            }
            result += symbols[i];
            if (dims[i] != 1)
            {
                result += superscript_exponent<CharT>(dims[i]);
            }
        }
    }

    if (result.empty())
    {
        return std::basic_string<CharT>{};
    }

    return result;
}

} // namespace PKR_UNITS_NAMESPACE
