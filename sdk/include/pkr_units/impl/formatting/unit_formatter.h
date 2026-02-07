#pragma once

#include <algorithm>
#include <format>
#include <type_traits>
#include <sstream>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_t.h>
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

        // Build dimension symbol into static buffer (no allocation)
        PKR_UNITS_NAMESPACE::impl::format_buffer<CharT> buf;
        buf.clear();
        constexpr auto dim = PKR_UNITS_NAMESPACE::details::is_pkr_unit<T>::value_dimension;
        PKR_UNITS_NAMESPACE::impl::build_dimension_symbol_to_buffer(buf, dim);

        // Space before symbol
        *out++ = static_cast<CharT>(' ');
        return std::copy(buf.begin(), buf.end(), out);
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

// Generic operator<< for all character streams with pkr_units
// This allows units to be output to any ostream (including wcout for wide character output)
template <typename CharT, typename Traits, typename T>
    requires PKR_UNITS_NAMESPACE::is_pkr_unit_c<T>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const T& unit)
{
    // Use std::format with the appropriate character type to format the unit
    // The formatter specialization will handle selecting the correct symbol (symbol, w_symbol, or u8_symbol)
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        // For wide character streams, format to wstring and output directly
        std::wstring formatted = std::format(L"{}", unit);
        os << formatted;
    }
    // else if constexpr (std::is_same_v<CharT, char8_t>)
    // {
    //     // For UTF-8 character streams, format to u8string and output directly
    //     std::u8string formatted = std::format(u8"{}", unit);
    //     os << formatted;
    // }
    else
    {
        // For normal char streams
        std::string formatted = std::format("{}", unit);
        os << formatted;
    }
    return os;
}

} // namespace std
