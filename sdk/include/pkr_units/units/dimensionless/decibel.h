#pragma once

#include <algorithm>
#include <format>
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/decls/unit_t_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Decibel (power ratio, 10 * log10)
// Intentionally does NOT define _base, to avoid generic unit_cast.
struct decibel_power_t final : public details::unit_t<double, std::ratio<1, 1>, scalar_dimension>
{
    using decibel_power_t::unit_t::unit_t;
    [[maybe_unused]] static constexpr std::string_view name{"decibel_power"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dB"};
};

// Decibel (amplitude ratio, 20 * log10)
// Intentionally does NOT define _base, to avoid generic unit_cast.
struct decibel_amplitude_t final : public details::unit_t<double, std::ratio<1, 1>, scalar_dimension>
{
    using decibel_amplitude_t::unit_t::unit_t;
    [[maybe_unused]] static constexpr std::string_view name{"decibel_amplitude"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dB"};
};

} // namespace PKR_UNITS_NAMESPACE

namespace std
{

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::decibel_power_t, CharT>
{
    std::formatter<double, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::decibel_power_t& value, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(value.value(), ctx);
        *out++ = static_cast<CharT>(' ');
        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t::symbol.end(), out);
        }
        if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t::w_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t::w_symbol.end(), out);
        }
        if constexpr (std::is_same_v<CharT, char8_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t::u8_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t::u8_symbol.end(), out);
        }
        return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t::symbol.end(), out);
    }
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::decibel_amplitude_t, CharT>
{
    std::formatter<double, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::decibel_amplitude_t& value, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(value.value(), ctx);
        *out++ = static_cast<CharT>(' ');
        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t::symbol.end(), out);
        }
        if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t::w_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t::w_symbol.end(), out);
        }
        if constexpr (std::is_same_v<CharT, char8_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t::u8_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t::u8_symbol.end(), out);
        }
        return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t::symbol.end(), out);
    }
};

} // namespace std
