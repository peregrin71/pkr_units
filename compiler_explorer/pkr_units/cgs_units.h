#pragma once

/**
 * @file cgs_units.h
 * @brief Master header for CGS (centimeter-gram-second) units
 *
 * Include this file to get access to the CGS unit system. This includes
 * common mechanical, magnetic, electrical, and viscosity units.
 *
 * Usage:
 *   #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/cgs_units.h"
 *
 *   auto field = pkr::units::gauss_t{2500.0};
 */

// ============================================================================
// Core Framework
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

// ============================================================================
// CGS Units
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/acceleration.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/viscosity.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/electrical/charge.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/mechanical/force.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/mechanical/energy.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/mechanical/pressure.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/magnetic/gauss.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/magnetic/oersted.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/cgs/magnetic/maxwell.h"

// ============================================================================
// Unit Operators and Casting
// ============================================================================

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/unit_cast.h"
// #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/multi_unit_cast.h"

// ============================================================================
// Unit Literals
// ============================================================================
// Use <pkr_units/cgs_units_literals.h> for user-defined literals.
