#pragma once

/**
 * @file si_units.h
 * @brief Master header for the pkr_units library
 * 
 * Include this file to get access to the complete SI units system and framework
 * for creating custom units.
 * 
 * Usage:
 *   #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/si_units.h"
 *   
 *   // Use predefined units
 *   auto distance = pkr::units::meter_t(100.0);
 *   auto speed = pkr::units::meter_per_second_t(10.0);
 *   
 *   // Create custom units (see custom_units_guide.md for details)
 *   // Define dimension and unit types, then register with derived_unit_type_t
 */

// ============================================================================
// Core Framework
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

// ============================================================================
// SI Base Units (9 fundamental units)
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/length.h"      // meter (m)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/mass.h"        // kilogram (kg)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/time.h"        // second (s)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/current.h"     // ampere (A)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/temperature.h" // kelvin (K)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/amount.h"      // mole (mol)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/intensity.h"   // candela (cd)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/angle.h"       // radian (rad)
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/solid_angle.h" // steradian (sr)

// ============================================================================
// Derived SI Units (common compound units)
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/velocity.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/acceleration.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/mechanical/force.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/mechanical/pressure.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/mechanical/energy.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/mechanical/power.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/density.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/concentration.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/electrical.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/magnetic_flux.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/thermal.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/viscosity.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/photometry/luminous_flux.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/photometry/luminous_exitance.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/radiometry/radiant_intensity.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/radiometry/radiance.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/radiometry/irradiance.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/dimensionless/scalar.h"

// ============================================================================
// Unit Operators and Casting
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/unit_cast.h"
// #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/multi_unit_cast.h"

// ============================================================================
// Math Functions
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/math/unit_math.h"

// ============================================================================
// Unit Literals
// ============================================================================
// Use <pkr_units/si_units_literals.h> for user-defined literals.
