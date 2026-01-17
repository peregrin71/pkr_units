#pragma once

#include "arithmetic_helpers.h"
#include "dimension.h"

// ============================================================================
// Division Operations
// ============================================================================
// Free-function operator/ for any two si_unit types.
// Combines dimensions (subtracts exponents) and ratios (divides them).
//
// Key Design Decisions:
// - No dimension matching requirement: any units can be divided
// - Result dimensions computed at compile-time via constexpr dimension combination
// - Ratios combined using std::ratio_divide for exact rational arithmetic
// - Delegates to divide_values helper for arithmetic (reduces binary bloat)
// - Division by zero is checked at runtime; compile-time evaluation asserts safety
//
// Examples:
//   meter(10) / meter(2)     → unit_t with length=0, value=5
//   meter(10) / second(2)    → unit_t with length=1, time=-1, value=5
//   kilometer(5) / kilometer(1) → unit_t with length=0, value=5

// Free-function operator/ for any two si_unit types
// Combines dimensions (subtracts exponents) and ratios (divides them)
// Optimizations:
// - If result dimensions are scalar (all zero), return value directly as dimensionless unit_t
// - If both ratios are identical, skip the ratio division (result is always 1/1)
// - If divisor ratio is ratio<1,1>, skip the division
template<si_unit_type T1, si_unit_type T2>
constexpr auto operator/(const T1& lhs, const T2& rhs)
{
    using value_type = typename is_si_unit<T1>::value_type;
    using ratio1 = typename is_si_unit<T1>::ratio_type;
    using ratio2 = typename is_si_unit<T2>::ratio_type;
    constexpr dimension_t dim1 = is_si_unit<T1>::value_dimension;
    constexpr dimension_t dim2 = is_si_unit<T2>::value_dimension;
    
    // Combine ratios and dimensions
    // Optimization: if divisor is 1/1, use dividend ratio; if both same, use 1/1; else divide
    using combined_ratio = std::conditional_t<
        std::is_same_v<ratio2, std::ratio<1, 1>>,
        ratio1,
        std::conditional_t<
            std::is_same_v<ratio1, ratio2>,
            std::ratio<1, 1>,
            std::ratio_divide<ratio1, ratio2>
        >
    >;
    
    constexpr dimension_t combined_dim{
        .length = dim1.length - dim2.length,
        .mass = dim1.mass - dim2.mass,
        .time = dim1.time - dim2.time,
        .current = dim1.current - dim2.current,
        .temperature = dim1.temperature - dim2.temperature,
        .amount = dim1.amount - dim2.amount,
        .intensity = dim1.intensity - dim2.intensity};
    
    using result_type = unit_t<value_type, combined_ratio, combined_dim>;
    return result_type{si::divide_values(lhs.value(), rhs.value())};
}


