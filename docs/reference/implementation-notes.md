# Implementation Notes

Technical details about the architecture and design of pkr_units.

## Core Architecture

### The Generic Unit Type

All units are specializations of a single generic template:

```cpp
template <typename ValueType, typename Ratio, dimension_t Dimension>
class unit_t {
    ValueType value;  // The numeric value
public:
    constexpr unit_t(ValueType v = {}) noexcept : value(v) {}
    constexpr ValueType count() const noexcept { return value; }
    // ... operators
};
```

**Parameters:**
- `ValueType`: `double`, `float`, or custom numeric type—the underlying value
- `Ratio`: `std::ratio<N, D>`—the conversion factor to SI base unit
- `Dimension`: 8-integer exponent vector—dimensional information

**Example:** `meter_t` becomes:
```cpp
using meter_t = unit_t<double, std::ratio<1, 1>, length_dimension>;
```

### Dimension Representation

Dimensions use a 9-tuple of integer exponents following SI:

```cpp
struct dimension_t {
    int mass;           // Kilogram (M)
    int length;         // Meter (L)
    int time;           // Second (T)
    int current;        // Ampere (I)
    int temperature;    // Kelvin (Θ)
    int amount;         // Mole (N)
    int luminosity;     // Candela (J)
    int angle;          // Radian (α)
    int solid_angle;    // Steradian (Ω)
};
```

Examples:
- **Length**: `{0, 1, 0, 0, 0, 0, 0, 0, 0}` (L¹)
- **Velocity**: `{0, 1, -1, 0, 0, 0, 0, 0, 0}` (L¹T⁻¹)
- **Force**: `{1, 1, -2, 0, 0, 0, 0, 0, 0}` (M¹L¹T⁻²)
- **Energy**: `{1, 2, -2, 0, 0, 0, 0, 0, 0}` (M¹L²T⁻²)
- **Solid Angle**: `{0, 0, 0, 0, 0, 0, 0, 0, 1}` (Ω¹)

### Ratio Scaling

The `std::ratio` template encodes unit conversion:

```cpp
// kilometer_t
using kilometer_t = unit_t<double, std::ratio<1000, 1>, length_dimension>;
// 1 km = 1000 m

// millisecond_t
using millisecond_t = unit_t<double, std::ratio<1, 1000>, time_dimension>;
// 1 ms = 0.001 s
```

Ratios are stored as exact fractions (numerator/denominator) to avoid floating-point errors in conversions.

## Operator Semantics

### Addition & Subtraction

Precondition: LHS and RHS must have identical dimensions

```cpp
template <typename V1, typename R1, typename D1,
          typename V2, typename R2>
unit_t<V1, R1, D1> operator+
    (unit_t<V1, R1, D1> lhs, unit_t<V2, R2, D1> rhs) 
{
    // Convert RHS to LHS scaling, add values, return LHS type
    return unit_t<V1, R1, D1>(
        lhs.count() + rhs.count() * (R2::num * R1::den) 
                                 / (R2::den * R1::num)
    );
}
```

Result type is always the **left-hand side** type.

### Multiplication

Dimensions are combined (exponents added):

```cpp
// meter_t * meter_t = square_meter_t
// Dimension: {0,1,0,0,0,0,0,0} + {0,1,0,0,0,0,0,0} = {0,2,0,0,0,0,0,0}
```

Ratio is computed as: `(R1::num * R2::num) / (R1::den * R2::den)`

Result type is determined by `derived_unit_type_t` type deduction.

### Division

Dimensions are combined (exponents subtracted):

```cpp
// meter_t / second_t = meter_per_second_t
// Dimension: {0,1,0,0,0,0,0,0} - {0,0,1,0,0,0,0,0} = {0,1,-1,0,0,0,0,0}
```

Ratio is computed as: `(R1::num * R2::den) / (R1::den * R2::num)`

## Type Deduction: derived_unit_type_t

When you multiply/divide units, the result type is automatically deduced via specialization:

```cpp
template <typename ValueType, typename Ratio, dimension_t Dimension>
struct derived_unit_type_t {
    using type = /* most specific type for this combination */;
};
```

