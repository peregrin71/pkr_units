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

namespace std
{

// Specialization for base unit_t types
template <PKR_UNITS_NAMESPACE::is_unit_value_type_c type_t, typename ratio_t, PKR_UNITS_NAMESPACE::dimension_t dim_v, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::details::unit_t<type_t, ratio_t, dim_v>, CharT>
{
    std::formatter<type_t, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::details::unit_t<type_t, ratio_t, dim_v>& unit, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(unit.value(), ctx);

        // For base unit_t, always build dimension symbol
        static std::basic_string<CharT> built = PKR_UNITS_NAMESPACE::build_dimension_symbol<CharT>(dim_v);
        std::basic_string_view<CharT> sym = built;

        // Space before symbol
        *out++ = static_cast<CharT>(' ');
        return std::copy(sym.begin(), sym.end(), out);
    }
};

// Specialization for derived unit types
template <typename T, typename CharT>
requires PKR_UNITS_NAMESPACE::is_pkr_unit_c<T> && std::is_base_of_v<typename T::_base, T>

struct formatter<T, CharT>
{
    std::formatter<typename PKR_UNITS_NAMESPACE::details::is_pkr_unit<T>::value_type, CharT> value_formatter;

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

        // For derived types, use the constexpr symbol
        std::basic_string_view<CharT> sym;
        if constexpr (std::is_same_v<CharT, char>)
        {
            sym = T::symbol;
        }
        else if constexpr (std::is_same_v<CharT, char8_t>)
        {
            sym = T::u8_symbol;
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            sym = T::w_symbol;
        }
        else
        {
            sym = T::symbol;
        }

        // Space before symbol
        *out++ = static_cast<CharT>(' ');
        return std::copy(sym.begin(), sym.end(), out);
    }
};

} // namespace std
