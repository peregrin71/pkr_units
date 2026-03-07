# Time Series Design & Implementation

Design and architecture of temporal measurement systems in pkr_units.

## Overview

The time series subsystem provides type-safe storage and analysis of quantities measured over time, with automatic uncertainty propagation and temporal operations (interpolation, resampling, derivatives).

**Key components:**
- `quantity_series<Quantity, Allocator>` — Temporal sequence of unit quantities
- `measurement_series<Quantity, Allocator>` — Temporal sequence with uncertainty
- `timelike` concept — Flexible timestamp representation

## Memory Model

### Why std::pmr::deque?

`std::pmr::deque` provides zero-reallocation growth, unlike `std::vector`:
- Each growth allocates a new node (constant time)
- Existing elements never move (stable references)
- Single large allocation possible via `monotonic_buffer_resource`

### Storage Strategies

**Default PMR (runtime allocation):**
```cpp
quantity_series<meter_t> series;
```

**Arena (pre-allocated buffer):**
```cpp
std::array<std::byte, 1_MB> buffer;
std::pmr::monotonic_buffer_resource resource(buffer.data(), buffer.size());
std::pmr::polymorphic_allocator<std::byte> alloc(&resource);
quantity_series<meter_t, decltype(alloc)> series(alloc);
```

**Pool (fixed-size pre-allocation):**
```cpp
std::pmr::pool_resource pool;
std::pmr::polymorphic_allocator<std::byte> alloc(&pool);
quantity_series<meter_t, decltype(alloc)> series(alloc);
```

## Timestamp System: The Timelike Concept

### Problem Statement

Standard `std::chrono::time_point` works well for C++ but doesn't integrate with the unit system:
- Cannot apply dimensional analysis to intervals
- No support for uncertain timestamps
- Chrono and unit-based time don't interoperate smoothly

### Solution: Specializable Timelike Concept

```cpp
template<typename T>
concept timelike = requires(T t) {
    // Specializations for: chrono time_point, unit-based time, measurements
};
```

**Built-in specializations:**

1. **Chrono-based (std::chrono::time_point)**
   - High-precision, certain timestamps
   - Natural for system time, elapsed measurement

2. **Unit-based (e.g., `second_t`)**
   - Unit-aware timestamps
   - Enables dimensional analysis on time intervals

3. **Measurement-based (e.g., `measurement_lin_t<second_t>`)**
   - Uncertain timestamps
   - For experimental/noisy time data

### Example

```cpp
// Chrono timestamps (default)
quantity_series<meter_t> distance_vs_time;
distance_vs_time.add_now(100_m);

// Unit-based timestamps
using unit_time_series = quantity_series<
    meter_t,
    std::pmr::polymorphic_allocator<std::byte>,
    second_t  // Custom timelike type
>;
unit_time_series series;
series.add_at(10_s, 100_m);

// Uncertain timestamps
using uncertain_time_series = quantity_series<
    meter_t,
    std::pmr::polymorphic_allocator<std::byte>,
    measurement_lin_t<second_t>
>;
uncertain_time_series noisy_series;
noisy_series.add_at(measurement_lin_t<second_t>(10_s, 0.1_s), 100_m);
```

## API Overview

### Core Operations

```cpp
template<typename Quantity, typename Allocator, typename TimeType>
class quantity_series {
    // Construction
    quantity_series();
    explicit quantity_series(const Allocator& alloc);
    
    // Add measurements
    void add_at(TimeType t, const Quantity& value);
    void add_now(const Quantity& value);  // Uses current time
    
    // Access
    const Quantity& operator[](size_t index) const;
    std::pair<TimeType, Quantity> at(size_t index) const;
    
    // Properties
    size_t size() const;
    bool empty() const;
    
    // Temporal operations
    Quantity interpolate_at(TimeType t) const;
    quantity_series resample(duration interval) const;
    auto time_derivative() const;  // Series<dQ/dt>
    
    // Statistics
    Quantity mean() const;
    Quantity std_dev() const;
    Quantity min() const;
    Quantity max() const;
    
    // Filtering
    quantity_series filter(
        std::function<bool(const Quantity&)> pred) const;
    quantity_series smooth(size_t window_size) const;
    quantity_series decimate(size_t ratio) const;
};
```

### Measurement Series

`measurement_series<Quantity>` extends `quantity_series` with uncertainty propagation:

```cpp
class measurement_series : public quantity_series<measurement<Quantity>> {
    // Uncertainty-aware statistics
    measurement<Quantity> mean() const;      // Propagated uncertainty
    measurement<Quantity> std_dev() const;
    
    // Uncertainty bounds
    std::pair<Quantity, Quantity> 
        uncertainty_bounds() const;
};
```

## Time Derivatives

The `time_derivative()` method correctly applies dimensional analysis:

```cpp
// Input: series of positions [length]
quantity_series<meter_t> positions;

// Output: series of velocities [length / time]
quantity_series<meter_per_second_t> velocities = positions.time_derivative();
```

Computed via finite differences (backward for first point, forward for last, central for interior).

## Design Trade-offs

### Deque vs. Vector

**Deque (chosen):**
- ✓ No reallocation on growth
- ✓ Stable references to existing elements
- ✗ Slightly more complex memory layout
- ✗ Cache locality worse than vector

**Vector (not chosen):**
- ✓ Better cache locality
- ✗ Reallocation invalidates references
- ✗ Must predict capacity in advance

**Trade-off:** Stability and consistency over micro-optimization.

### Polymorphic Allocator

**Chosen:**
- ✓ Flexibility: arena, pool, or default allocation
- ✓ Zero-cost using type specialization
- ✗ Adds template parameter complexity

**Rationale:** Users can choose memory strategy without library changes.

---

## See Also

- [Timelike System](./timelike-system.md) — Detailed timelike concept design
- [Storage Policies](./storage-policies.md) — General storage strategy patterns
- [Architecture Deep Dive](./architecture-deep-dive.md) — Core system design

