#pragma once

#include <array>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>
#include <pkr_units/units/math/matrix_storage_policies.h>
#include "vector_measurement_rss_4d.h"

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Specialized 4x4 Matrix for Measurements (using RSS uncertainty propagation)
// StoragePolicy parameter allows stack or arena-based allocation
// Default: stack_storage (zero overhead, current behavior)
// ============================================================================

template <pkr::units::is_pkr_unit_c T, typename StoragePolicy = stack_storage<pkr::units::measurement_rss_t<T>>>
class matrix_measurement_rss_4d_t
{
public:
    using value_type = pkr::units::measurement_rss_t<T>;
    using storage_type = StoragePolicy;
    using array_type = std::array<std::array<value_type, 4>, 4>;

    storage_type storage;

    constexpr matrix_measurement_rss_4d_t() = default;

    constexpr matrix_measurement_rss_4d_t(const array_type& arr)
    {
        for (std::size_t r = 0; r < 4; ++r)
        {
            for (std::size_t c = 0; c < 4; ++c)
            {
                storage.get(r, c) = arr[r][c];
            }
        }
    }

    constexpr value_type& operator()(std::size_t row, std::size_t col)
    {
        return storage.get(row, col);
    }

    constexpr const value_type& operator()(std::size_t row, std::size_t col) const
    {
        return storage.get(row, col);
    }

    constexpr std::array<value_type, 4>& operator[](std::size_t row)
    {
        return storage[row];
    }

    constexpr const std::array<value_type, 4>& operator[](std::size_t row) const
    {
        return storage[row];
    }
};

template <pkr::units::is_pkr_unit_c T>
constexpr matrix_measurement_rss_4d_t<T> identity_4d()
{
    matrix_measurement_rss_4d_t<T> m{};
    for (size_t i = 0; i < 4; ++i)
    {
        m[i][i] = typename matrix_measurement_rss_4d_t<T>::value_type{1.0, 0.0};
    }
    return m;
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_4d_t<T> matrix_vector_multiply(const matrix_measurement_rss_4d_t<T>& m, const vec_measurement_rss_4d_t<T>& v) noexcept
{
    auto r0 = (m.data[0][0] * v.x) + (m.data[0][1] * v.y) + (m.data[0][2] * v.z) + (m.data[0][3] * v.w);
    auto r1 = (m.data[1][0] * v.x) + (m.data[1][1] * v.y) + (m.data[1][2] * v.z) + (m.data[1][3] * v.w);
    auto r2 = (m.data[2][0] * v.x) + (m.data[2][1] * v.y) + (m.data[2][2] * v.z) + (m.data[2][3] * v.w);
    auto r3 = (m.data[3][0] * v.x) + (m.data[3][1] * v.y) + (m.data[3][2] * v.z) + (m.data[3][3] * v.w);
    return vec_measurement_rss_4d_t<T>{r0, r1, r2, r3};
}

template <pkr::units::is_pkr_unit_c T>
constexpr vec_measurement_rss_4d_t<T> operator*(const matrix_measurement_rss_4d_t<T>& m, const vec_measurement_rss_4d_t<T>& v) noexcept
{
    return matrix_vector_multiply(m, v);
}

} // namespace PKR_UNITS_NAMESPACE
