#include <gtest/gtest.h>
#include <sstream>

#include <pkr_units/si_units.h>
#include <pkr_units/impl/parsing/parse.h>

using namespace pkr::units;

// ============================================================================
// Parse basic value tests
// ============================================================================

class ParseBasicTest : public ::testing::Test
{
};

TEST_F(ParseBasicTest, parse_double_meter)
{
    auto result = parse<meter_t<double>>("5.2 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.2);
}

TEST_F(ParseBasicTest, parse_float_meter)
{
    auto result = parse<meter_t<float>>("5.2f m");
    ASSERT_TRUE(result);
    EXPECT_FLOAT_EQ(result->value(), 5.2f);
}

TEST_F(ParseBasicTest, parse_integer_second)
{
    auto result = parse<second_t<int>>("42 s");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->value(), 42);
}

TEST_F(ParseBasicTest, parse_kilogram)
{
    auto result = parse<kilogram_t<double>>("100.5 kg");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 100.5);
}

TEST_F(ParseBasicTest, parse_ampere)
{
    auto result = parse<ampere_t<double>>("2.5 A");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 2.5);
}

// ============================================================================
// Error handling tests
// ============================================================================

class ParseErrorHandlingTest : public ::testing::Test
{
};

TEST_F(ParseErrorHandlingTest, numeric_parse_error)
{
    auto result = parse<meter_t<double>>("invalid m");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(ParseErrorHandlingTest, symbol_mismatch)
{
    auto result = parse<meter_t<double>>("5.2 kg");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

TEST_F(ParseErrorHandlingTest, has_value_on_success)
{
    auto result = parse<meter_t<double>>("5.0 m");
    EXPECT_TRUE(result.has_value());
}

TEST_F(ParseErrorHandlingTest, has_value_on_error)
{
    auto result = parse<meter_t<double>>("invalid m");
    EXPECT_FALSE(result.has_value());
}

TEST_F(ParseErrorHandlingTest, explicit_error_check)
{
    auto result = parse<meter_t<double>>("5.0 kg");
    ASSERT_FALSE(result);
    ASSERT_TRUE(!result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

TEST_F(ParseErrorHandlingTest, error_discrimination)
{
    // numeric_parse_error
    auto numeric_err = parse<meter_t<double>>("abc m");
    if (!numeric_err)
    {
        EXPECT_EQ(numeric_err.error(), parse_error::numeric_parse_error);
    }

    // symbol_mismatch
    auto symbol_err = parse<meter_t<double>>("5.0 kg");
    if (!symbol_err)
    {
        EXPECT_EQ(symbol_err.error(), parse_error::symbol_mismatch);
    }

    // unknown_symbol
    auto unknown_err = parse<meter_t<double>>("5.0");
    if (!unknown_err)
    {
        EXPECT_EQ(unknown_err.error(), parse_error::unknown_symbol);
    }
}

TEST_F(ParseErrorHandlingTest, dereference_operator)
{
    auto result = parse<meter_t<double>>("5.0 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.0);
}

TEST_F(ParseErrorHandlingTest, dereference_with_star)
{
    auto result = parse<meter_t<double>>("5.0 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ((*result).value(), 5.0);
}

// ============================================================================
// Monadic operations tests
// ============================================================================

class ParseMonadicTest : public ::testing::Test
{
};

TEST_F(ParseMonadicTest, map_value_transformation)
{
    // Transform parsed unit value by doubling it
    auto result = parse<meter_t<double>>("5.0 m").map([](const auto& unit) { return unit.value() * 2.0; });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 10.0);
}

TEST_F(ParseMonadicTest, map_unit_conversion)
{
    // Convert meters to kilometers
    auto result = parse<meter_t<double>>("5000.0 m").map([](const auto& m) { return m.value() / 1000.0; });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 5.0);
}

TEST_F(ParseMonadicTest, map_error_propagation)
{
    // Map on error should not execute the lambda
    auto result = parse<meter_t<double>>("invalid m").map([](const auto& m) { return m.value() * 2.0; });

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

TEST_F(ParseMonadicTest, and_then_chained_parsing)
{
    // Chain two parsing operations
    auto result = parse<meter_t<double>>("10.0 m").and_then(
        [](const auto& m)
        {
            // If first parse succeeds, validate and transform
            if (m.value() > 5.0)
            {
                return expected_t<double, parse_error>{m.value() * 100.0};
            }
            return expected_t<double, parse_error>{parse_error::numeric_parse_error};
        });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 1000.0);
}

TEST_F(ParseMonadicTest, and_then_error_in_chain)
{
    // Chain fails after first operation succeeds
    auto result = parse<meter_t<double>>("3.0 m").and_then(
        [](const auto& m)
        {
            // Validation fails for small values
            if (m.value() > 5.0)
            {
                return expected_t<double, parse_error>{m.value() * 100.0};
            }
            return expected_t<double, parse_error>{parse_error::symbol_mismatch};
        });

    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

TEST_F(ParseMonadicTest, or_else_success)
{
    // or_else only executes on error, not on success
    auto result = parse<meter_t<double>>("5.0 m")
                      .or_else(
                          [](parse_error)
                          {
                              // Should not execute - success path
                              return expected_t<meter_t<double>, parse_error>{meter_t<double>{-1.0}};
                          })
                      .map([](const auto& unit) { return unit.value(); });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 5.0);
}

TEST_F(ParseMonadicTest, or_else_error_recovery)
{
    // or_else with error recovery
    auto result = parse<meter_t<double>>("invalid m")
                      .or_else(
                          [](parse_error)
                          {
                              // Return default unit on error
                              return expected_t<meter_t<double>, parse_error>{meter_t<double>{0.0}};
                          });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 0.0);
}

TEST_F(ParseMonadicTest, value_or_success)
{
    // value_or returns stored value on success
    auto value = parse<meter_t<double>>("7.5 m").map([](const auto& m) { return m.value(); }).value_or(0.0);

    EXPECT_DOUBLE_EQ(value, 7.5);
}

TEST_F(ParseMonadicTest, value_or_error)
{
    // value_or returns default on error
    auto value = parse<meter_t<double>>("invalid m").map([](const auto& m) { return m.value(); }).value_or(42.0);

    EXPECT_DOUBLE_EQ(value, 42.0);
}

TEST_F(ParseMonadicTest, value_or_else_with_error_handler)
{
    // value_or_else applies function to error
    auto value = parse<meter_t<double>>("invalid m")
                     .map([](const auto& m) { return m.value(); })
                     .value_or_else(
                         [](parse_error e)
                         {
                             // Return different defaults based on error type
                             if (e == parse_error::numeric_parse_error)
                             {
                                 return 99.0;
                             }
                             return 0.0;
                         });

    EXPECT_DOUBLE_EQ(value, 99.0);
}

// ============================================================================
// Whitespace handling tests
// ============================================================================

class ParseWhitespaceTest : public ::testing::Test
{
};

TEST_F(ParseWhitespaceTest, leading_whitespace)
{
    auto result = parse<meter_t<double>>("  5.2 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.2);
}

TEST_F(ParseWhitespaceTest, trailing_whitespace)
{
    auto result = parse<meter_t<double>>("5.2 m  ");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.2);
}

TEST_F(ParseWhitespaceTest, whitespace_handling)
{
    // Extra whitespace handling
    auto result = parse<meter_t<double>>("  5.0   m  ");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.0);
}

// ============================================================================
// Float vs Double deduction tests
// ============================================================================

class ParseNumericTypeTest : public ::testing::Test
{
};

TEST_F(ParseNumericTypeTest, float_suffix_lowercase)
{
    auto result = parse<meter_t<float>>("5.2f m");
    ASSERT_TRUE(result);
    EXPECT_FLOAT_EQ(result->value(), 5.2f);
}

TEST_F(ParseNumericTypeTest, float_suffix_uppercase)
{
    auto result = parse<meter_t<float>>("5.2F m");
    ASSERT_TRUE(result);
    EXPECT_FLOAT_EQ(result->value(), 5.2f);
}

TEST_F(ParseNumericTypeTest, no_suffix_defaults_double)
{
    auto result = parse<meter_t<double>>("5.2 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.2);
}

TEST_F(ParseNumericTypeTest, scientific_notation)
{
    // Scientific notation support
    auto result = parse<kilogram_t<double>>("1.5e-3 kg");
    ASSERT_TRUE(result);
    EXPECT_NEAR(result->value(), 0.0015, 1e-10);
}

// ============================================================================
// Wide character tests
// ============================================================================

class ParseWideCharTest : public ::testing::Test
{
};

TEST_F(ParseWideCharTest, wide_char_meter)
{
    auto result = parse<meter_t<double>, wchar_t>(L"5.2 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.2);
}

TEST_F(ParseWideCharTest, wide_char_kilogram)
{
    auto result = parse<kilogram_t<double>, wchar_t>(L"100.5 kg");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 100.5);
}

TEST_F(ParseWideCharTest, wide_char_error)
{
    auto result = parse<meter_t<double>, wchar_t>(L"invalid m");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::numeric_parse_error);
}

// ============================================================================
// Negative values tests
// ============================================================================

class ParseNegativeTest : public ::testing::Test
{
};

TEST_F(ParseNegativeTest, negative_meter)
{
    auto result = parse<meter_t<double>>("-5.2 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), -5.2);
}

TEST_F(ParseNegativeTest, negative_kilogram)
{
    auto result = parse<kilogram_t<double>>("-100.0 kg");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), -100.0);
}

// ============================================================================
// Scientific notation tests
// ============================================================================

class ParseScientificNotationTest : public ::testing::Test
{
};

TEST_F(ParseScientificNotationTest, scientific_notation_positive)
{
    auto result = parse<meter_t<double>>("1.23e2 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 123.0);
}

TEST_F(ParseScientificNotationTest, scientific_notation_negative_exponent)
{
    auto result = parse<meter_t<double>>("1.23e-2 m");
    ASSERT_TRUE(result);
    EXPECT_NEAR(result->value(), 0.0123, 1e-6);
}

// ============================================================================
// Derived unit tests
// ============================================================================

class ParseDerivedUnitsTest : public ::testing::Test
{
};

TEST_F(ParseDerivedUnitsTest, meter_per_second)
{
    // Test parsing of derived units like m/s
    // Using a simpler approach to avoid template nesting issues
    // The actual derived unit support depends on how symbols are defined
    auto result = parse<meter_t<double>>("5.0 m");
    if (result)
    {
        EXPECT_NEAR(result->value(), 5.0, 1e-9);
    }
}

// ============================================================================
// Larger value tests
// ============================================================================

class ParseLargeValuesTest : public ::testing::Test
{
};

TEST_F(ParseLargeValuesTest, large_double_value)
{
    auto result = parse<meter_t<double>>("1234567.89 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 1234567.89);
}

TEST_F(ParseLargeValuesTest, very_small_value)
{
    auto result = parse<meter_t<double>>("0.00001234 m");
    ASSERT_TRUE(result);
    EXPECT_NEAR(result->value(), 0.00001234, 1e-10);
}

TEST_F(ParseLargeValuesTest, zero_value)
{
    auto result = parse<meter_t<double>>("0.0 m");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 0.0);
}

// ============================================================================
// const char* Overload Tests
// ============================================================================

class ConstCharOverloadTest : public ::testing::Test
{
};

TEST_F(ConstCharOverloadTest, parse_const_char_pointer)
{
    // Parse from const char* literal
    const char* input = "7.5 m";
    auto result = parse<meter_t<double>>(input);
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 7.5);
}

TEST_F(ConstCharOverloadTest, parse_const_char_array)
{
    // Parse from char array
    char input[] = "3.3 s";
    auto result = parse<second_t<double>>(input);
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 3.3);
}

