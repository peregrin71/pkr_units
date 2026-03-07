# pkr_units Documentation

Welcome to the **pkr_units** library—a header-only C++20 library for type-safe physical units with compile-time dimensional checking.

## I'm a...

### 👤 **User** — I want to use pkr_units in my project

#### Getting Started
- [Getting Started Guide](getting-started.md) — Installation, basic setup, first example (5 min)
- [Type Safety & Dimensional Analysis](guides/type-safety.md) — How the compiler ensures correctness

#### API Reference
- [API Overview](api/overview.md) — Quick tour of the API
- [Base Units](api/base-units/) — SI base units (length, mass, time, etc.)
- [Derived Units](api/derived-units/) — Common derived units (velocity, force, energy, etc.)
- [Constants](api/constants/) — Physical constants with proper unit types

#### How-To Guides
- [Creating Custom Units](guides/custom-units.md) — Add your own unit types
- [Temperature & Affine Units](guides/temperature.md) — Working with temperature and offsets
- [Matrix Storage Policies](guides/matrix-storage.md) — Memory management for matrices
- [Parsing Measurements](guides/parsing.md) — Parse strings and measurements

#### Quick Reference
- [Unit Symbols Reference](reference/units-table.md) — Complete table of all units and symbols
- [Architecture Overview](reference/architecture.md) — How units work (brief)
- [Limitations](reference/limitations.md) — Known constraints and workarounds
- [Symbol Guide](reference/symbols.md) — ASCII and Unicode symbol variants
- [Header Quick Reference](reference/headers.md) — Which header to include for what

---

### 🔧 **Contributor** — I want to contribute code or understand the internals

- [Developer Documentation](development/) — Architecture, design decisions, roadmap
- [Architecture Deep Dive](development/architecture-deep-dive.md) — Full internal design
- [Design Decisions](development/design-decisions.md) — Why key choices were made
- [Roadmap](development/roadmap.md) — Planned features and priorities
- [Contributing Guide](../CONTRIBUTING.md) — How to contribute


---

## Key Features

- **Compile-time safety** — Dimensional mismatches caught by the compiler
- **Type-preserving arithmetic** — Operations return the correct unit type
- **Extensive built-in units** — SI, imperial, CGS, astronomical
- **Measurements with uncertainty** — Built-in uncertainty propagation
- **Temporal analysis** — Time series with automatic derivatives
- **Extensible** — Create custom units without modifying the library
- **Zero-cost abstraction** — Header-only, fully optimizable  

---

## Browser by Task

| I want to... | Start here |
|---|---|
| Get the library working in my project | [Getting Started](getting-started.md) |
| Understand how units work | [Type Safety Guide](guides/type-safety.md) |
| See examples of common tasks | [Guides](guides/) |
| Add custom units or dimensions | [Custom Units](guides/custom-units.md) |
| Parse strings like "5.2 m" | [Parsing Guide](guides/parsing.md) |
| Work with temperature scales | [Temperature Guide](guides/temperature.md) |
| Use matrices with different storage | [Storage Policies](guides/matrix-storage.md) |
| Look up a specific unit's symbol | [Units Table](reference/units-table.md) |
| Understand the internals | [Developer Docs](development/) |

---

## Subsystems

### Measurements & Uncertainty
Represent experimental data with uncertainty:
```cpp
measurement_lin_t<meter_t> m{100.0, ±5.0};  // 100 ± 5 meters
measurement_rss_t<meter_t> m{100.0, ±5.0};  // RSS uncertainty propagation
```

### Time Series
Analyze sequences of quantities over time:
```cpp
quantity_series<meter_t> distance_series;
distance_series.add_now(100_m);
auto velocities = distance_series.time_derivative();  // meter_per_second
```

### Matrix Storage
Flexible memory management for matrix operations:
```cpp
// Stack: fast, fixed size
matrix_3d_t<meter_t, stack_storage_3d<meter_t>>

// Arena: pre-allocated buffer
matrix_3d_t<meter_t, arena_storage_3d<meter_t>>
```

---

## License

MIT — See [LICENSE](../LICENSE) for details.
