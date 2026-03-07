#include <gtest/gtest.h>
#include <pkr_units/si_units.h>
#include <pkr_units/json/json.h>
#include <string>

using namespace pkr::units;

// ============================================================================
// JSON Serialization Tests
// ============================================================================

class JsonSerializationTest : public ::testing::Test
{
};

TEST_F(JsonSerializationTest, serialize_meter_double)
{
    meter_t<double> m{5.0};
    auto json_str = json::serialize_unit_to_json_string(m);

    EXPECT_FALSE(json_str.empty());
    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":5,\"unit\":\"m\"}");
}

TEST_F(JsonSerializationTest, serialize_kilometer_double)
{
    kilometer_t<double> km{10.5};
    auto json_str = json::serialize_unit_to_json_string(km);

    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":10.5,\"unit\":\"km\"}");
}

TEST_F(JsonSerializationTest, serialize_kilogram_double)
{
    kilogram_t<double> kg{50.25};
    auto json_str = json::serialize_unit_to_json_string(kg);

    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":50.25,\"unit\":\"kg\"}");
}

TEST_F(JsonSerializationTest, serialize_second_integer)
{
    second_t<int> s{42};
    auto json_str = json::serialize_unit_to_json_string(s);

    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":42,\"unit\":\"s\"}");
}

TEST_F(JsonSerializationTest, serialize_ampere_float)
{
    ampere_t<float> a{2.5f};
    auto json_str = json::serialize_unit_to_json_string(a);

    std::string result(json_str);
    // Float representation may have slight variations
    EXPECT_THAT(result, ::testing::MatchesRegex(R"(\{"value":2\.5[0-9]*,"unit":"A"\})"));
}

// ============================================================================
// JSON Deserialization Tests
// ============================================================================

class JsonDeserializationTest : public ::testing::Test
{
};

TEST_F(JsonDeserializationTest, deserialize_meter_double)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":5.0,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.0);
}

TEST_F(JsonDeserializationTest, deserialize_kilometer_double)
{
    auto result = json::deserialize_unit_from_json_string<kilometer_t<double>>(R"({"value":10.5,"unit":"km"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 10.5);
}

TEST_F(JsonDeserializationTest, deserialize_kilogram_double)
{
    auto result = json::deserialize_unit_from_json_string<kilogram_t<double>>(R"({"value":50.25,"unit":"kg"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 50.25);
}

TEST_F(JsonDeserializationTest, deserialize_second_integer)
{
    auto result = json::deserialize_unit_from_json_string<second_t<int>>(R"({"value":42,"unit":"s"})");

    ASSERT_TRUE(result);
    EXPECT_EQ(result->value(), 42);
}

TEST_F(JsonDeserializationTest, deserialize_ampere_float)
{
    auto result = json::deserialize_unit_from_json_string<ampere_t<float>>(R"({"value":2.5,"unit":"A"})");

    ASSERT_TRUE(result);
    EXPECT_FLOAT_EQ(result->value(), 2.5f);
}

// ============================================================================
// JSON Round-Trip Tests
// ============================================================================

class JsonRoundTripTest : public ::testing::Test
{
};

TEST_F(JsonRoundTripTest, meter_round_trip)
{
    meter_t<double> original{7.5};

    // Serialize
    auto json_str = json::serialize_unit_to_json_string(original);
    EXPECT_FALSE(json_str.empty());

    // Deserialize
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(json_str);

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), original.value());
}

TEST_F(JsonRoundTripTest, kilometer_round_trip)
{
    kilometer_t<double> original{123.456};

    auto json_str = json::serialize_unit_to_json_string(original);
    auto result = json::deserialize_unit_from_json_string<kilometer_t<double>>(json_str);

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), original.value());
}

TEST_F(JsonRoundTripTest, kilogram_round_trip)
{
    kilogram_t<double> original{99.9};

    auto json_str = json::serialize_unit_to_json_string(original);
    auto result = json::deserialize_unit_from_json_string<kilogram_t<double>>(json_str);

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), original.value());
}

// ============================================================================
// JSON Deserialization Error Tests
// ============================================================================

class JsonDeserializationErrorTest : public ::testing::Test
{
};

TEST_F(JsonDeserializationErrorTest, missing_value_field)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"unit":"m"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(JsonDeserializationErrorTest, missing_unit_field)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":5.0})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

TEST_F(JsonDeserializationErrorTest, invalid_numeric_value)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":abc,"unit":"m"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(JsonDeserializationErrorTest, dimension_mismatch)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":5.0,"unit":"kg"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

