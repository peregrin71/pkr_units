#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/viscosity_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Dynamic viscosity units
// Base unit: pascal second (Pa*s) = kg·m^-1·s^-1
struct pascal_second_t final : public details::unit_t<double, std::ratio<1, 1>, dynamic_viscosity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, dynamic_viscosity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"pascal_second"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Pa*s"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pa*s"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pa*s"};
};

// Kinematic viscosity units
// Base unit: square meter per second (m^2/s) = m^2·s^-1
struct square_meter_per_second_t final : public details::unit_t<double, std::ratio<1, 1>, kinematic_viscosity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, kinematic_viscosity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"square_meter_per_second"};

    [[maybe_unused]] static constexpr std::string_view symbol{"m^2/s"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m^2/s"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m^2/s"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, dynamic_viscosity_dimension>
{
    using type = pascal_second_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, kinematic_viscosity_dimension>
{
    using type = square_meter_per_second_t;
};

} // namespace PKR_UNITS_NAMESPACE
