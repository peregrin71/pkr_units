//
// Atomic physics constants from CODATA 2022
// Source: https://physics.nist.gov/cuu/Constants/Table/allascii.txt
//
// These constants are commonly used in atomic physics calculations,
// spectroscopy, and quantum mechanics.

#pragma once

#include <type_traits>
#include <limits>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/base/mass.h>
#include <pkr_units/units/derived/mechanical/energy.h>

namespace PKR_UNITS_NAMESPACE
{

namespace details
{

// ============================================================================
// Atomic Physics Constants
// ============================================================================

/**
 * @brief Bohr radius - radius of hydrogen atom ground state
 * Symbol: a_0, Units: m
 * 2022 CODATA: 5.29177210544e-11
 */
template <typename T>
constexpr T bohr_radius()
{
    return static_cast<T>(5.29177210544e-11);
}

/**
 * @brief Rydberg constant - fundamental constant for atomic spectra
 * Symbol: R_∞, Units: m⁻¹
 * 2022 CODATA: 10973731.568157
 */
template <typename T>
constexpr T rydberg_constant()
{
    return static_cast<T>(10973731.568157);
}

/**
 * @brief Hartree energy - atomic unit of energy
 * Symbol: E_h, Units: J
 * 2022 CODATA: 4.3597447222060e-18
 */
template <typename T>
constexpr T hartree_energy()
{
    return static_cast<T>(4.3597447222060e-18);
}

/**
 * @brief Hartree energy in eV
 * Symbol: E_h, Units: eV
 * 2022 CODATA: 27.211386245981
 */
template <typename T>
constexpr T hartree_energy_ev()
{
    return static_cast<T>(27.211386245981);
}

} // namespace details

// ============================================================================
// Atomic Physics Constants
// ============================================================================

// Note: Atomic constants with appropriate unit types
constexpr meter_t bohr_radius{details::bohr_radius<double>()};
constexpr auto rydberg_constant = details::rydberg_constant<double>(); // 1/meter, using auto for now
constexpr joule_t hartree_energy{details::hartree_energy<double>()};

} // namespace PKR_UNITS_NAMESPACE
