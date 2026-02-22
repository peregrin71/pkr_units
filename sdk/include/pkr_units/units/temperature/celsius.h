#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>

namespace PKR_UNITS_NAMESPACE
{
// Celsius temperature
//
// The type is tagged with `celsius_tag_t` so that conversions can be
// specialized in `temperature_cast.h`.  This replaces the earlier
// "no _base typedef" marker technique; the unit now simply provides
// `_base` via `unit_t`, which allows generic helpers to inspect the tag.
// Conversions requiring an offset (Celsius <-> Fahrenheit) are handled by
// the custom `unit_cast` overloads in temperature_cast.h.
// tag to identify affine Celsius-scale units
struct celsius_tag_t
{
};

template <is_unit_value_type_c T>
struct celsius_t final : public unit_t<T, std::ratio<1, 1>, temperature_dimension, celsius_tag_t>
{
    // `_base` alias is required by the pkr::units type traits in order to
    // detect derived units; other code and the unit_cast machinery rely on it.
    using _base = unit_t<T, std::ratio<1, 1>, temperature_dimension, celsius_tag_t>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"celsius"};
    [[maybe_unused]] static constexpr std::string_view symbol{"C"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b0C"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b0C"};
};

template <is_unit_value_type_c T>
celsius_t(T) -> celsius_t<T>;
} // namespace PKR_UNITS_NAMESPACE
