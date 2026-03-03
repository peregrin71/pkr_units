#pragma once

#include <string_view>
#include <optional>
#include <pkr_units/impl/parsing/parse_impl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>

namespace pkr::units::impl
{

// ============================================================================
// Forward Declarations
// ============================================================================

// Forward declarations for specialization
template <is_pkr_unit_c UnitT>
class measurement_lin_t;

template <is_pkr_unit_c UnitT>
class measurement_rss_t;

// ============================================================================
// Measurement Type Traits
// ============================================================================

/// Extract unit type from measurement_lin_t<UnitT> or measurement_rss_t<UnitT>
/// This trait is specialized for measurement types to access their internal unit type
template <typename MeasurementT>
struct measurement_unit_traits;

// Specialization for measurement_lin_t
template <is_pkr_unit_c UnitT>
struct measurement_unit_traits<measurement_lin_t<UnitT>>
{
    using type = UnitT;
    using value_type = typename UnitT::value_type;
};

// Specialization for measurement_rss_t
template <is_pkr_unit_c UnitT>
struct measurement_unit_traits<measurement_rss_t<UnitT>>
{
    using type = UnitT;
    using value_type = typename UnitT::value_type;
};

template <typename MeasurementT>
using measurement_unit_t = typename measurement_unit_traits<MeasurementT>::type;

template <typename MeasurementT>
using measurement_value_t = typename measurement_unit_traits<MeasurementT>::value_type;

// ============================================================================
// Measurement Parsing Implementation Details
// ============================================================================

/// Split measurement string into value, uncertainty, and symbol parts
/// Input format: "5.2 +/- 0.1 m" or "5.2 ± 0.1 m"
/// Returns: ("5.2", "0.1", "m")
template <typename CharT>
struct measurement_parts
{
    std::basic_string_view<CharT> value;
    std::basic_string_view<CharT> uncertainty;
    std::basic_string_view<CharT> symbol;
};

/// Parse measurement format into value, uncertainty, and symbol parts
/// Handles both "+/-" (ASCII) and "±" (Unicode) separators
template <typename CharT>
inline auto split_measurement_components(std::basic_string_view<CharT> input) -> std::optional<measurement_parts<CharT>>
{
    // Find the separator: "+/-" or "±" (for wide char)
    size_t sep_pos = input.npos;
    size_t sep_len = 0;

    // Try to find "+/-" separator
    if constexpr (std::is_same_v<CharT, char>)
    {
        const auto sep_str = std::string_view("+/-");
        sep_pos = input.find(sep_str);
        if (sep_pos != input.npos)
        {
            sep_len = 3;
        }
    }
    else if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        // Try to find "±" (U+00B1)
        const auto sep_str = std::wstring_view(L"\u00b1");
        sep_pos = input.find(sep_str);
        if (sep_pos != input.npos)
        {
            sep_len = 1;
        }
    }

    // If no separator found, invalid format
    if (sep_pos == input.npos)
    {
        return std::nullopt;
    }

    // Extract value part (before separator)
    auto value_part = input.substr(0, sep_pos);
    value_part = trim_right(value_part);

    // Extract uncertainty and symbol (after separator)
    auto remainder = input.substr(sep_pos + sep_len);
    remainder = trim_left(remainder);

    // Split uncertainty from symbol
    auto [uncertainty_part, symbol_part] = split_value_symbol<CharT>(remainder);
    uncertainty_part = trim_right(uncertainty_part);

    return measurement_parts<CharT>{value_part, uncertainty_part, symbol_part};
}

/// Trim leading whitespace
template <typename CharT>
inline std::basic_string_view<CharT> trim_left(std::basic_string_view<CharT> str)
{
    while (!str.empty() && (str.front() == static_cast<CharT>(' ') || str.front() == static_cast<CharT>('\t')))
    {
        str.remove_prefix(1);
    }
    return str;
}

} // namespace pkr::units::impl
