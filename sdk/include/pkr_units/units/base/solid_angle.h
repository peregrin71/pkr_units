#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/solid_angle_decl.h>
#include <pkr_units/impl/dimension.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for steradian (SI base unit for solid angle)
struct steradian_t final : public details::unit_t<double, std::ratio<1, 1>, solid_angle_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, solid_angle_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"steradian"};

    [[maybe_unused]] static constexpr std::string_view symbol{"sr"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"sr"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"sr"};
};

// ============================================================================
// Most derived unit type specializations
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, solid_angle_dimension>
{
    using type = steradian_t;
};

} // namespace PKR_UNITS_NAMESPACE
