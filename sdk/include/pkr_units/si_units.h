#pragma once

/**
 * @file si_units.h
 * @brief Master header for the pkr_units library
 * 
 * Include this file to get access to the complete SI units system and framework
 * for creating custom units.
 * 
 * Usage:
 *   #include <pkr_units/si_units.h>
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

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

// ============================================================================
// SI Base Units (8 fundamental units)
// ============================================================================

#include <pkr_units/units/base/length.h>      // meter (m)
#include <pkr_units/units/base/mass.h>        // kilogram (kg)
#include <pkr_units/units/base/time.h>        // second (s)
#include <pkr_units/units/base/current.h>     // ampere (A)
#include <pkr_units/units/base/temperature.h> // kelvin (K)
#include <pkr_units/units/base/amount.h>      // mole (mol)
#include <pkr_units/units/base/intensity.h>   // candela (cd)
#include <pkr_units/units/base/angle.h>       // radian (rad)

// ============================================================================
// Derived SI Units (common compound units)
// ============================================================================

#include <pkr_units/units/derived/velocity.h>
#include <pkr_units/units/derived/acceleration.h>
#include <pkr_units/units/derived/mechanical/force.h>
#include <pkr_units/units/derived/mechanical/pressure.h>
#include <pkr_units/units/derived/mechanical/energy.h>
#include <pkr_units/units/derived/mechanical/power.h>
#include <pkr_units/units/derived/density.h>
#include <pkr_units/units/derived/concentration.h>
#include <pkr_units/units/derived/electrical.h>
#include <pkr_units/units/derived/magnetic_flux.h>
#include <pkr_units/units/derived/thermal.h>
#include <pkr_units/units/derived/viscosity.h>
#include <pkr_units/units/dimensionless/scalar.h>

// ============================================================================
// Unit Operators and Casting
// ============================================================================

#include <pkr_units/impl/cast/unit_cast.h>
// #include <pkr_units/impl/cast/multi_unit_cast.h>

// ============================================================================
// Math Functions
// ============================================================================

#include <pkr_units/math/unit/unit_math.h>

// ============================================================================
// Measurements with Uncertainty Propagation
// ============================================================================

#include <pkr_units/measurements/measurement.h>

// ============================================================================
// Unit Literals
// ============================================================================
// Use <pkr_units/si_units_literals.h> for user-defined literals.
