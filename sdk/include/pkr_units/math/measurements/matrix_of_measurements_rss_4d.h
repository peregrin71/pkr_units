#pragma once

#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 4x4 Matrix for Measurements (using RSS uncertainty propagation)
// ============================================================================

template <pkr::units::is_pkr_unit_c T>
class matrix_4d_measurements_t
{
public:
    using value_type = pkr::units::measurement_t<T>;
    using array_type = std::array<std::array<pkr::units::measurement_t<T>, 4>, 4>;

    array_type data;

    constexpr matrix_4d_measurements_t() = default;

    constexpr matrix_4d_measurements_t(const array_type& arr)
        : data(arr)
    {
    }

    constexpr pkr::units::measurement_t<T>& operator()(size_t row, size_t col)
    {
        return data[row][col];
    }

    constexpr const pkr::units::measurement_t<T>& operator()(size_t row, size_t col) const
    {
        return data[row][col];
    }

    constexpr std::array<pkr::units::measurement_t<T>, 4>& operator[](size_t row)
    {
        return data[row];
    }

    constexpr const std::array<pkr::units::measurement_t<T>, 4>& operator[](size_t row) const
    {
        return data[row];
    }
};

template <pkr::units::is_measurement_c T>
constexpr matrix_4d_measurements_t<T> identity_4d()
{
    matrix_4d_measurements_t<T> m{};
    for (int i = 0; i < 4; ++i)
        m[i][i] = T{1};
    return m;
}

template <pkr::units::is_measurement_c T>
constexpr vec_measurement_rss_4d_t<T> matrix_vector_multiply(const matrix_4d_measurements_t<T>& m, const vec_measurement_rss_4d_t<T>& v) noexcept
{
    return vec_measurement_rss_4d_t<T>{
        pkr::units::add_rss(
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[0][0], v.x), pkr::units::multiply_rss(m.data[0][1], v.y)),
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[0][2], v.z), pkr::units::multiply_rss(m.data[0][3], v.w))),
        pkr::units::add_rss(
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[1][0], v.x), pkr::units::multiply_rss(m.data[1][1], v.y)),
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[1][2], v.z), pkr::units::multiply_rss(m.data[1][3], v.w))),
        pkr::units::add_rss(
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[2][0], v.x), pkr::units::multiply_rss(m.data[2][1], v.y)),
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[2][2], v.z), pkr::units::multiply_rss(m.data[2][3], v.w))),
        pkr::units::add_rss(
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[3][0], v.x), pkr::units::multiply_rss(m.data[3][1], v.y)),
            pkr::units::add_rss(pkr::units::multiply_rss(m.data[3][2], v.z), pkr::units::multiply_rss(m.data[3][3], v.w)))};
}

template <pkr::units::is_measurement_c T>
constexpr vec_measurement_rss_4d_t<T> operator*(const matrix_4d_measurements_t<T>& m, const vec_measurement_rss_4d_t<T>& v) noexcept
{
    return matrix_vector_multiply(m, v);
}

} // namespace PKR_UNITS_NAMESPACE
