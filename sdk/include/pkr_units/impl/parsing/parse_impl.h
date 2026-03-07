#pragma once

#include <string_view>
#include <optional>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/impl/formatting/unit_formatting_traits.h>

namespace pkr::units::impl
{

// ============================================================================
// Symbol trait system: Select appropriate symbol by character type
// ============================================================================

template <typename UnitT, typename CharT>
struct get_symbol_for_char;

template <typename UnitT>
struct get_symbol_for_char<UnitT, char>
{
    static constexpr auto value()
    {
        return UnitT::symbol;
    }
};

template <typename UnitT>
struct get_symbol_for_char<UnitT, wchar_t>
{
    static constexpr auto value()
    {
        return UnitT::w_symbol;
    }
};

// ============================================================================
// Numeric type deduction
// ============================================================================

enum class numeric_type
{
    DOUBLE,
    FLOAT
};

constexpr numeric_type deduce_numeric_type(std::string_view input)
{
    if (input.empty())
        return numeric_type::DOUBLE;

    // Skip whitespace at end
    size_t last_non_ws = input.find_last_not_of(" \t\n\r");
    if (last_non_ws == std::string_view::npos)
        return numeric_type::DOUBLE;

    char last_char = input[last_non_ws];
    if (last_char == 'f' || last_char == 'F')
        return numeric_type::FLOAT;

    return numeric_type::DOUBLE;
}

// Wide-char version
constexpr numeric_type deduce_numeric_type(std::wstring_view input)
{
    if (input.empty())
        return numeric_type::DOUBLE;

    // Skip whitespace at end
    size_t last_non_ws = input.find_last_not_of(L" \t\n\r");
    if (last_non_ws == std::wstring_view::npos)
        return numeric_type::DOUBLE;

    wchar_t last_char = input[last_non_ws];
    if (last_char == L'f' || last_char == L'F')
        return numeric_type::FLOAT;

    return numeric_type::DOUBLE;
}

// ============================================================================
// Input splitting: Separate numeric value from symbol
// ============================================================================

template <typename CharT>
struct split_result
{
    std::basic_string_view<CharT> numeric;
    std::basic_string_view<CharT> symbol;
};

template <typename CharT>
constexpr split_result<CharT> split_value_symbol(std::basic_string_view<CharT> input)
{
    // Find last space separator
    auto pos = input.rfind(static_cast<CharT>(' '));
    if (pos == std::basic_string_view<CharT>::npos)
    {
        // No space found - treat entire string as numeric part
        return {input, std::basic_string_view<CharT>{}};
    }
    return {input.substr(0, pos), input.substr(pos + 1)};
}

// Trim whitespace from right
template <typename CharT>
constexpr std::basic_string_view<CharT> trim_right(std::basic_string_view<CharT> str)
{
    while (!str.empty() && (str.back() == static_cast<CharT>(' ') || str.back() == static_cast<CharT>('\t') || str.back() == static_cast<CharT>('\n') ||
                            str.back() == static_cast<CharT>('\r')))
    {
        str.remove_suffix(1);
    }
    return str;
}

// ============================================================================
// Numeric value parsing
// ============================================================================

namespace
{
// Remove 'f' or 'F' suffix for float deduction before parsing
template <typename CharT>
constexpr std::basic_string_view<CharT> remove_float_suffix(std::basic_string_view<CharT> input)
{
    if (!input.empty())
    {
        CharT last = input.back();
        if (last == static_cast<CharT>('f') || last == static_cast<CharT>('F'))
        {
            return input.substr(0, input.size() - 1);
        }
    }
    return input;
}
} // namespace

template <typename ValueType>
std::optional<ValueType> parse_numeric_char(std::string_view numeric_str)
{
    try
    {
        // Use a stack buffer for small strings to avoid heap allocation in the common case
        // Most numeric literals are much less than 64 bytes
        std::array<char, 64> buffer{};
        std::string_view to_parse = numeric_str;

        if (numeric_str.size() < buffer.size())
        {
            // Copy to buffer and remove suffix in-place if needed
            std::copy(numeric_str.begin(), numeric_str.end(), buffer.begin());
            buffer[numeric_str.size()] = '\0';

            // Check and remove float suffix
            std::size_t actual_len = numeric_str.size();
            if (!numeric_str.empty() && (numeric_str.back() == 'f' || numeric_str.back() == 'F'))
            {
                actual_len--;
                buffer[actual_len] = '\0';
            }
            to_parse = std::string_view(buffer.data(), actual_len);
        }
        else
        {
            // Fallback to std::string only for oversized input (edge case)
            std::string num_str(numeric_str);
            if (!num_str.empty() && (num_str.back() == 'f' || num_str.back() == 'F'))
            {
                num_str.pop_back();
            }
            to_parse = num_str;
        }

        if constexpr (std::is_floating_point_v<ValueType>)
        {
            char* endptr = nullptr;
            double value = std::strtod(to_parse.data(), &endptr);
            if (endptr == to_parse.data() || endptr == nullptr)
            {
                return std::nullopt;
            }
            return static_cast<ValueType>(value);
        }
        else
        {
            // For non-floating point types, attempt conversion
            char* endptr = nullptr;
            long value = std::strtol(to_parse.data(), &endptr, 10);
            if (endptr == to_parse.data() || endptr == nullptr)
            {
                return std::nullopt;
            }
            return static_cast<ValueType>(value);
        }
    }
    catch (...)
    {
        return std::nullopt;
    }
}

template <typename ValueType>
std::optional<ValueType> parse_numeric_wchar(std::wstring_view numeric_str)
{
    try
    {
        // Use shared static buffer for string conversion
        // Avoids stack allocation, suitable for resource-constrained systems
        auto* buffer = shared_buffer<wchar_t>::data();
        const std::size_t capacity = shared_buffer<wchar_t>::capacity();

        const wchar_t* c_str;

        if (numeric_str.size() < capacity - 1) // -1 for null terminator
        {
            // Copy to shared buffer
            std::copy(numeric_str.begin(), numeric_str.end(), buffer);
            buffer[numeric_str.size()] = L'\0';
            c_str = buffer;
        }
        else
        {
            // Fallback to heap only for oversized strings (exceptional case)
            static thread_local std::wstring overflow_str;
            overflow_str = std::wstring(numeric_str);
            c_str = overflow_str.c_str();
        }

        // Create a view to remove the float suffix before parsing
        std::wstring_view to_parse{c_str};
        size_t parse_len = to_parse.size();
        if (!to_parse.empty() && (to_parse.back() == L'f' || to_parse.back() == L'F'))
        {
            parse_len--;
        }

        if constexpr (std::is_floating_point_v<ValueType>)
        {
            wchar_t* endptr = nullptr;
            double value = std::wcstod(c_str, &endptr);

            // Verify we consumed at least some characters before any suffix
            size_t consumed = static_cast<size_t>(endptr - c_str);
            if (consumed == 0 || consumed > parse_len)
            {
                return std::nullopt;
            }
            return static_cast<ValueType>(value);
        }
        else
        {
            // For non-floating point types, attempt conversion
            wchar_t* endptr = nullptr;
            long value = std::wcstol(c_str, &endptr, 10);

            // Verify we consumed at least some characters
            size_t consumed = static_cast<size_t>(endptr - c_str);
            if (consumed == 0 || consumed > parse_len)
            {
                return std::nullopt;
            }
            return static_cast<ValueType>(value);
        }
    }
    catch (...)
    {
        return std::nullopt;
    }
}

template <typename CharT, typename ValueType>
std::optional<ValueType> parse_numeric(std::basic_string_view<CharT> numeric_str)
{
    if constexpr (std::is_same_v<CharT, char>)
    {
        return parse_numeric_char<ValueType>(numeric_str);
    }
    else if constexpr (std::is_same_v<CharT, wchar_t>)
    {
        return parse_numeric_wchar<ValueType>(numeric_str);
    }
    else
    {
        // For other CharT types, convert to char first
        std::string narrow(numeric_str.begin(), numeric_str.end());
        return parse_numeric_char<ValueType>(narrow);
    }
}

// ============================================================================
// Symbol matching
// ============================================================================

template <is_pkr_unit_c TargetUnit, typename CharT>
constexpr bool symbol_matches(std::basic_string_view<CharT> symbol)
{
    return symbol == get_symbol_for_char<TargetUnit, CharT>::value();
}

} // namespace pkr::units::impl
