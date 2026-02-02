#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_formatting_traits.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Dimension struct for dimensional analysis (C++20 as NTTP)
// ============================================================================
//
// 9-Dimensional SI System:
// - Standard 7 SI base units (length, mass, time, current, temperature, amount, intensity)
// - Extended with plane angle (radians) as 8th dimension for type-safe rotational mechanics
// - Extended with solid angle (steradians) as 9th dimension for type-safe solid angle measurements
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
    int star_angle = 0;  // steradian (sr) - solid angle [NON-STANDARD SI EXTENSION]

    constexpr bool operator==(const dimension_t&) const = default;
};

// Dimensionless (scalar) dimension - default constructed with all zeros
inline constexpr dimension_t scalar_dimension{0, 0, 0, 0, 0, 0, 0, 0, 0};

// ============================================================================
// Dimension symbol building for formatting
// ============================================================================

// Base unit symbols in canonical dimension order: mass, length, time, current, temperature, amount, intensity, angle, star_angle
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

    // Add sign using dispatch traits
    if (negative)
        s += impl::char_traits_dispatch<CharT>::superscript_minus();
    else
        s += impl::char_traits_dispatch<CharT>::superscript_caret();

    // Convert digits using lookup table (no branching)
    std::string digit_str = std::to_string(abs_exp);
    for (char c : digit_str)
    {
        int digit_idx = c - '0';
        s += impl::superscript_digit_lookup<CharT>(digit_idx);
    }

    return s;
}

// Build dimension symbol string from dimension_t
// Produces canonical form: M·L·T·I·Θ·N·J·A·Ω with negative exponents
template <typename CharT>
std::basic_string<CharT> build_dimension_symbol(const dimension_t& dim)
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
                result += impl::char_traits_dispatch<CharT>::separator();

            result += symbols[i];
            if (dims[i] != 1)
                result += superscript_exponent<CharT>(dims[i]);
        }
    }

    if (result.empty())
        return std::basic_string<CharT>{};

    return result;
}

} // namespace PKR_UNITS_NAMESPACE
