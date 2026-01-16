# SI Units Library - Design Document

## Overview

This document outlines the key design decisions made in the SI Units type-safe library, which provides compile-time dimensional analysis with zero runtime overhead.

---

## 1. Core Type System

### 1.1 Template-Based Dimensional Analysis

**Decision**: Use three template parameters to represent SI units:
- `type_t`: The underlying numeric type (e.g., `double`, `float`)
- `ratio_t`: The conversion ratio relative to the base SI unit (e.g., `std::milli` for millimeters)
- `dimension_t`: A compile-time value representing the physical dimension

**Rationale**:
- Provides **zero runtime overhead**: dimension checking is completely compile-time
- Allows implicit conversions between units of the same dimension via ratios
- Enables type-safe arithmetic on quantities with different scales

**Example**:
```cpp
// kilometer: 1000 meters
unit_t<double, std::kilo, length_dimension>

// millimeter: 0.001 meters  
unit_t<double, std::milli, length_dimension>
```

### 1.2 Strong Types via Inheritance

**Decision**: Use struct inheritance with `using _base` to create strong types:

```cpp
struct meter : public unit_t<double, std::ratio<1, 1>, length_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, length_dimension>;
    using _base::_base;  // Inherit constructors
};
```

**Rationale**:
- Strong typing prevents mixing incompatible units at compile-time
- `_base` typedef enables generic type introspection when needed
- Inheriting constructors (`using _base::_base`) provides clean initialization
- Allows derived unit specializations while maintaining a common base

---

## 2. Unit Type Identification

### 2.1 Template Specialization over Constexpr If

**Decision**: Use template specialization with `si_unit_type_impl<dimension_t>` for mapping dimensions to SI unit types.

**Previous Approach** (rejected):
```cpp
// Old: Multiple constexpr if branches
if constexpr (dim_v == length_dimension) return si_unit_type::meter;
else if constexpr (dim_v.mass == 1 && ...) return si_unit_type::kilogram;
// ... more conditions
```

**New Approach**:
```cpp
template<dimension_t dim_v>
struct si_unit_type_impl { /* default */ };

template<>
struct si_unit_type_impl<length_dimension> { 
    static constexpr si_unit_type value = si_unit_type::meter; 
};
// ... more specializations
```

**Rationale**:
- **Faster compilation**: Direct template matching vs. evaluating multiple conditions
- **Better extensibility**: Adding derived units only requires new specializations, not modifying conditional logic
- **Cleaner code**: Each dimension maps to exactly one specialization
- **LTO friendly**: Compiler can optimize specializations independently

---

## 3. Arithmetic Operations

### 3.1 Canonical Unit Returns

**Decision**: All addition and subtraction operations return results in the **canonical base SI unit** (ratio `<1,1>`):
- Length operations → `meter`
- Mass operations → `kilogram`
- Time operations → `second`

**Example**:
```cpp
kilometer(5) + decimeter(20)  // → meter(5.002)
meter(1000) + kilometer(1)     // → meter(2000)
```

**Rationale**:
- **Predictable return type**: Users always know the result dimension without needing type inference
- **Eliminates ambiguity**: No question about which ratio to use (would it be km, dm, or m?)
- **Type safety**: Impossible to accidentally mix units of different dimensions
- **Normalization**: Reduces result type explosion in complex expressions

### 3.2 Dimension Matching Constraint

**Decision**: Addition and subtraction only work when **dimensions exactly match**:

```cpp
template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr auto operator+(const T1& lhs, const T2& rhs) noexcept
```

**Rationale**:
- **Compile-time verification**: Prevents nonsensical operations like `meters + kilograms`
- **Dimensions don't add**: Only quantities with identical dimensions can be combined
- **Early error detection**: Invalid operations fail at compile-time with clear messages

### 3.3 Free-Function Operators

**Decision**: Implement `operator+`, `operator-`, `operator*`, and `operator/` as free functions (not class methods) that work with any `si_unit_type`.

**Benefits**:
- Works seamlessly with strong types (derived from `unit_t`) via the `is_si_unit` trait
- Enables `meter(5) + kilometer(3)` without explicit conversions
- Consistent API for all unit combinations

**Implementation**:
```cpp
template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr auto operator+(const T1& lhs, const T2& rhs) noexcept { /* ... */ }
```

### 3.4 Multiplication and Division

**Decision**: Allow multiplication and division of any two si_unit types with **dimension combination**:
- **Multiplication**: Dimensions add (exponents add)
- **Division**: Dimensions subtract (exponents subtract)
- **Ratios**: Combined using `std::ratio_multiply` and `std::ratio_divide`

**Example**:
```cpp
meter(2) * second(3)  // → unit_t<..., length:1, time:1> with value 6
meter(5) / second(2)  // → unit_t<..., length:1, time:-1> with value 2.5
```

