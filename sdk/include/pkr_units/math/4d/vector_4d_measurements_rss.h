#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/math/measurements/measurement_math_rss.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 4D Vector for Measurements (using RSS uncertainty propagation)
// ============================================================================

template<pkr::units::is_measurement_c T>
struct vec_4d_measurements_rss_t {
    T x, y, z, w;

    vec_4d_measurements_rss_t() : x{T{0.0, 0.0}}, y{T{0.0, 0.0}}, z{T{0.0, 0.0}}, w{T{1.0, 0.0}} {}
    vec_4d_measurements_rss_t(T x, T y, T z, T w = T{1.0, 0.0}) : x{x}, y{y}, z{z}, w{w} {}

    constexpr vec_4d_measurements_rss_t operator-() const noexcept {
        return vec_4d_measurements_rss_t{
            -x,
            -y,
            -z,
            -w
        };
    }

    constexpr vec_4d_measurements_rss_t& operator+=(const vec_4d_measurements_rss_t& other) noexcept {
        x = pkr::units::add_rss(x, other.x);
        y = pkr::units::add_rss(y, other.y);
        z = pkr::units::add_rss(z, other.z);
        w = pkr::units::add_rss(w, other.w);
        return *this;
    }

    constexpr vec_4d_measurements_rss_t& operator-=(const vec_4d_measurements_rss_t& other) noexcept {
        x = pkr::units::subtract_rss(x, other.x);
        y = pkr::units::subtract_rss(y, other.y);
        z = pkr::units::subtract_rss(z, other.z);
        w = pkr::units::subtract_rss(w, other.w);
        return *this;
    }

    // In-place addition/subtraction with different measurement types (compatible dimensions)
    template<pkr::units::is_measurement_c OtherT>
    requires same_dimensions_c<typename T::value_type, typename OtherT::value_type>
    constexpr vec_4d_measurements_rss_t& operator+=(const vec_4d_measurements_rss_t<OtherT>& other) noexcept {
        x = pkr::units::add_rss(x, other.x);
        y = pkr::units::add_rss(y, other.y);
        z = pkr::units::add_rss(z, other.z);
        w = pkr::units::add_rss(w, other.w);
        return *this;
    }

    template<pkr::units::is_measurement_c OtherT>
    requires same_dimensions_c<typename T::value_type, typename OtherT::value_type>
    constexpr vec_4d_measurements_rss_t& operator-=(const vec_4d_measurements_rss_t<OtherT>& other) noexcept {
        x = pkr::units::subtract_rss(x, other.x);
        y = pkr::units::subtract_rss(y, other.y);
        z = pkr::units::subtract_rss(z, other.z);
        w = pkr::units::subtract_rss(w, other.w);
        return *this;
    }

    constexpr vec_4d_measurements_rss_t& operator*=(double scalar) noexcept {
        x = pkr::units::multiply_rss(x, scalar);
        y = pkr::units::multiply_rss(y, scalar);
        z = pkr::units::multiply_rss(z, scalar);
        w = pkr::units::multiply_rss(w, scalar);
        return *this;
    }

    constexpr vec_4d_measurements_rss_t& operator/=(double scalar) noexcept {
        x = pkr::units::divide_rss(x, scalar);
        y = pkr::units::divide_rss(y, scalar);
        z = pkr::units::divide_rss(z, scalar);
        w = pkr::units::divide_rss(w, scalar);
        return *this;
    }
};

template<pkr::units::is_measurement_c T>
constexpr vec_4d_measurements_rss_t<T> operator+(const vec_4d_measurements_rss_t<T>& a, const vec_4d_measurements_rss_t<T>& b) noexcept {
    return vec_4d_measurements_rss_t<T>{
        pkr::units::add_rss(a.x, b.x),
        pkr::units::add_rss(a.y, b.y),
        pkr::units::add_rss(a.z, b.z),
        pkr::units::add_rss(a.w, b.w)
    };
}

