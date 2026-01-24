#pragma once

#include <string_view>
#include "namespace_config.h"

// Include unit_t class definition at global scope before opening any namespaces
// This breaks the circular dependency between unit_impl.h and _decl.h files
#include "decls/unit_t_decl.h"
#include "concepts/unit_concepts.h"
#include "dimension.h"

// ============================================================================
// Operators in main si namespace
// ============================================================================
PKR_UNITS_BEGIN_NAMESPACE
{

// Concept for dimension compatibility
// All dimensions must match between operands
template<typename T1, typename T2>
concept same_dimensions_c = 
    requires {
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.length == details::is_si_unit<T2>::value_dimension.length>; };
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.mass == details::is_si_unit<T2>::value_dimension.mass>; };
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.time == details::is_si_unit<T2>::value_dimension.time>; };
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.current == details::is_si_unit<T2>::value_dimension.current>; };
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.temperature == details::is_si_unit<T2>::value_dimension.temperature>; };
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.amount == details::is_si_unit<T2>::value_dimension.amount>; };
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.intensity == details::is_si_unit<T2>::value_dimension.intensity>; };
        requires requires { typename std::enable_if_t<details::is_si_unit<T1>::value_dimension.angle == details::is_si_unit<T2>::value_dimension.angle>; };
    };

// Addition operator
template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr T1 operator+(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    constexpr auto dim = details::is_si_unit<T1>::value_dimension;
    using result_ratio = typename details::is_si_unit<T1>::ratio_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    
    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        return T1{lhs.value() + rhs.value()};
    }
    else
    {
        value_type canonical_sum = details::add_canonical<value_type, ratio1, ratio2>(
            lhs.value(), rhs.value()
        );
        value_type converted = details::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
            canonical_sum
        );
        return T1{converted};
    }
}

// Named add function
template<details::si_unit_concept ResultType, details::si_unit_concept T1, details::si_unit_concept T2>
requires (same_dimensions_c<T1, T2> && same_dimensions_c<T1, ResultType>)
constexpr auto add(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<ResultType>::value_type;
    using result_ratio = typename details::is_si_unit<ResultType>::ratio_type;
    constexpr auto dim = details::is_si_unit<ResultType>::value_dimension;
    
    value_type canonical_sum = details::add_canonical<value_type, 
                                                     typename details::is_si_unit<T1>::ratio_type,
                                                     typename details::is_si_unit<T2>::ratio_type>(
        lhs.value(), rhs.value()
    );
    
    value_type converted = details::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
        canonical_sum
    );
    
    return details::unit_t<value_type, result_ratio, dim>{converted};
}

// Subtraction operator
template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr T1 operator-(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    constexpr auto dim = details::is_si_unit<T1>::value_dimension;
    using result_ratio = typename details::is_si_unit<T1>::ratio_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    
    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        return T1{lhs.value() - rhs.value()};
    }
    else
    {
        value_type canonical_diff = details::subtract_canonical<value_type, ratio1, ratio2>(
            lhs.value(), rhs.value()
        );
        value_type converted = details::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
            canonical_diff
        );
        return T1{converted};
    }
}

// Multiplication operators
template<typename T1, typename T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value)
constexpr auto operator*(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_si_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_si_unit<T2>::value_dimension;
    
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
        .intensity = dim1.intensity + dim2.intensity,
        .angle = dim1.angle + dim2.angle};
    
    using result_type = details::unit_t<value_type, combined_ratio, combined_dim>;
    return result_type{details::multiply_values(lhs.value(), rhs.value())};
}

// Division operator
template<typename T1, typename T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value)
constexpr auto operator/(const T1& lhs, const T2& rhs)
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_si_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_si_unit<T2>::value_dimension;
    
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
        .intensity = dim1.intensity - dim2.intensity,
        .angle = dim1.angle - dim2.angle};
    
    using result_type = details::unit_t<value_type, combined_ratio, combined_dim>;
    return result_type{details::divide_values(lhs.value(), rhs.value())};
}