**Examples of specializations:**
```cpp
template <>
struct derived_unit_type_t<double, std::ratio<1, 1>, velocity_dimension> {
    using type = meter_per_second_t;
};

template <>
struct derived_unit_type_t<double, std::ratio<1, 1>, force_dimension> {
    using type = newton_t;
};
```

When no specialization exists, the result is the generic `unit_t` type.

## Compile-Time Checks

Dimensional correctness is enforced via `static_assert`:

```cpp
template <typename Lhs, typename Rhs>
auto operator+(Lhs lhs, Rhs rhs) {
    static_assert(std::is_same_v<typename Lhs::dimension_type, 
                                 typename Rhs::dimension_type>,
                  "Cannot add different dimensions");
    // ...
}
```

This causes compiler errors before runtime, with clear messages about dimension mismatches.

## Floating-Point Precision

All built-in units use `double` (IEEE 754, ~15 significant digits):

```cpp
meter_t x = 123456789.123456789;  // Some digits lost to precision
// Stored as: 123456789.1234567
```

For higher precision, custom value types can be used:

```cpp
auto y = meter_t<long double>(123456789012345.0L);
```

## Unit Conversion via unit_cast

Conversions between same-dimension units are explicit:

```cpp
template <typename TargetUnit, typename SourceUnit>
requires(std::is_same_v<typename SourceUnit::dimension_type, 
                        typename TargetUnit::dimension_type>)
constexpr TargetUnit unit_cast(SourceUnit source) {
    using ratio_conversion = std::ratio_divide<
        typename SourceUnit::ratio_type, 
        typename TargetUnit::ratio_type
    >;
    
    return TargetUnit(
        source.count() * 
        (double)ratio_conversion::num / ratio_conversion::den
    );
}
```

The conversion factor is computed at compile time using `std::ratio` arithmetic.

## Measurement Uncertainty

`measurement_t<Unit>` pairs a value with uncertainty:

```cpp
template <typename Unit>
struct measurement_t {
    Unit value;
    Unit uncertainty;
    
    // Propagation strategies:
    // - RSS (Root Sum of Squares): assumed independent
    // - Worst-case: assume perfectly correlated
};
```

Uncertainty propagates automatically through operators based on selected strategy.

## Affine Arithmetic (Temperature)

Absolute temperatures (Celsius, Fahrenheit) use special handling for conversions:

```cpp
// Celsius: Tc = Tk - 273.15
// Fahrenheit: Tf = (9/5) * Tk - 459.67

// These offsets are baked into conversion formulas
// Differences (delta) use linear arithmetic without offsets
```

## Performance Characteristics

- **Compilation**: O(template instantiation count)
- **Runtime arithmetic**: O(1)—optimized to single FPU operation
- **Memory footprint**: Identical to underlying `double`
- **No virtual functions**: Full devirtualization/inlining
- **No heap allocation**: Stack-only (unless using matrix arena storage)

## Header Organization

```
sdk/include/pkr_units/
├── si_units.h              (Main entry point)
├── imperial_units.h        
├── cgs_units.h             
├── astronomical_units.h    
├── literal/               (User-defined literals)
├── format/                (Output formatting)
├── constants.h            (Physical constants)
├── math/                  (Advanced math)
├── measurements/          (Uncertainty support)
└── units/                 (Detailed unit definitions)
    ├── base/
    ├── derived/
    └── impl/              (Internal implementation)
```

## Extensibility Points

Users can add custom units by:
1. Defining a new type inheriting from `unit_t`
2. Adding `derived_unit_type_t` specializations
3. (Optional) Adding literals, format support, etc.

See [Creating Custom Units](../guides/custom-units.md).

## Testing Strategy

The library includes:
- **Unit tests** (1334+) for individual dimensions
- **Integration tests** for conversions between systems
- **Dimensional analysis tests** ensuring correctness
- **Performance benchmarks** against raw numeric operations

All tests use `std::cout` assertions (no external test framework required in core library).

## Related

- [Type Safety](../guides/type-safety.md) — How dimensional checking works
- [Creating Custom Units](../guides/custom-units.md) — Extending the system
- [Limitations](limitations.md) — Known constraints
