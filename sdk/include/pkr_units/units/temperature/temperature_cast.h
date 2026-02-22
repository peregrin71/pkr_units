#pragma once
#include <pkr_units/impl/cast/unit_cast.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/units/base/temperature.h>
#include <pkr_units/units/temperature/celsius.h>
#include <pkr_units/units/temperature/fahrenheit.h>
#include <type_traits>
#include <compare>

namespace PKR_UNITS_NAMESPACE
{
// unit_cast specializations: Converts between offset-based temperature scales.
//
// Instead of relying on an ad-hoc trait struct, we tag Celsius and Fahrenheit
// units via the `tag_t` parameter of `unit_t`.  Conversions are driven by the
// tag type at compile time.
inline constexpr double KELVIN_OFFSET = 273.15;

// helper predicate implementation that avoids touching `is_pkr_unit<U>::tag_type`
// when `U` is not actually a pkr unit.  This prevents hard-to-debug compile
// errors when the variable template is instantiated with unrelated types
// (e.g. `dimension_t`).

template <typename U, bool = is_pkr_unit_c<U>>
struct affine_temp_unit_helper : std::false_type
{
};

// Specialization for real unit types
template <typename U>
struct affine_temp_unit_helper<U, true>
    : std::bool_constant<
          std::is_same_v<typename details::is_pkr_unit<U>::tag_type, celsius_tag_t> ||
          std::is_same_v<typename details::is_pkr_unit<U>::tag_type, fahrenheit_tag_t>>
{
};

// public variable template
template <typename U>
inline constexpr bool is_affine_temp_unit_v = affine_temp_unit_helper<U>::value;

// any temperature-like quantity is either an affine unit (C/F) or a
// pkr_unit whose dimension equals temperature_dimension (Kelvin and its
// ratio-based derivatives).  Wrap the dimension check in a helper to avoid
// referencing `details::is_pkr_unit<T>::value_dimension` when `T` is not a
// unit type.

template <typename T, bool = is_pkr_unit_c<T>>
struct temperature_like_helper : std::false_type
{
};

template <typename T>
struct temperature_like_helper<T, true> : std::bool_constant<is_affine_temp_unit_v<T> || (details::is_pkr_unit<T>::value_dimension == temperature_dimension)>
{
};

template <typename T>
inline constexpr bool is_temperature_like_v = temperature_like_helper<T>::value;

// convert any temperature-like quantity to a Kelvin value (double) for
// comparison or intermediate calculations
template <typename T>
    requires is_temperature_like_v<T>
constexpr double to_kelvin_for_comparison(const T& temp) noexcept
{
    if constexpr (std::is_same_v<unit_tag_t<T>, celsius_tag_t>)
    {
        return static_cast<double>(temp.value()) + KELVIN_OFFSET;
    }
    else if constexpr (std::is_same_v<unit_tag_t<T>, fahrenheit_tag_t>)
    {
        return ((static_cast<double>(temp.value()) - 32.0) * 5.0 / 9.0) + KELVIN_OFFSET;
    }
    else
    {
        auto kelvin_unit = details::unit_cast_impl<std::ratio<1, 1>>(temp);
        return static_cast<double>(kelvin_unit.value());
    }
}

template <typename target_unit_t, typename source_unit_t>
    requires is_temperature_like_v<target_unit_t> && is_temperature_like_v<source_unit_t> &&
             (is_affine_temp_unit_v<target_unit_t> || is_affine_temp_unit_v<source_unit_t>)
constexpr target_unit_t unit_cast(const source_unit_t& source) noexcept
{
    double kelvin_value = to_kelvin_for_comparison(source);
    if constexpr (is_affine_temp_unit_v<target_unit_t>)
    {
        if constexpr (std::is_same_v<unit_tag_t<target_unit_t>, celsius_tag_t>)
        {
            return target_unit_t{static_cast<unit_value_t<target_unit_t>>(kelvin_value - KELVIN_OFFSET)};
        }
        else // fahrenheit
        {
            double f = ((kelvin_value - KELVIN_OFFSET) * 9.0 / 5.0) + 32.0;
            return target_unit_t{static_cast<unit_value_t<target_unit_t>>(f)};
        }
    }
    else
    {
        using ratio_type = unit_ratio_t<target_unit_t>;
        using value_type = unit_value_t<target_unit_t>;
        unit_t<value_type, std::ratio<1, 1>, temperature_dimension> base_kelvin{static_cast<value_type>(kelvin_value)};
        auto converted = details::unit_cast_impl<ratio_type>(base_kelvin);
        return target_unit_t{converted.value()};
    }
}

// Special comparison operators for temperature units with affine transformations
// (the `to_kelvin_for_comparison` defined above serves both comparison and
// casting purposes; no duplicate helper is required here)

// Three-way comparison for temperature units
template <typename T1, typename T2>
    requires is_temperature_like_v<T1> && is_temperature_like_v<T2>
constexpr auto operator<=>(const T1& lhs, const T2& rhs) noexcept
{
    double lhs_kelvin = to_kelvin_for_comparison(lhs);
    double rhs_kelvin = to_kelvin_for_comparison(rhs);
    return lhs_kelvin <=> rhs_kelvin;
}

// Equality comparison for temperature units (needed for <=> to work properly)
template <typename T1, typename T2>
    requires is_temperature_like_v<T1> && is_temperature_like_v<T2>
constexpr bool operator==(const T1& lhs, const T2& rhs) noexcept
{
    double lhs_kelvin = to_kelvin_for_comparison(lhs);
    double rhs_kelvin = to_kelvin_for_comparison(rhs);
    return lhs_kelvin == rhs_kelvin;
}
} // namespace PKR_UNITS_NAMESPACE
