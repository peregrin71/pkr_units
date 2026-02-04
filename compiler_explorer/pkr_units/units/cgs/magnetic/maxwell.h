#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/magnetic_flux.h"

namespace PKR_UNITS_NAMESPACE
{
// CGS magnetic flux unit
// Maxwell = 10^-8 weber
template <is_unit_value_type_c T>
struct maxwell_t final : public details::unit_t<T, std::ratio<1, 100000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 100000000>, magnetic_flux_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"maxwell"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mx"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mx"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mx"};
};

template <is_unit_value_type_c T>
maxwell_t(T) -> maxwell_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_dimension)
maxwell_t(const U&) -> maxwell_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 100000000>, magnetic_flux_dimension>
{
    using type = maxwell_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
