#pragma once

#include <array>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/measurements/decl/measurement_lin_decl.h>
#include "vector_measurement_lin_3d.h"

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 3x3 Matrix for Linear Measurements with linear uncertainty propagation
// ============================================================================

template <pkr::units::is_pkr_unit_c T>
class matrix_measurement_lin_3d_t
{
public:
    using value_type = pkr::units::measurement_lin_t<T>;
    using array_type = std::array<std::array<value_type, 3>, 3>;

    array_type data;

    constexpr matrix_measurement_lin_3d_t() = default;

    constexpr matrix_measurement_lin_3d_t(const array_type& arr)
        : data(arr)
    {
    }

    constexpr value_type& operator()(size_t row, size_t col)
    {
        return data[row][col];
    }

    constexpr const value_type& operator()(size_t row, size_t col) const
    {
        return data[row][col];
    }

    constexpr std::array<value_type, 3>& operator[](size_t row)
    {
        return data[row];
    }

    constexpr const std::array<value_type, 3>& operator[](size_t row) const
    {
        return data[row];
    }
};

template <pkr::units::is_pkr_unit_c T>
constexpr matrix_measurement_lin_3d_t<T> identity_3d()
{
    matrix_measurement_lin_3d_t<T> m{};
    for (size_t i = 0; i < 3; ++i)
    {
        m[i][i] = typename matrix_measurement_lin_3d_t<T>::value_type{1.0, 0.0};
    }
    return m;
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_lin_3d_t<T> matrix_vector_multiply(const matrix_measurement_lin_3d_t<T>& m, const vec_measurement_lin_3d_t<T>& v) noexcept
{
    auto r0 = (m.data[0][0] * v.x) + (m.data[0][1] * v.y) + (m.data[0][2] * v.z);
    auto r1 = (m.data[1][0] * v.x) + (m.data[1][1] * v.y) + (m.data[1][2] * v.z);
    auto r2 = (m.data[2][0] * v.x) + (m.data[2][1] * v.y) + (m.data[2][2] * v.z);
    return vec_measurement_lin_3d_t<T>{r0, r1, r2};
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_lin_3d_t<T> operator*(const matrix_measurement_lin_3d_t<T>& m, const vec_measurement_lin_3d_t<T>& v) noexcept
{
    return matrix_vector_multiply(m, v);
}

} // namespace PKR_UNITS_NAMESPACE
