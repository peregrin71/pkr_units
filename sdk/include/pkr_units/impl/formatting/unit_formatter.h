#pragma once

#include <algorithm>
#include <format>
#include <string>
#include <string_view>
#include <type_traits>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/unit_t_decl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>

namespace std
{

// Specialization for base unit_t types
template <PKR_UNITS_NAMESPACE::is_base_pkr_unit_c T, typename CharT>
struct formatter<T, CharT>
{
    std::formatter<typename T::value_type, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const T& unit, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(unit.value(), ctx);
        constexpr auto dim = PKR_UNITS_NAMESPACE::details::is_pkr_unit<T>::value_dimension;
        static const std::basic_string<CharT> symbol = PKR_UNITS_NAMESPACE::impl::build_dimension_symbol<CharT>(dim);
        // Space before symbol
        *out++ = static_cast<CharT>(' ');
        return std::copy(symbol.begin(), symbol.end(), out);
    }
};

// Specialization for derived unit types
template <PKR_UNITS_NAMESPACE::is_derived_pkr_unit_c T, typename CharT>
struct formatter<T, CharT>
{
    std::formatter<typename T::value_type, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const T& unit, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(unit.value(), ctx);

        // For derived types, select appropriate symbol
        std::basic_string_view<CharT> sym;
        if constexpr (std::is_same_v<CharT, char>)
            sym = T::symbol;
        else if constexpr (std::is_same_v<CharT, char8_t>)
            sym = T::u8_symbol;
        else if constexpr (std::is_same_v<CharT, wchar_t>)
            sym = T::w_symbol;
        else
            sym = T::symbol;

        // Space before symbol
        *out++ = static_cast<CharT>(' ');
        return std::copy(sym.begin(), sym.end(), out);
    }
};

} // namespace std
