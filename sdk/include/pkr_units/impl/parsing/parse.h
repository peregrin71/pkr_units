#pragma once

#include <string_view>
#include <optional>
#include <pkr_units/expected.h>
#include <pkr_units/impl/parsing/parse_error.h>
#include <pkr_units/impl/parsing/parse_impl.h>
#include <pkr_units/impl/parsing/parse_measurement_impl.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/measurements/decl/measurement_lin_decl.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>

namespace pkr::units
{

// ============================================================================
// Parse function with explicit target unit type
// ============================================================================

/// Parse a string into a unit with automatic dimension validation
///
/// Parses input in the form "numeric_value symbol" and converts to the target unit.
/// Automatically detects float vs double from the numeric suffix (f/F for float).
///
/// @tparam TargetUnit The target unit type to parse into
/// @tparam CharT Character type (char or wchar_t)
/// @param input Input string in format "numeric_value symbol"
/// @return expected_t containing the parsed unit or a parse_error
///
/// @example
/// ```cpp
/// // Parse meters
/// auto result = parse<meter_t<double>>("5.2 m");
/// if (result) {
///     std::cout << result->value() << " m\n";  // 5.2 m
/// }
///
/// // Parse with precision loss handling
/// auto result = parse<meter_t<float>>("5.123456789 m");
/// if (result) {
///     std::cout << result->value() << " m\n";  // ~5.1235 m
/// }
///
/// // Wide character parsing
/// auto result = parse<meter_t<double>, wchar_t>(L"5.2 m");
/// if (result) {
///     std::wcout << result->value() << L" m\n";
/// }
/// ```
template <is_pkr_unit_c TargetUnit, typename CharT = char>
auto parse(std::basic_string_view<CharT> input) -> expected_t<TargetUnit, parse_error>
{
    // Trim whitespace
    while (!input.empty() && (input.front() == static_cast<CharT>(' ') || input.front() == static_cast<CharT>('\t')))
    {
        input.remove_prefix(1);
    }
    input = impl::trim_right(input);

    // Split input: "5.2 m" → ("5.2", "m")
    auto [numeric_part, symbol_part] = impl::split_value_symbol<CharT>(input);

    // Trim numeric part
    numeric_part = impl::trim_right(numeric_part);

    // Parse numeric value
    auto numeric_value = impl::parse_numeric<CharT, typename TargetUnit::value_type>(numeric_part);
    if (!numeric_value)
    {
        return expected_t<TargetUnit, parse_error>{parse_error::numeric_parse_error};
    }

    // Check if symbol (if provided) matches target unit (dimension validation)
    // If no symbol is provided, default to the target unit type
    if (!symbol_part.empty() && !impl::symbol_matches<TargetUnit, CharT>(symbol_part))
    {
        return expected_t<TargetUnit, parse_error>{parse_error::symbol_mismatch};
    }

    // Construct the unit with the parsed value
    return expected_t<TargetUnit, parse_error>{TargetUnit{*numeric_value}};
}

/// Overload for const CharT* strings
template <is_pkr_unit_c TargetUnit, typename CharT = char>
inline auto parse(const CharT* input) -> expected_t<TargetUnit, parse_error>
{
    return parse<TargetUnit, CharT>(std::basic_string_view<CharT>{input});
}

// ============================================================================
// Parse function for measurement_lin_t (linear uncertainty)
// ============================================================================

/// Parse a string into a measurement_lin_t with automatic dimension validation
///
/// Parses input in the form "numeric_value +/- uncertainty symbol" and converts
/// to the target measurement type. The separator can be "+/-" (ASCII) or "±" (Unicode).
///
/// @tparam TargetMeasurement The target measurement_lin_t type
/// @tparam CharT Character type (char or wchar_t)
/// @param input Input string in format "numeric_value +/- uncertainty symbol"
/// @return expected_t containing the parsed measurement or a parse_error
///
/// @example
/// ```cpp
/// // Parse linear measurement
/// auto result = parse_linear<measurement_lin_t<meter_t<double>>>("5.2 +/- 0.1 m");
/// if (result) {
///     std::cout << result->value() << " +/- " << result->uncertainty() << " m\n";
/// }
///
/// // Wide character parsing with ± separator
/// auto result = parse_linear<measurement_lin_t<meter_t<double>>, wchar_t>(
///     L"5.2 ± 0.1 m"
/// );
/// ```
template <typename TargetMeasurement, typename CharT = char>
    requires is_measurement_lin_c<TargetMeasurement>
auto parse_linear(std::basic_string_view<CharT> input) -> expected_t<TargetMeasurement, parse_error>
{
    using unit_type = impl::measurement_unit_t<TargetMeasurement>;
    using value_type = impl::measurement_value_t<TargetMeasurement>;

    // Trim whitespace
    while (!input.empty() && (input.front() == static_cast<CharT>(' ') || input.front() == static_cast<CharT>('\t')))
    {
        input.remove_prefix(1);
    }
    input = impl::trim_right(input);

    // Split measurement: "5.2 +/- 0.1 m" → (value, uncertainty, symbol)
    auto parts = impl::split_measurement_components<CharT>(input);
    if (!parts)
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    // Parse numeric value
    auto value_result = impl::parse_numeric<CharT, value_type>(parts->value);
    if (!value_result)
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    // Parse uncertainty value
    auto uncertainty_result = impl::parse_numeric<CharT, value_type>(parts->uncertainty);
    if (!uncertainty_result)
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    // Check if symbol is empty - measurements must have units
    if (parts->symbol.empty())
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::unknown_symbol};
    }

    // Verify symbol matches target unit (dimension validation)
    if (!impl::symbol_matches<unit_type, CharT>(parts->symbol))
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::symbol_mismatch};
    }

    // Construct the measurement with parsed values
    auto value_unit = unit_type{*value_result};
    auto uncertainty_unit = unit_type{*uncertainty_result};
    return expected_t<TargetMeasurement, parse_error>{TargetMeasurement{value_unit, uncertainty_unit}};
}

