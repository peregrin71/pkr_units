#include <gtest/gtest.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/mechanical/force.h>
#include <pkr_units/format/si.h>

using namespace ::testing;

class ForceFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII) - double
// ============================================================================

TEST_F(ForceFormattingTest, newton_ascii_formatting_double)
{
    pkr::units::newton_t<double> force{100.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "100 N");
}

TEST_F(ForceFormattingTest, newton_ascii_formatting_float)
{
    pkr::units::newton_t<float> force{100.0f};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "100 N");
}

TEST_F(ForceFormattingTest, newton_ascii_precision_double)
{
    pkr::units::newton_t<double> force{123.456789};
    std::string result = std::format("{:.2f}", force);
    ASSERT_EQ(result, "123.46 N");
}

TEST_F(ForceFormattingTest, newton_ascii_precision_float)
{
    pkr::units::newton_t<float> force{123.456789f};
    std::string result = std::format("{:.2f}", force);
    ASSERT_EQ(result, "123.46 N");
}

TEST_F(ForceFormattingTest, kilonewton_ascii_formatting_double)
{
    pkr::units::kilonewton_t<double> force{5.5};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "5.5 kN");
}

TEST_F(ForceFormattingTest, kilonewton_ascii_formatting_float)
{
    pkr::units::kilonewton_t<float> force{5.5f};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "5.5 kN");
}

TEST_F(ForceFormattingTest, meganewton_ascii_formatting_double)
{
    pkr::units::meganewton_t<double> force{2.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "2 MN");
}

TEST_F(ForceFormattingTest, meganewton_ascii_formatting_float)
{
    pkr::units::meganewton_t<float> force{2.0f};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "2 MN");
}

TEST_F(ForceFormattingTest, millinewton_ascii_formatting_double)
{
    pkr::units::millinewton_t<double> force{500.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "500 mN");
}

TEST_F(ForceFormattingTest, millinewton_ascii_formatting_float)
{
    pkr::units::millinewton_t<float> force{500.0f};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "500 mN");
}

TEST_F(ForceFormattingTest, micronewton_ascii_formatting_double)
{
    pkr::units::micronewton_t<double> force{1000.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "1000 uN");
}

TEST_F(ForceFormattingTest, micronewton_ascii_formatting_float)
{
    pkr::units::micronewton_t<float> force{1000.0f};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "1000 uN");
}

TEST_F(ForceFormattingTest, nanonewton_ascii_formatting_double)
{
    pkr::units::nanonewton_t<double> force{5000000.0};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "5e+06 nN");
}

TEST_F(ForceFormattingTest, nanonewton_ascii_formatting_float)
{
    pkr::units::nanonewton_t<float> force{5000000.0f};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "5e+06 nN");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t - double
// ============================================================================

TEST_F(ForceFormattingTest, newton_wide_formatting_double)
{
    pkr::units::newton_t<double> force{100.0};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"100 N");
}

TEST_F(ForceFormattingTest, newton_wide_formatting_float)
{
    pkr::units::newton_t<float> force{100.0f};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"100 N");
}

TEST_F(ForceFormattingTest, newton_wide_precision_double)
{
    pkr::units::newton_t<double> force{123.456789};
    std::wstring result = std::format(L"{:.2f}", force);
    ASSERT_EQ(result, L"123.46 N");
}

TEST_F(ForceFormattingTest, newton_wide_precision_float)
{
    pkr::units::newton_t<float> force{123.456789f};
    std::wstring result = std::format(L"{:.2f}", force);
    ASSERT_EQ(result, L"123.46 N");
}

TEST_F(ForceFormattingTest, kilonewton_wide_formatting_double)
{
    pkr::units::kilonewton_t<double> force{5.5};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"5.5 kN");
}

TEST_F(ForceFormattingTest, kilonewton_wide_formatting_float)
{
    pkr::units::kilonewton_t<float> force{5.5f};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"5.5 kN");
}

TEST_F(ForceFormattingTest, meganewton_wide_formatting_double)
{
    pkr::units::meganewton_t<double> force{2.0};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"2 MN");
}

TEST_F(ForceFormattingTest, meganewton_wide_formatting_float)
{
    pkr::units::meganewton_t<float> force{2.0f};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"2 MN");
}

TEST_F(ForceFormattingTest, millinewton_wide_formatting_double)
{
    pkr::units::millinewton_t<double> force{500.0};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"500 mN");
}

TEST_F(ForceFormattingTest, millinewton_wide_formatting_float)
{
    pkr::units::millinewton_t<float> force{500.0f};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"500 mN");
}

TEST_F(ForceFormattingTest, micronewton_wide_formatting_double)
{
    pkr::units::micronewton_t<double> force{1000.0};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"1000 \u00b5N");
}

TEST_F(ForceFormattingTest, micronewton_wide_formatting_float)
{
    pkr::units::micronewton_t<float> force{1000.0f};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"1000 \u00b5N");
}

TEST_F(ForceFormattingTest, nanonewton_wide_formatting_double)
{
    pkr::units::nanonewton_t<double> force{5000000.0};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"5e+06 nN");
}

TEST_F(ForceFormattingTest, nanonewton_wide_formatting_float)
{
    pkr::units::nanonewton_t<float> force{5000000.0f};
    std::wstring result = std::format(L"{}", force);
    ASSERT_EQ(result, L"5e+06 nN");
}

TEST_F(ForceFormattingTest, very_small_force)
{
    pkr::units::nanonewton_t force{1e-12};
    std::string result = std::format("{:.2e}", force);
    ASSERT_EQ(result, "1.00e-12 nN");
}

TEST_F(ForceFormattingTest, very_large_force)
{
    pkr::units::meganewton_t force{1e6};
    std::string result = std::format("{:.1e}", force);
    ASSERT_EQ(result, "1.0e+06 MN");
}

TEST_F(ForceFormattingTest, default_precision)
{
    pkr::units::newton_t force{3.141592653589793};
    std::string result = std::format("{}", force);
    std::string expected = std::format("{}", 3.141592653589793) + " N";
    ASSERT_EQ(result, expected);
}

TEST_F(ForceFormattingTest, value_preservation)
{
    pkr::units::newton_t force{123.456};
    std::string result = std::format("{}", force);
    ASSERT_EQ(result, "123.456 N");
}
