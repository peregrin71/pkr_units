#pragma once

#include <ratio>
#include <stdexcept>
#include <string_view>
#include "dimension.h"
#include "../namespace_config.h"

// Include concepts BEFORE opening namespace to avoid including headers within namespace
#include "../concepts/si_concepts.h"

PKR_SI_DETAILS_BEGIN_NAMESPACE

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

// ============================================================================
inline constexpr dimension_t length_dimension{.length = 1};
inline constexpr dimension_t mass_dimension{.mass = 1};
inline constexpr dimension_t time_dimension{.time = 1};
inline constexpr dimension_t current_dimension{.current = 1};
inline constexpr dimension_t temperature_dimension{.temperature = 1};
inline constexpr dimension_t amount_dimension{.amount = 1};
inline constexpr dimension_t intensity_dimension{.intensity = 1};
inline constexpr dimension_t scalar_dimension{};  // dimensionless

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

template<si::is_si_type_c type_t, typename ratio_t, dimension_t dim_v>
class unit_t
{
public:
    using value_type = type_t;
    using ratio_type = ratio_t;
    // Expose dimension type and value for compile-time access
    struct dimension
    {
        static constexpr dimension_t value = dim_v;
    };

    // Unit type identification for formatting
    static constexpr si_unit_type unit_type = get_si_unit_type<dim_v>();

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

PKR_SI_DETAILS_END_NAMESPACE

// ============================================================================
// Operators in main si namespace
// ============================================================================
PKR_SI_BEGIN_NAMESPACE
{

// Addition operator
template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr T1 operator+(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    constexpr auto dim = details::is_si_unit<T1>::value_dimension;
    using result_ratio = typename details::is_si_unit<T1>::ratio_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    
    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        return T1{lhs.value() + rhs.value()};
    }
    else
    {
        value_type canonical_sum = details::add_canonical<value_type, ratio1, ratio2>(
            lhs.value(), rhs.value()
        );
        value_type converted = details::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
            canonical_sum
        );
        return T1{converted};
    }
}

// Named add function
template<details::si_unit_type ResultType, details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension &&
          details::is_si_unit<T1>::value_dimension == details::is_si_unit<ResultType>::value_dimension)
constexpr auto add(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<ResultType>::value_type;
    using result_ratio = typename details::is_si_unit<ResultType>::ratio_type;
    constexpr auto dim = details::is_si_unit<ResultType>::value_dimension;
    
    value_type canonical_sum = details::add_canonical<value_type, 
                                                     typename details::is_si_unit<T1>::ratio_type,
                                                     typename details::is_si_unit<T2>::ratio_type>(
        lhs.value(), rhs.value()
    );
    
    value_type converted = details::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
        canonical_sum
    );
    
    return details::unit_t<value_type, result_ratio, dim>{converted};
}

// Subtraction operator
template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr T1 operator-(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    constexpr auto dim = details::is_si_unit<T1>::value_dimension;
    using result_ratio = typename details::is_si_unit<T1>::ratio_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    
    if constexpr (std::is_same_v<ratio1, ratio2>)
    {
        return T1{lhs.value() - rhs.value()};
    }
    else
    {
        value_type canonical_diff = details::subtract_canonical<value_type, ratio1, ratio2>(
            lhs.value(), rhs.value()
        );
        value_type converted = details::convert_ratio_to<value_type, std::ratio<1, 1>, result_ratio>(
            canonical_diff
        );
        return T1{converted};
    }
}

// Multiplication operators
template<details::si_unit_type T1, details::si_unit_type T2>
constexpr auto operator*(const T1& lhs, const T2& rhs) noexcept
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_si_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_si_unit<T2>::value_dimension;
    
    using combined_ratio = std::conditional_t<
        std::is_same_v<ratio1, std::ratio<1, 1>>,
        ratio2,
        std::conditional_t<
            std::is_same_v<ratio2, std::ratio<1, 1>>,
            ratio1,
            std::ratio_multiply<ratio1, ratio2>
        >
    >;
    
    constexpr details::dimension_t combined_dim{
        .length = dim1.length + dim2.length,
        .mass = dim1.mass + dim2.mass,
        .time = dim1.time + dim2.time,
        .current = dim1.current + dim2.current,
        .temperature = dim1.temperature + dim2.temperature,
        .amount = dim1.amount + dim2.amount,
        .intensity = dim1.intensity + dim2.intensity};
    
    using result_type = details::unit_t<value_type, combined_ratio, combined_dim>;
    return result_type{details::multiply_values(lhs.value(), rhs.value())};
}

