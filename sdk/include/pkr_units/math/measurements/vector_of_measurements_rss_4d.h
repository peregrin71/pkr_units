#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
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
        x = pkr::units::math::divide_rss(x, scalar);
        y = pkr::units::math::divide_rss(y, scalar);
        z = pkr::units::math::divide_rss(z, scalar);
        w = pkr::units::math::divide_rss(w, scalar);
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

template<pkr::units::is_measurement_c T1, pkr::units::is_measurement_c T2>
requires same_dimensions_c<T1::unit_type, T2::unit_type>
constexpr auto operator+(const vec_4d_t<T1>& a, const vec_4d_t<T2>& b) noexcept {
    using ResultT = decltype(a.x + b.x);
    return vec_4d_t<ResultT>{
        pkr::units::math::stable_add(a.x, b.x),
        pkr::units::math::stable_add(a.y, b.y),
        pkr::units::math::stable_add(a.z, b.z),
        pkr::units::math::stable_add(a.w, b.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept {
    return vec_4d_t<T>{
        pkr::units::math::stable_subtract(a.x, b.x),
        pkr::units::math::stable_subtract(a.y, b.y),
        pkr::units::math::stable_subtract(a.z, b.z),
        pkr::units::math::stable_subtract(a.w, b.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator*(double scalar, const vec_4d_t<T>& v) noexcept {
    return vec_4d_t<T>{
        pkr::units::math::stable_multiply(scalar, v.x),
        pkr::units::math::stable_multiply(scalar, v.y),
        pkr::units::math::stable_multiply(scalar, v.z),
        pkr::units::math::stable_multiply(scalar, v.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_t<T> operator*(const vec_4d_t<T>& v, double scalar) noexcept {
    return vec_4d_t<T>{
        pkr::units::math::stable_multiply(v.x, scalar),
        pkr::units::math::stable_multiply(v.y, scalar),
        pkr::units::math::stable_multiply(v.z, scalar),
        pkr::units::math::stable_multiply(v.w, scalar)
    };
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

} // namespace PKR_UNITS_NAMESPACE
