#pragma once

#include <ratio>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// ============================================================================
// Solid Angle Dimension (9th SI Base Unit - Non-Standard Extension)
// ============================================================================
//
// RATIONALE FOR ADDING SOLID ANGLE:
// ==================================
//
// Following the same design principle as plane angle (dimension 8), solid angle
// is tracked as a distinct dimension (dimension 9) to enable type-safe operations
// involving solid angles in photometry, radiometry, and related fields.
//
// BENEFITS:
// ---------
// 1. TYPE SAFETY IN PHOTOMETRIC CODE
//    Distinguishes between luminous flux [cd·sr] and luminous intensity [cd]:
//    ✗ COMPILE ERROR:  auto result = luminous_flux / luminous_intensity;
//    ✓ Requires explicit steradian dimensions
//
// 2. DIMENSIONAL CONSISTENCY IN RADIOMETRY
//    Validates relationships:
//    - Radiant intensity = radiant flux / solid angle [W / sr]
//    - Radiance = radiant intensity / projected area [W / (m² · sr)]
//    All properly tracked at compile time
//
// 3. COMMON PHOTOMETRY OPERATIONS
//    - Luminous flux [cd · sr] (lumens)
//    - Luminous intensity [cd] (candela from flux / solid angle)
//    - Illuminance [cd · sr / m²] (lux)
//    All properly distinguished via dimensional analysis
//
// 4. RADIOMETRY APPLICATIONS
//    - Radiant flux [W] (power over solid angle)
//    - Radiant intensity [W / sr]
//    - Radiance [W / (m² · sr)]
//    Type-safe calculations throughout
//
// STANDARDS NOTE:
// ----------------
// ISO 80000-3 defines solid angle as a "supplementary SI unit" with dimension [1],
// but treating it as explicit dimensional quantity (like plane angle) provides
// practical benefits for scientific computing without violating SI principles.
//
// RELATIONSHIP TO PLANE ANGLE:
// ----------------------------
// Both plane angle (rad) and solid angle (sr) are dimensionless in SI,
// but treated as distinct dimensions here for type safety:
// - Plane angle (radian) dimension = 8, symbol "rad"
// - Solid angle (steradian) dimension = 9, symbol "sr"
//
// COMMON USE CASES:
// -----------------
// - Photometry: luminous intensity from flux
// - Radiometry: radiant intensity, radiance calculations
// - Astronomy: solid angles of celestial objects
// - Lighting design: beam angles, light distribution
// - Radiation physics: detector solid angles
// - Antenna engineering: radiation patterns, gain

// Solid angle dimension: sr (steradians)
inline constexpr dimension_t solid_angle_dimension{0, 0, 0, 0, 0, 0, 0, 0, 1};

// Solid angle quantity template
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using solid_angle_unit_t = details::unit_t<type_t, ratio_t, solid_angle_dimension>;
} // namespace PKR_UNITS_NAMESPACE
