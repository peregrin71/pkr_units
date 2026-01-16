// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <format>
#include <cmath>
#include <si_units/impl/details/si_unit.h>
#include <si_units/standard/length.h>
#include <si_units/standard/mass.h>
#include <si_units/imperial/length.h>
#include <si_units/imperial/mass.h>

namespace std
{

// Generic formatter for all other unit_t types
template<typename type_t, typename ratio_t, si::dimension_t dim>
struct formatter<si::unit_t<type_t, ratio_t, dim>>
{
    std::formatter<type_t> m_value_formatter;

    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return m_value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    auto format(const si::unit_t<type_t, ratio_t, dim>& unit, FormatContext& ctx) const
    {
        // Get unit type for formatting decisions
        constexpr auto unit_type = si::unit_t<type_t, ratio_t, dim>::unit_type;
        auto base_unit = si::get_si_unit_symbol(unit_type);

        // Get the prefix based on ratio
        auto prefix = get_prefix<ratio_t>();

        // Get the exponent suffix based on dimension
        auto exponent_suffix = get_exponent_suffix<dim>();

        // Format the value using the underlying formatter
        // This will apply any precision/width specs from the format context
        auto out = m_value_formatter.format(unit.value(), ctx);
        
        // Append the unit symbol and exponent suffix
        out = std::format_to(out, " {}{}{}", prefix, base_unit, exponent_suffix);
        return out;
    }

private:
    // Constexpr helper to format dimension exponent as string like "^2", "^3", etc.
    template<int exponent>
    static constexpr auto format_exponent() noexcept
    {
        // Create a constexpr string with format "^{digit}"
        constexpr std::array<char, 3> chars = {'^', static_cast<char>('0' + (exponent % 10)), '\0'};
        return chars;
    }

    template<si::dimension_t dim>
    static constexpr std::string_view get_exponent_formatted() noexcept
    {
        if constexpr (dim.length == 1)
        {
            return ""; // No exponent for linear dimension
        }
        else if constexpr (dim.length == 2)
        {
            return "²";
        }
        else if constexpr (dim.length == 3)
        {
            return "³";
        }
        else if constexpr (dim.length < 10)
        {
            // For dimensions 4-9, use static formatted strings
            static constexpr auto formatted = format_exponent<dim.length>();
            return std::string_view(formatted.data(), 2); // "^n"
        }
        else
        {
            // For dimensions >= 10, return generic format
            return "^n"; // General format for higher exponents
        }
    }

    template<typename ratio_t>
    static constexpr std::string_view get_prefix() noexcept
    {
        // Metric prefixes (SI)
        if constexpr (std::is_same_v<ratio_t, std::atto>)
            return "a";
        if constexpr (std::is_same_v<ratio_t, std::femto>)
            return "f";
        if constexpr (std::is_same_v<ratio_t, std::pico>)
            return "p";
        if constexpr (std::is_same_v<ratio_t, std::nano>)
            return "n";
        if constexpr (std::is_same_v<ratio_t, std::micro>)
            return "μ";
        if constexpr (std::is_same_v<ratio_t, std::milli>)
            return "m";
        if constexpr (std::is_same_v<ratio_t, std::centi>)
            return "c";
        if constexpr (std::is_same_v<ratio_t, std::deci>)
            return "d";
        if constexpr (std::is_same_v<ratio_t, std::deca>)
            return "da";
        if constexpr (std::is_same_v<ratio_t, std::hecto>)
            return "h";
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 1>>)
            return ""; // No prefix for base unit
        if constexpr (std::is_same_v<ratio_t, std::kilo>)
            return "k";
        if constexpr (std::is_same_v<ratio_t, std::mega>)
            return "M";
        if constexpr (std::is_same_v<ratio_t, std::giga>)
            return "G";
        if constexpr (std::is_same_v<ratio_t, std::tera>)
            return "T";
        if constexpr (std::is_same_v<ratio_t, std::peta>)
            return "P";
        if constexpr (std::is_same_v<ratio_t, std::exa>)
            return "E";

        // Imperial and special units - no prefix
        if constexpr (std::is_same_v<ratio_t, std::ratio<254, 10000>>)
            return ""; // inch
        if constexpr (std::is_same_v<ratio_t, std::ratio<254, 10000000>>)
            return ""; // mil
        if constexpr (std::is_same_v<ratio_t, std::ratio<3048, 10000>>)
            return ""; // foot
        if constexpr (std::is_same_v<ratio_t, std::ratio<9144, 10000>>)
            return ""; // yard
        if constexpr (std::is_same_v<ratio_t, std::ratio<18288, 10000>>)
            return ""; // fathom
        if constexpr (std::is_same_v<ratio_t, std::ratio<50292, 10000>>)
            return ""; // rod
        if constexpr (std::is_same_v<ratio_t, std::ratio<201168, 10000>>)
            return ""; // chain
        if constexpr (std::is_same_v<ratio_t, std::ratio<201168, 1000>>)
            return ""; // furlong
        if constexpr (std::is_same_v<ratio_t, std::ratio<1609344, 1000>>)
            return ""; // mile
        if constexpr (std::is_same_v<ratio_t, std::ratio<1852, 1>>)
            return ""; // nautical mile

        // Astronomical and other units
        if constexpr (std::is_same_v<ratio_t, std::ratio<1, 10000000000>>)
            return ""; // angstrom
        if constexpr (std::is_same_v<ratio_t, std::ratio<149597870700, 1>>)
            return ""; // au
        if constexpr (std::is_same_v<ratio_t, std::ratio<9460730472580800, 1>>)
            return ""; // light-year
        if constexpr (std::is_same_v<ratio_t, std::ratio<30856775814913673, 1>>)
            return ""; // parsec
    }

    template<si::dimension_t dim>
    static constexpr std::string_view get_exponent_suffix() noexcept
    {
        return get_exponent_formatted<dim>();
    }
};
} // namespace std








