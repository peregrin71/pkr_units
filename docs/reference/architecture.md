# Architecture Overview

A quick reference to pkr_units' internal design for users who want to understand how it works.

## Core Concepts

### Type-Based Unit Representation

Every unit is a template specialization in the form:

```cpp
unit_t<ValueType, Ratio, Dimension>
```

For example:
- `meter_t` = `unit_t<double, std::ratio<1,1>, length_dimension>`
- `kilometer_t` = `unit_t<double, std::kilo, length_dimension>`

Strong type wrappers (like `meter_t`) inherit from this template for type safety.

### Compile-Time Dimensional Analysis

Dimensions are stored as a 9-element exponent vector at compile-time:

```cpp
meter × meter = square_meter    // [L] × [L] = [L²]
meter / second = meter_per_sec  // [L] × [T⁻¹] = [L·T⁻¹]
force × distance = energy       // [M·L·T⁻²] × [L] = [M·L²·T⁻²]
```

The compiler validates all operations match dimensionally.

### Affine Units (Temperature)

Some quantities like temperature have an arbitrary zero point. These use an offset:

```cpp
// Celsius zero point = 273.15 Kelvin
celsius_to_kelvin: K = °C + 273.15
```

The library handles this automatically via template specialization.

## For More Details

- **Full architectural guide**: [Architecture Deep Dive](../development/architecture-deep-dive.md) (for contributors)
- **Design trade-offs**: [Design Decisions](../development/design-decisions.md)
- **Specific deep dives**: See [Developer Documentation](../development/)

