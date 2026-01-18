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

### 1.3 Type Naming Convention: The `_t` Postfix

**Decision**: All strong type struct names use the `_t` postfix (e.g., `meter_t`, `kilogram_t`, `ampere_t`).

```cpp
struct meter_t final : public unit_t<double, std::ratio<1, 1>, length_dimension> { /* ... */ };
struct kilogram_t final : public unit_t<double, std::ratio<1, 1>, mass_dimension> { /* ... */ };
struct second_t final : public unit_t<double, std::ratio<1, 1>, time_dimension> { /* ... */ };
struct ampere_t final : public unit_t<double, std::ratio<1, 1>, current_dimension> { /* ... */ };
```

**Rationale**:
- **Consistent naming discipline**: Applies the same naming convention as template aliases (`length_unit_t`, `mass_unit_t`), reinforcing the pattern that `_t` and `_unit_t` denote concrete strong types
- **C++ naming conventions alignment**: Follows the common C++ convention of using `_t` to denote type aliases and strong types (inherited from POSIX where applicable)
- **Prevents naming collisions**: Ensures that non-suffixed names (e.g., `meter`, `kilogram`) are available for future use without conflicts with the strong type definitions

**POSIX Compatibility Considerations**:

This library prioritizes **type safety and clarity over strict POSIX compatibility**. While POSIX defines several `_t` types (e.g., `time_t`, `pid_t`, `size_t`), the SI units library consciously chooses to use the `_t` postfix for all strong types.

**Known POSIX Conflicts Avoided**:
- ✗ `time_t` conflict → Resolved by using `second_t` instead of `time_t` or `second`
- ✗ `pid_t` conflict → Not applicable (no "process ID" unit)
- ✗ `size_t` conflict → Not applicable (no "size" unit in SI)

**Deliberate Trade-off**:
The decision to use `_t` universally, rather than conditionally avoid POSIX conflicts, prioritizes:
1. **Internal consistency**: All strong types follow the same naming pattern
2. **Clarity**: The `_t` suffix immediately indicates "this is a strong type"
3. **Forward compatibility**: Prevents future naming conflicts if new POSIX types are introduced
4. **Code readability**: Type definitions are unmistakably identified as strong types

**Usage Pattern**:
```cpp
// Recommended: Use the _t suffix directly
pkr::units::meter_t distance{100.0};
pkr::units::kilogram_t mass{75.0};
pkr::units::second_t time_elapsed{30.0};

// Type aliases (optional, for backward compatibility where needed)
using meter = meter_t;  // If desired for specific contexts
```

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

### 3.1 Addition and Subtraction Return Type (Option 2: LHS Type)

**Decision**: Addition and subtraction operations return results in the **same unit type as the left-hand side (LHS) operand**, converting the right-hand side as needed:

**Example**:
```cpp
meter(500) + kilometer(1)    // → meter(1500)      [LHS type: meter]
kilometer(1) + meter(500)    // → kilometer(1.5)   [LHS type: kilometer]
millimeter(500) + meter(1)   // → millimeter(1500) [LHS type: millimeter]
meter(1500) - kilometer(1)   // → meter(500)       [LHS type: meter]
kilometer(2) - meter(500)    // → kilometer(1.5)   [LHS type: kilometer]
```

**Rationale**:
- **Predictable return type**: Return type is always determined by LHS operand type
- **User intent preservation**: The programmer's choice of LHS unit is honored in the result
- **Intuitive arithmetic**: Matches mathematical expectations (left-hand side "wins")
- **Eliminates design inconsistency**: Previously, same-ratio operations returned input type, but different-ratio operations returned canonical type—creating unpredictable behavior

**Design Alternatives Considered**:

1. **Option 1 - Always Canonical**: Return canonical SI unit (`meter`, `kilogram`, etc.)
   - ✓ Normalizes all results
   - ✗ Loses user's original unit choice
   - ✗ Unexpected for users coming from physics libraries

2. **Option 2 - LHS Type (Selected)**: Return LHS operand type
   - ✓ Predictable and intuitive
   - ✓ Honors user intent
   - ✓ Consistent across same-ratio and different-ratio cases
   - ✗ May return non-standard SI units

