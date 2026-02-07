# Reference Documentation

Technical details and reference materials for advanced usage and implementation understanding.

## Reference Materials

- **[Units Table](units-table.md)** — Complete listing of all unit types, names, and symbols
  - Searchable table of all 300+ unit types
  - ASCII and Unicode symbol variants
  - Header file locations

- **[Symbol Guide](symbols.md)** — ASCII vs. Unicode notation
  - When to use each format
  - Configuration in output formatting
  - Accessibility considerations

- **[Header Quick Reference](headers.md)** — Which header to include
  - Main entry points
  - Category-specific headers
  - Import patterns
  - Dependencies

- **[Implementation Notes](implementation-notes.md)** — Architecture and design
  - Type system model (core `unit_t<>` template)
  - Dimension tracking mechanism
  - Type deduction strategies
  - Arithmetic rules and semantics

- **[Limitations](limitations.md)** — Known constraints
  - Prefix boundaries (attogram to teragram)
  - Temperature affine arithmetic restrictions
  - std::ratio compile-time limits
  - Floating-point precision expectations

## Advanced Topics

### Type System

The core of pkr_units is the generic `unit_t` template:

```cpp
template <typename ValueType, typename Ratio, dimension_t Dimension>
class unit_t { /* ... */ };
```

- **ValueType**: `double`, `float`, or custom numeric type
- **Ratio**: `std::ratio<N, D>` encoding the conversion to SI base
- **Dimension**: 8-integer vector tracking unit exponents

Example: `meter_t` → `unit_t<double, std::ratio<1,1>, length_dimension>`

### Dimensional Analysis

Dimensions are tracked as 8 integer exponents:
- Mass (M), Length (L), Time (T), Current (I)
- Temperature (Θ), Amount (N), Luminosity (J), Angle (α)

Arithmetic rules automatically combine dimensions:
- Multiply: Add exponent vectors
- Divide: Subtract exponent vectors
- Add/Subtract: Exponent vectors must match (same dimension)

### Type Deduction

When you compute with units, the result type is automatically deduced via `derived_unit_type_t`:

```cpp
template <typename ValueType, typename Ratio, dimension_t Dimension>
struct derived_unit_type_t {
    using type = /* most specific type for this (ValueType, Ratio, Dimension) */;
};
```

This enables `10_m / 5_s` to return `meter_per_second_t` rather than generic `unit_t`.

## Design Philosophy

The library emphasizes:
1. **Compile-time safety** — All dimensional checks at compile time
2. **Type preservation** — Operations maintain strong types where possible
3. **Zero-cost abstraction** — No runtime overhead vs. bare `double`
4. **Extensibility** — Users can add custom units easily
5. **Transparency** — No hidden conversions or implicit casting

## Performance Characteristics

- **Compilation**: Moderate (templates are expanded)
- **Runtime**: Zero overhead (inline, constexpr capable)
- **Arithmetic**: Same speed as `double` operations
- **Memory**: Identical footprint to underlying scalar type

## Compatibility

- **Standard**: C++20
- **Compilers**: GCC, Clang, MSVC (recent versions)
- **Platforms**: Windows, Linux, macOS, embedded systems
- **Header-only**: No separate compilation needed

## Testing & Quality

The library includes:
- 1334+ test cases across 82 test suites
- Dimensional analysis verification tests
- Conversion accuracy tests
- Performance benchmarks
- Symbol formatting tests

## Version & Updates

- **License**: MIT
- **Repository**: https://github.com/your-org/pkr_units
- **Issue Tracker**: GitHub Issues

## Related Resources

- [Getting Started](../getting-started.md) — Quick start guide
- [Guides](../guides/) — How-to documentation
- [API Reference](../api/overview.md) — Available units
