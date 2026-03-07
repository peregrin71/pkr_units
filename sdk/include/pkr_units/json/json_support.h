#pragma once

#include <string_view>
#include <array>
#include <charconv>
#include <pkr_units/expected.h>
#include <pkr_units/impl/parsing/parse.h>
#include <pkr_units/impl/parsing/parse_error.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>
#include <pkr_units/impl/concepts/unit_concepts.h>

namespace PKR_UNITS_NAMESPACE::json
{

// ============================================================================
// C++20 Character Type Helpers - Using concepts for type-safe dispatch
// ============================================================================

// Helper function to get JSON string literal based on character type (C++20)
template <is_narrow_char_c CharT>
[[nodiscard]] constexpr std::string_view get_json_value_key()
{
    return "\"value\":";
}

template <is_wide_char_c CharT>
[[nodiscard]] constexpr std::wstring_view get_json_value_key()
{
    return L"\"value\":";
}

template <is_narrow_char_c CharT>
[[nodiscard]] constexpr std::string_view get_json_unit_key()
{
    return ",\"unit\":\"";
}

template <is_wide_char_c CharT>
[[nodiscard]] constexpr std::wstring_view get_json_unit_key()
{
    return L",\"unit\":\"";
}

template <is_narrow_char_c CharT>
[[nodiscard]] constexpr std::string_view get_json_close_obj()
{
    return "\"}";
}

template <is_wide_char_c CharT>
[[nodiscard]] constexpr std::wstring_view get_json_close_obj()
{
    return L"\"}";
}

template <is_narrow_char_c CharT>
[[nodiscard]] constexpr std::string_view get_json_field_sep()
{
    return ",";
}

template <is_wide_char_c CharT>
[[nodiscard]] constexpr std::wstring_view get_json_field_sep()
{
    return L",";
}

template <is_narrow_char_c CharT>
[[nodiscard]] constexpr std::string_view get_json_open_obj()
{
    return "{";
}

template <is_wide_char_c CharT>
[[nodiscard]] constexpr std::wstring_view get_json_open_obj()
{
    return L"{";
}

template <is_narrow_char_c CharT>
[[nodiscard]] constexpr std::string_view get_json_uncertainty_key()
{
    return "\"uncertainty\":";
}

template <is_wide_char_c CharT>
[[nodiscard]] constexpr std::wstring_view get_json_uncertainty_key()
{
    return L"\"uncertainty\":";
}

// ============================================================================
// JSON Serialization: Generate complete JSON objects in static buffer
// ============================================================================

/// Serialize a unit to a JSON string representation.
/// Generates a complete JSON object: {"value":X,"unit":"symbol"}
///
/// Uses the static format buffer for zero-allocation serialization.
/// The returned string_view is valid until the next SDK call.
///
/// @tparam UnitT The unit type to serialize
/// @tparam CharT The character type (char or wchar_t)
/// @param unit The unit value to serialize
/// @return string_view containing the JSON object, or empty view on error
///
/// @example
/// ```cpp
/// meter_t<double> m{5.0};
/// auto json_str = json::serialize_unit_to_json_string(m);
/// // Result: {"value":5.0,"unit":"m"}
/// ```
template <is_pkr_unit_c UnitT, typename CharT = char>
auto serialize_unit_to_json_string(const UnitT& unit) -> std::basic_string_view<CharT>
{
    auto& buffer = impl::shared_buffer<CharT>::data();
    auto capacity = impl::shared_buffer<CharT>::capacity();

    auto symbol = impl::get_symbol_for_char<UnitT, CharT>::value();

    std::size_t offset = 0;

    // Opening brace
    if (offset + 1 > capacity)
        return {};
    buffer[offset++] = static_cast<CharT>('{');

    // "value": - Using C++20 concept-based helpers
    auto value_key = get_json_value_key<CharT>();

    if (offset + value_key.size() + 64 > capacity)
        return {};

    for (CharT c : value_key)
    {
        buffer[offset++] = c;
    }

    // Serialize numeric value using std::to_chars
    std::array<CharT, 64> num_buf{};
    auto [ptr, ec] = std::to_chars(num_buf.data(), num_buf.data() + num_buf.size(), unit.value());
    if (ec != std::errc())
        return {};

    std::size_t num_len = ptr - num_buf.data();
    if (offset + num_len > capacity)
        return {};

    for (std::size_t i = 0; i < num_len; ++i)
    {
        buffer[offset++] = num_buf[i];
    }

    // ,"unit":"symbol" - Using C++20 concept-based helpers
    auto unit_key = get_json_unit_key<CharT>();

    if (offset + unit_key.size() + symbol.size() + 2 > capacity)
        return {};

    for (CharT c : unit_key)
    {
        buffer[offset++] = c;
    }

    for (CharT c : symbol)
    {
        buffer[offset++] = c;
    }

    // Closing quote and brace - Using C++20 concept-based helpers
    auto close_obj = get_json_close_obj<CharT>();

    for (CharT c : close_obj)
    {
        buffer[offset++] = c;
    }

    return std::basic_string_view<CharT>(buffer, offset);
}

/// Serialize a measurement (with uncertainty) to a JSON string representation.
/// Generates a complete JSON object: {"value":X,"uncertainty":Y,"unit":"symbol"}
///
/// Uses the static format buffer for zero-allocation serialization.
/// The returned string_view is valid until the next SDK call.
///
/// @tparam MeasT The measurement type to serialize
/// @tparam CharT The character type (char or wchar_t)
/// @param meas The measurement value to serialize
/// @return string_view containing the JSON object, or empty view on error
///
/// @example
/// ```cpp
/// measurement_lin_t<meter_t<double>> m{meter_t<double>{5.0}, 0.1};
/// auto json_str = json::serialize_measurement_to_json_string(m);
/// // Result: {"value":5.0,"uncertainty":0.1,"unit":"m"}
/// ```
template <typename MeasT, typename CharT = char>
auto serialize_measurement_to_json_string(const MeasT& meas) -> std::basic_string_view<CharT>
{
    auto& buffer = impl::shared_buffer<CharT>::data();
    auto capacity = impl::shared_buffer<CharT>::capacity();

    using unit_type = typename MeasT::unit_type;
    auto symbol = impl::get_symbol_for_char<unit_type, CharT>::value();

    std::size_t offset = 0;

    // Opening brace
    if (offset + 1 > capacity)
        return {};
    buffer[offset++] = static_cast<CharT>('{');

    // "value": - Using C++20 concept-based helpers
    auto value_key = get_json_value_key<CharT>();

    if (offset + value_key.size() + 64 > capacity)
        return {};

    for (CharT c : value_key)
    {
        buffer[offset++] = c;
    }

    // Serialize value
    std::array<CharT, 64> val_buf{};
    auto [ptr1, ec1] = std::to_chars(val_buf.data(), val_buf.data() + val_buf.size(), meas.value());
    if (ec1 != std::errc())
        return {};

    std::size_t val_len = ptr1 - val_buf.data();
    if (offset + val_len > capacity)
        return {};

    for (std::size_t i = 0; i < val_len; ++i)
    {
        buffer[offset++] = val_buf[i];
    }

    // ,"uncertainty": - Using C++20 concept-based helpers
    auto uncert_key = get_json_uncertainty_key<CharT>();

    if (offset + uncert_key.size() + 64 > capacity)
        return {};

    for (CharT c : uncert_key)
    {
        buffer[offset++] = c;
    }

    // Serialize uncertainty
    std::array<CharT, 64> uncert_buf{};
    auto [ptr2, ec2] = std::to_chars(uncert_buf.data(), uncert_buf.data() + uncert_buf.size(), meas.uncertainty());
    if (ec2 != std::errc())
        return {};

    std::size_t uncert_len = ptr2 - uncert_buf.data();
    if (offset + uncert_len > capacity)
        return {};

    for (std::size_t i = 0; i < uncert_len; ++i)
    {
        buffer[offset++] = uncert_buf[i];
    }

    // ,"unit":"symbol" - Using C++20 concept-based helpers
    auto unit_key = get_json_unit_key<CharT>();

    if (offset + unit_key.size() + symbol.size() + 2 > capacity)
        return {};

    for (CharT c : unit_key)
    {
        buffer[offset++] = c;
    }

    for (CharT c : symbol)
    {
        buffer[offset++] = c;
    }

    // Closing quote and brace - Using C++20 concept-based helpers
    auto close_obj = get_json_close_obj<CharT>();

    for (CharT c : close_obj)
    {
        buffer[offset++] = c;
    }

    return std::basic_string_view<CharT>(buffer, offset);
}

// ============================================================================
// JSON Deserialization: Parse JSON strings using existing parse() functions
// ============================================================================

/// Helper function to extract a quoted string value from JSON
/// Finds the first occurrence of a key and extracts its string value.
template <typename CharT>
std::basic_string_view<CharT> extract_json_string(std::basic_string_view<CharT> json, std::basic_string_view<CharT> key)
{
    auto key_pos = json.find(key);
    if (key_pos == std::basic_string_view<CharT>::npos)
        return {};

    auto value_start = json.find(static_cast<CharT>('"'), key_pos + key.size());
    if (value_start == std::basic_string_view<CharT>::npos)
        return {};

    auto value_end = json.find(static_cast<CharT>('"'), value_start + 1);
    if (value_end == std::basic_string_view<CharT>::npos)
        return {};

    return json.substr(value_start + 1, value_end - value_start - 1);
}

/// Helper function to extract a numeric value from JSON
/// Finds the first occurrence of a key and extracts its numeric value.
template <typename CharT>
std::basic_string_view<CharT> extract_json_number(std::basic_string_view<CharT> json, std::basic_string_view<CharT> key)
{
    auto key_pos = json.find(key);
    if (key_pos == std::basic_string_view<CharT>::npos)
        return {};

    auto value_start = key_pos + key.size();

    // Skip whitespace
    while (value_start < json.size() && (json[value_start] == static_cast<CharT>(' ') || json[value_start] == static_cast<CharT>('\t')))
    {
        ++value_start;
    }

    auto value_end = value_start;
    while (value_end < json.size() && (std::isdigit(static_cast<unsigned char>(json[value_end])) || json[value_end] == static_cast<CharT>('.') ||
                                       json[value_end] == static_cast<CharT>('-') || json[value_end] == static_cast<CharT>('+') ||
                                       json[value_end] == static_cast<CharT>('e') || json[value_end] == static_cast<CharT>('E')))
    {
        ++value_end;
    }

    return json.substr(value_start, value_end - value_start);
}

/// Deserialize a JSON string to a unit.
/// Parses JSON in the form: {"value":X,"unit":"symbol"}
///
/// Uses the static format buffer to reconstruct "X symbol" and feeds
/// it to the existing parse<TargetUnit>() for validation and conversion.
///
/// @tparam TargetUnit The target unit type to deserialize into
/// @tparam CharT The character type (char or wchar_t)
/// @param json_str The JSON string to parse
/// @return expected_t containing the parsed unit or a parse_error
///
/// @example
/// ```cpp
/// auto result = json::deserialize_unit_from_json_string<meter_t<double>>(
///     R"({"value":5.0,"unit":"m"})");
/// if (result) {
///     std::cout << result->value() << " m\n";  // 5.0 m
/// }
/// ```
template <is_pkr_unit_c TargetUnit, typename CharT = char>
auto deserialize_unit_from_json_string(std::basic_string_view<CharT> json_str) -> expected_t<TargetUnit, parse_error>
{
    // Extract "value" and "unit" fields from JSON using C++20 concept-based helpers
    auto value_key_str = get_json_value_key<CharT>();
    auto value_key = std::basic_string_view<CharT>(value_key_str.data(), 7); // "value"

    auto value_part = extract_json_number(json_str, value_key);
    if (value_part.empty())
    {
        return expected_t<TargetUnit, parse_error>{parse_error::numeric_parse_error};
    }

    std::basic_string_view<CharT> unit_key;
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        constexpr std::wstring_view unit_key_wide = L"\"unit\"";
        unit_key = unit_key_wide;
    }
    else
    {
        constexpr std::string_view unit_key_ascii = "\"unit\"";
        unit_key = unit_key_ascii;
    }

