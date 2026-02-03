#pragma once
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
namespace PKR_UNITS_NAMESPACE
{
template <is_unit_value_type_c T>
struct scalar_t final : public details::unit_t<T, std::ratio<1, 1>, scalar_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, scalar_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"scalar"};
    [[maybe_unused]] static constexpr std::string_view symbol{""};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L""};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8""};
};

template <is_unit_value_type_c T>
scalar_t(T) -> scalar_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == scalar_dimension)
scalar_t(const U&) -> scalar_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, scalar_dimension>
{
    using type = scalar_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
