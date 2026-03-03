# Ostream Formatting Design

## Overview

This document defines the complete design for `std::ostream` formatting support across the SI Units library, including both `unit_t` types and `measurement_t` types. It establishes consistency, extensibility, and a clear path for `std::format` and `operator<<` integration.

---

## Current State

### Implemented
- `std::formatter` specializations for base and derived `unit_t` types (numeric value + dimension symbol)
- Generic `operator<<` overload for all `unit_t` types in `std::` namespace
- Character-type aware symbol selection (char, wchar_t, char8_t)
- Format specifier delegation to underlying numeric formatter
- `operator<<` for `measurement_lin_t` and `measurement_rss_t` (basic implementation)

### Missing
- **`std::formatter` specializations for `measurement_t` types** (only `operator<<` exists)
- Consistent format specifier handling across measurement types
- Comprehensive wide-character support for measurements
- Clear design documentation for formatting behavior and extensibility

---

## Design Goals

1. **Consistency**: All unit-related types (`unit_t`, `measurement_lin_t`, `measurement_rss_t`) have parity in formatting capabilities
2. **Flexibility**: Format specifiers (precision, width, etc.) apply consistently to both value and uncertainty
3. **Character Type Distinction**: Separate ASCII (char) from wide character (wchar_t) formatting symbols via `symbol` and `w_symbol` static members
4. **Seamless Character Stream Support**: Each formatter specialization automatically selects the correct symbol type for its `CharT` parameter
5. **Extensibility**: User-defined derived units and measurements format correctly without additional work
6. **Zero Overhead**: Formatting is compile-time where possible; runtime formatting is efficient
7. **Clear Intent**: Output clearly distinguishes measurements from raw values

---

## 1. Unit Formatting (`unit_t` types)

### 1.1 Current Implementation

#### `std::formatter` Specializations

Two specializations exist (in `unit_formatter.h`):

**Base Units** (via `is_base_pkr_unit_c`):
```cpp
template <is_base_pkr_unit_c T, typename CharT>
struct formatter<T, CharT>
{
    std::formatter<typename T::value_type, CharT> value_formatter;

    constexpr auto parse(ParseContext& ctx) 
    { 
        return value_formatter.parse(ctx); 
    }

    auto format(const T& unit, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(unit.value(), ctx);
        
        // Build dimension symbol (e.g., "kg*m*s^-2" for force)
        impl::format_buffer<CharT> buf;
        build_dimension_symbol_to_buffer(buf, unit.dimension);
        
        *out++ = static_cast<CharT>(' ');
        return std::copy(buf.begin(), buf.end(), out);
    }
};
```

**Derived Units** (via `is_derived_pkr_unit_c`):
```cpp
template <is_derived_pkr_unit_c T, typename CharT>
struct formatter<T, CharT>
{
    std::formatter<typename T::value_type, CharT> value_formatter;

    constexpr auto parse(ParseContext& ctx) 
    { 
        return value_formatter.parse(ctx); 
    }

    auto format(const T& unit, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(unit.value(), ctx);
        
        // Select symbol based on character type
        std::basic_string_view<CharT> sym;
        if constexpr (std::is_same_v<CharT, wchar_t>)
            sym = T::w_symbol;
        else
            sym = T::symbol;
        
        *out++ = static_cast<CharT>(' ');
        return std::copy(sym.begin(), sym.end(), out);
    }
};
```

#### Generic `operator<<`

```cpp
template <typename CharT, typename Traits, typename T>
    requires is_pkr_unit_c<T>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os, 
    const T& unit)
{
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        std::wstring formatted = std::format(L"{}", unit);
        os << formatted;
    }
    else
    {
        std::string formatted = std::format("{}", unit);
        os << formatted;
    }
    return os;
}
```

### 1.2 Output Format

Units output as: `<value> <symbol>`

**Examples:**
- `meter_t<double>{5.0}` → `"5 m"`
- `kilometer_per_hour_t<float>{100.0}` → `"100 km/h"`
- `kilogram_t<double>{9.81}` → `"9.81 kg"`
- Base dimension composite: `(kilogram_t * meter_t / (second_t * second_t)){10.0}` → `"10 kg*m*s^-2"`

