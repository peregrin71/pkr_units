# Getting Started

## Installation

The **pkr_units** library is header-only. Simply include the main header and start using it.

### Copy into Your Project

```bash
# Clone or download the repository
git clone https://github.com/your-org/pkr_units.git

# Copy the header directory
cp -r pkr_units/sdk/include /your/project
```

## First Example

```cpp
#include <pkr_units/si_units.h>
#include <iostream>

int main()
{
    // Create quantities with units
    pkr::units::meter_t distance = 100.0;           // 100 meters
    pkr::units::second_t time = 5.0;                // 5 seconds
    
    // Divide to get velocity (automatic type deduction)
    auto velocity = distance / time;    // Result is meter_per_second_t
    
    // Print with formatting
    std::cout << distance << " / " << time << " = " << velocity << std::endl;
    // Output: 100 m / 5 s = 20 m/s
    
    return 0;
    
    return 0;
}
```

Compile with C++20:
```bash
g++ -std=c++20 example.cpp -I/path/to/pkr_units/sdk/include -o example
```

## Core Concepts

### Strong Types

Each unit is a distinct type. The compiler prevents mixing incompatible units:

```cpp
using pkr::units::meter_t, pkr::units::second_t;

meter_t distance = 100.0;
second_t time = 5.0;

// This compiles (division of different dimensions)
auto speed = distance / time;  // meter_per_second_t

// This doesn't compile (adding incompatible types)
// auto sum = distance + time;    // ERROR: cannot add meter + second
```

### Dimensional Correctness

Operations automatically track dimensions:

```cpp
using namespace pkr::units::literals;

// Correct: meter × meter = square_meter
auto area = 5_m * 3_m;         // square_meter_t(15)

// Correct: velocity squared gives m²/s²
auto speed_squared = velocity * velocity;  // (meter per second)²

// Won't compile: can't add different dimensions
// auto invalid = distance + velocity;  // ERROR
```

### Explicit Conversions

Converting between units is always explicit via `unit_cast`:

```cpp
using pkr::units::meter_t, pkr::units::kilometer_t, pkr::units::unit_cast;
using namespace pkr::units::literals;

meter_t m = 1000.0;
kilometer_t km = unit_cast<kilometer_t>(m);  // 1.0 km

// Also works with literals
auto feet = 5_m;
auto inches = unit_cast<pkr::units::inch_t>(feet);
```

## Common Entry Points

Choose the header that matches your needs:

| Header | Purpose |
|--------|---------|
| `pkr_units/si_units.h` | SI base + derived units (recommended starting point) |
| `pkr_units/imperial_units.h` | Feet, pounds, gallons, etc. |
| `pkr_units/cgs_units.h` | CGS units (gauss, dyne, erg, etc.) |
| `pkr_units/astronomical_units.h` | Light-years, parsecs, AU, etc. |
| `pkr_units/format/si.h` | std::format support for SI units |

## Sample Code Patterns

### Pattern 1: Physics Calculation

```cpp
#include <pkr_units/si_units.h>
#include <cmath>

// Calculate kinetic energy: E = 0.5 * m * v²
int main()
{
    pkr::units::kilogram_t mass = 10.0;
    pkr::units::meter_per_second_t velocity = 4.0;
    
    // Automatic type deduction: kg × (m/s)² = joule
    auto energy = 0.5 * mass * (velocity * velocity);
    
    // energy is joule_t with value 80.0
    return 0;
}
```

### Pattern 2: Unit Conversion

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>

int main()
{
    // Start with meters
    pkr::units::meter_t metric = 100.0;
    
    // Convert to feet
    pkr::units::foot_t imperial = pkr::units::unit_cast<pkr::units::foot_t>(metric);
    
    // Cross-check: convert back
    pkr::units::meter_t roundtrip = pkr::units::unit_cast<pkr::units::meter_t>(imperial);
    
    return 0;
    
    return 0;
}
```

### Pattern 3: Literals for Convenience

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/literals/si.h>

int main()
{
    using namespace pkr::units::literals;
    
    // Use literals for readability
    auto distance = 42.195_km;      // marathon distance
    auto time = 2_h + 2_min + 57_s;  // world record (approximate)
    auto pace = distance / time;     // pace in km/h
    
    return 0;
    
    return 0;
}
```

## Next Steps

1. **Explore the [API Reference](api/)** to see what units are available
2. **Check [Creating Custom Units](guides/custom-units.md)** if you need domain-specific units
3. **Read [Type Safety & Dimensional Analysis](guides/type-safety.md)** for deeper understanding
4. **See the [Units Table](reference/units-table.md)** for symbol reference

For detailed examples, check the `examples/` directory in the repository.
