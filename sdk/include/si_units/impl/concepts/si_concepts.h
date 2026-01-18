#pragma once
#include <concepts>
#include <complex>
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Concept for types that can represent SI quantity values
// Supports:
//   - Arithmetic types (int, float, double, etc.)
//   - Complex types (std::complex<float>, std::complex<double>, etc.)
template<typename type_t>
concept is_si_type_c = requires(type_t a, type_t b, double d) {
    { a + b } -> std::convertible_to<type_t>;
    { a - b } -> std::convertible_to<type_t>;
    { a * b } -> std::convertible_to<type_t>;
    { a / b } -> std::convertible_to<type_t>;
    { a * d } -> std::convertible_to<type_t>;
    { a / d } -> std::convertible_to<type_t>;
    { static_cast<type_t>(d) };
};

// Verify fundamental types satisfy the concept
static_assert(is_si_type_c<float>);
static_assert(is_si_type_c<double>);
static_assert(is_si_type_c<int>);

} // PKR_SI_NAMESPACE








