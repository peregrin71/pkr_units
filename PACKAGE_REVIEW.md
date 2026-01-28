# SI Units Package - Comprehensive Review & Recommendations

## Executive Summary

The SI Units library is a **well-architected, production-quality C++20 header-only library** for type-safe dimensional analysis. It successfully prevents unit mismatches at compile-time through template metaprogramming and constexpr evaluation.

**Current Status: 50-60% Feature Complete**
- ✅ Core foundation: Excellent
- ✅ Basic SI units (4 of 7): Complete
- 🟡 Derived units: Partially implemented
- 🟡 String formatting: Basic implementation exists
- 🟡 Type conversions: Explicit casting in progress
- ⚠️ Advanced features: Limited

**Test Coverage: 272 tests passing** across all basic unit types with constexpr evaluation and edge case handling.

---

## Current Implementation Summary

### ✅ What's Working Well

#### 1. **Core Architecture** (Excellent)
- **Template-based unit system**: Uses NTTP (Non-Type Template Parameters) for dimensions
- **Dimensional analysis**: Enforces correct unit combinations at compile-time
- **Zero-cost abstraction**: Arithmetic operations inline to assembly-level operations
- **Type safety**: Prevents invalid operations like `meter + second`, but allows valid operations like `meter / meter` → scalar
- **Constexpr evaluation**: All operations available at compile-time
- **Scalar support**: Division of same dimensions correctly produces dimensionless quantities (e.g., `meter / meter` → scalar, dereferenceable via `operator*()` to get underlying `double`)

#### 2. **Implemented Basic SI Units** (Complete)
```
✅ Length:       meter, kilometer, millimeter, micrometer, nanometer, decimeter, centimeter
✅ Mass:         kilogram, gram, milligram, microgram, nanogram
✅ Time:         second, millisecond, microsecond, nanosecond
✅ Current:      ampere, milliampere, microampere, nanoampere
✅ Temperature:  kelvin (offset-free arithmetic)
✅ Amount:       mole, millimole, micromole, nanomole
✅ Intensity:    candela (basic, fewer prefixes)
```

#### 3. **Partially Implemented Derived Units**
- **Velocity**: `meter_per_second_t`, `kilometer_per_hour_t`, imperial variants
- **Acceleration**: `meter_per_second_squared_t`, standard gravity
- **Force**: `newton_t`, `kilonewton_t`, imperial variants (`pound_force_t`, `poundal_t`)
- **Pressure**: `pascal`, `kilopascal`, `megapascal` (basic)
- **Energy**: `joule` (basic definition)
- **Power**: `watt` (basic definition)
- **Concentration**: `molar_concentration`, `mass_concentration` (dimension defined)
- **Electrical**: `siemens_t` (conductance), partial resistance/voltage support
- **Density**: Framework exists, unit definitions incomplete

#### 4. **Imperial & Non-SI Units** (Partial)
- Length: `foot_t`, `inch_t`, `yard_t`, `mile_t`
- Mass: `pound_t`, `ounce_t`
- Velocity: `miles_per_hour_t`, `knots_t`, `feet_per_second_t`
- Force: `pound_force_t`, `poundal_t`
- Acceleration: `feet_per_second_squared_t`
- **Missing**: Fahrenheit temperature, BTU, slug units

#### 5. **Advanced Features** (Partial)
- **Multi-cast operations**: Can multiply/divide multiple units with arbitrary powers
- **Casting system**: `si_cast<>` template exists for unit conversions
- **Arithmetic optimizations**: Fast path for same-ratio operations
- **Formatting**: Basic formatting exists, uses AST-based dimension representation

#### 6. **Testing Infrastructure** (Good)
- 272 GTest unit tests covering:
  - Basic operations (add, subtract, multiply, divide)
  - Cross-scale operations (meter + kilometer)
  - Constexpr evaluation
  - Edge cases (zero, negative, very large/small values)
  - Dimension verification
  - Type variations (float, custom types)
  - Imperial conversions
  - Casting operations

---

## Issues & Gaps

### 🔴 Critical Issues

#### 1. **String Formatting is Incomplete**
**Status**: Basic implementation only
- ✅ Can format basic units with dimension info
- ❌ **No symbolic unit names**: Outputs dimension struct, not "5 meters"
- ❌ **No std::format support**: Manual formatting functions only
- ❌ **No parsing**: Cannot parse "5 meters" → unit_t

**Impact**: Library is difficult to use for I/O operations
**Example missing**:
```cpp
auto distance = 5.0_m;
std::cout << distance;  // Outputs dimension struct, not "5 m"
```

**Fix Priority**: HIGH - Blocking usability

#### 2. **Derived Units are Incomplete & Inconsistent**
**Status**: Framework exists, implementation scattered

