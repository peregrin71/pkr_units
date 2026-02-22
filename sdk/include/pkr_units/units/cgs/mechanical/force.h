#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/units/derived/mechanical/force.h>

namespace PKR_UNITS_NAMESPACE
{
// CGS force unit
// Dyne = 10^-5 newton
template <is_unit_value_type_c T>
struct dyne_t final : public unit_t<T, std::ratio<1, 100000>, force_dimension>
{
    using _base = unit_t<T, std::ratio<1, 100000>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"dyne"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dyn"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dyn"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dyn"};
};

template <is_unit_value_type_c T>
dyne_t(T) -> dyne_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
dyne_t(const U&) -> dyne_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 100000>, force_dimension>
{
    using type = dyne_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
