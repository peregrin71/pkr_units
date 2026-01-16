// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <ratio>
#include <stdexcept>

namespace si
{

// ============================================================================
// Arithmetic Helper Functions
// ============================================================================
// These functions provide low-level arithmetic operations templated only on
// value types and ratios (not unit types). This allows:
// - Reduced binary bloat: instantiated once per value type, not per unit pair
// - Better link-time optimization: simple functions can be inlined aggressively
// - Clean separation: type checking in operators, computation in helpers

// Helper: convert a value from one ratio to another
// Only templated on value type for better compilation and optimization
template<typename type_t, typename ratio_from, typename ratio_to>
constexpr type_t convert_ratio_to(type_t value) noexcept
{
    using conversion = std::ratio_divide<ratio_from, ratio_to>;
    return (value / static_cast<type_t>(conversion::den)) * 
           static_cast<type_t>(conversion::num);
}

// Helper: add two values with different ratios, result in canonical ratio (1/1)
// Only templated on value type and ratios, not on unit types
template<typename type_t, typename ratio_t1, typename ratio_t2>
constexpr type_t add_canonical(type_t val1, type_t val2) noexcept
{
    type_t canonical1 = convert_ratio_to<type_t, ratio_t1, std::ratio<1, 1>>(val1);
    type_t canonical2 = convert_ratio_to<type_t, ratio_t2, std::ratio<1, 1>>(val2);
    return canonical1 + canonical2;
}

// Helper: subtract two values with different ratios, result in canonical ratio (1/1)
// Only templated on value type and ratios, not on unit types
template<typename type_t, typename ratio_t1, typename ratio_t2>
constexpr type_t subtract_canonical(type_t val1, type_t val2) noexcept
{
    type_t canonical1 = convert_ratio_to<type_t, ratio_t1, std::ratio<1, 1>>(val1);
    type_t canonical2 = convert_ratio_to<type_t, ratio_t2, std::ratio<1, 1>>(val2);
    return canonical1 - canonical2;
}

// Helper: multiply two values
// Only templated on value type, not on unit types
template<typename type_t>
constexpr type_t multiply_values(type_t val1, type_t val2) noexcept
{
    return val1 * val2;
}

// Helper: divide two values
// Only templated on value type, not on unit types
template<typename type_t>
constexpr type_t divide_values(type_t val1, type_t val2)
{
    // Division by zero check: at runtime throw, at compile-time assert
    if (!std::is_constant_evaluated())
    {
        if ((val2 < static_cast<type_t>(0) ? -val2 : val2) == static_cast<type_t>(0))
        {
            throw std::invalid_argument("Division by zero in si_unit::operator/");
        }
    }
    return val1 / val2;
}

} // namespace si
