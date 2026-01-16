// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "arithmetic_helpers.h"
#include "dimension.h"

// ============================================================================
// Subtraction Operations
// ============================================================================
// Free-function operator- for any two si_unit types with matching dimensions.
// Returns result in the canonical base SI unit (meter, kilogram, second, etc.).
//
// Key Design Decisions:
// - Dimensions must match exactly (enforced at compile-time via requires clause)
// - Result always in canonical unit (ratio<1,1>) for predictable return type
// - Delegates to subtract_canonical helper for arithmetic (reduces binary bloat)
//
// Examples:
//   meter(5) - kilometer(2)     → meter(-1995)
//   kilometer(3) - meter(500)   → meter(2500)
//   decimeter(50) - millimeter(2000) → meter(3)

// Free-function operator- for any two si_unit types with matching dimensions
// Returns result in the canonical base SI unit (meter, kilogram, second, etc.)
// OPTIMIZATION: If both operands have identical ratios, returns result in the same unit type
// (no conversion needed). Otherwise returns canonical form.
template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr auto operator-(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename is_si_unit<T1>::value_type;
    constexpr dimension_t dim = is_si_unit<T1>::value_dimension;
    using ratio1 = typename is_si_unit<T1>::ratio_type;
    using ratio2 = typename is_si_unit<T2>::ratio_type;
    
    // Optimization: if both have same ratio, just subtract and keep the type
    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        using result_type = unit_t<value_type, ratio1, dim>;
        return result_type(lhs.value() - rhs.value());
    }
    else
    {
        // Different ratios - convert to canonical
        using result_type = unit_t<value_type, std::ratio<1, 1>, dim>;
        return result_type(
            si::subtract_canonical<value_type, ratio1, ratio2>(
                lhs.value(), rhs.value()
            )
        );
    }
}
