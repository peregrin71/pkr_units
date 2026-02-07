# API Reference

## Navigating the API

The **pkr_units** library is organized around SI dimensions. Choose your starting point based on what you're measuring:

### Core Dimensions

- **[Base Units](base-units/)** — Seven SI base units plus angle
  - Length: meters, kilometers, feet, etc.
  - Mass: kilograms, grams, pounds, etc.
  - Time: seconds, hours, milliseconds, etc.
  - Electric Current: amperes and submultiples
  - Temperature: kelvin (absolute), celsius, fahrenheit (affine)
  - Amount of Substance: moles and submultiples
  - Luminous Intensity: candela and submultiples

- **[Derived Units](derived-units/)** — Common combinations of base units
  - Velocity & Acceleration
  - Force & Pressure
  - Energy & Power
  - Density & Concentration
  - Electrical: voltage, current, resistance, capacitance
  - Magnetic: tesla, weber
  - Thermal: specific heat, thermal conductivity
  - And many more

### Special Collections

- **[Physical Constants](constants/)** — Pre-computed fundamental constants with units
  - Atomic constants
  - Physical constants
  - Mathematical constants
  - Astrophysical constants

### Unit Systems

Beyond SI, the library provides:

- **Imperial Units** — `#include <pkr_units/imperial_units.h>`
  - Length: feet, inches, miles, nautical miles
  - Mass: pounds, ounces, stones, tons
  - Force: pound-force, poundal
  - Pressure: psi
  - Velocity: mph, knots

- **CGS Units** — `#include <pkr_units/cgs_units.h>`
  - Gauss, maxwell, oersted (magnetic)
  - Dyne (force), erg (energy), barye (pressure)
  - Poise, stokes (viscosity)
  - Gal (acceleration)

- **Astronomical Units** — `#include <pkr_units/astronomical_units.h>`
  - Light-year, parsec, AU
  - Angstrom, micron
  - Astronomical angle (DMS and HMS)

### Special Unit Types

- **Dimensionless** — `ratio_t`, `percentage_t`, `decibel_t`
- **Measurements** — Units with uncertainty propagation
- **Affine Units** — Temperature (celsius, fahrenheit with offset)
- **Matrices** — 4×4 matrices with unit types and flexible storage

## Quick Lookup

| I want to... | Header | Class |
|---|---|---|
| Measure distance | `si_units.h` | `meter_t`, `kilometer_t`, etc. |
| Measure weight/mass | `si_units.h` | `kilogram_t`, `kilogram_t`, etc. |
| Measure speed | `si_units.h` | `meter_per_second_t` |
| Measure force | `si_units.h` | `newton_t` |
| Measure temperature | `si_units.h` | `kelvin_t`, `celsius_t`, `fahrenheit_t` |
| Use feet/pounds | `imperial_units.h` | `foot_t`, `pound_t` |
| Use CGS units | `cgs_units.h` | `dyne_t`, `erg_t`, `gauss_t` |
| Track uncertainty | `si_units.h` | `measurement_t<meter_t>` |
| Work with constants | `constants.h` | `physical_constants::*` |
| 4×4 matrix math | `si_units.h` | `matrix_4d_units_t<meter_t>` |
| Format output | `format/si.h` | Automatic via `std::format` |

## Complete Symbol Table

See [Unit Symbols Reference](../reference/units-table.md) for all unit type names and their ASCII/Unicode symbols.

## Import Patterns

```cpp
// All SI units (most common)
#include <pkr_units/si_units.h>

// Imperial units
#include <pkr_units/imperial_units.h>

// CGS units
#include <pkr_units/cgs_units.h>

// Formatting support
#include <pkr_units/format/si.h>

// User-defined literals (e.g., 5_km)
#include <pkr_units/literals/si.h>

// String conversion helpers
#include <pkr_units/chrono.h>  // For std::chrono integration

// Physical constants
#include <pkr_units/constants.h>

// Math utilities (Newton-Raphson, Runge-Kutta, stable operations)
#include <pkr_units/math/unit_math.h>
```
