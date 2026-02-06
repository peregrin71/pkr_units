#include <gtest/gtest.h>
#include <pkr_units/format/si.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/mass.h>

using namespace ::testing;

class SiMassFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII) - double
// ============================================================================

TEST_F(SiMassFormattingTest, kilogram_ascii_formatting_double)
{
    pkr::units::kilogram_t<double> kg{5.0};
    std::string result = std::format("{}", kg);
    ASSERT_EQ(result, "5 kg");
}

TEST_F(SiMassFormattingTest, kilogram_ascii_formatting_float)
{
    pkr::units::kilogram_t<float> kg{5.0f};
    std::string result = std::format("{}", kg);
    ASSERT_EQ(result, "5 kg");
}

TEST_F(SiMassFormattingTest, kilogram_ascii_precision_double)
{
    pkr::units::kilogram_t<double> kg{5.123456};
    std::string result = std::format("{:.2f}", kg);
    ASSERT_EQ(result, "5.12 kg");
}

TEST_F(SiMassFormattingTest, kilogram_ascii_precision_float)
{
    pkr::units::kilogram_t<float> kg{5.123456f};
    std::string result = std::format("{:.2f}", kg);
    ASSERT_EQ(result, "5.12 kg");
}

TEST_F(SiMassFormattingTest, gram_ascii_formatting_double)
{
    pkr::units::gram_t<double> g{2500.0};
    std::string result = std::format("{}", g);
    ASSERT_EQ(result, "2500 g");
}

TEST_F(SiMassFormattingTest, gram_ascii_formatting_float)
{
    pkr::units::gram_t<float> g{2500.0f};
    std::string result = std::format("{}", g);
    ASSERT_EQ(result, "2500 g");
}

TEST_F(SiMassFormattingTest, milligram_ascii_formatting_double)
{
    pkr::units::milligram_t<double> mg{1500.0};
    std::string result = std::format("{}", mg);
    ASSERT_EQ(result, "1500 mg");
}

TEST_F(SiMassFormattingTest, milligram_ascii_formatting_float)
{
    pkr::units::milligram_t<float> mg{1500.0f};
    std::string result = std::format("{}", mg);
    ASSERT_EQ(result, "1500 mg");
}

TEST_F(SiMassFormattingTest, microgram_ascii_formatting_double)
{
    pkr::units::microgram_t<double> ug{0.5};
    std::string result = std::format("{}", ug);
    ASSERT_EQ(result, "0.5 ug");
}

TEST_F(SiMassFormattingTest, microgram_ascii_formatting_float)
{
    pkr::units::microgram_t<float> ug{0.5f};
    std::string result = std::format("{}", ug);
    ASSERT_EQ(result, "0.5 ug");
}

TEST_F(SiMassFormattingTest, nanogram_ascii_formatting_double)
{
    pkr::units::nanogram_t<double> ng{100.0};
    std::string result = std::format("{}", ng);
    ASSERT_EQ(result, "100 ng");
}

TEST_F(SiMassFormattingTest, nanogram_ascii_formatting_float)
{
    pkr::units::nanogram_t<float> ng{100.0f};
    std::string result = std::format("{}", ng);
    ASSERT_EQ(result, "100 ng");
}

TEST_F(SiMassFormattingTest, picogram_ascii_formatting_double)
{
    pkr::units::picogram_t<double> pg{500.0};
    std::string result = std::format("{}", pg);
    ASSERT_EQ(result, "500 pg");
}

TEST_F(SiMassFormattingTest, picogram_ascii_formatting_float)
{
    pkr::units::picogram_t<float> pg{500.0f};
    std::string result = std::format("{}", pg);
    ASSERT_EQ(result, "500 pg");
}

TEST_F(SiMassFormattingTest, metric_ton_ascii_formatting_double)
{
    pkr::units::metric_ton_t<double> t{2.5};
    std::string result = std::format("{}", t);
    ASSERT_EQ(result, "2.5 t");
}

