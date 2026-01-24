#pragma once

// ============================================================================
// Master header that includes unit operators and all unit definitions
// ============================================================================
#include "impl/unit_impl.h"

// ============================================================================
// Canonical SI Base Units (7 fundamental units)
// ============================================================================
#include "base/length.h"        // meter (m) - length
#include "base/mass.h"          // kilogram (kg) - mass
#include "base/time.h"          // second (s) - time
#include "base/current.h"       // ampere (A) - electric current
#include "base/temperature.h"   // kelvin (K) - thermodynamic temperature
#include "base/amount.h"        // mole (mol) - amount of substance
#include "base/intensity.h"     // candela (cd) - luminous intensity

// ============================================================================
// Derived SI Units (common compound units)
// ============================================================================
// NOTE: Derived units are temporarily disabled due to incomplete definitions
#include "derived/velocity.h"
#include "derived/acceleration.h"
#include "derived/mechanical.h"
#include "derived/density.h"
#include "derived/concentration.h"
#include "derived/electrical.h"
#include "derived/magnetic_flux.h"

// ============================================================================
// Unit Casting and Conversion
// ============================================================================
// #include "cast/unit_cast.h"

















