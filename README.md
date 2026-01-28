# pkr_units: Type-Safe Units for Dimensional Correctness in C++

A C++ library providing compile-time type safety for physical units, strictly enforcing dimensional correctness in scientific and engineering computations.

## Overview

pkr_units is a header-only C++ library that provides type-safe units, strictly enforcing dimensional correctness at compile-time to prevent physical unit errors in calculations.

### Characteristics
- Strict compile-time dimensional correctness enforcement
- Zero runtime overhead - all unit checking performed at compile time
- C++20 compatible with concepts and constexpr
- Header-only library with no external dependencies
- Extensible unit system using CRTP and template specialization

### Applications
- Physics engines and simulations
- Engineering calculation libraries
- Scientific computing frameworks
- Aerospace and automotive control systems

## Features

### Units System
- SI base units (meter, kilogram, second, ampere, kelvin, mole, candela, radian)
- Derived units (velocity, acceleration, force, energy, pressure, etc.)
- Imperial/US customary units
- Astronomical units
- Temperature scales with conversions

### Arithmetic Operations
- Strict compile-time dimensional correctness checking
- Automatic unit conversion during operations
- Prevention of dimensionally incorrect operations
- Mixed-unit arithmetic with type safety

### Chrono Integration
- Bidirectional conversion with std::chrono
- Interoperability with existing timing code
- Optimized conversions

### Numerical Methods
- Numerically stable operations in pkr::numerical namespace
- Unit-aware Newton-Raphson and Runge-Kutta methods
- Transcendental functions with dimensional constraints

### Additional Features
- Custom unit definition system
- User-defined literals
- Formatting and I/O support
- Comprehensive test suite
- CMake-based build system

## Getting Started

### Basic Usage

```cpp
#include <pkr_units/si_units.h>

using namespace pkr;

int main() {
    // Create units
    auto distance = meter_t{100.0};
    auto time = second_t{10.0};

    // Arithmetic operations
    auto speed = distance / time;  // Results in meter_per_second_t

    // Unit conversion
    auto speed_kmh = unit_cast<kilometer_per_hour_t>(speed);

    // Mixed unit operations
    auto total_distance = meter_t{500} + kilometer_t{2};

    return 0;
}
```

### Chrono Integration

```cpp
#include <pkr_units/si_units.h>
#include <chrono>

using namespace pkr;
using namespace std::chrono;

int main() {
    // Convert between chrono and pkr_units
    auto chrono_time = seconds{30};
    auto pkr_time = unit_cast<second_t>(chrono_time);

    // Convert back
    auto back_to_chrono = unit_cast<milliseconds>(pkr_time);

    return 0;
}
```

### Numerical Methods

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/numerical.h>

using namespace pkr;
using namespace pkr::numerical;

int main() {
    // Numerically stable operations
    auto result = stable_add(meter_t{1}, millimeter_t{500});

    // Unit-aware Newton-Raphson
    auto f = [](meter_t x) { return x * x - meter_t{4}; };
    auto df = [](meter_t x) { return meter_t{2} * x; };
    auto root = newton_raphson(meter_t{1.5}, f, df);

    return 0;
}
```

## Implementation Details

### Template Metaprogramming Architecture

pkr_units uses advanced C++ template metaprogramming techniques:

- **CRTP (Curiously Recurring Template Pattern)** for unit type hierarchies
- **Template specialization** for dimensional analysis
- **std::ratio** for compile-time rational arithmetic
- **SFINAE** for conditional compilation and error messages
- **constexpr** functions for compile-time calculations

### Memory Layout

```cpp
// Unit types are thin wrappers around arithmetic types
static_assert(sizeof(meter_t) == sizeof(double));  // No overhead
static_assert(alignof(meter_t) == alignof(double)); // Same alignment
```

### Error Messages

The library provides clear, actionable compile-time error messages:

```cpp
// Error: cannot add length and time
auto invalid = meter_t{1} + second_t{1};
// error: no match for 'operator+' (operand types are 'meter_t' and 'second_t')
```

### Extensibility

Custom units can be defined using the provided macros:

```cpp
// Define a custom unit
PKR_DEFINE_UNIT(furlong_t, length_dimension, ratio<201168, 1000>, "furlong");
PKR_DEFINE_UNIT(fortnight_t, time_dimension, ratio<1209600, 1>, "fortnight");
```

## Dimensional Correctness Enforcement

### Physical Dimensions

Each unit type encodes its physical dimensions at compile-time to enforce dimensional correctness:

```cpp
// Base dimensions (7 SI base quantities)
using length_dimension    = dimension_t<1,0,0,0,0,0,0>;  // L
using mass_dimension      = dimension_t<0,1,0,0,0,0,0>;  // M
using time_dimension      = dimension_t<0,0,1,0,0,0,0>;  // T
using current_dimension   = dimension_t<0,0,0,1,0,0,0>;  // I
using temperature_dimension = dimension_t<0,0,0,0,1,0,0>; // Θ
using amount_dimension    = dimension_t<0,0,0,0,0,1,0>;  // N
using intensity_dimension = dimension_t<0,0,0,0,0,0,1>;  // J

