# Matrix Storage Policies Guide

## Overview

Matrix storage policies provide flexible memory allocation strategies for `matrix_4d_units_t` and `matrix_measurement_rss_4d_t` classes. This is essential for embedded systems with limited stack space while maintaining backward compatibility with existing code.

## Quick Start

### Default Usage (Stack Storage)
```cpp
#include <pkr_units/pkr_units.h>
using pkr::units::matrix_4d_units_t, pkr::units::meter_t;

// Uses stack storage (default, zero overhead)
matrix_4d_units_t<meter_t> m1;
auto result = m1 * m1;
```

### Embedded Systems (Arena Storage)
```cpp
// Use pre-allocated arena for matrices
using MatrixWithArena = matrix_4d_units_t<meter_t, 
                                          arena_storage<meter_t, 10>>;

MatrixWithArena m1;
// Falls back to stack gracefully if pool exhausted
```

## Storage Policies

### `stack_storage<T>` (Default)

**Purpose**: Direct allocation of 128-byte 4×4 array on the stack.

**Characteristics**:
- Zero runtime overhead
- Backward compatible (default template parameter)
- 128 bytes per instance
- Suitable for normal use cases

**Usage**:
```cpp
// Explicit (rarely needed)
matrix_4d_units_t<meter_t, stack_storage<meter_t>> m;

// Implicit (recommended)
matrix_4d_units_t<meter_t> m;  // Uses stack_storage by default
```

**Memory Profile**:
- Static: 0 bytes
- Per instance: 128 bytes on stack
- Per allocation: O(1) time, no heap allocation

### `arena_storage<T, POOL_SIZE, ExhaustedPolicy>` (Embedded)

**Purpose**: Pre-allocate a fixed pool of matrices with graceful fallback to stack.

**Template Parameters**:
- `T`: Value type (element of the matrix)
- `POOL_SIZE`: Number of matrices in pool (default: 10)
- `ExhaustedPolicy`: Callback when pool exhausted (default: silent)

**Characteristics**:
- Fixed-size pool (deterministic)
- Automatic fallback to stack
- RAII allocation/deallocation
- Move-aware, copy-disabled
- Thread-unsafe (acceptable for embedded systems)
- Monitoring hooks for tuning

**Basic Usage**:
```cpp
using MatrixWithArena = matrix_4d_units_t<meter_t,
                                          arena_storage<meter_t, 10>>;

MatrixWithArena m1;  // Allocates from pool
MatrixWithArena m2;  // Allocates from pool
// ...
MatrixWithArena m11; // Falls back to stack
```

**Memory Profile**:
- Static: 10 × 128 bytes = 1,280 bytes (pool)
- Per instance: 128 bytes fallback on stack (if needed)
- Per allocation: O(1) time, O(POOL_SIZE) worst-case search

**Monitoring Methods**:
```cpp
using ArenaType = arena_storage<meter_t, 10>;

// Current usage
size_t active = ArenaType::active_slots();    // Currently allocated slots

// Peak statistics
size_t peak = ArenaType::get_peak_usage();    // Max simultaneous allocations
size_t fallbacks = ArenaType::get_fallback_count();

// Reset for testing
ArenaType::reset_statistics();
```

## Custom Exhaustion Policies

Handle arena exhaustion with custom behavior:

### Silent Fallback (Default)
```cpp
struct default_arena_policy {
    static void on_exhausted() { /* silent */ }
};

using Matrix = matrix_4d_units_t<meter_t, arena_storage<meter_t, 10>>;
```

### Warning Policy
```cpp
struct warning_policy {
    static void on_exhausted() {
        std::cerr << "Matrix arena exhausted, falling back to stack\n";
    }
};

using Matrix = matrix_4d_units_t<meter_t, 
                                 arena_storage<meter_t, 10, warning_policy>>;
```

### Error Policy
```cpp
struct error_policy {
    static void on_exhausted() {
        throw std::runtime_error("Matrix arena exhausted");
    }
};

using Matrix = matrix_4d_units_t<meter_t, 
                                 arena_storage<meter_t, 10, error_policy>>;
```

### Logging Policy
```cpp
struct logging_policy {
    static inline int exhaustion_count = 0;
    
    static void on_exhausted() {
        log_warning("Arena exhaustion #%d", ++exhaustion_count);
    }
};
```

## Embedded Systems Workflow

### Phase 1: Profiling

Profile to find your actual peak allocation:

```cpp
void profile_application() {
    using MatrixProfile = matrix_4d_units_t<meter_t,
                                            arena_storage<meter_t, 20>>;
    
    arena_storage<meter_t, 20>::reset_statistics();
    
    // Run representative workloads
    run_algorithm_1();
    run_algorithm_2();
    run_algorithm_3();
    
    // Analyze results
    size_t peak = arena_storage<meter_t, 20>::get_peak_usage();
    size_t fallbacks = arena_storage<meter_t, 20>::get_fallback_count();
    
    printf("Peak simultaneous matrices: %zu\n", peak);
    printf("Fallback events: %zu\n", fallbacks);
    printf("Recommended POOL_SIZE: %zu\n", peak + 1);
}
```

### Phase 2: Tuning

Set `POOL_SIZE` based on profiling results:

```cpp
// Based on profiling, peak was 7 simultaneous matrices
// Set POOL_SIZE to peak + 1 for safety buffer
using OptimizedMatrix = matrix_4d_units_t<meter_t,
                                          arena_storage<meter_t, 8>>;
```

### Phase 3: Production

Run with optimized settings:

```cpp
using ProductionMatrix = matrix_4d_units_t<meter_t,
                                           arena_storage<meter_t, 8>>;

// No need for monitoring in production
// Falls back to stack gracefully if needed
// Predictable memory usage
```

