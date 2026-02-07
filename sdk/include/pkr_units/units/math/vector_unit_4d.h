#pragma once
#include <type_traits>
#include <utility>
#include <cmath>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/math/unit_math.h>

namespace PKR_UNITS_NAMESPACE
{
// ============================================================================
// Specialized 4D Vector for Units (using stable math)
// ============================================================================
template <is_pkr_unit_c T>
struct vec_4d_units_t
{
    T x, y, z, w;

    constexpr vec_4d_units_t()
        : x{0}
        , y{0}
        , z{0}
        , w{1}
    {
    }

    constexpr vec_4d_units_t(T x_value, T y_value, T z_value, T w_value = 1)
        : x{x_value}
        , y{y_value}
        , z{z_value}
        , w{w_value}
    {
    }

    // Template constructor: accept any pkr_unit type and construct from its value
    template <typename U>
        requires(is_pkr_unit_c<U> && !std::is_same_v<U, T>)
    constexpr vec_4d_units_t(U x_value, U y_value, U z_value, U w_value = U{1})
        : x{T{x_value.value()}}
        , y{T{y_value.value()}}
        , z{T{z_value.value()}}
        , w{T{w_value.value()}}
    {
    }

    // Template constructor: accept scalar values and construct units from them
    template <typename ScalarT>
        requires scalar_value_c<ScalarT>
    constexpr vec_4d_units_t(ScalarT x_value, ScalarT y_value, ScalarT z_value, ScalarT w_value = 1)
        : x{T{x_value}}
        , y{T{y_value}}
        , z{T{z_value}}
        , w{T{w_value}}
    {
    }

    constexpr vec_4d_units_t& operator+=(const vec_4d_units_t& other) noexcept
    {
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        w = w + other.w;
        return *this;
    }

    constexpr vec_4d_units_t& operator-=(const vec_4d_units_t& other) noexcept
    {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        w = w - other.w;
        return *this;
    }

    // In-place addition/subtraction with different unit types (compatible dimensions)
    template <is_base_pkr_unit_c OtherT>
        requires same_dimensions_c<T, OtherT>
    constexpr vec_4d_units_t& operator+=(const vec_4d_units_t<OtherT>& other) noexcept
    {
        x = x + other.x;
        y = y + other.y;
        z = z + other.z;
        w = w + other.w;
        return *this;
    }

    template <is_base_pkr_unit_c OtherT>
        requires same_dimensions_c<T, OtherT>
    constexpr vec_4d_units_t& operator-=(const vec_4d_units_t<OtherT>& other) noexcept
    {
        x = x - other.x;
        y = y - other.y;
        z = z - other.z;
        w = w - other.w;
        return *this;
    }

    template <typename Factor>
        requires(scalar_value_c<Factor> || is_pkr_unit_c<Factor>)
    constexpr vec_4d_units_t& operator*=(const Factor& value) noexcept
    {
        x = x * value;
        y = y * value;
        z = z * value;
        w = w * value;
        return *this;
    }

    template <typename Factor>
        requires scalar_value_c<Factor>
    constexpr vec_4d_units_t& operator/=(const Factor& value) noexcept
    {
        x = x / value;
        y = y / value;
        z = z / value;
        w = w / value;
        return *this;
    }

    // Calculate the magnitude (length) of the 4D vector
    constexpr T magnitude() const noexcept
    {
        auto sum_of_squares = (x * x + y * y) + (z * z + w * w);
        // Extract the underlying scalar value, take sqrt, and construct result unit
        auto scalar_value = sum_of_squares.value();
        using value_type = typename details::is_pkr_unit<T>::value_type;
        auto sqrt_value = static_cast<value_type>(std::sqrt(static_cast<double>(scalar_value)));
        return T{sqrt_value};
    }
};

template <is_pkr_unit_c T>
constexpr auto operator+(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept
{
    auto x_result = a.x + b.x;
    auto y_result = a.y + b.y;
    auto z_result = a.z + b.z;
    auto w_result = a.w + b.w;
    return vec_4d_units_t<decltype(x_result)>{x_result, y_result, z_result, w_result};
}

template <is_pkr_unit_c T1, is_pkr_unit_c T2>
    requires same_dimensions_c<T1, T2>
constexpr auto operator+(const vec_4d_units_t<T1>& a, const vec_4d_units_t<T2>& b) noexcept
{
    using ResultT = decltype(a.x + b.x);
    return vec_4d_units_t<ResultT>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

template <is_pkr_unit_c T>
constexpr auto operator-(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept
{
    auto x_result = a.x - b.x;
    auto y_result = a.y - b.y;
    auto z_result = a.z - b.z;
    auto w_result = a.w - b.w;
    return vec_4d_units_t<decltype(x_result)>{x_result, y_result, z_result, w_result};
}

template <typename T, is_pkr_unit_c U>
    requires(scalar_value_c<T> || is_pkr_unit_c<T>)
constexpr auto operator*(const T& value, const vec_4d_units_t<U>& v) noexcept
{
    using ResultT = decltype(value * v.x);
    return vec_4d_units_t<ResultT>{value * v.x, value * v.y, value * v.z, value * v.w};
}

template <is_pkr_unit_c U, typename T>
    requires(scalar_value_c<T> || is_pkr_unit_c<T>)
constexpr auto operator*(const vec_4d_units_t<U>& v, const T& value) noexcept
{
    return value * v;
}

template <is_pkr_unit_c T>
constexpr auto dot(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept
{
    return (a.x * b.x + a.y * b.y) + (a.z * b.z + a.w * b.w);
}

// division by scalar or unit type
template <is_pkr_unit_c U, typename T>
    requires(scalar_value_c<T> || is_pkr_unit_c<T>)
constexpr auto operator/(const vec_4d_units_t<U>& v, const T& value) noexcept
{
    using ResultT = decltype(v.x / value);
    return vec_4d_units_t<ResultT>{v.x / value, v.y / value, v.z / value, v.w / value};
}

// scalar or unit divided by vector (reciprocal scaling)
template <typename T, is_pkr_unit_c U>
    requires(scalar_value_c<T> || is_pkr_unit_c<T>)
constexpr auto operator/(const T& value, const vec_4d_units_t<U>& v) noexcept
{
    using ResultT = decltype(value / v.x);
    return vec_4d_units_t<ResultT>{value / v.x, value / v.y, value / v.z, value / v.w};
}

// negation operator
template <is_pkr_unit_c T>
constexpr vec_4d_units_t<T> operator-(const vec_4d_units_t<T>& v) noexcept
{
    return vec_4d_units_t<T>{-v.x, -v.y, -v.z, -v.w};
}

// equality operator
template <is_pkr_unit_c T>
constexpr bool operator==(const vec_4d_units_t<T>& a, const vec_4d_units_t<T>& b) noexcept
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
} // namespace PKR_UNITS_NAMESPACE
