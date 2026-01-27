#pragma once

/**
 * @file namespace_config.h
 * @brief Namespace configuration for SI Units library
 * 
 * This header allows users to customize the root namespace used by the SI Units library.
 * 
 * By default, all units are defined in the `pkr::units` namespace. However, if your codebase
 * prefers a different namespace, you can override it by defining `PKR_UNITS_NAMESPACE` before 
 * including any SI Units headers:
 * 
 * @code
 * // Option 1: Use a different namespace (must be done before including pkr_units headers)
 * #define PKR_UNITS_NAMESPACE physics
 * #include <pkr_units/si.h>
 * 
 * // Now all SI units are in physics namespace
 * physics::meter distance = 5.0_m;
 * physics::kilogram mass = 10.0_kg;
 * 
 * // Option 2: Use nested namespace
 * #define PKR_UNITS_NAMESPACE my_app::units
 * #include <pkr_units/si.h>
 * 
 * // Now units are in my_app::units
 * my_app::units::meter distance = 5.0_m;
 * @endcode
 * 
 * If `PKR_UNITS_NAMESPACE` is not defined, it defaults to `pkr::units`.
 */

#ifndef PKR_UNITS_NAMESPACE
    #define PKR_UNITS_NAMESPACE pkr::units
#endif

/**
 * @def PKR_UNITS_BEGIN_NAMESPACE
 * @brief Begin the Units namespace block
 * 
 * Usage in headers:
 * @code
 * PKR_UNITS_BEGIN_NAMESPACE
 * {
 *     // Unit definitions go here
 * }  // namespace PKR_UNITS_NAMESPACE
 * @endcode
 */
#define PKR_UNITS_BEGIN_NAMESPACE namespace PKR_UNITS_NAMESPACE

/**
 * @def PKR_UNITS_DETAILS_BEGIN_NAMESPACE
 * @brief Begin the Units details namespace block (for implementation details)
 * 
 * Usage in headers:
 * @code
 * PKR_UNITS_DETAILS_BEGIN_NAMESPACE
 * {
 *     // Implementation details go here
 * }  // namespace details
 * }  // namespace PKR_UNITS_NAMESPACE
 * @endcode
 */
#define PKR_UNITS_DETAILS_BEGIN_NAMESPACE namespace PKR_UNITS_NAMESPACE { namespace details