### 1.3 Format Specifier Support

Format specifiers like `"{:.2f}"` or `"{:10.3}"` are delegated to the numeric formatter:

```cpp
meter_t<double>{5.123456};
std::format("{:.2}", m)    // → "5.1 m"
std::format("{:10.3}", m)  // → "     5.12 m"
```

**Design Rationale:**
- Format specs apply only to the numeric value, not the symbol
- The space separator is always included between value and symbol
- Symbol is fixed-width per unit type

---

## 2. Measurement Formatting (`measurement_t` types)

### 2.1 Current State

Only basic `operator<<` support exists:

```cpp
template <typename UnitT>
std::ostream& operator<<(std::ostream& os, const measurement_lin_t<UnitT>& m)
{
    os << m.value() << " +/- " << m.uncertainty() << " " << UnitT::symbol;
    return os;
}
```

**Limitations:**
- No `std::formatter` specialization
- No format specifier support
- No wide-character support
- No design for optional precision or alternate formats

### 2.2 Proposed Design

#### Output Format Rules

Measurements output as: `<value> +/- <uncertainty> <symbol>`

**Examples:**
- `measurement_lin_t<meter_t>{5.0 ± 0.1}` → `"5 +/- 0.1 m"`
- `measurement_lin_t<kilogram_t>{100.0 ± 2.5}` → `"100 +/- 2.5 kg"`

#### `std::formatter` for `measurement_lin_t`

```cpp
// In std namespace (or measurement formatting header)
namespace std
{

template <typename UnitT, typename CharT = char>
struct formatter<pkr::units::measurement_lin_t<UnitT>, CharT>
{
private:
    std::formatter<typename UnitT::value_type, CharT> value_formatter;

public:
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    auto format(const pkr::units::measurement_lin_t<UnitT>& m, FormatContext& ctx) const
    {
        auto out = ctx.out();
        
        // Format value
        out = value_formatter.format(m.value(), ctx);
        
        // Separator
        auto sep = std::basic_string_view<CharT>(" +/- ");
        out = std::copy(sep.begin(), sep.end(), out);
        
        // Format uncertainty (with same precision as value)
        out = value_formatter.format(m.uncertainty(), ctx);
        
        // Symbol
        *out++ = static_cast<CharT>(' ');
        
        std::basic_string_view<CharT> sym;
        if constexpr (std::is_same_v<CharT, wchar_t>)
            sym = UnitT::w_symbol;
        else
            sym = UnitT::symbol;
        
        return std::copy(sym.begin(), sym.end(), out);
    }
};

} // namespace std
```

**Format Specifier Behavior:**
- Specifiers apply to **both** value and uncertainty uniformly
- Example: `std::format("{:.2}", m)` formats both as 2 decimal places
- Symbol is invariant

```cpp
pkr::units::measurement_lin_t<meter_t> m{5.123 ± 0.456};
std::format("{}", m)          // → "5.123 +/- 0.456 m"
std::format("{:.2}", m)       // → "5.12 +/- 0.46 m"
std::format("{:10.3}", m)     // → "     5.123 +/-      0.456 m"
```

#### `std::formatter` for `measurement_rss_t`

Analogous implementation for RSS (root-sum-square) measurements. Uses the same formatting as linear measurements:

```cpp
template <typename UnitT, typename CharT = char>
struct formatter<pkr::units::measurement_rss_t<UnitT>, CharT>
{
private:
    std::formatter<typename UnitT::value_type, CharT> value_formatter;

public:
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    auto format(const pkr::units::measurement_rss_t<UnitT>& m, FormatContext& ctx) const
    {
        auto out = ctx.out();
        
        // Format value
        out = value_formatter.format(m.value(), ctx);
        
        // Separator (ASCII: +/-, wide character: ±)
        if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            auto sep = std::basic_string_view<CharT>(L" ± ");
            out = std::copy(sep.begin(), sep.end(), out);
        }
        else
        {
            auto sep = std::basic_string_view<CharT>(" +/- ");
            out = std::copy(sep.begin(), sep.end(), out);
        }
        
        // Format uncertainty
        out = value_formatter.format(m.uncertainty(), ctx);
        
        // Symbol
        *out++ = static_cast<CharT>(' ');
        
        std::basic_string_view<CharT> sym;
        if constexpr (std::is_same_v<CharT, wchar_t>)
            sym = UnitT::w_symbol;
        else
            sym = UnitT::symbol;
        
        return std::copy(sym.begin(), sym.end(), out);
    }
};
```

