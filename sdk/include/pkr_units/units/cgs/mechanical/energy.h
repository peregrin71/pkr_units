#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/energy.h>

namespace PKR_UNITS_NAMESPACE
{

// CGS energy unit
// Erg = 10^-7 joule
struct erg_t final : public details::unit_t<double, std::ratio<1, 10000000>, energy_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10000000>, energy_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"erg"};
    static constexpr std::string_view symbol{"erg"};
    static constexpr std::wstring_view w_symbol{L"erg"};
    static constexpr std::u8string_view u8_symbol{u8"erg"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 10000000>, energy_dimension>
{
    using type = erg_t;
};

} // namespace PKR_UNITS_NAMESPACE
