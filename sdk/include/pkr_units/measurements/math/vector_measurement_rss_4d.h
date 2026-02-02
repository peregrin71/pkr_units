#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>
#include <cmath>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 4D Vector for RSS Measurements with RSS uncertainty propagation
// ============================================================================

template <pkr::units::is_pkr_unit_c T>
struct vec_measurement_rss_4d_t
{
    pkr::units::measurement_rss_t<T> x, y, z, w;

    vec_measurement_rss_4d_t()
        : x{0.0, 0.0}
        , y{0.0, 0.0}
        , z{0.0, 0.0}
        , w{1.0, 0.0}
    {
    }

    vec_measurement_rss_4d_t(
        pkr::units::measurement_rss_t<T> x_value,
        pkr::units::measurement_rss_t<T> y_value,
        pkr::units::measurement_rss_t<T> z_value,
        pkr::units::measurement_rss_t<T> w_value = pkr::units::measurement_rss_t<T>{1.0, 0.0})
        : x{x_value}
        , y{y_value}
        , z{z_value}
        , w{w_value}
    {
    }

    // Constructor accepting scalar values for convenience
    vec_measurement_rss_4d_t(
        typename T::value_type x_val,
        typename T::value_type x_unc,
        typename T::value_type y_val,
        typename T::value_type y_unc,
        typename T::value_type z_val,
        typename T::value_type z_unc,
        typename T::value_type w_val = 1.0,
        typename T::value_type w_unc = 0.0)
        : x{x_val, x_unc}
        , y{y_val, y_unc}
        , z{z_val, z_unc}
        , w{w_val, w_unc}
    {
    }

    constexpr vec_measurement_rss_4d_t& operator+=(const vec_measurement_rss_4d_t& other) noexcept
    {
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        w = w + other.w;
        return *this;
    }

    constexpr vec_measurement_rss_4d_t& operator-=(const vec_measurement_rss_4d_t& other) noexcept
    {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        w = w - other.w;
        return *this;
    }

    constexpr vec_measurement_rss_4d_t& operator*=(double scalar) noexcept
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        w = w * scalar;
        return *this;
    }

    constexpr vec_measurement_rss_4d_t& operator/=(double scalar) noexcept
    {
        x = x / scalar;
        y = y / scalar;
        z = z / scalar;
        w = w / scalar;
        return *this;
    }

    // Calculate magnitude of the 3D portion with RSS uncertainty propagation
    constexpr auto magnitude() const noexcept
    {
        using measurement_t = pkr::units::measurement_rss_t<T>;
        // RSS combination: sqrt(x^2 + y^2 + z^2)
        auto x_sq = x * x;
        auto y_sq = y * y;
        auto z_sq = z * z;
        auto sum_sq = x_sq + y_sq + z_sq;
        // For magnitude, we need to take the square root
        // Return as a measurement with the value being the sqrt and uncertainty propagated
        auto value = std::sqrt(sum_sq.value());
        auto uncertainty = std::sqrt((sum_sq.uncertainty() * sum_sq.uncertainty()) / (4.0 * value * value));
        return measurement_t{value, uncertainty};
    }
};

template <pkr::units::is_pkr_unit_c T>
constexpr auto operator+(const vec_measurement_rss_4d_t<T>& a, const vec_measurement_rss_4d_t<T>& b) noexcept
{
    return vec_measurement_rss_4d_t<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

template <pkr::units::is_pkr_unit_c T>
constexpr auto operator-(const vec_measurement_rss_4d_t<T>& a, const vec_measurement_rss_4d_t<T>& b) noexcept
{
    return vec_measurement_rss_4d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_4d_t<T> operator*(const vec_measurement_rss_4d_t<T>& v, double scalar) noexcept
{
    return vec_measurement_rss_4d_t<T>{v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar};
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_4d_t<T> operator*(double scalar, const vec_measurement_rss_4d_t<T>& v) noexcept
{
    return v * scalar;
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_4d_t<T> operator/(const vec_measurement_rss_4d_t<T>& v, double scalar) noexcept
{
    return vec_measurement_rss_4d_t<T>{v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar};
}

template <pkr::units::is_pkr_unit_c T>
constexpr auto dot(const vec_measurement_rss_4d_t<T>& a, const vec_measurement_rss_4d_t<T>& b) noexcept
{
    return (a.x * b.x) + (a.y * b.y) + ((a.z * b.z) + (a.w * b.w));
}

} // namespace PKR_UNITS_NAMESPACE
