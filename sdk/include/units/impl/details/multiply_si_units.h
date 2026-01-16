// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include "arithmetic_helpers.h"
#include "dimension.h"

// ============================================================================
// Multiplication Operations
// ============================================================================
// Free-function operator* for any two si_unit types.
// Combines dimensions (adds exponents) and ratios (multiplies them).
//
// Key Design Decisions:
// - No dimension matching requirement: any units can be multiplied
// - Result dimensions computed at compile-time via constexpr dimension combination
// - Ratios combined using std::ratio_multiply for exact rational arithmetic
// - Delegates to multiply_values helper for arithmetic (reduces binary bloat)
//
// Examples:
//   meter(2) * meter(3)     → unit_t with length=2, value=6
//   meter(5) * kilometer(2) → unit_t with length=2, value=10 (with ratio=1000)
//   meter(10) * second(2)   → unit_t with length=1, time=1, value=20

// Free-function operator* for any two si_unit types
// Combines dimensions (adds exponents) and ratios (multiplies them)
// Optimization: if either ratio is ratio<1,1>, skip the multiplication
template<si_unit_type T1, si_unit_type T2>
constexpr auto operator*(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename is_si_unit<T1>::value_type;
    using ratio1 = typename is_si_unit<T1>::ratio_type;
    using ratio2 = typename is_si_unit<T2>::ratio_type;
    constexpr dimension_t dim1 = is_si_unit<T1>::value_dimension;
    constexpr dimension_t dim2 = is_si_unit<T2>::value_dimension;
    
    // Combine ratios and dimensions
    // Optimization: if either ratio is 1/1, skip the ratio multiplication
    using combined_ratio = std::conditional_t<
        std::is_same_v<ratio1, std::ratio<1, 1>>,
        ratio2,
        std::conditional_t<
            std::is_same_v<ratio2, std::ratio<1, 1>>,
            ratio1,
            std::ratio_multiply<ratio1, ratio2>
        >
    >;
    
    constexpr dimension_t combined_dim{
        .length = dim1.length + dim2.length,
        .mass = dim1.mass + dim2.mass,
        .time = dim1.time + dim2.time,
        .current = dim1.current + dim2.current,
        .temperature = dim1.temperature + dim2.temperature,
        .amount = dim1.amount + dim2.amount,
        .intensity = dim1.intensity + dim2.intensity};
    
    using result_type = unit_t<value_type, combined_ratio, combined_dim>;
    return result_type(si::multiply_values(lhs.value(), rhs.value()));
}
