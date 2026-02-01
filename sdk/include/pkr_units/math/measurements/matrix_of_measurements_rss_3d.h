#pragma once

#include <array>
#include <pkr_units/measurements.h>
#include <pkr_units/math/unit/unit_math.h>
#include "vector_of_measurements_rss_3d.h"

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 3x3 Matrix for Measurements (using RSS uncertainty propagation)
// ============================================================================

template <pkr::units::is_measurement_c T>
class matrix_3d_measurements_t
{
public:
    using value_type = T;
    using array_type = std::array<std::array<T, 3>, 3>;

    array_type data;

    constexpr matrix_3d_measurements_t() = default;

    constexpr matrix_3d_measurements_t(const array_type& arr)
        : data(arr)
    {
    }

    constexpr matrix_3d_measurements_t(std::initializer_list<std::initializer_list<T>> list)
    {
        auto row_it = list.begin();
        for (size_t i = 0; i < 3 && row_it != list.end(); ++i, ++row_it)
        {
            auto col_it = row_it->begin();
            for (size_t j = 0; j < 3 && col_it != row_it->end(); ++j, ++col_it)
            {
                data[i][j] = *col_it;
            }
        }
    }

    constexpr T& operator()(size_t row, size_t col)
    {
        return data[row][col];
    }

    constexpr const T& operator()(size_t row, size_t col) const
    {
        return data[row][col];
    }

    constexpr std::array<T, 3>& operator[](size_t row)
    {
        return data[row];
    }

    constexpr const std::array<T, 3>& operator[](size_t row) const
    {
        return data[row];
    }
};

template <pkr::units::is_measurement_c T>
constexpr matrix_3d_measurements_t<T> identity_3d()
{
    matrix_3d_measurements_t<T> m{};
    for (int i = 0; i < 3; ++i)
        m[i][i] = T{1};
    return m;
}

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> matrix_vector_multiply(const matrix_3d_measurements_t<T>& m, const vec_3d_t<T>& v) noexcept
{
    return vec_3d_t<T>{
        pkr::units::add_rss(
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[0][0], v.x), pkr::units::multiply_rss(m.data[0][1], v.y)),
            pkr::units::multiply_rss(m.data[0][2], v.z)),
        pkr::units::add_rss(
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[1][0], v.x), pkr::units::multiply_rss(m.data[1][1], v.y)),
            pkr::units::multiply_rss(m.data[1][2], v.z)),
        pkr::units::add_rss(
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[2][0], v.x), pkr::units::multiply_rss(m.data[2][1], v.y)),
            pkr::units::multiply_rss(m.data[2][2], v.z))};
}

template <pkr::units::is_measurement_c T>
constexpr vec_3d_t<T> operator*(const matrix_3d_measurements_t<T>& m, const vec_3d_t<T>& v) noexcept
{
    return matrix_vector_multiply(m, v);
}

} // namespace PKR_UNITS_NAMESPACE
