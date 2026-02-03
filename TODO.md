# SI Units Library - Development Roadmap

[ ] Each header file should include what it needs, this file misses an include for <string_view> for example... and others may include too much



## Build System & Infrastructure

### Completed
- [x] MSVC compiler support with full test suite passing (367 tests: 366 PASSED, 1 known precision issue)
- [x] GTest integration with Conan
- [x] CMake build configuration
- [x] Separate build profiles for MSVC and Clang
- [x] Remove stale compiler flags from Clang profile

### GitHub Actions CI/CD (High Priority)
- [x] Create GitHub Actions workflow (`.github/workflows/ci.yml` exists)
  - [x] Windows runner: MSVC build
  - [x] Ubuntu runner: GCC build
  - [x] Ubuntu runner: Clang build
  - [ ] macOS runner (optional): Native Clang build
  - [x] Matrix strategy for Debug/Release configurations
- [x] Validation in CI
  - [x] Run full test suite on all platforms
  - [ ] Generate test reports (currently just ctest output) -> code coverage
  - [x] Flag failures to PR (fail-fast: false)
  - [x] use libc++ for Clang on Linux if pipeline succeeds (for better Clang integration)
  - [ ] Add UBSan to debug builds for undefined behavior detection
- [x] Branching Strategy
  - [x] PR workflow: triggers on pull_request to main, development branches
  - [x] CI validation required before merge to master (workflow exists but strategy not fully documented)
  - [x] Master always in releasable state (workflow ensures this)
- [ ] Make Conan profiles single source of truth for compiler configuration

---

## 1. Complete Basic Units

### Length Units

- [x] meter
- [x] kilometer
- [x] millimeter
- [x] centimeter
- [x] micrometer
- [x] nanometer
- [x] decimeter
- [x] hectometer

### Mass Units
- [x] kilogram
- [x] gram
- [x] milligram
- [x] microgram
- [x] nanogram
- [x] picogram
- [x] metric_ton (tonne)

### Time Units
- [x] second
- [x] millisecond
- [x] microsecond
- [x] nanosecond
- [x] minute
- [x] hour
- [x] day
- [x] week
- [x] month 
- [x] year 

### Angle Units
- [x] radian
- [x] degree
- [x] gradian
- [x] hms_archour
- [x] hms_arcminute
- [x] hms_arcsecond
- [x] dms_degree
- [x] dms_arcminute
- [x] dms_arcsecond
- [x] HMS/DMS type for formatting

### Solid Angle Units (star radians)
- [x] implement as 9th dimension (steradian_t)
- [x] add to dimension tracking system

### Electric Current Units
- [x] ampere
- [x] milliampere
- [x] microampere
- [x] nanoampere
- [x] kiloampere

### Temperature Units
- [x] kelvin
- [x] millikelvin
- [x] microkelvin
- [x] nanokelvin
- [x] kilokelvin
- [x] celsius (conversion handling)
- [x] fahrenheit (conversion handling)

### Amount of Substance Units
- [x] mole
- [x] millimole
- [x] micromole
- [x] nanomole
- [x] kilomole

### Luminous Intensity Units
- [x] candela
- [x] millicandela
- [x] microcandela
- [x] nanocandela
- [x] kilocandela

---

## 2. Derived Units

### Mechanical
- [x] Area (length²) with dedicated square_meter_t, square_kilometer_t, etc.
- [x] Volume (length³) with dedicated cubic_meter_t, cubic_kilometer_t, etc.
- [x] Velocity (length/time) with dedicated meter_per_second_t, kilometer_per_hour_t, etc.
- [x] Acceleration (length/time²)
- [x] Force (mass × length/time²) - Newton
- [x] Energy (force × length) - Joule
- [x] Electronvolt units: exact conversion path or improved ratio handling (std::ratio limits)
- [x] Power (energy/time) - Watt
- [x] Pressure (force/area) - Pascal

### Electrical
- [x] Electric Charge (ampere × time) - Coulomb
- [x] Electric Potential (energy/charge) - Volt
- [x] Electric Resistance (potential/current) - Ohm
- [x] Capacitance (charge/potential) - Farad
- [x] Inductance (potential × time/current) - Henry
- [x] Magnetic Flux (potential × time) - Weber
- [x] Magnetic Flux Density (force/(current × length)) - Tesla

### Thermal
- [ ] Specific Heat Capacity (energy/(mass × temperature))
- [ ] Thermal Conductivity

