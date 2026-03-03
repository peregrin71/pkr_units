# C++ Units Library Comparison

This document compares pkr_units with other popular C++ unit libraries.

## Feature Comparison Table

| Feature | pkr_units | Boost.Units | mp-units | nholthaus/units | bernedom/SI | PhysUnits |
|---------|-----------|-------------|----------|-----------------|-------------|-----------|
| **Language Standard** | C++20 | C++98+ | C++20 | C++11 | C++17 | C++11 |
| **Header-Only** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **Compile-Time Checking** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **Type-Safe Arithmetic** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **Dimensional Errors at Compile-Time** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **Base SI Units** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **Derived Units** | Extensive | Extensive | Extensive | Comprehensive | Moderate | Moderate |
| **Imperial Units** | ✓ | ✓ | ✓ | ✓ | ✗ | ✓ |
| **CGS Units** | ✓ | ✓ | ✓ | Limited | ✗ | Limited |
| **Astronomical Units** | ✓ | Limited | ✓ | ✗ | ✗ | ✗ |
| **Custom Unit Definitions** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **User-Defined Literals** | ✓ | ✓ | ✓ | ✓ | ✓ | Partial |
| **Temperature (Offset Handling)** | ✓ Tagged | ✓ Affine | ✓ Affine | ✓ Affine | ✗ | Limited |
| **Measurements with Uncertainty** | ✓ | ✗ | ✓ | ✗ | ✗ | ✗ |
| **Tagged Units (Different Semantics)** | ✓ | ✗ | ✗ | ✗ | ✗ | ✗ |
| **Complex Value Types** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **std::format Support** | ✓ | ✗ | ✓ | Limited | ✗ | ✓ |
| **std::iostream (<<, >>)** | ✓ Output / ✓ Parsing Design | ✓ | ✓ | ✓ | ✗ | ✓ |
| **Constants (Physical)** | ✓ | Limited | ✓ | ✗ | ✗ | Partial |
| **Numerical Helpers (Newton-Raphson, etc)** | ✓ | ✗ | ✓ | ✗ | ✗ | ✗ |
| **std::chrono Integration** | ✓ | ✓ | ✓ | ✓ | ✗ | ✓ |
| **Namespace Customization** | ✓ | ✗ | Limited | ✗ | ✗ | ✗ |
| **Unit Conversion (unit_cast)** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **Zero Runtime Overhead** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| **LHS Type Preservation (Add/Sub)** | ✓ | ✓ | Limited | ✓ | ✓ | ✓ |
| **Computer Science Units (bytes, FLOPs)** | ✓ Tagged | ✗ | ✗ | ✗ | ✗ | ✗ |
| **Actively Maintained** | ✓ | ✓ | ✓ | Moderate | Active | Inactive |

---

## Detailed Library Descriptions

### pkr_units
**Key Strengths:**
- Modern C++20 with advanced type system features
- Measurements with uncertainty propagation built-in
- Tagged units for semantically distinct quantities (computer science units, temperature)
- Physical constants as typed units
- Numerical helpers (stable arithmetic, Newton-Raphson, Runge-Kutta)
- Customizable namespace
- Full std::format support
- Comprehensive predefined units (SI, Imperial, CGS, Astronomical)

**Key Limitations:**
- Requires C++20 (higher barrier than older alternatives)
- Smaller ecosystem compared to Boost

**Design Roadmap:**
- [PARSING_DESIGN.md](../design/PARSING_DESIGN.md) outlines a novel return-value specialization approach for unit parsing where `parse_unit<kilometer_t>("5.2 km")` returns the exact derived type, not a generic unit template.

**Best For:**
- Scientific/engineering applications requiring uncertainty quantification
- Systems mixing different unit domains (SI, Imperial, CGS)
- Applications needing computational units with distinct semantics
- Projects requiring flexible parsing with type-safe specialization

---

### Boost.Units
**Key Strengths:**
- Very mature and widely adopted (Boost 1.36+)
- Excellent documentation and extensive use in production
- Works with older C++ standards (C++98)
- Deep integration with Boost ecosystem
- Extremely flexible and customizable
- Well-tested in large-scale applications

**Key Limitations:**
- Complex syntax due to older C++ idioms
- Steep learning curve for complex dimensional analysis
- No built-in measurements or uncertainty
- Compilation times can be long
- Less elegant API compared to modern alternatives

**Best For:**
- Projects already using Boost
- Legacy codebases
- Applications requiring maximum compatibility

---

### mp-units
**Key Strengths:**
- Modern C++20 design with clean API
- Comprehensive unit catalog including astronometrical units
- Strong focus on ISO 80000 standards compliance
- Excellent error messages in modern compilers
- Built-in measurements and quantity types
- Advanced quantity point support (absolute vs. relative)
- Active development with modern language features

**Key Limitations:**
- Requires recent C++20 support
- Still relatively newer (less production adoption than Boost)
- Pre-compiled library option (not pure header-only in all cases)

