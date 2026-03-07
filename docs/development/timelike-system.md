# Timelike Concept Design

Flexible timestamp representation in temporal measurement systems.

## Overview

The `timelike` concept abstracts timestamp types, enabling the time series system to work with:
- Standard chrono timestamps (`std::chrono::time_point`)
- Unit-based time (`second_t`)
- Measurements with uncertainty (`measurement_lin_t<second_t>`)

## The Timelike Concept

```cpp
template<typename T>
concept timelike = 
    std::regular<T> &&
    requires(T a, T b) {
        { a < b } -> std::convertible_to<bool>;
        // Specialization defines operations on T
    };
```

Each timelike type has a specialization providing:
- Ordering operations (`<`, `>`, `==`)
- Interval calculation (`end - start`)
- Default/current values

## Built-in Specializations

### Chrono Timestamps

**Type:** `std::chrono::high_resolution_clock::time_point`

```cpp
template<>
struct timelike_traits<std::chrono::high_resolution_clock::time_point> {
    using duration = std::chrono::high_resolution_clock::duration;
    
    static auto now() { 
        return std::chrono::high_resolution_clock::now(); 
    }
    
    static duration interval(time_point a, time_point b) {
        return b - a;
    }
};
```

**Use case:** General-purpose timestamp tracking, system time

### Unit-Based Time

**Type:** `second_t` (or any time unit)

```cpp
template<>
struct timelike_traits<second_t> {
    using duration = second_t;
    
    static second_t now() { 
        return /* system time converted to second_t */; 
    }
    
    static second_t interval(second_t a, second_t b) {
        return b - a;
    }
};
```

**Use case:** Unit-aware temporal analysis, dimensional consistency

### Measurement-Based Time

**Type:** `measurement_lin_t<second_t>`

```cpp
template<>
struct timelike_traits<measurement_lin_t<second_t>> {
    using duration = measurement_lin_t<second_t>;
    
    static auto now() { 
        return measurement_lin_t<second_t>(current_time, uncertainty); 
    }
    
    static auto interval(measurement_lin_t<second_t> a, 
                         measurement_lin_t<second_t> b) {
        return b - a;  // Uncertainty propagated automatically
    }
};
```

**Use case:** Experimental data with timestamp uncertainty

## Usage

### Default Chrono Timestamps

```cpp
quantity_series<meter_t> series;
series.add_now(100_m);  // Uses current time
series.add_at(time_point, 100_m);
```

### Custom Timelike Type

```cpp
using unit_time_series = quantity_series<
    meter_t,
    std::pmr::polymorphic_allocator<>,
    second_t  // Custom timelike
>;

unit_time_series series;
series.add_at(10_s, 100_m);

// Intervals are automatically second_t
auto t = series.at(1).first - series.at(0).first;  // second_t
```

## Design Rationale

### Why a Concept?

**Chosen:**
- ✓ Works with any type meeting requirements
- ✓ Extensible without library modification
- ✓ Type-safe and compile-time verified

**Alternative (inheritance):**
- ✗ Forces base class inheritance
- ✗ Less flexible, more boilerplate

### Why Specialization Pattern?

Different timelike types need different behaviors:
- Chrono: system calls, real-time precision
- Unit-based: unit conversions
- Measurement: uncertainty propagation

A specialization trait provides customization without requiring virtual functions.

---

## See Also

- [Time Series Design](./time-series.md) — Uses timelike for series timestamps
- [Architecture Deep Dive](./architecture-deep-dive.md) — Trait-based design patterns

