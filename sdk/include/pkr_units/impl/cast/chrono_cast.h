#pragma once

#include <chrono>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/cast/unit_cast.h>

namespace PKR_UNITS_NAMESPACE
{

// Default specialization for time dimension to allow conversion from arbitrary chrono periods
// placed at namespace scope so it refers to the primary template declared in
// PKR_UNITS_NAMESPACE (not inside the nested `details` namespace).

template <typename type_t, typename ratio_t>
struct derived_unit_type_t<type_t, ratio_t, time_dimension>
{
    using type = time_unit_t<type_t, ratio_t>;
};

// unit_cast overload: from chrono duration to pkr time unit
template <pkr_unit_c target_unit_t, typename Rep, typename Period>
    requires(::PKR_UNITS_NAMESPACE::details::unit_traits<target_unit_t>::dimension::value == time_dimension)
constexpr target_unit_t unit_cast(std::chrono::duration<Rep, Period> d) noexcept
{
    // Convert directly from chrono period to target unit ratio
    using target_ratio = unit_ratio_t<target_unit_t>;
    using target_type_t = unit_value_t<target_unit_t>;

    // Use the same conversion factor logic as unit_cast_impl
    constexpr target_type_t conversion_factor = details::compute_conversion_factor<target_type_t>(
        Period::num, Period::den, target_ratio::num, target_ratio::den); // Convert chrono period to target unit ratio

    target_type_t value = static_cast<target_type_t>(d.count()) * conversion_factor;

    return target_unit_t(value);
}

// unit_cast overload: from pkr time unit to chrono duration
template <typename Duration, pkr_unit_c source_unit_t>
    requires(::PKR_UNITS_NAMESPACE::details::unit_traits<source_unit_t>::dimension::value == time_dimension)
constexpr Duration unit_cast(const source_unit_t& source) noexcept
{
    using source_ratio = unit_ratio_t<source_unit_t>;
    using source_type_t = unit_value_t<source_unit_t>;

    // Compute the count for the Duration
    constexpr source_type_t conversion_factor = details::compute_conversion_factor<source_type_t>(
        source_ratio::num, source_ratio::den, Duration::period::num, Duration::period::den); // Convert unit ratio to Duration period

    source_type_t count = source.value() * conversion_factor;

    return Duration(static_cast<typename Duration::rep>(count));
}

} // namespace PKR_UNITS_NAMESPACE
