# Uncertainty Propagation with Dimensional Analysis

## Overview

This document describes a rigorous approach to uncertainty propagation that leverages dimensional analysis. Instead of treating uncertainties as dimensionless values, we track them by base physical dimensions, providing deeper insight into measurement limitations.

## Core Concept

**Track uncertainties by base dimension:**
- Length (L)
- Time (T) 
- Mass (M)
- Temperature (Θ)
- Electric current (I)
- Amount of substance (N)
- Luminous intensity (J)

## Dimensional Breakdown of Quantities

Each measured quantity is expressed in terms of base dimensions:

- **Velocity** v: L⋅T⁻¹
- **Area** A: L²  
- **Density** ρ: M⋅L⁻³
- **Drag force** F_d: M⋅L⋅T⁻²

## Dimensional Uncertainty Propagation

For each base dimension, sum uncertainty contributions from all variables containing that dimension.

### Example: Drag Force F_d

Given: F_d = ½ × ρ × v² × A × C_d

**Length (L) uncertainty** comes from:
- Area A (L²)
- Velocity v² (L²⋅T⁻²) 
- Density ρ (M⋅L⁻³)

**Time (T) uncertainty** comes from:
- Velocity v² (L²⋅T⁻²)

**Mass (M) uncertainty** comes from:
- Density ρ (M⋅L⁻³)

#### Mathematical Decomposition Steps

**Step 1: Express Drag Force in Base Dimensions**
```
F_d = ½ × ρ × C_d × A × v²
```

Dimensions:
- ρ (density): M⋅L⁻³
- C_d (drag coefficient): dimensionless  
- A (area): L²
- v² (velocity squared): L²⋅T⁻²

Result: F_d ∼ M¹⋅L¹⋅T⁻²

**Step 2: Relative Uncertainty Formula**
For multiplication and powers, the total relative uncertainty combines via:
```
(ΔF_d/F_d)² = (Δρ/ρ)² + (ΔC_d/C_d)² + (ΔA/A)² + (2⋅Δv/v)²
```

**Step 3: Group Contributions by Dimension**

**Mass (M)** - comes only from ρ:
```
Mass contribution: (Δρ/ρ)²
```

**Length (L)** - from ρ (power -3), A (power +2), and v² (power +2):
```
Length contribution: (-3⋅Δρ/ρ)² + (2⋅ΔA/A)² + (2⋅Δv/v)²
```

**Time (T)** - only from v² (power -2):
```
Time contribution: (-2⋅Δv/v)²
```

**Step 4: Compute Per-Dimension Uncertainty**
For each dimension, take the square root of the sum of squares:
```
u_M = √[(Δρ/ρ)²]
u_L = √[(-3⋅Δρ/ρ)² + (2⋅ΔA/A)² + (2⋅Δv/v)²]  
u_T = √[(-2⋅Δv/v)²]
```

**Step 5: Flatten to Total Uncertainty**
Combine all dimensions using quadrature:
```
(ΔF_d/F_d)² = u_M² + u_L² + u_T²
```

This provides both per-dimension contributions and the final combined uncertainty.

## Reporting Per-Dimension Uncertainty

Express contributions as relative uncertainties:

- Length contribution: ±X%
- Time contribution: ±Y%  
- Mass contribution: ±Z%

## Final Combined Uncertainty

Combine per-dimension contributions using quadrature (RSS):

δ_total = √(δ_L² + δ_T² + δ_M² + ...)

## Benefits

1. **Identifies dominant uncertainty sources** - shows which physical dimension limits precision
2. **Guides measurement improvement** - prioritize better equipment for dominant dimensions
3. **Physical insight** - connects uncertainty to fundamental physical quantities
4. **Advanced metrology approach** - used in precision measurement and dimensional analysis

## Implementation Considerations

This approach requires:
- Dimensional decomposition of all quantities
- Uncertainty tracking per base dimension
- Proper mathematical propagation rules
- Clear reporting of per-dimension contributions

## Library Extension: measurement_t Class

**Design updated to use `unit_t` types for uncertainties**, leveraging existing arithmetic for precise uncertainty propagation.

### Updated Design

