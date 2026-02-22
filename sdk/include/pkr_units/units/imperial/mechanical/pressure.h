#pragma once
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/units/derived/mechanical/pressure.h>

namespace PKR_UNITS_NAMESPACE
{
// Imperial pressure units
template <is_unit_value_type_c T>
struct psi_t final : public unit_t<T, std::ratio<6894757, 1000>, pressure_dimension>
{
    using _base = unit_t<T, std::ratio<6894757, 1000>, pressure_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"psi"};
    [[maybe_unused]] static constexpr std::string_view symbol{"psi"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"psi"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"psi"};
};

template <is_unit_value_type_c T>
psi_t(T) -> psi_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == pressure_dimension)
psi_t(const U&) -> psi_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for imperial pressure units
// ============================================================================
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<6894757, 1000>, pressure_dimension>
{
    using type = psi_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
