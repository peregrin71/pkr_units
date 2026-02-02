#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/magnetic_flux.h>

namespace PKR_UNITS_NAMESPACE
{

// CGS magnetic flux unit
// Maxwell = 10^-8 weber
struct maxwell_t final : public details::unit_t<double, std::ratio<1, 100000000>, magnetic_flux_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 100000000>, magnetic_flux_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"maxwell"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mx"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mx"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mx"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 100000000>, magnetic_flux_dimension>
{
    using type = maxwell_t;
};

} // namespace PKR_UNITS_NAMESPACE
