# Limitations

Known constraints and workarounds for pkr_units.

## Metric Prefix Boundaries

### Smallest Mass Unit: Picogram

The library uses `std::ratio` which has `ptrdiff_t` limits on numerator/denominator (~9·10¹⁸).

```cpp
// Available
picogram_t small = 1e-15_kg;          // 10⁻¹µ kg

// Not available (would exceed std::ratio limits)
// femtogram_t tiny = 1e-18_kg;        // 10⁻¹⁸ kg
// attogram_t micro = 1e-21_kg;        // 10⁻²¹ kg
```

**Workaround:** Use raw `double` for extremely small quantities:
```cpp
double femtogram_count = value / 1e-18;  // Manual scaling
```

### Largest Length Unit: Terameter

Similar limit applies to large scales:

```cpp
// Available
terameter_t large = 1e12_m;            // 10¹² m

// Not available (would exceed limits)
// petameter_t huge = 1e15_m;           // 10¹⁵ m
```

**Workaround:** Use smaller units or manual scaling:
```cpp
auto distance = 5e15_m;  // Just treat as raw m/s result from division
```

## Floating-Point Precision

All built-in units use `double` precision (~15-17 significant digits):

```cpp
meter_t x = 123456789012345.0;  // At the precision limit
// Actual stored value may differ in last few digits

// For higher precision, use long double:
auto y = meter_t<long double>(123456789012345.0L);
```

### Temperature Edge Cases

Very small temperature differences lose precision:

```cpp
celsius_t t1 = 0.0_C;  // 273.15 K
celsius_t t2 = 1e-10_C;  // Loses precision in affine offset
```

## Affine Arithmetic Restrictions

Temperature uses affine scales (with offset), not pure linear scales:

```cpp
celsius_t cold = 0_C;
celsius_t warm = 10_C;

// Adding two absolute temperatures is meaningless
// auto sum = cold + warm;  // Don't do this!

// Getting the difference is OK
kelvin_t diff = warm - cold;  // 10 K difference

// Adding to absolute is OK (absolute + offset)
celsius_t cooler = cold - 5_K;  // -5°C
```

**Rationale:** Absolute temperatures have arbitrary zero points:
- 0°C ≠ "no temperature" (it's 273.15 K)
- Adding 10°C + 20°C = "30°C" doesn't make physical sense

## Type Explosion with Deep Nesting

Deeply nested arithmetic creates many unique types, affecting compile time:

```cpp
// Bad (many intermediate types)
auto result = a * b * c * d * e * f * g * h * i * j;

// Better (breaks into stages)
auto temp1 = a * b * c;
auto temp2 = d * e * f;
auto result = temp1 * temp2 * g * h * i * j;

// Best (explicit intermediate types)
auto temp1 = unit_cast<joule_t>(a * b);
auto temp2 = unit_cast<joule_t>(c * d);
auto result = temp1 * temp2;
```

## std::ratio Limitations

`std::ratio` has some edge cases:

```cpp
// Won't compile (denominator overflow)
// using weird_ratio = std::ratio<1, 1000000000000000000000>;

// Check your compile limits
static_assert(std::ratio<1, 1000000000000000>::num > 0);
```

## No Support for Dimensionless Zero

The type system doesn't distinguish between scalars and dimensionless quantities:

```cpp
scalar_t unitless = 5.0;
meter_t distance = 10.0;

// Conceptually: scalar + distance = error
// Practically: scalar is unitless, could mean anything
auto result = unitless + distance;  // Compiles (ratio unit is unitless)
```

**Best practice:** Don't mix scalars and dimensioned quantities.

## Matrix Limitations

### Stack Space

4×4 matrices use 128 bytes on the stack (4×4 × 8 bytes double):

```cpp
matrix_4d_units_t<meter_t> m1, m2, m3;  // 384 bytes on stack

// On systems with small stack (embedded), use arena storage:
using MatrixArena = matrix_4d_units_t<meter_t, arena_storage<meter_t, 10>>;
```

### Arena Storage Not Thread-Safe

Arena storage uses static variables without synchronization:

```cpp
// Not safe in multi-threaded context
using MatrixArena = matrix_4d_units_t<meter_t, arena_storage<meter_t, 10>>;
// Each thread needs its own pool, or use stack_storage

// Thread-safe (each thread has its own stack)
matrix_4d_units_t<meter_t> m;  // Uses stack_storage by default
```

## No Symbolic Algebra

The library does numeric computation only—no symbolic manipulation:

```cpp
// Can't simplify symbolically
// auto weird = meter_t(5) / meter_t(5);  // Type: unitless, value: 1.0
// (You could check if true, but type system doesn't know)

// Numeric evaluation
auto ratio = meter_t(10) / meter_t(5);  // 2.0 (dimensionless)
```

## Formatting Limitations

### Output Format Not Configurable Per-Instance

Symbol representation (ASCII vs Unicode) is set at compile time:

```cpp
meter_t m = 100.0;
std::cout << m;  // Uses meter_t::symbol (ASCII) by default

// To get Unicode, you'd need custom formatter
// Default format: "100 m" not "100 m²" with nice superscripts
```

## Limited to Positive Exponents

Very large exponents can overflow:

```cpp
// Normal range
auto v2 = velocity * velocity;     // m²/s² (exponent: 2, -2)

// Extreme case (rarely occurs)
// If you somehow had 1000+ dimensional exponent, could overflow int
```

## No Complex Numbers

Units don't support complex impedance (Z = R + jX):

```cpp
// Not supported
// auto impedance = ohm_t(100) + 1.0i * ohm_t(50);

// Use pairs or custom types
struct Impedance {
    ohm_t resistance;
    ohm_t reactance;
};
```

## Integer Value Types: Limited Arithmetic

If using integer value types, fractional results are truncated:

```cpp
auto m_int = meter_t<int>(100);
auto s_int = second_t<int>(3);

auto velocity = m_int / s_int;  // Result: 33 m/s (integer division, not ~33.33)

// Use double for most calculations
meter_t m = 100.0;
second_t s = 3.0;
auto v = m / s;  // 33.333... m/s
```

## Workarounds Summary

| Limitation | Workaround |
|-----------|-----------|
| Precision beyond 15 digits | Use `long double` value type |
| Extreme prefixes (smaller/larger) | Manual scaling with raw numbers |
| Type explosion in deep nesting | Break into intermediate stages |
| Integer division losing precision | Use `double` instead of `int` |
| Arena not thread-safe | Use `stack_storage` or thread-local |
| Symbol format not customizable | Write custom formatter |

## See Also

- [Implementation Notes](implementation-notes.md) — How things work
- [Type Safety](../guides/type-safety.md) — Dimensional correctness guarantees
- [Matrix Storage](../guides/matrix-storage.md) — Memory management strategies
