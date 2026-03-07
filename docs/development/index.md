# Developer Documentation

Architecture, design decisions, and internal implementation details for contributors and maintainers.

## New Contributor? Start Here

1. Read [Getting Started](../getting-started.md) for setup
2. Understand the [Architecture Overview](../reference/architecture.md) (5-minute read)
3. Explore [Architecture Deep Dive](./architecture-deep-dive.md) for internals
4. See [Contributing](../../CONTRIBUTING.md) for development workflow

## Documentation Map

### Core Architecture

- [Architecture Deep Dive](./architecture-deep-dive.md) — Complete internal design, type system, dimensional analysis
- [Design Decisions](./design-decisions.md) — Rationale for key trade-offs and choices
- [Architecture Overview](../reference/architecture.md) — Quick reference (for users too)

### Subsystem Design

- [Time Series Design](./time-series.md) — Temporal measurement systems, memory model, timestamps
- [Timelike Concept](./timelike-system.md) — Flexible timestamp representation
- [Storage Policies](./storage-policies.md) — Memory management strategies (stack, arena, heap)

### Roadmap & Process

- [Development Roadmap](./roadmap.md) — Planned features, known issues, and priorities
- [Contributing](../../CONTRIBUTING.md) — How to contribute code
- [Code of Conduct](../../CODE_OF_CONDUCT.md) — Community standards

## Quick Links

| I want to... | Start here |
|---|---|
| Understand how units work internally | [Architecture Deep Dive](./architecture-deep-dive.md) |
| Know why a design choice was made | [Design Decisions](./design-decisions.md) |
| Work on time series features | [Time Series Design](./time-series.md) |
| Add custom storage strategies | [Storage Policies](./storage-policies.md) |
| Contribute code | [Contributing](../../CONTRIBUTING.md) |
| Track/plan work | [Roadmap](./roadmap.md) |

## Key Concepts for Contributors

### Type System
- **`unit_t<ValueType, Ratio, Dimension>`** — Core unit template
- **Strong types** (e.g., `meter_t`) inherit from `unit_t`
- **Dimensional analysis** enforced at compile-time via template specialization
- **8 dimensions** (7 SI + plane angle)

### Template Specialization
- **`derived_unit_type_t<>`** — Maps components to strong types
- **`affine_offset_t<>`** — Temperature and other affine units
- **Zero-cost abstractions** — All checked at compile-time

### Memory & Performance
- **Stack storage** for fixed-size matrices (default)
- **Arena storage** for controlled allocation
- **PMR allocators** for series (flexible, runtime-configurable)
- **Deque-based series** for stable references and no-reallocation growth

## Architecture Diagram

```
┌─ Core Types ──────────────────────────────────┐
│  unit_t<ValueType, Ratio, Dimension>          │
│  └─ meter_t, kilogram_t, second_t, ... (strong types)
└────────────────────────────────────────────────┘
    ↓
┌─ Operators ────────────────────────────────────┐
│ meter + meter = meter                          │
│ meter × meter = square_meter (dimensional)     │
│ meter / second = meter_per_second              │
└────────────────────────────────────────────────┘
    ↓
┌─ Measurements ─────────────────────────────────┐
│ measurement_lin_t<UnitT> (linear uncertainty)  │
│ measurement_rss_t<UnitT> (RSS propagation)     │
└────────────────────────────────────────────────┘
    ↓
┌─ Temporal Systems ─────────────────────────────┐
│ quantity_series<Q, Allocator, TimeType>        │
│ measurement_series<Q, Allocator, TimeType>     │
│ timelike concept (chrono, unit-based, measurement)
└────────────────────────────────────────────────┘
    ↓
┌─ Storage ──────────────────────────────────────┐
│ stack_storage (matrices, default)              │
│ arena_storage (pre-allocated buffer)           │
│ PMR allocators (runtime-configurable)          │
└────────────────────────────────────────────────┘
```

## Development Process

### Adding a New Unit

1. Define the strong type (inherit from `unit_t`)
2. Add dimension representation
3. Add specialized `derived_unit_type_t` if it's a base or common unit
4. Add tests for arithmetic operations
5. Update documentation

### Adding a New Feature

1. Document the design in a `.md` file in this folder
2. Add tests (TDD)
3. Implement
4. Update relevant `.md` documentation
5. Submit PR with clear design rationale

### Performance Concerns

1. **Compile-time:** Use template specialization, not `if constexpr`
2. **Runtime:** All operations should be inline-able
3. **Memory:** Consider arena/pool strategies for large data

---

## See Also

- [User Documentation](../index.md)
- [References](../reference/)
- [Examples](../../examples/)
- [CMakeLists.txt](../../CMakeLists.txt) — Build system