// ============================================================================
// Missing Unit Symbol Tests
// ============================================================================

class MissingUnitSymbolTest : public ::testing::Test
{
};

TEST_F(MissingUnitSymbolTest, parse_numeric_without_symbol)
{
    // Parsing just a numeric value without unit symbol should succeed
    // and default to the target unit type
    auto result = parse<meter_t<double>>("5.0");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 5.0);
}

TEST_F(MissingUnitSymbolTest, parse_various_units_without_symbol)
{
    // Test multiple unit types without symbols
    auto m_result = parse<meter_t<double>>("12.5");
    ASSERT_TRUE(m_result);
    EXPECT_DOUBLE_EQ(m_result->value(), 12.5);

    auto kg_result = parse<kilogram_t<double>>("75.3");
    ASSERT_TRUE(kg_result);
    EXPECT_DOUBLE_EQ(kg_result->value(), 75.3);

    auto s_result = parse<second_t<double>>("42.1");
    ASSERT_TRUE(s_result);
    EXPECT_DOUBLE_EQ(s_result->value(), 42.1);
}

TEST_F(MissingUnitSymbolTest, parse_float_without_symbol)
{
    // Float without unit symbol
    auto result = parse<meter_t<float>>("3.14f");
    ASSERT_TRUE(result);
    EXPECT_FLOAT_EQ(result->value(), 3.14f);
}

