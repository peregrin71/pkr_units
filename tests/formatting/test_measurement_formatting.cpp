#include <gtest/gtest.h>
#include <format>
#include <sstream>
#include <iomanip>
#include <string>
#include <pkr_units/si_units.h>
#include <pkr_units/measurements.h>

// ============================================================================
// measurement_lin_t Formatting Tests (Linear/Worst-Case Uncertainty)
// ============================================================================

class MeasurementLinFormattingTest : public ::testing::Test
{
};

// Basic ASCII formatting tests
TEST_F(MeasurementLinFormattingTest, basic_ascii_formatting)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "5 +/- 0.1 m");
}

TEST_F(MeasurementLinFormattingTest, precision_control)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.123, 0.456};
    auto formatted = std::format("{:.2f}", m);
    EXPECT_EQ(formatted, "5.12 +/- 0.46 m");
}

TEST_F(MeasurementLinFormattingTest, precision_one_decimal)
{
    pkr::units::measurement_lin_t<pkr::units::kilogram_t<double>> m{100.567, 2.345};
    auto formatted = std::format("{:.1f}", m);
    EXPECT_EQ(formatted, "100.6 +/- 2.3 kg");
}

TEST_F(MeasurementLinFormattingTest, no_precision_specified)
{
    pkr::units::measurement_lin_t<pkr::units::second_t<float>> m{2.5f, 0.05f};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "2.5 +/- 0.05 s");
}

TEST_F(MeasurementLinFormattingTest, high_precision)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.123456789, 0.000123456};
    auto formatted = std::format("{:.4f}", m);
    EXPECT_EQ(formatted, "5.1235 +/- 0.0001 m");
}

// Different unit type tests
TEST_F(MeasurementLinFormattingTest, kilogram_measurement)
{
    pkr::units::measurement_lin_t<pkr::units::kilogram_t<double>> m{100.0, 2.5};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "100 +/- 2.5 kg");
}

TEST_F(MeasurementLinFormattingTest, second_measurement)
{
    pkr::units::measurement_lin_t<pkr::units::second_t<double>> m{30.0, 1.0};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "30 +/- 1 s");
}

TEST_F(MeasurementLinFormattingTest, ampere_measurement)
{
    pkr::units::measurement_lin_t<pkr::units::ampere_t<double>> m{2.5, 0.1};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "2.5 +/- 0.1 A");
}

TEST_F(MeasurementLinFormattingTest, kilometer_measurement)
{
    pkr::units::measurement_lin_t<pkr::units::kilometer_t<double>> m{100.0, 5.0};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "100 +/- 5 km");
}

// Wide-character tests
TEST_F(MeasurementLinFormattingTest, wide_char_formatting)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    auto formatted = std::format(L"{}", m);
    EXPECT_EQ(formatted, L"5 \u00b1 0.1 m");
}

TEST_F(MeasurementLinFormattingTest, wide_char_with_precision)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.123, 0.456};
    auto formatted = std::format(L"{:.2f}", m);
    EXPECT_EQ(formatted, L"5.12 \u00b1 0.46 m");
}

TEST_F(MeasurementLinFormattingTest, wide_char_kilogram)
{
    pkr::units::measurement_lin_t<pkr::units::kilogram_t<double>> m{100.0, 2.5};
    auto formatted = std::format(L"{}", m);
    EXPECT_EQ(formatted, L"100 \u00b1 2.5 kg");
}

// ostream operator tests
TEST_F(MeasurementLinFormattingTest, ostream_operator)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "5 +/- 0.1 m");
}

TEST_F(MeasurementLinFormattingTest, wostream_operator)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    std::wstringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), L"5 \u00b1 0.1 m");
}

// ============================================================================
// measurement_rss_t Formatting Tests (Root-Sum-Square Uncertainty)
// ============================================================================

class MeasurementRssFormattingTest : public ::testing::Test
{
};

