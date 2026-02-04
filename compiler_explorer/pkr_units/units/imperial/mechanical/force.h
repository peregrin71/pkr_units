#pragma once
#include <string_view>
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/derived/mechanical/force.h"

namespace PKR_UNITS_NAMESPACE
{
// Imperial force units
template <is_unit_value_type_c T>
struct poundal_t final : public details::unit_t<T, std::ratio<45359237, 1000000000>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<45359237, 1000000000>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"poundal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pdl"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pdl"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pdl"};
};

template <is_unit_value_type_c T>
poundal_t(T) -> poundal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
poundal_t(const U&) -> poundal_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct pound_force_t final : public details::unit_t<T, std::ratio<4448222, 1000000>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<4448222, 1000000>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"pound_force"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lbf"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"lbf"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"lbf"};
};

template <is_unit_value_type_c T>
pound_force_t(T) -> pound_force_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
pound_force_t(const U&) -> pound_force_t<typename details::is_pkr_unit<U>::value_type>;
} // namespace PKR_UNITS_NAMESPACE
