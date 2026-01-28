# SI Units Library - Development Roadmap

[ ] Each header file should include what it needs, this file misses an include for <string_view> for example... and others may include too much
[ ] 



## Build System & Infrastructure

### Completed
- [x] MSVC compiler support with full test suite passing (367 tests: 366 PASSED, 1 known precision issue)
- [x] GTest integration with Conan
- [x] CMake build configuration
- [x] Separate build profiles for MSVC and Clang
- [x] Remove stale compiler flags from Clang profile

### In Progress / Known Issues
  - Remove compiler version duplication between profiles and CI workflow
  - Centralize CC/CXX environment variables in profile [buildenv] sections
  - Eliminate cmake_extra_flags overrides of profile generators
  - Simplify CI matrix to reference profile settings only
- [ ] Fix Clang build issue (Windows ABI/GTest linking - linker undefined references to testing::Test symbols)
- [ ] Fix floating-point precision test (SiMassTest.add_very_different_scales)

### GitHub Actions CI/CD (High Priority)
- [x] Create GitHub Actions workflow (`.github/workflows/ci.yml` exists)
  - [x] Windows runner: MSVC build
  - [x] Ubuntu runner: GCC build
  - [x] Ubuntu runner: Clang build
  - [ ] macOS runner (optional): Native Clang build
  - [x] Matrix strategy for Debug/Release configurations
- [x] Validation in CI
  - [x] Run full test suite on all platforms
  - [ ] Generate test reports (currently just ctest output)
  - [x] Flag failures to PR (fail-fast: false)
  - [ ] use libc++ for Clang on Linux if pipeline succeeds (for better Clang integration)
  - [ ] Add UBSan to debug builds for undefined behavior detection
- [x] Branching Strategy
  - [x] PR workflow: triggers on pull_request to main, development branches
  - [x] CI validation required before merge to master (workflow exists but strategy not fully documented)
  - [x] Master always in releasable state (workflow ensures this)
- [ ] Make Conan profiles single source of truth for compiler configuration

---

## 1. Complete Basic SI Units

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
- [x] megagram (tonne)

### Time Units
- [x] second
- [x] millisecond
- [x] microsecond
- [x] nanosecond
- [ ] minute
- [ ] hour
- [ ] day
- [ ] week
- [ ] month (estimated)
- [ ] year (estimated)

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
- [ ] celsius (conversion handling)
- [ ] fahrenheit (conversion handling)

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
- [ ] Area (length²) with dedicated square_meter_t, square_kilometer_t, etc.
- [ ] Volume (length³) with dedicated cubic_meter_t, cubic_kilometer_t, etc.
- [ ] Velocity (length/time) with dedicated meter_per_second_t, kilometer_per_hour_t, etc.
- [ ] Acceleration (length/time²)
- [ ] Force (mass × length/time²) - Newton
- [ ] Energy (force × length) - Joule
- [ ] Electronvolt units: exact conversion path or improved ratio handling (std::ratio limits)
- [ ] Power (energy/time) - Watt
- [ ] Pressure (force/area) - Pascal

### Electrical
- [ ] Electric Charge (ampere × time) - Coulomb
- [ ] Electric Potential (energy/charge) - Volt
- [ ] Electric Resistance (potential/current) - Ohm
- [ ] Capacitance (charge/potential) - Farad
- [ ] Inductance (potential × time/current) - Henry
- [ ] Magnetic Flux (potential × time) - Weber
- [ ] Magnetic Flux Density (force/(current × length)) - Tesla

### Thermal
- [ ] Specific Heat Capacity (energy/(mass × temperature))
- [ ] Thermal Conductivity

### Chemical
- [ ] Concentration (molar) - mol/m³
- [ ] Concentration (mass) - kg/m³
- [ ] Molarity - mol/L

---

## 3. String Formatting and Parsing

### Formatting
- [ ] Basic output formatting (partial implementation exists)
- [ ] Format units with proper SI symbols (m, kg, s, etc.)
- [ ] Format with exponents (m², m³, m/s)
- [ ] Format with metric prefixes (km, mm, μm)
- [ ] Support for std::format with custom format specs
- [ ] Pretty printing with Unicode symbols (μ, Ω, Å, etc.)

---

## 4. Conversion and Cast Operators

### Unit Conversion
- [x] Implicit conversion for compatible ratios (same dimension, different scales)
- [ ] Explicit conversion function: `si_cast<target_unit>(value)`
- [ ] Conversion validation (prevent invalid unit combinations)
- [ ] Runtime conversion with value checking

