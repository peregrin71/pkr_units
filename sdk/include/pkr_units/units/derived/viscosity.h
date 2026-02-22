#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Dynamic viscosity units
// Base unit: pascal second (Pa*s) = kgÂ·m^-1Â·s^-1
template <is_unit_value_type_c T>
struct pascal_second_t final : public unit_t<T, std::ratio<1, 1>, dynamic_viscosity_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1>, dynamic_viscosity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"pascal_second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pa*s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pa\u00B7s"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pa\u00B7s"};
};

template <is_unit_value_type_c T>
pascal_second_t(T) -> pascal_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == dynamic_viscosity_dimension)
pascal_second_t(const U&) -> pascal_second_t<typename details::is_pkr_unit<U>::value_type>;

// Kinematic viscosity units
// Base unit: square meter per second (m^2/s) = m^2Â·s^-1
template <is_unit_value_type_c T>
struct square_meter_per_second_t final : public unit_t<T, std::ratio<1, 1>, kinematic_viscosity_dimension>
{
    using _base = unit_t<T, std::ratio<1, 1>, kinematic_viscosity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"square_meter_per_second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"m^2/s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"m\u00B2\u00B7s\u207B\u00B9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"m\u00B2\u00B7s\u207B\u00B9"};
};

template <is_unit_value_type_c T>
square_meter_per_second_t(T) -> square_meter_per_second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == kinematic_viscosity_dimension)
square_meter_per_second_t(const U&) -> square_meter_per_second_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, dynamic_viscosity_dimension>
{
    using type = pascal_second_t<T>;
};

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, kinematic_viscosity_dimension>
{
    using type = square_meter_per_second_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