**Problems**:
- Area, volume: Dimension defined but no dedicated types (must use `length * length`)
- Energy: Dimension exists but no standard units (joule, kilojoule, etc.)
- Many derived unit headers are **empty shells** with no actual unit definitions
- No consistent naming pattern across derived units
- Electrical units incomplete (resistance, voltage, charge missing)

**Missing**: Force × distance = Energy, but no proper `joule` class

**Fix Priority**: HIGH - Core functionality

#### 3. **Type Casting Limitations**
**Status**: Partial implementation

- ✅ `si_cast<>` exists for unit conversions
- ✅ **Explicit conversions only**: meter ↔ kilometer requires explicit `si_cast<>` (intentional design)
- ❌ **Complex casting**: Multiple unit conversions in one expression are verbose
- ❌ **No runtime value checking**: Cannot validate conversion safety at runtime

**Problem Example**:
```cpp
auto a = 1000_m;
auto b = 1_km;
// a and b are different types, even though equal
// Converting requires: si_cast<kilometers>(a)
```

**Fix Priority**: MEDIUM - Workaround exists

#### 4. **Temperature Conversions are Problematic**
**Status**: Partial, offset handling incomplete

- ✅ Kelvin works (no offset)
- ❌ Celsius/Fahrenheit: Offset-based conversions not properly handled
- ❌ Cannot mix Celsius and Kelvin in arithmetic
- ❌ Conversion factors are hardcoded, not symbolic

**Problem**: Temperature is special because 0°C ≠ 0 K (offset of 273.15), but SI unit math assumes zero-equivalence.

**Fix Priority**: MEDIUM-HIGH - Important for real applications

---

### 🟡 Medium Priority Issues

#### 5. **Solid Angle Support (Future Extension)**
**Status**: Not yet implemented
**Complexity**: Medium (requires 9th dimension)

**Rationale**: The library currently includes plane angle (radians) as the 8th SI dimension. Solid angle (steradians) would be a valuable 9th extension for photometry and radiometry applications.

**What is Solid Angle**:
- Plane angle: arc length / radius = θ [rad]
- Solid angle: surface area / radius² = Ω [sr] (steradian)
- Range: 0 to 4π steradians for full sphere

**Use Cases**:
```cpp
// Photometry: luminous intensity per solid angle
candela_t luminous_intensity = lumens / steradian_t;

// Astronomy: angular size of celestial objects
// Sun solid angle from Earth ≈ 0.0000683 sr

// Antenna/Acoustics: radiation patterns
// Field of view in steradians
```

**Implementation**: Add `int solid_angle = 0` to dimension_t struct
- Enables type-safe photometric and radiometric calculations
- Prevents mixing plane angle with solid angle
- Supports luminous intensity [cd] = luminous flux / solid angle [sr]
- Supports radiance [W/sr] = power / solid angle

**Recommendation**: Phase 3+ feature; low priority unless photometry support is needed

---

#### 6. **Incomplete Basic SI Units**
Some metric prefixes missing:
- Length: Missing `decameter`, `hectometer` in some places
- Missing: `yotta`, `zetta`, `exa`, `peta` (high-end) and `atto`, `zepto` (low-end) prefixes

**Fix Priority**: LOW - Rare in practice

#### 6. **Limited Physical Constants Support**
- Framework: None
- Missing: Speed of light, Planck constant, Boltzmann constant, gravitational constant
- Impact: Cannot write physics simulations easily

**Fix Priority**: MEDIUM-HIGH

#### 7. **Dimensionless Quantities**
- ✅ Supported (scalar dimension)
- ❌ Not well-named: No `percentage`, `ratio`, `decibel` types
- ❌ No semantic meaning preservation

**Example**: `0.5_scalar` could mean percentage, ratio, or dimensionless coefficient

**Fix Priority**: LOW-MEDIUM

#### 8. **std::format Integration Missing**
- Current: Manual formatting with custom functions
- Missing: C++20 `std::format` custom formatter specialization

**Fix Priority**: MEDIUM

---

### ⚠️ Lower Priority Issues

#### 9. **Documentation Gaps**
- ✅ DESIGN.md: Excellent architectural documentation
- ❌ User guide: Very minimal
- ❌ API reference: Limited
- ❌ Examples: Few real-world use cases

**Fix Priority**: LOW (Code is self-documenting)

#### 10. **Package/Distribution**
- ✅ CMake setup works
- ✅ Conan package structure exists
- ❌ Vcpkg support missing
- ❌ No pre-built release packages
- ❌ Not distributed on package repositories

**Fix Priority**: LOW-MEDIUM (header-only = easy distribution)

#### 11. **Cross-Platform Testing**
- ✅ Works on Windows MSVC and Clang
- ❌ GCC not supported on Windows (expected)
- ❌ No Linux/macOS testing yet
- ❌ No CI/CD pipeline

**Fix Priority**: MEDIUM

#### 12. **Performance Benchmarks Missing**
- No compile-time analysis
- No runtime performance comparison
- No binary size measurements
- No caching strategy documentation

