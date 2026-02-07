# Physical Constants

The library provides carefully computed physical constants with proper unit types.

## Using Constants

```cpp
#include <pkr_units/constants.h>
using pkr::units::kelvin_t;
using namespace pkr::units::physical_constants;

// Constants are available both as typed values and raw numbers
auto c_light = speed_of_light;          // meter_per_second_t
double c_raw = speed_of_light_raw;      // Raw value in SI units

// Use directly in calculations
auto energy = avogadro_number * boltzmann_constant * kelvin_t(273.15);
```

## Available Constants

(See header comments in `sdk/include/pkr_units/constants.h` for complete list)

Common constants include:
- Speed of light: `speed_of_light`
- Gravitational constant: `gravitational_constant`
- Planck constant: `planck_constant`
- Boltzmann constant: `boltzmann_constant`
- Avogadro number: `avogadro_number`
- Elementary charge: `elementary_charge`
- And many others...

## Physical Constant Categories

- **Atomic constants** — Electron mass, atomic radius, etc.
- **Electromagnetic constants** — Permeability, permittivity, etc.
- **Thermodynamic constants** — Boltzmann, gas constant, etc.
- **Astrophysical constants** — Solar mass, light-year, parsec, etc.

## Precision Notes

Constants are computed to double precision (~15 significant digits). Refer to NIST or CODATA for the authoritative values and uncertainty estimates.

## Related

- [Getting Started](../getting-started.md) — Using constants in examples
- [API Reference](../overview.md) — Complete constant listing
