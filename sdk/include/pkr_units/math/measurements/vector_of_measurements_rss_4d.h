#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{
namespace math
{

// ============================================================================
// Specialized 4D Vector for Measurements (using RSS uncertainty propagation)
// ============================================================================

template<pkr::units::is_measurement_c T>
struct vec_4d_t<T> {
    T x, y, z, w;

    vec_4d_t() : x{0}, y{0}, z{0}, w{1} {}
    vec_4d_t(T x, T y, T z, T w = 1) : x{x}, y{y}, z{z}, w{w} {}

    constexpr vec_4d_t& operator+=(const vec_4d_t& other) noexcept {
        x = pkr::units::math::add_rss(x, other.x);
        y = pkr::units::math::add_rss(y, other.y);
        z = pkr::units::math::add_rss(z, other.z);
        w = pkr::units::math::add_rss(w, other.w);
        return *this;
    }

    constexpr vec_4d_t& operator-=(const vec_4d_t& other) noexcept {
        x = pkr::units::math::subtract_rss(x, other.x);
        y = pkr::units::math::subtract_rss(y, other.y);
        z = pkr::units::math::subtract_rss(z, other.z);
        w = pkr::units::math::subtract_rss(w, other.w);
        return *this;
    }

    constexpr vec_4d_t& operator*=(double scalar) noexcept {
        x = pkr::units::math::multiply_rss(x, scalar);
        y = pkr::units::math::multiply_rss(y, scalar);
        z = pkr::units::math::multiply_rss(z, scalar);
        w = pkr::units::math::multiply_rss(w, scalar);
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

template<pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator+(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept {
    return vec_4d_t<T>{
        pkr::units::math::add_rss(a.x, b.x),
        pkr::units::math::add_rss(a.y, b.y),
        pkr::units::math::add_rss(a.z, b.z),
        pkr::units::math::add_rss(a.w, b.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept {
    return vec_4d_t<T>{
        pkr::units::math::subtract_rss(a.x, b.x),
        pkr::units::math::subtract_rss(a.y, b.y),
        pkr::units::math::subtract_rss(a.z, b.z),
        pkr::units::math::subtract_rss(a.w, b.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator*(double scalar, const vec_4d_t<T>& v) noexcept {
    return vec_4d_t<T>{
        pkr::units::math::multiply_rss(scalar, v.x),
        pkr::units::math::multiply_rss(scalar, v.y),
        pkr::units::math::multiply_rss(scalar, v.z),
        pkr::units::math::multiply_rss(scalar, v.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator*(const vec_4d_t<T>& v, double scalar) noexcept {
    return scalar * v;
}

template<pkr::units::is_measurement_c T>
constexpr auto dot(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept {
    return math::stable_add(
        math::stable_add(
            math::stable_multiply(a.x, b.x),
            math::stable_multiply(a.y, b.y)
        ),
        math::stable_add(
            math::stable_multiply(a.z, b.z),
            math::stable_multiply(a.w, b.w)
        )
    );
}

} // namespace math
} // namespace PKR_UNITS_NAMESPACE