3. **Option 3 - Document the Behavior**: Keep mixed behavior, document clearly
   - ✓ Minimal code changes
   - ✗ Confusing and error-prone for users
   - ✗ Violates principle of least surprise

**Optimization**: When both operands have **identical ratios**, the operation is optimized:
```cpp
// Optimized path: both are kilometers (ratio<1000,1>)
kilometer(5) + kilometer(3)  // → kilometer(8)
// No conversion to canonical needed, just add values directly
```

When ratios differ:
```cpp
// Non-optimized path: meter (ratio<1,1>) + kilometer (ratio<1000,1>)
meter(500) + kilometer(1)
// 1. Convert both to canonical: 500m + 1000m = 1500m
// 2. Convert result back to LHS ratio: 1500m → 1500 meters
// 3. Return: meter(1500)
```

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

### 3.5 Arithmetic Helper Functions and Compile-Time Optimizations

**Decision**: Factor arithmetic into standalone functions templated **only on value type and ratios**, not on unit types, with compile-time optimization for special cases:

```cpp
// Optimized for identical ratios at compile-time
template<typename type_t, typename ratio_t1, typename ratio_t2>
constexpr type_t add_canonical(type_t val1, type_t val2) noexcept
{
    if constexpr (std::is_same_v<ratio_t1, ratio_t2>)
    {
        // Same ratio: no conversion needed
        return val1 + val2;
    }
    else
    {
        // Different ratios: convert to canonical, add, convert back
        type_t canonical1 = convert_ratio_to<type_t, ratio_t1, std::ratio<1, 1>>(val1);
        type_t canonical2 = convert_ratio_to<type_t, ratio_t2, std::ratio<1, 1>>(val2);
        return canonical1 + canonical2;
    }
}

template<typename type_t>
constexpr type_t multiply_values(type_t val1, type_t val2) noexcept;
```

**Optimization Details**:

1. **Ratio Identity Detection (Multiply/Divide)**:
   ```cpp
   // When either operand has ratio<1,1>, avoid std::ratio_multiply/divide
   std::conditional_t<std::is_same_v<ratio1, std::ratio<1, 1>>, 
                      ratio2,    // Identity: 1 * X = X
                      std::conditional_t<std::is_same_v<ratio2, std::ratio<1, 1>>,
                                         ratio1,  // Identity: X * 1 = X
                                         std::ratio_multiply<ratio1, ratio2>>>
   ```

2. **Same-Ratio Fast Path (Add/Subtract)**:
   ```cpp
   if constexpr (std::is_same_v<ratio_t1, ratio_t2>)
       return val1 + val2;  // Skip all conversions
   ```

**Rationale**:
- **Smaller binary size**: The actual arithmetic is instantiated once per value type (e.g., one for `double`), 
  not once per unit-type pair (could be thousands of instantiations)
- **Better compile-time optimization**: Using `if constexpr` allows the compiler to eliminate unused branches entirely
- **Zero runtime overhead**: Optimized paths compile to identical machine code as if written directly
- **Cleaner separation of concerns**: Type checking in operators, computation in helpers
- **Easier to profile/optimize**: Arithmetic logic is isolated and simple

**Design Trade-off**:
```
// Without factoring: 
operator+(meter, kilometer) → specialized implementation
operator+(meter, millimeter) → another specialized implementation
// ... one instantiation per unit pair

// With factoring and optimization:
operator+(meter, kilometer) → delegates to add_canonical<double, ratio<1,1>, ratio<1000,1>>
operator+(meter, millimeter) → delegates to add_canonical<double, ratio<1,1>, ratio<1,1000>>
// ... one add_canonical per value type, shared across all unit pairs
// ... same-ratio branch compiled away for identical ratio cases
```

**Compile-Time Decision Tree** (Demonstrated in Tests):
- **Addition/Subtraction**: If both operands have identical ratios → skip conversion; else → convert to canonical, operate, convert back to LHS ratio
- **Multiplication**: If either operand has ratio<1,1> → use the other ratio directly; else → call std::ratio_multiply
- **Division**: If both operands have same ratio → result ratio is <1,1>; if denominator is <1,1> → result ratio is numerator ratio; else → call std::ratio_divide

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

