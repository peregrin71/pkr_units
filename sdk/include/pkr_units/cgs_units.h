#pragma once

/**
 * @file cgs_units.h
 * @brief Master header for CGS (centimeter-gram-second) units
 *
 * Include this file to get access to the CGS unit system. This includes
 * common mechanical, magnetic, electrical, and viscosity units.
 *
 * Usage:
 *   #include <pkr_units/cgs_units.h>
 *
 *   auto field = pkr::units::gauss_t{2500.0};
 */

// ============================================================================
// Core Framework
// ============================================================================

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

// ============================================================================
// CGS Units
// ============================================================================

#include <pkr_units/units/cgs/acceleration.h>
#include <pkr_units/units/cgs/viscosity.h>
#include <pkr_units/units/cgs/electrical/charge.h>
#include <pkr_units/units/cgs/mechanical/force.h>
#include <pkr_units/units/cgs/mechanical/energy.h>
#include <pkr_units/units/cgs/mechanical/pressure.h>
#include <pkr_units/units/cgs/magnetic/gauss.h>
#include <pkr_units/units/cgs/magnetic/oersted.h>
#include <pkr_units/units/cgs/magnetic/maxwell.h>

// ============================================================================
// Unit Operators and Casting
// ============================================================================

#include <pkr_units/impl/cast/unit_cast.h>
// #include <pkr_units/impl/cast/multi_unit_cast.h>

// ============================================================================
// Unit Literals
// ============================================================================
// Use <pkr_units/cgs_units_literals.h> for user-defined literals.