// Free function scalar multiplication (scalar * unit) - returns the most derived type
template<typename ScalarType, typename T>
requires (details::is_si_unit<T>::value && std::is_arithmetic_v<ScalarType>)
constexpr auto operator*(const ScalarType& scalar, const T& unit) noexcept
{
    using value_type = typename details::is_si_unit<T>::value_type;
    using ratio_type = typename details::is_si_unit<T>::ratio_type;
    constexpr auto dim = details::is_si_unit<T>::value_dimension;
    
    using result_type = typename details::named_unit_type_t<value_type, ratio_type, dim>::type;
    return result_type{details::multiply_values(scalar, unit.value())};
}

// Free function scalar division (scalar / unit) - returns the most derived type of 1/unit
template<typename ScalarType, typename T>
requires (details::is_si_unit<T>::value && std::is_arithmetic_v<ScalarType>)
constexpr auto operator/(const ScalarType& scalar, const T& unit)
{
    using value_type = typename details::is_si_unit<T>::value_type;
    using ratio_type = typename details::is_si_unit<T>::ratio_type;
    constexpr auto dim = details::is_si_unit<T>::value_dimension;
    
    // Invert the dimensions for division
    constexpr dimension_t inverted_dim{
        .length = -dim.length,
        .mass = -dim.mass,
        .time = -dim.time,
        .current = -dim.current,
        .temperature = -dim.temperature,
        .amount = -dim.amount,
        .intensity = -dim.intensity,
        .angle = -dim.angle};
    
    // Invert the ratio for division
    using inverted_ratio = std::ratio_divide<std::ratio<1, 1>, ratio_type>;
    
    using result_type = details::unit_t<value_type, inverted_ratio, inverted_dim>;
    return result_type{details::divide_values(scalar, unit.value())};
}

// Comparison operators
template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr bool operator==(const T1& lhs, const T2& rhs) noexcept
{
    using lhs_ratio = typename details::is_si_unit<T1>::ratio_type;
    using rhs_ratio = typename details::is_si_unit<T2>::ratio_type;
    using canonical_value_lhs = double;
    
    if constexpr (std::ratio_equal_v<lhs_ratio, rhs_ratio>)
    {
        return lhs.value() == rhs.value();
    }
    else
    {
        auto to_canonical = [](const auto& unit) {
            using ratio_type = typename details::is_si_unit<decltype(unit)>::ratio_type;
            return static_cast<double>(unit.value()) * 
                   (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        };
        return to_canonical(lhs) == to_canonical(rhs);
    }
}

template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr bool operator!=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs == rhs);
}

template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr bool operator<(const T1& lhs, const T2& rhs) noexcept
{
    auto to_canonical = [](const auto& unit) {
        using unit_type = std::remove_cvref_t<decltype(unit)>;
        using ratio_type = typename details::is_si_unit<unit_type>::ratio_type;
        return static_cast<double>(unit.value()) * 
               (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
    };
    return to_canonical(lhs) < to_canonical(rhs);
}

template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr bool operator<=(const T1& lhs, const T2& rhs) noexcept
{
    return lhs < rhs || lhs == rhs;
}

template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr bool operator>(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs <= rhs);
}

template<details::si_unit_concept T1, details::si_unit_concept T2>
requires same_dimensions_c<T1, T2>
constexpr bool operator>=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs < rhs);
}

}  // namespace PKR_UNITS_NAMESPACE

// Include dimension definitions at global scope after all namespaces close
// The _decl.h files will open their own namespace PKR_UNITS_NAMESPACE blocks
#include "decls/length_decl.h"
#include "decls/mass_decl.h"
#include "decls/time_decl.h"
#include "decls/current_decl.h"
#include "decls/temperature_decl.h"
#include "decls/amount_decl.h"
#include "decls/intensity_decl.h"