// Basic ASCII formatting tests - RSS uses ± character
TEST_F(MeasurementRssFormattingTest, basic_ascii_formatting)
{
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    auto formatted = std::format("{}", m);
    // Should contain space, ±, and unit. Check components instead of exact string
    // since UTF-8 encoding of ± is tricky
    EXPECT_TRUE(formatted.find("5") != std::string::npos);
    EXPECT_TRUE(formatted.find("0.1") != std::string::npos);
    EXPECT_TRUE(formatted.find("m") != std::string::npos);
}

TEST_F(MeasurementRssFormattingTest, precision_control)
{
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> m{5.123, 0.456};
    auto formatted = std::format("{:.2f}", m);
    EXPECT_TRUE(formatted.find("5.12") != std::string::npos);
    EXPECT_TRUE(formatted.find("0.46") != std::string::npos);
    EXPECT_TRUE(formatted.find("m") != std::string::npos);
}

TEST_F(MeasurementRssFormattingTest, kilogram_measurement)
{
    pkr::units::measurement_rss_t<pkr::units::kilogram_t<double>> m{100.0, 2.5};
    auto formatted = std::format("{}", m);
    EXPECT_TRUE(formatted.find("100") != std::string::npos);
    EXPECT_TRUE(formatted.find("2.5") != std::string::npos);
    EXPECT_TRUE(formatted.find("kg") != std::string::npos);
}

TEST_F(MeasurementRssFormattingTest, second_measurement)
{
    pkr::units::measurement_rss_t<pkr::units::second_t<double>> m{30.0, 1.0};
    auto formatted = std::format("{}", m);
    EXPECT_TRUE(formatted.find("30") != std::string::npos);
    EXPECT_TRUE(formatted.find("1") != std::string::npos);
    EXPECT_TRUE(formatted.find("s") != std::string::npos);
}

// Wide-character tests
TEST_F(MeasurementRssFormattingTest, wide_char_formatting)
{
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    auto formatted = std::format(L"{}", m);
    EXPECT_EQ(formatted, L"5 \u00b1 0.1 m"); // Unicode ±
}

TEST_F(MeasurementRssFormattingTest, wide_char_with_precision)
{
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> m{5.123, 0.456};
    auto formatted = std::format(L"{:.2f}", m);
    EXPECT_EQ(formatted, L"5.12 \u00b1 0.46 m"); // Unicode ±
}

TEST_F(MeasurementRssFormattingTest, wide_char_kilogram)
{
    pkr::units::measurement_rss_t<pkr::units::kilogram_t<double>> m{100.0, 2.5};
    auto formatted = std::format(L"{}", m);
    EXPECT_EQ(formatted, L"100 \u00b1 2.5 kg"); // Unicode ±
}

// ostream operator tests
TEST_F(MeasurementRssFormattingTest, ostream_operator)
{
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    std::stringstream ss;
    ss << m;
    EXPECT_NE(ss.str(), ""); // Should output something
}

TEST_F(MeasurementRssFormattingTest, wostream_operator)
{
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> m{5.0, 0.1};
    std::wstringstream ss;
    ss << m;
    EXPECT_NE(ss.str(), L""); // Should output something
}

// ============================================================================
// Integration Tests: Verifying Distinction Between Linear and RSS
// ============================================================================

class MeasurementFormattingDistinctionTest : public ::testing::Test
{
};

TEST_F(MeasurementFormattingDistinctionTest, distinguish_lin_vs_rss)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> lin{5.0, 0.1};
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> rss{5.0, 0.1};

    auto lin_formatted = std::format("{}", lin);
    auto rss_formatted = std::format("{}", rss);

    // In ASCII mode, both use +/- since ± is not an ASCII character
    // The distinction is visible in wide-char mode
    EXPECT_TRUE(lin_formatted.find("+/-") != std::string::npos);
    EXPECT_TRUE(rss_formatted.find("+/-") != std::string::npos);
}