## Memory Calculations

### Stack allocation with stack storage:
```
Total stack per matrix = 128 bytes (4×4 × double)
```

### Stack allocation with arena storage:
```
Pool static allocation = POOL_SIZE × 128 bytes
Fallback per instance = 128 bytes (if needed)
Max total stack = POOL_SIZE × 128 + 128 × (concurrent_fallbacks)
```

### Example: ARM Cortex-M4 with 16 KB stack
```cpp
// Without arena:
// Each matrix = 128 bytes
// 128 matrices would use entire stack

// With arena:
using Matrix = matrix_4d_units_t<meter_t, arena_storage<meter_t, 50>>;
// Pool = 6.4 KB
// Leaves 9.6 KB for algorithm code and other allocations
```

## Design Patterns

### Pattern 1: Type Alias for Consumer Code
```cpp
// In library header
namespace mylib {
    using Matrix3D = matrix_4d_units_t<meter_t, arena_storage<meter_t, 10>>;
}

// In user code
using namespace mylib;
Matrix3D m1, m2;
```

### Pattern 2: Compile-Time Configuration
```cpp
// In build configuration header
#define MATRIX_POOL_SIZE 8

// In library
template <typename T>
using EmbeddedMatrix = matrix_4d_units_t<T, arena_storage<T, MATRIX_POOL_SIZE>>;
```

### Pattern 3: Conditional Based on Platform
```cpp
#ifdef EMBEDDED_SYSTEM
    template <typename T>
    using OptimizedMatrix = matrix_4d_units_t<T, arena_storage<T, 10>>;
#else
    template <typename T>
    using OptimizedMatrix = matrix_4d_units_t<T>;  // Default stack
#endif
```

## Troubleshooting

### Issue: Frequent fallback warnings
**Symptom**: `fallback_count` keeps increasing

**Solution**:
1. Increase `POOL_SIZE` in arena_storage template
2. Rerun profiling to find actual peak
3. Check for unintended matrix allocations in hot paths

### Issue: Stack overflow
**Symptom**: Program crashes with no fallback warnings

**Possible causes**:
- `POOL_SIZE` too large (consuming stack)
- Fallback happening but not visible (no policy)
- Other stack consumers in algorithm

**Solution**:
1. Add warning policy to detect fallbacks
2. Profile other parts of algorithm
3. Consider reducing POOL_SIZE or profile with larger pool

### Issue: Out of memory
**Symptom**: Arena exhaustion with fallback

**Solution**:
- This is designed behavior (graceful fallback)
- Increase `POOL_SIZE` if stack allows
- Or restructure algorithm to reduce concurrent matrices

## Measurements with Arena Storage

When using `matrix_measurement_rss_4d_t`, the storage policy applies to the measurement type:

```cpp
// StoragePolicy is for measurement_rss_t<T>, not T
using MeasurementMatrix = matrix_measurement_rss_4d_t<meter_t,
                              arena_storage<measurement_rss_t<meter_t>, 5>>;

auto m = measurement_rss_t<meter_t>{5_m, 0.1_m};
MeasurementMatrix mat;
mat(0, 0) = m;
```

## Performance Characteristics

| Operation | Stack Storage | Arena (available) | Arena (fallback) |
|-----------|----------------|-------------------|-----------------|
| Allocation | O(1) | O(POOL_SIZE) | O(1) |
| Access | O(1) | O(1) | O(1) |
| Deallocation | O(1) | O(1) | O(1) |
| Memory fragmentation | None | None | None |
| 4×4 multiply | No difference | No difference | No difference |

**Note**: Arena allocation worst-case is O(POOL_SIZE) because it scans for free slots. Use bitset scan for faster allocation in performance-critical code if needed.

## Backward Compatibility

**Fully backward compatible**

Existing code without storage policy template parameter continues to work:
```cpp
// Old code still works (uses stack_storage by default)
matrix_4d_units_t<meter_t> m1;
matrix_measurement_rss_4d_t<meter_t> m2;
```

## Best Practices

1. **Start with default**: Use stack storage unless profiling shows problems
2. **Profile first**: Measure actual peak usage before optimizing
3. **Add safety margin**: Set `POOL_SIZE = peak_usage + 1`
4. **Monitor in tuning**: Use custom policy during development
5. **Silent in production**: Use default policy when stable
6. **Document assumptions**: Note POOL_SIZE tuning in comments
7. **Test edge cases**: Verify fallback behavior under stress

## FAQ

**Q: Does arena storage add overhead to normal operations?**
A: No. Storage access is O(1) with no loops in hot path.

**Q: Is arena storage thread-safe?**
A: No. It uses unsynchronized static variables. For multi-threaded systems, use stack storage or add your own synchronization.

**Q: Can I change POOL_SIZE at runtime?**
A: No. Pool size is compile-time constant for predictability in embedded systems.

**Q: What happens if I forget to reset_statistics()?**
A: Peak usage and fallback count persist across test runs. Reset before each test.

**Q: Can I use arena storage for other types?**
A: The pattern is generic. You can create `arena_storage<YourType, 10>` for any type.

## References

- Matrix Storage Policies: `sdk/include/pkr_units/units/math/matrix_storage_policies.h`
- Matrix Unit 4D: `sdk/include/pkr_units/units/math/matrix_unit_4d.h`
- Matrix Measurement RSS 4D: `sdk/include/pkr_units/measurements/math/matrix_measurement_rss_4d.h`
- Example Code: `examples/matrix_storage_policies_example.cpp`
- Unit Tests: `tests/storage_policies/test_matrix_storage_policies.cpp`
