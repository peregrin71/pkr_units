#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/temperature_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Fahrenheit temperature
//
// NOTE: fahrenheit_t intentionally does NOT define _base typedef.
// This serves as a marker that prevents it from being used with unit_cast().
// Temperature conversions between Celsius and Fahrenheit require offset handling
// that the ratio-based unit_cast template doesn't support. Use the unit_cast
// overloads defined in temperature_cast.h instead.
//
// The absence of _base causes SFINAE rejection in unit_cast's requires clause,
// which accesses target_unit_t::_base. This is an intentional design pattern.

struct fahrenheit_t final : public details::unit_t<double, std::ratio<1, 1>, temperature_dimension>
{
    // Intentionally no _base typedef - this is the marker that prevents unit_cast usage
    using fahrenheit_t::unit_t::unit_t;

    [[maybe_unused]] static constexpr std::string_view name{"fahrenheit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"F"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"°F"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"°F"};
};

} // namespace PKR_UNITS_NAMESPACE
