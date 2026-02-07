#pragma once

#include <algorithm>
#include <format>
#include <string_view>
#include <type_traits>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>

namespace PKR_UNITS_NAMESPACE::impl::vector_formatting
{

// Helper to format a single vector component with format spec
template <typename CharT, typename ValueT, typename FormatContext>
inline auto format_component(FormatContext& ctx, std::basic_string_view<CharT> format_spec, const ValueT& value)
{
    return std::vformat_to(ctx.out(), std::basic_string_view<CharT>{format_spec}, std::make_format_args(value));
}

// Helper to write a unit symbol from dimension into output iterator
template <typename CharT, typename OutputIt>
inline OutputIt write_unit_symbol(OutputIt out, const dimension_t& dim)
{
    PKR_UNITS_NAMESPACE::impl::format_buffer<CharT> buf;
    buf.clear();
    PKR_UNITS_NAMESPACE::impl::build_dimension_symbol_to_buffer(buf, dim);
    return std::copy(buf.begin(), buf.end(), out);
}

// Helper to write a comma and space separator (constexpr-compatible)
template <typename CharT, typename OutputIt>
constexpr OutputIt write_separator(OutputIt out)
{
    *out++ = static_cast<CharT>(',');
    *out++ = static_cast<CharT>(' ');
    return out;
}

} // namespace PKR_UNITS_NAMESPACE::impl::vector_formatting
