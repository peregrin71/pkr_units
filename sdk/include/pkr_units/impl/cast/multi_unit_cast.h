#pragma once

#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/cast/unit_pow.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <ratio>
#include <tuple>
#include <type_traits>
#include <utility>

namespace PKR_UNITS_NAMESPACE
{

// ========================================================================
// Marker wrapper to indicate units in the denominator and their powers
// ========================================================================
// Usage patterns for multi_unit_cast:
//   multi_unit_cast<meter_t, per<second_t>>(source)                          // m/s
//   multi_unit_cast<meter_t, per_unit_squared<hour_t>>(source)               // m/h^2
//   multi_unit_cast<meter_t, per_unit_cubed<second_t>>(source)               // m/s^3
//   multi_unit_cast<kilogram_t, meter_t, per<second_t>>(source)              // kg*m/s
//   multi_unit_cast<meter_t, per<hour_t, std::integral_constant<int, 2>>>(source)  // m/h^2

template <typename... Units>
struct per
{
};

// Specialized per templates for common powers to avoid explicit integral_constant

template <typename Unit>
struct per_unit_squared : per<Unit, std::integral_constant<int, 2>>
{
    using per_type = per<Unit, std::integral_constant<int, 2>>;
};

template <typename Unit>
struct per_unit_cubed : per<Unit, std::integral_constant<int, 3>>
{
    using per_type = per<Unit, std::integral_constant<int, 3>>;
};

template <typename Unit>
struct per_unit_quartic : per<Unit, std::integral_constant<int, 4>>
{
    using per_type = per<Unit, std::integral_constant<int, 4>>;
};

template <typename Unit>
struct per_unit_inverse : per<Unit, std::integral_constant<int, -1>>
{
    using per_type = per<Unit, std::integral_constant<int, -1>>;
};

template <typename Unit>
struct per_unit_inverse_squared : per<Unit, std::integral_constant<int, -2>>
{
    using per_type = per<Unit, std::integral_constant<int, -2>>;
};

// ========================================================================
// Dimension combination helpers
// ========================================================================

constexpr dimension_t combine_dimensions_multiply(dimension_t left, dimension_t right) noexcept
{
    return dimension_t{
        static_cast<int>(left.length + right.length),
        static_cast<int>(left.mass + right.mass),
        static_cast<int>(left.time + right.time),
        static_cast<int>(left.current + right.current),
        static_cast<int>(left.temperature + right.temperature),
        static_cast<int>(left.amount + right.amount),
        static_cast<int>(left.intensity + right.intensity),
        static_cast<int>(left.angle + right.angle)};
}

constexpr dimension_t combine_dimensions_divide(dimension_t left, dimension_t right) noexcept
{
    return dimension_t{
        static_cast<int>(left.length - right.length),
        static_cast<int>(left.mass - right.mass),
        static_cast<int>(left.time - right.time),
        static_cast<int>(left.current - right.current),
        static_cast<int>(left.temperature - right.temperature),
        static_cast<int>(left.amount - right.amount),
        static_cast<int>(left.intensity - right.intensity),
        static_cast<int>(left.angle - right.angle)};
}

constexpr dimension_t pow_dimension(dimension_t dim, int power) noexcept
{
    return dimension_t{
        static_cast<int>(dim.length * power),
        static_cast<int>(dim.mass * power),
        static_cast<int>(dim.time * power),
        static_cast<int>(dim.current * power),
        static_cast<int>(dim.temperature * power),
        static_cast<int>(dim.amount * power),
        static_cast<int>(dim.intensity * power),
        static_cast<int>(dim.angle * power)};
}

// ========================================================================
// Type traits helpers
// ========================================================================

template <typename T>
struct is_integral_constant : std::false_type
{
};

template <typename T, T Value>
struct is_integral_constant<std::integral_constant<T, Value>> : std::true_type
{
};

template <typename T>
constexpr bool is_integral_constant_v = is_integral_constant<T>::value;

// ========================================================================
// Ratio helpers
// ========================================================================

template <typename Ratio, int power_v>
struct ratio_pow
{
    static constexpr int power = power_v;
    static constexpr intmax_t num =
        (power >= 0) ? constexpr_pow(Ratio::num, static_cast<unsigned int>(power)) : constexpr_pow(Ratio::den, static_cast<unsigned int>(-power));
    static constexpr intmax_t den =
        (power >= 0) ? constexpr_pow(Ratio::den, static_cast<unsigned int>(power)) : constexpr_pow(Ratio::num, static_cast<unsigned int>(-power));
    using type = std::ratio<num, den>;
};

template <typename type_t, typename source_ratio_t, typename target_ratio_t>
constexpr type_t compute_conversion_factor() noexcept
{
    return (static_cast<type_t>(source_ratio_t::num) * static_cast<type_t>(target_ratio_t::den)) /
           (static_cast<type_t>(source_ratio_t::den) * static_cast<type_t>(target_ratio_t::num));
}

// ========================================================================
// Numerator/denominator aggregation
// ========================================================================

template <typename Ratio, dimension_t Dim, typename... Units>
struct apply_numerators;

template <typename Ratio, dimension_t Dim>
struct apply_numerators<Ratio, Dim>
{
    using ratio = Ratio;
    static constexpr dimension_t dim = Dim;
};

template <typename Ratio, dimension_t Dim, typename Unit, typename... Rest>
    requires(is_pkr_unit_c<Unit>)
struct apply_numerators<Ratio, Dim, Unit, Rest...>
{
    using unit_traits = details::is_pkr_unit<Unit>;
    using next_ratio = std::ratio_multiply<Ratio, typename unit_traits::ratio_type>;
    static constexpr dimension_t next_dim = combine_dimensions_multiply(Dim, unit_traits::value_dimension);
    using next = apply_numerators<next_ratio, next_dim, Rest...>;
    using ratio = typename next::ratio;
    static constexpr dimension_t dim = next::dim;
};

template <typename Ratio, dimension_t Dim, typename... Items>
struct apply_denominators;

template <typename Ratio, dimension_t Dim>
struct apply_denominators<Ratio, Dim>
{
    using ratio = Ratio;
    static constexpr dimension_t dim = Dim;
};

template <typename Ratio, dimension_t Dim, typename Unit>
    requires(is_pkr_unit_c<Unit>)
struct apply_denominators<Ratio, Dim, Unit>
{
    using unit_traits = details::is_pkr_unit<Unit>;
    using powered_ratio = typename ratio_pow<typename unit_traits::ratio_type, 1>::type;
    using next_ratio = std::ratio_divide<Ratio, powered_ratio>;
    static constexpr dimension_t powered_dim = pow_dimension(unit_traits::value_dimension, 1);
    static constexpr dimension_t next_dim = combine_dimensions_divide(Dim, powered_dim);
    using ratio = next_ratio;
    static constexpr dimension_t dim = next_dim;
};

template <typename Ratio, dimension_t Dim, typename Unit, typename PowerConst, typename... Rest>
    requires(is_pkr_unit_c<Unit> && is_integral_constant_v<PowerConst>)
struct apply_denominators<Ratio, Dim, Unit, PowerConst, Rest...>
{
    using unit_traits = details::is_pkr_unit<Unit>;
    static constexpr int power = static_cast<int>(PowerConst::value);
    using powered_ratio = typename ratio_pow<typename unit_traits::ratio_type, power>::type;
    using next_ratio = std::ratio_divide<Ratio, powered_ratio>;
    static constexpr dimension_t powered_dim = pow_dimension(unit_traits::value_dimension, power);
    static constexpr dimension_t next_dim = combine_dimensions_divide(Dim, powered_dim);
    using next = apply_denominators<next_ratio, next_dim, Rest...>;
    using ratio = typename next::ratio;
    static constexpr dimension_t dim = next::dim;
};

template <typename Ratio, dimension_t Dim, typename Unit, typename Unit2, typename... Rest>
    requires(is_pkr_unit_c<Unit> && is_pkr_unit_c<Unit2>)
struct apply_denominators<Ratio, Dim, Unit, Unit2, Rest...>
{
    using unit_traits = details::is_pkr_unit<Unit>;
    using powered_ratio = typename ratio_pow<typename unit_traits::ratio_type, 1>::type;
    using next_ratio = std::ratio_divide<Ratio, powered_ratio>;
    static constexpr dimension_t powered_dim = pow_dimension(unit_traits::value_dimension, 1);
    static constexpr dimension_t next_dim = combine_dimensions_divide(Dim, powered_dim);
    using next = apply_denominators<next_ratio, next_dim, Unit2, Rest...>;
    using ratio = typename next::ratio;
    static constexpr dimension_t dim = next::dim;
};

// ========================================================================
// Core multi-unit SI cast implementation
// ========================================================================

template <typename source_unit_t, typename... numerator_unit_types, typename... denominator_items>
constexpr auto multi_unit_cast_impl(const source_unit_t& source, std::tuple<numerator_unit_types...>*, std::tuple<denominator_items...>*) noexcept
{
    using source_traits = details::is_pkr_unit<source_unit_t>;
    using source_ratio = typename source_traits::ratio_type;
    using source_value_type = typename source_traits::value_type;

    using after_num = apply_numerators<std::ratio<1, 1>, scalar_dimension, numerator_unit_types...>;
    using after_den = apply_denominators<typename after_num::ratio, after_num::dim, denominator_items...>;

    using result_ratio = typename after_den::ratio;
    constexpr dimension_t result_dim = after_den::dim;

    using result_unit = details::unit_t<source_value_type, result_ratio, result_dim>;
    constexpr source_value_type conversion_factor = compute_conversion_factor<source_value_type, source_ratio, result_ratio>();
    return result_unit(source.value() * conversion_factor);
}

// ============================================================================
// Public API: Overloads for multi_unit_cast
// ============================================================================

namespace _multi_unit_cast_detail
{
// Check if type is per<...>
template <typename T, typename = void>
struct is_per : std::false_type
{
};

template <typename... Units>
struct is_per<per<Units...>> : std::true_type
{
};

template <typename T>
struct is_per<T, std::void_t<typename T::per_type>> : is_per<typename T::per_type>
{
};

template <typename T>
constexpr bool is_per_v = is_per<T>::value;

// ========================================================================
// Dimension validation concept
// ========================================================================

template <typename NumUnit, typename DenomPer, typename SourceUnit>
concept valid_multi_unit_cast_single = is_pkr_unit_c<NumUnit> && is_per_v<DenomPer> && is_pkr_unit_c<SourceUnit>;

template <typename Num1Unit, typename Num2Unit, typename DenomPer, typename SourceUnit>
concept valid_multi_unit_cast_dual = is_pkr_unit_c<Num1Unit> && is_pkr_unit_c<Num2Unit> && is_per_v<DenomPer> && is_pkr_unit_c<SourceUnit>;

template <typename Num1Unit, typename Num2Unit, typename Num3Unit, typename DenomPer, typename SourceUnit>
concept valid_multi_unit_cast_triple =
    is_pkr_unit_c<Num1Unit> && is_pkr_unit_c<Num2Unit> && is_pkr_unit_c<Num3Unit> && is_per_v<DenomPer> && is_pkr_unit_c<SourceUnit>;

// Helper struct for single numerator with per denominator
template <typename num_t, typename per_wrapper>
struct multi_unit_cast_helper;

template <typename num_t, typename per_wrapper>
    requires(requires { typename per_wrapper::per_type; })
struct multi_unit_cast_helper<num_t, per_wrapper>
{
    template <typename source_t>
    static constexpr auto call(const source_t& source) noexcept
    {
        return multi_unit_cast_helper<num_t, typename per_wrapper::per_type>::call(source);
    }
};

template <typename num_t, typename... denoms>
struct multi_unit_cast_helper<num_t, per<denoms...>>
{
    template <typename source_t>
    static constexpr auto call(const source_t& source) noexcept
    {
        return multi_unit_cast_impl(source, static_cast<std::tuple<num_t>*>(nullptr), static_cast<std::tuple<denoms...>*>(nullptr));
    }
};

// Helper struct for two numerators with per denominator
template <typename num1_t, typename num2_t, typename per_wrapper>
struct multi_unit_cast_helper2;

template <typename num1_t, typename num2_t, typename per_wrapper>
    requires(requires { typename per_wrapper::per_type; })
struct multi_unit_cast_helper2<num1_t, num2_t, per_wrapper>
{
    template <typename source_t>
    static constexpr auto call(const source_t& source) noexcept
    {
        return multi_unit_cast_helper2<num1_t, num2_t, typename per_wrapper::per_type>::call(source);
    }
};

template <typename num1_t, typename num2_t, typename... denoms>
struct multi_unit_cast_helper2<num1_t, num2_t, per<denoms...>>
{
    template <typename source_t>
    static constexpr auto call(const source_t& source) noexcept
    {
        return multi_unit_cast_impl(source, static_cast<std::tuple<num1_t, num2_t>*>(nullptr), static_cast<std::tuple<denoms...>*>(nullptr));
    }
};

// Helper struct for three numerators with per denominator
template <typename num1_t, typename num2_t, typename num3_t, typename per_wrapper>
struct multi_unit_cast_helper3;

template <typename num1_t, typename num2_t, typename num3_t, typename per_wrapper>
    requires(requires { typename per_wrapper::per_type; })
struct multi_unit_cast_helper3<num1_t, num2_t, num3_t, per_wrapper>
{
    template <typename source_t>
    static constexpr auto call(const source_t& source) noexcept
    {
        return multi_unit_cast_helper3<num1_t, num2_t, num3_t, typename per_wrapper::per_type>::call(source);
    }
};

template <typename num1_t, typename num2_t, typename num3_t, typename... denoms>
struct multi_unit_cast_helper3<num1_t, num2_t, num3_t, per<denoms...>>
{
    template <typename source_t>
    static constexpr auto call(const source_t& source) noexcept
    {
        return multi_unit_cast_impl(source, static_cast<std::tuple<num1_t, num2_t, num3_t>*>(nullptr), static_cast<std::tuple<denoms...>*>(nullptr));
    }
};
} // namespace _multi_unit_cast_detail

// ============================================================================
// Overload 1: multi_unit_cast<NumType, per<DenomTypes...>>(source)
// Single numerator with per<> denominator
// ============================================================================

template <typename num_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_single<num_t, per_unit, source_t>
constexpr auto multi_unit_cast(const source_t& source) noexcept
{
    return _multi_unit_cast_detail::multi_unit_cast_helper<num_t, per_unit>::call(source);
}

// ============================================================================
// Overload 2: multi_unit_cast<Num1Type, Num2Type, per<DenomTypes...>>(source)
// Two numerators with per<> denominator
// ============================================================================

template <typename num1_t, typename num2_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_dual<num1_t, num2_t, per_unit, source_t>
constexpr auto multi_unit_cast(const source_t& source) noexcept
{
    return _multi_unit_cast_detail::multi_unit_cast_helper2<num1_t, num2_t, per_unit>::call(source);
}

// ============================================================================
// Overload 3: multi_unit_cast<Num1Type, Num2Type, Num3Type, per<DenomTypes...>>(source)
// Three numerators with per<> denominator
// ============================================================================

template <typename num1_t, typename num2_t, typename num3_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_triple<num1_t, num2_t, num3_t, per_unit, source_t>
constexpr auto multi_unit_cast(const source_t& source) noexcept
{
    return _multi_unit_cast_detail::multi_unit_cast_helper3<num1_t, num2_t, num3_t, per_unit>::call(source);
}

// ========================================================================
// multi_unit_cast_to_base_units
// Returns a unit_t with ratio<1,1> for the computed dimension.
// ========================================================================

template <typename num_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_single<num_t, per_unit, source_t>
constexpr auto multi_unit_cast_to_base_units(const source_t& source) noexcept
{
    auto result = multi_unit_cast<num_t, per_unit>(source);
    return result.in_base_si_units();
}

template <typename num1_t, typename num2_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_dual<num1_t, num2_t, per_unit, source_t>
constexpr auto multi_unit_cast_to_base_units(const source_t& source) noexcept
{
    auto result = multi_unit_cast<num1_t, num2_t, per_unit>(source);
    return result.in_base_si_units();
}

template <typename num1_t, typename num2_t, typename num3_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_triple<num1_t, num2_t, num3_t, per_unit, source_t>
constexpr auto multi_unit_cast_to_base_units(const source_t& source) noexcept
{
    auto result = multi_unit_cast<num1_t, num2_t, num3_t, per_unit>(source);
    return result.in_base_si_units();
}

// ========================================================================
// multi_unit_cast_to_derived
// Returns the derived unit type for ratio<1,1> and computed dimension.
// ========================================================================

template <typename num_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_single<num_t, per_unit, source_t>
constexpr auto multi_unit_cast_to_derived(const source_t& source) noexcept
{
    auto base = multi_unit_cast_to_base_units<num_t, per_unit>(source);
    using base_unit = std::decay_t<decltype(base)>;
    using value_type = typename base_unit::value_type;
    using derived_type = typename details::derived_unit_type_t<value_type, std::ratio<1, 1>, base_unit::dimension::value>::type;
    return derived_type{base.value()};
}

template <typename num1_t, typename num2_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_dual<num1_t, num2_t, per_unit, source_t>
constexpr auto multi_unit_cast_to_derived(const source_t& source) noexcept
{
    auto base = multi_unit_cast_to_base_units<num1_t, num2_t, per_unit>(source);
    using base_unit = std::decay_t<decltype(base)>;
    using value_type = typename base_unit::value_type;
    using derived_type = typename details::derived_unit_type_t<value_type, std::ratio<1, 1>, base_unit::dimension::value>::type;
    return derived_type{base.value()};
}

template <typename num1_t, typename num2_t, typename num3_t, typename per_unit, typename source_t>
    requires _multi_unit_cast_detail::valid_multi_unit_cast_triple<num1_t, num2_t, num3_t, per_unit, source_t>
constexpr auto multi_unit_cast_to_derived(const source_t& source) noexcept
{
    auto base = multi_unit_cast_to_base_units<num1_t, num2_t, num3_t, per_unit>(source);
    using base_unit = std::decay_t<decltype(base)>;
    using value_type = typename base_unit::value_type;
    using derived_type = typename details::derived_unit_type_t<value_type, std::ratio<1, 1>, base_unit::dimension::value>::type;
    return derived_type{base.value()};
}

} // namespace PKR_UNITS_NAMESPACE
