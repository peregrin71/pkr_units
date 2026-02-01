#pragma once

#include <string_view>
#include <pkr_units/impl/namespace_config.h>

// Include unit_t class definition at global scope before opening any namespaces
// This breaks the circular dependency between unit_impl.h and _decl.h files
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/dimension.h>

// ============================================================================
// Operators in main si namespace
// ============================================================================
namespace PKR_UNITS_NAMESPACE
{

// Concept for dimension compatibility - works with both base and derived types
template <typename T1, typename T2>
concept same_dimensions_c = details::is_pkr_unit<T1>::value_dimension.length == details::is_pkr_unit<T2>::value_dimension.length &&
                            details::is_pkr_unit<T1>::value_dimension.mass == details::is_pkr_unit<T2>::value_dimension.mass &&
                            details::is_pkr_unit<T1>::value_dimension.time == details::is_pkr_unit<T2>::value_dimension.time &&
                            details::is_pkr_unit<T1>::value_dimension.current == details::is_pkr_unit<T2>::value_dimension.current &&
                            details::is_pkr_unit<T1>::value_dimension.temperature == details::is_pkr_unit<T2>::value_dimension.temperature &&
                            details::is_pkr_unit<T1>::value_dimension.amount == details::is_pkr_unit<T2>::value_dimension.amount &&
                            details::is_pkr_unit<T1>::value_dimension.intensity == details::is_pkr_unit<T2>::value_dimension.intensity &&
                            details::is_pkr_unit<T1>::value_dimension.angle == details::is_pkr_unit<T2>::value_dimension.angle;

// Direct unit_t addition for base units (same ratio, same dimension)
template <typename type_t, typename ratio_t, dimension_t dim_v>
constexpr details::unit_t<type_t, ratio_t, dim_v>
    operator+(const details::unit_t<type_t, ratio_t, dim_v>& lhs, const details::unit_t<type_t, ratio_t, dim_v>& rhs) noexcept
{
    return details::unit_t<type_t, ratio_t, dim_v>{lhs.value() + rhs.value()};
}

// Direct unit_t addition for units with same dimension, different ratios
template <typename type_t, typename ratio_t1, typename ratio_t2, dimension_t dim_v>
    requires(!std::is_same_v<ratio_t1, ratio_t2>)
constexpr details::unit_t<type_t, ratio_t1, dim_v>
    operator+(const details::unit_t<type_t, ratio_t1, dim_v>& lhs, const details::unit_t<type_t, ratio_t2, dim_v>& rhs) noexcept
{
    type_t converted_rhs = details::convert_ratio_to<type_t, ratio_t2, ratio_t1>(rhs.value());
    return details::unit_t<type_t, ratio_t1, dim_v>{lhs.value() + converted_rhs};
}

// ============================================================================
// Unified arithmetic operators with if constexpr for base/derived handling
// ============================================================================

// Addition operator - handles all combinations of base and derived types
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires(same_dimensions_c<T1, T2>)
constexpr auto operator+(const T1& lhs, const T2& rhs) noexcept
{
    // Unwrap derived types to their base for calculation
    if constexpr (is_derived_pkr_unit_c<T1> && is_derived_pkr_unit_c<T2>)
    {
        // Both derived: delegate to base operators, wrap result in T1
        auto base_result = (static_cast<const typename T1::_base&>(lhs) + static_cast<const typename T2::_base&>(rhs));
        return T1{base_result.value()};
    }
    else if constexpr (is_derived_pkr_unit_c<T1> && !is_derived_pkr_unit_c<T2>)
    {
        // T1 derived, T2 base: delegate and wrap in T1
        auto base_result = (static_cast<const typename T1::_base&>(lhs) + rhs);
        return T1{base_result.value()};
    }
    else if constexpr (!is_derived_pkr_unit_c<T1> && is_derived_pkr_unit_c<T2>)
    {
        // T1 base, T2 derived: delegate and wrap in T2
        auto base_result = (lhs + static_cast<const typename T2::_base&>(rhs));
        return T2{base_result.value()};
    }
    else
    {
        // Both base: normal base type logic
        if constexpr (std::is_same_v<T1, T2>)
        {
            return T1{lhs.value() + rhs.value()};
        }
        else
        {
            // Different base types, same dimension: use LHS ratio
            using value_type = typename details::is_pkr_unit<T1>::value_type;
            using lhs_ratio = typename details::is_pkr_unit<T1>::ratio_type;
            using rhs_ratio = typename details::is_pkr_unit<T2>::ratio_type;

            if constexpr (std::is_same_v<lhs_ratio, rhs_ratio>)
            {
                return T1{lhs.value() + rhs.value()};
            }
            else
            {
                value_type converted_rhs = details::convert_ratio_to<value_type, rhs_ratio, lhs_ratio>(rhs.value());
                return T1{lhs.value() + converted_rhs};
            }
        }
    }
}

// Subtraction operator - unified for all base/derived combinations
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires(same_dimensions_c<T1, T2>)
constexpr auto operator-(const T1& lhs, const T2& rhs) noexcept
{
    if constexpr (is_derived_pkr_unit_c<T1> && is_derived_pkr_unit_c<T2>)
    {
        auto base_result = (static_cast<const typename T1::_base&>(lhs) - static_cast<const typename T2::_base&>(rhs));
        return T1{base_result.value()};
    }
    else if constexpr (is_derived_pkr_unit_c<T1> && !is_derived_pkr_unit_c<T2>)
    {
        auto base_result = (static_cast<const typename T1::_base&>(lhs) - rhs);
        return T1{base_result.value()};
    }
    else if constexpr (!is_derived_pkr_unit_c<T1> && is_derived_pkr_unit_c<T2>)
    {
        auto base_result = (lhs - static_cast<const typename T2::_base&>(rhs));
        return T2{base_result.value()};
    }
    else
    {
        if constexpr (std::is_same_v<T1, T2>)
        {
            return T1{lhs.value() - rhs.value()};
        }
        else
        {
            using value_type = typename details::is_pkr_unit<T1>::value_type;
            using lhs_ratio = typename details::is_pkr_unit<T1>::ratio_type;
            using rhs_ratio = typename details::is_pkr_unit<T2>::ratio_type;

            if constexpr (std::is_same_v<lhs_ratio, rhs_ratio>)
            {
                return T1{lhs.value() - rhs.value()};
            }
            else
            {
                value_type converted_rhs = details::convert_ratio_to<value_type, rhs_ratio, lhs_ratio>(rhs.value());
                return T1{lhs.value() - converted_rhs};
            }
        }
    }
}

// Unary negation operator - unified for base and derived types
template <is_pkr_unit_c T>
constexpr T operator-(const T& a) noexcept
{
    return T{-a.value()};
}

// Multiplication operators
template <is_base_pkr_unit_c T1, is_base_pkr_unit_c T2>
constexpr auto operator*(const T1& lhs, const T2& rhs) noexcept
{
    // Multiply stored values and set result ratio = lhs_ratio * rhs_ratio (do not canonicalize)
    using value_type = typename details::is_pkr_unit<T1>::value_type;
    using lhs_ratio = typename details::is_pkr_unit<T1>::ratio_type;
    using rhs_ratio = typename details::is_pkr_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<T2>::value_dimension;

    constexpr dimension_t combined_dim{
        .length = dim1.length + dim2.length,
        .mass = dim1.mass + dim2.mass,
        .time = dim1.time + dim2.time,
        .current = dim1.current + dim2.current,
        .temperature = dim1.temperature + dim2.temperature,
        .amount = dim1.amount + dim2.amount,
        .intensity = dim1.intensity + dim2.intensity,
        .angle = dim1.angle + dim2.angle};

    using result_ratio = std::ratio_multiply<lhs_ratio, rhs_ratio>;
    using result_type = typename details::derived_unit_type_t<value_type, result_ratio, combined_dim>::type;
    return result_type{details::multiply_values(lhs.value(), rhs.value())};
}

// Division operator
template <is_base_pkr_unit_c T1, is_base_pkr_unit_c T2>
constexpr auto operator/(const T1& lhs, const T2& rhs) noexcept
{
    // Divide stored values and set result ratio = lhs_ratio / rhs_ratio (do not canonicalize)
    using value_type = typename details::is_pkr_unit<T1>::value_type;
    using lhs_ratio = typename details::is_pkr_unit<T1>::ratio_type;
    using rhs_ratio = typename details::is_pkr_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<T2>::value_dimension;

    constexpr dimension_t combined_dim{
        .length = dim1.length - dim2.length,
        .mass = dim1.mass - dim2.mass,
        .time = dim1.time - dim2.time,
        .current = dim1.current - dim2.current,
        .temperature = dim1.temperature - dim2.temperature,
        .amount = dim1.amount - dim2.amount,
        .intensity = dim1.intensity - dim2.intensity,
        .angle = dim1.angle - dim2.angle};

    using result_ratio = std::ratio_divide<lhs_ratio, rhs_ratio>;
    using result_type = typename details::derived_unit_type_t<value_type, result_ratio, combined_dim>::type;
    return result_type{details::divide_values(lhs.value(), rhs.value())};
}

// Support multiplying/dividing by dimensionless unit types (`scalar_t`-like) while preserving non-scalar unit ratio
// operator*(Unit, scalar_t) -> preserves Unit
template <is_base_pkr_unit_c T, is_base_pkr_unit_c S>
    requires(details::is_pkr_unit<S>::value_dimension == scalar_dimension && details::is_pkr_unit<T>::value_dimension != scalar_dimension)
constexpr auto operator*(const T& lhs, const S& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using lhs_ratio = typename details::is_pkr_unit<T>::ratio_type;
    using rhs_ratio = typename details::is_pkr_unit<S>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<T>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<S>::value_dimension;

    constexpr dimension_t combined_dim{
        .length = dim1.length + dim2.length,
        .mass = dim1.mass + dim2.mass,
        .time = dim1.time + dim2.time,
        .current = dim1.current + dim2.current,
        .temperature = dim1.temperature + dim2.temperature,
        .amount = dim1.amount + dim2.amount,
        .intensity = dim1.intensity + dim2.intensity,
        .angle = dim1.angle + dim2.angle};

    // Preserve lhs unit and ratio
    value_type rhs_converted = details::convert_ratio_to<value_type, rhs_ratio, lhs_ratio>(rhs.value());
    using result_type = typename details::derived_unit_type_t<value_type, lhs_ratio, combined_dim>::type;
    return result_type{details::multiply_values(lhs.value(), rhs_converted)};
}

// operator*(scalar_t, Unit) -> preserves Unit (use rhs as reference)
template <is_base_pkr_unit_c S, is_base_pkr_unit_c T>
    requires(details::is_pkr_unit<S>::value_dimension == scalar_dimension && details::is_pkr_unit<T>::value_dimension != scalar_dimension)
constexpr auto operator*(const S& lhs, const T& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using lhs_ratio = typename details::is_pkr_unit<S>::ratio_type;
    using rhs_ratio = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<S>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<T>::value_dimension;

    constexpr dimension_t combined_dim{
        .length = dim1.length + dim2.length,
        .mass = dim1.mass + dim2.mass,
        .time = dim1.time + dim2.time,
        .current = dim1.current + dim2.current,
        .temperature = dim1.temperature + dim2.temperature,
        .amount = dim1.amount + dim2.amount,
        .intensity = dim1.intensity + dim2.intensity,
        .angle = dim1.angle + dim2.angle};

    // Use rhs as reference
    value_type lhs_converted = details::convert_ratio_to<value_type, lhs_ratio, rhs_ratio>(lhs.value());
    using result_type = typename details::derived_unit_type_t<value_type, rhs_ratio, combined_dim>::type;
    return result_type{details::multiply_values(lhs_converted, rhs.value())};
}

// operator/(Unit, scalar_t) -> preserves Unit
template <is_base_pkr_unit_c T, is_base_pkr_unit_c S>
    requires(details::is_pkr_unit<S>::value_dimension == scalar_dimension && details::is_pkr_unit<T>::value_dimension != scalar_dimension)
constexpr auto operator/(const T& lhs, const S& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using lhs_ratio = typename details::is_pkr_unit<T>::ratio_type;
    using rhs_ratio = typename details::is_pkr_unit<S>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<T>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<S>::value_dimension;

    constexpr dimension_t result_dim{
        .length = dim1.length - dim2.length,
        .mass = dim1.mass - dim2.mass,
        .time = dim1.time - dim2.time,
        .current = dim1.current - dim2.current,
        .temperature = dim1.temperature - dim2.temperature,
        .amount = dim1.amount - dim2.amount,
        .intensity = dim1.intensity - dim2.intensity,
        .angle = dim1.angle - dim2.angle};

    // Preserve lhs unit ratio
    value_type rhs_converted = details::convert_ratio_to<value_type, rhs_ratio, lhs_ratio>(rhs.value());
    using result_type = typename details::derived_unit_type_t<value_type, lhs_ratio, result_dim>::type;
    return result_type{details::divide_values(lhs.value(), rhs_converted)};
}

// operator/(scalar_t, Unit) -> produces inverse unit (1/Unit)
template <is_base_pkr_unit_c S, is_base_pkr_unit_c T>
    requires(details::is_pkr_unit<S>::value_dimension == scalar_dimension && details::is_pkr_unit<T>::value_dimension != scalar_dimension)
constexpr auto operator/(const S& lhs, const T& rhs) noexcept
{
    using value_type = typename details::is_pkr_unit<S>::value_type;
    using lhs_ratio = typename details::is_pkr_unit<S>::ratio_type;
    using rhs_ratio = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim1 = details::is_pkr_unit<S>::value_dimension;
    constexpr auto dim2 = details::is_pkr_unit<T>::value_dimension;

    // Invert the ratio and dimensions of rhs for the result
    using inv_ratio = std::ratio_divide<std::ratio<1, 1>, rhs_ratio>;
    constexpr dimension_t inv_dim{
        .length = -dim2.length,
        .mass = -dim2.mass,
        .time = -dim2.time,
        .current = -dim2.current,
        .temperature = -dim2.temperature,
        .amount = -dim2.amount,
        .intensity = -dim2.intensity,
        .angle = -dim2.angle};

    using result_type = typename details::derived_unit_type_t<value_type, inv_ratio, inv_dim>::type;
    // Convert rhs to canonical for stable division
    value_type rhs_canonical = details::convert_ratio_to<value_type, rhs_ratio, std::ratio<1, 1>>(rhs.value());
    return result_type{details::divide_values(lhs.value(), rhs_canonical)};
}

// Free function scalar division (unit / scalar) - returns the most derived type
template <typename T, typename ScalarType>
    requires(is_base_pkr_unit_c<T> && scalar_value_c<ScalarType>)
constexpr auto operator/(const T& unit, const ScalarType& scalar) noexcept
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using ratio_type = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;

