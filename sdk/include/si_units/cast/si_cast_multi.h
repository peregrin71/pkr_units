// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <si_units/impl/details/si_unit.h>
#include "si_pow.h"
#include <type_traits>
#include <tuple>
#include <ratio>
#include <utility>

namespace si
{
    // ========================================================================
    // Marker wrapper to indicate units in the denominator and their powers
    // ========================================================================
    // Usage patterns for si_cast_multi:
    //   si_cast_multi<meter, per<seconds>>(source)                         // m/s  
    //   si_cast_multi<meter, per_unit_squared<hours>>(source)             // m/h²
    //   si_cast_multi<meter, per_unit_cubed<seconds>>(source)             // m/s³
    //   si_cast_multi<kilogram, meter, per<seconds>>(source)              // kg*m/s
    //   si_cast_multi<meter, per<hours, std::integral_constant<int, 2>>>(source)  // m/h² (explicit power)
    template<typename... Units>
    struct per
    {
    };

    // Specialized per templates for common powers to avoid explicit integral_constant
    template<typename Unit>
    struct per_unit_squared : per<Unit, std::integral_constant<int, 2>>
    {
    };

    template<typename Unit>
    struct per_unit_cubed : per<Unit, std::integral_constant<int, 3>>
    {
    };

    template<typename Unit>
    struct per_unit_quartic : per<Unit, std::integral_constant<int, 4>>
    {
    };

    template<typename Unit>
    struct per_unit_inverse : per<Unit, std::integral_constant<int, -1>>
    {
    };

    template<typename Unit>
    struct per_unit_inverse_squared : per<Unit, std::integral_constant<int, -2>>
    {
    };

    // ========================================================================
    // Dimension combination helpers
    // ========================================================================

    // Combine dimensions by adding exponents (multiply)
    constexpr dimension_t combine_dimensions_multiply(dimension_t left, dimension_t right) noexcept
    {
        return dimension_t{
            static_cast<int>(left.length + right.length),
            static_cast<int>(left.mass + right.mass),
            static_cast<int>(left.time + right.time),
            static_cast<int>(left.current + right.current),
            static_cast<int>(left.temperature + right.temperature),
            static_cast<int>(left.amount + right.amount),
            static_cast<int>(left.intensity + right.intensity)
        };
    }

    // Combine dimensions by subtracting exponents (divide)
    constexpr dimension_t combine_dimensions_divide(dimension_t left, dimension_t right) noexcept
    {
        return dimension_t{
            static_cast<int>(left.length - right.length),
            static_cast<int>(left.mass - right.mass),
            static_cast<int>(left.time - right.time),
            static_cast<int>(left.current - right.current),
            static_cast<int>(left.temperature - right.temperature),
            static_cast<int>(left.amount - right.amount),
            static_cast<int>(left.intensity - right.intensity)
        };
    }

    // ========================================================================
    // Type traits helpers
    // ========================================================================

    template<typename T>
    constexpr bool is_si_unit_v = is_si_unit<T>::value;

    template<typename T>
    struct is_integral_constant : std::false_type {};

    template<typename T, T Value>
    struct is_integral_constant<std::integral_constant<T, Value>> : std::true_type {};

    template<typename T>
    constexpr bool is_integral_constant_v = is_integral_constant<T>::value;

    // ========================================================================
    // Denominator item processor
    // ========================================================================
    // Handles recursive processing of denominator items: units and powers from per<...>

    namespace _si_cast_multi_impl
    {
        // Base case: no more items
        template<typename... Items>
        constexpr void process_items(intmax_t&, intmax_t&, dimension_t&) noexcept;

        // Specialization for empty items
        template<>
        constexpr void process_items<>(intmax_t&, intmax_t&, dimension_t&) noexcept
        {
            // Do nothing - base case
        }

        // Case 1: Single unit (denominator with power 1)
        template<typename Unit>
        constexpr void process_items(intmax_t& num, intmax_t& den, dimension_t& dim) noexcept
            requires is_si_unit_v<Unit>
        {
            using traits = si::is_si_unit<Unit>;
            num *= traits::ratio_type::den;
            den *= traits::ratio_type::num;
            dim = combine_dimensions_divide(dim, traits::value_dimension);
        }