/// Overload for const CharT* strings
template <typename TargetMeasurement, typename CharT = char>
    requires is_measurement_lin_c<TargetMeasurement>
inline auto parse_linear(const CharT* input) -> expected_t<TargetMeasurement, parse_error>
{
    return parse_linear<TargetMeasurement, CharT>(std::basic_string_view<CharT>{input});
}

// ============================================================================
// Parse function for measurement_rss_t (RSS uncertainty)
// ============================================================================

/// Parse a string into a measurement_rss_t with automatic dimension validation
///
/// Parses input in the form "numeric_value ± uncertainty symbol" and converts
/// to the target measurement type. The separator can be "+/-" (ASCII) or "±" (Unicode).
///
/// @tparam TargetMeasurement The target measurement_rss_t type
/// @tparam CharT Character type (char or wchar_t)
/// @param input Input string in format "numeric_value ± uncertainty symbol"
/// @return expected_t containing the parsed measurement or a parse_error
///
/// @example
/// ```cpp
/// // Parse RSS measurement
/// auto result = parse_rss<measurement_rss_t<meter_t<double>>>("5.2 +/- 0.1 m");
/// if (result) {
///     std::cout << result->value() << " +/- " << result->uncertainty() << " m\n";
/// }
///
/// // Wide character parsing with ± separator
/// auto result = parse_rss<measurement_rss_t<meter_t<double>>, wchar_t>(
///     L"5.2 ± 0.1 m"
/// );
/// ```
template <typename TargetMeasurement, typename CharT = char>
    requires is_measurement_rss_c<TargetMeasurement>
auto parse_rss(std::basic_string_view<CharT> input) -> expected_t<TargetMeasurement, parse_error>
{
    using unit_type = impl::measurement_unit_t<TargetMeasurement>;
    using value_type = impl::measurement_value_t<TargetMeasurement>;

    // Trim whitespace
    while (!input.empty() && (input.front() == static_cast<CharT>(' ') || input.front() == static_cast<CharT>('\t')))
    {
        input.remove_prefix(1);
    }
    input = impl::trim_right(input);

    // Split measurement: "5.2 ± 0.1 m" → (value, uncertainty, symbol)
    auto parts = impl::split_measurement_components<CharT>(input);
    if (!parts)
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    // Parse numeric value
    auto value_result = impl::parse_numeric<CharT, value_type>(parts->value);
    if (!value_result)
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    // Parse uncertainty value
    auto uncertainty_result = impl::parse_numeric<CharT, value_type>(parts->uncertainty);
    if (!uncertainty_result)
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    // Check if symbol is empty - measurements must have units
    if (parts->symbol.empty())
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::unknown_symbol};
    }

    // Verify symbol matches target unit (dimension validation)
    if (!impl::symbol_matches<unit_type, CharT>(parts->symbol))
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::symbol_mismatch};
    }

    // Construct the measurement with parsed values
    auto value_unit = unit_type{*value_result};
    auto uncertainty_unit = unit_type{*uncertainty_result};
    return expected_t<TargetMeasurement, parse_error>{TargetMeasurement{value_unit, uncertainty_unit}};
}

/// Overload for const CharT* strings
template <typename TargetMeasurement, typename CharT = char>
    requires is_measurement_rss_c<TargetMeasurement>
inline auto parse_rss(const CharT* input) -> expected_t<TargetMeasurement, parse_error>
{
    return parse_rss<TargetMeasurement, CharT>(std::basic_string_view<CharT>{input});
}

} // namespace pkr::units
