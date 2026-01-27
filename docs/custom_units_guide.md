# Creating Custom Units - User Guide

This guide shows how to extend the SI units library with your own custom unit types. The system is designed to be extensible using C++20 template specialization.

## Overview

The SI units library provides a framework where you can:
1. Define custom dimensions (if needed)
2. Create custom unit types with specific ratios
3. Register them with the `derived_unit_type_t` pattern for automatic type deduction
4. Use them with all standard operators and dimensional analysis

## Basic Example: Custom Angular Velocity

Let's create a custom header file for angular velocity units that aren't in the standard library.

### Step 1: Create Your Header File

```cpp
// my_custom_units/angular_velocity.h

#pragma once

#include <pkr_units/units.h>

namespace PKR_UNITS_NAMESPACE
{

// Define the dimension for angular velocity (radians per second)
// Using existing time_dimension and creating a custom ratio
inline constexpr dimension_t angular_velocity_dimension{0, 0, -1, 0, 0, 0, 0, 1};  // Θ·T⁻¹ (angle/time)

// Radians per second (SI base for angular velocity)
struct radians_per_second_t final : public details::unit_t<double, std::ratio<1, 1>, angular_velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, angular_velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"radians per second"};
    static constexpr std::string_view symbol{"rad/s"};
    static constexpr std::wstring_view w_symbol{L"rad/s"};
    static constexpr std::u8string_view u8_symbol{u8"rad/s"};
};

// Revolutions per minute
struct rpm_t final : public details::unit_t<double, std::ratio<628318530, 60000000000>, angular_velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<628318530, 60000000000>, angular_velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"revolutions per minute"};
    static constexpr std::string_view symbol{"rpm"};
    static constexpr std::wstring_view w_symbol{L"rpm"};
    static constexpr std::u8string_view u8_symbol{u8"rpm"};
};

// Degrees per second
struct degrees_per_second_t final : public details::unit_t<double, std::ratio<1745329, 100000000>, angular_velocity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1745329, 100000000>, angular_velocity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"degrees per second"};
    static constexpr std::string_view symbol{"°/s"};
    static constexpr std::wstring_view w_symbol{L"°/s"};
    static constexpr std::u8string_view u8_symbol{u8"°/s"};
};

// ============================================================================
// Most derived unit type specializations - CRITICAL STEP
// ============================================================================

template<>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, angular_velocity_dimension>
{
    using type = radians_per_second_t;
};

template<>
struct details::derived_unit_type_t<double, std::ratio<628318530, 60000000000>, angular_velocity_dimension>
{
    using type = rpm_t;
};

template<>
struct details::derived_unit_type_t<double, std::ratio<1745329, 100000000>, angular_velocity_dimension>
{
    using type = degrees_per_second_t;
};

}  // namespace PKR_UNITS_NAMESPACE
```

### Step 2: Use Your Custom Units

```cpp
#include "my_custom_units/angular_velocity.h"

int main()
{
    using namespace pkr::units;
    
    // Create custom units
    auto motor_speed = rpm_t(3000.0);           // 3000 RPM
    auto converted = radians_per_second_t(motor_speed.count() * 2 * M_PI / 60);
    
    // Use with operators - returns correct derived type!
    auto doubled = motor_speed * 2.0;           // Still rpm_t, not base unit_t
    auto halved = motor_speed / 2.0;            // Still rpm_t
    
    return 0;
}
```

## Key Points

### 1. **Dimension Definition**

Each custom unit family needs a dimension that describes its properties:

```cpp
inline constexpr dimension_t my_dimension{
    .mass = 0,
    .length = 0,
    .time = -1,        // T⁻¹
    .current = 0,
    .temperature = 0,
    .amount = 0,
    .intensity = 0,
    .angle = 0
};
```

The dimension ensures dimensional analysis works correctly:
- Multiplying two velocities (L·T⁻¹ × L·T⁻¹) produces area per time squared
- The system verifies you can't add velocity to acceleration
- Compiler catches unit mismatches at compile-time

### 2. **Unit Type Definition**

Each specific unit needs:

