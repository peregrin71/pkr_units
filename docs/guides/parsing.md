# Parsing & String Conversion

Guide to parsing strings into units and measurements.

## Overview

The library provides compile-time validated parsing for strings containing unit values:

- **`parse<UnitType>(string)`** — Parse a single unit value
- **`parse_linear<MeasurementType>(string)`** — Parse a unit with linear uncertainty
- **`parse_rss<MeasurementType>(string)`** — Parse a unit with RSS uncertainty

## Basic Parsing

### Parsing Simple Units

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/impl/parsing/parse.h>

using namespace pkr::units;

// Parse basic value
auto result = parse<meter_t>("5.2 m");
if (result) {
    std::cout << result->value() << " m\n";  // 5.2 m
}

// With float suffix (auto-detects precision)
auto float_result = parse<meter_t<float>>("5.2f m");
// Result is meter_t<float> with float value
```

### Error Handling

Parsing returns `expected_t<UnitType, parse_error>`:

```cpp
auto result = parse<meter_t>("invalid input");

if (result) {
    // Success: use result->value()
    std::cout << result->value() << std::endl;
} else {
    // Error: result.error() contains parse_error
    std::cout << "Parse failed: " << static_cast<int>(result.error()) << std::endl;
}
```

## Measurements with Uncertainty

### Linear Uncertainty

Linear uncertainty uses symmetric error bounds: `value ± uncertainty`

```cpp
auto meas = parse_linear<measurement_lin_t<meter_t>>("5.0 +/- 0.1 m");

if (meas) {
    std::cout << "Value: " << meas->value() << std::endl;        // 5.0
    std::cout << "Uncertainty: " << meas->uncertainty() << std::endl;  // 0.1
}
```

### RSS Uncertainty

Root-sum-square propagation (standard physics):

```cpp
auto meas = parse_rss<measurement_rss_t<meter_t>>("5.0 +/- 0.1 m");

if (meas) {
    // Identical parsing; internally uses RSS propagation
    std::cout << "Value: " << meas->value() << std::endl;
    std::cout << "Uncertainty: " << meas->uncertainty() << std::endl;
}
```

## Input Formats

### String Variants

```cpp
// All of these work:
parse<meter_t>("5.2 m");           // Standard: value space unit
parse<meter_t>("5.2m");            // No space
parse<meter_t>("  5.2   m  ");     // Extra whitespace

// Scientific notation
parse<meter_t>("1.5e-3 m");        // 0.0015 m
parse<meter_t>("1.5E3 m");         // 1500 m
```

### Uncertainty Formats

```cpp
// Plus-minus symbol
parse_linear<measurement_lin_t<meter_t>>("5.0 +/- 0.1 m");

// Unicode plus-minus
parse_linear<measurement_lin_t<meter_t>>("5.0 ± 0.1 m");

// All variations of spacing work
parse_linear<measurement_lin_t<meter_t>>("5.0+/-0.1 m");
parse_linear<measurement_lin_t<meter_t>>("5.0  ±  0.1  m");
```

## Character Types

### char (ASCII)

```cpp
auto result = parse<meter_t>("5.2 m");  // std::string_view<char>
auto result = parse<meter_t, char>(std::string_view("5.2 m"));
```

### wchar_t (Wide Characters)

```cpp
auto result = parse<meter_t, wchar_t>(L"5.2 m");
```

### char8_t (UTF-8)

```cpp
auto result = parse<meter_t, char8_t>(u8"5.2 m");

// UTF-8 plus-minus symbol works
auto meas = parse_linear<measurement_lin_t<meter_t>, char8_t>(
    u8"5.0 ± 0.1 m"
);
```

## Unit Symbol Validation

The parser validates that the symbol matches the target unit:

```cpp
// Correct symbol: succeeds
parse<meter_t>("5.2 m");       // ✓

// Wrong symbol: fails
parse<meter_t>("5.2 km");     // ✗ dimension matches but not the same unit
parse<meter_t>("5.2 kg");     // ✗ different dimension

// No symbol: succeeds (assumes target unit)
parse<meter_t>("5.2");        // ✓ assumes m

// For unit_cast to different scale:
auto result = parse<meter_t>("5.2 m");
auto km = unit_cast<kilometer_t>(*result);  // Manual conversion
```

## Advanced Examples

### Batch Parsing

```cpp
std::vector<meter_t> measurements;

std::string_view data[] = {"5.2 m", "10.1 m", "3.5 m"};

for (const auto& str : data) {
    auto result = parse<meter_t>(str);
    if (result) {
        measurements.push_back(*result);
    } else {
        std::cerr << "Failed to parse: " << str << std::endl;
    }
}
```

### Parsing with Unit Conversion

```cpp
// Parse in kilometers, convert to meters
auto result = parse<kilometer_t>("1.5 km");
if (result) {
    auto meters = unit_cast<meter_t>(*result);
    std::cout << meters.value() << " m\n";  // 1500 m
}
```

### Parsing Measurements into Series

```cpp
using measurement_series_t = measurement_series<meter_t>;

measurement_series_t data;

std::string_view readings[] = {
    "100.5 +/- 0.5 m",
    "101.2 +/- 0.6 m",
    "99.8 +/- 0.4 m"
};

for (const auto& str : readings) {
    auto meas = parse_linear<measurement_lin_t<meter_t>>(str);
    if (meas) {
        data.add_now(*meas);
    }
}
```

## Error Cases

Common parse errors:

```cpp
// Invalid numeric value
parse<meter_t>("abc m");          // parse_error::numeric_parse_error

// Missing symbol when required
parse<meter_t>("5.2");            // Depends on context; may be allowed

// Symbol mismatch
parse<meter_t>("5.2 kg");         // parse_error::symbol_mismatch

// Invalid uncertainty format
parse_linear<measurement_lin_t<meter_t>>("5.0 +/- m");  // Missing uncertainty value

// Precision loss (float vs double)
auto f = parse<meter_t<float>>("5.123456789 m");  // OK, truncated to float precision
```

## Performance Notes

- Parsing happens at runtime (call `parse()` when needed, not at compile-time)
- All numeric conversions are standard `std::strtod`/`std::strtof`
- Symbol lookup is case-sensitive
- Zero allocation when using `std::string_view` input

## See Also

- [Getting Started](../getting-started.md) — Quick setup
- [Type Safety](./type-safety.md) — How dimensional checking works
- [API Overview](../api/overview.md) — Full API reference