**Fix Priority**: LOW (likely zero-overhead)

---

## Recommendations by Category

### 🚀 CRITICAL - Do First (Week 1-2)

#### 1. **Complete String Formatting**
**Effort**: 2-3 days
**Impact**: Transforms usability

**Tasks**:
```cpp
// Implement custom std::formatter specialization
template<> struct std::formatter<si::meter> {
    constexpr auto parse(auto& ctx) { return ctx.begin(); }
    auto format(const si::meter& m, auto& ctx) const {
        return std::format_to(ctx.out(), "{} m", m.value());
    }
};

// Add symbolic unit names for all units
// Add parsing: from_string("5.0 meters") -> meter{5.0}
```

**Benefits**:
- Enables readable I/O
- Makes library practical for real use
- Unblocks example writing

---

#### 2. **Fix Derived Unit Implementation**
**Effort**: 3-4 days
**Impact**: Completes core functionality

**Tasks**:
- Move derived unit definitions from empty headers to actual implementations
- Add: Area (m²), Volume (m³), Energy/Joule, Work
- Ensure consistent naming: `square_meter`, `cubic_meter`, `joule`
- Add specializations in `derived_unit_type_t` for all derived units

**Example fix**:
```cpp
// Currently: derive_area.h is mostly empty
// Should have:
inline constexpr dimension_t area_v{.length = 2};
using square_meter = unit_t<double, std::ratio<1, 1>, area_v>;
using square_kilometer = unit_t<double, std::ratio<1000000, 1>, area_v>;
using square_millimeter = unit_t<double, std::ratio<1, 1000000>, area_v>;
```

---

#### 3. **Implement Proper Casting System**
**Effort**: 2 days
**Impact**: Better ergonomics

**Current limitation**:
```cpp
auto a = 1000_m;
auto b = 1_km;
// a != b (different types), even though dimensionally equivalent
```

**Solution**:
```cpp
// Explicit conversions for same-dimension units using si_cast<>
auto a = 1000_m;
auto b = si_cast<meter>(1_km);  // Explicit conversion
auto result = a + b;  // Now both are same type, addition works

// Or use si_cast for result:
auto meters = si_cast<meter>(1_km) + si_cast<meter>(500_m);
```

---

### 📈 HIGH PRIORITY (Week 2-3)

#### 4. **Temperature Conversion Framework**
**Effort**: 2-3 days
**Impact**: Enables thermal calculations

**Tasks**:
- Separate `temperature` (point) from `temperature_difference` (relative)
- Handle offset in Celsius/Fahrenheit conversions
- Implement: `celsius_to_kelvin()`, `fahrenheit_to_kelvin()`
- Allow arithmetic only on `temperature_difference`, not absolute `temperature`

---

#### 5. **Physical Constants**
**Effort**: 1 day
**Impact**: Enables physics simulations

```cpp
namespace si::constants {
    constexpr meters_per_second speed_of_light = 299792458_mps;
    constexpr joules planck_constant = 6.62607015e-34_J;
    constexpr joules_per_kelvin boltzmann_constant = 1.380649e-23_JperK;
}
```

---

#### 6. **Complete Electrical Units**
**Effort**: 1-2 days
**Impact**: Enables electrical engineering

**Missing**:
- Voltage (Volt = J/C = kg⋅m²⋅s⁻³⋅A⁻¹)
- Resistance (Ohm = V/A = kg⋅m²⋅s⁻³⋅A⁻²)
- Charge (Coulomb = A⋅s)
- Capacitance (Farad = C/V)
- Inductance (Henry = V⋅s/A)
- Magnetic Flux (Weber = V⋅s)
- Magnetic Flux Density (Tesla = Wb/m²)

---

### 🎯 MEDIUM PRIORITY (Week 3-4)

#### 7. **Enhanced Type Casting**
- Implement automatic unit narrowing/widening
- Add compile-time validation of unit compatibility
- Support `quantity_cast` for semantic conversions

#### 8. **Astronomical Units & Extended Prefixes**
- Add yocto (10⁻²⁴) through yotta (10²⁴) prefixes
- Astronomical: AU, light-year, parsec
- Solar masses (for astrophysics)

#### 9. **std::format Integration**
```cpp
// Enable all formatting options:
std::cout << std::format("{:.2f} m/s", velocity);
std::cout << std::format("{:^10}", distance);  // Custom width/alignment
```

---

### ✨ NICE-TO-HAVE (Later)

#### 10. **Named Quantities**
```cpp
struct distance : meter {};
struct height : meter {};
struct width : meter {};
// Would prevent accidental mixing of different semantic types
```

#### 11. **Documentation**
- Quick-start guide
- Common patterns (physics, engineering, finance)
- Benchmarks vs. raw doubles
- Migration guide from other libraries

#### 12. **Python Bindings**
- pybind11 wrapper
- Enable NumPy integration
- Jupyter notebook examples