        // Case 2: Unit followed by integral_constant power
        template<typename Unit, typename T, T Power>
        constexpr void process_items(
            intmax_t& num, intmax_t& den, dimension_t& dim) noexcept
            requires is_si_unit_v<Unit> && std::is_integral_v<T>
        {
            constexpr int PowerValue = static_cast<int>(Power);
            using traits = si::is_si_unit<Unit>;

            // Compute powered ratio
            intmax_t powered_num = constexpr_pow(traits::ratio_type::num, 
                                                  static_cast<unsigned int>(std::abs(PowerValue)));
            intmax_t powered_den = constexpr_pow(traits::ratio_type::den, 
                                                  static_cast<unsigned int>(std::abs(PowerValue)));

            if constexpr (PowerValue > 0)
            {
                num *= powered_den;
                den *= powered_num;
            }
            else if constexpr (PowerValue < 0)
            {
                num *= powered_num;
                den *= powered_den;
            }

            // Compute powered dimension
            dimension_t powered_dim = traits::value_dimension;
            powered_dim.length = static_cast<signed char>(powered_dim.length * PowerValue);
            powered_dim.mass = static_cast<signed char>(powered_dim.mass * PowerValue);
            powered_dim.time = static_cast<signed char>(powered_dim.time * PowerValue);
            powered_dim.current = static_cast<signed char>(powered_dim.current * PowerValue);
            powered_dim.temperature = static_cast<signed char>(powered_dim.temperature * PowerValue);
            powered_dim.amount = static_cast<signed char>(powered_dim.amount * PowerValue);
            powered_dim.intensity = static_cast<signed char>(powered_dim.intensity * PowerValue);

            dim = combine_dimensions_divide(dim, powered_dim);
        }

        // Case 3: Unit followed by another unit (multiple denominators without powers)
        template<typename Unit1, typename Unit2, typename... Rest>
        constexpr void process_items(
            intmax_t& num, intmax_t& den, dimension_t& dim) noexcept
            requires is_si_unit_v<Unit1> && is_si_unit_v<Unit2>
        {
            process_items<Unit1>(num, den, dim);
            process_items<Unit2, Rest...>(num, den, dim);
        }

        // Case 4: Unit, power, then more items
        template<typename Unit, typename T, T Power, typename Unit2, typename... Rest>
        constexpr void process_items(
            intmax_t& num, intmax_t& den, dimension_t& dim) noexcept
            requires is_si_unit_v<Unit> && std::is_integral_v<T> && is_si_unit_v<Unit2>
        {
            process_items<Unit, T, Power>(num, den, dim);
            process_items<Unit2, Rest...>(num, den, dim);
        }
    }

    // ========================================================================
    // Core multi-unit SI cast implementation
    // ========================================================================

    template<typename source_unit_t, typename... numerator_unit_types, typename... denominator_items>
    constexpr auto si_cast_multi_impl(
        const source_unit_t& source,
        std::tuple<numerator_unit_types...>*,
        std::tuple<denominator_items...>*) noexcept
    {
        using source_traits = si::is_si_unit<source_unit_t>;
        using source_value_type = typename source_traits::value_type;

        intmax_t result_num = source_traits::ratio_type::num;
        intmax_t result_den = source_traits::ratio_type::den;
        dimension_t result_dim = source_traits::value_dimension;

        // Multiply by numerator units
        (
            [&]()
            {
                using num_traits = si::is_si_unit<numerator_unit_types>;
                result_num *= num_traits::ratio_type::num;
                result_den *= num_traits::ratio_type::den;
                result_dim = combine_dimensions_multiply(result_dim, num_traits::value_dimension);
            }(),
            ...
        );

        // Divide by denominator items
        _si_cast_multi_impl::process_items<denominator_items...>(result_num, result_den, result_dim);

        using result_ratio = std::ratio<result_num, result_den>;
        using result_unit = unit_t<source_value_type, result_ratio, result_dim>;
        return result_unit(source.value());
    }

} // namespace si

// ============================================================================
// Public API: Overloads for si_cast_multi
// ============================================================================

namespace _si_cast_multi_detail {
    // Check if type is per<...>
    template<typename T>
    struct is_per : std::false_type {};

    template<typename... Units>
    struct is_per<si::per<Units...>> : std::true_type {};

    template<typename T>
    constexpr bool is_per_v = is_per<T>::value;

    // ========================================================================
    // Dimension validation concept
    // ========================================================================
    
    // Concept for single numerator dimensionality check
    // Allows any SI unit combination - dimension safety is enforced by ratio calculation
    template<typename NumUnit, typename DenomPer, typename SourceUnit>
    concept valid_si_cast_multi_single = 
        is_si_unit<NumUnit>::value &&
        is_per_v<DenomPer> &&
        is_si_unit<SourceUnit>::value;

