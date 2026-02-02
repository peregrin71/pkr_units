#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/electrical/charge.h>

namespace PKR_UNITS_NAMESPACE
{

// CGS electrostatic unit of charge
// Statcoulomb = 1 / (10 * c) coulomb (c in m/s, exact)
struct statcoulomb_t final : public details::unit_t<double, std::ratio<1, 2997924580>, electric_charge_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 2997924580>, electric_charge_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"statcoulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"statC"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"statC"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"statC"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 2997924580>, electric_charge_dimension>
{
    using type = statcoulomb_t;
};

} // namespace PKR_UNITS_NAMESPACE