### Viscosity
- [x] Dynamic viscosity (Pa*s)
- [x] Kinematic viscosity (m^2/s)

### Chemical
- [x] Concentration (molar) - mol/m³
- [x] Concentration (mass) - kg/m³
- [x] Molarity - mol/L

### Photometry
- [x] Luminous Flux (candela × steradian) - Lumen
- [x] Luminous Intensity (candela × steradian) - relationship documentation
- [x] Illuminance (candela × steradian / length²) - Lux

### Radiometry
- [x] Radiant Flux (power) - Watts
- [x] Radiant Intensity (power / steradian) - Watts per Steradian
- [x] Radiance (power / (area × steradian)) - Watts per Square Meter per Steradian
- [x] Irradiance (power / area) - Watts per Square Meter

---

## 3. String Formatting and Parsing

### Formatting
- [x] Basic output formatting (partial implementation exists)
- [x] Format units with proper SI symbols (m, kg, s, etc.)
- [x] Format with exponents (m², m³, m/s)
- [x] Format with metric prefixes (km, mm, μm)
- [x] Support for std::format with custom format specs
- [x] Pretty printing with Unicode symbols (μ, Ω, Å, etc.)

---

## 4. Conversion and Cast Operators

### Unit Conversion
- [x] Implicit conversion for compatible ratios (same dimension, different scales)

### Type Conversions
- [x] `double` to unit_t (explicit)
- [x] unit_t to `double` (via `.value()` - already done)

### Temperature Conversions
- [x] Celsius to Kelvin with offset handling
- [x] Fahrenheit to Kelvin with offset handling

---

## 5. Extended Unit Systems

### CGS Units
- [x] Gauss (magnetic flux density)
- [x] Dyne (force)
- [x] Erg (energy)
- [x] Barye (pressure)
- [x] Gal (acceleration)
- [x] Maxwell (magnetic flux)
- [x] Poise (dynamic viscosity)
- [x] Stokes (kinematic viscosity)
- [x] Statcoulomb (charge)
- [x] Oersted (magnetic field strength)
- [ ] Add more CGS units (abvolt, abampere, abohm, etc.)

### Imperial Units
- [x] inch_t, foot_t, yard_t, mile_t
- [x] pound_t (mass), ounce_t
- [x] Fahrenheit
- [x] Conversion factors to SI
- [x] Integration with SI arithmetic

### Astronomical Units
- [x] Astronomical Unit (AU)
- [x] Light-year
- [x] Parsec
- [ ] Solar masses
- [ ] Planck units (advanced)

---

## 6. Advanced Features

### Dimensionless Quantities
- [x] Support for scalar/dimensionless units
- [x] Named dimensionless quantities (e.g., percentage, ratio, decibel)

### Constants
- [x] Physical constants (Planck constant, Boltzmann constant, etc.)
- [x] Unit support for constants
- [x] Pre-defined quantity constants

### Compound Operations
- [x] Power function for units (e.g., `pow<2>(meter)` for area)
- [x] Implemented in `sdk/include/pkr_units/impl/cast/unit_pow.h`
- [ ] Square root and other roots
- [ ] Properly typed results

---

## 7. Testing

### Unit Tests
- [ ] Complete test coverage for all basic SI units
- [ ] Test all derived units
- [ ] Test string parsing and formatting
- [ ] Test conversions and casts
- [ ] Test edge cases (zero, negative, very large/small values)
- [ ] Test constexpr evaluation
- [ ] Test exception handling

### Benchmarks
- [ ] Performance benchmarks vs. hand-written doubles
- [ ] Compile-time performance analysis
- [ ] Binary size analysis
- [ ] Memory layout verification

### Integration Tests
- [ ] Real-world use cases (physics simulations)
- [x] Cross-compiler testing (GCC, Clang, MSVC)
- [ ] Different platforms (Linux, Windows, macOS)

---

## 8. Documentation

### User Documentation
- [x] Quick start guide
- [ ] API reference for all units
- [ ] Examples for common operations
- [ ] Best practices guide
- [ ] FAQ and troubleshooting

### Technical Documentation
- [x] Design document (DESIGN.md completed)
- [x] Assembly optimization analysis (completed)
- [ ] Implementation internals guide
- [x] Extension guide for adding new units
- [ ] Performance characteristics document

### Code Examples
- [ ] Physics simulation example
- [ ] Engineering calculation example
- [ ] Financial/scientific computing example
- [ ] Unit conversion examples

