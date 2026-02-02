#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/units/base/intensity.h>
#include <pkr_units/units/base/solid_angle.h>

namespace PKR_UNITS_NAMESPACE
{

// ============================================================================
// Luminous Flux (Lumen)
// ============================================================================
// 
// Luminous flux is the total amount of visible light emitted by a source.
// Unit: lumen (lm) = candela × steradian (cd · sr)
//
// CHARACTERISTICS:
// - Measures total light output from a source in all directions
// - Weighted by human eye sensitivity (photopic response)
// - Used to specify total brightness of light bulbs and fixtures
//
// RELATIONSHIPS:
// - Luminous intensity [cd] = Luminous flux / Solid angle [lm / sr]
// - Luminous flux [lm] = Luminous intensity × Solid angle [cd · sr]
// - Illuminance [lux] = Luminous flux / Area [lm / m²]
//
// EXAMPLES:
// - 100W incandescent bulb ≈ 1700 lumens
// - Full moon illumination ≈ 0.25 lux = 0.25 lm/m²
// - Bright sunlight ≈ 100,000 lux = 100,000 lm/m²

// Strong type for lumen (luminous flux)
struct lumen_t final : public details::unit_t<double, std::ratio<1, 1>, dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 1}>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 1}>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"lumen"};

    [[maybe_unused]] static constexpr std::string_view symbol{"lm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cd\u00b7sr"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cd\u00b7sr"};

};

// ============================================================================
// Derived unit type specialization
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 1}>
{
    using type = lumen_t;
};

} // namespace PKR_UNITS_NAMESPACE
