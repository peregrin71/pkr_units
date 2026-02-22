#pragma once

#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/namespace_config.h>
#include <type_traits>
#include <ratio>

// Forward declare temperature tags so we can exclude affine conversions from
// the generic unit_cast overload without including temperature headers (which
// would create a circular dependency).
namespace PKR_UNITS_NAMESPACE
{
struct celsius_tag_t;
struct fahrenheit_tag_t;
} // namespace PKR_UNITS_NAMESPACE

namespace PKR_UNITS_NAMESPACE
{

namespace details
{
// Helper to compute conversion factor from ratio components
// Templated only on type_t to reduce template bloat
template <typename type_t>
constexpr type_t compute_conversion_factor(long long source_num, long long source_den, long long target_num, long long target_den) noexcept
{
    return (static_cast<type_t>(source_num) * static_cast<type_t>(target_den)) / (static_cast<type_t>(source_den) * static_cast<type_t>(target_num));
}

// Internal cast function (preserves dimension, converts ratio).
// Accepts any pkr unit (base or derived) thanks to the new `unit_traits`.
// The returned object is always a bare `unit_t`; callers may wrap it in a
// stronger type if desired.

template <typename target_ratio_t, pkr_unit_c Source>
constexpr auto unit_cast_impl(const Source& source) noexcept
{
    using V = unit_value_t<Source>;
    using SR = unit_ratio_t<Source>;
    constexpr dimension_t D = ::PKR_UNITS_NAMESPACE::details::unit_traits<Source>::dimension::value;

    if constexpr (std::is_same_v<SR, target_ratio_t>)
    {
        return unit_t<V, target_ratio_t, D>(source.value());
    }
    else
    {
        constexpr V factor = compute_conversion_factor<V>(SR::num, SR::den, target_ratio_t::num, target_ratio_t::den);
        return unit_t<V, target_ratio_t, D>(source.value() * factor);
    }
}

// Concept: two types have the same dimension
template <typename Target, typename Source>
concept same_dimension_si_units = is_pkr_unit<Target>::value_dimension == is_pkr_unit<Source>::value_dimension;
} // namespace details

// Compatibility overload: the original API allowed callers to specify the
// target unit parameters directly (value type, ratio, dimension).  Older
// tests and user code relied on that form.  Reintroduce it as a thin wrapper
// around the new general template to avoid breaking existing call sites.

// Overload 1 (compatibility): same as the previous implementation
template <typename target_type_t, typename target_ratio_t, dimension_t target_dim_v, typename source_type_t, typename source_ratio_t, dimension_t source_dim_v>
    requires(target_dim_v == source_dim_v) // Same dimension
constexpr unit_t<target_type_t, target_ratio_t, target_dim_v> unit_cast(const unit_t<source_type_t, source_ratio_t, source_dim_v>& source) noexcept
{
    using target_unit_t = unit_t<target_type_t, target_ratio_t, target_dim_v>;
    // delegate to the unified template
    return unit_cast<target_unit_t>(source);
}

// Unified casting for any two pkr units with matching dimensions.  This
// handles plain `unit_t` types, derived strong types, or any mix of the two.
// The old two-overload design was brittle; overload resolution could fail when
// one operand was a base type and the other a derived type because the second
// overload required both arguments to have an `_base` alias.  The result was
// the caller ending up with a plain `unit_t` when a more specific derived type
// existed (see examples errors during clang build).  The new implementation
// computes the conversion via `unit_cast_impl` and then constructs the target
// type from the converted value, which works uniformly.

template <is_pkr_unit_c Target, is_pkr_unit_c Source>
    requires(details::is_pkr_unit<Target>::value_dimension == details::is_pkr_unit<Source>::value_dimension) &&
            (!std::is_same_v<typename details::is_pkr_unit<Target>::tag_type, celsius_tag_t> &&
             !std::is_same_v<typename details::is_pkr_unit<Target>::tag_type, fahrenheit_tag_t> &&
             !std::is_same_v<typename details::is_pkr_unit<Source>::tag_type, celsius_tag_t> &&
             !std::is_same_v<typename details::is_pkr_unit<Source>::tag_type, fahrenheit_tag_t>)
constexpr Target unit_cast(const Source& source) noexcept
{
    using target_ratio = typename details::is_pkr_unit<Target>::ratio_type;
    auto converted = details::unit_cast_impl<target_ratio>(source);

    if constexpr (std::is_constructible_v<Target, decltype(converted.value())>)
        return Target(converted.value());
    else
        return converted; // already target-esque unit_t
}

} // namespace PKR_UNITS_NAMESPACE
