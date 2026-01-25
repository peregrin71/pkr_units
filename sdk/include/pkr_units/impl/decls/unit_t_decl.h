#pragma once

#include <ratio>
#include <stdexcept>
#include "../dimension.h"
#include <pkr_units/impl/namespace_config.h>

// Include concepts BEFORE opening namespace to avoid including headers within namespace
#include "../concepts/unit_concepts.h"

PKR_UNITS_DETAILS_BEGIN_NAMESPACE

// Forward declaration of named_unit_type_t
template<PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v>
struct named_unit_type_t;

// ============================================================================
// Helper: convert a value from one ratio to another
template<typename type_t, typename ratio_from, typename ratio_to>
constexpr type_t convert_ratio_to(type_t value) noexcept
{
    using conversion = std::ratio_divide<ratio_from, ratio_to>;
    return (value / static_cast<type_t>(conversion::den)) * 
           static_cast<type_t>(conversion::num);
}

// Helper: add two values with different ratios, result in canonical ratio (1/1)
template<typename type_t, typename ratio_t1, typename ratio_t2>
constexpr type_t add_canonical(type_t val1, type_t val2) noexcept
{
    if constexpr (std::is_same_v<ratio_t1, ratio_t2>)
    {
        return val1 + val2;
    }
    else
    {
        // Convert both to canonical ratio (1/1) and add
        type_t canonical_val1 = convert_ratio_to<type_t, ratio_t1, std::ratio<1, 1>>(val1);
        type_t canonical_val2 = convert_ratio_to<type_t, ratio_t2, std::ratio<1, 1>>(val2);
        return canonical_val1 + canonical_val2;
    }
}

// Helper: subtract two values with different ratios, result in canonical ratio (1/1)
template<typename type_t, typename ratio_t1, typename ratio_t2>
constexpr type_t subtract_canonical(type_t val1, type_t val2) noexcept
{
    if constexpr (std::is_same_v<ratio_t1, ratio_t2>)
    {
        return val1 - val2;
    }
    else
    {
        // Convert both to canonical ratio (1/1) and subtract
        type_t canonical_val1 = convert_ratio_to<type_t, ratio_t1, std::ratio<1, 1>>(val1);
        type_t canonical_val2 = convert_ratio_to<type_t, ratio_t2, std::ratio<1, 1>>(val2);
        return canonical_val1 - canonical_val2;
    }
}

// Helper: multiply two values
template<typename type_t>
constexpr type_t multiply_values(type_t val1, type_t val2) noexcept
{
    return val1 * val2;
}

// Helper: divide two values
template<typename type_t>
constexpr type_t divide_values(type_t val1, type_t val2)
{
    // Division by zero check: at runtime throw, at compile-time assert
    if (!std::is_constant_evaluated())
    {
        if ((val2 < static_cast<type_t>(0) ? -val2 : val2) == static_cast<type_t>(0))
        {
            throw std::invalid_argument("Division by zero");
        }
    }
    return val1 / val2;
}

template<PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v>
class unit_t
{
public:
    using value_type = type_t;
    using ratio_type = ratio_t;
    using dimension_type = std::integral_constant<PKR_UNITS_NAMESPACE::dimension_t, dim_v>; // Add this typedef
    // Expose dimension type and value for compile-time access
    struct dimension
    {
        static constexpr PKR_UNITS_NAMESPACE::dimension_t value = dim_v;
    };

    // Allow construction from underlying type
    explicit constexpr unit_t(type_t value) noexcept
         : m_value(value)
    {
    }

    // Allow construction from another unit with same dimension but different ratio
    template<typename other_ratio_t>
    constexpr unit_t(const unit_t<type_t, other_ratio_t, dim_v>& other) noexcept
         : m_value(convert_ratio_to<type_t, other_ratio_t, ratio_t>(other.value()))
    {
    }

    // make sure type is default copyable and movable
    constexpr unit_t(const unit_t&) noexcept = default;
    constexpr unit_t(unit_t&&) noexcept = default;
    constexpr unit_t& operator=(const unit_t&) noexcept = default;
    constexpr unit_t& operator=(unit_t&&) noexcept = default;

