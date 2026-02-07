#pragma once

#include <complex>
#include <ratio>
#include <stdexcept>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Concept for types that can represent unit quantity values
// Explicitly allows:
//   - Signed integral types only (int, long, int64_t, etc.)
//   - All floating point types (float, double, long double)
//   - __float128 if available (GCC/Clang extension)
//   - Complex types (std::complex<float>, std::complex<double>)
template <typename type_t>
concept is_unit_value_type_c = (std::is_integral_v<type_t> && !std::same_as<type_t, bool> && std::is_signed_v<type_t>) || std::is_floating_point_v<type_t> ||
#if defined(__SIZEOF_FLOAT128__) && !defined(_MSC_VER)
                               std::same_as<type_t, __float128> ||
#endif
                               std::same_as<type_t, std::complex<float>> || std::same_as<type_t, std::complex<double>>;

// Verify fundamental types satisfy the concept
static_assert(is_unit_value_type_c<float>);
static_assert(is_unit_value_type_c<double>);
static_assert(is_unit_value_type_c<std::complex<double>>);
static_assert(is_unit_value_type_c<int>);
static_assert(is_unit_value_type_c<long long>);
static_assert(!is_unit_value_type_c<bool>);

namespace details
{

// Forward declaration of derived_unit_type_t
template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v>
struct derived_unit_type_t;

// ============================================================================
// Helper: convert a value from one ratio to another
template <typename type_t, typename ratio_from, typename ratio_to>
constexpr type_t convert_ratio_to(type_t value) noexcept
{
    using conversion = std::ratio_divide<ratio_from, ratio_to>;
    return (value / static_cast<type_t>(conversion::den)) * static_cast<type_t>(conversion::num);
}

// Helper: multiply two values
template <typename type_t>
constexpr type_t multiply_values(type_t val1, type_t val2) noexcept
{
    return val1 * val2;
}

// Helper: divide two values
template <typename type_t>
constexpr type_t divide_values(type_t val1, type_t val2) noexcept
{
    return val1 / val2;
}

// ============================================================================
// Helper utilities for complex number support

// Concept: type is std::complex<float> or std::complex<double>
template <typename T>
concept complex_type_c = (std::same_as<T, std::complex<float>> || std::same_as<T, std::complex<double>>);

// Helper to extract the underlying real type from std::complex<T>
template <typename T>
struct complex_underlying_type
{
};

template <typename T>
struct complex_underlying_type<std::complex<T>>
{
    using type = T;
};

template <typename T>
using complex_underlying_type_t = typename complex_underlying_type<T>::type;

template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v>
class unit_t
{
public:
    using value_type = type_t;
    using ratio_type = ratio_t;
    using dimension_type = std::integral_constant<PKR_UNITS_NAMESPACE::dimension_t, dim_v>;

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
    template <typename other_ratio_t>
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
    template <typename ratio_u, dimension_t dim_u>
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
        return typename details::derived_unit_type_t<type_t, combined_ratio, combined_dim_v>::type{result_value};
    }

    // Divide by another si_unit quantity (combine dimensions and ratios)
    template <typename ratio_u, dimension_t dim_u>
    constexpr auto operator/(const details::unit_t<type_t, ratio_u, dim_u>& other) const
    {
        // Division by zero check: at runtime throw, at compile-time assert
        if (!std::is_constant_evaluated())
        {
            if constexpr (std::is_arithmetic_v<type_t>)
            {
                if ((other.value() < static_cast<type_t>(0) ? -other.value() : other.value()) == static_cast<type_t>(0))
                {
                    throw std::invalid_argument("Division by zero in si_unit::operator/");
                }
            }
            else
            {
                // For complex value types, check magnitude instead of direct comparison
                using magnitude_type = decltype(std::abs(other.value()));
                if (std::abs(other.value()) == static_cast<magnitude_type>(0))
                {
                    throw std::invalid_argument("Division by zero in si_unit::operator/");
                }
            }
        }

        // Combine ratios: (this_num/this_den) / (other_num/other_den)
        using combined_ratio = std::ratio_divide<ratio_t, ratio_u>;

        // Combine dimensions: subtract all exponents
        constexpr dimension_t combined_dim_v{
            dim_v.length - dim_u.length,
            dim_v.mass - dim_u.mass,
            dim_v.time - dim_u.time,
            dim_v.current - dim_u.current,
            dim_v.temperature - dim_u.temperature,
            dim_v.amount - dim_u.amount,
            dim_v.intensity - dim_u.intensity,
            dim_v.angle - dim_u.angle};

        type_t result_value = m_value / other.value();
        return typename details::derived_unit_type_t<type_t, combined_ratio, combined_dim_v>::type{result_value};
    }

    // ============================================================================
    // Additional member utilities

    constexpr auto operator*(std::same_as<type_t> auto scalar) const noexcept
    {
        using result_type = typename details::derived_unit_type_t<type_t, ratio_t, dim_v>::type;
        return result_type{m_value * scalar};
    }

