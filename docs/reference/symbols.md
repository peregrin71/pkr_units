# Symbol Guide - ASCII vs. Unicode

The library supports both ASCII and Unicode representations of unit symbols for flexibility and accessibility.

## Overview

Each unit type has three symbol representations:

```cpp
struct meter_t {
    static constexpr std::string_view symbol{"m"};          // ASCII
    static constexpr std::wstring_view w_symbol{L"m"};      // Wide (Unicode)
    static constexpr std::u8string_view u8_symbol{u8"m"};   // UTF-8
};

struct square_meter_t {
    static constexpr std::string_view symbol{"m^2"};        // ASCII: caret
    static constexpr std::wstring_view w_symbol{L"m²"};     // Unicode: superscript
    static constexpr std::u8string_view u8_symbol{u8"m²"};  // UTF-8 superscript
};
```

## When to Use Each

### ASCII Symbol (`symbol`)

**Use when:**
- Output is plain text or log files
- Terminal/console that doesn't support Unicode
- Parsing or machine-readable format
- Legacy systems
- Email or plain-text protocols

**Example:**
```
Force: 100 N
Velocity: 20 m/s
Density: 1000 kg/m^3
```

### Unicode Symbol (`w_symbol`, `u8_symbol`)

**Use when:**
- Professional/scientific documentation (PDF, HTML)
- User-facing displays (GUI, web)
- Mathematical typesetting
- Accessibility (screen readers benefit from standard symbols)
- International contexts

**Example:**
```
Force: 100 N
Velocity: 20 m·s⁻¹
Density: 1000 kg·m⁻³
```

## Symbol Patterns

### Multiplication: Dot or Space

| Quantity | ASCII | Unicode |
|----------|-------|---------|
| Newton·meter | `N*m` | `N·m` |
| Kilogram·meter/second² | `kg*m/s^2` | `kg·m·s⁻²` |

The Unicode version uses a **centered dot** (·) which is standard in scientific notation.

### Division: Slash or Superscript

| Quantity | ASCII | Unicode |
|----------|-------|---------|
| Meter per second | `m/s` | `m·s⁻¹` |
| Kilogram per cubic meter | `kg/m^3` | `kg·m⁻³` |

The Unicode version uses **negative superscripts** (s⁻¹) following ISO 80000 standard.

### Powers: Caret or Superscript

| Quantity | ASCII | Unicode |
|----------|-------|---------|
| Square meter | `m^2` | `m²` |
| Cubic meter | `m^3` | `m³` |
| Newton per meter squared | `N/m^2` | `N·m⁻²` |

The Unicode version uses **superscript digits** for cleaner visual representation.

## Selected Examples

### Length
- Meter: `m` ↔ `m`
- Kilometer: `km` ↔ `km`
- Micrometer: `um` ↔ `µm` (micro symbol)
- Angstrom: `A` ↔ `Å`

### Temperature
- Kelvin: `K` ↔ `K`
- Celsius: `C` ↔ `°C` (degree symbol)
- Fahrenheit: `F` ↔ `°F`

### Electrical
- Ampere: `A` ↔ `A`
- Volt: `V` ↔ `V`
- Omega (resistance): `ohm` ↔ `Ω` (Greek omega)
- Micro-siemens: `uS` ↔ `µS`

### Derived Units
- Newton: `N` ↔ `N`
- Pascal: `Pa` ↔ `Pa`
- Joule: `J` ↔ `J`
- Watt: `W` ↔ `W`
- Meter per second: `m/s` ↔ `m·s⁻¹`
- Kilogram per meter³: `kg/m^3` ↔ `kg·m⁻³`

## Configuration in Formatting

When using `std::format`, you can format symbols:

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/format/si.h>
#include <iostream>

using pkr::units::meter_t;

int main() {
    meter_t distance = 100.0;
    
    // Default formatting (uses ASCII)
    std::cout << std::format("Distance: {}\n", distance);
    // Output: Distance: 100 m
    
    // Unicode formatting (if supported by formatter)
    // Implementation details depend on formatter
}
```

## Accessibility Notes

### For Screen Readers

Standard Unicode symbols (°C, ², µ, Ω) are recognized by most screen readers and spoken as:
- °C → "degrees celsius"
- ² → "squared"
- µ → "micro"
- Ω → "ohm"

Plain ASCII (`^2` for squared, `u` for micro) may not be as well recognized.

### For Terminal/Console Output

If storing in monospace log files or terminals, ASCII is safer:
```
Modern HTML log: might render unicode beautifully
Legacy plaintext: should use ASCII

Desktop GUI: can use unicode
Old SSH terminal: might default to ASCII-safe
```

## Best Practices

1. **User-facing output** → Use Unicode (professional, standards-compliant)
2. **Logs/internal systems** → Use ASCII (compatibility, machine-readable)
3. **Scientific/academic** → Use Unicode (matches ISO standards)
4. **Web/PDF documents** → Use Unicode (UTF-8 is standard)
5. **Testing/debugging** → Use ASCII (simpler to read raw logs)
6. **Cross-platform tools** → Use ASCII (safest default)

## Unicode Character Reference

| Symbol | Name | Code | Used For |
|--------|------|------|----------|
| ° | Degree | U+00B0 | Temperature |
| · | Middle Dot | U+00B7 | Multiplication |
| µ | Micro | U+00B5 | Metric prefix |
| Ω | Omega | U+03A9 | Resistance (ohm) |
| ² | Superscript 2 | U+00B2 | Squared |
| ³ | Superscript 3 | U+00B3 | Cubed |
| ⁻ | Superscript Minus | U+207B | Negative exponent |
| ¹ | Superscript 1 | U+00B9 | Exponent 1 |

## Encoding Notes

- **ASCII** (`symbol`) — Standard ASCII, safe everywhere
- **UTF-16** (`w_symbol`) — Wide string, Windows-friendly
- **UTF-8** (`u8_symbol`) — Modern standard, web-friendly

Most modern applications use UTF-8 internally and convert as needed.

## Related

- [Formatting](headers.md#formatting--output) — How to format units in output
- [Constants](../api/constants/index.md) — Physical constants with symbols
- [Units Table](units-table.md) — Complete symbol reference
