#pragma once

/// @file si_units_formatters.h
/// @brief Comprehensive std::format support for SI units
/// 
/// This header provides std::formatter specializations for SI unit types,
/// including support for three character encoding types:
/// - char (ASCII) - use "u" for micro prefix
/// - char8_t (UTF-8) - use "μ" for micro prefix
/// - wchar_t (wide) - use "μ" for micro prefix

#include <si_units/formatting/length_formatter.h>
#include <si_units/formatting/mass_formatter.h>
#include <si_units/formatting/time_formatter.h>
#include <si_units/formatting/current_formatter.h>
#include <si_units/formatting/temperature_formatter.h>
#include <si_units/formatting/amount_formatter.h>
#include <si_units/formatting/intensity_formatter.h>
#include <si_units/formatting/velocity_formatter.h>