// Derived dimensions
using velocity_dimension  = dimension_t<1,0,-1,0,0,0,0>; // L/T
using acceleration_dimension = dimension_t<1,0,-2,0,0,0,0>; // L/T²
using force_dimension     = dimension_t<1,1,-2,0,0,0,0>; // M*L/T²
```

### Unit Conversion

Automatic conversion between units of the same dimension with compile-time correctness checking:

```cpp
// Ratio-based conversion at compile-time
meter_t m{1000};
kilometer_t km = unit_cast<kilometer_t>(m);  // Compile-time ratio<1,1000>
static_assert(km.value() == 1.0);
```

### Type Safety

Operations are strictly checked for dimensional correctness at compile-time:

```cpp
meter_t length{10};
second_t time{5};
auto velocity = length / time;  // ✅ L/T dimension - correct

// Compile error: dimensional mismatch prevents incorrect operations
auto invalid = length + time;   // ❌ L + T - incorrect, caught at compile-time
```

## Unit Operations

### Arithmetic Operations

```cpp
// Addition/Subtraction (same dimensions only)
auto total_length = meter_t{10} + millimeter_t{500};  // Automatic conversion
auto difference = kilogram_t{5} - gram_t{200};

// Multiplication/Division (combines dimensions)
auto area = meter_t{5} * meter_t{3};           // meter²
auto speed = meter_t{100} / second_t{10};      // meter/second
auto acceleration = speed / second_t{5};       // meter/second²

// Scalar operations
auto doubled = meter_t{5} * 2.0;               // meter_t
auto halved = kilogram_t{10} / 2.0;            // kilogram_t
```

### Unit Casting

```cpp
// Convert between compatible units
auto length_m = meter_t{1000};
auto length_km = unit_cast<kilometer_t>(length_m);     // 1.0 km
auto length_mm = unit_cast<millimeter_t>(length_m);    // 1000000.0 mm

// Convert between chrono and pkr_units
auto chrono_time = std::chrono::seconds{30};
auto pkr_time = unit_cast<second_t>(chrono_time);
```

### Comparisons

```cpp
// Compare same dimensions (automatic conversion)
bool equal = meter_t{1000} == kilometer_t{1};          // true
bool less = gram_t{500} < kilogram_t{1};               // true

// Compare with tolerance for floating-point
bool approx_equal = almost_equal(meter_t{1.0000001}, meter_t{1.0}, 1e-6);
```

## Chrono Integration

### Overview

pkr_units provides bidirectional conversion with `std::chrono`, allowing use of both libraries together.

### Features

- Conversions when ratios match
- Automatic ratio arithmetic for different time scales
- Canonical ratio calculations
- Compile-time safety prevents chrono/pkr mixing errors

### Usage Examples

```cpp
#include <pkr_units/si_units.h>
#include <chrono>