    using result_type = typename details::derived_unit_type_t<value_type, ratio_type, dim>::type;
    // Ensure scalar uses same value_type before dividing
    return result_type(details::divide_values<value_type>(unit.value(), static_cast<value_type>(scalar)));
}

// Free function scalar multiplication (scalar * unit) - returns the most derived type
template <typename ScalarType, typename T>

    requires(is_base_pkr_unit_c<T> && scalar_value_c<ScalarType>)
constexpr auto operator*(const ScalarType& scalar, const T& unit) noexcept
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using ratio_type = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;

    using result_type = typename details::derived_unit_type_t<value_type, ratio_type, dim>::type;
    // Ensure scalar and unit value use the same value_type before multiplying
    return result_type(details::multiply_values<value_type>(static_cast<value_type>(scalar), unit.value()));
}

// Free function scalar division (scalar / unit) - returns the most derived type of 1/unit
template <typename ScalarType, typename T>

    requires(is_base_pkr_unit_c<T> && scalar_value_c<ScalarType>)
constexpr auto operator/(const ScalarType& scalar, const T& unit)
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using ratio_type = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;

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

    using result_type = typename details::derived_unit_type_t<value_type, inverted_ratio, inverted_dim>::type;
    // Ensure scalar uses same value_type before dividing
    return result_type(details::divide_values<value_type>(static_cast<value_type>(scalar), unit.value()));
}

