//
// High-precision physical constants that can be retrieved at float, double, or long double precision.
// All values are from CODATA 2022 or SI 9th edition and are precise enough for long double representation.
// 
// Constants are defined as function templates in the details namespace, with typed SI unit instances
// created in the main si:: namespace for use throughout the codebase.

#pragma once

#include <type_traits>
#include <limits>

// Include unit type definitions if available
#include <pkr_units/units/base/mass.h>
#include <pkr_units/units/derived/velocity.h>

namespace PKR_UNITS_NAMESPACE {

namespace details
{    

// ============================================================================
// Fundamental Physical Constants (CODATA 2022 / SI 9th edition)
// ============================================================================

/**
 * @brief Avogadro's number - amount of particles per mole
 * Symbol: Nₐ, Units: mol⁻¹
 * 2022 CODATA: 6.02214076e23 exactly (defined)
 */
template<typename T> constexpr T avogadro() 
{ 
    return static_cast<T>(6.02214076e23); 
}

/**
 * @brief Speed of light in vacuum
 * Symbol: c, Units: m/s
 * 2022 CODATA: 299792458 exactly (defined)
 */
template<typename T> constexpr T speed_of_light() 
{ 
    return static_cast<T>(299792458.0); 
}

/**
 * @brief Planck constant
 * Symbol: h, Units: J·s
 * 2022 CODATA: 6.62607015e-34 exactly (defined)
 */
template<typename T> constexpr T planck_constant() 
{ 
    return static_cast<T>(6.62607015e-34); 
}

/**
 * @brief Reduced Planck constant (Dirac constant)
 * Symbol: ℏ = h/(2π), Units: J·s
 * Value: 1.054571817e-34
 */
template<typename T> constexpr T reduced_planck_constant() 
{ 
    return static_cast<T>(1.054571817e-34); 
}

/**
 * @brief Boltzmann constant - energy per temperature
 * Symbol: k_B, Units: J/K
 * 2022 CODATA: 1.380649e-23 exactly (defined)
 */
template<typename T> constexpr T boltzmann_constant() 
{ 
    return static_cast<T>(1.380649e-23); 
}

/**
 * @brief Elementary charge - magnitude of electron charge
 * Symbol: e, Units: C
 * 2022 CODATA: 1.602176634e-19 exactly (defined)
 */
template<typename T> constexpr T elementary_charge() 
{ 
    return static_cast<T>(1.602176634e-19); 
}

/**
 * @brief Gravitational constant
 * Symbol: G, Units: m³/(kg·s²)
 * 2022 CODATA: 6.67430e-11
 */
template<typename T> constexpr T gravitational_constant() 
{ 
    return static_cast<T>(6.67430e-11); 
}

/**
 * @brief Fine structure constant - dimensionless fundamental constant
 * Symbol: α
 * 2022 CODATA: 7.2973525693e-3
 */
template<typename T> constexpr T fine_structure_constant() 
{ 
    return static_cast<T>(7.2973525693e-3); 
}

// ============================================================================
// Derived Physical Constants
// ============================================================================

/**
 * @brief Standard acceleration due to gravity
 * Symbol: g, Units: m/s²
 * Value: 9.80665 m/s² (defined)
 */
template<typename T> constexpr T standard_gravity() 
{ 
    return static_cast<T>(9.80665); 
}

/**
 * @brief Vacuum permeability (magnetic constant)
 * Symbol: μ₀, Units: H/m
 * Value: 4π × 10⁻⁷ = 1.25663706212e-6
 */
template<typename T> constexpr T vacuum_permeability() 
{ 
    return static_cast<T>(1.25663706212e-6); 
}

/**
 * @brief Vacuum permittivity (electric constant)
 * Symbol: ε₀, Units: F/m
 * Value: 1/(μ₀ × c²) = 8.8541878128e-12
 */
template<typename T> constexpr T vacuum_permittivity() 
{ 
    return static_cast<T>(8.8541878128e-12); 
}

/**
 * @brief Molar gas constant - R = N_A × k_B
 * Symbol: R, Units: J/(mol·K)
 * Value: 8.314462618
 */
template<typename T> constexpr T molar_gas_constant() 
{ 
    return static_cast<T>(8.314462618); 
}

/**
 * @brief Stefan-Boltzmann constant - radiation power per area per temperature
 * Symbol: σ, Units: W/(m²·K⁴)
 * Value: (π²/60) × k_B⁴ / (ℏ³ × c²) = 5.670374419e-8
 */
template<typename T> constexpr T stefan_boltzmann() 
{ 
    return static_cast<T>(5.670374419e-8); 
}

// ============================================================================
// Particle Masses
// ============================================================================

/**
 * @brief Electron rest mass
 * Symbol: m_e, Units: kg
 * 2022 CODATA: 9.1093837015e-31
 */
template<typename T> constexpr T electron_mass() 
{ 
    return static_cast<T>(9.1093837015e-31); 
}

/**
 * @brief Proton rest mass
 * Symbol: m_p, Units: kg
 * 2022 CODATA: 1.67262192369e-27
 */
template<typename T> constexpr T proton_mass() 
{ 
    return static_cast<T>(1.67262192369e-27); 
}

/**
 * @brief Neutron rest mass
 * Symbol: m_n, Units: kg
 * 2022 CODATA: 1.67492749804e-27
 */
template<typename T> constexpr T neutron_mass() 
{ 
    return static_cast<T>(1.67492749804e-27); 
}

}  // namespace details

// ============================================================================
// SI Unit Constants - Typed Instances in si:: Namespace
// ============================================================================
// These constants are created as actual SI unit types for type-safe calculations.
// Each constant's units are appropriate to its physical dimension.

// Physical particle masses (SI unit instances)
constexpr kilogram electron_mass{details::electron_mass<double>()};
constexpr kilogram proton_mass{details::proton_mass<double>()};
constexpr kilogram neutron_mass{details::neutron_mass<double>()};

// Speed of light (velocity constant)
constexpr meter_per_second speed_of_light{details::speed_of_light<double>()};

// Raw numerical constants (dimensionless or awaiting dedicated SI unit types)
// These are available as constexpr for compile-time use
constexpr auto avogadro = details::avogadro<double>();
constexpr auto planck_constant = details::planck_constant<double>();
constexpr auto reduced_planck_constant = details::reduced_planck_constant<double>();
constexpr auto boltzmann_constant = details::boltzmann_constant<double>();
constexpr auto elementary_charge = details::elementary_charge<double>();
constexpr auto gravitational_constant = details::gravitational_constant<double>();
constexpr auto fine_structure_constant = details::fine_structure_constant<double>();
constexpr auto standard_gravity = details::standard_gravity<double>();
constexpr auto vacuum_permeability = details::vacuum_permeability<double>();
constexpr auto vacuum_permittivity = details::vacuum_permittivity<double>();
constexpr auto molar_gas_constant = details::molar_gas_constant<double>();
constexpr auto stefan_boltzmann = details::stefan_boltzmann<double>();

}  // namespace PKR_UNITS_NAMESPACE






