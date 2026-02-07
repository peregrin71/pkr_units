# Guides & How-To

Learn how to use pkr_units effectively for your specific use cases.

## Quick Links

- **[Creating Custom Units](custom-units.md)** — Extend the library with your own unit types
  - Define custom dimensions
  - Implement new unit types
  - Register with type deduction system
  - Best practices and patterns

- **[Matrix Storage Policies](matrix-storage.md)** — Flexible memory management for 4×4 matrices
  - Stack vs. arena allocation
  - Profiling your usage
  - Configuration for embedded systems
  - Performance characteristics

- **[Type Safety & Dimensional Analysis](type-safety.md)** — Compile-time correctness guarantees
  - How the compiler prevents unit mismatches
  - Dimension tracking
  - Common patterns and pitfalls

- **[Temperature & Affine Units](temperature.md)** — Working with affine quantities
  - Kelvin vs. Celsius vs. Fahrenheit
  - Temperature differences
  - Conversion rules

- **[Symbol Reference](../reference/symbols.md)** — ASCII and Unicode variants 
  - When to use each
  - Configuration options
  - Formatting for output

## By Use Case

### I want to...

**...measure quantities in SI units**
→ See [Getting Started](../getting-started.md) and [Base Units](../api/base-units/)

**...perform physics calculations**
→ See [Derived Units](../api/derived-units/) and [Type Safety](type-safety.md)

**...extend the library with custom units**
→ See [Creating Custom Units](custom-units.md)

**...work with matrices**
→ See [Matrix Storage Policies](matrix-storage.md)

**...use imperial or CGS units**
→ See [API Overview](../api/overview.md)

**...understand the type system**
→ See [Type Safety & Dimensional Analysis](type-safety.md)

**...work with measurements and uncertainty**
→ See [Getting Started](../getting-started.md) (Measurements section)

## Common Patterns

### Pattern: Unit Conversion

```cpp
#include <pkr_units/si_units.h>
using pkr::units::meter_t, pkr::units::unit_cast, pkr::units::foot_t;

meter_t metric = 100.0;
auto imperial = unit_cast<foot_t>(metric);
```

### Pattern: Physics Calculation

```cpp
auto force = 10_kg * 5_m_per_s2;      // Newton
auto work = force * 10_m;              // Joule
auto power = work / 2_s;               // Watt
```

### Pattern: Type-Safe Data Structure

```cpp
struct Measurement {
    meter_t position;
    meter_per_second_t velocity;
    meter_per_second_squared_t acceleration;
};
```

### Pattern: Custom Unit Definition

```cpp
namespace my_units {
    struct rpm_t final : public details::unit_t<double, ...> { /* ... */ };
}
```

## Next Steps

- Explore the [API Reference](../api/)
- Review [implementation details](../reference/implementation-notes.md)
- Check the `examples/` directory in the repository
