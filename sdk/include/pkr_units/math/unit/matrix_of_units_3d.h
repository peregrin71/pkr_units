#pragma once

#include <array>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/math/unit/unit_math.h>
#include "vector_of_units_3d.h"

namespace PKR_UNITS_NAMESPACE
{
namespace math
{

// ============================================================================
// Specialized 3x3 Matrix for Units (using stable math)
// ============================================================================

template<is_pkr_unit_c T>
class matrix_3d_units_t {
public:
    using value_type = T;
    using array_type = std::array<std::array<T, 3>, 3>;
    
    array_type data;
    
    constexpr matrix_3d_units_t() = default;
    
    constexpr matrix_3d_units_t(const array_type& arr) : data(arr) {}
    
    constexpr matrix_3d_units_t(std::initializer_list<std::initializer_list<T>> list) {
        auto row_it = list.begin();
        for (size_t i = 0; i < 3 && row_it != list.end(); ++i, ++row_it) {
            auto col_it = row_it->begin();
            for (size_t j = 0; j < 3 && col_it != row_it->end(); ++j, ++col_it) {
                data[i][j] = *col_it;
            }
        }
    }
    
    constexpr T& operator()(size_t row, size_t col) { return data[row][col]; }
    constexpr const T& operator()(size_t row, size_t col) const { return data[row][col]; }
    
    constexpr std::array<T, 3>& operator[](size_t row) { return data[row]; }
    constexpr const std::array<T, 3>& operator[](size_t row) const { return data[row]; }
};

template<is_pkr_unit_c T>
constexpr matrix_3d_units_t<T> identity_3d() {
    matrix_3d_units_t<T> m{};
    for (int i = 0; i < 3; ++i) m[i][i] = T{1};
    return m;
}

template<is_pkr_unit_c T>
constexpr vec_3d_t<T> matrix_vector_multiply(const matrix_3d_units_t<T>& m, const vec_3d_t<T>& v) noexcept {
    return vec_3d_t<T>{
        numerical::stable_add(
            numerical::stable_add(
                numerical::stable_multiply(m.data[0][0], v.x),
                numerical::stable_multiply(m.data[0][1], v.y)
            ),
            numerical::stable_multiply(m.data[0][2], v.z)
        ),
        numerical::stable_add(
            numerical::stable_add(
                numerical::stable_multiply(m.data[1][0], v.x),
                numerical::stable_multiply(m.data[1][1], v.y)
            ),
            numerical::stable_multiply(m.data[1][2], v.z)
        ),
        numerical::stable_add(
            numerical::stable_add(
                numerical::stable_multiply(m.data[2][0], v.x),
                numerical::stable_multiply(m.data[2][1], v.y)
            ),
            numerical::stable_multiply(m.data[2][2], v.z)
        )
    };
}

template<is_pkr_unit_c T>
constexpr vec_3d_t<T> operator*(const matrix_3d_units_t<T>& m, const vec_3d_t<T>& v) noexcept {
    return matrix_vector_multiply(m, v);
}

} // namespace math
} // namespace PKR_UNITS_NAMESPACE