TEST_F(JsonDeserializationErrorTest, unknown_unit_symbol)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":5.0,"unit":"unknown"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

// ============================================================================
// JSON Measurement Serialization Tests
// ============================================================================

class JsonMeasurementSerializationTest : public ::testing::Test
{
};

TEST_F(JsonMeasurementSerializationTest, serialize_measurement_lin_meter_double)
{
    measurement_lin_t<meter_t<double>> meas{meter_t<double>{5.0}, 0.1};
    auto json_str = json::serialize_measurement_to_json_string(meas);

    EXPECT_FALSE(json_str.empty());
    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":5,\"uncertainty\":0.1,\"unit\":\"m\"}");
}

TEST_F(JsonMeasurementSerializationTest, serialize_measurement_lin_kilometer_double)
{
    measurement_lin_t<kilometer_t<double>> meas{kilometer_t<double>{10.5}, 0.25};
    auto json_str = json::serialize_measurement_to_json_string(meas);

    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":10.5,\"uncertainty\":0.25,\"unit\":\"km\"}");
}

TEST_F(JsonMeasurementSerializationTest, serialize_measurement_lin_kilogram_double)
{
    measurement_lin_t<kilogram_t<double>> meas{kilogram_t<double>{50.0}, 0.05};
    auto json_str = json::serialize_measurement_to_json_string(meas);

    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":50,\"uncertainty\":0.05,\"unit\":\"kg\"}");
}

// ============================================================================
// JSON Measurement Deserialization Tests
// ============================================================================

class JsonMeasurementDeserializationTest : public ::testing::Test
{
};

TEST_F(JsonMeasurementDeserializationTest, deserialize_measurement_lin_meter_double)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"value":5.0,"uncertainty":0.1,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.0);
    EXPECT_DOUBLE_EQ(result->uncertainty(), 0.1);
}

TEST_F(JsonMeasurementDeserializationTest, deserialize_measurement_lin_kilometer_double)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<kilometer_t<double>>>(R"({"value":10.5,"uncertainty":0.25,"unit":"km"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 10.5);
    EXPECT_DOUBLE_EQ(result->uncertainty(), 0.25);
}

TEST_F(JsonMeasurementDeserializationTest, deserialize_measurement_lin_kilogram_double)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<kilogram_t<double>>>(R"({"value":50.0,"uncertainty":0.05,"unit":"kg"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 50.0);
    EXPECT_DOUBLE_EQ(result->uncertainty(), 0.05);
}

// ============================================================================
// JSON Measurement Round-Trip Tests
// ============================================================================

class JsonMeasurementRoundTripTest : public ::testing::Test
{
};

TEST_F(JsonMeasurementRoundTripTest, measurement_meter_round_trip)
{
    measurement_lin_t<meter_t<double>> original{meter_t<double>{7.5}, 0.15};

    auto json_str = json::serialize_measurement_to_json_string(original);
    EXPECT_FALSE(json_str.empty());

    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(json_str);

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), original.value());
    EXPECT_DOUBLE_EQ(result->uncertainty(), original.uncertainty());
}

TEST_F(JsonMeasurementRoundTripTest, measurement_kilometer_round_trip)
{
    measurement_lin_t<kilometer_t<double>> original{kilometer_t<double>{123.456}, 0.789};

    auto json_str = json::serialize_measurement_to_json_string(original);
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<kilometer_t<double>>>(json_str);

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), original.value());
    EXPECT_DOUBLE_EQ(result->uncertainty(), original.uncertainty());
}

TEST_F(JsonMeasurementRoundTripTest, measurement_kilogram_round_trip)
{
    measurement_lin_t<kilogram_t<double>> original{kilogram_t<double>{99.9}, 0.01};

    auto json_str = json::serialize_measurement_to_json_string(original);
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<kilogram_t<double>>>(json_str);

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), original.value());
    EXPECT_DOUBLE_EQ(result->uncertainty(), original.uncertainty());
}

// ============================================================================
// JSON Measurement Deserialization Error Tests
// ============================================================================

class JsonMeasurementDeserializationErrorTest : public ::testing::Test
{
};

TEST_F(JsonMeasurementDeserializationErrorTest, missing_value_field)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"uncertainty":0.1,"unit":"m"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(JsonMeasurementDeserializationErrorTest, missing_uncertainty_field)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"value":5.0,"unit":"m"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(JsonMeasurementDeserializationErrorTest, missing_unit_field)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"value":5.0,"uncertainty":0.1})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

