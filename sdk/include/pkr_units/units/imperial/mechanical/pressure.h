#pragma once
#include <string_view>

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/pressure.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial pressure units
struct psi_t final : public details::unit_t<double, std::ratio<6894757, 1000>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<6894757, 1000>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"psi"};
    static constexpr std::string_view symbol{"psi"};
    static constexpr std::wstring_view w_symbol{L"psi"};
    static constexpr std::u8string_view u8_symbol{u8"psi"};
};

// ============================================================================
// Most derived unit type specializations for imperial pressure units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<6894757, 1000>, pressure_dimension>
{
    using type = psi_t;
};

} // namespace PKR_UNITS_NAMESPACE