---

## 9. Code Quality and Refactoring

### Code Review
- [ ] Review all template instantiations
- [ ] Check for potential compile-time explosion
- [ ] Verify optimal inlining
- [ ] Check for code duplication

### Optimization Opportunities
- [ ] Profile compile-time performance
- [ ] Optimize template specialization
- [ ] Review arithmetic helper efficiency
- [ ] Consider caching compiled unit types

### Documentation in Code
- [ ] Add inline documentation for complex templates
- [ ] Document template specialization patterns
- [ ] Clarify NTTP usage
- [ ] Add examples in code comments

---

## 10. Build and Packaging

### CMake Improvements
- [ ] Add feature detection (C++20 required)
- [ ] Create configuration options for optional features
- [ ] Add subdirectory builds for components
- [ ] Improve test discovery and organization

### Packaging
- [ ] Create package config files
- [ ] Add installation targets
- [ ] Support header-only build option
- [ ] Create Conan package (conanfile.py exists, needs completion)
- [ ] Add vcpkg support

### CI/CD
- [x] GitHub Actions workflow
- [x] Multi-compiler testing (GCC, Clang, MSVC)
- [ ] Multi-platform testing (Linux, Windows, macOS)
- [ ] Code coverage reporting
- [ ] Performance regression testing

---

## 11. Library Integration

### Standard Library Integration
- [ ] Ensure compatibility with std::string, std::format
- [ ] Support with std::cout operators
- [ ] Integration with algorithms (std::sort with custom comparators, etc.)

### Third-Party Integration
- [ ] Eigen/Armadillo integration (for linear algebra)
- [ ] Python bindings (pybind11)
- [ ] MATLAB/Octave compatibility considerations

---

## 12. Known Issues and TODOs

### From Code Comments
- [ ] TODO: model if a value in a dimension can be negative or not (dimension.h)
- [ ] TODO: move helper to separate formatting header (si_unit.h)
- [ ] TODO: add template-aware unit_cast specializations for formatting-only units (e.g., `decibel_power_t<T>`, `decibel_amplitude_t<T>`) and update tests that currently rely on `unit_cast` behavior for these types (#decibel-unit-cast)

### Design Decisions to Revisit
- [x] Comparison operators are supported
- [x] Offset-based temperature conversions handled via affine traits
- [ ] Should implicit conversions be allowed, or always explicit^2

### Low Priority: String Parsing (Future Enhancement)
- [ ] Parse strings like "5.0 meters"
- [ ] Parse strings like "1.5 km"
- [ ] Parse strings like "10 m/s"
- [ ] Parse strings like "100 m²"
- [ ] Handle invalid input gracefully

---

## Priority Levels

### High Priority (MVP)
1. Complete all 7 basic SI units with all metric prefixes
2. Essential derived units (area, volume, velocity, force)
3. Proper string formatting
4. Unit conversion operators
5. Comprehensive test coverage

### Medium Priority (Production Ready)
1. Imperial unit system
2. Advanced derived units
3. Temperature conversions
4. Named quantities system
5. Physical constants

### Low Priority (Enhancement)
1. Expand CGS unit system
2. Astronomical units
3. Python bindings
4. Extended documentation and examples
5. Performance optimizations

---

## Completion Tracking

| Category | Status | % Complete | Notes |
|----------|--------|-----------|-------|
| Basic SI Units | Complete | 100% | All listed base units implemented |
| Derived Units | In Progress | 85% | Thermal units added; others still missing |
| String Formatting | In Progress | 70% | Formatting done, parsing not implemented |
| Conversion/Casts | In Progress | 60% | unit_cast done; si_cast and value-type casts missing |
| Testing | In Progress | 70% | Broad coverage, still missing parsing/edge cases |
| Documentation | In Progress | 65% | README/design done; API reference still missing |
| Code Quality | In Progress | 90% | Ongoing review/cleanup items remain |
| Build System | In Progress | 80% | CI works; packaging/coverage/UBSan missing |

---

## Next Immediate Steps

1. **String Parsing**
   - Parse basic unit strings ("5.0 m", "10 m/s")
   - Add parsing tests and edge cases

2. **Conversion Framework**
   - Implement `si_cast<>`
   - Add value-type conversions (double <-> float)
   - Clarify/lock temperature arithmetic behavior

3. **CI Quality**
   - Add coverage reporting
   - Add UBSan to debug builds (where compatible)