**Rationale**:
- **No dimension matching required**: Unlike addition/subtraction
- **Precise ratio arithmetic**: Using `std::ratio` for exact calculations
- **Type-safe dimensional analysis**: Result dimensions computed at compile-time

### 3.5 Arithmetic Helper Functions

**Decision**: Factor arithmetic into standalone functions templated **only on value type and ratios**, not on unit types:

```cpp
template<typename type_t, typename ratio_t1, typename ratio_t2>
constexpr type_t add_canonical(type_t val1, type_t val2) noexcept;

template<typename type_t>
constexpr type_t multiply_values(type_t val1, type_t val2) noexcept;
```

**Rationale**:
- **Smaller binary size**: The actual arithmetic is instantiated once per value type (e.g., one for `double`), 
  not once per unit-type pair (could be thousands of instantiations)
- **Better link-time optimization**: Compiler can inline and optimize pure arithmetic functions more aggressively
- **Cleaner separation of concerns**: Type checking in operators, computation in helpers
- **Easier to profile/optimize**: Arithmetic logic is isolated and simple

**Design Trade-off**:
```
// Without factoring: 
operator+(meter, kilometer) → specialized implementation
operator+(meter, millimeter) → another specialized implementation
// ... one instantiation per unit pair

// With factoring:
operator+(meter, kilometer) → delegates to add_canonical<double, ratio<1,1>, std::kilo>
operator+(meter, millimeter) → delegates to add_canonical<double, ratio<1,1>, std::milli>
// ... one add_canonical per value type, shared across all unit pairs
```

---

## 4. Type Introspection

### 4.1 is_si_unit Trait

**Decision**: Provide a trait that extracts unit components:

```cpp
template<typename T>
struct is_si_unit
{
    static constexpr bool value = /* ... */;
    using value_type = type_t;
    using ratio_type = ratio_t;
    static constexpr dimension_t value_dimension = dim_v;
};
```

**Specializations**:
1. **Direct unit_t types**: `is_si_unit<unit_t<type_t, ratio_t, dim_v>>`
2. **Derived strong types**: Uses SFINAE to detect types derived from `unit_t` via `_base`

**Example**:
```cpp
struct meter : public unit_t<double, std::ratio<1, 1>, length_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, length_dimension>;
    using _base::_base;
};

// is_si_unit<meter> extracts components from meter::_base
```

**Rationale**:
- Enables generic code to work with any unit type (including strong types)
- Allows extraction of dimension for dispatch (via template specialization)
- Works transparently with both `unit_t<...>` and derived strong types
- `_base` pattern enables compile-time introspection

### 4.2 si_unit_type Concept

**Decision**: Use a concept to constrain templates to only accept SI unit types:

```cpp
template<typename T>
concept si_unit_type = is_si_unit<T>::value;
```

**Rationale**:
- Provides clear semantic intent in function signatures
- Better error messages when non-unit types are passed
- Enables overload resolution for unit-specific operations

---

## 5. Multiplication and Division

**Design Note**: The existing implementation in `unit_t` class template maintains dimension combination:
- **Multiplication**: Dimensions add (e.g., meter × second = meter·second)
- **Division**: Dimensions subtract (e.g., meter ÷ second = meter/second)
- **Ratios**: Combined using `std::ratio_multiply` and `std::ratio_divide`

These operations preserve the full precision of rational arithmetic.

---

## 6. Zero-Cost Abstraction Principles

The design ensures:

1. **No runtime overhead**: All unit checking happens at compile-time
2. **Minimal code bloat**: Arithmetic factoring reduces instantiation count
3. **Inline-friendly**: Small functions allow aggressive inlining
4. **Type erasure opportunity**: Non-templated functions can be called through function pointers if needed

---

## 7. Future Extensibility

### Adding Derived Units

Add new specializations to `si_unit_type_impl`:
```cpp
template<>
struct si_unit_type_impl<force_dimension> {
    static constexpr si_unit_type value = si_unit_type::newton;
};
```

### Adding Derived Dimensions

Define new dimension constants and specializations without modifying existing logic.

### Adding New Value Types

Arithmetic helpers automatically support new types (e.g., `float`, `long double`, custom scalar types).

---

## 8. Summary of Trade-offs

| Decision | Benefits | Trade-offs |
|----------|----------|-----------|
| Template specialization for dimension mapping | Faster compilation, extensibility | More boilerplate code |
| Canonical unit returns | Type predictability | Users lose the original unit scale |
| Dimension matching only | Type safety | Cannot combine different physical quantities |
| Arithmetic factoring | Smaller binaries, better optimization | Additional indirection layer |
| Strong types via inheritance | Type safety, readability | Requires explicit strong type declarations |

---

## References

- [C++20 Concepts](https://en.cppreference.com/w/cpp/language/constraints)
- [std::ratio](https://en.cppreference.com/w/cpp/numeric/ratio)
- [Template Specialization](https://en.cppreference.com/w/cpp/language/template_specialization)
