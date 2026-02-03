#pragma once
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/mechanical/power.h>
namespace PKR_UNITS_NAMESPACE
{
// Imperial power units
template <is_unit_value_type_c T>
struct horsepower_t final : public details::unit_t<T, std::ratio<745700, 1000>, power_dimension>
{
    using _base = details::unit_t<T, std::ratio<745700, 1000>, power_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"horsepower"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hp"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hp"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hp"};
};

template <is_unit_value_type_c T>
horsepower_t(T) -> horsepower_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == power_dimension)
horsepower_t(const U&) -> horsepower_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for imperial power units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<745700, 1000>, power_dimension>
{
    using type = horsepower_t<T>;
}; 
} // namespace PKR_UNITS_NAMESPACE
