// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <format>
#include <cmath>

namespace std
{

// Explicit specialization for si::foot
template<>
struct formatter<::si::foot>
{
    std::formatter<double> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const ::si::foot& unit, FormatContext& ctx) const
    {
        double feet_value = unit.value();
        double whole_feet = std::floor(feet_value);
        double fractional_feet = feet_value - whole_feet;

        // Convert fractional feet to inches (12 inches = 1 foot)
        double inches = fractional_feet * 12.0;
        double whole_inches = std::round(inches);

        // Handle rounding edge case where inches rounds to 12
        if (whole_inches >= 12.0)
        {
            whole_feet += 1.0;
            whole_inches = 0.0;
        }

        // Format as: "{feet}'{inches}\""
        auto out = ctx.out();
        
        // Always output the feet part (even if 0)
        out = std::format_to(out, "{}'", static_cast<int>(whole_feet));

        // Output inches part only if non-zero
        if (whole_inches > 0.0)
        {
            out = std::format_to(out, "{}", static_cast<int>(whole_inches));
            out = std::format_to(out, "\"");
        }

        return out;
    }
};

// Explicit specialization for si::inch
template<>
struct formatter<::si::inch>
{
    std::formatter<double> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const ::si::inch& unit, FormatContext& ctx) const
    {
        double inches_value = unit.value();
        double whole_inches = std::round(inches_value);

        auto out = ctx.out();
        out = std::format_to(out, "{}\"", static_cast<int>(whole_inches));
        return out;
    }
};

} // namespace std






