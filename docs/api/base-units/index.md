# Base Units

The seven SI base units plus angle. All other units are derived from combinations of these.

## SI Base Units

| Unit | Type | Symbol | Header |
|------|------|--------|--------|
| **Length** | `meter_t` | m | `si_units.h` |
| **Mass** | `kilogram_t` | kg | `si_units.h` |
| **Time** | `second_t` | s | `si_units.h` |
| **Electric Current** | `ampere_t` | A | `si_units.h` |
| **Temperature** | `kelvin_t` | K | `si_units.h` |
| **Amount of Substance** | `mole_t` | mol | `si_units.h` |
| **Luminous Intensity** | `candela_t` | cd | `si_units.h` |

## Supplementary Unit

| Unit | Type | Symbol | Header |
|------|------|--------|--------|
| **Plane Angle** | `radian_t` | rad | `si_units.h` |

### Angle Variants

While radian is the SI base, degrees and gradians are conveniences:
- `degree_t` — 1/360 of a circle (°)
- `gradian_t` — 1/400 of a circle (gon)

## SI Prefixes

All base units support standard metric prefixes:

| Prefix | Factor | Example |
|--------|--------|---------|
| pico- (p) | 10⁻¹² | `picosecond_t` |
| nano- (n) | 10⁻⁹ | `nanometer_t` |
| micro- (µ) | 10⁻⁶ | `microgram_t` |
| milli- (m) | 10⁻³ | `milliliter_t` |
| centi- (c) | 10⁻² | `centimeter_t` |
| deci- (d) | 10⁻¹ | `deciliter_t` |
| **base** | 10⁰ | `meter_t` |
| deca- (da) | 10¹ | `decameter_t` |
| hecto- (h) | 10² | `hectometer_t` |
| kilo- (k) | 10³ | `kilometer_t` |
| mega- (M) | 10⁶ | `megameter_t` |
| giga- (G) | 10⁹ | `gigameter_t` |
| tera- (T) | 10¹² | `terameter_t` |

## Usage Examples

```cpp
#include <pkr_units/si_units.h>
using pkr::units::meter_t, pkr::units::kilogram_t, pkr::units::second_t;

// Create base units
meter_t distance = 100.0;
kilogram_t mass = 50.0;
second_t time = 5.0;

// With literals
auto length = 25_mm;         // millimeter
auto weight = 2.5_kg;        // kilogram
auto duration = 100_ms;      // millisecond
auto current = 5_A;          // ampere

// Conversions between prefixes
kilometer_t kilo = unit_cast<kilometer_t>(distance);
microgram_t micro = unit_cast<microgram_t>(mass);
```

## Adding Support for New Prefixes

To add a prefix variant to any base unit, see [Creating Custom Units](../guides/custom-units.md).

## Limitations

### Extremely Small/Large Prefixes

The library uses `std::ratio` which has compile-time limits:
- **Smallest**: **picogram** (10⁻¹⁵ kg) — attogram and femtogram omitted due to `std::ratio` limitations
- **Largest**: **teragram** (10¹² kg) — petagram and larger omitted

### Temperature Precision

Temperature uses `double` internally, providing ~15 decimal digits of precision:
- Kelvin: Absolute scale (no offset)
- Celsius/Fahrenheit: Affine scales with offset (see [Temperature & Affine Units](../guides/temperature.md))

## Related

- [Derived Units](../derived-units/) — Build your formulas from base units
- [Creating Custom Units](../guides/custom-units.md) — How to add domain-specific variants
