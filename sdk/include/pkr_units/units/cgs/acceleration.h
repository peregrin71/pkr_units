#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/acceleration_decl.h>
namespace PKR_UNITS_NAMESPACE
{
// CGS acceleration unit (formatting-friendly, not a derived-unit mapping)
// Gal (cm/s^2) = 0.01 m/s^2
template <is_unit_value_type_c T>
struct gal_t final : public details::unit_t<T, std::ratio<1, 100>, acceleration_v>
{
    using _base = details::unit_t<T, std::ratio<1, 100>, acceleration_v>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gal"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gal"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gal"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gal"};
};

template <is_unit_value_type_c T>
gal_t(T) -> gal_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == acceleration_v)
gal_t(const U&) -> gal_t<typename details::is_pkr_unit<U>::value_type>; 
} // namespace PKR_UNITS_NAMESPACE