    // Concept for two numerators (combined as multiply)
    template<typename Num1Unit, typename Num2Unit, typename DenomPer, typename SourceUnit>
    concept valid_si_cast_multi_dual =
        is_si_unit<Num1Unit>::value &&
        is_si_unit<Num2Unit>::value &&
        is_per_v<DenomPer> &&
        is_si_unit<SourceUnit>::value;

    // Concept for three numerators (combined as multiply)
    template<typename Num1Unit, typename Num2Unit, typename Num3Unit, typename DenomPer, typename SourceUnit>
    concept valid_si_cast_multi_triple =
        is_si_unit<Num1Unit>::value &&
        is_si_unit<Num2Unit>::value &&
        is_si_unit<Num3Unit>::value &&
        is_per_v<DenomPer> &&
        is_si_unit<SourceUnit>::value;

    // Helper struct for single numerator with per denominator
    template<typename num_t, typename per_wrapper>
    struct si_cast_multi_helper;

    template<typename num_t, typename... denoms>
    struct si_cast_multi_helper<num_t, si::per<denoms...>>
    {
        template<typename source_t>
        static constexpr auto call(const source_t& source) noexcept
        {
            return ::si::si_cast_multi_impl(
                source,
                static_cast<std::tuple<num_t>*>(nullptr),
                static_cast<std::tuple<denoms...>*>(nullptr));
        }
    };

    // Helper struct for two numerators with per denominator
    template<typename num1_t, typename num2_t, typename per_wrapper>
    struct si_cast_multi_helper2;

    template<typename num1_t, typename num2_t, typename... denoms>
    struct si_cast_multi_helper2<num1_t, num2_t, si::per<denoms...>>
    {
        template<typename source_t>
        static constexpr auto call(const source_t& source) noexcept
        {
            return ::si::si_cast_multi_impl(
                source,
                static_cast<std::tuple<num1_t, num2_t>*>(nullptr),
                static_cast<std::tuple<denoms...>*>(nullptr));
        }
    };

    // Helper struct for three numerators with per denominator
    template<typename num1_t, typename num2_t, typename num3_t, typename per_wrapper>
    struct si_cast_multi_helper3;

    template<typename num1_t, typename num2_t, typename num3_t, typename... denoms>
    struct si_cast_multi_helper3<num1_t, num2_t, num3_t, si::per<denoms...>>
    {
        template<typename source_t>
        static constexpr auto call(const source_t& source) noexcept
        {
            return ::si::si_cast_multi_impl(
                source,
                static_cast<std::tuple<num1_t, num2_t, num3_t>*>(nullptr),
                static_cast<std::tuple<denoms...>*>(nullptr));
        }
    };
}

// ============================================================================
// Overload 1: si_cast_multi<NumType, per<DenomTypes...>>(source)
// Single numerator with per<> denominator
// Concept checks that source dimensions match (numerator - denominator)
// ============================================================================
template<typename num_t, typename per_unit, typename source_t>
    requires _si_cast_multi_detail::valid_si_cast_multi_single<num_t, per_unit, source_t>
constexpr auto si_cast_multi(const source_t& source) noexcept
{
    return _si_cast_multi_detail::si_cast_multi_helper<num_t, per_unit>::call(source);
}

// ============================================================================
// Overload 2: si_cast_multi<Num1Type, Num2Type, per<DenomTypes...>>(source)
// Two numerators with per<> denominator
// ============================================================================
template<typename num1_t, typename num2_t, typename per_unit, typename source_t>
    requires _si_cast_multi_detail::valid_si_cast_multi_dual<num1_t, num2_t, per_unit, source_t>
constexpr auto si_cast_multi(const source_t& source) noexcept
{
    return _si_cast_multi_detail::si_cast_multi_helper2<num1_t, num2_t, per_unit>::call(source);
}

// ============================================================================
// Overload 3: si_cast_multi<Num1Type, Num2Type, Num3Type, per<DenomTypes...>>(source)
// Three numerators with per<> denominator
// ============================================================================
template<typename num1_t, typename num2_t, typename num3_t, typename per_unit, typename source_t>
    requires _si_cast_multi_detail::valid_si_cast_multi_triple<num1_t, num2_t, num3_t, per_unit, source_t>
constexpr auto si_cast_multi(const source_t& source) noexcept
{
    return _si_cast_multi_detail::si_cast_multi_helper3<num1_t, num2_t, num3_t, per_unit>::call(source);
}

} // namespace si








