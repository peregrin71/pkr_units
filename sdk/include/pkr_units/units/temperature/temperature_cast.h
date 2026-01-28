#pragma once

#include <pkr_units/impl/cast/unit_cast.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/base/temperature.h>
#include <pkr_units/units/temperature/celsius.h>
#include <pkr_units/units/temperature/fahrenheit.h>
#include <type_traits>
#include <compare>

namespace PKR_UNITS_NAMESPACE
{

// unit_cast specializations: Converts between offset-based temperature scales.
//
// These specializations handle conversions that require offset adjustments
// (Celsius <-> Fahrenheit <-> Kelvin). They intentionally bypass the ratio-based
// unit_cast template because these scales have different zero points. Kelvin
// conversions to other Kelvin-based units remain handled by the generic unit_cast.

inline constexpr double KELVIN_OFFSET = 273.15;

template <typename T>
struct temperature_affine_traits
{
    static constexpr bool is_affine = false;
};

template <>
struct temperature_affine_traits<celsius_t>
{
    static constexpr bool is_affine = true;
    using value_type = double;

    static constexpr value_type to_kelvin(value_type value) noexcept
    {
        return value + KELVIN_OFFSET;
    }

    static constexpr value_type from_kelvin(value_type value) noexcept
    {
        return value - KELVIN_OFFSET;
    }
};

template <>
struct temperature_affine_traits<fahrenheit_t>
{
    static constexpr bool is_affine = true;
    using value_type = double;

    static constexpr value_type to_kelvin(value_type value) noexcept
    {
        return ((value - 32.0) * 5.0 / 9.0) + KELVIN_OFFSET;
    }

    static constexpr value_type from_kelvin(value_type value) noexcept
    {
        return ((value - KELVIN_OFFSET) * 9.0 / 5.0) + 32.0;
    }
};

template <typename T, typename = void>
struct is_temperature_pkr_unit : std::false_type
{
};

template <typename T>
struct is_temperature_pkr_unit<T, std::enable_if_t<details::pkr_unit_concept<T>>>
    : std::bool_constant<(details::is_pkr_unit<T>::value_dimension == temperature_dimension)>
{
};

template <typename T>
inline constexpr bool is_temperature_like_v = temperature_affine_traits<T>::is_affine || is_temperature_pkr_unit<T>::value;

template <typename target_unit_t, typename source_unit_t>
requires is_temperature_like_v<target_unit_t> && is_temperature_like_v<source_unit_t> &&
    (temperature_affine_traits<target_unit_t>::is_affine || temperature_affine_traits<source_unit_t>::is_affine)
constexpr target_unit_t unit_cast(const source_unit_t& source) noexcept
{
    double kelvin_value = 0.0;

    if constexpr (temperature_affine_traits<source_unit_t>::is_affine)
    {
        kelvin_value = temperature_affine_traits<source_unit_t>::to_kelvin(source.value());
    }
    else
    {
        auto kelvin_unit = details::unit_cast_impl<std::ratio<1>>(source);
        kelvin_value = static_cast<double>(kelvin_unit.value());
    }

    if constexpr (temperature_affine_traits<target_unit_t>::is_affine)
    {
        return target_unit_t{temperature_affine_traits<target_unit_t>::from_kelvin(kelvin_value)};
    }
    else
    {
        using ratio_type = typename details::is_pkr_unit<target_unit_t>::ratio_type;
        using value_type = typename details::is_pkr_unit<target_unit_t>::value_type;
        details::unit_t<value_type, std::ratio<1>, temperature_dimension> base_kelvin{static_cast<value_type>(kelvin_value)};
        auto converted = details::unit_cast_impl<ratio_type>(base_kelvin);
        return target_unit_t{converted.value()};
    }
}

// Special comparison operators for temperature units with affine transformations

// Helper function to convert any temperature unit to Kelvin for comparison
template <typename T>
requires is_temperature_like_v<T>
constexpr double to_kelvin_for_comparison(const T& temp) noexcept
{
    if constexpr (temperature_affine_traits<T>::is_affine)
    {
        return temperature_affine_traits<T>::to_kelvin(temp.value());
    }
    else
    {
        // For Kelvin-based units, just return the value
        return static_cast<double>(temp.value());
    }
}

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
