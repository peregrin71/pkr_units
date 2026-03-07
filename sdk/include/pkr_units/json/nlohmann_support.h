#pragma once

/// @file nlohmann_support.h
/// @brief Integration adapter for nlohmann/json with pkr_units
///
/// This header provides Argument-Dependent Lookup (ADL) specializations
/// that allow nlohmann/json to seamlessly serialize and deserialize pkr_units
/// types without any modification to the pkr_units library itself.
///
/// @usage
/// ```cpp
/// #include <nlohmann/json.hpp>
/// #include <pkr_units/pkr_units.h>
/// #include <pkr_units/json/nlohmann_support.h>
///
/// using json = nlohmann::json;
/// using namespace pkr::units;
///
/// // Serialize a unit
/// meter_t<double> distance{5.0};
/// json j = distance;
/// std::cout << j.dump() << "\n";  // {"unit":"m","value":5.0}
///
/// // Deserialize a unit
/// json data = json::parse(R"({"value":10.0,"unit":"km"})");
/// kilometer_t<double> parsed = data;
/// ```
///
/// @warning
/// This header requires nlohmann/json to be included BEFORE this file.
/// The static format buffer used by JSON serialization is NOT thread-safe.
/// Protect concurrent access with a mutex if needed.
///
/// This header is for convenience and does not require any dependencies on nlohmann/json in the core pkr_units library.
/// To be able to use it you must add a dependency on nlohmann/json in your project and include this header after including nlohmann/json.
///

#ifdef NLOHMANN_JSON_HPP

#include <pkr_units/json/json.h>
#include <pkr_units/impl/concepts/unit_concepts.h>
#include <pkr_units/units/unit_series.h>

namespace nlohmann
{

// ============================================================================
// Specialization for unit types
// ============================================================================

/// Serialization adapter for pkr_units unit types with nlohmann/json.
/// Enables automatic serialization/deserialization of any unit type.
template <typename UnitT>
    requires PKR_UNITS_NAMESPACE::is_pkr_unit_c<UnitT>
struct adl_serializer<UnitT>
{
    /// Serialize a unit to nlohmann/json
    ///
    /// Converts the unit to a JSON object with "value" and "unit" fields.
    /// The JSON object is parsed from the string representation.
    ///
    /// @param j The nlohmann/json object to populate
    /// @param unit The unit to serialize
    static void to_json(json& j, const UnitT& unit)
    {
        // Generate JSON string using pkr_units SDK
        auto json_str = PKR_UNITS_NAMESPACE::json::serialize_unit_to_json_string(unit);

        if (json_str.empty())
        {
            j = json::object();
            return;
        }

        // Parse it into nlohmann/json object (using iterators avoids string copy)
        j = json::parse(json_str.begin(), json_str.end());
    }

    /// Deserialize a unit from nlohmann/json
    ///
    /// Extracts the unit from a JSON object and validates the dimension.
    /// Throws std::runtime_error if deserialization fails.
    ///
    /// @param j The nlohmann/json object to deserialize
    /// @param unit The unit to populate
    /// @throw std::runtime_error if the JSON is invalid or dimension mismatches
    static void from_json(const json& j, UnitT& unit)
    {
        // Serialize nlohmann/json back to string, then parse with pkr_units
        auto json_str = j.dump();

        auto result = PKR_UNITS_NAMESPACE::json::deserialize_unit_from_json_string<UnitT>(json_str);

        if (!result)
        {
            throw std::runtime_error("Failed to deserialize unit from JSON: " + json_str);
        }

        unit = *result;
    }
};

// ============================================================================
// Specialization for measurement_lin_t (linear uncertainty) - C++20 concept
// ============================================================================

/// Serialization adapter for measurement_lin_t with linear uncertainty.
/// Enables automatic serialization/deserialization of measurements.
template <typename MeasT>
    requires PKR_UNITS_NAMESPACE::is_measurement_lin_c<MeasT>
struct adl_serializer<MeasT>
{
    /// Serialize a linear measurement to nlohmann/json
    ///
    /// Converts the measurement to a JSON object with "value", "uncertainty",
    /// and "unit" fields.
    ///
    /// @param j The nlohmann/json object to populate
    /// @param meas The measurement to serialize
    static void to_json(json& j, const MeasT& meas)
    {
        // Generate JSON string using pkr_units SDK
        auto json_str = PKR_UNITS_NAMESPACE::json::serialize_measurement_to_json_string(meas);

        if (json_str.empty())
        {
            j = json::object();
            return;
        }

        // Parse it into nlohmann/json object (using iterators avoids string copy)
        j = json::parse(json_str.begin(), json_str.end());
    }

    /// Deserialize a linear measurement from nlohmann/json
    ///
    /// Extracts the measurement from a JSON object and validates the dimension.
    /// Throws std::runtime_error if deserialization fails.
    ///
    /// @param j The nlohmann/json object to deserialize
    /// @param meas The measurement to populate
    /// @throw std::runtime_error if the JSON is invalid or dimension mismatches
    static void from_json(const json& j, MeasT& meas)
    {
        // Serialize nlohmann/json back to string, then parse with pkr_units
        auto json_str = j.dump();

        auto result = PKR_UNITS_NAMESPACE::json::deserialize_measurement_from_json_string<MeasT>(json_str);

        if (!result)
        {
            throw std::runtime_error("Failed to deserialize measurement from JSON: " + json_str);
        }

        meas = *result;
    }
};

// ============================================================================
// Specialization for measurement_rss_t (RSS uncertainty) - C++20 concept
// ============================================================================

/// Serialization adapter for measurement_rss_t with RSS (root-sum-square) uncertainty.
/// Enables automatic serialization/deserialization of RSS measurements.
template <typename MeasT>
    requires PKR_UNITS_NAMESPACE::is_measurement_rss_c<MeasT>
struct adl_serializer<MeasT>
{
    /// Serialize an RSS measurement to nlohmann/json
    ///
    /// Converts the measurement to a JSON object with "value", "uncertainty",
    /// and "unit" fields. The uncertainty is the root-sum-square value.
    ///
    /// @param j The nlohmann/json object to populate
    /// @param meas The measurement to serialize
    static void to_json(json& j, const MeasT& meas)
    {
        // Generate JSON string using pkr_units SDK
        auto json_str = PKR_UNITS_NAMESPACE::json::serialize_measurement_to_json_string(meas);

        if (json_str.empty())
        {
            j = json::object();
            return;
        }

        // Parse it into nlohmann/json object (using iterators avoids string copy)
        j = json::parse(json_str.begin(), json_str.end());
    }

    /// Deserialize an RSS measurement from nlohmann/json
    ///
    /// Extracts the measurement from a JSON object and validates the dimension.
    /// Throws std::runtime_error if deserialization fails.
    ///
    /// @param j The nlohmann/json object to deserialize
    /// @param meas The measurement to populate
    /// @throw std::runtime_error if the JSON is invalid or dimension mismatches
    static void from_json(const json& j, MeasT& meas)
    {
        // Serialize nlohmann/json back to string, then parse with pkr_units
        auto json_str = j.dump();

        auto result = PKR_UNITS_NAMESPACE::json::deserialize_measurement_from_json_string<MeasT>(json_str);

        if (!result)
        {
            throw std::runtime_error("Failed to deserialize RSS measurement from JSON: " + json_str);
        }

        meas = *result;
    }
};

} // namespace nlohmann
#endif // NLOHMANN_JSON_HPP