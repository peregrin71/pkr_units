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
//
// Unit library templates frequently take a `tag_t` parameter which is
// expected to be an empty struct used for disambiguation (or
// `details::untagged_t` when no tag is present).  A small concept makes
// declarations clearer than raw `typename` in places where a tag type is
// required.

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

// ============================================================================
// Helper: convert a value from one ratio to another
template <typename type_t, typename ratio_from, typename ratio_to>
constexpr type_t convert_ratio_to(type_t value) noexcept
{
    using conversion = std::ratio_divide<ratio_from, ratio_to>;
    return (value / static_cast<type_t>(conversion::den)) * static_cast<type_t>(conversion::num);
}

// ============================================================================
// Tag normalization
// Several areas in the library treat `void` as the “default” (no tag);
// however the unit_t default parameter uses `details::untagged_t` when nothing
// is specified.  Arithmetic operations and type-mapping traits need a
// consistent value so that a unit produced from two untagged operands still
// matches the specializations (e.g. force -> newton_t).  The helpers below
// convert `untagged_t` into `void` while leaving other tags unchanged.

// forward declare untagged_t so it can be referenced before its full definition
struct untagged_t;

template <typename tag_t>
using normalize_tag_t = std::conditional_t<std::is_same_v<tag_t, untagged_t>, void, tag_t>;

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

struct untagged_t
{
};

} // namespace details

// Forward declaration of derived_unit_type_t in the outer namespace.
// The full definition appears later after the unit_t class so that
// operations within unit_t can use it.
template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v, typename tag_t>
struct derived_unit_type_t;

template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v, typename tag_t = details::untagged_t>
class unit_t
{
public:
    using value_type = type_t;
    using ratio_type = ratio_t;
    using tag_type = tag_t;
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

    // Allow construction from another unit with same dimension but identical tag (different ratio allowed)
    template <typename other_ratio_t, typename other_tag_t>
        requires std::is_same_v<other_tag_t, tag_t>
    constexpr unit_t(const unit_t<type_t, other_ratio_t, dim_v, other_tag_t>& other) noexcept
        : m_value(details::convert_ratio_to<type_t, other_ratio_t, ratio_t>(other.value()))
    {
    }

    // Diagnostic constructor: explicit failure when attempting to construct from a unit with a DIFFERENT dimension
    // This provides a short, actionable message instead of a long overload-resolution trace.
    template <typename other_ratio_t, dimension_t other_dim_v, typename other_tag_t>
        requires(other_dim_v != dim_v)
    explicit constexpr unit_t(const unit_t<type_t, other_ratio_t, other_dim_v, other_tag_t>&) noexcept
    {
        static_assert(other_dim_v == dim_v, "unit_t: cannot construct from unit with different dimensions");
    }

    // make sure type is default copyable and movable
    constexpr unit_t(const unit_t&) noexcept = default;
    constexpr unit_t(unit_t&&) noexcept = default;
    constexpr unit_t& operator=(const unit_t&) noexcept = default;
    constexpr unit_t& operator=(unit_t&&) noexcept = default;

    // Multiply by another si_unit quantity (combine dimensions and ratios)
    template <typename ratio_u, dimension_t dim_u, typename tag_u>
        requires((dim_u != dim_v) || std::is_same_v<tag_u, tag_t>)
    constexpr auto operator*(const unit_t<type_t, ratio_u, dim_u, tag_u>& other) const noexcept
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

        // Determine resulting tag.  Normalize untagged_t -> void first so that
        // derived_unit_type_t specializations (which are written for tag=void)
        // match correctly when operands have the default/untagged value.
        using lhs_tag = details::normalize_tag_t<tag_t>;
        using rhs_tag = details::normalize_tag_t<tag_u>;
        using result_tag = std::conditional_t<
            std::is_same_v<lhs_tag, rhs_tag>,
            lhs_tag,
            std::conditional_t<std::is_same_v<lhs_tag, void>, rhs_tag, std::conditional_t<std::is_same_v<rhs_tag, void>, lhs_tag, void>>>;

