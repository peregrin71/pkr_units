//
// Unit conversion constants from CODATA 2022
// Source: https://physics.nist.gov/cuu/Constants/Table/allascii.txt
//
// Conversion factors between different units commonly used in physics.

#pragma once

#include <type_traits>
#include <limits>

#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

namespace details {

// ============================================================================
// Energy Unit Conversions
// ============================================================================

/**
 * @brief Electron volt
 * Symbol: eV, Units: J
 * 2022 CODATA: 1.602176634e-19 (exact)
 */
template<typename T> constexpr T electron_volt()
{
    return static_cast<T>(1.602176634e-19);
}

/**
 * @brief Electron volt-hartree relationship
 * Symbol: E_h, Units: eV
 * 2022 CODATA: 27.211386245981
 */
template<typename T> constexpr T hartree_in_ev()
{
    return static_cast<T>(27.211386245981);
}

/**
 * @brief Atomic mass unit-electron volt relationship
 * Symbol: u, Units: eV
 * 2022 CODATA: 931494103.72
 */
template<typename T> constexpr T atomic_mass_unit_in_ev()
{
    return static_cast<T>(931494103.72);
}

/**
 * @brief Atomic mass unit-hertz relationship
 * Symbol: u, Units: Hz
 * 2022 CODATA: 2.25234272185e23
 */
template<typename T> constexpr T atomic_mass_unit_in_hz()
{
    return static_cast<T>(2.25234272185e23);
}

// ============================================================================
// Wavelength/Frequency Conversions
// ============================================================================

/**
 * @brief Electron volt-hertz relationship
 * Symbol: eV, Units: Hz
 * 2022 CODATA: 2.417989242e14 (exact)
 */
template<typename T> constexpr T ev_in_hz()
{
    return static_cast<T>(2.417989242e14);
}

/**
 * @brief Electron volt-inverse meter relationship
 * Symbol: eV, Units: m⁻¹
 * 2022 CODATA: 8.065543937e5 (exact)
 */
template<typename T> constexpr T ev_in_inverse_meter()
{
    return static_cast<T>(8.065543937e5);
}

/**
 * @brief Hertz-inverse meter relationship
 * Symbol: Hz, Units: m⁻¹
 * 2022 CODATA: 3.335640951e-9 (exact)
 */
template<typename T> constexpr T hz_in_inverse_meter()
{
    return static_cast<T>(3.335640951e-9);
}

}  // namespace details

// ============================================================================
// Conversion Constants
// ============================================================================

// Energy conversions
constexpr auto electron_volt = details::electron_volt<double>();
constexpr auto hartree_in_ev = details::hartree_in_ev<double>();
constexpr auto atomic_mass_unit_in_ev = details::atomic_mass_unit_in_ev<double>();
constexpr auto atomic_mass_unit_in_hz = details::atomic_mass_unit_in_hz<double>();

// Spectral conversions
constexpr auto ev_in_hz = details::ev_in_hz<double>();
constexpr auto ev_in_inverse_meter = details::ev_in_inverse_meter<double>();
constexpr auto hz_in_inverse_meter = details::hz_in_inverse_meter<double>();

}  // namespace PKR_UNITS_NAMESPACE