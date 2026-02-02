#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Specific heat capacity dimension: m^2·s^-2·K^-1 (L^2·T^-2·Θ^-1)
inline constexpr dimension_t specific_heat_capacity_dimension{2, 0, -2, 0, -1, 0, 0, 0};

// Specific heat capacity unit: J/(kg*K)
struct specific_heat_capacity_t final : public details::unit_t<double, std::ratio<1, 1>, specific_heat_capacity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, specific_heat_capacity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"specific_heat_capacity"};

    [[maybe_unused]] static constexpr std::string_view symbol{"J/(kg*K)"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"J·kg⁻¹·K⁻¹"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"J·kg⁻¹·K⁻¹"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, specific_heat_capacity_dimension>
{
    using type = specific_heat_capacity_t;
};

} // namespace PKR_UNITS_NAMESPACE