using namespace pkr;
using namespace std::chrono;

// Convert chrono to pkr_units
auto chrono_duration = milliseconds{1500};
auto pkr_time = unit_cast<second_t>(chrono_duration);  // 1.5 seconds

// Convert pkr_units to chrono
auto pkr_duration = minute_t{2.5};
auto chrono_result = unit_cast<seconds>(pkr_duration); // 150 seconds

// Use in calculations
auto speed = meter_t{100} / unit_cast<second_t>(milliseconds{5000});
```

### Performance Characteristics

- Same ratio: ~1-2 nanoseconds
- Different ratios: ~5-10 nanoseconds
- No heap allocation or runtime type checking
- Fully constexpr compatible

## Numerical Methods

### Overview

The `pkr::numerical` namespace provides numerically stable operations and unit-aware algorithms for scientific computing. These operations return `unit_t` types with canonical ratios to maximize precision in complex calculations.

### Stable Operations

```cpp
#include <pkr_units/numerical.h>

using namespace pkr::numerical;

// Numerically stable arithmetic (returns unit_t with canonical ratios)
auto result = stable_add(meter_t{1}, millimeter_t{500});    // unit_t<..., ratio<1,1>, ...>
auto product = stable_multiply(force_t{10}, meter_t{5});    // unit_t<..., combined_ratio, ...>
auto quotient = stable_divide(energy_t{100}, second_t{2});  // unit_t<..., combined_ratio, ...>
```

### Transcendental Functions

```cpp
// Dimensionally constrained functions
auto exponential = exp(dimensionless_t{2.0});        // dimensionless_t
auto logarithm = log(dimensionless_t{10.0});         // dimensionless_t
auto square_root = sqrt(meter_t{4.0});               // unit_t<..., ratio<1,2>, length_dim>

// Compile-time dimensional checking
auto invalid = exp(meter_t{1.0});  // ❌ Compile error: exp requires dimensionless
```

### Newton-Raphson Method

```cpp
// Find roots of f(x) = 0 with automatic unit checking
template<typename UnitT, typename Function, typename Derivative>
UnitT newton_raphson(UnitT initial_guess, Function f, Derivative df,
                    double tolerance = 1e-10, int max_iterations = 100);

// Example: Find square root of 2
auto f = [](dimensionless_t x) { return x*x - dimensionless_t{2}; };
auto df = [](dimensionless_t x) { return dimensionless_t{2}*x; };
auto root = newton_raphson(dimensionless_t{1.5}, f, df);  // ≈ 1.414...
```

### Runge-Kutta Integration

```cpp
// Solve ODE dy/dx = f(x,y) with units preserved
template<typename TimeUnit, typename StateUnit, typename RHS>
StateUnit runge_kutta_step(RHS f, TimeUnit x, StateUnit y, TimeUnit h);

// Example: Exponential decay dy/dx = -k*y
auto decay_rate = [](second_t t, dimensionless_t y) {
    return -dimensionless_t{0.5} * y;  // 1/time units
};
auto result = runge_kutta_step(decay_rate, second_t{0}, dimensionless_t{1}, second_t{0.1});
```

### Benefits for Scientific Computing

1. **Automatic Unit Checking**: Functions must have dimensionally correct signatures
2. **Numerical Stability**: Canonical ratios prevent precision loss in complex calculations
3. **Type Safety**: Prevents mixing incompatible physical quantities
4. **Self-Documenting**: Function signatures clearly show physical meanings
5. **Performance**: No runtime unit checking overhead

## Measurements with Uncertainty Propagation

### Overview

pkr_units provides `measurement_t<UnitT>` for tracking measurements with uncertainties and automatic uncertainty propagation through arithmetic operations. This enables proper error analysis in scientific and engineering calculations.

### Features

- **Automatic Uncertainty Propagation**: Uses proper statistical methods (quadrature for addition/subtraction, relative uncertainties for multiplication/division)
- **Type-Safe Operations**: All operations maintain dimensional correctness
- **Mathematical Functions**: Uncertainty propagation through transcendental functions
- **Formatting Support**: Display measurements with uncertainty notation

### Basic Usage

```cpp
#include <pkr_units/measurements/measurement.h>

