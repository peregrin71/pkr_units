#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/viscosity_decl.h>
namespace PKR_UNITS_NAMESPACE
{
// CGS dynamic viscosity unit
// Poise = 0.1 Pa*s
template <is_unit_value_type_c T>
struct poise_t final : public details::unit_t<T, std::ratio<1, 10>, dynamic_viscosity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 10>, dynamic_viscosity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"poise"};
    [[maybe_unused]] static constexpr std::string_view symbol{"P"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"P"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"P"};
};

template <is_unit_value_type_c T>
poise_t(T) -> poise_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == dynamic_viscosity_dimension)
poise_t(const U&) -> poise_t<typename details::is_pkr_unit<U>::value_type>;

// CGS kinematic viscosity unit
// Stokes = 1e-4 m^2/s
template <is_unit_value_type_c T>
struct stokes_t final : public details::unit_t<T, std::ratio<1, 10000>, kinematic_viscosity_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 10000>, kinematic_viscosity_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"stokes"};
    [[maybe_unused]] static constexpr std::string_view symbol{"St"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"St"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"St"};
};

template <is_unit_value_type_c T>
stokes_t(T) -> stokes_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == kinematic_viscosity_dimension)
stokes_t(const U&) -> stokes_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 10>, dynamic_viscosity_dimension>
{
    using type = poise_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 10000>, kinematic_viscosity_dimension>
{
    using type = stokes_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
