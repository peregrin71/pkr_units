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
 *   auto speed = pkr::units::miles_per_hour_t(60.0);
 */

// ============================================================================
// Core Framework (needed for imperial units)
// ============================================================================

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

// ============================================================================
// Imperial Units
// ============================================================================

#include <pkr_units/units/imperial/length.h>              // foot, inch, yard, mile, etc.
#include <pkr_units/units/imperial/mass.h>                // pound_t, ounce_t, stone_t, etc.
#include <pkr_units/units/imperial/velocity.h>            // miles_per_hour_t, feet_per_second_t, etc.
#include <pkr_units/units/imperial/acceleration.h>        // feet_per_second_squared_t, etc.
#include <pkr_units/units/imperial/mechanical/force.h>    // pound_force_t, etc.
#include <pkr_units/units/imperial/mechanical/pressure.h> // psi_t, etc.
#include <pkr_units/units/imperial/mechanical/power.h>    // horsepower_t, etc.
#include <pkr_units/units/imperial/density.h>             // pound_per_cubic_inch_t, etc.
#include <pkr_units/units/imperial/formatting.h>          // imperial unit formatting

// ============================================================================
// Unit Operators and Casting
// ============================================================================

// Note: Operators are already included via unit.h
#include <pkr_units/impl/cast/unit_cast.h>
// #include <pkr_units/impl/cast/multi_unit_cast.h>

// ============================================================================
// Unit Literals
// ============================================================================

#include <pkr_units/impl/literals/literals.h>