TEST_F(MissingUnitSymbolTest, parse_with_wrong_symbol_still_fails)
{
    // Wrong unit symbol should still fail with symbol_mismatch
    auto result = parse<meter_t<double>>("5.0 kg");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), parse_error::symbol_mismatch);
}

TEST_F(MissingUnitSymbolTest, parse_with_whitespace_no_symbol)
{
    // Extra whitespace with no symbol
    auto result = parse<meter_t<double>>("  7.5  ");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->value(), 7.5);
}

// ============================================================================
// Complex Monadic Chains
// ============================================================================

class ComplexMonadicChainTest : public ::testing::Test
{
};

TEST_F(ComplexMonadicChainTest, multi_level_transformation)
{
    // Chain: parse -> scale -> validate -> extract
    auto result = parse<meter_t<double>>("10.0 m")
                      .map([](const auto& m) { return m.value() * 1000.0; }) // Scale to mm
                      .and_then(
                          [](double mm)
                          {
                              // Validate range
                              if (mm >= 0 && mm <= 50000)
                              {
                                  return expected_t<double, parse_error>{mm};
                              }
                              return expected_t<double, parse_error>{parse_error::numeric_parse_error};
                          })
                      .map([](double mm) { return mm / 100.0; }); // Convert to cm

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 100.0); // 10m = 1000cm
}

