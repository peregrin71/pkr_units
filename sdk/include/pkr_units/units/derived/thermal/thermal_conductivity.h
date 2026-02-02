#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Thermal conductivity dimension: kg·m·s^-3·K^-1 (M·L·T^-3·Θ^-1)
inline constexpr dimension_t thermal_conductivity_dimension{1, 1, -3, 0, -1, 0, 0, 0};

// Thermal conductivity unit: W/(m*K)
struct thermal_conductivity_t final : public details::unit_t<double, std::ratio<1, 1>, thermal_conductivity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, thermal_conductivity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"thermal_conductivity"};

    [[maybe_unused]] static constexpr std::string_view symbol{"W/(m*K)"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"W·m⁻¹·K⁻¹"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"W·m⁻¹·K⁻¹"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, thermal_conductivity_dimension>
{
    using type = thermal_conductivity_t;
};

} // namespace PKR_UNITS_NAMESPACE