template<pkr::units::is_measurement_c T1, pkr::units::is_measurement_c T2>
requires same_dimensions_c<typename T1::value_type, typename T2::value_type>
constexpr auto operator+(const vec_4d_measurements_rss_t<T1>& a, const vec_4d_measurements_rss_t<T2>& b) noexcept {
    using ResultT = decltype(a.x + b.x);
    return vec_4d_measurements_rss_t<ResultT>{
        pkr::units::add_rss(a.x, b.x),
        pkr::units::add_rss(a.y, b.y),
        pkr::units::add_rss(a.z, b.z),
        pkr::units::add_rss(a.w, b.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_measurements_rss_t<T> operator-(const vec_4d_measurements_rss_t<T>& a, const vec_4d_measurements_rss_t<T>& b) noexcept {
    return vec_4d_measurements_rss_t<T>{
        pkr::units::subtract_rss(a.x, b.x),
        pkr::units::subtract_rss(a.y, b.y),
        pkr::units::subtract_rss(a.z, b.z),
        pkr::units::subtract_rss(a.w, b.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_measurements_rss_t<T> operator*(double scalar, const vec_4d_measurements_rss_t<T>& v) noexcept {
    return vec_4d_measurements_rss_t<T>{
        pkr::units::multiply_rss(scalar, v.x),
        pkr::units::multiply_rss(scalar, v.y),
        pkr::units::multiply_rss(scalar, v.z),
        pkr::units::multiply_rss(scalar, v.w)
    };
}

template<pkr::units::is_measurement_c T>
constexpr vec_4d_measurements_rss_t<T> operator*(const vec_4d_measurements_rss_t<T>& v, double scalar) noexcept {
    return vec_4d_measurements_rss_t<T>{
        pkr::units::multiply_rss(v.x, scalar),
        pkr::units::multiply_rss(v.y, scalar),
        pkr::units::multiply_rss(v.z, scalar),
        pkr::units::multiply_rss(v.w, scalar)
    };
}

template<pkr::units::is_measurement_c ScalarT, pkr::units::is_measurement_c VecT>
constexpr vec_4d_measurements_rss_t<decltype(pkr::units::multiply_rss(std::declval<ScalarT>(), std::declval<VecT>()))> operator*(const ScalarT& scalar, const vec_4d_measurements_rss_t<VecT>& v) {
    auto result_x = pkr::units::multiply_rss(scalar, v.x);
    auto result_y = pkr::units::multiply_rss(scalar, v.y);
    auto result_z = pkr::units::multiply_rss(scalar, v.z);
    auto result_w = pkr::units::multiply_rss(scalar, v.w);
    return {result_x, result_y, result_z, result_w};
}

template<pkr::units::is_measurement_c VecT, pkr::units::is_measurement_c ScalarT>
constexpr vec_4d_measurements_rss_t<decltype(pkr::units::multiply_rss(std::declval<VecT>(), std::declval<ScalarT>()))> operator*(const vec_4d_measurements_rss_t<VecT>& v, const ScalarT& scalar) {
    auto result_x = pkr::units::multiply_rss(v.x, scalar);
    auto result_y = pkr::units::multiply_rss(v.y, scalar);
    auto result_z = pkr::units::multiply_rss(v.z, scalar);
    auto result_w = pkr::units::multiply_rss(v.w, scalar);
    return {result_x, result_y, result_z, result_w};
}



template<pkr::units::is_measurement_c T>
constexpr vec_4d_measurements_rss_t<T> operator/(const vec_4d_measurements_rss_t<T>& v, double scalar) noexcept {
    return vec_4d_measurements_rss_t<T>{
        pkr::units::divide_rss(v.x, scalar),
        pkr::units::divide_rss(v.y, scalar),
        pkr::units::divide_rss(v.z, scalar),
        pkr::units::divide_rss(v.w, scalar)
    };
}

// Vector-level add_rss for measurement vectors
template<pkr::units::is_measurement_c T1, pkr::units::is_measurement_c T2>
requires same_dimensions_c<typename T1::value_type, typename T2::value_type>
constexpr auto add_rss(const vec_4d_measurements_rss_t<T1>& a, const vec_4d_measurements_rss_t<T2>& b) {
    using ResultT = decltype(pkr::units::add_rss(a.x, b.x));
    return vec_4d_measurements_rss_t<ResultT>{
        pkr::units::add_rss(a.x, b.x),
        pkr::units::add_rss(a.y, b.y),
        pkr::units::add_rss(a.z, b.z),
        pkr::units::add_rss(a.w, b.w)
    };
}

// Vector-level multiply_rss: scalar measurement * vector
template<pkr::units::is_measurement_c ScalarT, pkr::units::is_measurement_c VecT>
constexpr auto multiply_rss(const ScalarT& scalar, const vec_4d_measurements_rss_t<VecT>& v) {
    using ResultT = decltype(pkr::units::multiply_rss(scalar, v.x));
    return vec_4d_measurements_rss_t<ResultT>{
        pkr::units::multiply_rss(scalar, v.x),
        pkr::units::multiply_rss(scalar, v.y),
        pkr::units::multiply_rss(scalar, v.z),
        pkr::units::multiply_rss(scalar, v.w)
    };
}

// Vector-level multiply_rss: vector * scalar measurement
template<pkr::units::is_measurement_c VecT, pkr::units::is_measurement_c ScalarT>
constexpr auto multiply_rss(const vec_4d_measurements_rss_t<VecT>& v, const ScalarT& scalar) {
    return multiply_rss(scalar, v);
}
// Vector-level subtract_rss for measurement vectors
template<pkr::units::is_measurement_c T1, pkr::units::is_measurement_c T2>
requires same_dimensions_c<typename T1::value_type, typename T2::value_type>
constexpr auto subtract_rss(const vec_4d_measurements_rss_t<T1>& a, const vec_4d_measurements_rss_t<T2>& b) {
    using ResultT = decltype(pkr::units::subtract_rss(a.x, b.x));
    return vec_4d_measurements_rss_t<ResultT>{
        pkr::units::subtract_rss(a.x, b.x),
        pkr::units::subtract_rss(a.y, b.y),
        pkr::units::subtract_rss(a.z, b.z),
        pkr::units::subtract_rss(a.w, b.w)
    };
}

// Vector-level divide_rss: vector / scalar (scalar may be arithmetic or a measurement)
template<pkr::units::is_measurement_c VecT, typename ScalarT>
    requires (std::is_arithmetic_v<ScalarT> || pkr::units::is_measurement_c<ScalarT>)
constexpr auto divide_rss(const vec_4d_measurements_rss_t<VecT>& v, const ScalarT& scalar) {
    using ResultT = decltype(pkr::units::divide_rss(v.x, scalar));
    return vec_4d_measurements_rss_t<ResultT>{
        pkr::units::divide_rss(v.x, scalar),
        pkr::units::divide_rss(v.y, scalar),
        pkr::units::divide_rss(v.z, scalar),
        pkr::units::divide_rss(v.w, scalar)
    };
}template<pkr::units::is_measurement_c T>
constexpr auto dot(const vec_4d_measurements_rss_t<T>& a, const vec_4d_measurements_rss_t<T>& b) noexcept {
    return pkr::units::stable_add(
        pkr::units::stable_add(
            pkr::units::stable_multiply(a.x, b.x),
            pkr::units::stable_multiply(a.y, b.y)
        ),
        pkr::units::stable_add(
            pkr::units::stable_multiply(a.z, b.z),
            pkr::units::stable_multiply(a.w, b.w)
        )
    );
}

} // namespace PKR_UNITS_NAMESPACE