    auto unit_part = extract_json_string(json_str, unit_key);
    if (unit_part.empty())
    {
        return expected_t<TargetUnit, parse_error>{parse_error::symbol_mismatch};
    }

    // Reconstruct "value unit" in shared buffer
    auto& buffer = impl::shared_buffer<CharT>::data();
    auto capacity = impl::shared_buffer<CharT>::capacity();

    std::size_t offset = 0;

    if (offset + value_part.size() + 1 + unit_part.size() > capacity)
    {
        return expected_t<TargetUnit, parse_error>{parse_error::numeric_parse_error};
    }

    // Copy value part
    for (CharT c : value_part)
    {
        buffer[offset++] = c;
    }

    // Add space separator
    buffer[offset++] = static_cast<CharT>(' ');

    // Copy unit part
    for (CharT c : unit_part)
    {
        buffer[offset++] = c;
    }

    // Use standard parse with reconstructed string
    return parse<TargetUnit, CharT>(std::basic_string_view<CharT>(buffer, offset));
}

/// Deserialize a JSON string to a measurement (with uncertainty).
/// Parses JSON in the form: {"value":X,"uncertainty":Y,"unit":"symbol"}
///
/// Uses the static format buffer to reconstruct "X +/- Y symbol" and feeds
/// it to the existing parse_measurement<TargetMeasurement>().
///
/// @tparam TargetMeasurement The target measurement type to deserialize into
/// @tparam CharT The character type (char or wchar_t)
/// @param json_str The JSON string to parse
/// @return expected_t containing the parsed measurement or a parse_error
///
/// @example
/// ```cpp
/// auto result = json::deserialize_measurement_from_json_string<
///     measurement_lin_t<meter_t<double>>>(
///     R"({"value":5.0,"uncertainty":0.1,"unit":"m"})");
/// if (result) {
///     std::cout << result->value() << " ± " << result->uncertainty() << " m\n";
/// }
/// ```
template <typename TargetMeasurement, typename CharT = char>
auto deserialize_measurement_from_json_string(std::basic_string_view<CharT> json_str) -> expected_t<TargetMeasurement, parse_error>
{
    // Extract "value", "uncertainty", and "unit" fields from JSON
    std::basic_string_view<CharT> value_key;
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        constexpr std::wstring_view value_key_wide = L"\"value\"";
        value_key = value_key_wide;
    }
    else
    {
        constexpr std::string_view value_key_ascii = "\"value\"";
        value_key = value_key_ascii;
    }

    auto value_part = extract_json_number(json_str, value_key);
    if (value_part.empty())
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    std::basic_string_view<CharT> uncert_key;
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        constexpr std::wstring_view uncert_key_wide = L"\"uncertainty\"";
        uncert_key = uncert_key_wide;
    }
    else
    {
        constexpr std::string_view uncert_key_ascii = "\"uncertainty\"";
        uncert_key = uncert_key_ascii;
    }

    auto uncert_part = extract_json_number(json_str, uncert_key);
    if (uncert_part.empty())
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    std::basic_string_view<CharT> unit_key;
    if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        constexpr std::wstring_view unit_key_wide = L"\"unit\"";
        unit_key = unit_key_wide;
    }
    else
    {
        constexpr std::string_view unit_key_ascii = "\"unit\"";
        unit_key = unit_key_ascii;
    }

    auto unit_part = extract_json_string(json_str, unit_key);
    if (unit_part.empty())
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::symbol_mismatch};
    }

    // Get the separator for this character type
    auto separator = impl::char_traits_dispatch<CharT>::plus_minus();

    // Reconstruct "value +/- uncertainty unit" in shared buffer
    auto& buffer = impl::shared_buffer<CharT>::data();
    auto capacity = impl::shared_buffer<CharT>::capacity();

    std::size_t offset = 0;

    std::size_t needed = value_part.size() + separator.size() + uncert_part.size() + 1 + unit_part.size();
    if (needed > capacity)
    {
        return expected_t<TargetMeasurement, parse_error>{parse_error::numeric_parse_error};
    }

    // Copy value
    for (CharT c : value_part)
    {
        buffer[offset++] = c;
    }

    // Copy separator
    for (CharT c : separator)
    {
        buffer[offset++] = c;
    }

    // Copy uncertainty
    for (CharT c : uncert_part)
    {
        buffer[offset++] = c;
    }

    // Add space separator
    buffer[offset++] = static_cast<CharT>(' ');

    // Copy unit
    for (CharT c : unit_part)
    {
        buffer[offset++] = c;
    }

    // Use standard parse_measurement with reconstructed string
    return parse_measurement<TargetMeasurement, CharT>(std::basic_string_view<CharT>(buffer, offset));
}

} // namespace PKR_UNITS_NAMESPACE::json
