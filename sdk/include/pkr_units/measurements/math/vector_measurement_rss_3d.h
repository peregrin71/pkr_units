#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>
#include <cmath>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 3D Vector for RSS Measurements with RSS uncertainty propagation
// ============================================================================

template <pkr::units::is_pkr_unit_c T>
struct vec_measurement_rss_3d_t
{
    pkr::units::measurement_rss_t<T> x, y, z;

    vec_measurement_rss_3d_t()
        : x{0.0, 0.0}
        , y{0.0, 0.0}
        , z{0.0, 0.0}
    {
    }

    vec_measurement_rss_3d_t(
        pkr::units::measurement_rss_t<T> x_measurement,
        pkr::units::measurement_rss_t<T> y_measurement,
        pkr::units::measurement_rss_t<T> z_measurement)
        : x{x_measurement}
        , y{y_measurement}
        , z{z_measurement}
    {
    }

    // Constructor accepting scalar values for convenience
    vec_measurement_rss_3d_t(
        typename T::value_type x_val,
        typename T::value_type x_unc,
        typename T::value_type y_val,
        typename T::value_type y_unc,
        typename T::value_type z_val,
        typename T::value_type z_unc)
        : x{x_val, x_unc}
        , y{y_val, y_unc}
        , z{z_val, z_unc}
    {
    }

    constexpr vec_measurement_rss_3d_t& operator+=(const vec_measurement_rss_3d_t& other) noexcept
    {
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        return *this;
    }

    constexpr vec_measurement_rss_3d_t& operator-=(const vec_measurement_rss_3d_t& other) noexcept
    {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        return *this;
    }

    constexpr vec_measurement_rss_3d_t& operator*=(double scalar) noexcept
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        return *this;
    }

    constexpr vec_measurement_rss_3d_t& operator/=(double scalar) noexcept
    {
        x = x / scalar;
        y = y / scalar;
        z = z / scalar;
        return *this;
    }

    // Calculate magnitude of the 3D portion with RSS uncertainty propagation
    constexpr auto magnitude() const noexcept
    {
        using measurement_t = pkr::units::measurement_rss_t<T>;
        auto x_sq = x * x;
        auto y_sq = y * y;
        auto z_sq = z * z;
        auto sum_sq = x_sq + y_sq + z_sq;
        auto value = std::sqrt(sum_sq.value());
        auto uncertainty = std::sqrt((sum_sq.uncertainty() * sum_sq.uncertainty()) / (4.0 * value * value));
        return measurement_t{value, uncertainty};
    }
};

template <pkr::units::is_pkr_unit_c T>
constexpr auto operator+(const vec_measurement_rss_3d_t<T>& a, const vec_measurement_rss_3d_t<T>& b) noexcept
{
    return vec_measurement_rss_3d_t<T>{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <pkr::units::is_pkr_unit_c T>
constexpr auto operator-(const vec_measurement_rss_3d_t<T>& a, const vec_measurement_rss_3d_t<T>& b) noexcept
{
    return vec_measurement_rss_3d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z};
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_3d_t<T> operator*(const vec_measurement_rss_3d_t<T>& v, double scalar) noexcept
{
    return vec_measurement_rss_3d_t<T>{v.x * scalar, v.y * scalar, v.z * scalar};
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_3d_t<T> operator*(double scalar, const vec_measurement_rss_3d_t<T>& v) noexcept
{
    return v * scalar;
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_3d_t<T> operator/(const vec_measurement_rss_3d_t<T>& v, double scalar) noexcept
{
    return vec_measurement_rss_3d_t<T>{v.x / scalar, v.y / scalar, v.z / scalar};
}

template <pkr::units::is_pkr_unit_c T>
constexpr auto dot(const vec_measurement_rss_3d_t<T>& a, const vec_measurement_rss_3d_t<T>& b) noexcept
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_3d_t<T> cross(const vec_measurement_rss_3d_t<T>& a, const vec_measurement_rss_3d_t<T>& b) noexcept
{
    return vec_measurement_rss_3d_t<T>{
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)};
}

} // namespace PKR_UNITS_NAMESPACE