```cpp
template<typename UnitT>
class measurement_t {
private:
    UnitT m_value_;           // The measured value with units
    UnitT m_uncertainty_;     // Uncertainty as same unit type (leverages existing arithmetic)
    
public:
    // Construction: uncertainty must be compatible unit type
    constexpr measurement_t(UnitT value, UnitT uncertainty);
    
    // Example: millimeter measurement with millimeter uncertainty
    // measurement_t<millimeter_t> length{millimeter_t{500.0}, millimeter_t{5.0}};  // 500 ± 5 mm
    
    // Arithmetic operations that propagate both values and uncertainties
    auto operator+(const measurement_t& other) const {
        // Values add using existing unit_t arithmetic
        auto result_value = m_value_ + other.m_value_;
        
        // Uncertainties combine in quadrature using library math functions
        auto uncertainty_sum_squares = m_uncertainty_ * m_uncertainty_ + other.m_uncertainty_ * other.m_uncertainty_;
        auto result_uncertainty = math::sqrt(uncertainty_sum_squares);
        
        return measurement_t<decltype(result_value)>{result_value, result_uncertainty};
    }
    
    auto operator*(const measurement_t& other) const {
        // Values multiply using existing unit_t arithmetic  
        auto result_value = m_value_ * other.m_value_;
        
        // Relative uncertainties add: δ(a×b)/(a×b) = δa/a + δb/b
        auto relative_uncertainty = (m_uncertainty_ / m_value_) + (other.m_uncertainty_ / other.m_value_);
        auto result_uncertainty = result_value * relative_uncertainty;
        
        return measurement_t<decltype(result_value)>{result_value, result_uncertainty};
    }
    
    // Accessors
    const UnitT& value() const { return m_value_; }
    const UnitT& uncertainty() const { return m_uncertainty_; }
    
    // Get relative uncertainty (dimensionless)
    auto relative_uncertainty() const { return m_uncertainty_ / m_value_; }
};
```

### Required Math Functions

The `measurement_t` class requires additional math functions to be added to the units library:

```cpp
namespace math {

// Square root for unit_t types (needed for quadrature uncertainty combination)
template<typename UnitT>
auto sqrt(const UnitT& value) -> /* appropriate result type */;

// Additional functions that may be needed for advanced uncertainty propagation:
template<typename UnitT>
auto pow(const UnitT& base, double exponent) -> /* appropriate result type */;

template<typename UnitT>  
auto exp(const UnitT& value) -> /* dimensionless result */;

template<typename UnitT>
auto log(const UnitT& value) -> /* dimensionless result */;

} // namespace math
```

**Note**: `math::sqrt()` needs to handle dimensional analysis correctly. For example:
- `sqrt(m²)` should return `m` (length)
- `sqrt(m⁴)` should return `m²` (area)
- `sqrt(dimensionless)` should return `dimensionless`

This requires implementing square root operations that are aware of dimensional exponents.

### Usage Examples

```cpp
// Length measurement in millimeters
measurement_t<millimeter_t> length{mm_t{500.0}, mm_t{5.0}};  // 500 ± 5 mm

// Time measurement in seconds  
measurement_t<second_t> time{second_t{2.0}, second_t{0.1}};  // 2.0 ± 0.1 s

// Velocity calculation with automatic uncertainty propagation
auto velocity = length / time;  
// Result: measurement_t<meter_per_second_t> with properly propagated uncertainty
// Units automatically converted (mm/s → m/s) for both value and uncertainty

// Addition with unit conversion
measurement_t<millimeter_t> len1{mm_t{500.0}, mm_t{5.0}};   // 500 ± 5 mm  
measurement_t<centimeter_t> len2{cm_t{30.0}, cm_t{0.5}};    // 30 ± 0.5 cm
auto total_length = len1 + len2;  // Automatic conversion and uncertainty combination
```

### Benefits

- **Zero Code Duplication**: Uncertainty math reuses all existing `unit_t` arithmetic
- **Automatic Unit Conversion**: Uncertainties convert units just like measurements
- **Type Safety**: Dimensional consistency enforced at compile-time
- **Precision**: Inherits all numerical stability of existing operations
- **Maintainability**: Bug fixes to `unit_t` arithmetic automatically improve uncertainty calculations

### Practical C++ Examples

#### Speed Measurement Example

```cpp
// Distance measurement with uncertainty
measurement_t<millimeter_t> distance{mm_t{5000.0}, mm_t{50.0}};  // 5000 ± 50 mm

// Time measurement with uncertainty  
measurement_t<second_t> time{second_t{2.5}, second_t{0.1}};      // 2.5 ± 0.1 s

// Velocity calculation with automatic uncertainty propagation
auto velocity = distance / time;
// Result: measurement_t<meter_per_second_t>
// Value: 2.0 m/s, Uncertainty: 0.092 m/s (automatically calculated)

// Access results
std::cout << "Velocity: " << velocity.value() << " ± " << velocity.uncertainty() << " m/s\n";
std::cout << "Relative uncertainty: " << velocity.relative_uncertainty() * 100 << " %\n";
```

#### Drag Force Calculation Example

