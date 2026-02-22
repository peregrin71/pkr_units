#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/units/derived/magnetic_flux.h>

namespace PKR_UNITS_NAMESPACE
{
// CGS (Gaussian) magnetic units
// Gauss (CGS unit for magnetic flux density)
// 1 Gauss = 10^-4 Tesla
template <is_unit_value_type_c T>
struct gauss_t final : public unit_t<T, std::ratio<1, 10000>, magnetic_flux_density_dimension>
{
    using _base = unit_t<T, std::ratio<1, 10000>, magnetic_flux_density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gauss"};
    [[maybe_unused]] static constexpr std::string_view symbol{"G"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"G"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"G"};
};

template <is_unit_value_type_c T>
gauss_t(T) -> gauss_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_flux_density_dimension)
gauss_t(const U&) -> gauss_t<typename details::is_pkr_unit<U>::value_type>;
} // namespace PKR_UNITS_NAMESPACE
