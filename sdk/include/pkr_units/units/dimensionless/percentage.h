#pragma once
#include <ratio>
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Percentage (100% == 1.0 ratio)
template <is_unit_value_type_c T>
struct percentage_t final : public unit_t<T, std::ratio<1, 100>, scalar_dimension>
{
    using _base = unit_t<T, std::ratio<1, 100>, scalar_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"percent"};
    [[maybe_unused]] static constexpr std::string_view symbol{"%"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"%"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"%"};
};

template <is_unit_value_type_c T>
percentage_t(T) -> percentage_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == scalar_dimension)
percentage_t(const U&) -> percentage_t<typename details::is_pkr_unit<U>::value_type>;
} // namespace PKR_UNITS_NAMESPACE
