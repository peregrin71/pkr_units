# Parsing and Stream I/O Design

## Overview

This document outlines the design for adding unit parsing with compile-time type safety, automatic unit conversion, and structured error handling.

## Current State

**What exists:**
- `operator<<` for outputting units to `std::ostream`
- `std::format` support for all units
- `std::chrono` integration (casting only)

**What's missing:**
- Parsing functions that convert strings to units
- `operator>>` for reading units from `std::istream`
- Automatic unit conversion during parsing (e.g., "1000 ft" → kilometers)

---

## Design Goals

1. **Compile-Time Type Safety**: Return type is known at compile-time (no runtime dispatch to determine type)
2. **Automatic Dimension Checking**: Reject parse if symbol doesn't match expected dimension
3. **Automatic Unit Conversion**: Parse "1000 ft" as `kilometer_t<double>` and convert automatically
4. **Explicit Intent**: Client code specifies the target unit, making intent clear
5. **Structured Error Handling**: Custom `expected_t` type with monadic operations
6. **Zero Code Duplication**: Single source of truth for symbols (in unit type definitions)
7. **Character-Type Aware**: Support char, wchar_t, char8_t seamlessly

---

## Design: Explicit Type Parse with Monadic expected_t

### API Signature

```cpp
namespace pkr::units {

enum class parse_error {
    numeric_parse_error,      // Invalid floating point format
    symbol_mismatch,          // Wrong dimension (e.g., parsed feet, expected meters)
    unknown_symbol,           // Symbol not recognized
};

// Parse with explicit target type
// Returns expected_t: success if parse + dimension match, error otherwise
template <typename TargetUnit, typename CharT = char>
auto parse(std::basic_string_view<CharT> input)
    -> expected_t<TargetUnit, parse_error>;

}
```

### The expected_t Type

A C++20-compatible alternative to `std::expected` with monadic operations and optimized move semantics. API-compatible with C++23's `std::expected` for future migration.

**Location**: `<pkr_units/expected.h>` (public header for client code)

```cpp
namespace pkr::units {

#if __cplusplus >= 202302L
// Use standard library in C++23 and later
using expected_t = std::expected;
#else
// C++20 implementation for compatibility

template <typename T, typename E>
class expected_t {
    std::variant<T, E> m_data;

public:
    // Construction
    expected_t(const T& value) : m_data(value) {}
    expected_t(T&& value) noexcept(std::is_nothrow_move_constructible_v<T>) 
        : m_data(std::move(value)) {}
    
    explicit expected_t(const E& error) : m_data(error) {}
    explicit expected_t(E&& error) noexcept(std::is_nothrow_move_constructible_v<E>) 
        : m_data(std::move(error)) {}
    
    // In-place construction
    template <typename... Args>
    expected_t(std::in_place_index_t<0>, Args&&... args)
        : m_data(std::in_place_index<0>, std::forward<Args>(args)...) {}
    
    template <typename... Args>
    expected_t(std::in_place_index_t<1>, Args&&... args)
        : m_data(std::in_place_index<1>, std::forward<Args>(args)...) {}
    
    // Move/Copy semantics (implicit from variant)
    expected_t(const expected_t&) = default;
    expected_t(expected_t&&) noexcept(
        std::is_nothrow_move_constructible_v<T> && 
        std::is_nothrow_move_constructible_v<E>) = default;
    expected_t& operator=(const expected_t&) = default;
    expected_t& operator=(expected_t&&) noexcept = default;

    // Status checks (C++23 compatible)
    bool has_value() const noexcept { return std::holds_alternative<T>(m_data); }
    explicit operator bool() const noexcept { return has_value(); }
    
    // Value access (C++23 compatible)
    T& operator*() { return std::get<T>(m_data); }
    const T& operator*() const { return std::get<T>(m_data); }
    
    T* operator->() { return &std::get<T>(m_data); }
    const T* operator->() const { return &std::get<T>(m_data); }
    
    // Throws std::bad_variant_access if error is held (C++23 compatible)
    T& value() { return std::get<T>(m_data); }
    const T& value() const { return std::get<T>(m_data); }
    
    // Error access (C++23 compatible)
    E& error() & { return std::get<E>(m_data); }
    const E& error() const& { return std::get<E>(m_data); }
    E error() && { return std::get<E>(std::move(m_data)); }
    const E error() const&& { return std::get<E>(std::move(m_data)); }

    // Monadic operations (C++23 compatible)

    // map: Transform success value to a new type
    template <typename F>
    auto map(F&& f) const {
        if (has_value()) {
            return expected_t<decltype(f(**this)), E>{f(**this)};
        }
        return expected_t<decltype(f(**this)), E>{error()};
    }

    // map_error: Transform error value
    template <typename F>
    auto map_error(F&& f) const {
        if (has_value()) {
            return expected_t<T, decltype(f(error()))>{**this};
        }
        return expected_t<T, decltype(f(error()))>{f(error())};
    }

    // and_then: Chain expected operations (flatmap)
    template <typename F>
    auto and_then(F&& f) const {
        if (has_value()) {
            return f(**this);
        }
        using result_type = decltype(f(**this));
        return result_type{error()};
    }

    // or_else: Handle error by returning a new expected
    template <typename F>
    auto or_else(F&& f) const {
        if (has_value()) {
            return expected_t{**this};
        }
        return f(error());
    }

    // value_or: Unwrap with default on error (C++23 compatible)
    T value_or(T default_val) const {
        return has_value() ? **this : std::move(default_val);
    }
    
    // value_or_else: Unwrap with computed default on error
    template <typename F>
    T value_or_else(F&& f) const {
        return has_value() ? **this : f(error());
    }
};

#endif // __cplusplus >= 202302L

}
```