**Output examples:**
```cpp
measurement_rss_t<meter_t> m{5.0, 0.1};
std::format("{}", m)        // ASCII → "5 +/- 0.1 m"
std::format(L"{}", m)       // wchar_t → "5 ± 0.1 m"
```

**Character type distinction:**
- ASCII (char): Both linear and RSS use `+/-` notation
- Wide character (wchar_t): Both linear and RSS use `±` notation for improved readability

### 2.3 Generic `operator<<` for Measurements

Provide generic overloads that use the formatter:

```cpp
namespace std
{

template <typename CharT, typename Traits, typename UnitT>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,
    const pkr::units::measurement_lin_t<UnitT>& m)
{
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        std::wstring formatted = std::format(L"{}", m);
        os << formatted;
    }
    else
    {
        std::string formatted = std::format("{}", m);
        os << formatted;
    }
    return os;
}

template <typename CharT, typename Traits, typename UnitT>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,
    const pkr::units::measurement_rss_t<UnitT>& m)
{
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        std::wstring formatted = std::format(L"{}", m);
        os << formatted;
    }
    else
    {
        std::string formatted = std::format("{}", m);
        os << formatted;
    }
    return os;
}

} // namespace std
```

---

## 3. Character Type Support

### 3.1 Strategy

Support two primary character types:

1. **`char` (ASCII/UTF-8)**:
   - Default stream output
   - Uses `T::symbol`
   - No special handling needed

2. **`wchar_t` (Wide)**:
   - For `std::wcout`, `std::wofstream`, etc.
   - Uses `T::w_symbol` (wide-character variant of symbol)
   - Format prefix: `L"{}"`

### 3.2 Symbol Requirements

Each unit type (both base and derived) must provide:

```cpp
struct meter_t : public unit_t<double, std::ratio<1>, length_dimension>
{
    static constexpr std::string_view symbol = "m";
    static constexpr std::wstring_view w_symbol = L"m";
};

struct meter_per_second_t : unit_t<double, ...>
{
    static constexpr std::string_view symbol = "m/s";
    static constexpr std::wstring_view w_symbol = L"m/s";
};
```

### 3.3 Dimension Symbols (Base Units)

For base `unit_t` types (dynamically computed dimensions), dimension symbols must handle character types:

```cpp
// In impl/formatting/unit_formatting_traits.h

template <typename CharT>
void build_dimension_symbol_to_buffer(
    impl::format_buffer<CharT>& buf,
    const dimension_value& dim)
{
    // Build symbol like "kg*m*s^-2" for force
    // Character type is established via CharT
    // No allocations; output directly to buffer
}
```

---

## 4. Formatter Architecture

### 4.1 Header Organization

```
sdk/include/pkr_units/
├── impl/
│   └── formatting/
│       ├── unit_formatter.h          /* std::formatter for unit_t */
│       ├── measurement_formatter.h   /* NEW: std::formatter for measurement_t */
│       └── unit_formatting_traits.h
├── measurements/
│   └── decl/
│       ├── measurement_lin_decl.h    /* Update: include formatter header */
│       └── measurement_rss_decl.h    /* Update: include formatter header */
└── si_units.h                        /* Main include file */
```

### 4.2 Implementation Files

**`measurement_formatter.h`** (NEW):
```cpp
#pragma once

#include <format>
#include <string_view>
#include <type_traits>
#include <algorithm>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/concepts/unit_concepts.h>

namespace std
{

// Formatter for measurement_lin_t
template <typename UnitT, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::measurement_lin_t<UnitT>, CharT>
{
    // ... implementation
};

// Formatter for measurement_rss_t
template <typename UnitT, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::measurement_rss_t<UnitT>, CharT>
{
    // ... implementation
};

} // namespace std
```

