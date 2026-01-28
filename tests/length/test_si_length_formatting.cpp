#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/length.h>

using namespace ::testing;

class SiLengthFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiLengthFormattingTest, meter_ascii_formatting)
{
    pkr::units::meter_t m{5.0};
    std::string result = std::format("{}", m);
    ASSERT_EQ(result, "5 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_with_precision)
{
    pkr::units::meter_t m{5.123456};
    std::string result = std::format("{:.2f}", m);
    ASSERT_EQ(result, "5.12 m");
}

TEST_F(SiLengthFormattingTest, kilometer_ascii_formatting)
{
    pkr::units::kilometer_t km{2.5};
    std::string result = std::format("{}", km);
    ASSERT_EQ(result, "2.5 km");
}

TEST_F(SiLengthFormattingTest, millimeter_ascii_formatting)
{
    pkr::units::millimeter_t mm{1500.0};
    std::string result = std::format("{}", mm);
    ASSERT_EQ(result, "1500 mm");
}

TEST_F(SiLengthFormattingTest, micrometer_ascii_formatting)
{
    pkr::units::micrometer_t um{0.5};
    std::string result = std::format("{}", um);
    ASSERT_EQ(result, "0.5 um"); // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiLengthFormattingTest, nanometer_ascii_formatting)
{
    pkr::units::nanometer_t nm{100.0};
    std::string result = std::format("{}", nm);
    ASSERT_EQ(result, "100 nm");
}

TEST_F(SiLengthFormattingTest, decimeter_ascii_formatting)
{
    pkr::units::decimeter_t dm{3.5};
    std::string result = std::format("{}", dm);
    ASSERT_EQ(result, "3.5 dm");
}

TEST_F(SiLengthFormattingTest, centimeter_ascii_formatting)
{
    pkr::units::centimeter_t cm{42.0};
    std::string result = std::format("{}", cm);
    ASSERT_EQ(result, "42 cm");
}

TEST_F(SiLengthFormattingTest, decameter_ascii_formatting)
{
    pkr::units::decameter_t dam{1.5};
    std::string result = std::format("{}", dam);
    ASSERT_EQ(result, "1.5 dam");
}

TEST_F(SiLengthFormattingTest, hectometer_ascii_formatting)
{
    pkr::units::hectometer_t hm{2.0};
    std::string result = std::format("{}", hm);
    ASSERT_EQ(result, "2 hm");
}

TEST_F(SiLengthFormattingTest, megameter_ascii_formatting)
{
    pkr::units::megameter_t Mm{0.001};
    std::string result = std::format("{}", Mm);
    ASSERT_EQ(result, "0.001 Mm");
}

// ============================================================================
// ASCII Formatting with Different Precisions
// ============================================================================

TEST_F(SiLengthFormattingTest, meter_ascii_high_precision)
{
    pkr::units::meter_t m{3.141592653589793};
    std::string result = std::format("{:.10f}", m);
    ASSERT_EQ(result, "3.1415926536 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_scientific_notation)
{
    pkr::units::meter_t m{1234567.0};
    std::string result = std::format("{:e}", m);
    ASSERT_EQ(result, "1.234567e+06 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_zero_value)
{
    pkr::units::meter_t m{0.0};
    std::string result = std::format("{}", m);
    ASSERT_EQ(result, "0 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_negative_value)
{
    pkr::units::meter_t m{-5.5};
    std::string result = std::format("{}", m);
    ASSERT_EQ(result, "-5.5 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_width_and_precision)
{
    pkr::units::meter_t m{3.14159};
    std::string result = std::format("{:8.2f}", m);
    ASSERT_EQ(result, "    3.14 m");
}

TEST_F(SiLengthFormattingTest, meter_ascii_explicit_sign)
{
    pkr::units::meter_t m{5.0};
    std::string result = std::format("{:+.1f}", m);
    ASSERT_EQ(result, "+5.0 m");
}

// ============================================================================
// UTF-8 Formatting Tests - char8_t (disabled for C++20)
// ============================================================================

// TEST_F(SiLengthFormattingTest, meter_utf8_formatting)
// {
//     pkr::units::meter_t m{5.0};
//     std::u8string result = std::format(u8"{}", m);
//     ASSERT_EQ(result, u8"5 m");
// }

// TEST_F(SiLengthFormattingTest, micrometer_utf8_formatting)
// {
//     pkr::units::micrometer_t um{0.5};
//     std::u8string result = std::format(u8"{}", um);
//     std::u8string expected = std::u8string(u8"0.5 ") + std::u8string(pkr::units::micrometer_t::u8_symbol);
//     ASSERT_EQ(result, expected);
// }

// TEST_F(SiLengthFormattingTest, kilometer_utf8_formatting)
// {
//     pkr::units::kilometer_t km{1.5};
//     std::u8string result = std::format(u8"{}", km);
//     ASSERT_EQ(result, u8"1.5 km");
// }

// ============================================================================
// Wide Character Formatting Tests - wchar_t
// ============================================================================

TEST_F(SiLengthFormattingTest, meter_wide_formatting)
{
    pkr::units::meter_t m{5.0};
    std::wstring result = std::format(L"{}", m);
    ASSERT_EQ(result, L"5 m");
}

TEST_F(SiLengthFormattingTest, micrometer_wide_formatting)
{
    pkr::units::micrometer_t um{0.5};
    std::wstring result = std::format(L"{}", um);
    std::wstring expected = std::wstring(L"0.5 ") + std::wstring(pkr::units::micrometer_t::w_symbol);
    ASSERT_EQ(result, expected);
}

TEST_F(SiLengthFormattingTest, kilometer_wide_formatting)
{
    pkr::units::kilometer_t km{2.75};
    std::wstring result = std::format(L"{}", km);
    ASSERT_EQ(result, L"2.75 km");
}

// ============================================================================
// Comprehensive Unit Coverage
// ============================================================================

TEST_F(SiLengthFormattingTest, all_metric_prefixes_ascii)
{
    // Test all implemented metric prefixes
    struct TestCase
    {
        std::string expected;
        std::string result;
    };

    TestCase test_cases[] = {
        {"1 am", std::format("{}", pkr::units::attometer_t{1.0})},
        {"1 fm", std::format("{}", pkr::units::femtometer_t{1.0})},
        {"1 pm", std::format("{}", pkr::units::picometer_t{1.0})},
        {"1 nm", std::format("{}", pkr::units::nanometer_t{1.0})},
        {"1 um", std::format("{}", pkr::units::micrometer_t{1.0})},
        {"1 mm", std::format("{}", pkr::units::millimeter_t{1.0})},
        {"1 cm", std::format("{}", pkr::units::centimeter_t{1.0})},
        {"1 dm", std::format("{}", pkr::units::decimeter_t{1.0})},
        {"1 m", std::format("{}", pkr::units::meter_t{1.0})},
        {"1 dam", std::format("{}", pkr::units::decameter_t{1.0})},
        {"1 hm", std::format("{}", pkr::units::hectometer_t{1.0})},
        {"1 km", std::format("{}", pkr::units::kilometer_t{1.0})},
        {"1 Mm", std::format("{}", pkr::units::megameter_t{1.0})},
        {"1 Gm", std::format("{}", pkr::units::gigameter_t{1.0})},
    };

    // Verify all tests match expected output
    for (const auto& test_case : test_cases)
    {
        ASSERT_EQ(test_case.result, test_case.expected) << "Failed for expected: " << test_case.expected;
    }
}

TEST_F(SiLengthFormattingTest, output_stream_compatibility)
{
    pkr::units::meter_t m{3.5};
    std::ostringstream oss;
    oss << std::format("{}", m);
    ASSERT_EQ(oss.str(), "3.5 m");
}

TEST_F(SiLengthFormattingTest, format_in_string_context)
{
    pkr::units::kilometer_t distance{42.195};
    std::string message = std::format("The marathon distance is approximately {}", distance);
    ASSERT_EQ(message, "The marathon distance is approximately 42.195 km");
}

TEST_F(SiLengthFormattingTest, multiple_values_formatted)
{
    pkr::units::meter_t width{3.2};
    pkr::units::meter_t depth{2.5};
    pkr::units::meter_t height{1.75};

    std::string result = std::format("Dimensions: {}W x {}D x {}H", width, depth, height);

    ASSERT_EQ(result, "Dimensions: 3.2 mW x 2.5 mD x 1.75 mH");
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiLengthFormattingTest, very_small_value)
{
    pkr::units::meter_t m{1e-15};
    std::string result = std::format("{:e}", m);
    ASSERT_EQ(result, "1.000000e-15 m");
}

TEST_F(SiLengthFormattingTest, very_large_value)
{
    pkr::units::kilometer_t km{1e15};
    std::string result = std::format("{:e}", km);
    ASSERT_EQ(result, "1.000000e+15 km");
}

TEST_F(SiLengthFormattingTest, default_and_explicit_precision)
{
    pkr::units::meter_t m{1.0 / 3.0};
    std::string result_explicit = std::format("{:.6f}", m);

    ASSERT_EQ(result_explicit, "0.333333 m");
}
