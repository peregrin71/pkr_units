#pragma once

#include <ratio>
#include <stdexcept>
#include "dimension.h"
#include "../namespace_config.h"

// Include concepts BEFORE opening namespace to avoid including headers within namespace
#include "../concepts/si_concepts.h"

PKR_UNITS_DETAILS_BEGIN_NAMESPACE

template<PKR_UNITS_NAMESPACE::is_si_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v>
class unit_t
{
public:
    using value_type = type_t;
    using ratio_type = ratio_t;
    // Expose dimension type and value for compile-time access
    struct dimension
    {
        static constexpr PKR_UNITS_NAMESPACE::dimension_t value = dim_v;
    };

    // Explicit constructor from underlying type (general case - requires explicit construction)
    constexpr explicit unit_t(type_t value) noexcept
        requires (dim_v != scalar_dimension)
        : m_value(value)
    {
    }

    // Implicit constructor from underlying type (only for scalar/dimensionless units)
    constexpr unit_t(type_t value) noexcept
        requires (dim_v == scalar_dimension)
        : m_value(value)
    {
    }

    // Implicit conversion to underlying type (only for scalar/dimensionless units)
    constexpr operator type_t() const noexcept
        requires (dim_v == scalar_dimension)
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


// ============================================================================
// Arithmetic Helper Functions
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
        type_t canonical1 = convert_ratio_to<type_t, ratio_t1, std::ratio<1, 1>>(val1);
        type_t canonical2 = convert_ratio_to<type_t, ratio_t2, std::ratio<1, 1>>(val2);
        return canonical1 + canonical2;
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
        type_t canonical1 = convert_ratio_to<type_t, ratio_t1, std::ratio<1, 1>>(val1);
        type_t canonical2 = convert_ratio_to<type_t, ratio_t2, std::ratio<1, 1>>(val2);
        return canonical1 - canonical2;
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
    if (!std::is_constant_evaluated())
    {
        if ((val2 < static_cast<type_t>(0) ? -val2 : val2) == static_cast<type_t>(0))
        {
            throw std::invalid_argument("Division by zero in si_unit::operator/");
        }
    }
    return val1 / val2;
}

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
    // Extract dimension from the base unit_t class
    static constexpr dimension_t value_dimension = T::_base::dimension::value;
};

// Concept for any si_unit type
template<typename T>
concept si_unit_concept = is_si_unit<T>::value;

}  // namespace details
}  // namespace PKR_UNITS_NAMESPACE