## 8. Imperial and Non-SI Units: Design Philosophy

### 8.1 SI-First Architecture

**Decision**: SI (Système International d'Unités) units are the default and primary focus. Imperial and non-SI units are **deliberately excluded from the default includes** to encourage SI-based business logic.

**Rationale**:
- **SI as the standard**: The library enforces SI as the canonical system for scientific and engineering calculations
- **Conscious choice required**: Using imperial units requires explicit inclusion (`#include <pkr_units/imperial.h>`) or (`#include <pkr_units/imperial_literals.h>`), making it a deliberate decision
- **Prevents accidental mixing**: Developers cannot accidentally mix SI and imperial units without conscious intent
- **Promotes best practices**: Business logic and scientific calculations should use SI; imperial/custom units belong in UI/presentation layers only

### 8.2 When to Use Imperial Units

**Appropriate use cases** (UI and presentation layer only):
```cpp
// ✓ GOOD: Display layer converting SI to imperial for user interface
double km = distance_in_meters.value() / 1000.0;
double miles = km * 0.621371;  // Convert to miles for display
ui::display_distance(miles);  // Show in miles to user

// ✓ GOOD: Input conversion - user enters imperial, convert to SI
double user_input_pounds = get_user_weight_input();
si::kilogram weight{user_input_pounds * 0.453592};  // Convert to kg
calculate_force(weight);  // Use SI internally
```

**Inappropriate use cases** (business logic should always use SI):
```cpp
// ✗ BAD: Using imperial in calculations
si::imperial::pound weight{150.0};
calculate_nutritional_requirements(weight);  // Wrong: use kg instead

// ✗ BAD: Mixing SI and imperial in business logic
auto speed_mph = 60.0;
auto distance_km = 100.0;
auto time = distance_km / (speed_mph * 1.60934);  // Confusing and error-prone
```

### 8.3 Include Organization

**Default (SI-focused)**:
```cpp
#include <pkr_units/si.h>                    // All 7 SI base units + casting
#include <pkr_units/si_literals.h>           // SI unit literal operators
```

**With Imperial Support**:
```cpp
#include <pkr_units/si.h>                    // SI units
#include <pkr_units/imperial.h>              // Imperial units (conscious choice)
#include <pkr_units/imperial_literals.h>     // Imperial literal operators
```

**The barrier to entry** (explicit include requirement) serves as a visual reminder that you're leaving the SI standard and entering a domain that may have compatibility issues or ambiguity.

### 8.4 Design Trade-off

| Aspect | Benefit | Cost |
|--------|---------|------|
| Imperial excluded by default | Encourages SI usage, prevents accidents | Requires extra include for imperial |
| Explicit inclusion required | Clear intent, auditable in code review | Slightly more typing |
| Separate literal headers | Modular, can choose features à la carte | More headers to manage |
| SI as primary standard | Standards compliance, scientific rigor | Less convenient for legacy systems |

---

## 9. Summary of Trade-offs

| Decision | Benefits | Trade-offs |
|----------|----------|-----------|
| Template specialization for dimension mapping | Faster compilation, extensibility | More boilerplate code |
| LHS-type returns for addition/subtraction | Intuitive, predictable, honors user intent | May return non-canonical units |
| Compile-time ratio optimization | Zero runtime overhead, smaller binaries | Slightly more complex implementation |
| Dimension matching only | Type safety | Cannot combine different physical quantities |
| Arithmetic factoring | Smaller binaries, better optimization | Additional indirection layer |
| Strong types via inheritance | Type safety, readability | Requires explicit strong type declarations |
| SI-first, imperial opt-in | Encourages best practices, prevents mistakes | Requires conscious choice for imperial |

---

## References

- [C++20 Concepts](https://en.cppreference.com/w/cpp/language/constraints)
- [std::ratio](https://en.cppreference.com/w/cpp/numeric/ratio)
- [Template Specialization](https://en.cppreference.com/w/cpp/language/template_specialization)
- [SI System](https://www.bipm.org/en/measurement-units/si-system)