```cpp
// Fluid density measurement
measurement_t<kilogram_per_cubic_meter_t> density{
    kg_per_m3_t{1.225}, kg_per_m3_t{0.005}  // Air density: 1.225 ± 0.005 kg/m³
};

// Cross-sectional area
measurement_t<square_meter_t> area{
    m2_t{0.01}, m2_t{0.0001}  // 0.01 ± 0.0001 m²
};

// Velocity measurement
measurement_t<meter_per_second_t> velocity{
    m_per_s_t{10.0}, m_per_s_t{0.2}  // 10.0 ± 0.2 m/s
};

// Drag coefficient (dimensionless, uncertainty from measurement/calibration)
measurement_t<scalar_t> drag_coeff{
    scalar_t{0.47}, scalar_t{0.02}  // 0.47 ± 0.02 (sphere)
};

// Drag force calculation: F_d = 0.5 × ρ × v² × A × C_d
auto velocity_squared = velocity * velocity;  // v² with propagated uncertainty
auto dynamic_pressure = density * velocity_squared * scalar_t{0.5};  // ½ρv²
auto drag_force = dynamic_pressure * area * drag_coeff;

// Result: measurement_t<newton_t> with fully propagated uncertainty
std::cout << "Drag force: " << drag_force.value() << " ± " << drag_force.uncertainty() << " N\n";

// The uncertainty automatically accounts for:
// - Density measurement error (±0.005 kg/m³)
// - Area measurement error (±0.0001 m²) 
// - Velocity measurement error (±0.2 m/s)
// - Drag coefficient uncertainty (±0.02)
// - All correlations and dimensional conversions handled automatically
```

#### Unit Conversion with Uncertainties

```cpp
// Imperial to metric conversion with uncertainty preservation
measurement_t<mile_per_hour_t> speed_mph{mph_t{60.0}, mph_t{2.0}};  // 60 ± 2 mph

// Convert to metric (uncertainty converts automatically)
measurement_t<kilometer_per_hour_t> speed_kph = speed_mph;  // Automatic conversion
// Result: 96.56 ± 3.22 km/h (exact conversion of both value and uncertainty)

measurement_t<meter_per_second_t> speed_mps = speed_mph;    // To m/s
// Result: 26.82 ± 0.89 m/s
```

These examples demonstrate how `measurement_t` seamlessly extends your existing unit system with automatic uncertainty propagation, maintaining all the type safety and dimensional analysis of the core library.

### Usage Examples

```cpp
// Standard double precision (default)
measurement_t<meter_t> length{meter_t{5.0}, {.length = 0.1}};

// Single precision
measurement_t<meter_t, float> length_float{meter_t{5.0f}, {.length = 0.1f}};

// Complex uncertainties (for advanced uncertainty analysis)
measurement_t<meter_t, std::complex<double>> length_complex{
    meter_t{5.0}, 
    {.length = std::complex<double>{0.1, 0.05}}
};
```

### Key Features

1. **Wraps existing `unit_t`**: Maintains compatibility with current library
2. **Per-dimension uncertainties**: Tracks absolute uncertainty for each base dimension
3. **Automatic propagation**: Operations combine values via `unit_t` arithmetic and propagate uncertainties dimensionally
4. **Combined reporting**: Provides final uncertainty for the result quantity

### Usage Example

```cpp
// Create measurements with uncertainties
auto length = measurement_t{meter_t{5.0}, {.length = 0.1}};  // 5.0 ± 0.1 m
auto time = measurement_t{second_t{2.0}, {.time = 0.05}};    // 2.0 ± 0.05 s

// Calculate velocity with propagated uncertainty
auto velocity = length / time;  // Results in velocity measurement with combined uncertainty

// Access results
std::cout << "Velocity: " << velocity.value() << " ± " << velocity.combined_uncertainty() << " m/s\n";
```

### Benefits

- **Seamless integration** with existing `unit_t` types
- **Compile-time safety** maintained through template system
- **Advanced analysis** capabilities for uncertainty budgeting
- **Clear separation** of measurement values vs. uncertainties

## Key Insight: Single Uncertainty per Dimension

**Yes, you end up with one combined uncertainty per base dimension**, even when multiple powers of that dimension are involved.

### Why Only One Length Dimension?

In the SI system, area (L²) and volume (L³) are just powers of the same base dimension: Length (L). When propagating uncertainties dimensionally, you don't create separate categories for "area" or "volume"—they all contribute to the **same length uncertainty bucket**.

The contribution from each term is weighted by its exponent:
- Direct length measurements (L¹): multiply relative uncertainty by 1
- Area measurements (L²): multiply relative uncertainty by 2  
- Volume measurements (L³): multiply relative uncertainty by 3

### Mathematical Combination

For a calculation involving length, area, and volume:

```
u_L² = (1 ⋅ rel_error_from_length)² + (2 ⋅ rel_error_from_area)² + (3 ⋅ rel_error_from_volume)²
```

Then take the square root for the combined length contribution: `u_L = √u_L²`

### Example: Length Uncertainty in Complex Calculations

When length, area, and volume are involved:

- **Direct length measurements** (L¹): Contribute directly to length uncertainty
- **Area measurements** (L²): Their uncertainties contribute to length uncertainty (scaled by dimension power)
- **Volume measurements** (L³): Their uncertainties also contribute to length uncertainty (scaled by dimension power)

**Final result**: One combined length uncertainty that incorporates all contributions from L¹, L², L³, etc. measurements.

### Why This Works

The dimensional approach combines uncertainties from all measurements containing each base dimension into a single uncertainty value for that dimension in the final result. This provides the best of both worlds:

1. **Detailed analysis**: Shows which types of measurements (length vs. area vs. volume) contribute most to uncertainty
2. **Practical reporting**: Still produces a single uncertainty value per dimension for the final quantity
