#include <gtest/gtest.h>
#include <format>
#include <pkr_units/units/derived/velocity.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;

class VelocityFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII) - double
// ============================================================================

TEST_F(VelocityFormattingTest, meter_per_second_ascii_formatting_double)
{
    pkr::units::meter_per_second_t<double> v{1.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "1 m/s");
}

TEST_F(VelocityFormattingTest, meter_per_second_ascii_formatting_float)
{
    pkr::units::meter_per_second_t<float> v{1.0f};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "1 m/s");
}

TEST_F(VelocityFormattingTest, meter_per_second_ascii_precision_double)
{
    pkr::units::meter_per_second_t<double> v{3.14159};
    std::string result = std::format("{:.2f}", v);
    ASSERT_EQ(result, "3.14 m/s");
}

TEST_F(VelocityFormattingTest, meter_per_second_ascii_precision_float)
{
    pkr::units::meter_per_second_t<float> v{3.14159f};
    std::string result = std::format("{:.2f}", v);
    ASSERT_EQ(result, "3.14 m/s");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_ascii_formatting_double)
{
    pkr::units::kilometer_per_hour_t<double> v{36.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "36 km/h");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_ascii_formatting_float)
{
    pkr::units::kilometer_per_hour_t<float> v{36.0f};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "36 km/h");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_ascii_precision_double)
{
    pkr::units::kilometer_per_hour_t<double> v{100.12345};
    std::string result = std::format("{:.1f}", v);
    ASSERT_EQ(result, "100.1 km/h");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_ascii_precision_float)
{
    pkr::units::kilometer_per_hour_t<float> v{100.12345f};
    std::string result = std::format("{:.1f}", v);
    ASSERT_EQ(result, "100.1 km/h");
}

TEST_F(VelocityFormattingTest, centimeter_per_second_ascii_formatting_double)
{
    pkr::units::centimeter_per_second_t<double> v{100.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "100 cm/s");
}

TEST_F(VelocityFormattingTest, centimeter_per_second_ascii_formatting_float)
{
    pkr::units::centimeter_per_second_t<float> v{100.0f};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "100 cm/s");
}

TEST_F(VelocityFormattingTest, millimeter_per_second_ascii_formatting_double)
{
    pkr::units::millimeter_per_second_t<double> v{500.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "500 mm/s");
}

TEST_F(VelocityFormattingTest, millimeter_per_second_ascii_formatting_float)
{
    pkr::units::millimeter_per_second_t<float> v{500.0f};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "500 mm/s");
}

TEST_F(VelocityFormattingTest, kilometer_per_second_ascii_formatting_double)
{
    pkr::units::kilometer_per_second_t<double> v{10.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "10 km/s");
}

TEST_F(VelocityFormattingTest, kilometer_per_second_ascii_formatting_float)
{
    pkr::units::kilometer_per_second_t<float> v{10.0f};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "10 km/s");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t - double
// ============================================================================

TEST_F(VelocityFormattingTest, meter_per_second_wide_formatting_double)
{
    pkr::units::meter_per_second_t<double> v{1.0};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"1 m\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, meter_per_second_wide_formatting_float)
{
    pkr::units::meter_per_second_t<float> v{1.0f};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"1 m\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, meter_per_second_wide_precision_double)
{
    pkr::units::meter_per_second_t<double> v{3.14159};
    std::wstring result = std::format(L"{:.2f}", v);
    ASSERT_EQ(result, L"3.14 m\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, meter_per_second_wide_precision_float)
{
    pkr::units::meter_per_second_t<float> v{3.14159f};
    std::wstring result = std::format(L"{:.2f}", v);
    ASSERT_EQ(result, L"3.14 m\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_wide_formatting_double)
{
    pkr::units::kilometer_per_hour_t<double> v{36.0};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"36 km\u00B7h\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_wide_formatting_float)
{
    pkr::units::kilometer_per_hour_t<float> v{36.0f};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"36 km\u00B7h\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_wide_precision_double)
{
    pkr::units::kilometer_per_hour_t<double> v{100.12345};
    std::wstring result = std::format(L"{:.1f}", v);
    ASSERT_EQ(result, L"100.1 km\u00B7h\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_wide_precision_float)
{
    pkr::units::kilometer_per_hour_t<float> v{100.12345f};
    std::wstring result = std::format(L"{:.1f}", v);
    ASSERT_EQ(result, L"100.1 km\u00B7h\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, centimeter_per_second_wide_formatting_double)
{
    pkr::units::centimeter_per_second_t<double> v{100.0};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"100 cm\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, centimeter_per_second_wide_formatting_float)
{
    pkr::units::centimeter_per_second_t<float> v{100.0f};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"100 cm\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, millimeter_per_second_wide_formatting_double)
{
    pkr::units::millimeter_per_second_t<double> v{500.0};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"500 mm\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, millimeter_per_second_wide_formatting_float)
{
    pkr::units::millimeter_per_second_t<float> v{500.0f};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"500 mm\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, kilometer_per_second_wide_formatting_double)
{
    pkr::units::kilometer_per_second_t<double> v{10.0};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"10 km\u00B7s\u207B\u00B9");
}

TEST_F(VelocityFormattingTest, kilometer_per_second_wide_formatting_float)
{
    pkr::units::kilometer_per_second_t<float> v{10.0f};
    std::wstring result = std::format(L"{}", v);
    ASSERT_EQ(result, L"10 km\u00B7s\u207B\u00B9");
}

{
    // Start with 36 km/h, which should be 10 m/s
    pkr::units::kilometer_per_hour_t<double> kmh{36.0};

    // Cast to meter_per_second_t
    auto mps = pkr::units::unit_cast<pkr::units::meter_per_second_t<double>>(kmh);

    // Format the cast result and verify it uses m/s
    std::string result = std::format("{}", mps);
    ASSERT_EQ(result, "10 m/s");
}