**Key optimizations**:
- ✅ Move constructors/assignment operators (noexcept where possible)
- ✅ In-place construction to avoid temporaries
- ✅ Efficient storage via `std::variant`
- ✅ No dynamic allocation
- ✅ C++20 compatible (with automatic C++23 delegation)
- ✅ **API-compatible with std::expected** for seamless future migration
- ✅ Reusable in other parts of codebase

---

## Implementation Strategy

### 1. Symbol Trait System

Symbols are defined once in each unit type. The parser selects the appropriate symbol variant based on `CharT`:

```cpp
namespace impl {
    // Get symbol for specific character type
    template <typename UnitT, typename CharT>
    struct get_symbol_for_char;

    template <typename UnitT>
    struct get_symbol_for_char<UnitT, char> {
        static constexpr auto value() { return UnitT::symbol; }
    };

    template <typename UnitT>
    struct get_symbol_for_char<UnitT, wchar_t> {
        static constexpr auto value() { return UnitT::w_symbol; }
    };

    template <typename UnitT>
    struct get_symbol_for_char<UnitT, char8_t> {
        static constexpr auto value() { return UnitT::u8_symbol; }
    };
}
```

**Single Source of Truth**: Symbols live only in unit type definitions (e.g., `meter_t::symbol`). Parser references them, doesn't duplicate them.

### 2. Numeric Value Parsing

Extract the numeric value and deduce its type from the suffix:

```cpp
namespace impl {
    enum class numeric_type { DOUBLE, FLOAT };

    constexpr numeric_type deduce_numeric_type(std::string_view input) {
        if (input.empty()) return numeric_type::DOUBLE;
        char last = input.back();
        if (last == 'f' || last == 'F') return numeric_type::FLOAT;
        return numeric_type::DOUBLE;
    }

    // Parse numeric value (CharT-aware)
    template <typename CharT, typename ValueType>
    std::optional<ValueType> parse_numeric(
        std::basic_string_view<CharT> numeric_str,
        numeric_type type_hint)
    {
        try {
            if constexpr (std::is_same_v<CharT, char>) {
                if (type_hint == numeric_type::FLOAT) {
                    return static_cast<ValueType>(std::stof(std::string(numeric_str)));
                } else {
                    return static_cast<ValueType>(std::stod(std::string(numeric_str)));
                }
            } else if constexpr (std::is_same_v<CharT, wchar_t>) {
                if (type_hint == numeric_type::FLOAT) {
                    return static_cast<ValueType>(std::wcstof(numeric_str.data(), nullptr));
                } else {
                    return static_cast<ValueType>(std::wcstod(numeric_str.data(), nullptr));
                }
            } else {
                // char8_t: convert to char first
                std::string narrow(numeric_str.begin(), numeric_str.end());
                if (type_hint == numeric_type::FLOAT) {
                    return static_cast<ValueType>(std::stof(narrow));
                } else {
                    return static_cast<ValueType>(std::stod(narrow));
                }
            }
        } catch (...) {
            return std::nullopt;
        }
    }
}
```

### 3. Symbol Extraction and Matching

Split input into value and symbol parts, then match symbol against the target unit:

```cpp
namespace impl {
    template <typename CharT>
    struct split_result {
        std::basic_string_view<CharT> numeric;
        std::basic_string_view<CharT> symbol;
    };

    template <typename CharT>
    constexpr split_result<CharT> split_value_symbol(
        std::basic_string_view<CharT> input)
    {
        auto pos = input.rfind(static_cast<CharT>(' '));
        if (pos == std::basic_string_view<CharT>::npos) {
            return {input, {}};
        }
        return {input.substr(0, pos), input.substr(pos + 1)};
    }

    // Check if parsed symbol matches target unit (dimension validation)
    template <typename TargetUnit, typename CharT>
    bool symbol_matches(std::basic_string_view<CharT> symbol) {
        return symbol == get_symbol_for_char<TargetUnit, CharT>::value();
    }
}
```

### 4. Parse Function Implementation

```cpp
template <typename TargetUnit, typename CharT = char>
auto parse(std::basic_string_view<CharT> input)
    -> expected_t<TargetUnit, parse_error>
{
    // Split input into numeric and symbol parts
    auto [numeric_part, symbol_part] = impl::split_value_symbol<CharT>(input);

    // Deduce value type from numeric suffix
    auto type_hint = impl::deduce_numeric_type(numeric_part);

    // Parse numeric value
    auto numeric_value = impl::parse_numeric<CharT, typename TargetUnit::value_type>(
        numeric_part, type_hint);
    if (!numeric_value) {
        return parse_error::numeric_parse_error;
    }

    // Check if symbol matches target unit (dimension validation)
    if (!impl::symbol_matches<TargetUnit, CharT>(symbol_part)) {
        if (impl::is_unknown_symbol<CharT>(symbol_part)) {
            return parse_error::unknown_symbol;
        } else {
            return parse_error::symbol_mismatch;
        }
    }

    // Automatic unit conversion: if parsed unit differs from target, convert
    auto parsed_unit = impl::construct_from_symbol<CharT>(symbol_part, *numeric_value);
    auto target_unit = unit_cast<TargetUnit>(parsed_unit);

    return expected_t<TargetUnit, parse_error>{target_unit};
}
```

---

## Usage Examples

### Basic Parsing

```cpp
// Parse with automatic type deduction (C++17 CTAD)
auto result = parse<meter_t<double>>("5.2 m");
if (result) {
    std::cout << "Parsed: " << result->value() << " m\n";
} else {
    std::cerr << "Error: " << int(result.error()) << "\n";
}
```

### Automatic Unit Conversion

```cpp
// Parse feet, store as kilometers
auto km = parse<kilometer_t<double>>("1000.0 ft");
if (km) {
    std::cout << "1000 ft = " << km->value() << " km\n";  // ~0.3048 km
}
```

### Monadic Operations

```cpp
// Chain transformations with map
auto feet_value = parse<meter_t<double>>("100.0 m")
    .map([](const auto& m) {
        // Convert meters to feet
        return m.value() * 3.28084;
    })
    .value_or(0.0);

// Handle errors with recovery
auto distance = parse<kilometer_t<double>>("invalid_input")
    .or_else([](auto err) {
        // On error, return a default value
        return expected_t<kilometer_t<double>, parse_error>{
            kilometer_t<double>{0.0}
        };
    });

// Chain multiple parse operations
auto pipeline = parse<meter_t<double>>("1000.0 ft")
    .and_then([](const auto& m) {
        // Successfully parsed as meters, now convert to kilometers
        return parse<kilometer_t<double>>(
            fmt::format("{} m", m.value()));
    });
```

### Wide Character and UTF-8 Support

```cpp
// Wide character parsing
auto wide_result = parse<meter_t<double>, wchar_t>(L"5.2 m");
if (wide_result) {
    std::wcout << L"Parsed: " << wide_result->value() << L" m\n";
}

// UTF-8 parsing (handles µ symbol, etc.)
auto utf8_result = parse<micrometer_t<double>, char8_t>(u8"5.2 µm");
if (utf8_result) {
    std::cout << "Parsed: " << utf8_result->value() << " µm\n";
}
```

---

## Key Design Points

### 1. Why Explicit Type Specification?

- **Compile-time return type**: No variant overhead, no runtime dispatch
- **Dimension validation at parse time**: "1000 ft" parsed as `meter_t` → error (dimension mismatch)
- **Automatic conversion**: If symbol matches dimension, `unit_cast` to target automatically
- **Clear intent**: `parse<kilometer_t>` documents what unit is expected

### 2. Value Type Deduction

- **From numeric suffix**: `"1.0f"` → float, `"1.0"` or `"1.0d"` → double
- **Deduced automatically** during parsing (no explicit template parameter needed)
- **Matches target unit's value_type**: `parse<meter_t<float>>` parses into float

### 3. Symbol Matching Strategy

