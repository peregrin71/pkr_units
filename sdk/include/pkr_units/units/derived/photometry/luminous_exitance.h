#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/units/base/length.h>

namespace PKR_UNITS_NAMESPACE
{
// ============================================================================
// Illuminance (Lux)
// ============================================================================
//
// Illuminance is the luminous flux incident on a surface per unit area.
// Unit: lux (lx) = lumen / meterÂ² = candela Ã— steradian / meterÂ² (cdÂ·sr/mÂ²)
//
// CHARACTERISTICS:
// - Measures brightness of light on a surface
// - Independent of direction (scalar quantity)
// - Fundamental for lighting design and visibility
//
// RELATIONSHIPS:
// - Illuminance = Luminous flux / Area [lm / mÂ²]
// - Illuminance = Luminous intensity / DistanceÂ² [cd / mÂ²] (simplified for point source)
// - More precise: [cdÂ·sr / mÂ²] accounts for solid angle properly
//
// TYPICAL VALUES:
// - Full moon clear night: ~0.25 lux
// - Office/classroom: ~400 lux
// - Bright sunlight (direct): ~100,000 lux
// - Overcast daylight: ~10,000 lux
// - Sunrise/sunset: ~400 lux
// - Inside home (typical): ~50 lux
//
// APPLICATIONS:
// - Lighting design and specification
// - Safety standards (e.g., emergency exit signs)
// - Visibility and readability requirements
// - Camera sensor characterization
// - Astronomical observations
//
// NOTE: In the type system, illuminance is [intensityÂ·solid_angle / lengthÂ²]
// which reflects the full dimensional relationship.
// Strong type for lux (illuminance)
template <is_unit_value_type_c T>
struct lux_t final : public unit_t<T, std::ratio<1, 1>, dimension_t{-2, 0, 0, 0, 0, 0, 1, 0, 1}>
{
    using _base = unit_t<T, std::ratio<1, 1>, dimension_t{-2, 0, 0, 0, 0, 0, 1, 0, 1}>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"lux"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lx"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cd\u00b7sr\u00b7m\u207b\u00b2"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cd\u00b7sr\u00b7m\u207b\u00b2"};
};

template <is_unit_value_type_c T>
lux_t(T) -> lux_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == dimension_t{-2, 0, 0, 0, 0, 0, 1, 0, 1})
lux_t(const U&) -> lux_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Derived unit type specialization
// ============================================================================
template <is_unit_value_type_c T>
struct derived_unit_type_t<T, std::ratio<1, 1>, dimension_t{-2, 0, 0, 0, 0, 0, 1, 0, 1}>
{
    using type = lux_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
