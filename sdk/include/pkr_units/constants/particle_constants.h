//
// Particle physics constants from CODATA 2022
// Source: https://physics.nist.gov/cuu/Constants/Table/allascii.txt
//
// Masses and properties of elementary particles and common isotopes.

#pragma once

#include <type_traits>
#include <limits>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/mass.h>

PKR_UNITS_BEGIN_NAMESPACE
{

namespace details {

// ============================================================================
// Elementary Particle Masses
// ============================================================================

/**
 * @brief Muon mass
 * Symbol: m_μ, Units: kg
 * 2022 CODATA: 1.883531627e-28
 */
template<typename T> constexpr T muon_mass()
{
    return static_cast<T>(1.883531627e-28);
}

/**
 * @brief Tau mass
 * Symbol: m_τ, Units: kg
 * 2022 CODATA: 3.16754e-27
 */
template<typename T> constexpr T tau_mass()
{
    return static_cast<T>(3.16754e-27);
}

// ============================================================================
// Common Isotope Masses
// ============================================================================

/**
 * @brief Deuteron mass
 * Symbol: m_d, Units: kg
 * 2022 CODATA: 3.3435837768e-27
 */
template<typename T> constexpr T deuteron_mass()
{
    return static_cast<T>(3.3435837768e-27);
}

/**
 * @brief Triton mass
 * Symbol: m_t, Units: kg
 * 2022 CODATA: 5.0073567512e-27
 */
template<typename T> constexpr T triton_mass()
{
    return static_cast<T>(5.0073567512e-27);
}

/**
 * @brief Helion mass (³He nucleus)
 * Symbol: m_h, Units: kg
 * 2022 CODATA: 5.0064127862e-27
 */
template<typename T> constexpr T helion_mass()
{
    return static_cast<T>(5.0064127862e-27);
}

/**
 * @brief Alpha particle mass
 * Symbol: m_α, Units: kg
 * 2022 CODATA: 6.6446573450e-27
 */
template<typename T> constexpr T alpha_particle_mass()
{
    return static_cast<T>(6.6446573450e-27);
}

}  // namespace details

// ============================================================================
// Particle Physics Constants
// ============================================================================

// Note: Particle constants with appropriate unit types
constexpr kilogram_t muon_mass{details::muon_mass<double>()};
constexpr kilogram_t tau_mass{details::tau_mass<double>()};
constexpr kilogram_t deuteron_mass{details::deuteron_mass<double>()};
constexpr kilogram_t triton_mass{details::triton_mass<double>()};
constexpr kilogram_t helion_mass{details::helion_mass<double>()};
constexpr kilogram_t alpha_particle_mass{details::alpha_particle_mass<double>()};

}  // namespace PKR_UNITS_NAMESPACE