#### 13. **CGS Unit System**
- For scientific/legacy code
- Includes dyne, erg, gauss_t, etc.

#### 14. **CI/CD Pipeline**
- GitHub Actions for multi-compiler testing
- Code coverage reporting
- Performance regression detection
- Automated release building

---

## Code Quality Assessment

### ✅ Strengths
- **Template metaprogramming**: Excellent use of C++20 features
- **Compile-time computation**: Smart use of constexpr
- **Type safety**: Prevents entire classes of bugs
- **Zero-cost abstraction**: No runtime overhead vs. raw doubles
- **Clean architecture**: Well-organized header structure
- **Test coverage**: Good for implemented features

### ⚠️ Areas for Improvement
- **Template complexity**: Some headers are deep (multiply/divide chains)
- **Error messages**: Template errors can be verbose
- **Compile times**: Not measured, could accumulate with all headers
- **Code duplication**: Some arithmetic patterns repeated across unit types
- **Documentation**: Sparse inline comments for complex template logic

---

## Implementation Roadmap Priority Order

### Phase 1: Foundation (Current)
✅ Complete - Core SI units work correctly
✅ All 272 tests passing
✅ Excellent architecture

### Phase 2: Usability (CRITICAL - Do Next)
1. ⚠️ **String Formatting** - Without this, library is hard to use
2. ⚠️ **Derived Units** - Incomplete, many empty headers
3. ⚠️ **Casting System** - Ergonomic unit conversions

**Target**: 2-3 weeks
**Outcome**: Production-ready for basic use cases

### Phase 3: Completeness (HIGH)
4. Temperature conversions
5. Physical constants
6. Electrical units (voltage, resistance, charge, etc.)
7. std::format integration

**Target**: 2-3 weeks
**Outcome**: Handles engineering/physics calculations

### Phase 4: Polish (MEDIUM)
8. Extended SI prefixes
9. Astronomical units
10. Named quantities system
11. Documentation & examples

**Target**: 2 weeks
**Outcome**: Feature-complete

### Phase 5: Distribution (LOW)
12. Vcpkg, conda-forge integration
13. Python bindings (pybind11)
14. CI/CD pipeline
15. Performance benchmarks

**Target**: 1-2 weeks
**Outcome**: Production distribution

---

## Advanced Features Roadmap

Beyond the immediate critical/high-priority items, the library could be extended with sophisticated features that would make it industry-leading:

### **Tier 1: Quick Wins** (1-2 days each)
These provide significant value with minimal implementation effort:

#### 1. **Unit-Aware String Formatting (Explicit)**
The library philosophy is to keep formatting explicit and type-aware:
```cpp
auto distance = 1_mm;
std::cout << format(distance);  // Outputs "1 mm" (reflecting actual type)

auto distance2 = 0.000001_m;
std::cout << format(distance2);  // Outputs "0.000001 m" (reflects input type)

// User is in control - if they want different units, use explicit si_cast:
auto in_micrometers = si_cast<micrometers>(distance2);
std::cout << format(in_micrometers);  // Outputs "1 μm"
```
**Design Philosophy**: No hidden automatic conversions in formatting. The output type matches the input type, making it explicit and clear. Users control prefix/unit via explicit `si_cast`.

**Canonical Form Convention**: Derived units should follow BIPM SI convention for dimension ordering:
- Order: length, mass, time, current, temperature, amount, intensity
- Positive exponents first, then negative exponents
- Example: Force (Newton) → `kg⋅m⋅s⁻²`, not `s⁻²⋅kg⋅m`
- The `dimension_t` struct already implements this ordering
- When formatting derived units, canonical representation ensures consistency with international SI standards

**Character Encoding & Exponent Notation**: The formatter supports configurable output based on character encoding support:
```cpp
// UTF-8 formatting (preferred for modern systems, unicode support)
auto velocity = 10_mps;
std::cout << format(velocity, encoding::utf8);           // "10 m⋅s⁻¹" (superscript minus-one)
auto force = 5_N;
std::cout << format(force, encoding::utf8);              // "5 kg⋅m⋅s⁻²" (superscript powers)

// ASCII/ANSI fallback (for terminals with limited character support, logging systems)
std::cout << format(velocity, encoding::ascii);          // "10 m*s^-1" (caret notation)
std::cout << format(force, encoding::ascii);             // "5 kg*m*s^-2"

// Wide character (Windows console, wchar_t streams)
std::wcout << format(velocity, encoding::wide_char);    // L"10 m·s⁻¹" (wide-compatible unicode)

// Auto-detect based on stream type (default)
std::cout << format(velocity);                           // UTF-8 for std::cout
std::wcout << format(velocity);                          // Wide for std::wcout
```

