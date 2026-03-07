# Design Decisions

Detailed rationale for key architectural choices in pkr_units.

## Overview

This document explains the "why" behind specific design decisions: trade-offs made, alternatives considered, and the reasoning that led to the current implementation.

---

## Type System Decisions

### Decision: Three-Parameter Template for Units

We use `unit_t<ValueType, Ratio, Dimension>` instead of a single-parameter template:

**Alternatives Considered:**
- Single template parameter with embedded metadata ❌ Worse compile-time reflection
- Runtime type identification ❌ Violates zero-cost abstraction
- Macro-based unit definitions ❌ Poor IDE support and harder to debug

**Rationale:**
- Three parameters map cleanly to the mathematical properties of units
- ValueType (runtime storage), Ratio (conversion scale), Dimension (semantic)
- Each parameter can be specialized independently for optimization

---

## Naming Convention: The `_t` Suffix

All strong type names end with `_t` (e.g., `meter_t`, `kilogram_t`).

**Alternatives Considered:**
- No suffix: `meter`, `kilogram` ❌ Pollutes general namespace
- `_unit` suffix: `meter_unit`, `kilogram_unit` ❌ Verbose
- `unit_*` prefix: `unit_meter`, `unit_kilogram` ❌ Inconsistent with standard C++

**Rationale:**
- Follows C++ convention (`size_t`, `time_t`, standard library types)
- Short and unambiguous
- Known POSIX conflicts are minimal and resolvable via use context

---

## Dimensional System: Extending SI with Angle

We add angle (radians) as an explicit dimension beyond the 7 standard SI bases.

**Standard SI System (7 dimensions):**
- Length, Mass, Time, Current, Temperature, Amount, Intensity

**Our System (8 dimensions):**
- Standard 7 + Plane Angle

**Alternatives Considered:**
- Pure SI (angle as dimensionless) ❌ Loses type safety in rotational mechanics
- Separate concept for "angular" ❌ Duplicates too many type definitions
- Runtime angle tracking ❌ Violates zero-cost abstraction

**Rationale:**
- Enables compile-time validation of rotational code
- Catches errors: `angular_velocity ≠ linear_velocity` at compile-time
- Common use case: robotics, control systems, mechanics simulations
- Trade-off: deviates from strict SI definition but improves practical safety

---

## Template Specialization for Unit Type Mapping

We map `(ValueType, Ratio, Dimension)` triplets to strong types via `derived_unit_type_t<>` specialization.

**Alternative: Use `if constexpr`:**
```cpp
if constexpr (ratio == std::kilo && dimension == length) {
    using result = kilometer_t;
}
// ... more conditions
```

**Why specialization instead:**
- Clearer intent (trait = "lookup table", not "mini-program")
- Easier to extend with specializations (add new specialization = add file location)
- Natural for custom behaviors (e.g., affine temperature)
- Standard C++ pattern (familiar to template programmers)

---

## Affine Offset Support

Temperature scales have arbitrary zero points (e.g., 0°C ≠ 0 K).

**Implementation approach:**
- Template specialization: `affine_offset_t<temperature_type>::value`
- Auto-applied during `unit_cast` for affine types
- Transparent to user (no manual offset arithmetic needed)

**Alternative: Runtime offset field:**
```cpp
struct temperature_t {
    double value;
    double offset;  // ❌ Adds runtime data, violates zero-cost
};
```

---

## Storage Policies for Matrices

Matrix storage (stack vs. arena) is configurable via policy pattern:

```cpp
matrix_3d_t<ValueType, StoragePolicy>
```

**Alternatives Considered:**
- Single fixed storage (stack only) ❌ Inflexible for large data
- Single fixed storage (heap only) ❌ Unnecessary allocation for small data
- Static type dispatch ✓ Chosen approach

**Rationale:**
- Policies are zero-cost abstractions (compile-time choice)
- Stack policy for common case (performance)
- Arena policy for controlled allocation (systems code)
- User chooses policy at instantiation; performance is deterministic

---

## Measurements with Uncertainty

We provide `measurement_lin_t<>` and `measurement_rss_t<>` for uncertain quantities.

**Design decisions:**

1. **Wrapper type, not inherited:** Measurement wraps a unit, doesn't inherit
   - Rationale: uncertainty propagation is logic, not a unit property

2. **Two variants (linear and RSS):**
   - `measurement_lin_t` — symmetric uncertainty (simple addition)
   - `measurement_rss_t` — root-sum-square propagation (physics standard)
   - Rationale: different use cases require different propagation methods

3. **Automatic propagation on operations:**
   ```cpp
   auto result = m1 + m2;  // Uncertainty auto-propagated
   ```
   - Rationale: consistency with physics expectations

---

## See Also

- [Design Trade-offs](./design-decisions.md) — This document
- [Architecture Deep Dive](./architecture-deep-dive.md) — Full technical details
- [Time Series Design](./time-series.md) — Temporal system architecture
- [Storage Policies](./storage-policies.md) — Memory management design

