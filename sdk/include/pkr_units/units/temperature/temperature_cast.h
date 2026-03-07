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
// Tag-based dispatch at compile-time.
inline constexpr double KELVIN_OFFSET = 273.15;

// Concept: Type is a tagged temperature unit (Celsius or Fahrenheit)
template <typename U>
concept is_tagged_temp_unit_c = is_pkr_unit_c<U> && (std::is_same_v<unit_tag_t<U>, celsius_tag_t> || std::is_same_v<unit_tag_t<U>, fahrenheit_tag_t>);

// Concept: Type is temperature-like (tagged Celsius/Fahrenheit or Kelvin-based dimension)
template <typename T>
concept is_temperature_like_c = is_pkr_unit_c<T> && (is_tagged_temp_unit_c<T> || (details::is_pkr_unit<T>::value_dimension == temperature_dimension));

// convert any temperature-like quantity to a Kelvin value (double) for
// comparison or intermediate calculations
template <typename T>
    requires is_temperature_like_c<T>
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
    requires is_temperature_like_c<target_unit_t> && is_temperature_like_c<source_unit_t> &&
             (is_tagged_temp_unit_c<target_unit_t> || is_tagged_temp_unit_c<source_unit_t>)
constexpr target_unit_t unit_cast(const source_unit_t& source) noexcept
{
    double kelvin_value = to_kelvin_for_comparison(source);
    if constexpr (is_tagged_temp_unit_c<target_unit_t>)
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
    requires is_temperature_like_c<T1> && is_temperature_like_c<T2>
constexpr auto operator<=>(const T1& lhs, const T2& rhs) noexcept
{
    double lhs_kelvin = to_kelvin_for_comparison(lhs);
    double rhs_kelvin = to_kelvin_for_comparison(rhs);
    return lhs_kelvin <=> rhs_kelvin;
}

// Equality comparison for temperature units (needed for <=> to work properly)
template <typename T1, typename T2>
    requires is_temperature_like_c<T1> && is_temperature_like_c<T2>
constexpr bool operator==(const T1& lhs, const T2& rhs) noexcept
{
    double lhs_kelvin = to_kelvin_for_comparison(lhs);
    double rhs_kelvin = to_kelvin_for_comparison(rhs);
    return lhs_kelvin == rhs_kelvin;
}
} // namespace PKR_UNITS_NAMESPACE