TEST_F(JsonMeasurementDeserializationErrorTest, invalid_numeric_value)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"value":abc,"uncertainty":0.1,"unit":"m"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(JsonMeasurementDeserializationErrorTest, invalid_uncertainty_value)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"value":5.0,"uncertainty":xyz,"unit":"m"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(JsonMeasurementDeserializationErrorTest, measurement_dimension_mismatch)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"value":5.0,"uncertainty":0.1,"unit":"kg"})");

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

// ============================================================================
// Unit Conversion Tests (Deserialization with different target units)
// ============================================================================

class JsonUnitConversionTest : public ::testing::Test
{
};

TEST_F(JsonUnitConversionTest, deserialize_meters_as_kilometers)
{
    // Parse 1000 m as km -> should convert to 1.0 km
    auto result = json::deserialize_unit_from_json_string<kilometer_t<double>>(R"({"value":1000.0,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 1.0);
}

TEST_F(JsonUnitConversionTest, deserialize_kilometers_as_meters)
{
    // Parse 1 km as m -> should convert to 1000 m
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":1.0,"unit":"km"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 1000.0);
}

TEST_F(JsonUnitConversionTest, deserialize_millimeters_as_meters)
{
    // Parse 1000 mm as m -> should convert to 1.0 m
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":1000.0,"unit":"mm"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 1.0);
}

// ============================================================================
// Multiple Serializations (buffer state tests)
// ============================================================================

class JsonBufferStateTest : public ::testing::Test
{
};

TEST_F(JsonBufferStateTest, multiple_serializations_independent)
{
    meter_t<double> m1{5.0};
    meter_t<double> m2{10.0};
    kilogram_t<double> kg{50.0};

    auto json1 = json::serialize_unit_to_json_string(m1);
    auto json2 = json::serialize_unit_to_json_string(m2);
    auto json3 = json::serialize_unit_to_json_string(kg);

    // Each subsequent serialization should overwrite the buffer
    // but we immediately check the latest one
    EXPECT_EQ(std::string(json3), "{\"value\":50,\"unit\":\"kg\"}");
}

TEST_F(JsonBufferStateTest, serialize_then_deserialize_not_overlapping)
{
    meter_t<double> original{7.5};

    // Serialize
    auto json_str = json::serialize_unit_to_json_string(original);
    std::string json_copy(json_str); // Make a copy to avoid buffer overwrite

    // Deserialize
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(json_copy);

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), original.value());
}

// ============================================================================
// Zero and Negative Values
// ============================================================================

class JsonZeroAndNegativeTest : public ::testing::Test
{
};

TEST_F(JsonZeroAndNegativeTest, serialize_zero_meter)
{
    meter_t<double> m{0.0};
    auto json_str = json::serialize_unit_to_json_string(m);

    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":0,\"unit\":\"m\"}");
}

TEST_F(JsonZeroAndNegativeTest, serialize_negative_meter)
{
    meter_t<double> m{-5.5};
    auto json_str = json::serialize_unit_to_json_string(m);

    std::string result(json_str);
    EXPECT_EQ(result, "{\"value\":-5.5,\"unit\":\"m\"}");
}

TEST_F(JsonZeroAndNegativeTest, deserialize_zero_meter)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":0.0,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 0.0);
}

TEST_F(JsonZeroAndNegativeTest, deserialize_negative_meter)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":-5.5,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), -5.5);
}

TEST_F(JsonZeroAndNegativeTest, deserialize_negative_measurement)
{
    auto result = json::deserialize_measurement_from_json_string<measurement_lin_t<meter_t<double>>>(R"({"value":-5.5,"uncertainty":0.1,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), -5.5);
    EXPECT_DOUBLE_EQ(result->uncertainty(), 0.1);
}

// ============================================================================
// Scientific Notation Tests
// ============================================================================

class JsonScientificNotationTest : public ::testing::Test
{
};

TEST_F(JsonScientificNotationTest, deserialize_scientific_notation_positive)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":1.23e-4,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 1.23e-4);
}

TEST_F(JsonScientificNotationTest, deserialize_scientific_notation_negative_exponent)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":5.67e-2,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.67e-2);
}

TEST_F(JsonScientificNotationTest, deserialize_scientific_notation_positive_exponent)
{
    auto result = json::deserialize_unit_from_json_string<meter_t<double>>(R"({"value":1.5e+3,"unit":"m"})");

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 1.5e3);
}
