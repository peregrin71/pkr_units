# Derived Units

Derived units are combinations of base units. The library provides many pre-defined derived units for convenience.

## Common Derived Units

### Mechanics

| Quantity | Type | Formula | Header |
|----------|------|---------|--------|
| **Velocity** | `meter_per_second_t` | m/s | `si_units.h` |
| **Acceleration** | `meter_per_second_squared_t` | m/s² | `si_units.h` |
| **Force** | `newton_t` | kg·m/s² | `si_units.h` |
| **Pressure** | `pascal_t` | N/m² | `si_units.h` |
| **Energy** | `joule_t` | N·m | `si_units.h` |
| **Power** | `watt_t` | J/s | `si_units.h` |
| **Density** | `kilogram_per_cubic_meter_t` | kg/m³ | `si_units.h` |

### Electrical

| Quantity | Type | Formula | Header |
|----------|------|---------|--------|
| **Charge** | `coulomb_t` | A·s | `si_units.h` |
| **Voltage** | `volt_t` | J/C | `si_units.h` |
| **Resistance** | `ohm_t` | V/A | `si_units.h` |
| **Capacitance** | `farad_t` | C/V | `si_units.h` |
| **Inductance** | `henry_t` | Wb/A | `si_units.h` |
| **Conductance** | `siemens_t` | 1/Ω | `si_units.h` |

### Magnetic

| Quantity | Type | Formula | Header |
|----------|------|---------|--------|
| **Magnetic Flux** | `weber_t` | V·s | `si_units.h` |
| **Magnetic Flux Density** | `tesla_t` | Wb/m² | `si_units.h` |

### Thermal

| Quantity | Type | Formula | Header |
|----------|------|---------|--------|
| **Specific Heat Capacity** | `specific_heat_capacity_t` | J/(kg·K) | `si_units.h` |
| **Thermal Conductivity** | `thermal_conductivity_t` | W/(m·K) | `si_units.h` |

### Geometric

| Quantity | Type | Formula | Header |
|----------|------|---------|--------|
| **Area** | `square_meter_t` | m² | `si_units.h` |
| **Volume** | `cubic_meter_t` | m³ | `si_units.h` |
| **Solid Angle** | `steradian_t` | sr | `si_units.h` |

### Chemistry & Materials

| Quantity | Type | Formula | Header |
|----------|------|---------|--------|
| **Concentration** | `molar_concentration_t` | mol/L | `si_units.h` |
| **Viscosity** | `pascal_second_t` | Pa·s | `si_units.h` |

## Usage Examples

```cpp
#include <pkr_units/si_units.h>
using pkr::units::meter_t, pkr::units::second_t, pkr::units::kilogram_t, pkr::units::newton_t;

// Velocity from distance and time
meter_t distance = 100.0;
second_t time = 5.0;
auto velocity = distance / time;  // meter_per_second_t(20.0)

// Force from mass and acceleration
kilogram_t mass = 10.0;
meter_per_second_squared_t acceleration = 5.0;
auto force = mass * acceleration;  // newton_t(50.0)

// Energy from force and distance
newton_t applied_force = 100.0;
meter_t displacement = 50.0;
auto work = applied_force * displacement;  // joule_t(5000.0)

// Pressure from force and area
newton_t load = 1000.0;
square_meter_t contact_area = 0.01;
auto pressure = load / contact_area;  // pascal_t(100000.0)
```

## Type Deduction

When you multiply or divide units, the result type is automatically deduced:

```cpp
// Compiler knows the result type
auto v = 100_m / 5_s;  // Type: meter_per_second_t
auto f = 10_kg * 3_m_per_s2;  // Type: newton_t
auto p = 1000_N / 0.01_m2;  // Type: pascal_t

// Non-standard combinations may need explicit cast
auto unusual = 1_m * 1_A;  // Type deduced, but uncommon
auto result = unit_cast<some_unit_t>(unusual);  // Explicit conversion
```

## Variants and Prefix Support

Derived units inherit prefix support from their component base units:

```cpp
// All work automatically
kilometer_per_second_t speed1;     // km/s
millimeter_per_second_t speed2;    // mm/s
centimeter_per_second_t speed3;    // cm/s

kilonewton_t force1;               // kN
micronewton_t force2;              // µN

kilopascal_t pressure1;            // kPa
megapascal_t pressure2;            // MPa
```

## Building Your Own Derived Units

If a derived unit isn't pre-defined, you can:

1. **Compose on the fly**: `distance / time` gives velocity
2. **Create a custom typedef**: See [Creating Custom Units](../guides/custom-units.md)
3. **Use generic `unit_t`**: Work with the base unit_t type for one-off calculations

## Unit Systems

Additional unit systems with their own derived units:

- **[Imperial Derived Units](../../imperial_units.h)** — hp (horsepower), psi (pressure), etc.
- **[CGS Derived Units](../../cgs_units.h)** — dyne (force), erg (energy), gauss (magnetic field), etc.

## References

- [Base Units](../base-units/) — The seven SI fundamentals
- [Creating Custom Units](../guides/custom-units.md) — Define your own derived units
- [Type Safety](../guides/type-safety.md) — How dimensional analysis prevents bugs
