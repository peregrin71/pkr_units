#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
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
// Unit: lumen (lm) = candela Ã— steradian (cd Â· sr)
//
// CHARACTERISTICS:
// - Measures total light output from a source in all directions
// - Weighted by human eye sensitivity (photopic response)
// - Used to specify total brightness of light bulbs and fixtures
//
// RELATIONSHIPS:
// - Luminous intensity [cd] = Luminous flux / Solid angle [lm / sr]
// - Luminous flux [lm] = Luminous intensity Ã— Solid angle [cd Â· sr]
// - Illuminance [lux] = Luminous flux / Area [lm / mÂ²]
//
// EXAMPLES:
// - 100W incandescent bulb â‰ˆ 1700 lumens
// - Full moon illumination â‰ˆ 0.25 lux = 0.25 lm/mÂ²
// - Bright sunlight â‰ˆ 100,000 lux = 100,000 lm/mÂ²
// Strong type for lumen (luminous flux)
template <is_unit_value_type_c T>
struct lumen_t final : public details::unit_t<T, std::ratio<1, 1>, dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 1}>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 1}>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"lumen"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cd\u00b7sr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cd\u00b7sr"};
};

template <is_unit_value_type_c T>
lumen_t(T) -> lumen_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 1})
lumen_t(const U&) -> lumen_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Derived unit type specialization
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, dimension_t{0, 0, 0, 0, 0, 0, 1, 0, 1}>
{
    using type = lumen_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