        type_t result_value = m_value * other.value();
        return typename derived_unit_type_t<type_t, combined_ratio, combined_dim_v, result_tag>::type{result_value};
    }

    // Divide by another si_unit quantity (combine dimensions and ratios)
    template <typename ratio_u, dimension_t dim_u, typename tag_u>
    constexpr auto operator/(const unit_t<type_t, ratio_u, dim_u, tag_u>& other) const
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

        // Tag propagation (same policy as multiplication)
        using lhs_tag = details::normalize_tag_t<tag_t>;
        using rhs_tag = details::normalize_tag_t<tag_u>;
        using result_tag = std::conditional_t<
            std::is_same_v<lhs_tag, rhs_tag>,
            lhs_tag,
            std::conditional_t<std::is_same_v<lhs_tag, void>, rhs_tag, std::conditional_t<std::is_same_v<rhs_tag, void>, lhs_tag, void>>>;

        type_t result_value = m_value / other.value();
        return typename derived_unit_type_t<type_t, combined_ratio, combined_dim_v, result_tag>::type{result_value};
    }

    // ============================================================================
    // Additional member utilities

    constexpr auto operator*(std::same_as<type_t> auto scalar) const noexcept
    {
        using result_type = typename derived_unit_type_t<type_t, ratio_t, dim_v, details::normalize_tag_t<tag_t>>::type;
        return result_type{m_value * scalar};
    }

    constexpr auto operator/(std::same_as<type_t> auto scalar) const noexcept
    {
        using result_type = typename derived_unit_type_t<type_t, ratio_t, dim_v, details::normalize_tag_t<tag_t>>::type;
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

    [[nodiscard]] constexpr type_t value() const noexcept
    {
        return m_value;
    }

    constexpr type_t operator*() const noexcept
    {
        return m_value;
    }

    [[nodiscard]] constexpr auto to_si() const noexcept
    {
        type_t canonical_value = details::convert_ratio_to<type_t, ratio_t, std::ratio<1, 1>>(m_value);
        using canonical_unit = typename derived_unit_type_t<type_t, std::ratio<1, 1>, dim_v, details::normalize_tag_t<tag_t>>::type;
        return canonical_unit{canonical_value};
    }

    [[nodiscard]] constexpr auto in_base_si_units() const noexcept
    {
        type_t canonical_value = details::convert_ratio_to<type_t, ratio_t, std::ratio<1, 1>>(m_value);
        return unit_t<type_t, std::ratio<1, 1>, dim_v, tag_t>{canonical_value};
    }

    // Member function to get magnitude (only available for complex value types)
    // Returns the same unit type but with real-valued magnitude
    [[nodiscard]] constexpr auto magnitude() const noexcept
        requires details::complex_type_c<type_t>
    {
        using real_type = details::complex_underlying_type_t<type_t>;
        auto mag_value = static_cast<real_type>(std::abs(m_value));
        using result_unit = typename derived_unit_type_t<real_type, ratio_t, dim_v, details::normalize_tag_t<tag_t>>::type;
        return result_unit{mag_value};
    }

    // Member function to get phase angle in radians (only available for complex value types)
    // Returns a unit with angle dimension, which resolves to radian_t<real_type>
    // Result is in range [-π, π] radians
    [[nodiscard]] constexpr auto phase() const noexcept
        requires details::complex_type_c<type_t>
    {
        using real_type = details::complex_underlying_type_t<type_t>;
        auto phase_value = static_cast<real_type>(std::arg(m_value));
        using result_unit = typename derived_unit_type_t<real_type, std::ratio<1, 1>, angle_dimension, details::normalize_tag_t<tag_t>>::type;
        return result_unit{phase_value};
    }

private:
    type_t m_value;
};

// ============================================================================
// Most derived unit_type deduction helpers

template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v, typename tag_t = void>
struct derived_unit_type_t
{
    // normalize untagged_t -> void so that specializations (which are written
    // for tag=void) will be selected even if an untagged value slipped
    // through.
    using normalized_tag = std::conditional_t<std::is_same_v<tag_t, details::untagged_t>, void, tag_t>;
    using type = unit_t<type_t, ratio_t, dim_v, normalized_tag>;
};

// ============================================================================
// Type Traits for Unit Detection
// ============================================================================

