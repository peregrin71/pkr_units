#pragma once

#include <format>
#include <string>
#include "impl/namespace_config.h"
#include "impl/common/unit.h"

PKR_UNITS_BEGIN_NAMESPACE
{

namespace formatting
{

// Helper function to format dimension as canonical SI string
inline std::string format_dimension(const details::dimension_t& dim)
{
    std::string result;
    
    struct unit_info
    {
        int exponent;
        std::string_view symbol;
    };
    
    unit_info units[] = {
        {dim.length, "m"},
        {dim.mass, "kg"},
        {dim.time, "s"},
        {dim.current, "A"},
        {dim.temperature, "K"},
        {dim.amount, "mol"},
        {dim.intensity, "cd"}
    };
    
    // First pass: positive exponents
    for (const auto& unit : units)
    {
        if (unit.exponent > 0)
        {
            if (!result.empty())
                result += "·";
            
            result += unit.symbol;
            if (unit.exponent > 1)
            {
                result += std::to_string(unit.exponent);
            }
        }
    }
    
    // Second pass: negative exponents
    for (const auto& unit : units)
    {
        if (unit.exponent < 0)
        {
            if (!result.empty())
                result += "·";
            
            result += unit.symbol;
            result += std::to_string(unit.exponent);
        }
    }
    
    return result.empty() ? "1" : result;
}  // namespace PKR_UNITS_NAMESPACE
} // namespace formatting

} }  // namespace PKR_UNITS_NAMESPACE

// ============================================================================
// Standard Library std::formatter Specializations (outside namespace)
// ============================================================================

// Generic formatter for unit_t<type_t, ratio_t, dimension_t>
template<typename type_t, typename ratio_t, pkr::units::details::dimension_t dim_v>
struct std::formatter<pkr::units::details::unit_t<type_t, ratio_t, dim_v>>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }
    
    auto format(const pkr::units::details::unit_t<type_t, ratio_t, dim_v>& unit, 
                std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{} {}",
                             unit.value(),
                             pkr::units::formatting::format_dimension(dim_v));
    }
};

// Specialization for derived unit types with static symbol metadata
// This uses a requires clause to check if the type has a static symbol member
template<typename T>
    requires (requires { { T::symbol } -> std::convertible_to<std::string_view>; } && 
              pkr::units::details::is_si_unit<T>::value)
struct std::formatter<T>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }
    
    auto format(const T& unit, std::format_context& ctx) const
    {
        // For types with static symbol, use the symbol directly
        return std::format_to(ctx.out(), "{} {}",
                             unit.value(),
                             T::symbol);
    }
};
