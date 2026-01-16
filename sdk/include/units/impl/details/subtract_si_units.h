// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "arithmetic_helpers.h"
#include "dimension.h"

// ============================================================================
// Subtraction Operations
// ============================================================================
// Free-function operator- for any two si_unit types with matching dimensions.
// Returns result in the same unit type as the LHS operand.
//
// Key Design Decisions:
// - Dimensions must match exactly (enforced at compile-time via requires clause)
// - Result is always in LHS unit type for predictable, consistent behavior
// - Optimization: when both operands have identical ratios, no conversion overhead
// - When ratios differ: converts both to canonical, subtracts, then converts back to LHS ratio
//
// Examples:
//   meter(8) - meter(3)        → meter(5)          [same ratio, no conversion]
//   meter(1500) - kilometer(1) → meter(500)        [different ratio, returns LHS type]
//   kilometer(2) - meter(500)  → kilometer(1.5)    [different ratio, returns LHS type]

// Free-function operator- for any two si_unit types with matching dimensions
// Returns result in LHS unit type
template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr T1 operator-(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename is_si_unit<T1>::value_type;
    constexpr dimension_t dim = is_si_unit<T1>::value_dimension;
    using result_ratio = typename is_si_unit<T1>::ratio_type;
    using ratio1 = typename is_si_unit<T1>::ratio_type;
    using ratio2 = typename is_si_unit<T2>::ratio_type;
    
    // Optimization: if both have same ratio, just subtract and keep the type
    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        return T1{lhs.value() - rhs.value()};
    }
    else
    {
        // Different ratios: convert both to canonical, subtract, then convert back to LHS ratio
        value_type canonical_diff = si::subtract_canonical<value_type, ratio1, ratio2>(
            lhs.value(), rhs.value()
        );
        // Convert from canonical to LHS ratio
        value_type converted = si::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
            canonical_diff
        );
        return T1{converted};
    }
}
