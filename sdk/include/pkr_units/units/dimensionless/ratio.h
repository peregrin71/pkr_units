#pragma once
#include <ratio>
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{
// Dimensionless ratio (1.0 == 1:1)
template <is_unit_value_type_c T>
struct ratio_t final : public details::unit_t<T, std::ratio<1, 1>, scalar_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, scalar_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"ratio"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ratio"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ratio"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ratio"};
};

template <is_unit_value_type_c T>
ratio_t(T) -> ratio_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == scalar_dimension)
ratio_t(const U&) -> ratio_t<typename details::is_pkr_unit<U>::value_type>;

// Percentage (100% == 1.0 ratio)
template <is_unit_value_type_c T>
struct percentage_t final : public details::unit_t<T, std::ratio<1, 100>, scalar_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 100>, scalar_dimension>;
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
