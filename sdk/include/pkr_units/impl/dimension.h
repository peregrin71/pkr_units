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

// Base unit symbols in SI order
template <typename CharT>
inline constexpr std::basic_string_view<CharT> base_unit_symbols[] = {
    std::basic_string_view<CharT>{}, // length (m)
    std::basic_string_view<CharT>{}, // mass (kg)
    std::basic_string_view<CharT>{}, // time (s)
    std::basic_string_view<CharT>{}, // current (A)
    std::basic_string_view<CharT>{}, // temperature (K)
    std::basic_string_view<CharT>{}, // amount (mol)
    std::basic_string_view<CharT>{}, // intensity (cd)
    std::basic_string_view<CharT>{}  // angle (rad)
};

// Specialization for char
template <>
inline constexpr std::basic_string_view<char> base_unit_symbols<char>[] = {"m", "kg", "s", "A", "K", "mol", "cd", "rad"};

// Specialization for wchar_t
template <>
inline constexpr std::basic_string_view<wchar_t> base_unit_symbols<wchar_t>[] = {L"m", L"kg", L"s", L"A", L"K", L"mol", L"cd", L"rad"};

// Specialization for char8_t
template <>
inline constexpr std::basic_string_view<char8_t> base_unit_symbols<char8_t>[] = {u8"m", u8"kg", u8"s", u8"A", u8"K", u8"mol", u8"cd", u8"rad"};

// Build dimension symbol string from dimension_t
// Sorts positive dimensions first, then negative dimensions
template <typename CharT>
std::basic_string<CharT> build_dimension_symbol(const dimension_t& dim)
{
    std::basic_string<CharT> result;

    // Array of dimension values and their indices
    const int dims[] = {dim.length, dim.mass, dim.time, dim.current, dim.temperature, dim.amount, dim.intensity, dim.angle};

    // First pass: positive dimensions
    for (int i = 0; i < 8; ++i)
    {
        if (dims[i] > 0)
        {
            if (!result.empty())
                result += static_cast<CharT>('*');
            result += base_unit_symbols<CharT>[i];
            if (dims[i] != 1)
            {
                result += static_cast<CharT>('^');
                result += std::to_string(dims[i]);
            }
        }
    }

    // Second pass: negative dimensions
    bool has_negative = false;
    for (int i = 0; i < 8; ++i)
    {
        if (dims[i] < 0)
        {
            if (!has_negative)
            {
                if (!result.empty())
                    result += static_cast<CharT>('/');
                has_negative = true;
            }
            else
            {
                result += static_cast<CharT>('*');
            }
            result += base_unit_symbols<CharT>[i];
            if (dims[i] != -1)
            {
                result += static_cast<CharT>('^');
                result += std::to_string(-dims[i]);
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