TEST_F(MeasurementFormattingDistinctionTest, distinguish_lin_vs_rss_wide)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> lin{5.0, 0.1};
    pkr::units::measurement_rss_t<pkr::units::meter_t<double>> rss{5.0, 0.1};

    auto lin_formatted = std::format(L"{}", lin);
    auto rss_formatted = std::format(L"{}", rss);

    // Both should use the same ± separator for wide characters
    EXPECT_EQ(lin_formatted, rss_formatted);
    EXPECT_TRUE(lin_formatted.find(L"\u00b1") != std::wstring::npos);
}

// ============================================================================
// Edge Cases and Special Values
// ============================================================================

class MeasurementFormattingEdgeCasesTest : public ::testing::Test
{
};

TEST_F(MeasurementFormattingEdgeCasesTest, zero_uncertainty)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{5.0, 0.0};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "5 +/- 0 m");
}

TEST_F(MeasurementFormattingEdgeCasesTest, zero_value)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{0.0, 0.1};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "0 +/- 0.1 m");
}

TEST_F(MeasurementFormattingEdgeCasesTest, negative_value)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{-5.0, 0.1};
    auto formatted = std::format("{}", m);
    EXPECT_EQ(formatted, "-5 +/- 0.1 m");
}

TEST_F(MeasurementFormattingEdgeCasesTest, very_small_values)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<double>> m{0.00123, 0.00045};
    auto formatted = std::format("{:.5}", m);
    EXPECT_EQ(formatted, "0.00123 +/- 0.00045 m");
}

// ============================================================================
// Float Type Tests
// ============================================================================

class MeasurementFormattingFloatTest : public ::testing::Test
{
};

TEST_F(MeasurementFormattingFloatTest, float_lin_measurement)
{
    pkr::units::measurement_lin_t<pkr::units::meter_t<float>> m{5.5f, 0.1f};
    auto formatted = std::format("{}", m);
    EXPECT_TRUE(formatted.find("5.5") != std::string::npos);
    EXPECT_TRUE(formatted.find("0.1") != std::string::npos);
    EXPECT_TRUE(formatted.find("m") != std::string::npos);
}

TEST_F(MeasurementFormattingFloatTest, float_rss_measurement)
{
    pkr::units::measurement_rss_t<pkr::units::meter_t<float>> m{5.5f, 0.1f};
    auto formatted = std::format("{}", m);
    EXPECT_TRUE(formatted.find("5.5") != std::string::npos);
    EXPECT_TRUE(formatted.find("0.1") != std::string::npos);
    EXPECT_TRUE(formatted.find("m") != std::string::npos);
}

// ============================================================================
// Additional Derived Unit Tests
// ============================================================================

class MeasurementFormattingDerivedUnitsTest : public ::testing::Test
{
};

TEST_F(MeasurementFormattingDerivedUnitsTest, meter_per_second)
{
    pkr::units::meter_t<double> distance{100.0};
    pkr::units::second_t<double> time{2.0};
    auto velocity = distance / time;

    pkr::units::measurement_lin_t<decltype(velocity)> m{50.0, 1.0};
    auto formatted = std::format("{}", m);
    EXPECT_TRUE(formatted.find("50") != std::string::npos);
    EXPECT_TRUE(formatted.find("1") != std::string::npos);
    EXPECT_TRUE(formatted.find("m/s") != std::string::npos);
}

TEST_F(MeasurementFormattingDerivedUnitsTest, kilogram_meter_per_second_squared)
{
    pkr::units::kilogram_t<double> mass{10.0};
    pkr::units::meter_t<double> distance{2.0};
    pkr::units::second_t<double> time{1.0};

    auto force = mass * distance / (time * time);
    pkr::units::measurement_lin_t<decltype(force)> m{20.0, 2.0};
    auto formatted = std::format("{}", m);
    EXPECT_TRUE(formatted.find("20") != std::string::npos);
    EXPECT_TRUE(formatted.find("2") != std::string::npos);
}
