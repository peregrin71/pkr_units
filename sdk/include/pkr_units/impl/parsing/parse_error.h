#pragma once

namespace pkr::units
{

// Parse error enumeration
enum class parse_error
{
    numeric_parse_error, // Invalid floating point format
    symbol_mismatch,     // Wrong dimension (e.g., parsed feet, expected meters)
    unknown_symbol,      // Unrecognized unit symbol
};

} // namespace pkr::units
