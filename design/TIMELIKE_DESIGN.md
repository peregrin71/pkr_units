# Timelike Concept and Uncertain Timestamps Design

## Overview

The time series system supports flexible timestamp representation through a **`timelike` concept** system with specializations for three fundamental time representations:

1. **Chrono-based (std::chrono::time_point)** - Certain, high-precision timestamps
2. **Unit-based (PKR time units)** - Unit-aware, dimensionally-aware timestamps 
3. **Measurement-based (measurement_lin_t<TimeUnit>)** - Uncertain timestamps with explicit uncertainty bounds

## Problem Statement

### Original Limitation
The initial `quantity_series` implementation hardcoded `std::chrono::high_resolution_clock::time_point` as the timestamp type. This had several issues:
- No support for uncertain timestamps in experimental data
- No unit-aware temporal analysis
- Missing dimension for timestamp uncertainty (time measurement itself is uncertain)
- Conversion friction between chrono and library time units

### Design Requirements
- Support both chrono and library time units seamlessly
- Enable uncertain timestamps with built-in uncertainty tracking
- Maintain backward compatibility with existing chrono-based code
- Provide zero-cost abstractions through specialization
- Enable dimensional analysis on timestamp operations

## Architecture

### Timelike Concept

```cpp
template <typename T>
concept timelike = requires {
    typename timelike_traits<T>::duration_type;      // Associated duration
    typename timelike_traits<T>::representation_type; // The type itself
};
```

The concept validates that a type "behaves like time" by requiring it to have associated traits.

### Timelike Traits Specializations

All timelike types have a `timelike_traits<T>` specialization providing:

#### Specialization 1: `std::chrono::time_point<Clock, Duration>`

```cpp
template <typename Clock, typename Duration>
struct timelike_traits<std::chrono::time_point<Clock, Duration>>
{
    using duration_type = Duration;
    using representation_type = std::chrono::time_point<Clock, Duration>;
    using value_type = double;  // Seconds for arithmetic

    static double to_value(const representation_type& t);
    static representation_type from_value(double seconds);
    static constexpr double get_uncertainty(const representation_type&); // Always 0
};
```

**Properties:**
- Certain time (no inherent uncertainty)
- High precision via hardware clocks
- Duration: hardware-dependent (typically nanoseconds)
- Use case: Real-time system monitoring

**Example:**
```cpp
quantity_series<meter_t> position;  // Default: chrono::time_point
position.add_now(100.0_m);          // Uses clock::now()
```

#### Specialization 2: PKR Unit Types with Time Dimension

```cpp
template <is_pkr_unit_c TimeUnit>
    requires(details::is_pkr_unit<TimeUnit>::value_dimension == time_dimension)
struct timelike_traits<TimeUnit>
{
    using duration_type = TimeUnit;
    using representation_type = TimeUnit;
    using value_type = typename TimeUnit::value_type;

    static value_type to_value(const TimeUnit& t);
    static TimeUnit from_value(value_type val);
    static constexpr value_type get_uncertainty(const TimeUnit&); // Always 0
};
```

**Properties:**
- Certain time with unit semantics
- Enables unit conversions (second ↔ millisecond ↔ microsecond)
- Dimensional analysis enforced at compile-time
- Duration: Same as the unit (e.g., `second_t` has duration `second_t`)
- Use case: Unit-safe numerical simulations

**Supported Time Units:**
- `second_t`, `millisecond_t`, `microsecond_t`, `nanosecond_t`, ... (SI prefixes)
- `minute_t`, `hour_t`, `day_t` (derived)
- Any custom unit with `time_dimension`

**Example:**
```cpp
// Position as function of unit-safe time
quantity_series<meter_t, second_t<double>> trajectory;
trajectory.add_at(0.0_s, 0.0_m);
trajectory.add_at(0.1_s, 0.5_m);
trajectory.add_at(0.2_s, 2.0_m);

auto mean_pos = trajectory.mean();  // Dimensions preserved
```

#### Specialization 3: Measurements with Time Dimension

```cpp
template <is_pkr_unit_c TimeUnit>
    requires(details::is_pkr_unit<TimeUnit>::value_dimension == time_dimension)
struct timelike_traits<measurement_lin_t<TimeUnit>>
{
    using duration_type = TimeUnit;
    using representation_type = measurement_lin_t<TimeUnit>;
    using value_type = typename TimeUnit::value_type;

    static value_type to_value(const measurement_lin_t<TimeUnit>& m);
    static measurement_lin_t<TimeUnit> from_value(value_type val);
    static value_type get_uncertainty(const measurement_lin_t<TimeUnit>& m);
};
```

**Properties:**
- Uncertain time with explicit bounds
- Uncertainty linear combination same as measurements
- Time uncertainty may propagate into interpolation bounds
- Duration: Same as underlying time unit
- Use case: Experimental data with timestamp uncertainty

**Example:**
```cpp
using uncertain_time = measurement_lin_t<second_t<double>>;

quantity_series<meter_t, uncertain_time> experiment;

// Timestamp at 0.5s ± 0.01s
experiment.add_at(uncertain_time{0.5_s, 0.01_s}, 10.0_m);

// Query time uncertainty
auto [t, pos] = experiment[0];
auto time_unc = t.uncertainty().value();  // 0.01 seconds
```

## Timed Value Structure

Updated to support flexible time representation:

```cpp
template <timelike TimeType, typename Quantity>
struct timed_value
{
    TimeType time;              // Can be time_point, second_t, or measurement<second_t>
    Quantity value;

    // Get time uncertainty (0 if time has no uncertainty)
    auto get_time_uncertainty() const
    {
        return timelike_traits<TimeType>::get_uncertainty(time);
    }
};
```