namespace details
{
// Helper to check if a type is an pkr_unit and extract its components
template <typename T>
struct is_pkr_unit : std::false_type
{
};

// Specialization for direct unit_t types
template <typename type_t, typename ratio_t, dimension_t dim_v, typename tag_t>
struct is_pkr_unit<::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, dim_v, tag_t>> : std::true_type
{
    static constexpr bool value = true;
    using value_type = type_t;
    using ratio_type = ratio_t;
    using tag_type = tag_t;
    using most_derived_type = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, dim_v, tag_t>;
    static constexpr dimension_t value_dimension = dim_v;
};

// Specialization for derived types that inherit from unit_t
// (e.g., struct meter : public unit_t<...>)
template <typename T>
    requires std::is_base_of_v<typename T::_base, T>
struct is_pkr_unit<T> : std::true_type
{
    static constexpr bool value = true;
    using value_type = typename T::_base::value_type;
    using ratio_type = typename T::_base::ratio_type;
    using tag_type = typename T::_base::tag_type;
    using most_derived_type = T;
    // Extract dimension from the base unit_t class
    static constexpr dimension_t value_dimension = T::_base::dimension::value;
};

// ------------------------------------------------------------------
// NEW: unified trait helpers for easier access (see design notes)
// ------------------------------------------------------------------

// Primary template: non-unit by default
template <typename U>
struct unit_traits
{
    static constexpr bool is_unit = false;
};

// Simple alias to reduce verbosity in specializations below
using namespace PKR_UNITS_NAMESPACE;

// Specialization for plain unit_t
template <typename value_t, typename ratio_t, dimension_t dim_v, typename tag_t>
struct unit_traits<unit_t<value_t, ratio_t, dim_v, tag_t>>
{
    static constexpr bool is_unit = true;
    using value_type = value_t;
    using ratio_type = ratio_t;
    using dimension = std::integral_constant<dimension_t, dim_v>;
    using tag_type = tag_t;
    using most_derived = unit_t<value_t, ratio_t, dim_v, tag_t>;
};

// Derived units inherit traits from their base
template <typename U>
    requires std::is_base_of_v<typename U::_base, U>
struct unit_traits<U> : unit_traits<typename U::_base>
{
};

// Helpers for template aliases used by the public API

template <typename U>
using value_type_t = typename unit_traits<U>::value_type;

template <typename U>
using ratio_type_t = typename unit_traits<U>::ratio_type;

template <typename U>
using tag_type_t = typename unit_traits<U>::tag_type;

template <typename U>
using dim_v_t = typename unit_traits<U>::dimension::value_type;

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

template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v, typename tag_t = void>
using derived_unit_type_t = ::PKR_UNITS_NAMESPACE::derived_unit_type_t<type_t, ratio_t, dim_v, tag_t>;

} // namespace details

// public concepts/aliases

template <typename U>
concept pkr_unit_c = details::unit_traits<U>::is_unit;

template <typename U>
using unit_value_t = details::value_type_t<U>;

template <typename U>
using unit_ratio_t = details::ratio_type_t<U>;

template <typename U>
using unit_tag_t = details::tag_type_t<U>;

template <typename U>
using unit_dim_t = details::dim_v_t<U>;

// ============================================================================
// Unit Type Aliases for Common Dimensions
// ============================================================================

// SI Base Units
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using length_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::length_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::mass_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using time_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::time_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using current_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::current_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using temperature_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::temperature_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using amount_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::amount_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using intensity_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::intensity_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using angle_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::angle_dimension>;

// Derived Quantities (Common)
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using area_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::area_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using volume_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::volume_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using acceleration_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::acceleration_v>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using velocity_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::velocity_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using density_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::density_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using dynamic_viscosity_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::dynamic_viscosity_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using kinematic_viscosity_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::kinematic_viscosity_dimension>;

// Concentration Types
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass_concentration_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::mass_concentration_v>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using molar_concentration_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::molar_concentration_v>;

// Other Derived Quantities
template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using josephson_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::josephson_dimension>;

template <typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using solid_angle_unit_t = ::PKR_UNITS_NAMESPACE::unit_t<type_t, ratio_t, ::PKR_UNITS_NAMESPACE::solid_angle_dimension>;

} // namespace PKR_UNITS_NAMESPACE