using namespace pkr;

// Create measurements with values and uncertainties
measurement_t<meter_t> length{5.0, 0.1};        // 5.0 ± 0.1 m
measurement_t<second_t> time{2.0, 0.05};        // 2.0 ± 0.05 s

// Calculate velocity with propagated uncertainty
auto velocity = length / time;  // 2.5 ± 0.13 m/s

// Automatic unit conversion during operations
measurement_t<centimeter_t> width{300.0, 5.0};  // 3.0 ± 0.05 m
auto area = length * width;  // 15.0 ± 0.58 m²
```

### Uncertainty Propagation Rules

```cpp
// Addition/Subtraction: uncertainties combine in quadrature (RSS)
// σ_total = √(σ₁² + σ₂²)
auto total_length = measurement_t<meter_t>{5.0, 0.1} + measurement_t<meter_t>{3.0, 0.2};
// Result: 8.0 ± 0.2236 m

// Multiplication/Division: relative uncertainties add
// δ(a×b)/(a×b) = δa/a + δb/b
auto power = measurement_t<watt_t>{100.0, 5.0} * measurement_t<second_t>{10.0, 0.5};
// Result: 1000.0 ± 55.9 J (relative uncertainties: 5% + 5% = 10%)
```

### Mathematical Functions

```cpp
#include <pkr_units/measurements/measurement_math.h>

using namespace pkr::math;

// Transcendental functions with uncertainty propagation
auto sqrt_result = sqrt(measurement_t<square_meter_t>{16.0, 1.0});  // 4.0 ± 0.125 m
auto exp_result = exp(measurement_t<scalar_t>{1.0, 0.1});           // 2.718 ± 0.272
auto sin_result = sin(measurement_t<radian_t>{0.0, 0.1});            // 0.0 ± 0.1
```

### Uncertainty Propagation Strategies

pkr_units supports two uncertainty propagation strategies, selected by including the appropriate header:

#### RSS (Root Sum Square) Strategy (Default)
```cpp
#include <pkr_units/measurements/measurement_math_rss.h>
```
- **Multiplication/Division**: Relative uncertainties add in quadrature: \(\delta_{total} = \sqrt{(\delta_1)^2 + (\delta_2)^2}\)
- **Addition/Subtraction**: Absolute uncertainties add in quadrature: \(\sigma_{total} = \sqrt{\sigma_1^2 + \sigma_2^2}\)
- **Functions**: Uses appropriate derivatives for uncertainty propagation
- **Best for**: Most scientific applications where uncertainties are independent

**Important**: For correlated measurements (e.g., squaring), use `square_rss()` instead of `multiply_rss(a, a)`.

#### Linear Strategy
```cpp
#include <pkr_units/measurements/measurement_math_linear.h>
```
- **All Operations**: Uses linear approximation: \(\delta f \approx |\frac{\partial f}{\partial x}| \delta x\)
- **Worst-case Bounds**: Provides conservative (upper bound) uncertainty estimates
- **Simpler**: Direct application of derivatives
- **Best for**: Simple cases, error bounds, or when computational efficiency is critical

Both strategies maintain dimensional correctness but use different function names to avoid conflicts:
- RSS functions have `_rss` suffix (e.g., `multiply_rss`, `divide_rss`)
- Linear functions use standard names (e.g., `multiply`, `divide`)

### Formatting and Output

```cpp
measurement_t<meter_t> length{5.123, 0.456};

// ASCII output: "5.12 +/- 0.46 m"
std::cout << std::format("{:.2f}", length) << std::endl;

// Wide character output: "5.12 ± 0.46 m"
std::wcout << std::format(L"{:.2f}", length) << std::endl;

