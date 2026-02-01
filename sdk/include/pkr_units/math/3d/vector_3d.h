#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Templated 3D Vector
// ============================================================================

template <typename T>
struct vec_3d_t
{
    T x, y, z;

    vec_3d_t()
        : x{0}
        , y{0}
        , z{0}
    {
    }

    vec_3d_t(T x, T y, T z)
        : x{x}
        , y{y}
        , z{z}
    {
    }

    vec_3d_t& operator+=(const vec_3d_t& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec_3d_t& operator-=(const vec_3d_t& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec_3d_t& operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    vec_3d_t& operator/=(T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};

template <typename T>
constexpr vec_3d_t<T> operator+(const vec_3d_t<T>& a, const vec_3d_t<T>& b)
{
    return vec_3d_t<T>{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename T>
constexpr vec_3d_t<T> operator-(const vec_3d_t<T>& a, const vec_3d_t<T>& b)
{
    return vec_3d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T>
constexpr vec_3d_t<T> operator*(T scalar, const vec_3d_t<T>& v)
{
    return vec_3d_t<T>{scalar * v.x, scalar * v.y, scalar * v.z};
}

template <typename T>
constexpr vec_3d_t<T> operator*(const vec_3d_t<T>& v, T scalar)
{
    return scalar * v;
}

template <typename T>
constexpr T dot(const vec_3d_t<T>& a, const vec_3d_t<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
constexpr vec_3d_t<T> cross(const vec_3d_t<T>& a, const vec_3d_t<T>& b)
{
    return vec_3d_t<T>{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

} // namespace PKR_UNITS_NAMESPACE
