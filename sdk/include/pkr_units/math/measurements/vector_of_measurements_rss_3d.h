#pragma once

#include <pkr_units/measurements.h>
#include <pkr_units/math/unit/unit_math.h>
#include "vector_3d.h"

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 3D Vector for Measurements (using RSS uncertainty propagation)
// ============================================================================

template <pkr::units::is_measurement_c T>
struct vec_3d_t<T>
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

    constexpr vec_3d_t& operator+=(const vec_3d_t& other) noexcept
    {
        x = pkr::math::add_rss(x, other.x);
        y = pkr::math::add_rss(y, other.y);
        z = pkr::math::add_rss(z, other.z);
        return *this;
    }

    constexpr vec_3d_t& operator-=(const vec_3d_t& other) noexcept
    {
        x = pkr::math::subtract_rss(x, other.x);
        y = pkr::math::subtract_rss(y, other.y);
        z = pkr::math::subtract_rss(z, other.z);
        return *this;
    }

    constexpr vec_3d_t& operator*=(double scalar) noexcept
    {
        x = pkr::math::multiply_rss(x, scalar);
        y = pkr::math::multiply_rss(y, scalar);
        z = pkr::math::multiply_rss(z, scalar);
        return *this;
    }

    constexpr vec_3d_t& operator/=(double scalar) noexcept
    {
        x = pkr::units::divide_rss(x, scalar);
        y = pkr::units::divide_rss(y, scalar);
        z = pkr::units::divide_rss(z, scalar);
        return *this;
    }
};

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator+(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return vec_3d_t<T>{pkr::math::add_rss(a.x, b.x), pkr::math::add_rss(a.y, b.y), pkr::math::add_rss(a.z, b.z)};
}

template <pkr::units::is_measurement_c T1, pkr::units::is_measurement_c T2>
    requires same_dimensions_c<T1::value_type, T2::value_type>
constexpr auto operator+(const vec_3d_t<T1>& a, const vec_3d_t<T2>& b) noexcept
{
    using ResultT = decltype(a.x + b.x);
    return vec_3d_t<ResultT>{pkr::math::add_rss(a.x, b.x), pkr::math::add_rss(a.y, b.y), pkr::math::add_rss(a.z, b.z)};
}

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator-(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return vec_3d_t<T>{pkr::math::subtract_rss(a.x, b.x), pkr::math::subtract_rss(a.y, b.y), pkr::math::subtract_rss(a.z, b.z)};
}

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator*(double scalar, const vec_3d_t<T>& v) noexcept
{
    return vec_3d_t<T>{pkr::math::multiply_rss(scalar, v.x), pkr::math::multiply_rss(scalar, v.y), pkr::math::multiply_rss(scalar, v.z)};
}

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator*(const vec_3d_t<T>& v, double scalar) noexcept
{
    return scalar * v;
}

template <pkr::units::is_measurement_c ScalarT, pkr::units::is_measurement_c VecT>
constexpr vec_3d_t<decltype(pkr::units::multiply_rss(std::declval<ScalarT>(), std::declval<VecT>()))> operator*(const ScalarT& scalar, const vec_3d_t<VecT>& v)
{
    auto result_x = pkr::units::multiply_rss(scalar, v.x);
    auto result_y = pkr::units::multiply_rss(scalar, v.y);
    auto result_z = pkr::units::multiply_rss(scalar, v.z);
    return {result_x, result_y, result_z};
}

template <pkr::units::is_measurement_c VecT, pkr::units::is_measurement_c ScalarT>
constexpr vec_3d_t<decltype(pkr::units::multiply_rss(std::declval<VecT>(), std::declval<ScalarT>()))> operator*(const vec_3d_t<VecT>& v, const ScalarT& scalar)
{
    auto result_x = pkr::units::multiply_rss(v.x, scalar);
    auto result_y = pkr::units::multiply_rss(v.y, scalar);
    auto result_z = pkr::units::multiply_rss(v.z, scalar);
    return {result_x, result_y, result_z};
}

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator/(const vec_3d_t<T>& v, double scalar) noexcept
{
    return vec_3d_t<T>{pkr::units::divide_rss(v.x, scalar), pkr::units::divide_rss(v.y, scalar), pkr::units::divide_rss(v.z, scalar)};
}

template <pkr::units::is_measurement_c T>
constexpr auto dot(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return pkr::units::add_rss(pkr::units::add_rss(pkr::units::multiply_rss(a.x, b.x), pkr::units::multiply_rss(a.y, b.y)), pkr::units::multiply_rss(a.z, b.z));
}

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> cross(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return vec_3d_t<T>{
        pkr::units::subtract_rss(pkr::units::multiply_rss(a.y, b.z), pkr::units::multiply_rss(a.z, b.y)),
        pkr::units::subtract_rss(pkr::units::multiply_rss(a.z, b.x), pkr::units::multiply_rss(a.x, b.z)),
        pkr::units::subtract_rss(pkr::units::multiply_rss(a.x, b.y), pkr::units::multiply_rss(a.y, b.x))};
}

} // namespace PKR_UNITS_NAMESPACE