    // Multiply by another si_unit quantity (combine dimensions and ratios)
    template<typename ratio_u, dimension_t dim_u>
    constexpr auto operator*(const details::unit_t<type_t, ratio_u, dim_u>& other) const noexcept
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
            .intensity = dim_v.intensity + dim_u.intensity,
            .angle = dim_v.angle + dim_u.angle};

        type_t result_value = m_value * other.value();
        return details::unit_t<type_t, combined_ratio, combined_dim_v>{result_value};
    }

    // Divide by another si_unit quantity (combine dimensions and ratios)
    template<typename ratio_u, dimension_t dim_u>
    constexpr auto operator/(const details::unit_t<type_t, ratio_u, dim_u>& other) const
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
            .intensity = dim_v.intensity - dim_u.intensity,
            .angle = dim_v.angle - dim_u.angle};

        type_t result_value = m_value / other.value();
        return details::unit_t<type_t, combined_ratio, combined_dim_v>{result_value};
    }

    // Multiply by scalar - returns the most derived unit type
    constexpr auto operator*(std::same_as<type_t> auto scalar) const noexcept
    {
        using result_type = typename named_unit_type_t<type_t, ratio_t, dim_v>::type;
        return result_type{m_value * scalar};
    }

    // Divide by scalar - returns the most derived unit type
    constexpr auto operator/(std::same_as<type_t> auto scalar) const
    {
        if ((scalar < static_cast<type_t>(0) ? -scalar : scalar) == static_cast<type_t>(0))
        {
            throw std::invalid_argument("Division by zero in si_unit::operator/");
        }
        using result_type = typename named_unit_type_t<type_t, ratio_t, dim_v>::type;
        return result_type{m_value / scalar};
    }

    // Compound assignment operators
    constexpr unit_t& operator+=(const unit_t& other) noexcept
    {
        m_value += other.m_value;
        return *this;
    }

    constexpr unit_t& operator-=(const unit_t& other) noexcept
    {
        m_value -= other.m_value;
        return *this;
    }

    constexpr unit_t& operator*=(std::same_as<type_t> auto scalar) noexcept
    {
        m_value *= scalar;
        return *this;
    }

    constexpr unit_t& operator/=(std::same_as<type_t> auto scalar)
    {
        if ((scalar < static_cast<type_t>(0) ? -scalar : scalar) == static_cast<type_t>(0))
        {
            throw std::invalid_argument("Division by zero in si_unit::operator/=");
        }
        m_value /= scalar;
        return *this;
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

    // Convert to SI base units with canonical ratio (1/1)
    // Returns the most derived unit type in canonical SI form
    constexpr auto to_si() const noexcept
    {
        // Convert value from current ratio to canonical ratio (1/1)
        type_t canonical_value = convert_ratio_to<type_t, ratio_t, std::ratio<1, 1>>(m_value);
        
        // Return most derived unit type with canonical ratio and same dimensions
        using canonical_unit = typename named_unit_type_t<type_t, std::ratio<1, 1>, dim_v>::type;
        return canonical_unit{canonical_value};
    }

    // Return a normalized unit_t with canonical ratio (1/1) for dimensional analysis
    constexpr auto normalized() const noexcept
    {
        // Convert value from current ratio to canonical ratio (1/1)
        type_t canonical_value = convert_ratio_to<type_t, ratio_t, std::ratio<1, 1>>(m_value);
        
        // Return raw unit_t with canonical ratio and same dimensions
        return details::unit_t<type_t, std::ratio<1, 1>, dim_v>{canonical_value};
    }

private:
    type_t m_value;
};

// ============================================================================
// Most derived unit_type deduction helpers

template<PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v>
struct named_unit_type_t
{
    using type = details::unit_t<type_t, ratio_t, dim_v>;
};

// and now we can specialize for derived types everywhere like this
// and we must place these specializations close to the derived unit type definitions.
// template<>
// struct named_unit_type_t<double, std::ratio<1, 1000>, PKR_UNITS_NAMESPACE::dimension_t{0, 1, 0, 0, 0, 0, 0}>
// {
//     using type = PKR_UNITS_NAMESPACE::gram_t;
// };


// ============================================================================
// Type Traits for Unit Detection
// ============================================================================
// Helper to check if a type is an pkr_unit and extract its components
template<typename T>
struct is_pkr_unit : std::false_type
{
};

// Specialization for direct unit_t types
template<typename type_t, typename ratio_t, dimension_t dim_v>
struct is_pkr_unit<details::unit_t<type_t, ratio_t, dim_v>> : std::true_type
{
    static constexpr bool value = true;
    using value_type = type_t;
    using ratio_type = ratio_t;
    using most_derived_type = details::unit_t<type_t, ratio_t, dim_v>;
    static constexpr dimension_t value_dimension = dim_v;
};

// Specialization for derived types that inherit from unit_t
// (e.g., struct meter : public details::unit_t<...>)
template<typename T>
requires std::is_base_of_v<typename T::_base, T>
struct is_pkr_unit<T> : std::true_type
{
    static constexpr bool value = true;
    using value_type = typename T::_base::value_type;
    using ratio_type = typename T::_base::ratio_type;
    using most_derived_type = T;
    // Extract dimension from the base unit_t class
    static constexpr dimension_t value_dimension = T::_base::dimension::value;
};

// Specialization for const references
template<typename T>
struct is_pkr_unit<const T&> : is_pkr_unit<T>
{
};

// Specialization for references
template<typename T>
struct is_pkr_unit<T&> : is_pkr_unit<T>
{
};

// Specialization for const
template<typename T>
struct is_pkr_unit<const T> : is_pkr_unit<T>
{
};

// Concept for any pkr_unit type
template<typename T>
concept pkr_unit_concept = is_pkr_unit<T>::value;

}  // namespace details
}  // namespace PKR_UNITS_NAMESPACE