// ============================================================================
// Derived Type Operator Overloads
// ============================================================================

// Free function scalar multiplication (scalar * derived_unit) - delegates to base
template <typename ScalarType, typename T>
    requires(is_derived_pkr_unit_c<T> && scalar_value_c<ScalarType>)
constexpr auto operator*(const ScalarType& scalar, const T& unit) noexcept
{
    using base_type = typename T::_base;
    using value_type = typename details::is_pkr_unit<T>::value_type;
    // Delegate to base type operation, then convert result back to derived if needed
    auto base_result = scalar * static_cast<const base_type&>(unit);
    return T{base_result.value()};
}

// Free function unit * scalar (derived_unit * scalar)
template <typename T, typename ScalarType>
    requires(is_derived_pkr_unit_c<T> && scalar_value_c<ScalarType>)
constexpr auto operator*(const T& unit, const ScalarType& scalar) noexcept
{
    return scalar * unit;
}

// Free function scalar division (scalar / derived_unit)
template <typename ScalarType, typename T>
    requires(is_derived_pkr_unit_c<T> && scalar_value_c<ScalarType>)
constexpr auto operator/(const ScalarType& scalar, const T& unit) noexcept
{
    using base_type = typename T::_base;
    using value_type = typename details::is_pkr_unit<T>::value_type;
    // Delegate to base type operation
    auto base_result = scalar / static_cast<const base_type&>(unit);
    // Result type may differ (e.g., scalar/meter -> 1/meter), so return as-is
    return base_result;
}