    constexpr auto operator/(std::same_as<type_t> auto scalar) const noexcept
    {
        using result_type = typename details::derived_unit_type_t<type_t, ratio_t, dim_v>::type;
        return result_type{m_value / scalar};
    }

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

    constexpr unit_t& operator/=(std::same_as<type_t> auto scalar) noexcept
    {
        m_value /= scalar;
        return *this;
    }

    constexpr type_t value() const noexcept
    {
        return m_value;
    }

    constexpr type_t operator*() const noexcept
    {
        return m_value;
    }

    constexpr auto to_si() const noexcept
    {
        type_t canonical_value = convert_ratio_to<type_t, ratio_t, std::ratio<1, 1>>(m_value);
        using canonical_unit = typename derived_unit_type_t<type_t, std::ratio<1, 1>, dim_v>::type;
        return canonical_unit{canonical_value};
    }

    constexpr auto in_base_si_units() const noexcept
    {
        type_t canonical_value = convert_ratio_to<type_t, ratio_t, std::ratio<1, 1>>(m_value);
        return details::unit_t<type_t, std::ratio<1, 1>, dim_v>{canonical_value};
    }

    // Member function to get magnitude (only available for complex value types)
    // Returns the same unit type but with real-valued magnitude
    constexpr auto magnitude() const noexcept
        requires complex_type_c<type_t>
    {
        using real_type = complex_underlying_type_t<type_t>;
        real_type mag_value = static_cast<real_type>(std::abs(m_value));
        using result_unit = typename derived_unit_type_t<real_type, ratio_t, dim_v>::type;
        return result_unit{mag_value};
    }

    // Member function to get phase angle in radians (only available for complex value types)
    // Returns a unit with angle dimension, which resolves to radian_t<real_type>
    // Result is in range [-π, π] radians
    constexpr auto phase() const noexcept
        requires complex_type_c<type_t>
    {
        using real_type = complex_underlying_type_t<type_t>;
        real_type phase_value = static_cast<real_type>(std::arg(m_value));
        using result_unit = typename derived_unit_type_t<real_type, std::ratio<1, 1>, angle_dimension>::type;
        return result_unit{phase_value};
    }

private:
    type_t m_value;
};

// ============================================================================
// Most derived unit_type deduction helpers

template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v>
struct derived_unit_type_t
{
    using type = details::unit_t<type_t, ratio_t, dim_v>;
};

// ============================================================================
// Type Traits for Unit Detection
// ============================================================================
// Helper to check if a type is an pkr_unit and extract its components
template <typename T>
struct is_pkr_unit : std::false_type
{
};

// Specialization for direct unit_t types
template <typename type_t, typename ratio_t, dimension_t dim_v>
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
template <typename T>
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
template <typename T>
struct is_pkr_unit<const T&> : is_pkr_unit<T>
{
};

// Specialization for references
template <typename T>
struct is_pkr_unit<T&> : is_pkr_unit<T>
{
};

// Specialization for const
template <typename T>
struct is_pkr_unit<const T> : is_pkr_unit<T>
{
};

} // namespace details

// ============================================================================
// Unit Type Aliases for Common Dimensions
// ============================================================================

// SI Base Units
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length_unit_t = details::unit_t<type_t, ratio_t, length_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_unit_t = details::unit_t<type_t, ratio_t, mass_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using time_unit_t = details::unit_t<type_t, ratio_t, time_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using current_unit_t = details::unit_t<type_t, ratio_t, current_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using temperature_unit_t = details::unit_t<type_t, ratio_t, temperature_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using amount_unit_t = details::unit_t<type_t, ratio_t, amount_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using intensity_unit_t = details::unit_t<type_t, ratio_t, intensity_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using angle_unit_t = details::unit_t<type_t, ratio_t, angle_dimension>;

// Derived Quantities (Common)
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using area_unit_t = details::unit_t<type_t, ratio_t, area_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using volume_unit_t = details::unit_t<type_t, ratio_t, volume_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using acceleration_unit_t = details::unit_t<type_t, ratio_t, acceleration_v>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using velocity_unit_t = details::unit_t<type_t, ratio_t, velocity_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using density_unit_t = details::unit_t<type_t, ratio_t, density_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using dynamic_viscosity_unit_t = details::unit_t<type_t, ratio_t, dynamic_viscosity_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using kinematic_viscosity_unit_t = details::unit_t<type_t, ratio_t, kinematic_viscosity_dimension>;

// Concentration Types
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_concentration_unit_t = details::unit_t<type_t, ratio_t, mass_concentration_v>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using molar_concentration_unit_t = details::unit_t<type_t, ratio_t, molar_concentration_v>;

// Other Derived Quantities
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using josephson_unit_t = details::unit_t<type_t, ratio_t, josephson_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using solid_angle_unit_t = details::unit_t<type_t, ratio_t, solid_angle_dimension>;

} // namespace PKR_UNITS_NAMESPACE
