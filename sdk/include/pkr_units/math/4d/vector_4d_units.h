#pragma once

#include <type_traits>
#include <utility>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/math/unit/unit_math.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 4D Vector for Units (using stable math)
// ============================================================================

template<is_pkr_unit_c T>
struct vec_4d_units_t {
    T x, y, z, w;

    constexpr vec_4d_units_t() : x{0}, y{0}, z{0}, w{1} {}
    constexpr vec_4d_units_t(T x, T y, T z, T w = 1) : x{x}, y{y}, z{z}, w{w} {}

    constexpr vec_4d_units_t& operator+=(const vec_4d_units_t& other) noexcept {
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        w = w + other.w;
        return *this;
    }

    constexpr vec_4d_units_t& operator-=(const vec_4d_units_t& other) noexcept {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        w = w - other.w;
        return *this;
    }

    // In-place addition/subtraction with different unit types (compatible dimensions)
    template<is_pkr_unit_c OtherT>
    requires same_dimensions_c<T, OtherT>
    constexpr vec_4d_units_t& operator+=(const vec_4d_units_t<OtherT>& other) noexcept {
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        w = w + other.w;
        return *this;
    }

    template<is_pkr_unit_c OtherT>
    requires same_dimensions_c<T, OtherT>
    constexpr vec_4d_units_t& operator-=(const vec_4d_units_t<OtherT>& other) noexcept {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        w = w - other.w;
        return *this;
    }

    template<typename ScalarT>
    requires (std::is_arithmetic_v<ScalarT> || is_pkr_unit_c<ScalarT>)
    constexpr vec_4d_units_t& operator*=(const ScalarT& scalar) noexcept {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        w = w * scalar;
        return *this;
    }

    template<typename ScalarT>
    requires std::is_arithmetic_v<ScalarT>
    constexpr vec_4d_units_t& operator/=(const ScalarT& scalar) noexcept {
        x = x / scalar;
        y = y / scalar;
        z = z / scalar;
        w = w / scalar;
        return *this;
    }
};

template<is_pkr_unit_c T>
constexpr vec_4d_units_t<T> operator+(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept {
    return vec_4d_units_t<T>{
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };
}

template<is_pkr_unit_c T1, is_pkr_unit_c T2>
requires same_dimensions_c<T1, T2>
constexpr auto operator+(const vec_4d_units_t<T1>& a, const vec_4d_units_t<T2>& b) noexcept {
    using ResultT = decltype(a.x + b.x);
    return vec_4d_units_t<ResultT>{
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    };
}

template<is_pkr_unit_c T>
constexpr vec_4d_units_t<T> operator-(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept {
    return vec_4d_units_t<T>{
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    };
}

template<typename ScalarT, is_pkr_unit_c T>
requires (std::is_arithmetic_v<ScalarT> || is_pkr_unit_c<ScalarT>)
constexpr auto operator*(const ScalarT& scalar, const vec_4d_units_t<T>& v) noexcept {
    using ResultT = decltype(scalar * v.x);
    return vec_4d_units_t<ResultT>{scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w};
}

template<typename ScalarT, is_pkr_unit_c T>
requires (std::is_arithmetic_v<ScalarT> || is_pkr_unit_c<ScalarT>)
constexpr auto operator*(const vec_4d_units_t<T>& v, const ScalarT& scalar) noexcept {
    return scalar * v;
}

template<is_pkr_unit_c T>
constexpr auto dot(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept {
    return (a.x * b.x + a.y * b.y) + (a.z * b.z + a.w * b.w);
}

// division by scalar_t
template<is_pkr_unit_c T>
constexpr vec_4d_units_t<T> operator/(const vec_4d_units_t<T>& v, const scalar_t& scalar) noexcept {
    return vec_4d_units_t<T>{
        v.x / scalar,
        v.y / scalar,
        v.z / scalar,
        v.w / scalar
    };
}

// generic scalar_value_c division (float/double for now)
template<is_pkr_unit_c T, scalar_value_c ScalarT>
constexpr auto operator/(const vec_4d_units_t<T>& v, const ScalarT& scalar) noexcept {
    using ResultT = decltype(v.x / scalar);
    return vec_4d_units_t<ResultT>{ v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar };
}

// division by unit type (e.g., vec_4d_units_t<km> / second_t = vec_4d_units_t<km/s>)
template<is_pkr_unit_c T, is_pkr_unit_c ScalarUnit>
constexpr auto operator/(const vec_4d_units_t<T>& v, const ScalarUnit& scalar) noexcept {
    using ResultT = decltype(v.x / scalar);
    return vec_4d_units_t<ResultT>{ v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar };
}

// keep double division as convenience
template<is_pkr_unit_c T>
constexpr vec_4d_units_t<T> operator/(const vec_4d_units_t<T>& v, double scalar) noexcept {
    return v / scalar_t{scalar};
}

// Vector-level stable_add for unit vectors (works with compatible unit element types)
template<is_pkr_unit_c T1, is_pkr_unit_c T2>
requires same_dimensions_c<T1, T2>
constexpr auto stable_add(const vec_4d_units_t<T1>& a, const vec_4d_units_t<T2>& b) {
    return a + b;
}

// Vector-level stable_multiply: scalar * vector
template<is_unit_value_type_c ScalarT, is_pkr_unit_c VecT>
constexpr auto stable_multiply(const ScalarT& scalar, const vec_4d_units_t<VecT>& v) {
    return scalar * v;
}

// Vector-level stable_multiply: vector * scalar
template<is_pkr_unit_c VecT, is_unit_value_type_c ScalarT>
constexpr auto stable_multiply(const vec_4d_units_t<VecT>& v, const ScalarT& scalar) {
    return v * scalar;
}

// Vector-level stable_multiply: unit scalar * vector (both are unit types)
template<is_pkr_unit_c ScalarUnit, is_pkr_unit_c VecT>
constexpr auto stable_multiply(const ScalarUnit& scalar, const vec_4d_units_t<VecT>& v) {
    return scalar * v;
}

// Vector-level stable_multiply: vector * unit scalar
template<is_pkr_unit_c VecT, is_pkr_unit_c ScalarUnit>
constexpr auto stable_multiply(const vec_4d_units_t<VecT>& v, const ScalarUnit& scalar) {
    return v * scalar;
}

// Vector-level stable_subtract for unit vectors (works with compatible unit element types)
template<is_pkr_unit_c T1, is_pkr_unit_c T2>
requires same_dimensions_c<T1, T2>
constexpr auto stable_subtract(const vec_4d_units_t<T1>& a, const vec_4d_units_t<T2>& b) {
    return a - b;
}

// Vector-level stable_divide: vector / scalar
template<is_pkr_unit_c VecT, is_unit_value_type_c ScalarT>
constexpr auto stable_divide(const vec_4d_units_t<VecT>& v, const ScalarT& scalar) {
    return v / scalar;
}
template<is_pkr_unit_c T>
constexpr vec_4d_units_t<T> operator-(const vec_4d_units_t<T>& v) noexcept {
    return vec_4d_units_t<T>{
        T{-v.x.value()},
        T{-v.y.value()},
        T{-v.z.value()},
        T{-v.w.value()}
    };
}

template<is_pkr_unit_c T>
constexpr bool operator==(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

} // namespace PKR_UNITS_NAMESPACE