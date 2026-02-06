#pragma once

#include <pkr_units/impl/namespace_config.h>

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

} // namespace PKR_UNITS_NAMESPACE
