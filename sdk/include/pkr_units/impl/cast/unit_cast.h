#pragma once

#include <pkr_units/impl/details/si_unit.h>
#include "../namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Internal cast function (preserves dimension, converts ratio)
template<typename target_ratio_t, typename type_t, typename source_ratio_t, dimension_t dim_v>
constexpr unit_t<type_t, target_ratio_t, dim_v> unit_cast(const unit_t<type_t, source_ratio_t, dim_v>& source) noexcept
{
    if constexpr (std::is_same_v<source_ratio_t, target_ratio_t>)
    {
        // No conversion needed - same ratio
        return source;
    }
    else
    {
        // Convert between different ratios
        constexpr double conversion_factor =
            (static_cast<double>(source_ratio_t::num) * target_ratio_t::den) / (static_cast<double>(source_ratio_t::den) * target_ratio_t::num);
        type_t converted_value = source.value() * static_cast<type_t>(conversion_factor);
        return unit_t<type_t, target_ratio_t, dim_v>(converted_value);
    }
}  // namespace PKR_UNITS_NAMESPACE
// Public unit_cast function for user code
// Converts unit to a different ratio while preserving dimension
// Usage: pkr::units::unit_cast<pkr::units::kilometer>(source_in_meters)
// where pkr::units::kilometer is a ratio type alias
template<typename target_ratio_or_unit_t, typename source_unit_t>
constexpr auto unit_cast(const source_unit_t& source) noexcept
{
    // Handle two cases:
    // 1. target is a full unit_t type: pkr::units::unit_cast<unit_t<double, std::kilo, length_v>>(source)
    // 2. target is just a ratio: pkr::units::unit_cast<std::kilo>(source) or pkr::units::unit_cast<pkr::units::kilometer>(source)

    // Check if target is a full si_unit type
    if constexpr (is_si_unit<target_ratio_or_unit_t>::value)
    {
        // Case 1: target is a full unit_t type
        using target_traits = is_si_unit<target_ratio_or_unit_t>;
        using source_traits = is_si_unit<source_unit_t>;

        static_assert(
            target_traits::value_dimension == source_traits::value_dimension, "unit_cast requires source and target to have the same dimension");

        using target_ratio = typename target_traits::ratio_type;
        return unit_cast<target_ratio>(source);
    }
    else
    {
        // Case 2: target is a ratio, infer full si_unit type from source
        using source_traits = is_si_unit<source_unit_t>;
        static_assert(source_traits::value, "unit_cast source must be an si_unit type");

        // Build the target unit_t type with source's value type and dimension
        using target_unit = unit_t<typename source_traits::value_type, target_ratio_or_unit_t, source_traits::value_dimension>;

        return unit_cast<target_ratio_or_unit_t>(source);
    }
}  // namespace PKR_UNITS_NAMESPACE
} // PKR_UNITS_NAMESPACE