**Character Set Details**:
- **UTF-8** (default for std::cout): Uses Unicode superscripts (⁻, ¹, ², ³, etc.) and middle-dot (⋅) for multiplication
- **ASCII**: Uses `*` for multiplication, `^` for exponents (e.g., `s^-2`), avoids all unicode
- **Wide-char** (std::wcout): Unicode superscripts compatible with Windows console wide character output

**Benefit**: Transparent, predictable output; no surprise unit conversions; internationally consistent notation; adapts to output stream capabilities
**Use case**: Clear, debuggable output; code intent is obvious from type; compatibility with legacy systems and logging frameworks

---

#### 2. **Customizable Root Namespace (Integration)**
For codebases that already have a `si` namespace or prefer a different root namespace, the library supports namespace customization via preprocessor:

```cpp
// Option 1: Custom namespace (define BEFORE including pkr_units headers)
#define PKR_SI_NAMESPACE physics
#include <pkr_units/si.h>

auto distance = physics::meter{5.0};
physics::kilogram mass = 10.0_kg;

// Option 2: Nested namespace
#define PKR_SI_NAMESPACE my_app::units::si
#include <pkr_units/si.h>

my_app::units::si::meter height = 2.0_m;

// Option 3: Default (if PKR_SI_NAMESPACE not defined)
#include <pkr_units/si.h>

si::meter distance = 5.0_m;  // Uses default 'si' namespace
```

**Implementation**: The `namespace_config.h` header defines `PKR_SI_NAMESPACE` to `si` by default, but users can override it. All SI unit definitions use `PKR_SI_BEGIN_NAMESPACE` and `PKR_SI_END_NAMESPACE` macros that expand to the configured namespace.

**Rationale**: Namespace conflicts are common in large codebases. Providing customization at the preprocessor level (before compilation) ensures zero runtime overhead and clean integration with existing code. This is particularly valuable for:
- Legacy systems with existing `si` namespaces
- Organizations with strict naming conventions
- Multi-domain applications (physics, finance, engineering using different unit systems)

**Benefit**: Seamless integration with any existing codebase; no naming conflicts; zero overhead
**Use case**: Integration with legacy systems, multi-namespace applications, organizational standards compliance

---

#### 3. **Context-Aware Formatting (Explicit)**
```cpp
distance d = 1_km;
std::cout << format(d, context::imperial);    // "0.621371 mile" (explicit conversion requested)
std::cout << format(d, context::metric);      // "1 km" (default metric)
std::cout << format(d, context::scientific);  // "1.0 × 10³ m" (explicit format)
```
**Benefit**: User explicitly requests different context/units
**Use case**: International applications where different units are needed
**Note**: User must explicitly ask for unit conversion, maintaining design philosophy

---

#### 3. **Reverse Unit Conversion (Best Fit)**
Only if user explicitly requests:
```cpp
auto value = 1_mm;
std::cout << format(value);  // "1 mm"
// If user wants different unit:
auto best = si_cast<best_unit_for_value>(value);  // Explicit
std::cout << format(best);   // User chose the conversion
```
**Benefit**: Users in control of what gets displayed
**Use case**: When explicitly requested, not automatic

---

#### 4. **Unit Database & Registry**
```cpp
unit_registry registry;
registry.register_unit("parsec", 3.086e16_m);
registry.register_unit("slug", 14.593903_kg);
registry.register_alias("pc", "parsec");

// Load from file:
registry.load_from_yaml("custom_units.yaml");
```
**Benefit**: Extensible system, avoid hardcoding custom units
**Use case**: Domain-specific applications, legacy unit support
**Note**: Still explicit - user creates registry and uses si_cast to convert

---

#### 5. **C++ Concepts for Unit Type Safety (Better Error Messages)**
```cpp
// Define concepts for cleaner errors and better IDE support
template<typename T>
concept is_unit = requires {
    typename T::dimension_type;
    typename T::ratio_type;
    requires std::is_floating_point_v<typename T::value_type>;
};

template<typename T, typename U>
concept compatible_units = requires {
    requires is_unit<T> && is_unit<U>;
    // Same dimension check at compile-time
    requires std::same_as<typename T::dimension_type, typename U::dimension_type>;
};

// Usage: Cleaner compiler errors
template<is_unit T>
auto format(const T& value) { ... }

template<compatible_units T, U>
auto add(const T& a, const U& b) { ... }
```

**Benefits**:
- **Cleaner error messages**: Compiler shows "incompatible_units" instead of template substitution failures
- **Better IDE support**: Autocomplete/IntelliSense understands constraints
- **Early detection**: Type checking happens at concept boundary, not deep in template chain
- **Documentation**: Concepts serve as self-documenting API contracts

**Error Message Improvement**:
```
// Without concepts (current):
error: no matching function for call to 'operator+'
   with T1=unit_t<double, std::ratio<1>, {length: 1, ...}>
   with T2=unit_t<double, std::ratio<1>, {mass: 1, ...}>
   ... (50 lines of template instantiation backtrace)

// With concepts (proposed):
error: 'operator+' requires 'compatible_units<T1, T2>'
   T1 = meter
   T2 = kilogram
   -> dimensions are incompatible: length vs. mass
```

