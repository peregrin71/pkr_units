#pragma once

#include <format>
#include <string_view>
#include <type_traits>
#include <algorithm>
#include <sstream>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>

// Forward declarations in the correct namespace
namespace PKR_UNITS_NAMESPACE
{
template <is_pkr_unit_c UnitT>
class measurement_lin_t;

template <is_pkr_unit_c UnitT>
class measurement_rss_t;
} // namespace PKR_UNITS_NAMESPACE

namespace std
{

// ============================================================================
// std::formatter specialization for measurement_lin_t
// ============================================================================
template <PKR_UNITS_NAMESPACE::is_pkr_unit_c UnitT, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::measurement_lin_t<UnitT>, CharT>
{
private:
    std::formatter<typename UnitT::value_type, CharT> value_formatter;

public:
    constexpr auto parse(std::basic_format_parse_context<CharT>& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::measurement_lin_t<UnitT>& m, FormatContext& ctx) const
    {
        auto out = ctx.out();

        // Format value directly to output context
        out = value_formatter.format(m.value(), ctx);

        // Separator (ASCII: +/-, wide character: ±)
        if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            auto sep = std::basic_string_view<CharT>(L" \u00b1 ");
            out = std::copy(sep.begin(), sep.end(), out);
        }
        else
        {
            auto sep = std::basic_string_view<CharT>(" +/- ");
            out = std::copy(sep.begin(), sep.end(), out);
        }

        // Format uncertainty directly to output context
        out = value_formatter.format(m.uncertainty(), ctx);

        // Symbol
        *out++ = static_cast<CharT>(' ');

        std::basic_string_view<CharT> sym;
        if constexpr (std::is_same_v<CharT, wchar_t>)
            sym = UnitT::w_symbol;
        else
            sym = UnitT::symbol;

        return std::copy(sym.begin(), sym.end(), out);
    }
};

// ============================================================================
// std::formatter specialization for measurement_rss_t
// ============================================================================
template <PKR_UNITS_NAMESPACE::is_pkr_unit_c UnitT, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::measurement_rss_t<UnitT>, CharT>
{
private:
    std::formatter<typename UnitT::value_type, CharT> value_formatter;

public:
    constexpr auto parse(std::basic_format_parse_context<CharT>& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::measurement_rss_t<UnitT>& m, FormatContext& ctx) const
    {
        auto out = ctx.out();

        // Format value directly to output context
        out = value_formatter.format(m.value(), ctx);

        // Separator (use standard +/- for ASCII, ± for wide character)
        if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            auto sep = std::basic_string_view<CharT>(L" \u00b1 ");
            out = std::copy(sep.begin(), sep.end(), out);
        }
        else
        {
            auto sep = std::basic_string_view<CharT>(" +/- ");
            out = std::copy(sep.begin(), sep.end(), out);
        }

        // Format uncertainty directly to output context
        out = value_formatter.format(m.uncertainty(), ctx);

        // Symbol
        *out++ = static_cast<CharT>(' ');

        std::basic_string_view<CharT> sym;
        if constexpr (std::is_same_v<CharT, wchar_t>)
            sym = UnitT::w_symbol;
        else
            sym = UnitT::symbol;

        return std::copy(sym.begin(), sym.end(), out);
    }
};

} // namespace std
