#pragma once

#include <pkr_units/measurements.h>
#include <pkr_units/math/unit/unit_math.h>
#include "vector_3d.h"

namespace PKR_UNITS_NAMESPACE
{
namespace math
{

// ============================================================================
// Specialized 3D Vector for Measurements (using RSS uncertainty propagation)
// ============================================================================

template<pkr::units::is_measurement_c T>
struct vec_3d_t<T> {
    T x, y, z;

    vec_3d_t() : x{0}, y{0}, z{0} {}
    vec_3d_t(T x, T y, T z) : x{x}, y{y}, z{z} {}

    constexpr vec_3d_t& operator+=(const vec_3d_t& other) noexcept {
        x = pkr::math::add_rss(x, other.x);
        y = pkr::math::add_rss(y, other.y);
        z = pkr::math::add_rss(z, other.z);
        return *this;
    }

    constexpr vec_3d_t& operator-=(const vec_3d_t& other) noexcept {
        x = pkr::math::subtract_rss(x, other.x);
        y = pkr::math::subtract_rss(y, other.y);
        z = pkr::math::subtract_rss(z, other.z);
        return *this;
    }

    constexpr vec_3d_t& operator*=(double scalar) noexcept {
        x = pkr::math::multiply_rss(x, scalar);
        y = pkr::math::multiply_rss(y, scalar);
        z = pkr::math::multiply_rss(z, scalar);
        return *this;
    }

    constexpr vec_3d_t& operator/=(double scalar) noexcept {
        x = T{x.value() / scalar};
        y = T{y.value() / scalar};
        z = T{z.value() / scalar};
        return *this;
    }
};

template<pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator+(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept {
    return vec_3d_t<T>{
        pkr::math::add_rss(a.x, b.x),
        pkr::math::add_rss(a.y, b.y),
        pkr::math::add_rss(a.z, b.z)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator-(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept {
    return vec_3d_t<T>{
        pkr::math::subtract_rss(a.x, b.x),
        pkr::math::subtract_rss(a.y, b.y),
        pkr::math::subtract_rss(a.z, b.z)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator*(double scalar, const vec_3d_t<T>& v) noexcept {
    return vec_3d_t<T>{
        pkr::math::multiply_rss(scalar, v.x),
        pkr::math::multiply_rss(scalar, v.y),
        pkr::math::multiply_rss(scalar, v.z)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator*(const vec_3d_t<T>& v, double scalar) noexcept {
    return scalar * v;
}

template<pkr::units::is_measurement_c T>
constexpr auto dot(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept {
    return pkr::numerical::stable_add(
        pkr::numerical::stable_add(
            pkr::numerical::stable_multiply(a.x, b.x),
            pkr::numerical::stable_multiply(a.y, b.y)
        ),
        pkr::numerical::stable_multiply(a.z, b.z)
    );
}

template<pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> cross(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept {
    return vec_3d_t<T>{
        pkr::numerical::stable_subtract(
            pkr::numerical::stable_multiply(a.y, b.z),
            pkr::numerical::stable_multiply(a.z, b.y)
        ),
        pkr::numerical::stable_subtract(
            pkr::numerical::stable_multiply(a.z, b.x),
            pkr::numerical::stable_multiply(a.x, b.z)
        ),
        pkr::numerical::stable_subtract(
            pkr::numerical::stable_multiply(a.x, b.y),
            pkr::numerical::stable_multiply(a.y, b.x)
        )
    };
}

} // namespace math
} // namespace PKR_UNITS_NAMESPACE