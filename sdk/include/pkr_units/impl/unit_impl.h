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

// Concept for dimension compatibility
// All dimensions must match between operands
template <typename T1, typename T2>
concept same_dimensions_c =
    is_pkr_unit_c<T1> && is_pkr_unit_c<T2> && details::is_pkr_unit<T1>::value_dimension.length ==
    details::is_pkr_unit<T2>::value_dimension.length&& details::is_pkr_unit<T1>::value_dimension.mass ==
    details::is_pkr_unit<T2>::value_dimension.mass&& details::is_pkr_unit<T1>::value_dimension.time ==
    details::is_pkr_unit<T2>::value_dimension.time&& details::is_pkr_unit<T1>::value_dimension.current ==
    details::is_pkr_unit<T2>::value_dimension.current&& details::is_pkr_unit<T1>::value_dimension.temperature ==
    details::is_pkr_unit<T2>::value_dimension.temperature&& details::is_pkr_unit<T1>::value_dimension.amount ==
    details::is_pkr_unit<T2>::value_dimension.amount&& details::is_pkr_unit<T1>::value_dimension.intensity ==
    details::is_pkr_unit<T2>::value_dimension.intensity&& details::is_pkr_unit<T1>::value_dimension.angle == details::is_pkr_unit<T2>::value_dimension.angle;

// Addition operator (same-type overload)
template <is_pkr_unit_c T>
constexpr T operator+(const T& lhs, const T& rhs) noexcept
{
    return T{lhs.value() + rhs.value()};
}

// Addition operator (different-ratio overload) - preserve LHS unit and ratio
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
requires (same_dimensions_c<T1, T2> && (!std::is_same_v<T1, T2>))
constexpr T1 operator+(const T1& lhs, const T2& rhs) noexcept
{
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



template <is_pkr_unit_c T1, is_pkr_unit_c T2>
requires (same_dimensions_c<T1, T2> && (!std::is_same_v<T1, T2>))
constexpr T1 operator-(const T1& lhs, const T2& rhs) noexcept
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

// Unary negation operator
template <is_pkr_unit_c T>
constexpr T operator-(const T& a) noexcept
{
    return T{-a.value()};
}

// Subtraction operator (same-type overload)
template <is_pkr_unit_c T>
constexpr T operator-(const T& lhs, const T& rhs) noexcept
{
    return T{lhs.value() - rhs.value()};
}

// Multiplication operators
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
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
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
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
template <is_pkr_unit_c T, is_pkr_unit_c S>
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
template <is_pkr_unit_c S, is_pkr_unit_c T>
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
template <is_pkr_unit_c T, is_pkr_unit_c S>
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
template <is_pkr_unit_c S, is_pkr_unit_c T>
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
requires(is_pkr_unit_c<T>&& scalar_value_c<ScalarType>) constexpr auto operator/(const T& unit, const ScalarType& scalar) noexcept
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

requires(is_pkr_unit_c<T>&& scalar_value_c<ScalarType>) constexpr auto operator*(const ScalarType& scalar, const T& unit) noexcept
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

requires(is_pkr_unit_c<T>&& scalar_value_c<ScalarType>) constexpr auto operator/(const ScalarType& scalar, const T& unit)
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

// Comparison operators
template <is_pkr_unit_c T1, is_pkr_unit_c T2>
requires same_dimensions_c<T1, T2>

constexpr bool operator==(const T1& lhs, const T2& rhs) noexcept
{
    using lhs_ratio = typename details::is_pkr_unit<T1>::ratio_type;
    using rhs_ratio = typename details::is_pkr_unit<T2>::ratio_type;
    using canonical_value_lhs = double;

    if constexpr (std::ratio_equal_v<lhs_ratio, rhs_ratio>)
    {
        return lhs.value() == rhs.value();
    }
    else
    {
        auto to_canonical = [](const auto& unit)
        {
            using ratio_type = typename details::is_pkr_unit<decltype(unit)>::ratio_type;
            return static_cast<double>(unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        };
        return to_canonical(lhs) == to_canonical(rhs);
    }
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
        using ratio_type = typename details::is_pkr_unit<unit_type>::ratio_type;
        return static_cast<double>(unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
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
        using ratio_type = typename details::is_pkr_unit<unit_type>::ratio_type;
        return static_cast<double>(unit.value()) * (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
    };
    return to_canonical(lhs) <=> to_canonical(rhs);
}

} // namespace PKR_UNITS_NAMESPACE