// Free function derived_unit / scalar
template <typename T, typename ScalarType>
    requires(is_derived_pkr_unit_c<T> && scalar_value_c<ScalarType>)
constexpr auto operator/(const T& unit, const ScalarType& scalar) noexcept
{
    using value_type = typename details::is_pkr_unit<T>::value_type;
    using ratio_type = typename details::is_pkr_unit<T>::ratio_type;
    constexpr auto dim = details::is_pkr_unit<T>::value_dimension;

    using result_type = typename details::derived_unit_type_t<value_type, ratio_type, dim>::type;
    return result_type(details::divide_values<value_type>(unit.value(), static_cast<value_type>(scalar)));
}

// Comparison operators
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>

constexpr bool operator==(const T1& lhs, const T2& rhs) noexcept
{
    auto to_canonical = [](const auto& unit)
    {
        using unit_type = std::remove_cvref_t<decltype(unit)>;
        using actual_type = std::conditional_t<is_derived_pkr_unit_c<unit_type>, typename unit_type::_base, unit_type>;
        using ratio_type = typename details::is_pkr_unit<actual_type>::ratio_type;

        if constexpr (is_derived_pkr_unit_c<unit_type>)
        {
            const auto& base_unit = static_cast<const actual_type&>(unit);
            return static_cast<double>(base_unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        }
        else
        {
            return static_cast<double>(unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        }
    };
    return to_canonical(lhs) == to_canonical(rhs);
}

template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>

constexpr bool operator!=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs == rhs);
}