```cpp
struct my_unit_t final : public details::unit_t<double, std::ratio<num, denom>, my_dimension>
{
    using _base = details::unit_t<double, std::ratio<num, denom>, my_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"full name"};
    static constexpr std::string_view symbol{"symbol"};
    static constexpr std::wstring_view w_symbol{L"symbol"};
    static constexpr std::u8string_view u8_symbol{u8"symbol"};
};
```

The `std::ratio<num, denom>` represents the conversion factor to SI base units.

### 3. **The derived_unit_type_t Specialization (CRITICAL!)**

This is what enables automatic type deduction in scalar operations:

```cpp
template<>
struct details::derived_unit_type_t<double, std::ratio<num, denom>, my_dimension>
{
    using type = my_unit_t;
};
```

**Without this specialization:**
- `motor_speed * 2.0` returns generic `unit_t<double, std::ratio<...>, my_dimension>`
- You lose type safety and must cast back to `rpm_t`

**With this specialization:**
- `motor_speed * 2.0` automatically returns `rpm_t`
- Type deduction works seamlessly
- All operators preserve the specific unit type

## Ratios: Converting to SI Base

The `std::ratio` in each unit type represents conversion to the SI base unit.

**Examples:**

```cpp
// kilometer_t has ratio<1000, 1> because 1 km = 1000 m
struct kilometer_t : public unit_t<double, std::ratio<1000, 1>, length_dimension>

// rpm_t: 1 rpm = (2π/60) rad/s ≈ 0.10472 rad/s
// Ratio: 628318530/60000000000 (scaled to avoid floating point)
struct rpm_t : public unit_t<double, std::ratio<628318530, 60000000000>, angular_velocity_dimension>

// celsius_per_second (if your temperature rate unit): 
// 1 °C/s = 1 K/s (Celsius and Kelvin differences are identical)
struct celsius_per_second_t : public unit_t<double, std::ratio<1, 1>, temperature_rate_dimension>
```

## Best Practices

1. **Always include the specialization** - It enables the most ergonomic API
2. **Use precise ratios** - Avoid floating point; use `std::ratio` with exact integer fractions
3. **Document the dimension** - Comment which SI base units make up your dimension
4. **Provide symbols** - Users will appreciate having proper unit symbols in output
5. **Follow naming convention** - `my_unit_t` for the type, with `_t` suffix
6. **Group related units** - Keep all variants of one dimension in the same header

## Advanced: Multiple Value Types

The system supports custom value types beyond `double`:

```cpp
// Using float instead of double
struct rpm_float_t final : public details::unit_t<float, std::ratio<628318530, 60000000000>, angular_velocity_dimension>
{
    using _base = details::unit_t<float, std::ratio<628318530, 60000000000>, angular_velocity_dimension>;
    using _base::_base;
    // ...
};

// You'd still need specialization
template<>
struct details::derived_unit_type_t<float, std::ratio<628318530, 60000000000>, angular_velocity_dimension>
{
    using type = rpm_float_t;
};
```

## Testing Your Custom Units

```cpp
#include <cassert>
#include "my_custom_units/angular_velocity.h"

int main()
{
    using namespace pkr::units;
    
    // Test type preservation
    auto x = rpm_t(3000.0);
    auto result = x * 2.0;
    
    // Verify the type is preserved
    static_assert(std::is_same_v<decltype(result), rpm_t>, 
                  "Scalar multiplication should preserve type");
    
    assert(result.count() == 6000.0);
    
    return 0;
}
```

## Common Pitfalls

**❌ Forgetting the derived_unit_type_t specialization**
- Scalar operations will return base `unit_t` type
- Type information is lost
- Can't compose operations effectively

**❌ Using incorrect ratio**
- If ratio is wrong, conversions will be wrong
- Hard to debug because types still match
- Always verify with known conversions

**❌ Misaligned dimensions**
- Check that your dimension vector matches what the unit represents
- `length = 0, time = -1` is velocity (NO!) - should be `length = 1, time = -1`

**❌ Not including full unit_t constructor**
- `using _base::_base;` is essential - it delegates to the base constructor
- Without it, your type won't construct

## Summary

Custom units are just:
1. A dimension (what it measures)
2. A unit type inheriting from `unit_t` (the specific variant)
3. A `derived_unit_type_t` specialization (for type deduction)
4. Repeat for each variant of that dimension

That's it! The entire operator system, dimensional analysis, and type safety come for free from the base framework.
