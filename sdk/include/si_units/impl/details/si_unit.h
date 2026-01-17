#pragma once

#include <ratio>
#include <stdexcept>
#include <string_view>
#include "dimension.h"
#include "../concepts/si_concepts.h"
#include "../../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{

// Portable constexpr function that mimics std::unreachable() for C++20
// Indicates code path that should never be reached
constexpr void unreachable() noexcept
{
#if defined(__cpp_lib_unreachable)
    std::unreachable();
#elif defined(__GNUC__)
    __builtin_unreachable();
#elif defined(_MSC_VER)
    __assume(false);
#else
    // Fallback: unreachable but still valid in constexpr context
#endif
}

// SI base unit enumeration for identifying the primary unit
enum class si_unit_type
{
    meter,        // Length (m)
    kilogram,     // Mass (kg)
    second,       // Time (s)
    ampere,       // Electric current (A)
    kelvin,       // Temperature (K)
    mole,         // Amount of substance (mol)
    candela,      // Luminous intensity (cd)
    scalar        // For dimensionless quantities
};

// Helper implementation to get the SI unit type from a dimension
// Uses template specialization for faster compilation and better extensibility
template<dimension_t dim_v>
struct si_unit_type_impl
{
    static constexpr si_unit_type value = si_unit_type::scalar;
};

// Specializations for base SI units
template<>
struct si_unit_type_impl<length_dimension>
{
    static constexpr si_unit_type value = si_unit_type::meter;
};

template<>
struct si_unit_type_impl<mass_dimension>
{
    static constexpr si_unit_type value = si_unit_type::kilogram;
};

template<>
struct si_unit_type_impl<time_dimension>
{
    static constexpr si_unit_type value = si_unit_type::second;
};

template<>
struct si_unit_type_impl<current_dimension>
{
    static constexpr si_unit_type value = si_unit_type::ampere;
};

template<>
struct si_unit_type_impl<temperature_dimension>
{
    static constexpr si_unit_type value = si_unit_type::kelvin;
};

template<>
struct si_unit_type_impl<amount_dimension>
{
    static constexpr si_unit_type value = si_unit_type::mole;
};

template<>
struct si_unit_type_impl<intensity_dimension>
{
    static constexpr si_unit_type value = si_unit_type::candela;
};

// Primary function template to get the SI unit type from a dimension
// Dispatches to specializations for faster compilation
template<dimension_t dim_v>
constexpr si_unit_type get_si_unit_type() noexcept
{
    return si_unit_type_impl<dim_v>::value;
}

// Helper to get the SI unit symbol, TOOD move to seperate formatting header
constexpr std::string_view get_si_unit_symbol(si_unit_type unit) noexcept
{
    switch (unit)
    {
        case si_unit_type::meter:
            return "m";
        case si_unit_type::kilogram:
            return "kg";
        case si_unit_type::second:
            return "s";
        case si_unit_type::ampere:
            return "A";
        case si_unit_type::kelvin:
            return "K";
        case si_unit_type::mole:
            return "mol";
        case si_unit_type::candela:
            return "cd";
        case si_unit_type::scalar:
            return "";
    }
    return "";
}

template<si::is_si_type_c type_t, typename ratio_t, dimension_t dim_v>
class unit_t
{
public:
    using value_type = type_t;
    using ratio_type = ratio_t;

    // Expose dimension type and value for compile-time access
    struct dimension
    {
        static constexpr ::si::dimension_t value = dim_v;
    };

    // Unit type identification for formatting
    static constexpr si_unit_type unit_type = get_si_unit_type<dim_v>();

    // Explicit constructor from underlying type (general case - requires explicit construction)
    constexpr explicit unit_t(type_t value) noexcept
        requires (dim_v != scalar)
        : m_value(value)
    {
    }

    // Implicit constructor from underlying type (only for scalar/dimensionless units)
    constexpr unit_t(type_t value) noexcept
        requires (dim_v == scalar)
        : m_value(value)
    {
    }

    // Implicit conversion to underlying type (only for scalar/dimensionless units)
    constexpr operator type_t() const noexcept
        requires (dim_v == scalar)
    {
        return m_value;
    }

    // make sure type is default copyable and movable
    constexpr unit_t(const unit_t&) noexcept = default;
    constexpr unit_t(unit_t&&) noexcept = default;
    constexpr unit_t& operator=(const unit_t&) noexcept = default;
    constexpr unit_t& operator=(unit_t&&) noexcept = default;

