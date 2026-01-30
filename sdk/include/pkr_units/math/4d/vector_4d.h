#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{
namespace math
{

// ============================================================================
// Templated 4D Vector
// ============================================================================

template<typename T>
struct vec_4d_t {
    T x, y, z, w;

    vec_4d_t() : x{0}, y{0}, z{0}, w{1} {}
    vec_4d_t(T x, T y, T z, T w = 1) : x{x}, y{y}, z{z}, w{w} {}

    vec_4d_t& operator+=(const vec_4d_t& other) {
        x += other.x; y += other.y; z += other.z; w += other.w;
        return *this;
    }

    vec_4d_t& operator-=(const vec_4d_t& other) {
        x -= other.x; y -= other.y; z -= other.z; w -= other.w;
        return *this;
    }

    vec_4d_t& operator*=(T scalar) {
        x *= scalar; y *= scalar; z *= scalar; w *= scalar;
        return *this;
    }

    vec_4d_t& operator/=(T scalar) {
        x /= scalar; y /= scalar; z /= scalar; w /= scalar;
        return *this;
    }
};

template<typename T>
constexpr vec_4d_t<T> operator+(const vec_4d_t<T>& a, const vec_4d_t<T>& b) {
    return vec_4d_t<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

template<typename T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& a, const vec_4d_t<T>& b) {
    return vec_4d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

template<typename T>
constexpr vec_4d_t<T> operator*(T scalar, const vec_4d_t<T>& v) {
    return vec_4d_t<T>{scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w};
}

template<typename T>
constexpr vec_4d_t<T> operator*(const vec_4d_t<T>& v, T scalar) {
    return scalar * v;
}

template<typename T>
constexpr T dot(const vec_4d_t<T>& a, const vec_4d_t<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

} // namespace math
} // namespace PKR_UNITS_NAMESPACE