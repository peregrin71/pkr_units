#pragma once

/**
 * @file astronomical_units.h
 * @brief Master header for astronomical units
 *
 * Include this file to get access to astronomical units (angstrom, au, light_year, etc.)
 * commonly used in astronomy and physics.
 *
 * Usage:
 *   #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/astronomical_units.h"
 *
 *   // Use astronomical units
 *   auto distance = pkr::units::au_t(1.0);  // astronomical unit
 *   auto wavelength = pkr::units::angstrom_t(500.0);
 */

// ============================================================================
// Core Framework (needed for astronomical units)
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

// ============================================================================
// Astronomical Units
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/astronomical/angle.h"  // HMS/DMS angle units + formatting types
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/astronomical/length.h" // angstrom, au, light_year, parsec, etc.

// ============================================================================
// Unit Operators and Casting
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/unit_cast.h"
// #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/multi_unit_cast.h"

// ============================================================================
// Unit Literals
// ============================================================================
// Use <pkr_units/astronomical_units_literals.h> for user-defined literals (none yet).