// Scientific notation: "1.234567e+06 +/- 1.234567e+04 m"
measurement_t<meter_t> large_length{1.234567e6, 1.234567e4};
std::cout << std::format("{:e}", large_length) << std::endl;
```

### Real-World Example: Drag Force Calculation

```cpp
// Air density: 1.225 ± 0.005 kg/m³
measurement_t<kilogram_per_cubic_meter_t> density{1.225, 0.005};

// Velocity: 30.0 ± 0.5 m/s
measurement_t<meter_per_second_t> velocity{30.0, 0.5};

// Drag coefficient: 0.30 ± 0.02 (dimensionless)
measurement_t<scalar_t> drag_coeff{0.30, 0.02};

// Cross-sectional area: 2.5 ± 0.1 m²
measurement_t<square_meter_t> area{2.5, 0.1};

// Calculate drag force: F_d = 0.5 × ρ × v² × C_d × A
auto velocity_sq = velocity * velocity;
auto temp1 = density * velocity_sq;
auto temp2 = temp1 * drag_coeff;
auto temp3 = temp2 * area;
auto drag_force = measurement_t<scalar_t>{0.5, 0.0} * temp3;

// Result: 413.4 ± 59.6 N
std::cout << "Drag force: " << drag_force << std::endl;
```

### Benefits for Scientific Computing

1. **Proper Error Analysis**: Automatic uncertainty propagation using statistical methods
2. **Type Safety**: Dimensional correctness maintained throughout calculations
3. **Self-Documenting**: Measurement uncertainties are explicit in the code
4. **Comprehensive**: Supports all arithmetic and mathematical operations
5. **Standards Compliant**: Uses proper uncertainty propagation formulas

## Advanced Usage

### Custom Units

```cpp
// Define custom units using the framework
PKR_UNITS_DEFINE_UNIT(lightyear, length_dimension, std::ratio<9460730472580800, 1>, double)
PKR_UNITS_DEFINE_UNIT(solar_mass, mass_dimension, std::ratio<198847e24, 1>, double)

// Use custom units
auto distance = lightyear_t{4.24};  // Distance to Alpha Centauri
auto mass = solar_mass_t{1.0};      // One solar mass
```

### Performance Considerations

- **Zero runtime overhead** for unit operations
- **Compile-time computation** of all conversions
- **Optimal code generation** with modern compilers
- **Small binary size** (header-only, no runtime libraries)

### Error Handling

```cpp
// Division by zero throws at runtime
try {
    auto result = meter_t{10} / second_t{0};
} catch (const std::invalid_argument& e) {
    // Handle error
}

// Most errors caught at compile-time
auto invalid = meter_t{5} + second_t{3};  // Compile error
```

## API Reference

### Core Classes

- `unit_t<ValueType, Ratio, Dimensions>`: Generic unit type
- Named unit types: `meter_t`, `second_t`, `kilogram_t`, etc.
- `dimension_t`: Physical dimensions structure

### Key Functions

- `unit_cast<Target>(source)`: Convert between compatible units
- `almost_equal(a, b, tolerance)`: Floating-point comparison
- `stable_add/subtract/multiply/divide()`: Numerically stable operations
- `newton_raphson()`, `runge_kutta_step()`: Numerical methods

### Namespaces

- `pkr`: Main library namespace
- `pkr::numerical`: Stable numerical operations
- `pkr::units`: Predefined unit types
- `pkr::literals`: User-defined literals

## Examples

### Physics Simulation

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/numerical.h>

using namespace pkr;
using namespace pkr::numerical;

int main() {
    // Kinematic equation: distance = (1/2) * acceleration * time²
    auto acceleration = meter_per_second_squared_t{9.81};  // Gravity
    auto time = second_t{2.0};

    auto distance = 0.5 * acceleration * time * time;

    // Unit-aware result checking
    static_assert(std::is_same_v<decltype(distance), meter_t>,
                  "Result must be in meters");

    return 0;
}
```