### Type Conversions
- [ ] `double` to unit_t (explicit)
- [ ] unit_t to `double` (via `.value()` - already done)
- [ ] Between different value types (double ↔ float)
- [ ] Conversion tracking for dimensional analysis

### Temperature Conversions
- [ ] Celsius to Kelvin with offset handling
- [ ] Fahrenheit to Kelvin with offset handling
- [ ] Properly handle offset-based conversions in arithmetic

---

## 5. Extended Unit Systems

### Imperial Units
- [ ] inch_t, foot_t, yard_t, mile_t
- [ ] pound_t (mass), ounce_t
- [ ] Fahrenheit
- [ ] Conversion factors to SI
- [ ] Integration with SI arithmetic

### Astronomical Units
- [ ] Astronomical Unit (AU)
- [ ] Light-year
- [ ] Parsec
- [ ] Solar masses
- [ ] Planck units (advanced)

### CGS Units (optional)
- [ ] Centimeter-Gram-Second system
- [ ] Conversion to SI
- [ ] Dyne, Erg, etc.

---

## 6. Advanced Features

### Quantity System
- [ ] Named quantities (e.g., `distance`, `speed`, `mass`)
- [ ] Distinguish between scalar and vector quantities
- [ ] Quantity validation framework

### Dimensionless Quantities
- [x] Support for scalar/dimensionless units
- [ ] Named dimensionless quantities (e.g., percentage, ratio, decibel)

### Constants
- [ ] Physical constants (Planck constant, Boltzmann constant, etc.)
- [ ] Unit support for constants
- [ ] Pre-defined quantity constants

### Compound Operations
- [ ] Power function for units (e.g., `pow<2>(meter)` for area)
- [x] Already implemented in si_pow.h
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
- [ ] Cross-compiler testing (GCC, Clang, MSVC)
- [ ] Different platforms (Linux, Windows, macOS)

---

## 8. Documentation

### User Documentation
- [ ] Quick start guide
- [ ] API reference for all units
- [ ] Examples for common operations
- [ ] Best practices guide
- [ ] FAQ and troubleshooting

### Technical Documentation
- [x] Design document (DESIGN.md completed)
- [x] Assembly optimization analysis (completed)
- [ ] Implementation internals guide
- [ ] Extension guide for adding new units
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
- [ ] GitHub Actions workflow
- [ ] Multi-compiler testing (GCC, Clang, MSVC)
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

### Design Decisions to Revisit
- [ ] Should comparison operators be supported? (Currently intentionally omitted)
- [ ] How to handle temperature offset-based conversions elegantly?
- [ ] Should implicit conversions be allowed, or always explicit?

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
1. CGS unit system
2. Astronomical units
3. Python bindings
4. Extended documentation and examples
5. Performance optimizations

---

## Completion Tracking

| Category | Status | % Complete | Notes |
|----------|--------|-----------|-------|
| Basic SI Units | 🟡 In Progress | 40% | 4 of 7 base units, partial metric prefixes |
| Derived Units | 🔴 Not Started | 5% | Partial implementation exists |
| String Formatting | 🟡 In Progress | 30% | Basic formatting exists, needs completion |
| Conversion/Casts | 🟡 In Progress | 20% | Implicit conversion works, explicit operators needed |
| Testing | 🟡 In Progress | 50% | Good test foundation, needs extended coverage |
| Documentation | 🟡 In Progress | 60% | Design doc complete, user docs needed |
| Code Quality | ✅ Complete | 95% | Excellent, minor refinements possible |
| Build System | 🟡 In Progress | 70% | CMake works, packaging needs work |

---

## Next Immediate Steps

1. **Complete Basic SI Units** (Week 1-2)
   - Add centimeter, decimeter, hectometer for length
   - Add milligram through megagram for mass
   - Add ampere and derived units for current

2. **Implement Essential Derived Units** (Week 2-3)
   - Area (square_meter_t, etc.)
   - Volume (cubic_meter_t, etc.)
   - Velocity (meter_per_second_t, etc.)
   - Force (newton_t)

3. **Complete String Formatting** (Week 3-4)
   - Implement full std::format support
   - Add parsing capability
   - Write formatting tests

4. **Add Conversion Framework** (Week 4-5)
   - Implement si_cast<> template
   - Add explicit conversion operators
   - Test edge cases

5. **Expand Test Coverage** (Ongoing)
   - Add tests for each new unit
   - Integration tests
   - Performance benchmarks
