#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/units/base/mass.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/base/time.h>
#include <pkr_units/units/base/solid_angle.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Radiant Intensity (Watts per Steradian)
// ============================================================================
//
// Radiant intensity is the radiant flux emitted per unit solid angle.
// Unit: watt per steradian (W/sr)
// Dimension: [M·L²·T⁻³] / [sr] = [M·L²·T⁻³·sr⁻¹]
//
// CHARACTERISTICS:
// - Measures electromagnetic radiation power per solid angle
// - Independent of distance from source
// - Fundamental radiometry quantity parallel to luminous intensity in photometry
// - Accounts for directional distribution of radiation
//
// RELATIONSHIPS:
// - Radiant intensity = Radiant flux / Solid angle [W / sr]
// - Radiant flux = Radiant intensity × Solid angle [W]
// - Radiance = Radiant intensity / Projected area [W / (m² · sr)]
//
// APPLICATIONS:
// - Thermal radiation characterization
// - Sensor calibration
// - Radiometer design and specifications
// - Infrared thermography
// - Solar radiation measurements
// - Antenna radiation patterns
//
// NOTE: This is the radiometric equivalent of luminous intensity (candela).
// Where photometry is weighted for human eye sensitivity,
// radiometry treats all wavelengths equally.

// Strong type for watt_per_steradian (radiant intensity)
struct watt_per_steradian_t final : public details::unit_t<double, std::ratio<1, 1>, dimension_t{1, 2, -3, 0, 0, 0, 0, 0, -1}>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, dimension_t{1, 2, -3, 0, 0, 0, 0, 0, -1}>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"watt_per_steradian"};

    [[maybe_unused]] static constexpr std::string_view symbol{"W/sr"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W\u00b7sr\u207b\u00b9"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W\u00b7sr\u207b\u00b9"};
};

// ============================================================================
// Derived unit type specialization
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, dimension_t{1, 2, -3, 0, 0, 0, 0, 0, -1}>
{
    using type = watt_per_steradian_t;
};

} // namespace PKR_UNITS_NAMESPACE
