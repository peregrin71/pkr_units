#pragma once

#include <type_traits>
#include <utility>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

#include <pkr_units/math/unit/unit_math.h>

// ============================================================================
// Specialized 3D Vector for Units (using stable math)
// ============================================================================

template <is_base_pkr_unit_c T>
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
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        return *this;
    }

    constexpr vec_3d_t& operator-=(const vec_3d_t& other) noexcept
    {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        return *this;
    }

    template <typename ScalarT>
        requires(std::is_arithmetic_v<ScalarT> || is_base_pkr_unit_c<ScalarT>)
    constexpr vec_3d_t& operator*=(const ScalarT& scalar) noexcept
    {
        x = x * scalar;
        y = y * scalar;
        z = z * scalar;
        return *this;
    }

    template <typename ScalarT>
        requires std::is_arithmetic_v<ScalarT>
    constexpr vec_3d_t& operator/=(const ScalarT& scalar) noexcept
    {
        x = x / scalar;
        y = y / scalar;
        z = z / scalar;
        return *this;
    }
};

constexpr vec_3d_t<T> operator+(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return vec_3d_t<T>{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <is_base_pkr_unit_c T1, is_base_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>
constexpr auto operator+(const vec_3d_t<T1>& a, const vec_3d_t<T2>& b) noexcept
{
    using ResultT = decltype(a.x + b.x);
    return vec_3d_t<ResultT>{a.x + b.x, a.y + b.y, a.z + b.z};
}

constexpr vec_3d_t<T> operator-(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return vec_3d_t<T>{a.x - b.x, a.y - b.y, a.z - b.z};
}

constexpr vec_3d_t<T> operator*(double scalar, const vec_3d_t<T>& v) noexcept
{
    return vec_3d_t<T>{scalar * v.x, scalar * v.y, scalar * v.z};
}

template <is_base_pkr_unit_c T>
constexpr vec_3d_t<T> operator*(const vec_3d_t<T>& v, double scalar) noexcept
{
    return scalar * v;
}

constexpr auto dot(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

constexpr vec_3d_t<T> cross(const vec_3d_t<T>& a, const vec_3d_t<T>& b) noexcept
{
    return vec_3d_t<T>{(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)};
}

} // namespace PKR_UNITS_NAMESPACE