TEST_F(SiMassFormattingTest, metric_ton_ascii_formatting_float)
{
    pkr::units::metric_ton_t<float> t{2.5f};
    std::string result = std::format("{}", t);
    ASSERT_EQ(result, "2.5 t");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t - double
// ============================================================================

TEST_F(SiMassFormattingTest, kilogram_wide_formatting_double)
{
    pkr::units::kilogram_t<double> kg{5.0};
    std::wstring result = std::format(L"{}", kg);
    ASSERT_EQ(result, L"5 kg");
}

TEST_F(SiMassFormattingTest, kilogram_wide_formatting_float)
{
    pkr::units::kilogram_t<float> kg{5.0f};
    std::wstring result = std::format(L"{}", kg);
    ASSERT_EQ(result, L"5 kg");
}

TEST_F(SiMassFormattingTest, kilogram_wide_precision_double)
{
    pkr::units::kilogram_t<double> kg{5.123456};
    std::wstring result = std::format(L"{:.2f}", kg);
    ASSERT_EQ(result, L"5.12 kg");
}

TEST_F(SiMassFormattingTest, kilogram_wide_precision_float)
{
    pkr::units::kilogram_t<float> kg{5.123456f};
    std::wstring result = std::format(L"{:.2f}", kg);
    ASSERT_EQ(result, L"5.12 kg");
}

TEST_F(SiMassFormattingTest, gram_wide_formatting_double)
{
    pkr::units::gram_t<double> g{2500.0};
    std::wstring result = std::format(L"{}", g);
    ASSERT_EQ(result, L"2500 g");
}

TEST_F(SiMassFormattingTest, gram_wide_formatting_float)
{
    pkr::units::gram_t<float> g{2500.0f};
    std::wstring result = std::format(L"{}", g);
    ASSERT_EQ(result, L"2500 g");
}

TEST_F(SiMassFormattingTest, milligram_wide_formatting_double)
{
    pkr::units::milligram_t<double> mg{1500.0};
    std::wstring result = std::format(L"{}", mg);
    ASSERT_EQ(result, L"1500 mg");
}

TEST_F(SiMassFormattingTest, milligram_wide_formatting_float)
{
    pkr::units::milligram_t<float> mg{1500.0f};
    std::wstring result = std::format(L"{}", mg);
    ASSERT_EQ(result, L"1500 mg");
}

TEST_F(SiMassFormattingTest, microgram_wide_formatting_double)
{
    pkr::units::microgram_t<double> ug{0.5};
    std::wstring result = std::format(L"{}", ug);
    ASSERT_EQ(result, L"0.5 \u00b5g");
}

TEST_F(SiMassFormattingTest, microgram_wide_formatting_float)
{
    pkr::units::microgram_t<float> ug{0.5f};
    std::wstring result = std::format(L"{}", ug);
    ASSERT_EQ(result, L"0.5 \u00b5g");
}

TEST_F(SiMassFormattingTest, nanogram_wide_formatting_double)
{
    pkr::units::nanogram_t<double> ng{100.0};
    std::wstring result = std::format(L"{}", ng);
    ASSERT_EQ(result, L"100 ng");
}

TEST_F(SiMassFormattingTest, nanogram_wide_formatting_float)
{
    pkr::units::nanogram_t<float> ng{100.0f};
    std::wstring result = std::format(L"{}", ng);
    ASSERT_EQ(result, L"100 ng");
}

TEST_F(SiMassFormattingTest, picogram_wide_formatting_double)
{
    pkr::units::picogram_t<double> pg{500.0};
    std::wstring result = std::format(L"{}", pg);
    ASSERT_EQ(result, L"500 pg");
}

TEST_F(SiMassFormattingTest, picogram_wide_formatting_float)
{
    pkr::units::picogram_t<float> pg{500.0f};
    std::wstring result = std::format(L"{}", pg);
    ASSERT_EQ(result, L"500 pg");
}

TEST_F(SiMassFormattingTest, metric_ton_wide_formatting_double)
{
    pkr::units::metric_ton_t<double> t{2.5};
    std::wstring result = std::format(L"{}", t);
    ASSERT_EQ(result, L"2.5 t");
}

TEST_F(SiMassFormattingTest, metric_ton_wide_formatting_float)
{
    pkr::units::metric_ton_t<float> t{2.5f};
    std::wstring result = std::format(L"{}", t);
    ASSERT_EQ(result, L"2.5 t");
}
