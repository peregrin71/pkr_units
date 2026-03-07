# Architecture Deep Dive

A comprehensive guide to the internal design of pkr_units for contributors and maintainers.

## Table of Contents

1. [Core Design Philosophy](#design-philosophy)
2. [Type System Architecture](#type-system)  
3. [Dimensional Analysis](#dimensional-analysis)
4. [Template Specialization Strategy](#specialization)
5. [Memory & Performance](#performance)

---

## Design Philosophy {#design-philosophy}

The SI Units library is built on four core principles:

1. **Type Safety** — Dimensional errors caught at compile-time, not runtime
2. **Clear Semantic Types** — Expressive domain-specific types (e.g., `meter_t`, `kilogram_t`)
3. **Zero-Cost Abstraction** — All checking at compile-time; conversions optimized away when possible
4. **Extensibility** — Users can define custom units in their own code

---

## Type System Architecture {#type-system}

### Parameter-Based Unit Representation

All units are template specializations using three core parameters:

```cpp
template <typename ValueType, typename Ratio, dimension_t Dimension>
class unit_t;
```

**Parameters:**
- `ValueType` — `double`, `float`, or custom numeric type
- `Ratio` — `std::ratio<N, D>` for conversion to SI base unit
- `Dimension` — 8-integer exponent vector (see [Dimensional Analysis](#dimensional-analysis))

**Example:** `kilometer_t<double>` becomes:
```cpp
unit_t<double, std::kilo, length_dimension>
```

### Strong Typing via Inheritance

Semantic types inherit from `unit_t`:

```cpp
struct meter_t final : public unit_t<double, std::ratio<1, 1>, length_dimension> {
    using _base = unit_t<double, std::ratio<1, 1>, length_dimension>;
    using _base::_base;  // Inherit constructors
};
```

The `_base` member allows runtime type introspection and generic operations.

### Type Naming Convention: The `_t` Suffix

All strong type structs use the `_t` postfix for consistency:
- `meter_t`, `kilogram_t`, `second_t`, `ampere_t`

**Rationale:**
- Consistent with C++ conventions (`size_t`, `time_t`)
- Prevents namespace collisions
- Clearly indicates "this is a strong type"

---

## Dimensional Analysis {#dimensional-analysis}

### The 8-Dimensional SI System

The standard 7 SI base dimensions are extended with an 8th for plane angle:

```cpp
struct dimension_t {
    int length;          // [L] meter
    int mass;            // [M] kilogram  
    int time;            // [T] second
    int current;         // [I] ampere
    int temperature;     // [Θₖ] kelvin
    int amount;          // [N] mole
    int intensity;       // [J] candela
    int angle;           // [θ] radian (8th dimension)
};
```

**Why add angle?**

While ISO 80000-3 treats radians as dimensionless, explicit angle tracking enables:
- Type-safe rotational mechanics (`angular_velocity_t` ≠ `linear_velocity_t`)
- Compile-time validation: `torque = force × radius` (angle cancels correctly)
- Prevention of common bugs (confusing angular and linear quantities)

### Dimension Arithmetic

Operations derive the result dimension:

```cpp
// meter × meter = square_meter
// [L] × [L] = [L²]

// meter / second = meter_per_second  
// [L] × [T⁻¹] = [L·T⁻¹]

// newton × meter = newton_meter
// [M·L·T⁻²] × [L] = [M·L²·T⁻²]
```

The type system enforces these rules at compile-time via template specialization.

---

## Template Specialization Strategy {#specialization}

### Mapping Components to Strong Types

The `derived_unit_type_t` trait maps `(ValueType, Ratio, Dimension)` triplets to strong types:

```cpp
// Generic fallback
template<typename type_t, typename ratio_t, dimension_t dim_v>
struct derived_unit_type_t {
    using type = unit_t<type_t, ratio_t, dim_v>;
};

// Specialization for meter
template<>
struct derived_unit_type_t<double, std::ratio<1, 1>, length_dimension> {
    using type = meter_t;
};

// Specialization for kilometer  
template<>
struct derived_unit_type_t<double, std::kilo, length_dimension> {
    using type = kilometer_t;
};
```

**Why specialization over `if constexpr`?**
- Enables custom behavior per unit type (e.g., temperature affine offset)
- Clearer intent and easier to debug
- Natural fit for C++ template system

### Affine Unit Support

Some quantities have an offset (e.g., temperature scales). The `affine_offset_t` trait provides this:

```cpp
template<typename UnitT>
struct affine_offset_t;

// Specialization for Celsius
template<>
struct affine_offset_t<celsius_t> {
    static constexpr double value = 273.15;  // Kelvin offset
};
```

---

## Memory & Performance {#performance}

### Storage Policy Pattern

Matrix and series storage use configurable policies:

```cpp
template<typename T, typename StoragePolicy>
class matrix_3d_t {
    StoragePolicy storage;
};
```

**Stack Storage** (default, fixed-size):
```cpp
matrix_3d_t<meter_t<double>, stack_storage_3d<meter_t<double>>>
```

**Arena Storage** (pre-allocated buffer):
```cpp
std::pmr::monotonic_buffer_resource resource(buffer.data(), buffer.size());
matrix_3d_t<meter_t<double>, arena_storage_3d<meter_t<double>>>
```

### Compile-Time Optimization

- All ratio calculations happen at compile-time
- Dimension checking generates no runtime code (all template instantiation)
- Conversions compile to simple multiplications (often optimized to constants)

---

## See Also

- [Design Decisions](design-decisions.md) — Specific design trade-offs and rationale
- [Time Series Design](time-series.md) — Temporal measurement systems
- [Storage Policies](storage-policies.md) — Memory management strategies