### Engineering Calculations

```cpp
#include <pkr_units/si_units.h>

using namespace pkr;

int main() {
    // Ohm's law: V = I * R
    auto current = ampere_t{2.0};
    auto resistance = ohm_t{10.0};
    auto voltage = current * resistance;  // volt_t

    // Power: P = V * I
    auto power = voltage * current;  // watt_t

    // Energy over time: E = P * t
    auto time = hour_t{1.0};
    auto energy = power * time;  // joule_t

    return 0;
}
```

### Scientific Computing

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/numerical.h>

using namespace pkr;
using namespace pkr::numerical;

int main() {
    // Solve f(x) = x³ - 2x - 5 = 0 using Newton-Raphson
    auto f = [](dimensionless_t x) {
        return x*x*x - dimensionless_t{2}*x - dimensionless_t{5};
    };
    auto df = [](dimensionless_t x) {
        return dimensionless_t{3}*x*x - dimensionless_t{2};
    };

    auto root = newton_raphson(dimensionless_t{2.0}, f, df);

    // Result has correct dimensionless type
    static_assert(std::is_same_v<decltype(root), dimensionless_t>);

    return 0;
}
```

## Building and Installation

### System Requirements
- **Compiler**: C++20 compatible (GCC 10+, Clang 12+, MSVC 2022+)
- **Build System**: CMake 3.16+ with Ninja or Make
- **Package Manager**: Conan 2.0+ (optional, for dependency management)
- **Python**: 3.8+ (for build scripts)

### Build Configuration

The library supports multiple build configurations:

```bash
# Debug build with tests
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

# Release build (header-only, no compilation needed)
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Cross-platform build with Conan
conan install . --build missing
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
```

### Testing

```bash
# Build and run all tests
cmake --build build --target test

# Run specific test suite
ctest -R dimensional_analysis --output-on-failure

# Run performance benchmarks
cmake --build build --target benchmark
```

### Integration with CMake

For integrating into existing projects:

```cmake
# Add as subdirectory
add_subdirectory(path/to/pkr_units)

# Link to your target
target_link_libraries(your_target PRIVATE pkr_units)

# Or include headers directly
target_include_directories(your_target PRIVATE
    ${CMAKE_SOURCE_DIR}/path/to/pkr_units/sdk/include
)
```

### Package Managers

```bash
# Conan
conan install pkr_units/1.0.0@

