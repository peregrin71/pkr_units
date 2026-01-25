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
 *   // Define dimension and unit types, then register with named_unit_type_t
 */

// ============================================================================
// Core Framework
// ============================================================================

#include "impl/namespace_config.h"
#include "impl/unit_impl.h"
#include "impl/dimension.h"

// ============================================================================
// SI Base Units (8 fundamental units)
// ============================================================================

#include "units/base/length.h"        // meter (m)
#include "units/base/mass.h"          // kilogram (kg)
#include "units/base/time.h"          // second (s)
#include "units/base/current.h"       // ampere (A)
#include "units/base/temperature.h"   // kelvin (K)
#include "units/base/amount.h"        // mole (mol)
#include "units/base/intensity.h"     // candela (cd)
#include "units/base/angle.h"         // radian (rad)

// ============================================================================
// Derived SI Units (common compound units)
// ============================================================================

#include "units/derived/velocity.h"
#include "units/derived/acceleration.h"
#include "units/derived/mechanical/force.h"
#include "units/derived/mechanical/pressure.h"
#include "units/derived/mechanical/energy.h"
#include "units/derived/mechanical/power.h"
#include "units/derived/density.h"
#include "units/derived/concentration.h"
#include "units/derived/electrical.h"
#include "units/derived/magnetic_flux.h"

// ============================================================================
// Unit Operators and Casting
// ============================================================================

#include "impl/cast/unit_cast.h"
// #include "impl/cast/multi_unit_cast.h"

// ============================================================================
// Unit Literals
// ============================================================================

#include "impl/literals/literals.h"






