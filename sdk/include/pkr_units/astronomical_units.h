#pragma once

/**
 * @file astronomical_units.h
 * @brief Master header for astronomical units
 *
 * Include this file to get access to astronomical units (angstrom, au, light_year, etc.)
 * commonly used in astronomy and physics.
 *
 * Usage:
 *   #include <pkr_units/astronomical_units.h>
 *
 *   // Use astronomical units
 *   auto distance = pkr::units::au_t(1.0);  // astronomical unit
 *   auto wavelength = pkr::units::angstrom_t(500.0);
 */

// ============================================================================
// Core Framework (needed for astronomical units)
// ============================================================================

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

// ============================================================================
// Astronomical Units
// ============================================================================

#include <pkr_units/units/astronomical/angle.h>  // HMS/DMS angle units + formatting types
#include <pkr_units/units/astronomical/length.h> // angstrom, au, light_year, parsec, etc.

// ============================================================================
// Unit Operators and Casting
// ============================================================================

#include <pkr_units/impl/cast/unit_cast.h>
// #include <pkr_units/impl/cast/multi_unit_cast.h>

// ============================================================================
// Unit Literals (if any)
// ============================================================================

// Note: Astronomical literals would be included here if they exist
// #include <pkr_units/impl/literals/astronomical_literals.h>
