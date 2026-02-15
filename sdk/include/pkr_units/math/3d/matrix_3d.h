#pragma once

#include <array>
#include "vector_3d.h"

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Templated 3x3 Matrix
// ============================================================================

template <typename T>
struct matrix_3d_t
{
public:
    constexpr matrix_3d_t()
        : m_data{}
    {
    }

    constexpr matrix_3d_t(const std::array<std::array<T, 3>, 3>& init)
        : m_data{init}
    {
    }

    // Access operators
    constexpr std::array<T, 3>& operator[](size_t i)
    {
        return m_data[i];
    }

    constexpr const std::array<T, 3>& operator[](size_t i) const
    {
        return m_data[i];
    }

private:
    std::array<std::array<T, 3>, 3> m_data;
};

template <typename T>
constexpr matrix_3d_t<T> identity_3d()
{
    matrix_3d_t<T> m = {};
    for (int i = 0; i < 3; ++i)
    {
        m[i][i] = 1;
    }
    return m;
}

template <typename T>
constexpr vec_3d_t<T> matrix_vector_multiply(const matrix_3d_t<T>& m, const vec_3d_t<T>& v)
{
    return vec_3d_t<T>{
        m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z, m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z, m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z};
}

template <typename T>
constexpr vec_3d_t<T> operator*(const matrix_3d_t<T>& m, const vec_3d_t<T>& v)
{
    return matrix_vector_multiply(m, v);
}

} // namespace PKR_UNITS_NAMESPACE