**Use case**: Dramatically improves developer experience, especially for users new to strongly-typed units
**Implementation**: C++20 concepts on all arithmetic operators and casting functions
**Effort**: 2-3 days to retrofit existing templates

---

### **Tier 2: Medium Effort** (1-2 weeks each)
These provide power features with moderate implementation complexity:

#### 5. **Error Propagation Framework (Opt-In)**
**Status**: Not implemented, but valuable for scientific computing

The library should support **error propagation for measurements**, following proper numerical methods conventions. Users opt-in by using specialized types:

```cpp
// Standard: no error tracking
auto height = 1.5_m;

// Opt-in: explicit error tracking via specialized template
auto height_measured = measured_t<meter>{value: 1.5_m, uncertainty: 0.05_m};
auto width_measured = measured_t<meter>{value: 2.0_m, uncertainty: 0.1_m};

// Automatic error propagation in calculations
auto area = height_measured * width_measured;
// Result: 3.0 m² with uncertainty propagated via:
// σ_z = sqrt((∂z/∂x·σ_x)² + (∂z/∂y·σ_y)²)

std::cout << area;  // "3.0 ± 0.28 m²"
```

**Design Approach**:
- **Zero-cost abstraction**: Regular `meter` has zero overhead; only `measured_t<meter>` carries uncertainty tracking
- **Opt-in via type**: Users explicitly choose `measured_t<T>` vs. plain unit — no coupling between code paths
- **Proper error propagation**: Uses standard numerical methods (standard deviation propagation for dependent variables)
- **No hidden overhead**: Plain units completely unaffected; uncertainty infrastructure isolated via template specialization
- **Scientific rigor**: Properly documents error sources and propagation rules following ISO GUM

**Benefit**: Makes library suitable for experimental science, metrology, and measurement-based calculations
**Use case**: Laboratory measurements, sensor data analysis, error budgeting
**Mathematical foundation**: Standard uncertainty propagation from numerical methods textbooks
**Reference**: ISO Guide to the Expression of Uncertainty in Measurement (GUM)
**Performance guarantee**: `measured_t<T>` adds cost only when used; regular units remain zero-overhead

---

#### 6. **Runtime Dimensional Analysis**
```cpp
// For cases where units come from input/configuration
class quantity {
    double value;
    dimension_t dimension;  // Checked at runtime
    
    quantity operator+(const quantity& other) {
        if (dimension != other.dimension) throw dimension_mismatch();
        return {value + other.value, dimension};
    }
};
```
**Benefit**: Flexibility when compile-time types aren't available
**Use case**: Scientific scripts, data analysis, configuration systems

---

#### 7. **Quantity Coupling / Physical Laws**
```cpp
template<typename Distance, typename Time>
requires can_compute_velocity<Distance, Time>
auto compute_speed(Distance d, Time t) {
    return d / t;  // Returns velocity type automatically
}

// Could extend to enforcement of:
// - E = mc² (energy-mass equivalence)
// - F = ma (Newton's second law)
// - Ohm's law: V = IR
```
**Benefit**: Guides users to correct physics relationships
**Use case**: Physics simulations, engineering design tools

---

#### 8. **Unit Normalization / Canonical Forms**
```cpp
auto force = 5.0_N;
auto distance = 3.0_km;
auto energy = force * distance;

std::cout << energy;           // Current: force×distance compound
std::cout << normalize(energy);  // "15000000 J" (canonical joule)
```
**Benefit**: Simplification and unit comparison
**Use case**: Comparing quantities from different sources, simplifying expressions

---

#### 9. **Conversion History / Provenance Tracking (With Error Accumulation)**
```cpp
// For plain units: track conversion chain
auto original = 5.0_mile;
auto converted = si_cast<kilometer>(original);
auto trace = conversion_history(converted);
// Shows: 5 mi → 8.046720 km (with precision info)

// For measured quantities: track conversions AND error propagation
auto distance = measured_t<mile>{value: 5.0_mile, uncertainty: 0.1_mile};
auto distance_km = si_cast<kilometer>(distance);
// Automatically accounts for:
// 1. Propagation of original uncertainty through conversion factor
// 2. Floating-point rounding errors in the conversion operation itself
// 3. Cumulative error from conversion chain (mi → m → km, etc.)

auto history = conversion_history(distance_km);
// Shows: 5.0 ± 0.161 mi → 8.047 ± 0.259 km
//        (uncertainty grows due to conversion factor precision)
```

**Error Propagation Through Conversions**:
- **Conversion factor error**: Conversion constants (e.g., 1 mile = 1.60934 km) have limited precision
- **Floating-point rounding**: Each arithmetic operation in conversion adds ~machine epsilon error
- **Cumulative chains**: Multi-step conversions (mile → meter → kilometer) accumulate error at each step
- **Automatic tracking**: `measured_t<T>` automatically computes error growth using error propagation rules

