#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{
namespace math
{

// ============================================================================
// Specialized 4D Vector for Units (using stable math)
// ============================================================================

template<is_pkr_unit_c T>
struct vec_4d_t<T> {
    T x, y, z, w;

    vec_4d_t() : x{0}, y{0}, z{0}, w{1} {}
    vec_4d_t(T x, T y, T z, T w = 1) : x{x}, y{y}, z{z}, w{w} {}

    constexpr vec_4d_t& operator+=(const vec_4d_t& other) noexcept {
        x = stable_add(x, other.x);
        y = stable_add(y, other.y);
        z = stable_add(z, other.z);
        w = stable_add(w, other.w);
        return *this;
    }

    constexpr vec_4d_t& operator-=(const vec_4d_t& other) noexcept {
        x = stable_subtract(x, other.x);
        y = stable_subtract(y, other.y);
        z = stable_subtract(z, other.z);
        w = stable_subtract(w, other.w);
        return *this;
    }

    constexpr vec_4d_t& operator*=(double scalar) noexcept {
        x = stable_multiply(x, scalar);
        y = stable_multiply(y, scalar);
        z = stable_multiply(z, scalar);
        w = stable_multiply(w, scalar);
        return *this;
    }

    constexpr vec_4d_t& operator/=(double scalar) noexcept {
        x = T{x.value() / scalar};
        y = T{y.value() / scalar};
        z = T{z.value() / scalar};
        w = T{w.value() / scalar};
        return *this;
    }
};

template<is_pkr_unit_c T>
constexpr vec_4d_t<T> operator+(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept {
    return vec_4d_t<T>{
        stable_add(a.x, b.x),
        stable_add(a.y, b.y),
        stable_add(a.z, b.z),
        stable_add(a.w, b.w)
    };
}

template<is_pkr_unit_c T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept {
    return vec_4d_t<T>{
        stable_subtract(a.x, b.x),
        stable_subtract(a.y, b.y),
        stable_subtract(a.z, b.z),
        stable_subtract(a.w, b.w)
    };
}

template<is_pkr_unit_c T>
constexpr vec_4d_t<T> operator*(double scalar, const vec_4d_t<T>& v) noexcept {
    return vec_4d_t<T>{
        stable_multiply(scalar, v.x),
        stable_multiply(scalar, v.y),
        stable_multiply(scalar, v.z),
        stable_multiply(scalar, v.w)
    };
}

template<is_pkr_unit_c T>
constexpr vec_4d_t<T> operator*(const vec_4d_t<T>& v, double scalar) {
    return scalar * v;
}

template<is_pkr_unit_c T>
constexpr auto dot(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept {
    return stable_add(
        stable_add(
            stable_multiply(a.x, b.x),
            stable_multiply(a.y, b.y)
        ),
        stable_add(
            stable_multiply(a.z, b.z),
            stable_multiply(a.w, b.w)
        )
    );
}

} // namespace math
} // namespace PKR_UNITS_NAMESPACE
