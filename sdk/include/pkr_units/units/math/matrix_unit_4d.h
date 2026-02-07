#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/math/matrix_storage_policies.h>

namespace PKR_UNITS_NAMESPACE
{
// ============================================================================
// Specialized 4x4 Matrix for Units (using stable math)
// StoragePolicy parameter allows stack or arena-based allocation
// Default: stack_storage (zero overhead, current behavior)
// ============================================================================
template <is_base_pkr_unit_c T, typename StoragePolicy = stack_storage<T>>
class matrix_4d_units_t
{
public:
    using value_type = T;
    using storage_type = StoragePolicy;
    using array_type = std::array<std::array<T, 4>, 4>;

    storage_type storage;

    constexpr matrix_4d_units_t() = default;

    constexpr matrix_4d_units_t(const array_type& arr)
    {
        for (std::size_t r = 0; r < 4; ++r)
        {
            for (std::size_t c = 0; c < 4; ++c)
            {
                storage.get(r, c) = arr[r][c];
            }
        }
    }

    constexpr T& operator()(std::size_t row, std::size_t col)
    {
        return storage.get(row, col);
    }

    constexpr const T& operator()(std::size_t row, std::size_t col) const
    {
        return storage.get(row, col);
    }

    constexpr std::array<T, 4>& operator[](std::size_t row)
    {
        return storage[row];
    }

    constexpr const std::array<T, 4>& operator[](std::size_t row) const
    {
        return storage[row];
    }
};

template <is_base_pkr_unit_c T, typename StoragePolicy = stack_storage<T>>
constexpr matrix_4d_units_t<T, StoragePolicy> identity_4d()
{
    matrix_4d_units_t<T, StoragePolicy> m{};
    for (std::size_t i = 0; i < 4; ++i)
        m[i][i] = T{1};
    return m;
}

template <is_base_pkr_unit_c T, typename StoragePolicy = stack_storage<T>>
constexpr vec_4d_t<T> matrix_vector_multiply(const matrix_4d_units_t<T, StoragePolicy>& m, const vec_4d_t<T>& v) noexcept
{
    return vec_4d_t<T>{
        ((m(0, 0) * v.x) + (m(0, 1) * v.y)) + ((m(0, 2) * v.z) + (m(0, 3) * v.w)),
        ((m(1, 0) * v.x) + (m(1, 1) * v.y)) + ((m(1, 2) * v.z) + (m(1, 3) * v.w)),
        ((m(2, 0) * v.x) + (m(2, 1) * v.y)) + ((m(2, 2) * v.z) + (m(2, 3) * v.w)),
        ((m(3, 0) * v.x) + (m(3, 1) * v.y)) + ((m(3, 2) * v.z) + (m(3, 3) * v.w))};
}

template <is_base_pkr_unit_c T, typename StoragePolicy = stack_storage<T>>
constexpr vec_4d_t<T> operator*(const matrix_4d_units_t<T, StoragePolicy>& m, const vec_4d_t<T>& v) noexcept
{
    return matrix_vector_multiply(m, v);
}
} // namespace PKR_UNITS_NAMESPACE
