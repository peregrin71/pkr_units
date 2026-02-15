# pkr_units

Header-only C++20 library for type-safe physical units with compile-time dimensional checking,
including measurement support with uncertainty propagation.

License: MIT (see `LICENSE`).

## Index

- [Introduction](#introduction)
- [Design Summary](#design-summary)
- [Library Contents](#library-contents)
- [Headers and Entry Points](#headers-and-entry-points)
- [Quick Start](#quick-start)
- [Core Usage](#core-usage)
- [Temperature and Affine Units](#temperature-and-affine-units)
- [Measurements with Uncertainty](#measurements-with-uncertainty)
- [Numerical Helpers](#numerical-helpers)
- [Formatting and I-O](#formatting-and-i-o)
- [Constants](#constants)
- [User-defined Literals](#user-defined-literals)
- [Custom Units](#custom-units)
- [Extensibility](#extensibility)
- [Appendix: Predefined Unit Types](#appendix-predefined-unit-types)
- [Glossary](#glossary)
- [Build and Tests](#build-and-tests)

## Introduction

This library exists to prevent unit-mismatch bugs (for example, adding meters to seconds or mixing mph with m/s)
by introducing strong unit types. Dimensional correctness is enforced at compile time. Conversions are explicit and
performed with `unit_cast`, so any change of scale or system is visible in the code.
For convenience a lot of unit types have been declared to allow you to be very expressive in code. 

## Design Summary

Concise design approach based on the implementation:

- **Core type model**: `details::unit_t<value_type, ratio, dimension_t>` encodes value type, scaling ratio, and dimensions.
- **Strong types**: Unit types (e.g., `meter_t`) inherit from `unit_t` via `_base`, preserving strong typing and enabling traits.
- **Default value type**: Built-in units use `double`. You can define custom units with other value types.
- **8-dimensional system**: `dimension_t` has 8 integer exponents based on all standard SI units
- **Type mapping**: `derived_unit_type_t` maps (value type, ratio, dimension) to the most specific strong type when available.
- **Arithmetic rules**:
  - Add/Subtract only for same dimensions; **returns the LHS unit type**.
  - Multiply/Divide combines dimensions and ratios without forced normalization.
    The result is a `unit_t` with the combined ratio; use `unit_cast` (or `to_si`)
    when you want a specific named unit type.
- **Compile-time checks, runtime math**: Dimensional checks happen at compile time; conversions are numeric operations.
- **Extensible**: New units can be defined by adding types and `derived_unit_type_t` specializations.
- **Measurements**: `measurement_t` stores value+uncertainty and supports two propagation strategies.

## Library Contents

High-level overview of what is present in this repository:

- **SI units**: base units plus commonly used derived units (velocity, acceleration, force, pressure, energy, power, density, concentration, electrical, magnetic flux, viscosity).
- **Additional derived groups**: area and volume are provided in dedicated headers.
- **Imperial, CGS, and astronomical units**: separate headers for non-SI, CGS, and astronomical units.
- **Conversions**: `unit_cast` for same-dimension conversions, with affine support for temperature.
- **Measurements with uncertainty**: `measurement_t` and optional uncertainty math strategies.
- **Numerical helpers**: stable arithmetic, Newton-Raphson, and Runge-Kutta.
- **Formatting**: `std::format` support for units and measurements.
- **Constants**: selected physical constants as typed units and raw values.

## Headers and Entry Points

Common headers:

- `sdk/include/pkr_units/si_units.h` - SI base units plus several derived groups, unit_cast, measurement_t
- `sdk/include/pkr_units/imperial_units.h` - imperial and other non-SI units
- `sdk/include/pkr_units/cgs_units.h` - CGS units (gauss, dyne, erg, barye, gal, maxwell, poise, stokes, statcoulomb, oersted)
- `sdk/include/pkr_units/astronomical_units.h` - astronomical length units
- `sdk/include/pkr_units/chrono.h` - std::chrono conversion overloads for time units
- `sdk/include/pkr_units/math/unit_math.h` - stable operations, Newton-Raphson, Runge-Kutta, math functions
- `sdk/include/pkr_units/constants.h` - physical constants (typed and raw values)
- `sdk/include/pkr_units/format/si.h` - std::format support for SI units
- `sdk/include/pkr_units/format/cgs.h` - std::format support for CGS units
- `sdk/include/pkr_units/literals/si.h` - SI literal operators
- `sdk/include/pkr_units/literals/imperial_units.h` - imperial literal operators
- `sdk/include/pkr_units/literals/cgs.h` - CGS literal operators (none yet)
- `sdk/include/pkr_units/literals/astronomical.h` - astronomical literal operators (none yet)

Some unit groups live in narrower headers, for example:

- `sdk/include/pkr_units/units/derived/area/area_units.h`
- `sdk/include/pkr_units/units/derived/volume/volume_units.h`
- `sdk/include/pkr_units/units/temperature/celsius.h`
- `sdk/include/pkr_units/units/temperature/fahrenheit.h`

Default namespace is `pkr::units`. You can override it by defining `PKR_UNITS_NAMESPACE` before including headers.

```cpp
#define PKR_UNITS_NAMESPACE my_app::units
#include <pkr_units/si_units.h>

my_app::units::meter_t d{5.0};
```

## Quick Start

```cpp
#include <pkr_units/si_units.h>

int main()
{
    auto distance = pkr::units::meter_t{100.0};
    auto time = pkr::units::second_t{10.0};

    auto speed = distance / time; // unit with velocity dimensions
    auto speed_kmh = pkr::units::unit_cast<pkr::units::kilometer_per_hour_t>(speed);

    return 0;
}
```

## Core Usage

### Dimensional correctness

```cpp
using namespace pkr::units;

meter_t a{5.0};
second_t t{2.0};

auto v = a / t;               // OK (velocity dimensions)
// auto bad = a + t;           // Compile-time error
```

### LHS return type for add/subtract

```cpp
using namespace pkr::units;

meter_t m{500.0};
kilometer_t km{1.0};

auto sum_m = m + km;  // meter_t (LHS type)
auto sum_km = km + m; // kilometer_t (LHS type)
```

### unit_cast

```cpp
using namespace pkr::units;

kilometer_t d{1.2};
auto d_m = unit_cast<meter_t>(d);

meter_per_second_t v{10.0};
auto v_kmh = unit_cast<kilometer_per_hour_t>(v);
```

## Automatic conversion when passing units with the same dimensions

You can have different parts of the software that uses different units of
measurement "talk" safely with each other.

```cpp
#include <iostream>
#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>

void set_distance_in_meters(const pkr::units::meter_t<double>& distance)
{
    std::cout << "Distance in meters: " << distance.value() << " m\n";
}



int main()
{
    // So you can define a distance in feet
    pkr::units::foot_t<double> distance_in_feet{10.0};
    
    // and then pass it to a function the internally 
    // uses meters. Adn the conversion will happen automatically
    set_distance_in_meters(distance_in_feet);

return 0;
}
```

## Using Complex (imaginary) units

```cpp
void complex_units()
{
    // === Electrical example: complex impedance ===
    // Impedance Z = R + jX (ohms), current I (amperes) may be complex.
    // Use complex-valued units (std::complex<double>) and take the real part when needed.
    using cplx = std::complex<double>;
    pkr::units::ohm_t<cplx> Z{cplx{50.0, 30.0}};   // 50 + j30 ohm
    pkr::units::ampere_t<cplx> I{cplx{2.0, -1.0}}; // 2 - j1 A

    auto V = Z * I; // volt_t<cplx>

    std::cout << "Impedance Z: (" << std::real(Z.value()) << ") + j(" << std::imag(Z.value()) << ") ohm\n";
    std::cout << "Voltage V = Z * I: (" << std::real(V.value()) << ") + j(" << std::imag(V.value()) << ") V\n";

    // If you only want the resistive (real) part, extract it and use a real-valued unit
    pkr::units::ohm_t<double> resistance{std::real(Z.value())};
    std::cout << "Resistance (real part of Z): " << resistance.value() << " ohm\n"
```

## Temperature and Affine Units

Temperature conversions that involve offsets (Celsius/Fahrenheit) are handled through `unit_cast`
when affine traits are available. Include the temperature cast header to enable those overloads.

```cpp
#include <pkr_units/units/temperature/temperature_cast.h>

pkr::units::celsius_t c{20.0};
auto f = pkr::units::unit_cast<pkr::units::fahrenheit_t>(c);
auto k = pkr::units::unit_cast<pkr::units::kelvin_t>(c);
```

Recommendation: use `kelvin_t` for all your calculations and only convert to
`celsius_t` or `fahrenheit_t` for presentation. Offset-based conversions can
introduce additional rounding, so repeated conversions in the middle of a
calculation will accumulate error faster than staying in Kelvin.

### Affine Traits (How Temperature Casting Works)

Temperature units with offsets (Celsius/Fahrenheit) are the only predefined conversions
that require an additive offset in addition to a scale factor. Ratios alone are not enough
because the zero points differ between Celsius, Fahrenheit, and Kelvin.

The library uses `temperature_affine_traits<T>` to provide:

- `is_affine` flag
- `to_kelvin(value)` and `from_kelvin(value)` conversion functions

`unit_cast` remains generic for all normal units. Temperature handling is added in
`units/temperature/temperature_cast.h` by providing a more specialized overload for temperature like types,
so the generic `unit_cast` stays untouched. When the compiler selects the
temperature-specific overload, it checks `temperature_affine_traits<T>::is_affine`.
If either the source or target type is affine, it takes the temperature conversion
path and:

1) Converts the source value to Kelvin (ratio-based for Kelvin types, or `to_kelvin` for affine types)
2) Converts from Kelvin to the target type (ratio-based or `from_kelvin`)

This keeps `unit_cast` the single entry point while adding correct offset behavior.


## Measurements with Uncertainty

`measurement_t<UnitT>` stores a value and an uncertainty of the same unit type.
Basic arithmetic propagates uncertainties:

- Add/Subtract: root-sum-square (RSS)
- Multiply/Divide: linear sum of relative uncertainties

```cpp
#include <pkr_units/measurements/measurement.h>

using namespace pkr::units;

measurement_t<meter_t> length{5.0, 0.1};  // 5.0 +/- 0.1 m
measurement_t<second_t> time{2.0, 0.05};  // 2.0 +/- 0.05 s

auto velocity = length / time;
```

For explicit uncertainty strategies and math helpers, include:

- `sdk/include/pkr_units/measurements/measurement_math_rss.h`
- `sdk/include/pkr_units/measurements/measurement_math_linear.h`
- or `sdk/include/pkr_units/measurements/measurement_math.h` (defaults to RSS)

### Uncertainty strategies (step-by-step)

Example inputs:

- `length = 5.0 ± 0.1 m`
- `width  = 3.0 ± 0.2 m`

**RSS strategy** (root-sum-square of uncertainties):

1) Addition/Subtraction (absolute):
   - σ = sqrt(0.1^2 + 0.2^2) = 0.2236 m
2) Multiplication/Division (relative):
   - r1 = 0.1 / 5.0 = 0.02
   - r2 = 0.2 / 3.0 = 0.0667
   - r_total = sqrt(r1^2 + r2^2) = 0.0696
   - area = 5.0 * 3.0 = 15.0
   - σ = 15.0 * 0.0696 = 1.04 m^2

Use `measurement_math_rss.h` for `multiply_rss`, `divide_rss`, `sqrt_rss`, etc.

**Linear strategy** (sum of relative uncertainties):

1) Addition/Subtraction (absolute):
   - σ = sqrt(0.1^2 + 0.2^2) = 0.2236 m
2) Multiplication/Division (relative):
   - r_total = r1 + r2 = 0.0867
   - area = 15.0
   - σ = 15.0 * 0.0867 = 1.30 m^2

The linear strategy corresponds to the default `measurement_t` arithmetic for multiply/divide
and is also available via `measurement_math_linear.h`.

## Numerical Helpers

`sdk/include/pkr_units/math/unit_math.h` provides numerical utilities for unit-aware calculations:

### Regular Operators vs Stable Functions

**Regular operators (+, -, *, /)** perform ratio conversions during each operation:
- Convert operands to compatible ratios as needed
- Return results in the type of the left-hand operand
- Suitable for general arithmetic where type conversion is expected

**Stable functions** maintain working ratios to avoid accumulating rounding errors:
- `stable_add`, `stable_subtract` convert the right operand to match the left operand's ratio
- `stable_multiply`, `stable_divide` combine ratios naturally
- Return results maintaining the ratio of the left operand
- Preferred for iterative algorithms (Newton-Raphson, Runge-Kutta) where precision matters

### Available Functions

- **Stable arithmetic**: `stable_add`, `stable_subtract`, `stable_multiply`, `stable_divide`
- **Numerical methods**: `newton_raphson`, `runge_kutta_step`
- **Math functions**: `exp`, `log`, `sqrt` (with dimensional constraints)

For long calculation chains in numerical algorithms, use `stable_*` functions to maintain precision. Regular operators are fine for general use. At the end of calculations, use `to_si()`, `in_base_si_units()`, or `unit_cast` to convert to canonical or specific unit forms.

Example:

```cpp
#include <pkr_units/si_units.h>
#include <pkr_units/math/unit_math.h>

using namespace pkr::units;
using namespace pkr::math;

kilogram_t mass{1200.0};
newton_t target_force{3600.0};
second_t time{3.0};

// Solve for speed v such that F = m * (v / t)
auto f = [=](meter_per_second_t v) { return stable_multiply(mass, v / time) - target_force; };
auto df = [=](meter_per_second_t) { return mass / time; };

auto speed = newton_raphson(meter_per_second_t{1.0}, f, df);
meter_per_second_squared_t accel = (speed / time).to_si();
```

## Formatting and I-O

Unit formatting uses `std::format` via per-system formatting headers:

- `sdk/include/pkr_units/format/si.h`
- `sdk/include/pkr_units/format/imperial_formatting.h`
- `sdk/include/pkr_units/format/cgs.h`
- `sdk/include/pkr_units/format/astronomical.h`
`measurement_t` provides `operator<<` and a `std::formatter` specialization.

```cpp
#include <pkr_units/format/si.h>
#include <format>

using namespace pkr::units;

meter_t d{12.5};
std::string s = std::format("{}", d); // "12.5 m"
```

Formatting is based on the *unit type*. If you want a different unit symbol/scale,
convert first and then format:

```cpp
using namespace pkr::units;

meter_per_second_t v{10.0};
auto v_kmh = unit_cast<kilometer_per_hour_t>(v);
std::string s = std::format("{}", v_kmh); // "36 km/h"
```

## Constants

`sdk/include/pkr_units/constants.h` exposes physical constants as:

- Typed units where available (e.g., `speed_of_light`)
- Raw values (e.g., `boltzmann_constant`) when a dedicated unit type is not defined

```cpp
#include <pkr_units/constants.h>

auto c = pkr::units::speed_of_light; // meter_per_second_t
```

## User-defined Literals

Literal operators are provided via per-system headers and are **not** pulled in by default.

Example:

```cpp
#include <pkr_units/literals/si.h>

using namespace pkr::units::literals;

auto d{5.0_km};
```

## Custom Units

Define a new unit type by providing:

1. A dimension (`dimension_t`)
2. A unit type inheriting from `details::unit_t`
3. A `derived_unit_type_t` specialization

For custom units you will typically include:
`sdk/include/pkr_units/impl/decls/unit_t_decl.h`
and `sdk/include/pkr_units/impl/dimension.h`.

```cpp
// Custom unit: furlong (length)
inline constexpr pkr::units::dimension_t custom_length_dimension{.length = 1};

struct furlong_t final
    : public pkr::units::details::unit_t<double, std::ratio<201168, 1000>, custom_length_dimension>
{
    using _base = pkr::units::details::unit_t<double, std::ratio<201168, 1000>, custom_length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"furlong"};
    static constexpr std::string_view symbol{"furlong"};
    static constexpr std::wstring_view w_symbol{L"furlong"};
    static constexpr std::u8string_view u8_symbol{u8"furlong"};
};

template <>
struct pkr::units::details::derived_unit_type_t<double, std::ratio<201168, 1000>, custom_length_dimension>
{
    using type = furlong_t;
};
```

## Extensibility

The library is designed to be extended without modifying core headers. You can:

- Add new unit types by defining a `unit_t`-derived struct and a `derived_unit_type_t` specialization.
- Add new dimensions by introducing a new `dimension_t` constant.

Example: add a new dimension and two units, then let arithmetic return the derived types:

```cpp
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/dimension.h>

namespace my_units
{
inline constexpr pkr::units::dimension_t flow_dimension{.length = 3, .time = -1}; // volume/time

struct liter_per_second_t final
    : public pkr::units::details::unit_t<double, std::ratio<1, 1000>, flow_dimension>
{
    using _base = pkr::units::details::unit_t<double, std::ratio<1, 1000>, flow_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"liter per second"};
    static constexpr std::string_view symbol{"L\u00B7s\u207B\u00B9"};
    static constexpr std::wstring_view w_symbol{L"L\u00B7s\u207B\u00B9"};
    static constexpr std::u8string_view u8_symbol{u8"L\u00B7s\u207B\u00B9"};
};

struct cubic_meter_per_second_t final
    : public pkr::units::details::unit_t<double, std::ratio<1, 1>, flow_dimension>
{
    using _base = pkr::units::details::unit_t<double, std::ratio<1, 1>, flow_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"cubic meter per second"};
    static constexpr std::string_view symbol{"m\u00b3\u00B7s\u207B\u00B9"};
    static constexpr std::wstring_view w_symbol{L"m\u00b3\u00B7s\u207B\u00B9"};
    static constexpr std::u8string_view u8_symbol{u8"m\u00b3\u00B7s\u207B\u00B9"};
};

template <>
struct pkr::units::details::derived_unit_type_t<double, std::ratio<1, 1000>, flow_dimension>
{
    using type = liter_per_second_t;
};

template <>
struct pkr::units::details::derived_unit_type_t<double, std::ratio<1, 1>, flow_dimension>
{
    using type = cubic_meter_per_second_t;
};
} // namespace my_units
```

## Appendix: Predefined Unit Types

The following unit types are defined in the headers under `sdk/include/pkr_units/units/`.

### SI Base Units

`ampere_t`, `attoampere_t`, `attocandela_t`, `attokelvin_t`, `attometer_t`, `attomole_t`
`attosecond_t`, `candela_t`, `centiampere_t`, `centicandela_t`, `centigram_t`, `centikelvin_t`
`centimeter_t`, `centimole_t`, `centisecond_t`, `decaampere_t`, `decacandela_t`, `decagram_t`
`decakelvin_t`, `decameter_t`, `decamole_t`, `decasecond_t`, `deciampere_t`, `decicandela_t`
`decigram_t`, `decikelvin_t`, `decimeter_t`, `decimole_t`, `decisecond_t`, `degree_t`, `exaampere_t`
`exacandela_t`, `exagram_t`, `exakelvin_t`, `exameter_t`, `examole_t`, `exasecond_t`
`femtoampere_t`, `femtocandela_t`, `femtokelvin_t`, `femtometer_t`, `femtomole_t`, `femtosecond_t`
`gigaampere_t`, `gigacandela_t`, `gigagram_t`, `gigakelvin_t`, `gigameter_t`, `gigamole_t`
`gigasecond_t`, `gradian_t`, `gram_t`, `hectoampere_t`, `hectocandela_t`, `hectogram_t`
`hectokelvin_t`, `hectometer_t`, `hectomole_t`, `hectosecond_t`, `hour_t`, `kelvin_t`
`day_t`, `minute_t`, `month_t`, `week_t`, `year_t`
`kiloampere_t`, `kilocandela_t`, `kilogram_t`, `kilokelvin_t`, `kilometer_t`, `kilomole_t`
`kilosecond_t`, `megaampere_t`, `megacandela_t`, `megakelvin_t`, `megameter_t`, `megamole_t`
`megasecond_t`, `meter_t`, `metric_ton_t`, `microampere_t`, `microcandela_t`, `microgram_t`
`microkelvin_t`, `micrometer_t`, `micromole_t`, `microsecond_t`, `milliampere_t`, `millicandela_t`
`milligram_t`, `millikelvin_t`, `millimeter_t`, `millimole_t`, `millisecond_t`, `mole_t`
`nanoampere_t`, `nanocandela_t`, `nanogram_t`, `nanokelvin_t`, `nanometer_t`, `nanomole_t`
`nanosecond_t`, `petaampere_t`, `petacandela_t`, `petagram_t`, `petakelvin_t`, `petameter_t`
`petamole_t`, `petasecond_t`, `picoampere_t`, `picocandela_t`, `picogram_t`, `picokelvin_t`
`picometer_t`, `picomole_t`, `picosecond_t`, `radian_t`, `second_t`, `teraampere_t`, `teracandela_t`
`teragram_t`, `terakelvin_t`, `terameter_t`, `teramole_t`, `terasecond_t`

### SI Derived Units

`atmosphere_t`, `atomic_mass_unit_per_cubic_angstrom_t`, `bar_t`, `calorie_t`
`centimeter_per_second_squared_t`, `centimeter_per_second_t`, `coulomb_t`, `cubic_centimeter_t`
`cubic_kilometer_t`, `cubic_meter_t`, `cubic_millimeter_t`, `electronvolt_t`, `farad_t`
`gigaelectronvolt_t`, `gigajoule_t`, `gigaohm_t`, `gigawatt_t`, `gram_per_cubic_centimeter_t`
`gram_per_cubic_meter_t`, `gram_per_liter_t`, `gram_per_milliliter_t`, `hectopascal_t`, `henry_t`
`josephson_t`, `joule_t`, `kilocalorie_t`, `kilocoulomb_t`, `kiloelectronvolt_t`
`kilogram_per_cubic_meter_t`, `kilogram_per_liter_t`, `kilojoule_t`, `kilometer_per_hour_t`
`kilometer_per_second_squared_t`, `kilometer_per_second_t`, `kilonewton_t`, `kiloohm_t`
`specific_heat_capacity_t`, `thermal_conductivity_t`
`kilopascal_t`, `kilotesla_t`, `kilovolt_t`, `kilowatt_hour_t`, `kilowatt_t`, `kiloweber_t`
`liter_t`, `megaelectronvolt_t`, `megajoule_t`, `meganewton_t`, `megaohm_t`, `megapascal_t`
`megatesla_t`, `megavolt_t`, `megawatt_t`, `meter_per_second_squared_t`, `meter_per_second_t`
`microcoulomb_t`, `microfarad_t`, `microhenry_t`, `microjoule_t`, `micromolar_concentration_t`
`micronewton_t`, `microohm_t`, `micropascal_t`, `microsiemens_t`, `microtesla_t`, `microvolt_t`
`microwatt_t`, `microweber_t`, `millicoulomb_t`, `millifarad_t`, `milligram_per_cubic_centimeter_t`
`milligram_per_milliliter_t`, `millihenry_t`, `millijoule_t`, `milliliter_t`
`millimeter_per_second_squared_t`, `millimeter_per_second_t`, `millimolar_concentration_t`
`millinewton_t`, `milliohm_t`, `milliosmole_per_liter_concentration_t`, `millipascal_t`
`millisiemens_t`, `millitesla_t`, `millivolt_t`, `milliwatt_t`, `milliweber_t`
`molar_concentration_t`, `mole_per_cubic_centimeter_concentration_t`
`mole_per_cubic_meter_concentration_t`, `mole_per_liter_concentration_t`
`mole_per_milliliter_concentration_t`, `nanocoulomb_t`, `nanofarad_t`, `nanohenry_t`, `nanojoule_t`
`nanomolar_concentration_t`, `nanonewton_t`, `nanopascal_t`, `nanotesla_t`, `nanowatt_t`
`nanoweber_t`, `newton_t`, `ohm_t`, `osmole_per_liter_concentration_t`, `pascal_t`, `pascal_second_t`, `picocoulomb_t`
`picofarad_t`, `picomolar_concentration_t`, `siemens_t`, `square_centimeter_t`, `square_kilometer_t`
`square_meter_t`, `square_meter_per_second_t`, `square_millimeter_t`, `standard_gravity_t`, `tesla_t`, `ton_per_cubic_meter_t`
`volt_t`, `watt_hour_t`, `watt_t`, `weber_t`

### Temperature (Affine Units)

`celsius_t`, `fahrenheit_t`

### Imperial Units

`chain_t`, `dram_t`, `fathom_t`, `feet_per_second_squared_t`, `feet_per_second_t`, `foot_t`
`furlong_t`, `grain_t`, `horsepower_t`, `hundredweight_t`, `inch_t`, `inches_per_second_t`
`knots_t`, `long_ton_t`, `mil_t`, `mile_t`, `miles_per_hour_t`, `nautical_mile_t`
`ounce_per_cubic_inch_t`, `ounce_per_fluid_ounce_t`, `ounce_t`, `pound_force_t`
`pound_per_cubic_foot_t`, `pound_per_cubic_inch_t`, `pound_per_gallon_t`, `pound_t`, `poundal_t`
`psi_t`, `rod_t`, `stone_t`, `us_ton_t`, `yard_t`

### Astronomical Units

`angstrom_t`, `au_t`, `dms_angle_t`, `dms_arcminute_t`, `dms_arcsecond_t`, `dms_degree_t`, `hms_angle_t`,
`hms_archour_t`, `hms_arcminute_t`, `hms_arcsecond_t`, `light_year_t`, `micron_t`, `parsec_t`

### CGS Units

`barye_t`, `dyne_t`, `erg_t`, `gal_t`, `gauss_t`, `maxwell_t`, `oersted_t`, `poise_t`, `stokes_t`, `statcoulomb_t`

## Build and Tests

This is a header-only library. Tests use GTest and live under `tests/`.
For local builds, use `build/build.py` from the repository root. But read the buildnotes.md first

## Glossary

Ordered by dependency (foundational → high-level). Each item lists its primary dependencies and a short role description.

1. **Primitive numeric type / scalar / magnitude** (`double`, `float`, `std::complex<double>`, `std::complex<float>`)  
   - Depends on: none.  
   - Role: Raw numeric storage used by units.

2. **`ratio` / `ratio_t`**  
   - Depends on: numeric/compile-time ratio representation.  
   - Role: Compile-time scaling factor relating a unit to a base SI unit. Reuses standard library `std::ratio`

3. **`dimension` / `dimension_t`**  
   - A unit in this system has a dimension, this is a structure that for each "SI Unit" keeps track of the exponent 
     of that unit in a calculation.
   - Role: Compile-time descriptor for physical kinds (length, mass, time, angle, etc.). When two units participate in a calculation their dimensions are combined to calculate a new (strong) type at compile time.

4. **`prefix` (SI prefixes)**  
   - Depends on: `ratio_t`.  
   - Role: Convenience names for common ratios (kilo, milli, micro).

5. **`unit_t<type_t, ratio_t, dimension_t>`**  
   - Depends on: `type_t`, `ratio_t`, `dimension_t`.  
   - Role: Core template building block for all unit/quantity types.

6. **Strong unit types** (`meter_t`, `kilogram_t`, `second_t`)  
   - Depends on: `unit_t` and appropriate `ratio_t`/`dimension_t`.  
   - Role: Concrete, named unit types that inherit from `unit_t`.

7. **`derived_unit_type_t` trait**  
   - Depends on: the set of strong unit types and `unit_t`.  
   - Role: Maps a `<type, ratio, dimension>` triplet to the most specific strong type available.

8. **`quantity` / unit value**  
   - Depends on: `unit_t`/strong unit types and numeric values.  
   - Role: The actual numeric measurement used in computations.

9. **UDLs (user-defined literals)**  
   - Depends on: strong unit types and `quantity` constructors.  
   - Role: Literal operators to create quantities in source code (e.g., `10.0_m`).

10. **`dimensionless` and angle special-case (`radian_t`)**  
    - Depends on: `dimension_t`.  
    - Role: Special-case handling and explicit angle dimension for safer compile-time checks.

11. **Coherent / canonical unit concepts**  
    - Depends on: `ratio_t`, `dimension_t`, and unit definitions.  
    - Role: Canonical representations for conversions and documentation.

12. **`constexpr` / `noexcept` usage**  
    - Depends on: `unit_t`, UDLs, and compile-time evaluability of expressions.  
    - Role: Enable zero-cost abstractions and compile-time evaluation where possible.

13. **Dimensional analysis / dimensional safety / type safety**  
    - Depends on: `dimension_t`, `unit_t`, and strong unit types.  
    - Role: Compile-time enforcement preventing invalid operations between incompatible dimensions.

14. **Measurement wrappers** (`measurement_lin_t`, `measurement_rss_t`)  
    - Depends on: `unit_t`/quantities.  
    - Role: Provide domain-specific aggregation/uncertainty semantics for multi-component measures.

15. **Vector / matrix unit types** (`vec_4d_units_t`, matrix types)  
    - Depends on: quantities, measurement wrappers, and storage policies.  
    - Role: Unit-aware linear algebra types.

16. **Storage policies** (`stack_storage`, `arena_storage`)  
    - Depends on: vector/matrix storage needs.  
    - Role: Strategies for where and how component data is stored.

17. **Arena / memory pool details** (`arena`, `slot`, `fallback`, stats)  
    - Depends on: `arena_storage` implementation.  
    - Role: Pool semantics, fallback behavior, and telemetry used by `arena_storage`.

18. **Tooling and postprocessing** (UDL normalization, docs generation, e.g., `tools/fix_udl_return_types.py`)  
    - Depends on: UDL headers, unit definitions, and naming conventions.  
    - Role: Keep generated and handwritten headers consistent and deduplicated.
