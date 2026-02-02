#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/measurements.h>
#include <cmath>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Templated 4D Vector
// ============================================================================

template <typename T>
struct vec_4d_t
{
    T x, y, z, w;

    vec_4d_t()
        : x{0}
        , y{0}
        , z{0}
        , w{1}
    {
    }

    vec_4d_t(T x_value, T y_value, T z_value, T w_value = 1)
        : x{x_value}
        , y{y_value}
        , z{z_value}
        , w{w_value}
    {
    }

    vec_4d_t& operator+=(const vec_4d_t& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    vec_4d_t& operator-=(const vec_4d_t& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    vec_4d_t& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    vec_4d_t& operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    // Calculate magnitude of the 3D portion (ignoring w component)
    double magnitude() const
        requires requires(T a) { std::sqrt(a * a); }
    {
        return std::sqrt(static_cast<double>(x * x + y * y + z * z));
    }
};

template <typename T>
    requires(!is_base_pkr_unit_c<T>)
constexpr vec_4d_t<T> operator+(const vec_4d_t<T>& a, const vec_4d_t<T>& b)
{
    return vec_4d_t<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

template <typename T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& a, const vec_4d_t<T>& b)
{
    return vec_4d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

template <typename T, typename U>
    requires requires(T a, U b) { a * b; }
constexpr auto operator*(U scalar, const vec_4d_t<T>& v)
{
    using ResultT = decltype(scalar * v.x);
    return vec_4d_t<ResultT>{scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w};
}

template <typename T, typename U>
    requires requires(T a, U b) { a * b; }
constexpr auto operator*(const vec_4d_t<T>& v, U scalar)
{
    return scalar * v;
}

template <typename T>
constexpr vec_4d_t<T> operator/(const vec_4d_t<T>& v, T scalar)
{
    return vec_4d_t<T>{v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar};
}

template <typename T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& v)
{
    return vec_4d_t<T>{-v.x, -v.y, -v.z, -v.w};
}

template <typename T>
constexpr bool operator==(const vec_4d_t<T>& a, const vec_4d_t<T>& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

// Dot product for plain vectors (non-unit, non-measurement)
template <typename T>
    requires(!is_base_pkr_unit_c<T>)
constexpr auto dot(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

} // namespace PKR_UNITS_NAMESPACE