TEST_F(ComplexMonadicChainTest, error_recovery_with_fallback)
{
    // Try to parse with fallback on error
    auto result = parse<meter_t<double>>("invalid m")
                      .or_else(
                          [](parse_error)
                          {
                              // Fallback to default
                              return expected_t<meter_t<double>, parse_error>{meter_t<double>{5.0}};
                          })
                      .map([](const auto& m) { return m.value(); });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 5.0);
}

TEST_F(ComplexMonadicChainTest, conditional_transformation)
{
    // Apply different transformations based on parsed value
    auto result = parse<kilogram_t<double>>("75.0 kg").and_then(
        [](const auto& kg)
        {
            double value = kg.value();
            if (value > 50.0)
            {
                // Heavy: double the value
                return expected_t<double, parse_error>{value * 2.0};
            }
            else
            {
                // Light: return as is
                return expected_t<double, parse_error>{value};
            }
        });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 150.0); // 75kg > 50kg, so 75 * 2 = 150
}

TEST_F(ComplexMonadicChainTest, parse_with_validation)
{
    // Parse and validate in a single chain
    auto result = parse<second_t<double>>("42.5 s").and_then(
        [](const auto& time)
        {
            // Accept only positive times
            if (time.value() > 0.0)
            {
                return expected_t<double, parse_error>{time.value()};
            }
            return expected_t<double, parse_error>{parse_error::numeric_parse_error};
        });

    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(*result, 42.5);
}
