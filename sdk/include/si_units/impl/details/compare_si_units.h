#pragma once

#include "si_unit.h"
#include "../../namespace_config.h"

// ============================================================================
// Helper: Convert units to canonical form for comparison
// ============================================================================
// Converts operand to canonical form (value * ratio_num/ratio_den) for comparison
// when ratios differ, allowing cross-ratio comparisons within same dimension
template<si_unit_type T>
requires is_si_unit<T>::value
constexpr double to_canonical_value(const T& unit) noexcept
{
    using ratio_type = typename is_si_unit<T>::ratio_type;
    // Canonical form: value * (ratio_num / ratio_den)
    return static_cast<double>(unit.value()) * 
           (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
}

// ============================================================================
// Equality and Inequality Operators
// ============================================================================

// operator== for units with same dimension (any ratio)
template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value && is_si_unit<T2>::value &&
          is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr bool operator==(const T1& lhs, const T2& rhs) noexcept
{
    using lhs_ratio = typename is_si_unit<T1>::ratio_type;
    using rhs_ratio = typename is_si_unit<T2>::ratio_type;

    // Optimized path: same ratio means direct comparison
    if constexpr (std::ratio_equal_v<lhs_ratio, rhs_ratio>)
    {
        return lhs.value() == rhs.value();
    }
    // Non-optimized path: different ratios require canonical conversion
    else
    {
        return to_canonical_value(lhs) == to_canonical_value(rhs);
    }
}

// operator!= for units with same dimension (any ratio)
template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value && is_si_unit<T2>::value &&
          is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr bool operator!=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs == rhs);
}

// ============================================================================
// Less Than Operator
// ============================================================================

template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value && is_si_unit<T2>::value &&
          is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr bool operator<(const T1& lhs, const T2& rhs) noexcept
{
    using lhs_ratio = typename is_si_unit<T1>::ratio_type;
    using rhs_ratio = typename is_si_unit<T2>::ratio_type;

    // Optimized path: same ratio means direct comparison
    if constexpr (std::ratio_equal_v<lhs_ratio, rhs_ratio>)
    {
        return lhs.value() < rhs.value();
    }
    // Non-optimized path: different ratios require canonical conversion
    else
    {
        return to_canonical_value(lhs) < to_canonical_value(rhs);
    }
}

// ============================================================================
// Greater Than Operator
// ============================================================================

template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value && is_si_unit<T2>::value &&
          is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr bool operator>(const T1& lhs, const T2& rhs) noexcept
{
    return rhs < lhs;
}

// ============================================================================
// Less Than or Equal Operator
// ============================================================================

template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value && is_si_unit<T2>::value &&
          is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr bool operator<=(const T1& lhs, const T2& rhs) noexcept
{
    return !(rhs < lhs);
}

// ============================================================================
// Greater Than or Equal Operator
// ============================================================================

template<si_unit_type T1, si_unit_type T2>
requires (is_si_unit<T1>::value && is_si_unit<T2>::value &&
          is_si_unit<T1>::value_dimension == is_si_unit<T2>::value_dimension)
constexpr bool operator>=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs < rhs);
}
