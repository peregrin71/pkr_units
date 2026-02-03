#pragma once
#include <type_traits>
#include <utility>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/units/dimensionless/scalar.h>
namespace PKR_UNITS_NAMESPACE
{
// ============================================================================
// Specialized 4D Vector for Units (using stable math)
// ============================================================================
template <is_base_pkr_unit_c T>
struct vec_4d_t<T>
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
    constexpr vec_4d_t& operator+=(const vec_4d_t& other) noexcept
    {
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        w = w + other.w;
        return *this;
    }
    constexpr vec_4d_t& operator-=(const vec_4d_t& other) noexcept
    {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        w = w - other.w;
        return *this;
    }
    template <scalar_value_c ScalarT>
    constexpr vec_4d_t& operator*=(const ScalarT& scalar) noexcept
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        w = w * scalar;
        return *this;
    }
    template <scalar_value_c ScalarT>
    constexpr vec_4d_t& operator/=(const ScalarT& scalar) noexcept
    {
        x = x / scalar;
        y = y / scalar;
        z = z / scalar;
        w = w / scalar;
        return *this;
    }
    // scalar_t overloads
    constexpr vec_4d_t& operator*=(const typename T::value_type& scalar) noexcept
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        w = w * scalar;
        return *this;
    }
    constexpr vec_4d_t& operator/=(const typename T::value_type& scalar) noexcept
    {
        x = x / scalar;
        y = y / scalar;
        z = z / scalar;
        w = w / scalar;
        return *this;
    }
};

template <is_base_pkr_unit_c T>
constexpr vec_4d_t<T> operator+(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept
{
    return vec_4d_t<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}
template <is_base_pkr_unit_c T1, is_base_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>
constexpr auto operator+(const vec_4d_t<T1>& a, const vec_4d_t<T2>& b) noexcept
{
    using ResultT = decltype(a.x + b.x);
    return vec_4d_t<ResultT>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}
template <is_base_pkr_unit_c T>
constexpr vec_4d_t<T> operator-(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept
{
    return vec_4d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}
template <scalar_value_c ScalarT, is_base_pkr_unit_c T>
constexpr auto operator*(const ScalarT& scalar, const vec_4d_t<T>& v) noexcept
{
    using ResultT = decltype(scalar * v.x);
    return vec_4d_t<ResultT>{scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w};
}
template <is_base_pkr_unit_c T, scalar_value_c ScalarT>
constexpr auto operator*(const vec_4d_t<T>& v, const ScalarT& scalar)
{
    return scalar * v;
}
// scalar_t overloads
template <is_base_pkr_unit_c T>
constexpr vec_4d_t<T> operator*(const typename T::value_type& scalar, const vec_4d_t<T>& v) noexcept
{
    return vec_4d_t<T>{scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w};
}
template <is_base_pkr_unit_c T>
constexpr vec_4d_t<T> operator*(const vec_4d_t<T>& v, const typename T::value_type& scalar) noexcept
{
    return scalar * v;
}
// division by scalar_t
template <is_base_pkr_unit_c T>
constexpr vec_4d_t<T> operator/(const vec_4d_t<T>& v, const typename T::value_type& scalar) noexcept
{
    return vec_4d_t<T>{v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar};
}
template <is_base_pkr_unit_c T, scalar_value_c ScalarT>
constexpr auto operator/(const vec_4d_t<T>& v, const ScalarT& scalar) noexcept
{
    using ResultT = decltype(v.x / scalar);
    return vec_4d_t<ResultT>{v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar};
}
template <is_base_pkr_unit_c T>
constexpr auto dot(const vec_4d_t<T>& a, const vec_4d_t<T>& b) noexcept
{
    // Use unit operators directly; addition combines units appropriately
    return (a.x * b.x + a.y * b.y) + (a.z * b.z + a.w * b.w);
}
} // namespace PKR_UNITS_NAMESPACE
