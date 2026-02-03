#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/energy.h>
namespace PKR_UNITS_NAMESPACE
{
// CGS energy unit
// Erg = 10^-7 joule
template <is_unit_value_type_c T>
struct erg_t final : public details::unit_t<T, std::ratio<1, 10000000>, energy_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 10000000>, energy_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"erg"};
    [[maybe_unused]] static constexpr std::string_view symbol{"erg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"erg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"erg"};
};

template <is_unit_value_type_c T>
erg_t(T) -> erg_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == energy_dimension)
erg_t(const U&) -> erg_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 10000000>, energy_dimension>
{
    using type = erg_t<T>;
}; 
} // namespace PKR_UNITS_NAMESPACE
