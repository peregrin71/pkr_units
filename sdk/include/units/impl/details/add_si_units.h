// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "arithmetic_helpers.h"
#include "dimension.h"

// ============================================================================
// Addition Operations
// ============================================================================
// Free-function operator+ for any two si_unit types with matching dimensions.
// Returns result in the canonical base SI unit (meter, kilogram, second, etc.).
//
// Key Design Decisions:
// - Dimensions must match exactly (enforced at compile-time via requires clause)
// - Result always in canonical unit (ratio<1,1>) for predictable return type
// - Delegates to add_canonical helper for arithmetic (reduces binary bloat)
//
// Examples:
//   meter(5) + kilometer(2)     → meter(2005)
//   kilometer(1) + meter(500)   → meter(1500)
//   decimeter(30) + millimeter(2000) → meter(5)

// Free-function operator+ for any two si_unit types with matching dimensions
// Returns result in the canonical base SI unit (meter, kilogram, second, etc.)
// OPTIMIZATION: If both operands have identical ratios, returns result in the same unit type
// (no conversion needed). Otherwise returns canonical form.
template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr auto operator+(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename is_si_unit<T1>::value_type;
    constexpr dimension_t dim = is_si_unit<T1>::value_dimension;
    using ratio1 = typename is_si_unit<T1>::ratio_type;
    using ratio2 = typename is_si_unit<T2>::ratio_type;
    
    // Optimization: if both have same ratio, just add and keep the type
    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        using result_type = unit_t<value_type, ratio1, dim>;
        return result_type(lhs.value() + rhs.value());
    }
    else
    {
        // Different ratios - convert to canonical
        using result_type = unit_t<value_type, std::ratio<1, 1>, dim>;
        return result_type(
            si::add_canonical<value_type, ratio1, ratio2>(
                lhs.value(), rhs.value()
            )
        );
    }
}

// Free function to add two si_unit types and convert result to a specified unit type.
// Useful when you want the result in a specific unit rather than canonical form.
//
// Template Parameters:
//   ResultType: The desired output unit type (e.g., si::millimeter)
//   T1, T2:     The input unit types (must have matching dimensions)
//
// Example:
//   si::add<si::millimeter>(decimeter(3.0), kilometer(2.0)) → millimeter(2000300)
//   // Result: 0.3m + 2000m = 2000.3m = 2000300mm
template<si_unit_type ResultType, si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension &&
          is_si_unit<T1>::value_dimension == is_si_unit<ResultType>::value_dimension)
constexpr auto add(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename is_si_unit<ResultType>::value_type;
    using result_ratio = typename is_si_unit<ResultType>::ratio_type;
    constexpr dimension_t dim = is_si_unit<ResultType>::value_dimension;
    
    // Add the values in canonical form (ratio<1,1>)
    value_type canonical_sum = si::add_canonical<value_type, 
                                                 typename is_si_unit<T1>::ratio_type,
                                                 typename is_si_unit<T2>::ratio_type>(
        lhs.value(), rhs.value()
    );
    
    // Convert from canonical unit to the target result unit ratio
    value_type converted = si::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
        canonical_sum
    );
    
    return unit_t<value_type, result_ratio, dim>(converted);
}