# vcpkg (planned)
vcpkg install pkr-units
```

## Contributing

We welcome contributions! Please see our contributing guidelines for:
- Code style and formatting
- Testing requirements
- Documentation standards
- Release process

## License

pkr_units is released under the MIT License. See LICENSE file for details.

## Acknowledgments

- Built on C++20 features and modern template metaprogramming
- Inspired by existing units libraries (Boost.Units, PhysUnits)
- Thanks to the C++ community for feedback and contributions

## Appendix: Unit Types Reference

The library provides over 150 unit types derived from `details::unit_t`, all following the `_t` postfix naming convention (e.g., `meter_t`, `joule_t`).

### Base SI Units
- **Length**: `meter_t`, `attometer_t`, `femtometer_t`, `picometer_t`, `nanometer_t`, `micrometer_t`, `millimeter_t`, `centimeter_t`, `decimeter_t`, `decameter_t`, `hectometer_t`, `kilometer_t`, `megameter_t`, `gigameter_t`, `terameter_t`, `petameter_t`, `exameter_t`
- **Mass**: `kilogram_t`, `milligram_t`, `microgram_t`, `nanogram_t`, `picogram_t`, `femtogram_t`, `attogram_t`, `gram_t`, `metric_ton_t`, `tonne_t`
- **Time**: `second_t`, `millisecond_t`, `microsecond_t`, `nanosecond_t`, `kilosecond_t`, `hour_t`, `minute_t`, `day_t`
- **Electric Current**: `ampere_t`, `milliampere_t`, `microampere_t`, `nanoampere_t`, `kiloampere_t`
- **Temperature**: `kelvin_t`, `millikelvin_t`, `microkelvin_t`, `nanokelvin_t`, `kilokelvin_t`, `celsius_t`, `fahrenheit_t`
- **Amount of Substance**: `mole_t`, `millimole_t`, `micromole_t`, `nanomole_t`, `kilomole_t`
- **Luminous Intensity**: `candela_t`, `millicandela_t`, `microcandela_t`, `nanocandela_t`, `kilocandela_t`

### Derived SI Units
- **Area**: `square_meter_t`, `square_kilometer_t`, `square_centimeter_t`, `square_millimeter_t`
- **Volume**: `cubic_meter_t`, `cubic_kilometer_t`, `cubic_centimeter_t`, `cubic_millimeter_t`, `liter_t`, `milliliter_t`
- **Velocity**: `meter_per_second_t`, `kilometer_per_hour_t`, `centimeter_per_second_t`, `millimeter_per_second_t`, `miles_per_hour_t`, `feet_per_second_t`, `knots_t`
- **Acceleration**: `meter_per_second_squared_t`, `centimeter_per_second_squared_t`, `millimeter_per_second_squared_t`, `kilometer_per_second_squared_t`, `standard_gravity_t`
- **Force**: `newton_t`, `kilonewton_t`, `meganewton_t`, `millinewton_t`, `micronewton_t`
- **Energy/Power**: `joule_t`, `kilojoule_t`, `megajoule_t`, `millijoule_t`, `microjoule_t`, `watt_t`, `kilowatt_t`, `megawatt_t`, `milliwatt_t`, `microwatt_t`, `horsepower_t`
- **Pressure**: `pascal_t`, `kilopascal_t`, `hectopascal_t`, `megapascal_t`, `bar_t`, `atmosphere_t`, `psi_t`
- **Electrical**: `coulomb_t`, `kilocoulomb_t`, `millicoulomb_t`, `microcoulomb_t`, `nanocoulomb_t`, `picocoulomb_t`, `volt_t`, `kilovolt_t`, `megavolt_t`, `millivolt_t`, `microvolt_t`, `ohm_t`, `kilohm_t`, `megohm_t`, `gigohm_t`, `milliohm_t`, `microohm_t`, `farad_t`, `millifarad_t`, `microfarad_t`, `nanofarad_t`, `henry_t`, `millihenry_t`, `microhenry_t`, `nanohenry_t`
- **Magnetic**: `tesla_t`, `millitesla_t`, `microtesla_t`, `nanotesla_t`, `gauss_t`, `weber_t`, `milliweber_t`, `microweber_t`, `nanoweber_t`
- **Concentration**: `mole_per_cubic_meter_t`, `mole_per_liter_t`, `molar_t`, `millimolar_t`, `micromolar_t`, `nanomolar_t`, `picomolar_t`, `osmole_per_liter_t`, `milliosmole_per_liter_t`
- **Other Derived**: `becquerel_t`, `gray_t`, `sievert_t`, `katal_t`, `lumen_t`, `lux_t`, `hertz_t`, `radian_t`, `steradian_t`, `degree_t`, `gradian_t`

### Imperial Units
- **Length**: `inch_t`, `mil_t`, `foot_t`, `yard_t`, `fathom_t`, `rod_t`, `chain_t`, `furlong_t`, `mile_t`, `nautical_mile_t`
- **Mass**: `pound_t`, `ounce_t`, `stone_t`, `ton_t`
- **Force**: `pound_force_t`, `kip_t`
- **Velocity**: `miles_per_hour_t`, `feet_per_second_t`, `knots_t`

### Astronomical Units
- `micron_t`, `angstrom_t`, `au_t`, `light_year_t`, `parsec_t`

### Special/Other
- `josephson_t`

For the complete list, search the codebase with `grep ": public details::unit_t"` in the `sdk/include/pkr_units/` directory.</content>
<parameter name="filePath">c:\Data\projects\si_units\README.md