template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>

constexpr bool operator<(const T1& lhs, const T2& rhs) noexcept
{
    auto to_canonical = [](const auto& unit)
    {
        using unit_type = std::remove_cvref_t<decltype(unit)>;
        using actual_type = std::conditional_t<is_derived_pkr_unit_c<unit_type>, typename unit_type::_base, unit_type>;
        using ratio_type = typename details::is_pkr_unit<actual_type>::ratio_type;

        if constexpr (is_derived_pkr_unit_c<unit_type>)
        {
            const auto& base_unit = static_cast<const actual_type&>(unit);
            return static_cast<double>(base_unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        }
        else
        {
            return static_cast<double>(unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        }
    };
    return to_canonical(lhs) < to_canonical(rhs);
}

template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>

constexpr bool operator<=(const T1& lhs, const T2& rhs) noexcept
{
    return lhs < rhs || lhs == rhs;
}

template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>

constexpr bool operator>(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs <= rhs);
}

template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>

constexpr bool operator>=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs < rhs);
}

template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>

constexpr auto operator<=>(const T1& lhs, const T2& rhs) noexcept
{
    auto to_canonical = [](const auto& unit)
    {
        using unit_type = std::remove_cvref_t<decltype(unit)>;
        using actual_type = std::conditional_t<is_derived_pkr_unit_c<unit_type>, typename unit_type::_base, unit_type>;
        using ratio_type = typename details::is_pkr_unit<actual_type>::ratio_type;

        if constexpr (is_derived_pkr_unit_c<unit_type>)
        {
            const auto& base_unit = static_cast<const actual_type&>(unit);
            return static_cast<double>(base_unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        }
        else
        {
            return static_cast<double>(unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        }
    };
    return to_canonical(lhs) <=> to_canonical(rhs);
}

// Equality operator for derived types (now handled by unified operator== above)
// template <is_derived_pkr_unit_c T>
// constexpr bool operator==(const T& lhs, const T& rhs) noexcept
// {
//     return lhs.value() == rhs.value();
// }

} // namespace PKR_UNITS_NAMESPACE
