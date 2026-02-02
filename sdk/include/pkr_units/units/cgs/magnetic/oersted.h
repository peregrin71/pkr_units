#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Magnetic field strength dimension: A·m^-1
inline constexpr dimension_t magnetic_field_strength_dimension{-1, 0, 0, 1, 0, 0, 0, 0};

// CGS magnetic field strength unit
// Oersted = (1000 / (4*pi)) A/m (approximate ratio)
struct oersted_t final : public details::unit_t<double, std::ratio<795774715459477, 10000000000000>, magnetic_field_strength_dimension>
{
    using _base = details::unit_t<double, std::ratio<795774715459477, 10000000000000>, magnetic_field_strength_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"oersted"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Oe"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Oe"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Oe"};
};

template <>
struct details::derived_unit_type_t<double, std::ratio<795774715459477, 10000000000000>, magnetic_field_strength_dimension>
{
    using type = oersted_t;
};

} // namespace PKR_UNITS_NAMESPACE
