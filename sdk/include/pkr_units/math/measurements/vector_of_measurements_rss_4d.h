#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 4D Vector for Measurements (using RSS uncertainty propagation)
// ============================================================================

template <pkr::units::is_measurement_c T>
struct vec_4d_t<T>
{
    T x, y, z, w;

    vec_4d_t()
        : x{0}
        , y{0}
        , z{0}
        , w{1}
    {
    }

    vec_4d_t(T x, T y, T z, T w = 1)
        : x{x}
        , y{y}
        , z{z}
        , w{w}
    {
    }

    constexpr vec_4d_t& operator+=(const vec_4d_t& other) noexcept
    {
        x = pkr::units::add_rss(x, other.x);
        y = pkr::units::add_rss(y, other.y);
        z = pkr::units::add_rss(z, other.z);
        w = pkr::units::add_rss(w, other.w);
        return *this;
    }

    constexpr vec_4d_t& operator-=(const vec_4d_t& other) noexcept
    {
        x = pkr::units::subtract_rss(x, other.x);
        y = pkr::units::subtract_rss(y, other.y);
        z = pkr::units::subtract_rss(z, other.z);
        w = pkr::units::subtract_rss(w, other.w);
        return *this;
    }

    constexpr vec_4d_t& operator*=(double scalar) noexcept
    {
        x = pkr::units::multiply_rss(x, scalar);
        y = pkr::units::multiply_rss(y, scalar);
        z = pkr::units::multiply_rss(z, scalar);
        w = pkr::units::multiply_rss(w, scalar);
        return *this;
    }

    constexpr vec_4d_t& operator/=(double scalar) noexcept
    {
        x = pkr::units::divide_rss(x, scalar);
        y = pkr::units::divide_rss(y, scalar);
        z = pkr::units::divide_rss(z, scalar);
        w = pkr::units::divide_rss(w, scalar);
        return *this;
    }
};

template <pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator+(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept
{
    return vec_4d_t<T>{pkr::units::add_rss(a.x, b.x), pkr::units::add_rss(a.y, b.y), pkr::units::add_rss(a.z, b.z), pkr::units::add_rss(a.w, b.w)};
}

template <pkr::units::is_measurement_c T1, pkr::units::is_measurement_c T2>
    requires same_dimensions_c<T1::unit_type, T2::unit_type>
constexpr auto operator+(const vec_4d_t<T1>& a, const vec_4d_t<T2>& b) noexcept
{
    using ResultT = decltype(a.x + b.x);
    return vec_4d_t<ResultT>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

template <pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept
{
    return vec_4d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

template <pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator*(double scalar, const vec_4d_t<T>& v) noexcept
{
    return vec_4d_t<T>{scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w};
}

template <pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator*(const vec_4d_t<T>& v, double scalar) noexcept
{
    return vec_4d_t<T>{v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar};
}

template <pkr::units::is_measurement_c T>
constexpr auto dot(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept
{
    return (a.x * b.x) + (a.y * b.y) + ((a.z * b.z) + (a.w * b.w));
}

} // namespace PKR_UNITS_NAMESPACE
