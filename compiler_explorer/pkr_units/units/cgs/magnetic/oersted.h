#pragma once
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/unit_impl.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/dimension.h"

namespace PKR_UNITS_NAMESPACE
{
// Magnetic field strength dimension: A·m^-1
inline constexpr dimension_t magnetic_field_strength_dimension{-1, 0, 0, 1, 0, 0, 0, 0};

// CGS magnetic field strength unit
// Oersted = (1000 / (4*pi)) A/m (approximate ratio)
template <is_unit_value_type_c T>
struct oersted_t final : public details::unit_t<T, std::ratio<795774715459477, 10000000000000>, magnetic_field_strength_dimension>
{
    using _base = details::unit_t<T, std::ratio<795774715459477, 10000000000000>, magnetic_field_strength_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"oersted"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Oe"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Oe"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Oe"};
};

template <is_unit_value_type_c T>
oersted_t(T) -> oersted_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == magnetic_field_strength_dimension)
oersted_t(const U&) -> oersted_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<795774715459477, 10000000000000>, magnetic_field_strength_dimension>
{
    using type = oersted_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
