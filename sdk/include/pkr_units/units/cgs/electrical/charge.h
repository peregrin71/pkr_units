#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/units/derived/electrical/charge.h>

namespace PKR_UNITS_NAMESPACE
{
// CGS electrostatic unit of charge
// Statcoulomb = 1 / (10 * c) coulomb (c in m/s, exact)
template <is_unit_value_type_c T>
struct statcoulomb_t final : public details::unit_t<T, std::ratio<1, 2997924580>, electric_charge_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 2997924580>, electric_charge_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"statcoulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"statC"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"statC"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"statC"};
};

template <is_unit_value_type_c T>
statcoulomb_t(T) -> statcoulomb_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_charge_dimension)
statcoulomb_t(const U&) -> statcoulomb_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 2997924580>, electric_charge_dimension>
{
    using type = statcoulomb_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
