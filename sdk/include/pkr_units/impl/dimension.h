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

// ============================================================================
// Dimension Constants for Common SI Quantities
// ============================================================================

// Angle dimension: rad (radians, plane angle)
// [NON-STANDARD SI EXTENSION - See design.md § 1.4 for rationale]
// Enables type-safe handling of angular quantities in rotational mechanics
inline constexpr dimension_t angle_dimension{0, 0, 0, 0, 0, 0, 0, 1, 0};

// SI Base Units
inline constexpr dimension_t length_dimension{1, 0, 0, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t mass_dimension{0, 1, 0, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t time_dimension{0, 0, 1, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t current_dimension{0, 0, 0, 1, 0, 0, 0, 0, 0};
inline constexpr dimension_t temperature_dimension{0, 0, 0, 0, 1, 0, 0, 0, 0};
inline constexpr dimension_t amount_dimension{0, 0, 0, 0, 0, 1, 0, 0, 0};
inline constexpr dimension_t intensity_dimension{0, 0, 0, 0, 0, 0, 1, 0, 0};

// amount rate: amount per time (e.g. bits/s, flops/s, nops/s)
inline constexpr dimension_t amount_rate_dimension{0, 0, -1, 0, 0, 1, 0, 0, 0};

// Derived Dimensions
inline constexpr dimension_t area_dimension{2, 0, 0, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t volume_dimension{3, 0, 0, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t acceleration_v{1, 0, -2, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t velocity_dimension{1, 0, -1, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t mass_concentration_v{-3, 1, 0, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t molar_concentration_v{-3, 0, 0, 0, 0, 1, 0, 0, 0};
inline constexpr dimension_t density_dimension{-3, 1, 0, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t dynamic_viscosity_dimension{-1, 1, -1, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t kinematic_viscosity_dimension{2, 0, -1, 0, 0, 0, 0, 0, 0};
inline constexpr dimension_t josephson_dimension{-2, -1, 2, 1, 0, 0, 0, 0, 0};

// Solid Angle dimension: sr (steradians)
// [NON-STANDARD SI EXTENSION]
inline constexpr dimension_t solid_angle_dimension{0, 0, 0, 0, 0, 0, 0, 0, 1};

} // namespace PKR_UNITS_NAMESPACE