**Benefit**: Complete traceability showing not just where data came from, but *how trustworthy* it is after conversions
**Use case**: Engineering reports (with uncertainty budgets), scientific data pipelines, regulatory compliance requiring uncertainty documentation

---

#### 10. **Optimal Error Division Strategy (For measured_t)**
```cpp
// measured_t automatically optimizes division to minimize error growth
auto distance = measured_t<meter>{value: 10.0_m, uncertainty: 0.1_m};
auto time = measured_t<second>{value: 2.0_s, uncertainty: 0.05_s};

// Library automatically chooses better error path:
auto velocity = distance / time;

// Implementation decides:
// Option A: Direct division (a / b)
// Option B: Multiply by inverse (a * (1/b))
// → Selects whichever propagates less uncertainty
```

**Numerical Analysis**:
- **Direct division**: $\sigma_z = |z| \sqrt{(\sigma_a/a)^2 + (\sigma_b/b)^2}$
- **Multiply by inverse**: Intermediate step creating (1/b) adds precision loss but sometimes results in lower overall error
- **Automatic selection**: Compile-time analysis (via partial specialization) predicts which path has lower error bound
- **Trade-off**: Slightly increased compile time, but guaranteed better measurement trustworthiness

**Benefit**: Ensures measurement uncertainty is minimized through numerically optimal operations
**Use case**: High-precision metrology, experimental physics where error minimization is critical
**Note**: Only affects `measured_t<T>`; plain units use simple division (zero overhead)

---

### **Tier 3: Advanced** (2-4 weeks each)
These are sophisticated features for specialized domains:

#### 10. **Symbolic Quantity Algebra**
```cpp
// Keep expressions symbolic instead of evaluating
using F = force;
using a = acceleration;
using m = mass;

equation<F> newtons_law = m * a;
auto mass_formula = solve_for<m>(newtons_law, F, a);  // Returns: m = F / a

// Algebraic manipulation of physics equations at compile-time
```
**Benefit**: Derive formulas, validate equations symbolically
**Use case**: Physics education, formula derivation tools

---

#### 11. **Automatic Differentiation with Units**
```cpp
auto position = [](time t) { return 5.0_m * t * t; };

auto velocity = differentiate(position);      // Returns velocity function
auto acceleration = differentiate(velocity);  // Returns acceleration function

// Compile-time dimension tracking through calculus!
```
**Benefit**: Differentiation automatically produces correct units
**Use case**: Physics simulations, control systems

---

#### 12. **Matrix/Tensor Operations with Units**
```cpp
matrix<meter> positions{{1_m, 2_m}, {3_m, 4_m}};
matrix<second> times{{1_s, 2_s}, {3_s, 4_s}};

auto velocities = positions / times;  // matrix<velocity>
// Element-wise unit tracking
```
**Benefit**: Enables advanced physics and engineering computations
**Use case**: Multibody dynamics, control theory, fluid dynamics

---

#### 13. **Buckingham π Theorem (Dimensionless Groups)**
```cpp
// In fluid dynamics: Re = ρ·v·D/μ (Reynolds number)
auto dimensionless_groups = find_dimensionless_groups(
    density, velocity, length, viscosity
);
// Outputs: Re = (ρ·v·D)/μ is dimensionless
```
**Benefit**: Automated scaling law discovery, dimensional reduction
**Use case**: Fluid dynamics, aerodynamics, similarity analysis

---

#### 14. **Constraint Solver for Unit Consistency**
```cpp
constraint_system eq;
eq.add(x + y == 10_m);
eq.add(x - y == 2_m);

auto [x_val, y_val] = eq.solve();
// Automatically verifies dimensional consistency throughout
```
**Benefit**: Solves systems with automatic unit validation
**Use case**: Engineering design, physics problems

---

#### 15. **Unit-Aware Optimization Framework**
```cpp
minimize energy;
subject_to {
    mass >= 1_kg,
    volume >= 0.001_m3,
    force <= 1000_N
};
// Solver understands dimensional consistency automatically
```
**Benefit**: Optimization with automatic constraint validation
**Use case**: Design optimization, resource allocation

---

#### 16. **Interpolation with Unit Preservation**
```cpp
std::vector<meter> heights = {1_m, 2_m, 3_m, 4_m};
std::vector<second> times = {0_s, 1_s, 2_s, 3_s};

auto spline = cubic_spline(times, heights);
meter h_at_1_5s = spline(1.5_s);  // Returns meter automatically

auto velocity_spline = differentiate(spline);  // Returns m/s
```
**Benefit**: Numerical methods with proper unit handling
**Use case**: Data fitting, signal processing, scientific computing

---

### **Tier 4: Research / Novel Features** (4+ weeks)
These push the boundaries of what's possible with units:

