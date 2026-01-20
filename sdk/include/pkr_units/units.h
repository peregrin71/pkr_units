#pragma once

/**
 * @file units.h
 * @brief Master header for the pkr_units library
 * 
 * Include this file to get access to the complete SI units system and framework
 * for creating custom units.
 * 
 * Usage:
 *   #include <pkr_units/units.h>
 *   
 *   // Use predefined units
 *   auto distance = pkr::units::meter_t(100.0);
 *   auto speed = pkr::units::meter_per_second_t(10.0);
 *   
 *   // Create custom units (see custom_units_guide.md for details)
 *   // Define dimension and unit types, then register with most_derived_unit_type
 */

// ============================================================================
// Core Framework
// ============================================================================

#include "impl/namespace_config.h"
#include "impl/common/unit.h"
#include "impl/common/dimension.h"

// ============================================================================
// SI Base Units (8 fundamental units)
// ============================================================================

#include "standard/length.h"        // meter (m)
#include "standard/mass.h"          // kilogram (kg)
#include "standard/time.h"          // second (s)
#include "standard/current.h"       // ampere (A)
#include "standard/temperature.h"   // kelvin (K)
#include "standard/amount.h"        // mole (mol)
#include "standard/intensity.h"     // candela (cd)
#include "standard/angle.h"         // radian (rad)

// ============================================================================
// Derived SI Units (common compound units)
// ============================================================================

#include "derived/velocity.h"
#include "derived/acceleration.h"
#include "derived/mechanical.h"
#include "derived/density.h"
#include "derived/concentration.h"
#include "derived/electrical.h"
#include "derived/magnetic_flux.h"

// ============================================================================
// Unit Operators and Casting
// ============================================================================

// Note: Operators are already included via unit.h
// For additional casting utilities, see: cast/unit_cast.h