    // Multiply by another si_unit quantity (combine dimensions and ratios)
    template<typename ratio_u, dimension_t dim_u>
    constexpr auto operator*(const unit_t<type_t, ratio_u, dim_u>& other) const noexcept
    {
        // Combine ratios: (this_num/this_den) * (other_num/other_den)
        using combined_ratio = std::ratio_multiply<ratio_t, ratio_u>;

        // Combine dimensions: add all exponents
        constexpr dimension_t combined_dim_v{
            .length = dim_v.length + dim_u.length,
            .mass = dim_v.mass + dim_u.mass,
            .time = dim_v.time + dim_u.time,
            .current = dim_v.current + dim_u.current,
            .temperature = dim_v.temperature + dim_u.temperature,
            .amount = dim_v.amount + dim_u.amount,
            .intensity = dim_v.intensity + dim_u.intensity};

        type_t result_value = m_value * other.value();
        return unit_t<type_t, combined_ratio, combined_dim_v>{result_value};
    }

    // Divide by another si_unit quantity (combine dimensions and ratios)
    template<typename ratio_u, dimension_t dim_u>
    constexpr auto operator/(const unit_t<type_t, ratio_u, dim_u>& other) const
    {
        // Division by zero check: at runtime throw, at compile-time assert
        if (!std::is_constant_evaluated())
        {
            if ((other.value() < static_cast<type_t>(0) ? -other.value() : other.value()) == static_cast<type_t>(0))
            {
                throw std::invalid_argument("Division by zero in si_unit::operator/");
            }
        }

        // Combine ratios: (this_num/this_den) / (other_num/other_den)
        using combined_ratio = std::ratio_divide<ratio_t, ratio_u>;

        // Combine dimensions: subtract all exponents
        constexpr dimension_t combined_dim_v{
            .length = dim_v.length - dim_u.length,
            .mass = dim_v.mass - dim_u.mass,
            .time = dim_v.time - dim_u.time,
            .current = dim_v.current - dim_u.current,
            .temperature = dim_v.temperature - dim_u.temperature,
            .amount = dim_v.amount - dim_u.amount,
            .intensity = dim_v.intensity - dim_u.intensity};

        type_t result_value = m_value / other.value();
        return unit_t<type_t, combined_ratio, combined_dim_v>{result_value};
    }

    // Multiply by scalar
    constexpr unit_t<type_t, ratio_t, dim_v> operator*(std::same_as<type_t> auto scalar) const noexcept
    {
        return unit_t<type_t, ratio_t, dim_v>{m_value * scalar};
    }

    constexpr unit_t<type_t, ratio_t, dim_v> operator/(std::same_as<type_t> auto scalar) const
    {
        if ((scalar < static_cast<type_t>(0) ? -scalar : scalar) == static_cast<type_t>(0))
        {
            throw std::invalid_argument("Division by zero in si_unit::operator/");
        }
        return unit_t<type_t, ratio_t, dim_v>{m_value / scalar};
    }

    // Get raw value
    constexpr type_t value() const noexcept
    {
        return m_value;
    }

    // Dereference operator to get the value (pointer-like interface)
    constexpr type_t operator*() const noexcept
    {
        return m_value;
    }

private:
    type_t m_value;
};

// Helper to check if a type is an si_unit and extract its components
template<typename T>
struct is_si_unit : std::false_type
{
};

// Specialization for direct unit_t types
template<typename type_t, typename ratio_t, dimension_t dim_v>
struct is_si_unit<unit_t<type_t, ratio_t, dim_v>> : std::true_type
{
    static constexpr bool value = true;
    using value_type = type_t;
    using ratio_type = ratio_t;
    static constexpr dimension_t value_dimension = dim_v;
};

// Specialization for derived types that inherit from unit_t
// (e.g., struct meter : public unit_t<...>)
template<typename T>
requires std::is_base_of_v<typename T::_base, T>
struct is_si_unit<T> : std::true_type
{
    static constexpr bool value = true;
    using value_type = typename T::_base::value_type;
    using ratio_type = typename T::_base::ratio_type;
    static constexpr dimension_t value_dimension = T::_base::dimension::value;
};

// Concept for any si_unit type
template<typename T>
concept si_unit_type = is_si_unit<T>::value;

// Include arithmetic operations
#include "add_si_units.h"
#include "subtract_si_units.h"
#include "multiply_si_units.h"
#include "divide_si_units.h"
#include "compare_si_units.h"

PKR_SI_NAMESPACE_END