- **Single source of truth**: Symbols defined in unit types only
- **CharT-aware lookup**: Trait selects correct symbol variant
- **Dimension validation**: Parse ensures symbol dimension matches target
- **Automatic conversion**: If dimensions match but ratios differ, `unit_cast` handles it

### 4. Error Handling via expected_t

Three error types:
- **numeric_parse_error**: Input doesn't parse as a number
- **unknown_symbol**: Unrecognized unit symbol
- **symbol_mismatch**: Symbol doesn't match target dimension

expected_t supports:
- **map**: Transform value type
- **and_then**: Chain parse operations
- **or_else**: Recovery with error handling
- **value_or**: Unwrap with default
- **value_or_else**: Unwrap with computed default

### 5. Reusable expected_t

The `expected_t` type is a public client-facing class in `<pkr_units/expected.h>`:
- Can replace `std::optional` in other parts of codebase
- C++20 compatible (no C++23 features)
- Optimized move semantics and in-place construction
- Zero-cost abstraction with monadic operations

---

## Implementation Checklist

- [ ] Create `<pkr_units/expected.h>` with public `expected_t<T, E>` class
- [ ] Define `parse_error` enum
- [ ] Implement symbol trait: `impl::get_symbol_for_char<UnitT, CharT>`
- [ ] Implement numeric deduction: `numeric_type deduce_numeric_type(string_view)`
- [ ] Implement input splitting: `split_value_symbol<CharT>(string_view)`
- [ ] Implement value parsing: `parse_numeric<CharT, ValueType>(string_view)`
- [ ] Implement symbol matching: `symbol_matches<TargetUnit, CharT>(string_view)`
- [ ] Implement main parse function: `parse<TargetUnit, CharT>(string_view)`
- [ ] Add `operator>>` using parse backend for stream input
- [ ] Add comprehensive tests:
  - Value type deduction (float vs double)
  - Symbol matching (all dimension types)
  - Character type handling (char, wchar_t, char8_t)
  - Unit conversion during parse
  - All error cases
  - Monadic operations (map, and_then, or_else, value_or)
- [ ] Documentation with examples for all CharT variants
- [ ] Consider UTF-8 symbol support (µ, °, etc.) in u8_symbol constants

---

## Stream I/O (operator>>)

Optional convenience wrapper:

```cpp
template <typename CharT, typename Traits, typename Unit>
    requires is_pkr_unit_c<Unit>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,
    Unit& unit)
{
    std::basic_string<CharT> buffer;
    is >> buffer;

    if (auto result = parse<Unit, CharT>(buffer)) {
        unit = *result;
    } else {
        is.setstate(std::ios_base::failbit);
    }
    return is;
}

// Usage
meter_t<double> m;
std::cin >> m;
if (!std::cin.fail()) {
    std::cout << "Got: " << m.value() << " m\n";
}
```

---

## Advantages of This Design

1. ✅ **Compile-time type safety**: Return type determined at compile-time
2. ✅ **No variant overhead**: Direct type, not std::variant
3. ✅ **Dimension validation**: Automatic checking at parse-time
4. ✅ **Automatic unit conversion**: Parse "1000 ft" as km automatically
5. ✅ **Single symbol source**: No duplication, changes propagate automatically
6. ✅ **CharT agnostic**: One implementation, multiple character types
7. ✅ **Monadic error handling**: Composable, expressive error recovery
8. ✅ **Explicit intent**: Template parameter makes expected unit clear
9. ✅ **C++20 compatible**: No C++23 features required
10. ✅ **Reusable expected_t**: Separate header enables use elsewhere in codebase
11. ✅ **Move optimized**: Efficient expected_t with move semantics
12. ✅ **In-place construction**: Avoid temporaries where possible

---

## Open Questions and Future Enhancements

1. **Locale support**: Parse `"5,2 m"` (European decimal separator)
   - Recommendation: Start with `std::locale::classic()`, extend later

2. **Whitespace flexibility**: Accept `"5.2m"` (no space)?
   - Recommendation: Require space separator for clarity

3. **Symbol aliases**: Support both `"m"` and `"meter"`?
   - Recommendation: Stick with short symbols; aliases via specialization if needed

4. **Dimension-filtered variant** (Phase 2): Parse from heterogeneous input
   - Would return `std::optional<std::variant<length_units...>>`
   - Requires different API than explicit type

5. **Custom symbol registration** (Phase 2): Allow domain-specific symbols
   - Extend trait system to support user-defined units

6. **Reuse expected_t across codebase** (Phase 2+): Replace std::optional where appropriate
   - Error handling improvements
   - Monadic operations reduce boilerplate

