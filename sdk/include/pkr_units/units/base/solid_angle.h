#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Strong type for steradian (SI base unit for solid angle)
template <is_unit_value_type_c T>
struct steradian_t final : public details::unit_t<T, std::ratio<1, 1>, solid_angle_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, solid_angle_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"steradian"};
    [[maybe_unused]] static constexpr std::string_view symbol{"sr"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"sr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"sr"};
};

template <is_unit_value_type_c T>
steradian_t(T) -> steradian_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == solid_angle_dimension)
steradian_t(const U&) -> steradian_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, solid_angle_dimension>
{
    using type = steradian_t<T>;
};

} // namespace PKR_UNITS_NAMESPACE
