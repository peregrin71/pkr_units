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


