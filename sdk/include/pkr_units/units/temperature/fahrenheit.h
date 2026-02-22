#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Fahrenheit temperature
//
// Tagged with `fahrenheit_tag_t` so that temperature_cast can dispatch to the
// appropriate affine conversion logic.  The old SFINAE trick (omitting `_base`)
// is no longer necessary.
// tag to identify affine Fahrenheit-scale units
struct fahrenheit_tag_t
{
};

template <is_unit_value_type_c T>
struct fahrenheit_t final : public unit_t<T, std::ratio<1, 1>, temperature_dimension, fahrenheit_tag_t>
{
    using _base = unit_t<T, std::ratio<1, 1>, temperature_dimension, fahrenheit_tag_t>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"fahrenheit"};
    [[maybe_unused]] static constexpr std::string_view symbol{"F"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b0F"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b0F"};
};

template <is_unit_value_type_c T>
fahrenheit_t(T) -> fahrenheit_t<T>;
} // namespace PKR_UNITS_NAMESPACE