// Multiplication by scalar
template<typename T, details::si_unit_type U>
requires (!details::is_si_unit<T>::value && details::is_si_unit<U>::value)
constexpr auto operator*(const T& scalar, const U& rhs) noexcept
{
    using value_type = typename details::is_si_unit<U>::value_type;
    using ratio_type = typename details::is_si_unit<U>::ratio_type;
    constexpr auto dim = details::is_si_unit<U>::value_dimension;
    
    return details::unit_t<value_type, ratio_type, dim>{scalar * rhs.value()};
}

template<details::si_unit_type T, typename U>
requires (details::is_si_unit<T>::value && !details::is_si_unit<U>::value)
constexpr auto operator*(const T& lhs, const U& scalar) noexcept
{
    using value_type = typename details::is_si_unit<T>::value_type;
    using ratio_type = typename details::is_si_unit<T>::ratio_type;
    constexpr auto dim = details::is_si_unit<T>::value_dimension;
    
    return details::unit_t<value_type, ratio_type, dim>{scalar * lhs.value()};
}

// Division operator
template<details::si_unit_type T1, details::si_unit_type T2>
constexpr auto operator/(const T1& lhs, const T2& rhs)
{
    using value_type = typename details::is_si_unit<T1>::value_type;
    using ratio1 = typename details::is_si_unit<T1>::ratio_type;
    using ratio2 = typename details::is_si_unit<T2>::ratio_type;
    constexpr auto dim1 = details::is_si_unit<T1>::value_dimension;
    constexpr auto dim2 = details::is_si_unit<T2>::value_dimension;
    
    using combined_ratio = std::conditional_t<
        std::is_same_v<ratio2, std::ratio<1, 1>>,
        ratio1,
        std::conditional_t<
            std::is_same_v<ratio1, ratio2>,
            std::ratio<1, 1>,
            std::ratio_divide<ratio1, ratio2>
        >
    >;
    
    constexpr details::dimension_t combined_dim{
        .length = dim1.length - dim2.length,
        .mass = dim1.mass - dim2.mass,
        .time = dim1.time - dim2.time,
        .current = dim1.current - dim2.current,
        .temperature = dim1.temperature - dim2.temperature,
        .amount = dim1.amount - dim2.amount,
        .intensity = dim1.intensity - dim2.intensity};
    
    using result_type = details::unit_t<value_type, combined_ratio, combined_dim>;
    return result_type{details::divide_values(lhs.value(), rhs.value())};
}

// Comparison operators
template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value &&
          details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr bool operator==(const T1& lhs, const T2& rhs) noexcept
{
    using lhs_ratio = typename details::is_si_unit<T1>::ratio_type;
    using rhs_ratio = typename details::is_si_unit<T2>::ratio_type;
    using canonical_value_lhs = double;
    
    if constexpr (std::ratio_equal_v<lhs_ratio, rhs_ratio>)
    {
        return lhs.value() == rhs.value();
    }
    else
    {
        auto to_canonical = [](const auto& unit) {
            using ratio_type = typename details::is_si_unit<decltype(unit)>::ratio_type;
            return static_cast<double>(unit.value()) * 
                   (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
        };
        return to_canonical(lhs) == to_canonical(rhs);
    }
}

template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value &&
          details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr bool operator!=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs == rhs);
}

template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value &&
          details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr bool operator<(const T1& lhs, const T2& rhs) noexcept
{
    auto to_canonical = [](const auto& unit) {
        using ratio_type = typename details::is_si_unit<decltype(unit)>::ratio_type;
        return static_cast<double>(unit.value()) * 
               (static_cast<double>(ratio_type::num) / static_cast<double>(ratio_type::den));
    };
    return to_canonical(lhs) < to_canonical(rhs);
}

template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value &&
          details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr bool operator<=(const T1& lhs, const T2& rhs) noexcept
{
    return lhs < rhs || lhs == rhs;
}

template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value &&
          details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr bool operator>(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs <= rhs);
}

template<details::si_unit_type T1, details::si_unit_type T2>
requires (details::is_si_unit<T1>::value && details::is_si_unit<T2>::value &&
          details::is_si_unit<T1>::value_dimension == details::is_si_unit<T2>::value_dimension)
constexpr bool operator>=(const T1& lhs, const T2& rhs) noexcept
{
    return !(lhs < rhs);
}

PKR_SI_NAMESPACE_END










