// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <format>
#include <cmath>

namespace std
{

// Explicit specialization for si::ounce
template<>
struct formatter<::si::ounce>
{
    std::formatter<double> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const ::si::ounce& unit, FormatContext& ctx) const
    {
        double ounces_value = unit.value();
        double whole_ounces = std::round(ounces_value);

        auto out = ctx.out();
        out = std::format_to(out, "{} oz", static_cast<int>(whole_ounces));
        return out;
    }
};

// Explicit specialization for si::pound
template<>
struct formatter<::si::pound>
{
    std::formatter<double> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const ::si::pound& unit, FormatContext& ctx) const
    {
        double pounds_value = unit.value();
        double whole_pounds = std::floor(pounds_value);
        double fractional_pounds = pounds_value - whole_pounds;

        // Convert fractional pounds to ounces (16 ounces = 1 pound)
        double ounces = fractional_pounds * 16.0;
        double whole_ounces = std::round(ounces);

        // Handle rounding edge case where ounces rounds to 16
        if (whole_ounces >= 16.0)
        {
            whole_pounds += 1.0;
            whole_ounces = 0.0;
        }

        // Format as: "{pounds} lb {ounces} oz"
        auto out = ctx.out();
        
        // Always output the pounds part (even if 0)
        out = std::format_to(out, "{} lb", static_cast<int>(whole_pounds));

        // Output ounces part only if non-zero
        if (whole_ounces > 0.0)
        {
            out = std::format_to(out, " {} oz", static_cast<int>(whole_ounces));
        }

        return out;
    }
};

} // namespace std






