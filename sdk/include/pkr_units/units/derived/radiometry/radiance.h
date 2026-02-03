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
// Radiance (Watts per Square Meter per Steradian)
// ============================================================================
//
// Radiance is the radiant intensity per unit projected area.
// Unit: watt per square meter per steradian (W/(m²·sr))
// Dimension: [M·T⁻³·sr⁻¹]
//
// CHARACTERISTICS:
// - Measures electromagnetic radiation intensity per unit area and solid angle
// - Fundamental radiometric quantity (directional intensity)
// - Key parameter for radiative transfer and thermal radiation
// - Independent of distance (appears same from all viewing directions)
// - Intrinsic property of radiation sources and receiving surfaces
//
// RELATIONSHIPS:
// - Radiance = Radiant intensity / Projected area [W / (m² · sr)]
// - Radiance = Irradiance / Solid angle [W / (m² · sr)]
// - Radiant intensity = Radiance × Projected area [(W/(m²·sr)) × m² = W/sr]
//
// BLACKBODY RADIATION:
// Stefan-Boltzmann Law: Radiance = σ·T⁴ (for perfect blackbody)
// where σ = 5.67×10⁻⁸ W/(m²·K⁴)
//
// PLANCK'S LAW:
// Spectral radiance describes wavelength-dependent radiation
// L(λ,T) = (2hc²/λ⁵) / (exp(hc/λkT) - 1) [W/(m³·sr)]
//
// TYPICAL VALUES:
// - Tungsten filament (2000K): ~1 MW/(m²·sr)
// - Human skin (310K): ~500 W/(m²·sr) in infrared
// - Clear blue sky: ~1000-3000 W/(m²·sr) in visible
// - Black coal at 300K: ~10 W/(m²·sr) in far IR
//
// APPLICATIONS:
// - Thermal imaging and infrared cameras
// - Radiative heat transfer calculations
// - Spectroscopy and photometry
// - Astronomical observations
// - Sensor response characterization
// - Emissivity measurements
// - Climate modeling (Earth radiation budget)
//
// NOTE: Radiance is the fundamental radiometric quantity because it's
// conserved along ray paths (invariant under optical transformations).
// This makes it ideal for radiative transfer calculations.
//
// RELATIONSHIP TO LUMINANCE:
// Luminance is the photometric equivalent (visible light weighted for human eye).
// Radiance treats all wavelengths equally; luminance weights by eye sensitivity.
// Strong type for watt_per_square_meter_per_steradian (radiance)
template <is_unit_value_type_c T>
struct watt_per_square_meter_per_steradian_t final : public details::unit_t<T, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, -1}>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, -1}>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"watt_per_square_meter_per_steradian"};
    [[maybe_unused]] static constexpr std::string_view symbol{"W/(m2·sr)"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W\u00b7m\u207b\u00b2\u00b7sr\u207b\u00b9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W\u00b7m\u207b\u00b2\u00b7sr\u207b\u00b9"};
};

template <is_unit_value_type_c T>
watt_per_square_meter_per_steradian_t(T) -> watt_per_square_meter_per_steradian_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == dimension_t{1, -2, -3, 0, 0, 0, 0, 0, -1})
watt_per_square_meter_per_steradian_t(const U&) -> watt_per_square_meter_per_steradian_t<typename details::is_pkr_unit<U>::value_type>;

// Shorter alias for radiance
template <is_unit_value_type_c T>
struct radiance_t final : public details::unit_t<T, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, -1}>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, -1}>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"radiance"};
    [[maybe_unused]] static constexpr std::string_view symbol{"W/(m2·sr)"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W\u00b7m\u207b\u00b2\u00b7sr\u207b\u00b9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W\u00b7m\u207b\u00b2\u00b7sr\u207b\u00b9"};
};

template <is_unit_value_type_c T>
radiance_t(T) -> radiance_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == dimension_t{1, -2, -3, 0, 0, 0, 0, 0, -1})
radiance_t(const U&) -> radiance_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Derived unit type specializations
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, dimension_t{1, -2, -3, 0, 0, 0, 0, 0, -1}>
{
    using type = radiance_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
