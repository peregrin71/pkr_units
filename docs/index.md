# pkr_units Documentation

Welcome to the **pkr_units** library—a header-only C++20 library for type-safe physical units with compile-time dimensional checking.

## Quick Navigation

### Getting Started
- [Getting Started Guide](getting-started.md) — Installation, basic usage, first example

### API Reference
- [Base Units](api/base-units/) — SI base units (length, mass, time, current, temperature, amount, intensity)
- [Derived Units](api/derived-units/) — Common derived units (velocity, force, energy, power, pressure, etc.)
- [Constants](api/constants/) — Physical constants with proper unit types
- [Unit Symbols Reference](reference/units-table.md) — Complete table of all unit types and symbols

### Guides & How-To
- [Creating Custom Units](guides/custom-units.md) — Extend the library with your own unit types
- [Matrix Storage Policies](guides/matrix-storage.md) — Memory management for matrix operations
- [Type Safety & Dimensional Analysis](guides/type-safety.md) — How the compiler ensures correctness
- [Temperature & Affine Units](guides/temperature.md) — Working with affine quantities

### Reference
- [Implementation Notes](reference/implementation-notes.md) — Architecture and design
- [Limitations](reference/limitations.md) — Known constraints and workarounds
- [Symbol Guide](reference/symbols.md) — ASCII and Unicode symbol variants
- [Header Quick Reference](reference/headers.md) — Which header to include for what

## Key Features

- **Compile-time safety** — Dimensional mismatches caught by the compiler
- **Type-preserving arithmetic** — Operations return the correct unit type
- **Extensive built-in units** — SI, imperial, CGS, astronomical
- **Measurements with uncertainty** — Built-in uncertainty propagation
- **Extensible** — Create custom units and dimensions
- **Zero-cost abstraction** — Header-only, fully optimizable  

## Browser Roadmap by Use Case

| I want to... | Start here |
|---|---|
| Get the library working in my project | [Getting Started](getting-started.md) |
| Understand the API | [API Overview](api/overview.md) |
| See examples of common tasks | [Guides](guides/) |
| Add custom units or dimensions | [Creating Custom Units](guides/custom-units.md) |
| Look up a specific unit's symbol | [Units Table](reference/units-table.md) |
| Understand memory management | [Matrix Storage Policies](guides/matrix-storage.md) |
| Check implementation details | [Reference](reference/) |

## License

MIT — See [LICENSE](../LICENSE) for details.
