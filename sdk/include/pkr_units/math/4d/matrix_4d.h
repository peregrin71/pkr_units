#pragma once

#include <array>
#include "vector_4d.h"

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Templated 4x4 Matrix
// ============================================================================

template <typename T>
struct matrix_4d_t
{
public:
    constexpr matrix_4d_t()
        : m_data{}
    {
    }

    constexpr matrix_4d_t(const std::array<std::array<T, 4>, 4>& init)
        : m_data{init}
    {
    }

    // Access operators
    constexpr std::array<T, 4>& operator[](size_t i)
    {
        return m_data[i];
    }

    constexpr const std::array<T, 4>& operator[](size_t i) const
    {
        return m_data[i];
    }

private:
    std::array<std::array<T, 4>, 4> m_data;
};

template <typename T>
constexpr matrix_4d_t<T> identity_4d()
{
    matrix_4d_t<T> m = {};
    for (int i = 0; i < 4; ++i)
        m[i][i] = 1;
    return m;
}

template <typename T>
constexpr vec_4d_t<T> matrix_vector_multiply(const matrix_4d_t<T>& m, const vec_4d_t<T>& v)
{
    return vec_4d_t<T>{
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
        m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
        m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
        m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w};
}

template <typename T>
constexpr vec_4d_t<T> operator*(const matrix_4d_t<T>& m, const vec_4d_t<T>& v)
{
    return matrix_vector_multiply(m, v);
}

} // namespace PKR_UNITS_NAMESPACE
