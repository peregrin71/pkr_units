#include <gtest/gtest.h>
#include <format>
#include <sstream>
#include <si_units/formatting/si_units_formatters.h>
#include <si_units/standard/length.h>

using namespace ::testing;

class SiLengthFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiLengthFormattingTest, meter_ascii_formatting)
{
    si::meter m{5.0};
    std::string result = std::format("{}", m);
    ASSERT_EQ(result, "5 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_with_precision)
{
    si::meter m{5.123456};
    std::string result = std::format("{:.2f}", m);
    ASSERT_EQ(result, "5.12 m");
}

TEST_F(SiLengthFormattingTest, kilometer_ascii_formatting)
{
    si::kilometer km{2.5};
    std::string result = std::format("{}", km);
    ASSERT_EQ(result, "2.5 km");
}

TEST_F(SiLengthFormattingTest, millimeter_ascii_formatting)
{
    si::millimeter mm{1500.0};
    std::string result = std::format("{}", mm);
    ASSERT_EQ(result, "1500 mm");
}

TEST_F(SiLengthFormattingTest, micrometer_ascii_formatting)
{
    si::micrometer um{0.5};
    std::string result = std::format("{}", um);
    ASSERT_EQ(result, "0.5 um");  // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiLengthFormattingTest, nanometer_ascii_formatting)
{
    si::nanometer nm{100.0};
    std::string result = std::format("{}", nm);
    ASSERT_EQ(result, "100 nm");
}

TEST_F(SiLengthFormattingTest, decimeter_ascii_formatting)
{
    si::decimeter dm{3.5};
    std::string result = std::format("{}", dm);
    ASSERT_EQ(result, "3.5 dm");
}

TEST_F(SiLengthFormattingTest, centimeter_ascii_formatting)
{
    si::centimeter cm{42.0};
    std::string result = std::format("{}", cm);
    ASSERT_EQ(result, "42 cm");
}

TEST_F(SiLengthFormattingTest, decameter_ascii_formatting)
{
    si::decameter dam{1.5};
    std::string result = std::format("{}", dam);
    ASSERT_EQ(result, "1.5 dam");
}

TEST_F(SiLengthFormattingTest, hectometer_ascii_formatting)
{
    si::hectometer hm{2.0};
    std::string result = std::format("{}", hm);
    ASSERT_EQ(result, "2 hm");
}

TEST_F(SiLengthFormattingTest, megameter_ascii_formatting)
{
    si::megameter Mm{0.001};
    std::string result = std::format("{}", Mm);
    ASSERT_EQ(result, "0.001 Mm");
}

// ============================================================================
// ASCII Formatting with Different Precisions
// ============================================================================

TEST_F(SiLengthFormattingTest, meter_ascii_high_precision)
{
    si::meter m{3.141592653589793};
    std::string result = std::format("{:.10f}", m);
    ASSERT_TRUE(result.find("3.14159265") == 0);  // First 10 decimal places
    ASSERT_TRUE(result.ends_with(" m"));
}

TEST_F(SiLengthFormattingTest, meter_ascii_scientific_notation)
{
    si::meter m{1234567.0};
    std::string result = std::format("{:e}", m);
    ASSERT_TRUE(result.find("1.234567e+06") == 0);
    ASSERT_TRUE(result.ends_with(" m"));
}

TEST_F(SiLengthFormattingTest, meter_ascii_zero_value)
{
    si::meter m{0.0};
    std::string result = std::format("{}", m);
    ASSERT_EQ(result, "0 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_negative_value)
{
    si::meter m{-5.5};
    std::string result = std::format("{}", m);
    ASSERT_EQ(result, "-5.5 m");
}

// ============================================================================
// UTF-8 Formatting Tests - char8_t
// ============================================================================

TEST_F(SiLengthFormattingTest, meter_utf8_formatting)
{
    si::meter m{5.0};
    std::u8string result = std::format(u8"{}", m);
    ASSERT_EQ(result, u8"5 m");
}

TEST_F(SiLengthFormattingTest, micrometer_utf8_formatting)
{
    si::micrometer um{0.5};
    std::u8string result = std::format(u8"{}", um);
    // UTF-8 uses Unicode micro symbol
    ASSERT_TRUE(result.ends_with(u8"m"));
    ASSERT_TRUE(result.starts_with(u8"0.5 "));
}

TEST_F(SiLengthFormattingTest, kilometer_utf8_formatting)
{
    si::kilometer km{1.5};
    std::u8string result = std::format(u8"{}", km);
    ASSERT_EQ(result, u8"1.5 km");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t
// ============================================================================

TEST_F(SiLengthFormattingTest, meter_wide_formatting)
{
    si::meter m{5.0};
    std::wstring result = std::format(L"{}", m);
    ASSERT_EQ(result, L"5 m");
}

TEST_F(SiLengthFormattingTest, micrometer_wide_formatting)
{
    si::micrometer um{0.5};
    std::wstring result = std::format(L"{}", um);
    // Wide uses Unicode micro symbol
    ASSERT_TRUE(result.ends_with(L"m"));
    ASSERT_TRUE(result.starts_with(L"0.5 "));
}

TEST_F(SiLengthFormattingTest, kilometer_wide_formatting)
{
    si::kilometer km{2.75};
    std::wstring result = std::format(L"{}", km);
    ASSERT_EQ(result, L"2.75 km");
}

// ============================================================================
// Comprehensive Unit Coverage
// ============================================================================

TEST_F(SiLengthFormattingTest, all_metric_prefixes_ascii)
{
    // Test all implemented metric prefixes
    std::string test_cases[] = {
        std::format("{}", si::attometer{1.0}),      // "1 am"
        std::format("{}", si::femtometer{1.0}),     // "1 fm"
        std::format("{}", si::picometer{1.0}),      // "1 pm"
        std::format("{}", si::nanometer{1.0}),      // "1 nm"
        std::format("{}", si::micrometer{1.0}),     // "1 um"
        std::format("{}", si::millimeter{1.0}),     // "1 mm"
        std::format("{}", si::centimeter{1.0}),     // "1 cm"
        std::format("{}", si::decimeter{1.0}),      // "1 dm"
        std::format("{}", si::meter{1.0}),          // "1 m"
        std::format("{}", si::decameter{1.0}),      // "1 dam"
        std::format("{}", si::hectometer{1.0}),     // "1 hm"
        std::format("{}", si::kilometer{1.0}),      // "1 km"
        std::format("{}", si::megameter{1.0}),      // "1 Mm"
        std::format("{}", si::gigameter{1.0}),      // "1 Gm"
    };

    // Verify all tests end with " m" (space + unit symbol)
    for (const auto& result : test_cases)
    {
        ASSERT_TRUE(result.ends_with(" m")) << "Failed for: " << result;
        ASSERT_TRUE(result.starts_with("1 ")) << "Failed for: " << result;
    }
}

TEST_F(SiLengthFormattingTest, output_stream_compatibility)
{
    si::meter m{3.5};
    std::ostringstream oss;
    oss << std::format("{}", m);
    ASSERT_EQ(oss.str(), "3.5 m");
}

TEST_F(SiLengthFormattingTest, format_in_string_context)
{
    si::kilometer distance{42.195};
    std::string message = std::format("The marathon distance is approximately {}", distance);
    ASSERT_EQ(message, "The marathon distance is approximately 42.195 km");
}

TEST_F(SiLengthFormattingTest, multiple_values_formatted)
{
    si::meter width{3.2};
    si::meter depth{2.5};
    si::meter height{1.75};
    
    std::string result = std::format(
        "Dimensions: {}W x {}D x {}H",
        width, depth, height
    );
    
    ASSERT_EQ(result, "Dimensions: 3.2 mW x 2.5 mD x 1.75 mH");
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiLengthFormattingTest, very_small_value)
{
    si::meter m{1e-15};
    std::string result = std::format("{:e}", m);
    ASSERT_TRUE(result.find("1.000000e-15") == 0);
    ASSERT_TRUE(result.ends_with(" m"));
}

TEST_F(SiLengthFormattingTest, very_large_value)
{
    si::kilometer km{1e15};
    std::string result = std::format("{:e}", km);
    ASSERT_TRUE(result.find("1.000000e+15") == 0);
    ASSERT_TRUE(result.ends_with(" km"));
}

TEST_F(SiLengthFormattingTest, default_and_explicit_precision)
{
    si::meter m{1.0 / 3.0};
    std::string result_default = std::format("{}", m);
    std::string result_explicit = std::format("{:.6f}", m);
    
    ASSERT_TRUE(result_default.ends_with(" m"));
    ASSERT_TRUE(result_explicit.ends_with(" m"));
    ASSERT_TRUE(result_explicit.find("0.333333") != std::string::npos);
}


