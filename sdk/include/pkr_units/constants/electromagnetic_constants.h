//
// Electromagnetic constants from CODATA 2022
// Source: https://physics.nist.gov/cuu/Constants/Table/allascii.txt
//
// Constants related to electromagnetism, Maxwell's equations, and electrical properties.

#pragma once

#include <type_traits>
#include <limits>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/derived/electrical.h>
#include <pkr_units/units/derived/magnetic_flux.h>
#include <pkr_units/units/derived/electrical/josephson.h>

PKR_UNITS_BEGIN_NAMESPACE
{

namespace details {

// ============================================================================
// Electromagnetic Constants
// ============================================================================

/**
 * @brief Characteristic impedance of vacuum
 * Symbol: Z_0, Units: ohm
 * 2022 CODATA: 376.730313412
 */
template<typename T> constexpr T vacuum_impedance()
{
    return static_cast<T>(376.730313412);
}

/**
 * @brief Josephson constant - conventional value
 * Symbol: K_J, Units: Hz/V
 * 2022 CODATA: 483597.8484e9 (conventional)
 */
template<typename T> constexpr T josephson_constant()
{
    return static_cast<T>(483597.8484e9);
}

/**
 * @brief von Klitzing constant - conventional value
 * Symbol: R_K, Units: ohm
 * 2022 CODATA: 25812.80745 (conventional)
 */
template<typename T> constexpr T von_klitzing_constant()
{
    return static_cast<T>(25812.80745);
}

/**
 * @brief Magnetic flux quantum
 * Symbol: Φ_0, Units: Wb
 * 2022 CODATA: 2.067833848e-15
 */
template<typename T> constexpr T magnetic_flux_quantum()
{
    return static_cast<T>(2.067833848e-15);
}

/**
 * @brief Conductance quantum
 * Symbol: G_0, Units: S
 * 2022 CODATA: 7.748091729e-5
 */
template<typename T> constexpr T conductance_quantum()
{
    return static_cast<T>(7.748091729e-5);
}

/**
 * @brief Inverse of conductance quantum
 * Symbol: 1/G_0, Units: ohm
 * 2022 CODATA: 12906.40372
 */
template<typename T> constexpr T inverse_conductance_quantum()
{
    return static_cast<T>(12906.40372);
}

}  // namespace details

// ============================================================================
// Electromagnetic Constants
// ============================================================================

// Note: Using appropriate unit types for type safety
constexpr ohm_t vacuum_impedance{details::vacuum_impedance<double>()};
constexpr josephson_t josephson_constant{details::josephson_constant<double>()};
constexpr ohm_t von_klitzing_constant{details::von_klitzing_constant<double>()};
constexpr weber_t magnetic_flux_quantum{details::magnetic_flux_quantum<double>()};
constexpr siemens_t conductance_quantum{details::conductance_quantum<double>()};
constexpr ohm_t inverse_conductance_quantum{details::inverse_conductance_quantum<double>()};

}  // namespace PKR_UNITS_NAMESPACE