#### 17. **Physics Domain-Specific Language (DSL)**
```cpp
// Embed physics equations naturally
using namespace si::dsl;

// Ideal gas law: PV = nRT
auto n = (p * v) / (R * T);

// Electromagnetism: F = q(E + v × B)
auto force = q * (E + cross_product(v, B));
```
**Benefit**: Allows physics equations to look like mathematics
**Use case**: Physics education, research, engineering design

---

#### 18. **Quantity Composition Hints / IDE Integration**
```cpp
// IDE could suggest: "Did you mean meters_per_second?"
// when seeing: length_value / time_value
hint<velocity> = length / time;
hint<energy> = force * distance;
hint<power> = energy / time;
```
**Benefit**: Guides users toward correct derived units
**Use case**: IDE plugins, educational tools

---

#### 19. **Historical & Regional Units**
```cpp
using rod = imperial::rod;        // 16.5 feet
using chain = imperial::chain;    // 66 feet
using furlong = imperial::furlong; // 1/8 mile
using shaku = japanese::shaku;    // Japanese unit
using yojana = indian::yojana;    // Historical Indian unit
```
**Benefit**: Support for legacy and regional measurements
**Use case**: Historical data analysis, cultural computing

---

#### 20. **Quantity Validation Framework**
```cpp
template<typename Quantity>
bool is_valid(const Quantity& q) {
    if (q.value() < 0 && !can_be_negative<Quantity>) 
        return false;  // e.g., absolute temperature can't be negative
    
    if (q.value() > physical_limit<Quantity>) 
        return false;  // e.g., velocity can't exceed speed of light
    
    return true;
}
```
**Benefit**: Runtime validation of physical realizability
**Use case**: Detecting invalid input, simulation validation

---

### **Implementation Priority by Value**

| Feature | Effort | Value | When | Notes |
|---------|--------|-------|------|-------|
| Explicit String Formatting | 2-3 days | ⭐⭐⭐⭐⭐ | Phase 2 | Core requirement, type-aware output |
| Context-Aware Formatting | 2 days | ⭐⭐⭐⭐ | Phase 2 | Optional, for specific use cases |
| Unit Database | 3 days | ⭐⭐⭐⭐ | Phase 2 | Extensibility framework |
| Uncertainty Quantification | 1 week | ⭐⭐⭐⭐⭐ | Phase 3 | Valuable for science/engineering |
| Runtime Dimensional Analysis | 5 days | ⭐⭐⭐⭐ | Phase 3 | Alternative to compile-time |
| Symbolic Algebra | 3 weeks | ⭐⭐⭐⭐ | Phase 4 | Advanced feature |
| Auto Differentiation | 2 weeks | ⭐⭐⭐⭐⭐ | Phase 4 | Powerful for physics |
| Matrix Operations | 2 weeks | ⭐⭐⭐⭐ | Phase 4 | Enables advanced computing |
| Physics DSL | 4 weeks | ⭐⭐⭐ | Phase 5 | Nice-to-have, can be built externally |

**Design Philosophy Note**: Features marked as automatic (like "auto-formatting") are explicitly left to client code. The library provides explicit, type-aware primitives; convenience features built on top are user responsibility.

---

## Conclusion

The SI Units library has **excellent foundational architecture** and is **well-tested for implemented features**. However, it's **incomplete for practical use** in several areas:

1. **String formatting** completely blocks usability
2. **Derived units** framework exists but implementations are incomplete
3. **Type casting** could be more ergonomic

**With 2-3 weeks of focused work** on the Critical phase items, this could be a **world-class C++ dimensional analysis library**. The architecture is solid enough to support all planned features without major redesigns.

**Estimated total effort to production-ready**: 6-8 weeks
**Estimated effort for basic usability**: 2-3 weeks

---

## Questions for Discussion

1. **Explicit conversions via si_cast<>** (meter ↔ kilometer) - ENFORCED
   - Pro: Makes code intent explicit, prevents accidental conversions
   - Pro: No hidden precision loss or type confusion
   - Design decision: Only explicit `si_cast<>` allowed, no implicit conversions
   - Rationale: Follows C++ best practice; implicit conversions are historical mistake

2. **Temperature: How to handle offsets elegantly?**
   - Option A: Separate `temperature` and `temperature_delta`
   - Option B: Force Kelvin, provide conversion functions
   - Recommendation: Option A (more correct)

3. **Comparison operators** - Currently intentionally omitted. Should they be added?
   - Could be dangerous with floating-point precision
   - Recommendation: Add with careful documentation

4. **Should parsing be supported?**
   - String parsing: "5 meters" → meter{5}
   - JSON integration: Optional nlohmann/json adapters for configuration/serialization
   - Design: Parsing as opt-in feature (no required regex dependency in core library)
   - Recommendation: Yes, important for real applications; offer as optional modules
   - Use cases: Config files, JSON APIs, data pipelines

