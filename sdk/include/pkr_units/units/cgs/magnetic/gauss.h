#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/units/derived/magnetic_flux.h>

namespace PKR_UNITS_NAMESPACE
{

// CGS (Gaussian) magnetic units
// Gauss (CGS unit for magnetic flux density)
// 1 Gauss = 10^-4 Tesla
struct gauss_t final : public details::unit_t<double, std::ratio<1, 10000>, magnetic_flux_density_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10000>, magnetic_flux_density_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gauss"};

    [[maybe_unused]] static constexpr std::string_view symbol{"G"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"G"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"G"};
};

} // namespace PKR_UNITS_NAMESPACE
