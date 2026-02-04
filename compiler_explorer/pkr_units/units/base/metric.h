#pragma once
// ============================================================================
// Master header that includes unit operators and all unit definitions
// ============================================================================
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
// ============================================================================
// Canonical SI Base Units (7 fundamental units)
// ============================================================================
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/length.h"      // meter (m) - length
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/mass.h"        // kilogram (kg) - mass
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/time.h"        // second (s) - time
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/current.h"     // ampere (A) - electric current
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/temperature.h" // kelvin (K) - thermodynamic temperature
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/amount.h"      // mole (mol) - amount of substance
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/intensity.h"   // candela (cd) - luminous intensity
// ============================================================================
// Derived SI Units (common compound units)
// ============================================================================
// NOTE: Derived units are temporarily disabled due to incomplete definitions
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
// ============================================================================
// Unit Casting and Conversion
// ============================================================================
// #include "cast/unit_cast.h"
