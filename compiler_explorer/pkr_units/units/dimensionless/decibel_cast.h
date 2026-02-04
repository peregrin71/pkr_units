#pragma once
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/unit_cast.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/dimensionless/ratio.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/dimensionless/decibel.h"

namespace PKR_UNITS_NAMESPACE
{
namespace details
{
template <typename T, typename = void>
struct is_dimensionless_unit : std::false_type
{
};

template <typename T>
struct is_dimensionless_unit<T, std::void_t<decltype(details::is_pkr_unit<T>::value_dimension)>>
    : std::bool_constant<(details::is_pkr_unit<T>::value_dimension == scalar_dimension)>
{
};

template <typename T>
inline constexpr bool is_dimensionless_unit_v = is_dimensionless_unit<T>::value;
} // namespace details

// Linear ratio -> decibel (power)
template <typename target_unit_t, typename source_unit_t>
    requires std::is_same_v<target_unit_t, decibel_power_t<double>> && details::is_dimensionless_unit_v<source_unit_t>
inline decibel_power_t<double> unit_cast(const source_unit_t& source)
{
    auto canonical = details::unit_cast_impl<std::ratio<1, 1>>(source);
    double value = static_cast<double>(canonical.value());
    if (value <= 0.0)
    {
        throw std::invalid_argument("decibel_power conversion requires positive linear ratio");
    }
    return decibel_power_t<double>{10.0 * std::log10(value)};
}

// Linear ratio -> decibel (amplitude)
template <typename target_unit_t, typename source_unit_t>
    requires std::is_same_v<target_unit_t, decibel_amplitude_t<double>> && details::is_dimensionless_unit_v<source_unit_t>
inline decibel_amplitude_t<double> unit_cast(const source_unit_t& source)
{
    auto canonical = details::unit_cast_impl<std::ratio<1, 1>>(source);
    double value = static_cast<double>(canonical.value());
    if (value <= 0.0)
    {
        throw std::invalid_argument("decibel_amplitude conversion requires positive linear ratio");
    }
    return decibel_amplitude_t<double>{20.0 * std::log10(value)};
}

// Decibel (power) -> linear ratio (dimensionless)
template <PKR_UNITS_NAMESPACE::is_unit_value_type_c SourceT, typename target_unit_t>
    requires details::is_dimensionless_unit_v<target_unit_t>
inline target_unit_t unit_cast(const decibel_power_t<SourceT>& source)
{
    double linear = std::pow(10.0, source.value() / 10.0);
    details::unit_t<double, std::ratio<1, 1>, scalar_dimension> base{linear};
    auto converted = details::unit_cast_impl<typename details::is_pkr_unit<target_unit_t>::ratio_type>(base);
    return target_unit_t{converted.value()};
}

// Decibel (amplitude) -> linear ratio (dimensionless)
template <PKR_UNITS_NAMESPACE::is_unit_value_type_c SourceT, typename target_unit_t>
    requires details::is_dimensionless_unit_v<target_unit_t>
inline target_unit_t unit_cast(const decibel_amplitude_t<SourceT>& source)
{
    double linear = std::pow(10.0, source.value() / 20.0);
    details::unit_t<double, std::ratio<1, 1>, scalar_dimension> base{linear};
    auto converted = details::unit_cast_impl<typename details::is_pkr_unit<target_unit_t>::ratio_type>(base);
    return target_unit_t{converted.value()};
}
} // namespace PKR_UNITS_NAMESPACE
