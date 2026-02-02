#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/units/base/mass.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/base/time.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Irradiance (Watts per Square Meter)
// ============================================================================
//
// Irradiance is the radiant flux incident on a surface per unit area.
// Unit: watt per square meter (W/m²)
// Dimension: [M·T⁻³]
//
// CHARACTERISTICS:
// - Measures electromagnetic radiation power received per unit area
// - Independent of direction (scalar quantity at a point)
// - Fundamental radiometry quantity parallel to illuminance in photometry
// - Depends on distance from source and surface orientation
//
// RELATIONSHIPS:
// - Irradiance = Radiant flux / Area [W / m²]
// - Irradiance = Radiance × Solid angle [W/m²] (for point source)
// - Radiant flux = Irradiance × Area [W]
//
// TYPICAL VALUES:
// - Solar constant (at Earth orbit): ~1361 W/m²
// - Bright sunlight (sea level, normal incidence): ~1000 W/m²
// - Cloudy day (sea level): ~100 W/m²
// - Office lighting: ~400 W/m² (visible only)
// - Thermal radiation from human body on surface: ~1 W/m² at 2m distance
// - Laser beam (1W laser, 1mm spot): ~10⁹ W/m²
//
// APPLICATIONS:
// - Solar energy systems and panel specifications
// - Sensor calibration and characterization
// - Radiometer measurements
// - UV exposure assessment
// - Thermal radiation studies
// - Astronomical observations
// - Environmental monitoring (UV index)
//
// NOTE: Irradiance is the radiometric equivalent of illuminance (lux).
// Where photometry weights by human eye sensitivity (illuminance in lux),
// radiometry treats all electromagnetic wavelengths equally (irradiance in W/m²).
//
// SPECTRAL IRRADIANCE:
// Spectral irradiance is irradiance per unit wavelength [W/(m³)]
// or per unit frequency [W/(m²·Hz)], used in detailed spectroscopy.

// Strong type for watt_per_square_meter (irradiance)
struct watt_per_square_meter_t final : public details::unit_t<double, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, 0}>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, 0}>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"watt_per_square_meter"};

    [[maybe_unused]] static constexpr std::string_view symbol{"W/m2"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W\u00b7m\u207b\u00b2"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W\u00b7m\u207b\u00b2"};

};

// Shorter alias for irradiance
struct irradiance_t final : public details::unit_t<double, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, 0}>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, 0}>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"irradiance"};

    [[maybe_unused]] static constexpr std::string_view symbol{"W/m2"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W\u00b7m\u207b\u00b2"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W\u00b7m\u207b\u00b2"};

};

// ============================================================================
// Derived unit type specializations
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, 0}>
{
    using type = irradiance_t;
};

} // namespace PKR_UNITS_NAMESPACE