**Update `measurement_lin_decl.h` and `measurement_rss_decl.h`:**
- Include `<pkr_units/impl/formatting/measurement_formatter.h>`
- Keep existing `operator<<` for backward compatibility and char-only streams
- Ensure both formatter and operator use consistent formatting

---

## 5. Testing Strategy

### 5.1 Unit Formatter Tests

**Already covered** in existing test cases.

### 5.2 Measurement Formatter Tests

Create `tests/formatting/test_measurement_formatting.cpp`:

```cpp
TEST(MeasurementFormattingTest, measurement_lin_basic_ascii)
{
    measurement_lin_t<meter_t> m{5.0, 0.1};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "5 +/- 0.1 m");
}

TEST(MeasurementFormattingTest, measurement_lin_precision)
{
    measurement_lin_t<meter_t> m{5.123, 0.456};
    auto formatted = std::format("{:.2}", m);
    EXPECT_EQ(formatted, "5.12 +/- 0.46 m");
}

TEST(MeasurementFormattingTest, measurement_lin_wide_char)
{
    measurement_lin_t<meter_t> m{5.0, 0.1};
    auto formatted = std::format(L"{}", m);
    EXPECT_EQ(formatted, L"5 +/- 0.1 m");
}

TEST(MeasurementFormattingTest, measurement_rss_basic_ascii)
{
    measurement_rss_t<kilogram_t> m{100.0, 2.5};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "100 ± 2.5 kg");
}

TEST(MeasurementFormattingTest, measurement_rss_wide_char)
{
    measurement_rss_t<kilogram_t> m{100.0, 2.5};
    auto formatted = std::format(L"{}", m);
    EXPECT_EQ(formatted, L"100 ± 2.5 kg");
}

TEST(MeasurementFormattingTest, operator_stream_ostream)
{
    measurement_lin_t<meter_t> m{5.0, 0.1};
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "5 +/- 0.1 m");
}

TEST(MeasurementFormattingTest, operator_stream_wostream)
{
    measurement_lin_t<meter_t> m{5.0, 0.1};
    std::wstringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), L"5 +/- 0.1 m");
}
```

### 5.3 Integration Tests

- Verify `std::cout << measurement` works
- Verify `std::wcout << measurement` works
- Verify format specifiers apply correctly
- Verify char and wchar_t paths

---

## 6. Backward Compatibility

- Existing `operator<<` implementations remain unchanged
- New formatter specializations coexist with existing code
- Format specifier support does not break existing non-specifier usage
- Output format of measurements (`value +/- uncertainty symbol`) remains consistent

---

## 7. Future Extensions

### 7.1 Custom Format Specifiers

For advanced use cases, consider C++23+ `std::formatter` parse specifications:

```cpp
std::format("{:.2:scientific}", m) // "5.12e+00 ± 4.60e-02 m"
```

This requires custom parse logic:
```cpp
constexpr auto parse(ParseContext& ctx)
{
    // Parse value format spec (e.g., ".2")
    // Parse custom spec (e.g., ":scientific")
    return ctx.begin();  // or advanced parsing
}
```

### 7.2 Localization

Support locale-aware separators (e.g., comma for decimal in some locales, different uncertainty symbol):

```cpp
std::locale french("fr_FR.UTF-8");
std::format(std::locale(french), "{}", m)  // "5,00 ± 0,10 m"
```

---

## 8. Implementation Order

1. ✅ **Phase 1** (Already Done): Basic `std::formatter` for unit_t + operator<<
2. 🔄 **Phase 2** (This Design): Add `std::formatter` for measurement types + tests
3. 📋 **Phase 3** (Future): Custom format specifiers (scientific notation)
4. 📋 **Phase 4** (Future): Locale support for measurements

---

## Summary

This design completes ostream formatting across the library by:

1. **Documenting existing unit formatting** to establish baseline and architecture
2. **Adding formatter specializations for measurements** with parity to units
3. **Defining clear output formats** (`+/-` for linear, `±` for RSS)
4. **Ensuring character-type awareness** (char, wchar_t, char8_t)
5. **Providing consistent format specifier support** across all types
6. **Establishing a foundation for future extensions** (custom specs, localization)

All changes maintain backward compatibility and zero-cost abstraction principles.
