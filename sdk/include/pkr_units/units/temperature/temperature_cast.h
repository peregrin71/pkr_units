#pragma once

#include <pkr_units/impl/namespace_config.h>
#include "celsius.h"
#include "fahrenheit.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// temperature_cast: Converts between offset-based temperature scales
// 
// This function handles temperature conversions that require offset adjustments
// (Celsius ↔ Fahrenheit). Unlike unit_cast(), temperature_cast() is needed because
// these temperature scales have different zero points.
// 
// Conversion formulas:
// - Celsius to Fahrenheit: °F = (°C × 9/5) + 32
// - Fahrenheit to Celsius: °C = (°F - 32) × 5/9
// - Kelvin conversions use unit_cast() (pure ratio, no offset needed)
// 
// Example:
//   celsius_t c{25.0};
//   fahrenheit_t f = temperature_cast<fahrenheit_t>(c);  // 77°F

template<typename target_temp_t, typename source_temp_t>
constexpr target_temp_t temperature_cast(const source_temp_t& source) noexcept;

// Celsius to Fahrenheit specialization
template<>
constexpr fahrenheit_t temperature_cast<fahrenheit_t, celsius_t>(const celsius_t& source) noexcept
{
    // °F = (°C × 9/5) + 32
    return fahrenheit_t((source.value() * 9.0 / 5.0) + 32.0);
}

// Fahrenheit to Celsius specialization
template<>
constexpr celsius_t temperature_cast<celsius_t, fahrenheit_t>(const fahrenheit_t& source) noexcept
{
    // °C = (°F - 32) × 5/9
    return celsius_t((source.value() - 32.0) * 5.0 / 9.0);
}

}  // PKR_UNITS_END_NAMESPACE






