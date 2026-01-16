// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <ratio>
#include <stdexcept>
#include <string_view>
#include "dimension.h"
#include "../concepts/si_concepts.h"

namespace si
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

// Helper to get the SI unit type from a dimension
// Todo in derived units we need to add specializations for derived units instead of solving by constexpr if's
// Todo shouldn't si_unit_type meter etc, be derived instead of just being weak type aliases? (this should also help with formatting etc since we can use template specializations directly))
template<dimension_t dim_v>
constexpr si_unit_type get_si_unit_type() noexcept
{
    if constexpr (dim_v == length_v)
        return si_unit_type::meter;
    else if constexpr (
        dim_v.mass == 1 && dim_v.length == 0 && dim_v.time == 0 && dim_v.current == 0 && dim_v.temperature == 0 && dim_v.amount == 0 &&
        dim_v.intensity == 0)
        return si_unit_type::kilogram;
    else if constexpr (
        dim_v.time == 1 && dim_v.length == 0 && dim_v.mass == 0 && dim_v.current == 0 && dim_v.temperature == 0 && dim_v.amount == 0 &&
        dim_v.intensity == 0)
        return si_unit_type::second;
    else if constexpr (
        dim_v.current == 1 && dim_v.length == 0 && dim_v.mass == 0 && dim_v.time == 0 && dim_v.temperature == 0 && dim_v.amount == 0 &&
        dim_v.intensity == 0)
        return si_unit_type::ampere;
    else if constexpr (
        dim_v.temperature == 1 && dim_v.length == 0 && dim_v.mass == 0 && dim_v.time == 0 && dim_v.current == 0 && dim_v.amount == 0 &&
        dim_v.intensity == 0)
        return si_unit_type::kelvin;
    else if constexpr (
        dim_v.amount == 1 && dim_v.length == 0 && dim_v.mass == 0 && dim_v.time == 0 && dim_v.current == 0 && dim_v.temperature == 0 &&
        dim_v.intensity == 0)
        return si_unit_type::mole;
    else if constexpr (
        dim_v.intensity == 1 && dim_v.length == 0 && dim_v.mass == 0 && dim_v.time == 0 && dim_v.current == 0 && dim_v.temperature == 0 &&
        dim_v.amount == 0)
        return si_unit_type::candela;
    else
        return si_unit_type::scalar;
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

    // Add quantities with different ratios, result in left-hand side ratio
    template<typename ratio_u>
    constexpr unit_t<type_t, ratio_t, dim_v> operator+(const unit_t<type_t, ratio_u, dim_v>& other) const noexcept
    {
        // Convert other to this ratio using std::ratio_divide for precision
        // conversion_ratio = ratio_u / ratio_t (exact rational arithmetic)
        using conversion_ratio = std::ratio_divide<ratio_u, ratio_t>;
        
        // Apply conversion carefully: divide first, then multiply to preserve precision
        // This avoids computing large intermediate values like (1e9 * 1) before dividing by 1e9
        type_t converted_value = 
            (other.value() / static_cast<type_t>(conversion_ratio::den)) * 
            static_cast<type_t>(conversion_ratio::num);
        
        type_t result_value = m_value + converted_value;
        return unit_t<type_t, ratio_t, dim_v>(result_value);
    }

    // Subtract quantities with different ratios, result in left-hand side ratio
    template<typename ratio_u>
    constexpr unit_t<type_t, ratio_t, dim_v> operator-(const unit_t<type_t, ratio_u, dim_v>& other) const noexcept
    {
        // Convert other to this ratio using std::ratio_divide for precision
        // conversion_ratio = ratio_u / ratio_t (exact rational arithmetic)
        using conversion_ratio = std::ratio_divide<ratio_u, ratio_t>;
        
        // Apply conversion carefully: divide first, then multiply to preserve precision
        // This avoids computing large intermediate values like (1e9 * 1) before dividing by 1e9
        type_t converted_value = 
            (other.value() / static_cast<type_t>(conversion_ratio::den)) * 
            static_cast<type_t>(conversion_ratio::num);
        
        type_t result_value = m_value - converted_value;
        return unit_t<type_t, ratio_t, dim_v>(result_value);
    }

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
        return unit_t<type_t, combined_ratio, combined_dim_v>(result_value);
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
        return unit_t<type_t, combined_ratio, combined_dim_v>(result_value);
    }

    // Multiply by scalar
    constexpr unit_t<type_t, ratio_t, dim_v> operator*(std::same_as<type_t> auto scalar) const noexcept
    {
        return unit_t<type_t, ratio_t, dim_v>(m_value * scalar);
    }

    constexpr unit_t<type_t, ratio_t, dim_v> operator/(std::same_as<type_t> auto scalar) const
    {
        if ((scalar < static_cast<type_t>(0) ? -scalar : scalar) == static_cast<type_t>(0))
        {
            throw std::invalid_argument("Division by zero in si_unit::operator/");
        }
        return unit_t<type_t, ratio_t, dim_v>(m_value / scalar);
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

template<typename type_t, typename ratio_t, dimension_t dim_v>
struct is_si_unit<unit_t<type_t, ratio_t, dim_v>> : std::true_type
{
    static constexpr bool value = true;
    using value_type = type_t;
    using ratio_type = ratio_t;
    static constexpr dimension_t value_dimension = dim_v;
};

// Concept for any si_unit type
template<typename T>
concept si_unit_type = is_si_unit<T>::value;

} // namespace si






