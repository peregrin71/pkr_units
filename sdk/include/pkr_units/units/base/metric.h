#pragma once
// ============================================================================
// Master header that includes unit operators and all unit definitions
// ============================================================================
#include <pkr_units/impl/unit_t.h>
// ============================================================================
// Canonical SI Base Units (7 fundamental units)
// ============================================================================
#include <pkr_units/units/base/length.h>      // meter (m) - length
#include <pkr_units/units/base/mass.h>        // kilogram (kg) - mass
#include <pkr_units/units/base/time.h>        // second (s) - time
#include <pkr_units/units/base/current.h>     // ampere (A) - electric current
#include <pkr_units/units/base/temperature.h> // kelvin (K) - thermodynamic temperature
#include <pkr_units/units/base/amount.h>      // mole (mol) - amount of substance
#include <pkr_units/units/base/intensity.h>   // candela (cd) - luminous intensity
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
// ============================================================================
// Unit Casting and Conversion
// ============================================================================
// #include "cast/unit_cast.h"
