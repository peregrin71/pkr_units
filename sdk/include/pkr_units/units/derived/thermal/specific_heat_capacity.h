#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Specific heat capacity dimension: m^2·s^-2·K^-1 (L^2·T^-2·Θ^-1)
inline constexpr dimension_t specific_heat_capacity_dimension{2, 0, -2, 0, -1, 0, 0, 0};

// Specific heat capacity unit: J/(kg*K)
template <is_unit_value_type_c T>
struct specific_heat_capacity_t final : public details::unit_t<T, std::ratio<1, 1>, specific_heat_capacity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, specific_heat_capacity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"specific_heat_capacity"};
    [[maybe_unused]] static constexpr std::string_view symbol{"J/(kg*K)"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"J\u00B7kg\u207B\u00B9\u00B7K\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"J\u00B7kg\u207B\u00B9\u00B7K\u207B\u00B9"};
};

template <is_unit_value_type_c T>
specific_heat_capacity_t(T) -> specific_heat_capacity_t<T>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, specific_heat_capacity_dimension>
{
    using type = specific_heat_capacity_t<T>;
};

// Explicit double instantiation
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, specific_heat_capacity_dimension>
{
    using type = specific_heat_capacity_t<double>;
};
} // namespace PKR_UNITS_NAMESPACE
