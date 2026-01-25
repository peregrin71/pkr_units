#pragma once

/**
 * @file imperial_units.h
 * @brief Master header for imperial and non-SI units
 *
 * Include this file to get access to imperial units (feet, pounds, miles, etc.)
 * and other non-SI units commonly used in various contexts.
 *
 * Usage:
 *   #include <pkr_units/imperial_units.h>
 *
 *   // Use imperial units
 *   auto distance = pkr::units::foot_t(100.0);
 *   auto weight = pkr::units::pound_t(150.0);
 *   auto speed = pkr::units::mile_per_hour_t(60.0);
 */

// ============================================================================
// Core Framework (needed for imperial units)
// ============================================================================

#include "impl/namespace_config.h"
#include "impl/unit_impl.h"
#include "impl/dimension.h"

// ============================================================================
// Imperial Units
// ============================================================================

#include "units/imperial/length.h"        // foot, inch, yard, mile, etc.
#include "units/imperial/mass.h"          // pound, ounce, stone, etc.
#include "units/imperial/velocity.h"      // mile per hour, foot per second, etc.
#include "units/imperial/acceleration.h"  // foot per second squared, etc.
#include "units/imperial/force.h"         // pound-force, etc.
#include "units/imperial/formatting.h"    // imperial unit formatting

// ============================================================================
// Unit Operators and Casting
// ============================================================================

// Note: Operators are already included via unit.h
#include "impl/cast/unit_cast.h"
// #include "impl/cast/multi_unit_cast.h"

// ============================================================================
// Unit Literals
// ============================================================================

#include "impl/literals/literals.h"
