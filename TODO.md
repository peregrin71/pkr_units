# SI Units Library - Development Roadmap

Build
- [ ] Make Conan profiles single source of truth for compiler configuration

### Formatting
- [] Vectors of units
- [] Vectors of measurments
- [] Matrices of units
- [] Matrices of measurements

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


### Packaging
- [ ] Create package config files
- [ ] Add installation targets
- [ ] Support header-only build option
- [ ] Create Conan package (conanfile.py exists, needs completion)
- [ ] Add vcpkg support

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

