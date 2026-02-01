#pragma once

#include <algorithm>
#include <cmath>
#include <format>
#include <string>
#include <type_traits>
#include <pkr_units/units/astronomical/angle.h>
#include <pkr_units/impl/unit_formatting_traits.h>

namespace std
{

template <typename UnitT, typename CharT>
struct hms_component_formatter
{
    std::formatter<double, CharT> value_formatter;

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return value_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const UnitT& value, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out = value_formatter.format(value.value(), ctx);

        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::copy(UnitT::symbol.begin(), UnitT::symbol.end(), out);
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::copy(UnitT::w_symbol.begin(), UnitT::w_symbol.end(), out);
        }
        else
        {
            static_assert(std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>, "UTF-8 formatting is not supported for astronomical angle units");
            return out;
        }
    }
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::hms_archour_t, CharT> : hms_component_formatter<PKR_UNITS_NAMESPACE::hms_archour_t, CharT>
{
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::hms_arcminute_t, CharT> : hms_component_formatter<PKR_UNITS_NAMESPACE::hms_arcminute_t, CharT>
{
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::hms_arcsecond_t, CharT> : hms_component_formatter<PKR_UNITS_NAMESPACE::hms_arcsecond_t, CharT>
{
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::dms_degree_t, CharT> : hms_component_formatter<PKR_UNITS_NAMESPACE::dms_degree_t, CharT>
{
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::dms_arcminute_t, CharT> : hms_component_formatter<PKR_UNITS_NAMESPACE::dms_arcminute_t, CharT>
{
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::dms_arcsecond_t, CharT> : hms_component_formatter<PKR_UNITS_NAMESPACE::dms_arcsecond_t, CharT>
{
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::hms_angle_t, CharT>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        auto end = ctx.end();
        while (it != end && *it != static_cast<CharT>('}'))
        {
            ++it;
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::hms_angle_t& value, FormatContext& ctx) const
    {
        using archour_ratio = typename PKR_UNITS_NAMESPACE::details::is_pkr_unit<PKR_UNITS_NAMESPACE::hms_archour_t>::ratio_type;
        double hours_value = PKR_UNITS_NAMESPACE::details::convert_ratio_to<double, std::ratio<1, 1>, archour_ratio>(value.value());
        bool negative = hours_value < 0.0;
        double total_seconds = std::abs(hours_value) * 3600.0;

        int hours = static_cast<int>(total_seconds / 3600.0);
        double remainder = total_seconds - static_cast<double>(hours) * 3600.0;
        int minutes = static_cast<int>(remainder / 60.0);
        double seconds = remainder - static_cast<double>(minutes) * 60.0;
        long long seconds_rounded = std::llround(seconds);
        if (seconds_rounded >= 60)
        {
            seconds_rounded = 0;
            ++minutes;
            if (minutes >= 60)
            {
                minutes = 0;
                ++hours;
            }
        }

        auto out = ctx.out();
        if (negative)
        {
            *out++ = static_cast<CharT>('-');
        }

        if constexpr (std::is_same_v<CharT, char>)
        {
            out = std::format_to(out, "{}", PKR_UNITS_NAMESPACE::hms_archour_t{static_cast<double>(hours)});
            *out++ = ' ';
            out = std::format_to(out, "{}", PKR_UNITS_NAMESPACE::hms_arcminute_t{static_cast<double>(minutes)});
            *out++ = ' ';
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            out = std::format_to(out, L"{}", PKR_UNITS_NAMESPACE::hms_archour_t{static_cast<double>(hours)});
            out = std::format_to(out, L"{}", PKR_UNITS_NAMESPACE::hms_arcminute_t{static_cast<double>(minutes)});
        }
        else
        {
            static_assert(std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>, "UTF-8 formatting is not supported for astronomical angle units");
        }

        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::format_to(out, "{}", PKR_UNITS_NAMESPACE::hms_arcsecond_t{static_cast<double>(seconds_rounded)});
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::format_to(out, L"{}", PKR_UNITS_NAMESPACE::hms_arcsecond_t{static_cast<double>(seconds_rounded)});
        }
        else
        {
            return out;
        }
    }
};

template <typename CharT>
struct formatter<PKR_UNITS_NAMESPACE::dms_angle_t, CharT>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        auto it = ctx.begin();
        auto end = ctx.end();
        while (it != end && *it != static_cast<CharT>('}'))
        {
            ++it;
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const PKR_UNITS_NAMESPACE::dms_angle_t& value, FormatContext& ctx) const
    {
        using degree_ratio = typename PKR_UNITS_NAMESPACE::details::is_pkr_unit<PKR_UNITS_NAMESPACE::dms_degree_t>::ratio_type;
        double degrees_value = PKR_UNITS_NAMESPACE::details::convert_ratio_to<double, std::ratio<1, 1>, degree_ratio>(value.value());
        bool negative = degrees_value < 0.0;
        double total_seconds = std::abs(degrees_value) * 3600.0;

        int degrees = static_cast<int>(total_seconds / 3600.0);
        double remainder = total_seconds - static_cast<double>(degrees) * 3600.0;
        int minutes = static_cast<int>(remainder / 60.0);
        double seconds = remainder - static_cast<double>(minutes) * 60.0;
        long long seconds_rounded = std::llround(seconds);
        if (seconds_rounded >= 60)
        {
            seconds_rounded = 0;
            ++minutes;
            if (minutes >= 60)
            {
                minutes = 0;
                ++degrees;
            }
        }

        auto out = ctx.out();
        if (negative)
        {
            *out++ = static_cast<CharT>('-');
        }

        if constexpr (std::is_same_v<CharT, char>)
        {
            out = std::format_to(out, "{}", PKR_UNITS_NAMESPACE::dms_degree_t{static_cast<double>(degrees)});
            *out++ = ' ';
            out = std::format_to(out, "{}", PKR_UNITS_NAMESPACE::dms_arcminute_t{static_cast<double>(minutes)});
            *out++ = ' ';
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            out = std::format_to(out, L"{}", PKR_UNITS_NAMESPACE::dms_degree_t{static_cast<double>(degrees)});
            out = std::format_to(out, L"{}", PKR_UNITS_NAMESPACE::dms_arcminute_t{static_cast<double>(minutes)});
        }
        else
        {
            static_assert(std::is_same_v<CharT, char> || std::is_same_v<CharT, wchar_t>, "UTF-8 formatting is not supported for astronomical angle units");
        }

        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::format_to(out, "{}", PKR_UNITS_NAMESPACE::dms_arcsecond_t{static_cast<double>(seconds_rounded)});
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::format_to(out, L"{}", PKR_UNITS_NAMESPACE::dms_arcsecond_t{static_cast<double>(seconds_rounded)});
        }
        else
        {
            return out;
        }
    }
};

} // namespace std