**Best For:**
- New projects targeting modern C++ standards
- Standards-compliant dimensional analysis
- Projects requiring quantity point semantics

---

### nholthaus/units
**Key Strengths:**
- Simple, intuitive API
- Good documentation with examples
- Reasonable middle ground between power and simplicity
- C++11 compatible (broader support)
- Clear operator overloading semantics

**Key Limitations:**
- Doesn't handle temperature with offsets elegantly
- More limited derived units catalog
- Community smaller than Boost
- Less active development

**Best For:**
- High school/university educational projects
- Prototyping
- Projects needing simple, readable code over power

---

### bernedom/SI
**Key Strengths:**
- Clean, minimal design focused on SI units
- Compile-time dimensional analysis with zero runtime overhead
- Header-only, template-based
- Small codebase (easy to understand and modify)

**Key Limitations:**
- SI-only (no Imperial, CGS, or other systems built-in)
- No measurements or uncertainty handling
- Limited documentation
- Smaller community
- No special handling for temperature offsets
- Limited derived units

**Best For:**
- Physics simulations using purely SI units
- Educational purposes
- Projects needing minimal dependencies

---

### PhysUnits
**Key Strengths:**
- Focused on physics-specific applications
- Good support for common physics units
- Useful for scientific computing

**Key Limitations:**
- Project appears inactive (not recently maintained)
- Limited documentation
- Smaller ecosystem
- No modern C++ features
- Not recommended for new projects

**Best For:**
- Legacy systems only
- Reference implementation for physics units

---

## Comparison Summary

### For Maximum Features and Flexibility: **mp-units** or **pkr_units**
- Both are modern (C++20), well-maintained, and feature-rich
- **mp-units**: Better for standards compliance and broad scientific use
- **pkr_units**: Better for uncertainty/measurement propagation and tagged units

### For Production Systems with Legacy Requirements: **Boost.Units**
- Most mature, tested in billions of lines of production code
- Sacrifice modern API elegance for compatibility and stability

### For Educational Use: **nholthaus/units** or **bernedom/SI**
- Simple, readable code
- Good for learning unit library concepts
- nholthaus/units: More complete but slightly more complex
- bernedom/SI: Minimal and SI-focused

### For Scientific/Engineering with Measurements: **pkr_units**
- Only solution with built-in uncertainty propagation
- Computer science units with semantic tags
- More comprehensive than alternatives

---

## Implementation Approaches

### Dimensional Representation
- **pkr_units, bernedom/SI, nholthaus/units**: Dimension as compile-time constant/template parameter
- **Boost.Units**: Complex template metaprogramming with dimension hierarchies
- **mp-units**: Advanced template system with quantity concepts

### Type Safety
All libraries achieve type safety, but:
- **mp-units**: Most rigorous with quantity vs. quantity_point semantics
- **pkr_units**: Strong typing with LHS preservation and tags
- **Boost.Units**: Maximum flexibility at cost of complexity
- **nholthaus/units**: Simple, direct approach

### Compilation
- **pkr_units, mp-units**: Modern C++20 templates (faster compilation than Boost)
- **Boost.Units**: Heavy template metaprogramming (slower compilation)
- **nholthaus/units, bernedom/SI**: Minimal templates (fastest compilation)

---

## Enhancement Opportunities for pkr_units

The following features would further strengthen pkr_units' position as a comprehensive units library:

### 1. **Serialization Support (JSON/XML/YAML)**
- JSON serialization/deserialization of measurements with units
- Preserve unit types when round-tripping through APIs
- Integration with popular C++ JSON libraries (nlohmann/json, RapidJSON)
- **Impact**: Critical for REST API development, data interchange

### 2. **Range/Collections Support**
- `std::ranges` compatibility for containers of measurements
- Aggregate operations: mean, sum, min, max with proper unit handling
- Statistical functions: standard deviation, variance for measurements
- **Impact**: Simplifies data analysis workflows

### 3. **Higher-Order Derivatives**
- Jerk (rate of change of acceleration)
- Snap, crackle, pop (higher derivatives)
- Easy expression of physics equations involving multiple derivatives
- **Impact**: More complete physics toolkit

### 4. **Unit Inference and Type Deduction**
- Automatic type inference for complex expressions
- Compile-time dimensionality checking without explicit type specifications
- Symbolic algebra for derived unit simplification
- **Impact**: Reduced verbosity, fewer template instantiations

### 5. **Error Messages with Unit Suggestions**
- When type mismatch occurs, suggest valid unit conversions
- Compile-time error messages that hint at correct usage
- Constraint violation explanations
- **Impact**: Improves developer experience, reduces debugging time

### 6. **Quantity History/Time Series**
- Built-in measurements with timestamps
- Interpolation between measurements respecting units
- Time-derivative operations on series data
- **Impact**: Perfect for sensor data processing

### 7. **Quantum and Relativistic Units**
- Planck units, natural units
- Spacetime interval calculations
- Lorentz invariant expressions
- **Impact**: Expands into modern physics


