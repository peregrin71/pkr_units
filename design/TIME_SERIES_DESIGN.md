# Time Series Design

## Overview

Time series support for measuring sequences of quantities and measurements over time. Enables temporal analysis, interpolation, derivatives, and statistical operations while preserving unit type safety and uncertainty propagation.

## File Organization

- `include/si/units/unit_series.h` - `quantity_series<Quantity, Allocator>`
- `include/si/measurements/unit_series.h` - `measurement_series<Quantity, Allocator>`

## Core Design

### Memory Model

Uses `std::pmr::deque` internally with polymorphic allocator support:

**Default (dynamic PMR)**
```cpp
si::quantity_series<si::meters_t> series;
```

**Arena allocation (pre-allocated buffer)**
```cpp
std::array<std::byte, 1_MB> buffer;
std::pmr::monotonic_buffer_resource resource(buffer.data(), buffer.size());
si::quantity_series<si::meters_t, std::pmr::polymorphic_allocator<std::byte>> 
    series(std::pmr::polymorphic_allocator<std::byte>(&resource));
```

**Pool allocation (custom resources)**
```cpp
std::pmr::pool_resource pool;
si::quantity_series<si::meters_t, std::pmr::polymorphic_allocator<std::byte>> 
    series(std::pmr::polymorphic_allocator<std::byte>(&pool));
```

**Benefits:**
- `std::pmr::deque` never reallocates on growth (unlike vector)
- Single allocation with arena strategy
- Flexible allocator for specialized scenarios
- User controls memory lifetime and strategy

### Timestamp Representation

- Uses `std::chrono::high_resolution_clock::time_point` by default
- Configurable via template parameter if needed
- Explicitly provided or implicit via `add_now()`

## API Design

### quantity_series<Quantity, Allocator>

```cpp
template<typename Quantity, 
         typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
class quantity_series {
  // Construction
  explicit quantity_series(const Allocator& alloc = {});
  
  // Add measurements
  template<typename T>
  void add_at(time_point t, T&& val);
  
  template<typename T>
  void add_now(T&& val);
  
  // Access
  const Quantity& operator[](size_t index) const;
  std::pair<time_point, Quantity> at(size_t index) const;
  const Quantity& front() const;
  const Quantity& back() const;
  size_t size() const;
  bool empty() const;
  
  // Iteration
  auto begin() const;
  auto end() const;
  auto cbegin() const;
  auto cend() const;
  
  // Temporal operations
  Quantity interpolate_at(time_point t) const;
  quantity_series<Quantity> resample(duration interval) const;
  auto time_derivative() const;  // Returns series<dQ/dt>
  
  // Statistics
  Quantity mean() const;
  Quantity std_dev() const;
  Quantity min() const;
  Quantity max() const;
  Quantity range() const;  // max - min
  
  // Filtering & transformation
  quantity_series<Quantity> filter(
      std::function<bool(const Quantity&)> predicate) const;
  quantity_series<Quantity> smooth(size_t window_size) const;
  quantity_series<Quantity> decimate(size_t ratio) const;
  quantity_series<Quantity> slice(time_point start, time_point end) const;
  
  // Clearing
  void clear() noexcept;
  void reserve(size_t capacity);
};
```

### measurement_series<Quantity, Allocator>

Inherits all methods from `quantity_series` plus:

```cpp
template<typename Quantity, 
         typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
class measurement_series : public quantity_series<measurement<Quantity>, Allocator> {
  // Measurement-specific operations
  measurement<Quantity> mean() const;  // Returns measurement with propagated uncertainty
  measurement<Quantity> std_dev() const;
  
  // Uncertainty analysis
  std::pair<Quantity, Quantity> uncertainty_bounds() const;  
      // Returns (min_with_uncertainty, max_with_uncertainty)
  
  measurement_series<Quantity> filter(
      std::function<bool(const measurement<Quantity>&)> predicate) const;
  // ... other overloads for measurement types
};
```

## Key Implementation Decisions

### Perfect Forwarding

Both `add_at()` and `add_now()` use perfect forwarding on value:
```cpp
template<typename T>
void add_at(time_point t, T&& val) {
    data.emplace_back(t, std::forward<T>(val));
}
```
Enables in-place construction of payload without unnecessary copies.

### Time Derivatives

`time_derivative()` returns correctly-dimensioned type:
```cpp
// If series contains meters
quantity_series<meters_per_second> derivative = series.time_derivative();
```

Computed via finite differences (backward/forward/central based on context).

### Interpolation Strategy

Linear interpolation by default:
```cpp
Quantity interpolate_at(time_point t) const {
    // Find bracketing points and linear interpolate
}
```

Future: support cubic spline via optional parameter.

### Time Range Operations

`slice()`, `resample()`, and temporal filtering work with explicit time points:
```cpp
auto subset = series.slice(start_time, end_time);
auto resampled = series.resample(100_ms);  // Every 100ms
```

## Testing Strategy

### Unit Tests
- **Type correctness**: Dimension mismatches fail to compile
- **Numeric accuracy**: Interpolation against known functions
- **Edge cases**: Empty series, single point, duplicate timestamps
- **Memory**: No leaks with allocator strategies
- **Uncertainty**: Propagation through operations (measurement_series)

### Integration Tests
- Real sensor data workflows
- Large datasets (>1M points)
- Time-derivative chains (velocity from acceleration)
- Mixed operations (filter → resample → derivative)

## Design Rationale

**Why `std::pmr::deque`?**
- Append-only workload never reallocates
- Iterator/reference stability
- Smooth memory growth vs vector's 2x growth factor

**Why separate `measurement_series`?**
- Distinct uncertainty semantics
- Cleaner API (no template specialization pollution)
- Measurement-specific operations colocated

**Why separate headers?**
- Logical organization (units/ and measurements/ folders)
- Avoids inclusion bloat
- Consistent namespace structure

**Why polymorphic allocator?**
- Single template handles all allocation strategies
- User controls memory lifetime
- Zero-cost abstraction
- Arena patterns emerge naturally

## Future Extensions

- **Cubic spline interpolation** via optional template parameter
- **Time-tagged variants** (e.g., commanded vs measured)
- **Windowed operations** (sliding window statistics)
- **Serialization** (to/from binary or text formats)
- **Multi-dimensional series** (e.g., 3D position vectors)
