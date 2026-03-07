# Storage Policies Design

Memory management and storage strategy patterns in pkr_units.

## Overview

Matrices and series use pluggable storage policies to support different allocation strategies while maintaining zero-cost abstractions.

## The Policy Pattern

Storage is decoupled from the container via a template parameter:

```cpp
template<typename ValueType, typename StoragePolicy>
class matrix_3d_t {
    StoragePolicy storage_;
    // ...
};
```

**Benefits:**
- User chooses memory strategy at type creation
- Cost is compile-time; no runtime overhead
- Components can use different policies in same application
- Strategies can be combined (e.g., arena + pool)

## Built-in Strategies

### Stack Storage (Default)

```cpp
template<typename ValueType>
class stack_storage_3d {
    std::array<ValueType, 3*3*3> data;  // Fixed 3×3×3 on stack
};
```

**Characteristics:**
- ✓ Ultra-fast allocation (zero heap allocation)
- ✓ Cache-friendly
- ✗ Limited to compile-time size
- ✗ Large matrices can overflow stack

**Use case:** Small matrices, tight loops, embedded systems

### Arena Storage

```cpp
template<typename ValueType>
class arena_storage_3d {
    std::span<ValueType> data;  // Pointer to user-managed buffer
};
```

**Characteristics:**
- ✓ Single allocation upfront
- ✓ Predictable performance
- ✗ Requires external buffer management
- ✗ "Leaky" until parent resource destroyed

**Use case:** Systems programming, RAII allocators, real-time systems

**Example:**
```cpp
std::array<std::byte, 64_KB> buffer;
std::pmr::monotonic_buffer_resource resource(buffer.data(), buffer.size());

auto matrix = create_matrix_with_arena<meter_t>(resource);
// When resource destroyed, all allocations freed together
```

### Heap Storage (Implicit)

When using allocators, implicit heap allocation occurs:

```cpp
quantity_series<meter_t> series;  // Uses std::pmr::deque (heap-allocated)
```

**Characteristics:**
- ✓ Flexible size
- ✓ Automatic cleanup (RAII)
- ✓ Standard C++ approach
- ✗ Allocation/deallocation cost

**Use case:** General-purpose code, data of variable size

## Storage Specialization for Matrices

### 3D Matrices

```cpp
// Stack (9 elements)
matrix_3d_t<meter_t, stack_storage_3d<meter_t>>

// Arena (pointer to external buffer)
matrix_3d_t<meter_t, arena_storage_3d<meter_t>>

// Measurement variants
matrix_3d_t<measurement_lin_t<meter_t>, stack_storage_3d<measurement_lin_t<meter_t>>>
```

### 4D Matrices

Same policies, different dimensions (16 elements instead of 9).

## Custom Policy Example

Define your own storage strategy:

```cpp
template<typename ValueType>
class custom_storage_policy {
    // Must implement:
    ValueType& at(size_t x, size_t y, size_t z);
    const ValueType& at(size_t x, size_t y, size_t z) const;
    
    // Called on construction
    void initialize(ValueType initial_value);
};

matrix_3d_t<meter_t, custom_storage_policy<meter_t>> matrix;
```

## Polymorphic Allocator Pattern

For containers (series, deques), use `std::pmr`:

```cpp
// Default PMR (uses default allocator)
quantity_series<meter_t> series1;

// Arena-based allocation
std::array<std::byte, 1_MB> buffer;
std::pmr::monotonic_buffer_resource resource(buffer.data(), buffer.size());
std::pmr::polymorphic_allocator<> alloc(&resource);

quantity_series<meter_t, std::pmr::polymorphic_allocator<>> series2(alloc);
// All allocations come from buffer; freed when resource destroyed
```

## Design Trade-offs

### Fixed Size (Stack) vs. Dynamic (Heap)

**Stack (chosen for matrices):**
- ✓ Predictable performance
- ✓ No allocation cost
- ✗ 3D/4D fixed at compile-time

**Heap (chosen for series):**
- ✓ Flexible size
- ✓ Unbounded growth
- ✗ Allocation cost

**Trade-off:** Different structures use different strategies based on use case.

### Monomorphic vs. Polymorphic

**Monomorphic (stack/arena):**
- ✓ Zero runtime overhead
- ✗ Must know strategy at compile-time

**Polymorphic (PMR):**
- ✓ Choose allocator at runtime
- ✗ Small virtual dispatch cost

**Trade-off:** Matrices use monomorphic (speed), series use polymorphic (flexibility).

---

## See Also

- [Time Series Design](./time-series.md) — Uses storage policies for series
- [Architecture Deep Dive](./architecture-deep-dive.md) — Memory model context