## Quantity Series Template

Extended with optional TimeType parameter:

```cpp
template <is_pkr_unit_c Quantity,
          timelike TimeType = std::chrono::high_resolution_clock::time_point,
          typename Allocator = std::pmr::polymorphic_allocator<std::byte>>
class quantity_series : public details::is_quantity_series_tag
{
    using timed_quantity = details::timed_value<TimeType, Quantity>;
    using duration = typename timelike_traits<TimeType>::duration_type;
    
    // Methods work with any timelike TimeType
    void add_at(TimeType t, Quantity&& val);
};
```

### Type Aliases for Common Patterns

```cpp
// Default: chrono-based (backward compatible)
quantity_series<meter_t>  // TimeType defaults to chrono::time_point

// Unit-based time
quantity_series<meter_t, second_t<double>>

// Uncertain time
quantity_series<meter_t, measurement_lin_t<second_t<double>>>
```

## API Extensions

### add_now() - Conditional on Chrono Type

```cpp
template <typename T>
    requires is_chrono_time_point<TimeType>
void add_now(T&& val);
```

Only available for chrono-based series. For unit-based time, pass explicit timestamp:
```cpp
position_unit_time.add_at(t_value, measurement);
```

### Time Uncertainty Querying

```cpp
// All series types support:
auto time_unc = series[i].get_time_uncertainty();

// For measurements (only):
auto [time, value] = measurement_series[i];
// time is measurement<second_t>
auto unc = time.uncertainty().value();
```

## Uncertainty Propagation

### Time Uncertainty → Value Uncertainty

When timestamps have uncertainty, operations like interpolation can propagate this into value bounds:

**Linear interpolation with uncertain time:**
```
v(t ± Δt) depends on interpolation slope
If slope is dv/dt = m, then Δv ~ m * Δt
```

**Current Implementation (Future Enhancement):**
- Interpolation methods can accept time_type argument
- Bounds checking respects time uncertainty ranges
- Statistics methods can integrate uncertainty from timestamps

### Practical Example

```cpp
using uncertain_second = measurement_lin_t<second_t<double>>;
quantity_series<meter_t, uncertain_second> experiment;

// Measurements with ±0.01s timing uncertainty
experiment.add_at({0.0_s, 0.01_s}, 0.0_m);
experiment.add_at({1.0_s, 0.01_s}, 5.0_m);
experiment.add_at({2.0_s, 0.01_s}, 20.0_m);

// Interpolation accounts for time uncertainty
// Position at t=1.5s could span range based on timing error
```

## Design Decisions

### Why Specialization Over Wrapper?
- Zero runtime overhead - traits are compile-time metadata
- Works naturally with existing PKR types (no wrapper types needed)
- Extensible without modifying core library
- Template specialization provides exact type information

### Why Separate Duration and Representation Types?
- `duration_type`: How time intervals are expressed (for diffs)
- `representation_type`: How time points are stored
- For chrono: both are related but slightly different concepts
- For units: both are the same type for clarity

### Backward Compatibility
- Default `TimeType` is chrono::time_point
- Existing code continues working unchanged
- No breaking changes to public API
- New features are purely additive

## Performance Characteristics

- **Memory:** No overhead for chrono vs unit-based time (same size)
- **Compile-time:** Specialization resolved at instantiation, not runtime
- **Runtime:** All operations are same as before (traits are compile-time only)
- **Zero-cost abstractions:** No virtual dispatch, all inline-able

## Limitations and Future Work

### Current Constraints
- Interpolation doesn't yet propagate time uncertainty bounds
- No automatic conversion between time representations
- Measurement-based time requires explicit uncertainty values

### Future Extensions
1. Interpolation bounds based on timestamp uncertainty
2. Automatic time representation conversion
3. Time uncertainty analysis methods
4. Correlation handling for timestamp-value pairs

## Examples

### Pattern 1: Simple Chrono Series (Backward Compatible)
```cpp
quantity_series<meter_t> simple;  // Default: chrono
simple.add_now(100.0_m);          // Works unchanged
```

### Pattern 2: Unit-Aware Time Series
```cpp
using second_f = second_t<float>;
quantity_series<meter_t, second_f> physics_sim;
physics_sim.add_at(0.0_s, x0);
physics_sim.add_at(dt, x1);
```

### Pattern 3: Experimental Data with Timestamp Uncertainty
```cpp
using uncertain_time = measurement_lin_t<second_t<double>>;
quantity_series<meter_t, uncertain_time> lab_data;
lab_data.add_at({measured_time, std_dev}, measured_value);
```

## Testing Strategy

1. **Compile-time verification:** Concept satisfaction tests
2. **Type checking:** Static assertions for trait requirements
3. **Backward compatibility:** Existing chrono tests unchanged
4. **Unit-based time:** New tests using second_t, millisecond_t
5. **Uncertain time:** Tests with measurement timestamps
6. **Mixed operations:** Interaction between different time types

## Summary

The timelike concept system enables flexible timestamp representation while maintaining:
- **Type safety** through compile-time specialization
- **Dimensional analysis** for unit-aware time
- **Explicit uncertainty** for measurement-based timestamps
- **Backward compatibility** through sensible defaults
- **Zero overhead** through compile-time resolution

This design transforms the time series container from a simple chrono wrapper into a general-purpose temporal data structure that integrates seamlessly with the PKR units library's dimensional analysis framework.
