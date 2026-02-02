#pragma once

#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/namespace_config.h>
#include <type_traits>
#include <ratio>

namespace PKR_UNITS_NAMESPACE
{

namespace details
{
// Helper to compute conversion factor from ratio components
// Templated only on type_t to reduce template bloat
template <typename type_t>
constexpr type_t compute_conversion_factor(long long source_num, long long source_den, long long target_num, long long target_den) noexcept
{
    return (static_cast<type_t>(source_num) * static_cast<type_t>(target_den)) /
           (static_cast<type_t>(source_den) * static_cast<type_t>(target_num));
}

// Internal cast function (preserves dimension, converts ratio)
template <typename target_ratio_t, typename type_t, typename source_ratio_t, dimension_t dim_v>
constexpr details::unit_t<type_t, target_ratio_t, dim_v> unit_cast_impl(const details::unit_t<type_t, source_ratio_t, dim_v>& source) noexcept
{
    if constexpr (std::is_same_v<source_ratio_t, target_ratio_t>)
    {
        // No conversion needed - same ratio
        return source;
    }
    else
    {
        // Convert between different ratios using type_t for precision matching
        constexpr type_t conversion_factor =
            compute_conversion_factor<type_t>(source_ratio_t::num, source_ratio_t::den, target_ratio_t::num, target_ratio_t::den);
        type_t converted_value = source.value() * conversion_factor;
        return details::unit_t<type_t, target_ratio_t, dim_v>(converted_value);
    }
}

// Concept: two types have the same dimension
template <typename Target, typename Source>
concept same_dimension_si_units = details::is_pkr_unit<Target>::value_dimension == details::is_pkr_unit<Source>::value_dimension;
} // namespace details

// Overload 1: For casting between direct unit_t types
template <typename target_type_t, typename target_ratio_t, dimension_t target_dim_v, typename source_type_t, typename source_ratio_t, dimension_t source_dim_v>

    requires(target_dim_v == source_dim_v) // Same dimension
constexpr details::unit_t<target_type_t, target_ratio_t, target_dim_v>
    unit_cast(const details::unit_t<source_type_t, source_ratio_t, source_dim_v>& source) noexcept
{
    return details::unit_cast_impl<target_ratio_t>(source);
}

// Overload 2: For casting between derived types (e.g., meter_per_second_t -> kilometer_per_hour_t)
// These are types that inherit from unit_t
template <typename target_unit_t, typename source_unit_t>

    requires std::is_base_of_v<typename target_unit_t::_base, target_unit_t> && std::is_base_of_v<typename source_unit_t::_base, source_unit_t> &&
             (details::is_pkr_unit<target_unit_t>::value_dimension == details::is_pkr_unit<source_unit_t>::value_dimension)
constexpr target_unit_t unit_cast(const source_unit_t& source) noexcept
{
    using target_ratio = typename details::is_pkr_unit<target_unit_t>::ratio_type;

    // Convert to base unit_t first, then construct the derived type
    auto converted = details::unit_cast_impl<target_ratio>(source);
    return target_unit_t(converted.value());
}

} // namespace PKR_UNITS_NAMESPACE
