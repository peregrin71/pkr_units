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
template <is_unit_value_type_c T>
struct decibel_power_t final : public details::unit_t<T, std::ratio<1, 1>, scalar_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, scalar_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decibel_power"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dB"};
};

template <is_unit_value_type_c T>
decibel_power_t(T) -> decibel_power_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == scalar_dimension)
decibel_power_t(const U&) -> decibel_power_t<typename details::is_pkr_unit<U>::value_type>;

// Decibel (amplitude ratio, 20 * log10)
// Intentionally does NOT define _base, to avoid generic unit_cast.
template <is_unit_value_type_c T>
struct decibel_amplitude_t final : public details::unit_t<T, std::ratio<1, 1>, scalar_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, scalar_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decibel_amplitude"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dB"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dB"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dB"};
};

template <is_unit_value_type_c T>
decibel_amplitude_t(T) -> decibel_amplitude_t<T>;
} // namespace PKR_UNITS_NAMESPACE

namespace std
{
template <PKR_UNITS_NAMESPACE::is_unit_value_type_c T, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::decibel_power_t<T>, CharT>
{
    std::formatter<double, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::decibel_power_t<T>& value, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(value.value(), ctx);
        *out++ = static_cast<CharT>(' ');
        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t<T>::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t<T>::symbol.end(), out);
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t<T>::w_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t<T>::w_symbol.end(), out);
        }
        else if constexpr (std::is_same_v<CharT, char8_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t<T>::u8_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t<T>::u8_symbol.end(), out);
        }
        else
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_power_t<T>::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_power_t<T>::symbol.end(), out);
        }
    }
};

template <PKR_UNITS_NAMESPACE::is_unit_value_type_c T, typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>, CharT>
{
    std::formatter<double, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>& value, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(value.value(), ctx);
        *out++ = static_cast<CharT>(' ');
        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::symbol.end(), out);
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::w_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::w_symbol.end(), out);
        }
        else if constexpr (std::is_same_v<CharT, char8_t>)
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::u8_symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::u8_symbol.end(), out);
        }
        else
        {
            return std::copy(PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::symbol.begin(), PKR_UNITS_NAMESPACE::decibel_amplitude_t<T>::symbol.end(), out);
        }
    }
};
} // namespace std
