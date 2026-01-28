#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/power.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial power units
struct horsepower_t final : public details::unit_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using _base = details::unit_t<double, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"horsepower"};
    static constexpr std::string_view symbol{"hp"};
    static constexpr std::wstring_view w_symbol{L"hp"};
    static constexpr std::u8string_view u8_symbol{u8"hp"};
};

// ============================================================================
// Most derived unit type specializations for imperial power units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<745700, 1000>, power_dimension>
{
    using type = horsepower_t;
};

} // namespace PKR_UNITS_NAMESPACE
