#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// ============================================================================
// Angle Dimension (8th SI Base Unit - Non-Standard Extension)
// ============================================================================
//
// RATIONALE FOR ADDING ANGLE:
// ============================
//
// While the official SI system treats plane angle (radians) as dimensionless,
// this library adds angle as an 8th dimension for improved type safety in
// rotational mechanics and angular calculations.
//
// BENEFITS:
// ---------
// 1. TYPE SAFETY IN ROTATIONAL CODE
//    Prevents mixing angular and linear velocities:
//    ✗ COMPILE ERROR:  auto result = angular_velocity / linear_velocity;
//    ✓ Catches hidden bugs at compile-time
//
// 2. DIMENSIONAL CONSISTENCY CHECKING
//    Validates relationships like: angular_velocity = linear_velocity / radius
//    where linear_velocity [L/T], radius [L], angular_velocity [T⁻¹·Θ]
//
// 3. COMMON ENGINEERING OPERATIONS
//    Moment of inertia [M·L²] × angular_accel [T⁻²·Θ] → torque [M·L²·T⁻²]
//    Angular momentum [M·L²·T⁻¹·Θ] consistent with rotational dynamics
//
// 4. ROTATIONAL KINEMATICS
//    - Angular position [Θ]
//    - Angular velocity [T⁻¹·Θ]
//    - Angular acceleration [T⁻²·Θ]
//    All properly distinguished from their linear counterparts
//
// STANDARDS NOTE:
// ----------------
// ISO 80000-3 defines plane angle as a "supplementary SI unit" with dimension [1],
// but treating it as explicit dimensional quantity provides practical benefits
// for scientific computing without violating SI principles—it's an extension
// for compile-time dimensional analysis, not a redefinition of SI.
//
// COMMON USE CASES:
// -----------------
// - Robotics: servo angles, joint rotations
// - Mechanics: torque calculations, moment of inertia
// - Navigation: heading, pitch, roll
// - Control systems: angle feedback, PID loops
// - Physics simulations: rotational dynamics
// - Aerospace: Euler angles, angular rates

// Angle dimension: rad (radians, plane angle)
inline constexpr dimension_t angle_dimension{.angle = 1};

// Angle quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using angle_unit_t = details::unit_t<type_t, ratio_t, angle_dimension>;
} // namespace PKR_UNITS_NAMESPACE
