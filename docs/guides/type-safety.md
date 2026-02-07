# Type Safety & Dimensional Analysis

The **pkr_units** library enables compile-time dimensional correctness checking. This document explains how the type system prevents unit mismatches.

## The Problem: Unit Mismatches

Bugs caused by mixing incompatible units are notoriously hard to find:

```cpp
// Classic bug: mixing meters and seconds
double result = distance_in_meters + time_in_seconds;  // NO COMPILER HELP!
// At runtime, this silently produces garbage
```

## The pkr_units Solution

```cpp
#include <pkr_units/si_units.h>
using pkr::units::meter_t, pkr::units::second_t;

meter_t distance = 100.0;
second_t time = 5.0;

// This doesn't compile
auto bad = distance + time;  // ERROR: cannot add meter + second

// This does compile (same dimension)
auto good = distance + 50_m;  // Result: meter_t(150)

// Division is allowed (creates new dimension)
auto velocity = distance / time;  // Result: meter_per_second_t(20)
```

## How It Works

### Strong Typing

Each unit is a distinct type:

```cpp
struct meter_t : public unit_t<double, std::ratio<1, 1>, length_dimension> { /* ... */ };
struct second_t : public unit_t<double, std::ratio<1, 1>, time_dimension> { /* ... */ };
struct kilogram_t : public unit_t<double, std::ratio<1, 1>, mass_dimension> { /* ... */ };
```

The compiler treats `meter_t` and `kilometer_t` differently because they're different types, even though both measure length.

### Dimension Tracking

Each unit carries an 8-dimensional exponent vector:

```cpp
// length_dimension = { L=1, M=0, T=0, I=0, Θ=0, N=0, J=0, α=0 }
// time_dimension = { L=0, M=0, T=1, I=0, Θ=0, N=0, J=0, α=0 }
// velocity_dimension = { L=1, M=0, T=-1, I=0, Θ=0, N=0, J=0, α=0 }
```

### Arithmetic Rules

When you operate on units, dimensions combine according to physics:

```cpp
// Addition/Subtraction: Dimensions must be identical
meter_t a = 5.0;
meter_t b = 3.0;
auto sum = a + b;  // Same dimension (length)
// second_t c = 2.0;
// auto bad = a + c;  // Cannot add length + time

// Multiplication: Dimensions are combined (exponents added)
meter_t distance = 100.0;
meter_t width = 50.0;
auto area = distance * width;  // meter² (length²)

// Division: Dimensions are combined (exponents subtracted)
meter_t distance = 100.0;
second_t time = 5.0;
auto speed = distance / time;  // meter/second (length × time⁻¹)

// Powers: Exponents are scaled
auto squared = distance * distance;  // meter² (length²)
```

## Type Deduction

The compiler automatically deduces the most appropriate result type:

```cpp
// Simple divisions automatically pick the right type
auto speed = 100_m / 5_s;             // Deduced as meter_per_second_t
auto acc = 20_m_per_s / 4_s;          // Deduced as meter_per_second_squared_t
auto force = 10_kg * 5_m_per_s2;      // Deduced as newton_t

// Type deduction works via the derived_unit_type_t specialization:
template <>
struct derived_unit_type_t<double, std::ratio<1, 1>, velocity_dimension> {
    using type = meter_per_second_t;
};
```

## Explicit Conversions

Converting between units of the same dimension is explicit:

```cpp
meter_t metric = 100.0;
foot_t imperial = unit_cast<foot_t>(metric);  // Explicit conversion

// This is intentional—it makes unit conversions visible in code
// (You can't accidentally mix unit systems)
```

## What the Compiler Can't Catch

Dimensional analysis prevents *type* mismatches, but not *value* errors:

```cpp
auto force1 = 10_kg * 5_m_per_s2;  // Type safe: 50 newton
auto force2 = 10_kg * 5_m_per_s2;  // Type safe: 50 newton
auto force3 = force1 + force2;      // Type safe: 100 newton
// ^ All type-safe, but values are your responsibility

// Same-dimension nonsense is still possible:
meter_t apples = 5.0;
meter_t oranges = 3.0;
auto mixed = apples + oranges;  // Compiles legally, but semantically wrong!
```

The compiler ensures you can't mix different kinds of quantities (meters with seconds), but it can't prevent you from adding semantically unrelated quantities of the same kind (apples with oranges when both are measured in meters).

## Common Patterns

### Pattern 1: Function Parameters Declare Intent

```cpp
// Wrong signature (ambiguous):
double calculate_force(double mass, double accel) { /* ... */ }

// Right signature (clear):
newton_t calculate_force(kilogram_t mass, meter_per_second_squared_t accel) {
    return mass * accel;
}

// Caller can't accidentally pass meters instead of kilograms
calculate_force(50_m);  // Won't compile
calculate_force(50_kg);  // Compiles
```

### Pattern 2: Dimension Mismatch Prevention

```cpp
// Function that only makes sense for lengths
std::string format_distance(meter_t dist) { /* ... */ }

// These don't compile:
format_distance(5_s);     // Wrong dimension
format_distance(10_kg);   // Wrong dimension
format_distance(50_ft);   // Right dimension (imperial foot)

// Auto helps type safety:
auto [dx, dy] = get_displacement();  // Types inferred from return type
// Compiler knows dx and dy are both meter_t (or similar length units)
```

### Pattern 3: Physics Equations as Code

```cpp
// Kinetic energy: KE = 0.5 * m * v²
joule_t kinetic_energy(kilogram_t mass, meter_per_second_t velocity) {
    return 0.5 * mass * (velocity * velocity);
}

// Pressure: P = F / A  
pascal_t pressure(newton_t force, square_meter_t area) {
    return force / area;
}

// Density: ρ = m / V
kilogram_per_cubic_meter_t density(kilogram_t mass, cubic_meter_t volume) {
    return mass / volume;
}
```

The code directly mirrors the mathematical equation—no confusion about units!

## Dimension Algebra

For reference, the 9 dimensions are:

```
dimension_t {
    mass:              // M (kilogram base)
    length:            // L (meter base)
    time:              // T (second base)
    current:           // I (ampere base)
    temperature:       // Θ (kelvin base)
    amount:            // N (mole base)
    luminosity:        // J (candela base)
    angle:             // α (radian base)
    solid_angle:       // Ω (steradian base)
};
```

Examples:

| Quantity | Dimension | Example Type |
|----------|-----------|--------------|
| Length | [0,1,0,0,0,0,0,0,0] | `meter_t` |
| Velocity | [0,1,-1,0,0,0,0,0,0] | `meter_per_second_t` |
| Force | [1,1,-2,0,0,0,0,0,0] | `newton_t` |
| Energy | [1,2,-2,0,0,0,0,0,0] | `joule_t` |
| Power | [1,2,-3,0,0,0,0,0,0] | `watt_t` |
| Charge | [0,0,1,1,0,0,0,0,0] | `coulomb_t` |

## Compilation Performance

Strong typing and dimensional checking are free at runtime (zero-cost abstraction), but have compilation-time cost:

- Template instantiation for each unique unit combination
- Dimension checking in operator overloads
- Type deduction resolution

For typical projects, compilation is still fast. For large codebases with extensive unit arithmetic, consider:
- Using `unit_cast` to reduce type explosion in template-heavy code
- Compiling with parallel builds (`-j`)
- Using precompiled header files

## See Also

- [Creating Custom Units](custom-units.md) — Extend the type system
- [Base Units](../api/base-units/) — All available unit types
- [Derived Units](../api/derived-units/) — Pre-defined combinations
