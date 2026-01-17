// Copyright (c) 2026
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#pragma once

#include <array>
#include <ratio>
#include <format>
#include <string>

PKR_SI_BEGIN_NAMESPACE {
    namespace formatting {

// Helper to detect if a type has _base member
template<typename T, typename = void>
struct has_base_member : std::false_type {};

template<typename T>
struct has_base_member<T, std::void_t<typename T::_base>> : std::true_type {};

// Primary template - for unit_t derived struct with _base member
template<typename Unit, bool HasBase = has_base_member<Unit>::value>
struct generic_unit_deducer_impl;

// Specialization for types WITH _base member
template<typename Unit>
struct generic_unit_deducer_impl<Unit, true> {
    using base_unit = typename Unit::_base;
    using dimension_type = decltype(Unit::_base::dimension::value);
    using ratio_type = typename Unit::_base::ratio_type;
};

// Specialization for unit_t types WITHOUT _base member (direct unit_t instances)
template<typename Unit>
struct generic_unit_deducer_impl<Unit, false> {
    using base_unit = Unit;
    using dimension_type = decltype(Unit::dimension::value);
    using ratio_type = typename Unit::ratio_type;
};

/**
 * Generic Unit Formatter for any unit_t type
 * 
 * All units now follow the pattern of having a _base member that refers to
 * the underlying unit_t<type_t, ratio_t, dimension_t> instantiation.
 * 
 * Example:
 *   struct meter : public unit_t<double, std::ratio<1,1>, length_dimension>
 *   {
 *       using _base = unit_t<double, std::ratio<1,1>, length_dimension>;
 *       using _base::_base;
 *   };
 * 
 * The formatter extracts dimension and ratio information from unit_t instances.
 * 
 * Implements BIPM SI canonical ordering:
 * 1. Positive exponents first (in canonical dimension order)
 * 2. Negative exponents second (in canonical dimension order)
 * 3. Canonical order: length, mass, time, current, temperature, amount, intensity
 */
template<typename Unit>
struct generic_unit_deducer : generic_unit_deducer_impl<Unit> {
    
    // Helper: get base unit name for a dimension index
    static constexpr const char* base_unit_name(int index) noexcept {
        switch (index) {
            case 0: return "m";      // length
            case 1: return "kg";     // mass
            case 2: return "s";      // time
            case 3: return "A";      // current
            case 4: return "K";      // temperature
            case 5: return "mol";    // amount
            case 6: return "cd";     // intensity
            default: return "";
        }
    }
    
    // Helper: convert exponent to superscript (UTF-8)
    static constexpr const char* superscript_utf8(int8_t exp) noexcept {
        switch (exp) {
            case -5: return "⁻⁵";
            case -4: return "⁻⁴";
            case -3: return "⁻³";
            case -2: return "⁻²";
            case -1: return "⁻¹";
            case 0: return "";
            case 1: return "¹";
            case 2: return "²";
            case 3: return "³";
            case 4: return "⁴";
            case 5: return "⁵";
            default: return "";
        }
    }
    
    // Helper: convert exponent to caret notation (ASCII)
    static constexpr const char* superscript_ascii(int8_t exp) noexcept {
        switch (exp) {
            case -5: return "^-5";
            case -4: return "^-4";
            case -3: return "^-3";
            case -2: return "^-2";
            case -1: return "^-1";
            case 0: return "";
            case 1: return "^1";
            case 2: return "^2";
            case 3: return "^3";
            case 4: return "^4";
            case 5: return "^5";
            default: return "";
        }
    }
    
    // Get SI prefix from ratio
    static constexpr const char* get_prefix() noexcept {
        using impl = generic_unit_deducer_impl<Unit>;
        if (impl::ratio_type::num == 1000000000000LL && impl::ratio_type::den == 1) return "T";  // tera
        if (impl::ratio_type::num == 1000000000 && impl::ratio_type::den == 1) return "G";      // giga
        if (impl::ratio_type::num == 1000000 && impl::ratio_type::den == 1) return "M";         // mega
        if (impl::ratio_type::num == 1000 && impl::ratio_type::den == 1) return "k";            // kilo
        if (impl::ratio_type::num == 1 && impl::ratio_type::den == 1) return "";                // base
        if (impl::ratio_type::num == 1 && impl::ratio_type::den == 1000) return "m";            // milli
        if (impl::ratio_type::num == 1 && impl::ratio_type::den == 1000000) return "μ";         // micro
        if (impl::ratio_type::num == 1 && impl::ratio_type::den == 1000000000) return "n";      // nano
        return "";  // unknown
    }
    
    /**
     * Build canonical unit string from dimension
     * Format: positive_units(canonical_order) · negative_units(canonical_order)
     * Example: "kg⋅m⋅s⁻²" for force (not "s⁻²⋅kg⋅m")
     */
    static constexpr const char* build_unit_string() noexcept {
        // This would be implemented with constexpr string building
        // For now, return placeholder - actual implementation depends on use case
        return "unit";
    }
};

    }  // namespace formatting
}  // PKR_SI_NAMESPACE
