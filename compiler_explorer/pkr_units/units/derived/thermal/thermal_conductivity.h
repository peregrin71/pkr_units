#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

namespace PKR_UNITS_NAMESPACE
{
// Thermal conductivity dimension: kg·m·s^-3·K^-1 (M·L·T^-3·Θ^-1)
inline constexpr dimension_t thermal_conductivity_dimension{1, 1, -3, 0, -1, 0, 0, 0};

// Thermal conductivity unit: W/(m*K)
template <is_unit_value_type_c T>
struct thermal_conductivity_t final : public details::unit_t<T, std::ratio<1, 1>, thermal_conductivity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, thermal_conductivity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"thermal_conductivity"};
    [[maybe_unused]] static constexpr std::string_view symbol{"W/(m*K)"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W\u00B7m\u207B\u00B9\u00B7K\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W\u00B7m\u207B\u00B9\u00B7K\u207B\u00B9"};
};

template <is_unit_value_type_c T>
thermal_conductivity_t(T) -> thermal_conductivity_t<T>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, thermal_conductivity_dimension>
{
    using type = thermal_conductivity_t<T>;
};

// Explicit double instantiation
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, thermal_conductivity_dimension>
{
    using type = thermal_conductivity_t<double>;
};
} // namespace PKR_UNITS_NAMESPACE
