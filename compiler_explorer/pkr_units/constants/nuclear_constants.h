//
// Nuclear physics constants from CODATA 2022
// Source: https://physics.nist.gov/cuu/Constants/Table/allascii.txt
//
// Constants related to nuclear physics, radioactivity, and nuclear structure.

#pragma once

#include <type_traits>
#include <limits>

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/length.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/area/area_units.h"

namespace PKR_UNITS_NAMESPACE
{

namespace details
{

// ============================================================================
// Nuclear Physics Constants
// ============================================================================

/**
 * @brief Fermi coupling constant
 * Symbol: G_F, Units: GeV⁻²
 * 2022 CODATA: 1.1663787e-5
 */
template <typename T>
constexpr T fermi_coupling_constant()
{
    return static_cast<T>(1.1663787e-5);
}

/**
 * @brief Weak mixing angle (on-shell scheme)
 * Symbol: sin²θ_W, Units: dimensionless
 * 2022 CODATA: 0.22305
 */
template <typename T>
constexpr T weak_mixing_angle()
{
    return static_cast<T>(0.22305);
}

/**
 * @brief Classical electron radius
 * Symbol: r_e, Units: m
 * 2022 CODATA: 2.8179403205e-15
 */
template <typename T>
constexpr T classical_electron_radius()
{
    return static_cast<T>(2.8179403205e-15);
}

/**
 * @brief Thomson cross section
 * Symbol: σ_T, Units: m²
 * 2022 CODATA: 6.6524587051e-29
 */
template <typename T>
constexpr T thomson_cross_section()
{
    return static_cast<T>(6.6524587051e-29);
}

/**
 * @brief Neutron Compton wavelength
 * Symbol: λ_C,n, Units: m
 * 2022 CODATA: 1.31959090382e-15
 */
template <typename T>
constexpr T neutron_compton_wavelength()
{
    return static_cast<T>(1.31959090382e-15);
}

/**
 * @brief Proton Compton wavelength
 * Symbol: λ_C,p, Units: m
 * 2022 CODATA: 1.32140985360e-15
 */
template <typename T>
constexpr T proton_compton_wavelength()
{
    return static_cast<T>(1.32140985360e-15);
}

} // namespace details

// ============================================================================
// Nuclear Physics Constants
// ============================================================================

// Note: Nuclear constants with appropriate unit types
constexpr auto fermi_coupling_constant = details::fermi_coupling_constant<double>();
constexpr auto weak_mixing_angle = details::weak_mixing_angle<double>();
constexpr meter_t classical_electron_radius{details::classical_electron_radius<double>()};
constexpr square_meter_t thomson_cross_section{details::thomson_cross_section<double>()};
constexpr meter_t neutron_compton_wavelength{details::neutron_compton_wavelength<double>()};
constexpr meter_t proton_compton_wavelength{details::proton_compton_wavelength<double>()};

} // namespace PKR_UNITS_NAMESPACE
