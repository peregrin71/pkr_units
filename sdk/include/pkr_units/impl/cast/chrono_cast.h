#pragma once

#include <chrono>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/time_decl.h>
#include <pkr_units/impl/cast/unit_cast.h>

namespace PKR_UNITS_NAMESPACE
{

namespace details
{
// Default specialization for time dimension to allow conversion from arbitrary chrono periods
template <typename type_t, typename ratio_t>
struct derived_unit_type_t<type_t, ratio_t, time_dimension>
{
    using type = time_unit_t<type_t, ratio_t>;
};
} // namespace details

// unit_cast overload: from chrono duration to pkr time unit
template <typename target_unit_t, typename Rep, typename Period>

    requires std::is_base_of_v<typename target_unit_t::_base, target_unit_t> && (details::is_pkr_unit<target_unit_t>::value_dimension == time_dimension)
constexpr target_unit_t unit_cast(std::chrono::duration<Rep, Period> d) noexcept
{
    // Convert directly from chrono period to target unit ratio
    using target_ratio = typename details::is_pkr_unit<target_unit_t>::ratio_type;
    using target_type_t = typename details::is_pkr_unit<target_unit_t>::value_type;

    // Use the same conversion factor logic as unit_cast_impl
    constexpr target_type_t conversion_factor = details::compute_conversion_factor<target_type_t>(
        Period::num, Period::den, target_ratio::num, target_ratio::den); // Convert chrono period to target unit ratio

    target_type_t value = static_cast<target_type_t>(d.count()) * conversion_factor;

    return target_unit_t(value);
}

// unit_cast overload: from pkr time unit to chrono duration
template <typename Duration, typename source_unit_t>

    requires std::is_base_of_v<typename source_unit_t::_base, source_unit_t> && (details::is_pkr_unit<source_unit_t>::value_dimension == time_dimension)
constexpr Duration unit_cast(const source_unit_t& source) noexcept
{
    using source_ratio = typename details::is_pkr_unit<source_unit_t>::ratio_type;
    using source_type_t = typename details::is_pkr_unit<source_unit_t>::value_type;

    // Compute the count for the Duration
    constexpr source_type_t conversion_factor = details::compute_conversion_factor<source_type_t>(
        source_ratio::num, source_ratio::den, Duration::period::num, Duration::period::den); // Convert unit ratio to Duration period

    source_type_t count = source.value() * conversion_factor;

    return Duration(static_cast<typename Duration::rep>(count));
}

} // namespace PKR_UNITS_NAMESPACE
