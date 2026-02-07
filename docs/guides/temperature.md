# Temperature & Affine Units

Temperature is special among the base dimensions because it uses an *affine* scale (with an offset) rather than a *linear* scale.

## The Difference: Linear vs. Affine

### Linear Scales (Most Units)

Linear units can be freely added and subtracted:

```cpp
// Linear: length
meter_t a = 5.0;
meter_t b = 3.0;
meter_t sum = a + b;  // Results in 8 meters

// The zero point is absolute (no length)
```

### Affine Scales (Temperature)

Affine units have an arbitrary zero point:

```cpp
// Affine: Celsius temperature
// 0°C is not "no temperature"—it's 273.15 K

// This doesn't make physical sense
celsius_t t1 = 20.0;
celsius_t t2 = 10.0;
celsius_t sum = t1 + t2;  // What is 30°C? Nonsensical!
```

## Absolute vs. Differences

### Absolute Temperature (Affine)

```cpp
// Kelvin (absolute scale)
kelvin_t temp_absolute = 293.15_K;
// Can't add two absolutes: addition is not defined

// Celsius (affine scale, equivalent to kelvin)
celsius_t temp_celsius = 20.0_C;  // Same as 293.15 K
// Still can't add two absolute temperatures
```

### Temperature Differences (Linear)

```cpp
// Temperature difference (delta, linear)
kelvin_t delta1 = 10.0_K;   // 10 kelvin difference
kelvin_t delta2 = 5.0_K;    // 5 kelvin difference
kelvin_t combined = delta1 + delta2;  // 15 K difference
```

## Working with Celsius & Fahrenheit

### Conversion

```cpp
#include <pkr_units/si_units.h>
using pkr::units::kelvin_t, pkr::units::celsius_t, pkr::units::fahrenheit_t, pkr::units::unit_cast;
using namespace pkr::units::literals;

// Absolute temperatures
kelvin_t absolute_temp = 300.0_K;
celsius_t celsius_temp = unit_cast<celsius_t>(absolute_temp);
fahrenheit_t fahrenheit_temp = unit_cast<fahrenheit_t>(absolute_temp);

// Conversions are explicit (required because of affine nature)
```

### Temperature Differences

```cpp
// When subtracting two absolute temperatures, you get a difference (linear)
celsius_t t1 = 25.0_C;
celsius_t t2 = 20.0_C;
kelvin_t diff = t1 - t2;  // 5 K (difference is linear)

// Differences can be added/subtracted freely
kelvin_t delta = 10.0_K;
celsius_t new_temp = t1 + delta;  // 35°C (absolute + difference)
```

## Implementation Notes

The library represents:

- **Kelvin** (`kelvin_t`) — Absolute linear scale
- **Celsius** (`celsius_t`) — Affine scale (0°C = 273.15 K)
- **Fahrenheit** (`fahrenheit_t`) — Affine scale (32°F = 0°C = 273.15 K)

Conversions are explicitly handled via `unit_cast` to make affine transformations visible.

## Common Patterns

### Pattern 1: Physical Calculations

```cpp
// Heat capacity uses temperature difference (linear)
kilogram_t mass = 1.0_kg;
joule_per_kilogram_per_kelvin_t specific_heat = 4186.0;  // Water
kelvin_t delta_temp = 5.0_K;  // 5 degree increase
auto heat_absorbed = mass * specific_heat * delta_temp;  // Joules
```

### Pattern 2: Sensor Readings

```cpp
// Sensors give absolute temperature
celsius_t room_temp = read_sensor();

// Compare to reference
celsius_t reference = 20.0_C;
kelvin_t difference = room_temp - reference;

if (difference > 5.0_K) {
    // Too hot by more than 5 degrees
    cool_down();
}
```

### Pattern 3: Temperature Conversion

```cpp
kelvin_t body_temp = 310.0_K;  // ~37°C

// Convert to celsius for user display
celsius_t celsius_display = unit_cast<celsius_t>(body_temp);
std::cout << "Temperature: " << celsius_display << std::endl;  // 36.85°C

// Convert to fahrenheit
fahrenheit_t fahrenheit_display = unit_cast<fahrenheit_t>(body_temp);
std::cout << "Température: " << fahrenheit_display << std::endl;  // 98.33°F
```

## FAQ

**Q: Can I add two kelvin values?**
A: Only if they represent temperature *differences* (deltas), not absolute temperatures. If they're absolute temperatures, this doesn't make physical sense and the operation should be avoided.

**Q: How do I get a temperature difference?**
A: Subtract two absolute temperatures: `t1 - t2` gives a linear result.

**Q: Why does Celsius have special handling?**
A: Because 0°C ≠ "no temperature"—it's 273.15 K. The offset must be handled whenever converting between scales.

**Q: Can I use Celsius and Kelvin interchangeably for differences?**
A: Yes! A 1 degree Celsius difference is exactly 1 kelvin difference. But for absolute temperatures, they have different zero points.

## Related

- [Getting Started](../getting-started.md) — Basic usage
- [Type Safety](type-safety.md) — How dimensional checking works
- [Base Units](../api/base-units/) — Temperature unit reference
