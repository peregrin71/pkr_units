#pragma once

/**
 * @file namespace_config.h
 * @brief Namespace configuration for SI Units library
 * 
 * This header allows users to customize the root namespace used by the SI Units library.
 * 
 * By default, all SI units are defined in the `si` namespace. However, if your codebase
 * already has a namespace named `si` (or you prefer a different namespace), you can
 * override it by defining `PKR_SI_NAMESPACE` before including any SI Units headers:
 * 
 * @code
 * // Option 1: Use a different namespace (must be done before including si_units headers)
 * #define PKR_SI_NAMESPACE physics
 * #include <si_units/si.h>
 * 
 * // Now all SI units are in physics namespace
 * physics::meter distance = 5.0_m;
 * physics::kilogram mass = 10.0_kg;
 * 
 * // Option 2: Use nested namespace
 * #define PKR_SI_NAMESPACE my_app::units::si
 * #include <si_units/si.h>
 * 
 * // Now units are in my_app::units::si
 * my_app::units::si::meter distance = 5.0_m;
 * @endcode
 * 
 * If `PKR_SI_NAMESPACE` is not defined, it defaults to `si`.
 */

#ifndef PKR_SI_NAMESPACE
    #define PKR_SI_NAMESPACE si
#endif

/**
 * @def PKR_SI_BEGIN_NAMESPACE
 * @brief Begin the SI Units namespace block
 * 
 * Usage in headers:
 * @code
 * PKR_SI_BEGIN_NAMESPACE
 * {
 *     // SI unit definitions go here
 * }
 * PKR_SI_NAMESPACE_END
 * @endcode
 */
#define PKR_SI_BEGIN_NAMESPACE namespace PKR_SI_NAMESPACE

/**
 * @def PKR_SI_NAMESPACE_END
 * @brief End the SI Units namespace block (matches PKR_SI_BEGIN_NAMESPACE)
 */
#define PKR_SI_NAMESPACE_END }
