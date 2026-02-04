#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

namespace PKR_UNITS_NAMESPACE
{
// ============================================================================
// Specialized 4x4 Matrix for Units (using stable math)
// ============================================================================
template <is_base_pkr_unit_c T>
class matrix_4d_units_t
{
public:
    using value_type = T;
    using array_type = std::array<std::array<T, 4>, 4>;
    array_type data;
    constexpr matrix_4d_units_t() = default;

    constexpr matrix_4d_units_t(const array_type& arr)
        : data(arr)
    {
    }

    constexpr T& operator()(size_t row, size_t col)
    {
        return data[row][col];
    }

    constexpr const T& operator()(size_t row, size_t col) const
    {
        return data[row][col];
    }

    constexpr std::array<T, 4>& operator[](size_t row)
    {
        return data[row];
    }

    constexpr const std::array<T, 4>& operator[](size_t row) const
    {
        return data[row];
    }
};

template <is_base_pkr_unit_c T>
constexpr matrix_4d_units_t<T> identity_4d()
{
    matrix_4d_units_t<T> m{};
    for (int i = 0; i < 4; ++i)
        m[i][i] = T{1};
    return m;
}

template <is_base_pkr_unit_c T>
constexpr vec_4d_t<T> matrix_vector_multiply(const matrix_4d_units_t<T>& m, const vec_4d_t<T>& v) noexcept
{
    return vec_4d_t<T>{
        ((m.data[0][0] * v.x) + (m.data[0][1] * v.y)) + ((m.data[0][2] * v.z) + (m.data[0][3] * v.w)),
        ((m.data[1][0] * v.x) + (m.data[1][1] * v.y)) + ((m.data[1][2] * v.z) + (m.data[1][3] * v.w)),
        ((m.data[2][0] * v.x) + (m.data[2][1] * v.y)) + ((m.data[2][2] * v.z) + (m.data[2][3] * v.w)),
        ((m.data[3][0] * v.x) + (m.data[3][1] * v.y)) + ((m.data[3][2] * v.z) + (m.data[3][3] * v.w))};
}

template <is_base_pkr_unit_c T>
constexpr vec_4d_t<T> operator*(const matrix_4d_units_t<T>& m, const vec_4d_t<T>& v) noexcept
{
    return matrix_vector_multiply(m, v);
}
} // namespace PKR_UNITS_NAMESPACE
