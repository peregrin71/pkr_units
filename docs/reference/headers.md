# Header Quick Reference

Guide to choosing and importing the right header files.

## Main Entry Points

These are the headers you'll typically include:

| Header | Purpose | When to Use |
|--------|---------|------------|
| `pkr_units/si_units.h` | SI base + common derived | **Default choice** for most users |
| `pkr_units/imperial_units.h` | Feet, pounds, gallons, etc. | Non-metric systems |
| `pkr_units/cgs_units.h` | Gauss, dyne, erg, etc. | Legacy or specific fields |
| `pkr_units/astronomical_units.h` | Light-year, parsec, AU | Astronomy/space systems |

## Formatting & Output

```cpp
#include <pkr_units/format/si.h>        // std::format support for SI units
#include <pkr_units/format/cgs.h>       // std::format support for CGS units
```

## Literals (User-Defined)

```cpp
#include <pkr_units/literals/si.h>           // 5_m, 10_kg, 3_s, etc.
#include <pkr_units/literals/imperial_units.h>  // 5_ft, 150_lb, 2_mi, etc.
#include <pkr_units/literals/cgs.h>          // CGS literals (limited)
```

## Specialized

```cpp
#include <pkr_units/chrono.h>           // std::chrono conversions (time units)
#include <pkr_units/constants.h>        // Physical constants with units
#include <pkr_units/math/unit_math.h>   // Advanced math (Newton-Raphson, Runge-Kutta)
```

## Import Patterns

### Pattern 1: Basic Usage

```cpp
#include <pkr_units/si_units.h>
using pkr::units::meter_t, pkr::units::second_t;

int main() {
    meter_t distance = 100.0;
    second_t time = 5.0;
    auto speed = distance / time;
}
```

### Pattern 2: With Literals

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/literals/si.h>

using namespace pkr::units::literals;

int main() {
    auto speed = 100_m / 5_s;  // Using literals
}
```

### Pattern 3: With Formatting

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <iostream>

using pkr::units::meter_t;

int main() {
    meter_t distance = 100.0;
    std::cout << std::format("Distance: {}\n", distance);
}
```

### Pattern 4: Multiple Unit Systems

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>
#include <pkr_units/literals/si.h>
#include <pkr_units/literals/imperial_units.h>

using pkr::units::unit_cast, pkr::units::foot_t;
using namespace pkr::units::literals;

int main() {
    auto metric = 100_m;
    auto imperial = unit_cast<foot_t>(metric);
}
```

### Pattern 5: Physics Simulations

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/constants.h>
#include <pkr_units/math/unit_math.h>
#include <pkr_units/format/si.h>

using namespace pkr::units::literals;
using namespace pkr::units::physical_constants;

int main() {
    auto force = 10_kg * standard_gravity;  // Uses constant
    // Use advanced math functions as needed
}
```

## Header Dependencies

Most headers transitively include what you need:

```
si_units.h
├── base unit definitions
├── derived unit definitions  
├── unit_cast<>
├── measurement_t with uncertainty
└── matrix types

imperial_units.h
└── Depends on: si_units.h

cgs_units.h
└── Depends on: si_units.h

format/si.h
└── Depends on: si_units.h

literals/si.h
└── Depends on: si_units.h
```

## Which Header?

**"I want to measure..."**
- Distance, speed, time, force, energy, power → `si_units.h`
- Feet, inches, pounds, gallons → `imperial_units.h`
- Gauss, dyne, erg → `cgs_units.h`
- Light-years, parsecs → `astronomical_units.h`
- Physical constants → `constants.h`
- Exact conversion with symbols → Add `format/si.h`
- Convenient syntax (5_m instead of meter_t(5)) → Add `literals/si.h`

## Minimal Includes

For compile-time sensitive projects, you can include selectively:

```cpp
// Instead of #include <pkr_units/si_units.h>
#include <pkr_units/units/base/length.h>      // Just meter_t
#include <pkr_units/units/base/time.h>        // Just second_t
#include <pkr_units/units/derived/velocity.h> // Just velocity units
```

However, this is rarely necessary—`si_units.h` compiles quickly even though it defines many units.

## Namespace Usage

Most names live in `pkr::units`. Use explicit imports to avoid namespace pollution:

```cpp
using pkr::units::meter_t, pkr::units::kilogram_t;

meter_t m = 5.0;                    // Clean syntax
pkr::units::meter_t m = 5.0;        // Also valid if fully qualified
```

Literals require explicit opt-in:

```cpp
using namespace pkr::units::literals;
auto m = 5_m;  // OK
// auto m = 5_m;  // Without using statement
```

## Related

- [Getting Started](../getting-started.md) — Complete example code
- [API Overview](../api/overview.md) — What units are in each header
