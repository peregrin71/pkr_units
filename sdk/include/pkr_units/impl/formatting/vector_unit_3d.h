#pragma once

#include <algorithm>
#include <format>
#include <string_view>
#include <type_traits>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/units/math/vector_unit_3d.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/formatting/vector_unit_formatting_traits.h>

namespace std
{

// Specialization for vec_3d_units_t - formats as [x, y, z] unit
// Forward format specifiers (precision, etc.) to each component's value,
// uses static buffer for symbol and formatting output
template <PKR_UNITS_NAMESPACE::is_pkr_unit_c T, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::vec_3d_units_t<T>, CharT>
{
    // Store format specification as string_view (non-owning reference to parse context input)
    std::basic_string_view<CharT> format_spec;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        auto end = ctx.end();

        // Store the format spec as a string_view into the parse context's input
        format_spec = std::basic_string_view<CharT>(it, end - it);

        return end;
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::vec_3d_units_t<T>& vec, FormatContext& ctx) const
    {
        auto out = ctx.out();

        // Opening bracket
        *out++ = static_cast<CharT>('[');

        // Format x
        out = PKR_UNITS_NAMESPACE::impl::vector_formatting::format_component(ctx, format_spec, vec.x.value());
        out = PKR_UNITS_NAMESPACE::impl::vector_formatting::write_separator(out);

        // Format y
        out = PKR_UNITS_NAMESPACE::impl::vector_formatting::format_component(ctx, format_spec, vec.y.value());
        out = PKR_UNITS_NAMESPACE::impl::vector_formatting::write_separator(out);

        // Format z
        out = PKR_UNITS_NAMESPACE::impl::vector_formatting::format_component(ctx, format_spec, vec.z.value());

        // Closing bracket and unit symbol
        *out++ = static_cast<CharT>(']');
        *out++ = static_cast<CharT>(' ');

        // Add unit symbol using static buffer (no allocation)
        constexpr auto dim = PKR_UNITS_NAMESPACE::details::is_pkr_unit<T>::value_dimension;
        out = PKR_UNITS_NAMESPACE::impl::vector_formatting::write_unit_symbol<CharT>(out, dim);

        return out;
    }
};

} // namespace std
