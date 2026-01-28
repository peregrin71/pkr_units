#pragma once
#include <concepts>
#include <complex>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Concept for types that can represent unit quantity values
// Supports:
//   - Arithmetic types (int, float, double, etc.)
//   - Complex types (std::complex<float>, std::complex<double>, etc.)
template <typename type_t>
concept is_unit_value_type_c = requires(type_t a, type_t b, double d) {
    { a + b } -> std::convertible_to<type_t>;
    { a - b } -> std::convertible_to<type_t>;
    { a * b } -> std::convertible_to<type_t>;
    { a / b } -> std::convertible_to<type_t>;
    { a * d } -> std::convertible_to<type_t>;
    { a / d } -> std::convertible_to<type_t>;
    { static_cast<type_t>(d) };
};

// Verify fundamental types satisfy the concept
static_assert(is_unit_value_type_c<float>);
static_assert(is_unit_value_type_c<double>);
static_assert(is_unit_value_type_c<int>);

// Concept to check if a unit type represents an angle (dimensionless in angle sense)
template <typename UnitT>
concept is_angle_unit_c = requires { typename UnitT::dimension; } && UnitT::dimension::value.angle == 1 && UnitT::dimension::value.length == 0 &&
                          UnitT::dimension::value.mass == 0 && UnitT::dimension::value.time == 0 && UnitT::dimension::value.current == 0 &&
                          UnitT::dimension::value.temperature == 0 && UnitT::dimension::value.amount == 0 && UnitT::dimension::value.intensity == 0;

} // namespace PKR_UNITS_NAMESPACE
