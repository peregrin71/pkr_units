#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/pressure.h>

namespace PKR_UNITS_NAMESPACE
{

// CGS pressure unit
// Barye (Ba) = 0.1 pascal
struct barye_t final : public details::unit_t<double, std::ratio<1, 10>, pressure_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10>, pressure_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"barye"};
    static constexpr std::string_view symbol{"Ba"};
    static constexpr std::wstring_view w_symbol{L"Ba"};
    static constexpr std::u8string_view u8_symbol{u8"Ba"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 10>, pressure_dimension>
{
    using type = barye_t;
};

} // namespace PKR_UNITS_NAMESPACE
