#include <gtest/gtest.h>
#include <pkr_units/format/si.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/current.h>

using namespace ::testing;

class SiCurrentFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII) - double
// ============================================================================

TEST_F(SiCurrentFormattingTest, ampere_ascii_formatting_double)
{
    pkr::units::ampere_t<double> A{5.0};
    std::string result = std::format("{}", A);
    ASSERT_EQ(result, "5 A");
}

TEST_F(SiCurrentFormattingTest, ampere_ascii_formatting_float)
{
    pkr::units::ampere_t<float> A{5.0f};
    std::string result = std::format("{}", A);
    ASSERT_EQ(result, "5 A");
}

TEST_F(SiCurrentFormattingTest, ampere_ascii_precision_double)
{
    pkr::units::ampere_t<double> A{5.123456};
    std::string result = std::format("{:.2f}", A);
    ASSERT_EQ(result, "5.12 A");
}

TEST_F(SiCurrentFormattingTest, ampere_ascii_precision_float)
{
    pkr::units::ampere_t<float> A{5.123456f};
    std::string result = std::format("{:.2f}", A);
    ASSERT_EQ(result, "5.12 A");
}

TEST_F(SiCurrentFormattingTest, milliampere_ascii_formatting_double)
{
    pkr::units::milliampere_t<double> mA{1500.0};
    std::string result = std::format("{}", mA);
    ASSERT_EQ(result, "1500 mA");
}

TEST_F(SiCurrentFormattingTest, milliampere_ascii_formatting_float)
{
    pkr::units::milliampere_t<float> mA{1500.0f};
    std::string result = std::format("{}", mA);
    ASSERT_EQ(result, "1500 mA");
}

TEST_F(SiCurrentFormattingTest, microampere_ascii_formatting_double)
{
    pkr::units::microampere_t<double> uA{0.5};
    std::string result = std::format("{}", uA);
    ASSERT_EQ(result, "0.5 uA");
}

TEST_F(SiCurrentFormattingTest, microampere_ascii_formatting_float)
{
    pkr::units::microampere_t<float> uA{0.5f};
    std::string result = std::format("{}", uA);
    ASSERT_EQ(result, "0.5 uA");
}

TEST_F(SiCurrentFormattingTest, nanoampere_ascii_formatting_double)
{
    pkr::units::nanoampere_t<double> nA{100.0};
    std::string result = std::format("{}", nA);
    ASSERT_EQ(result, "100 nA");
}

TEST_F(SiCurrentFormattingTest, nanoampere_ascii_formatting_float)
{
    pkr::units::nanoampere_t<float> nA{100.0f};
    std::string result = std::format("{}", nA);
    ASSERT_EQ(result, "100 nA");
}

TEST_F(SiCurrentFormattingTest, kiloampere_ascii_formatting_double)
{
    pkr::units::kiloampere_t<double> kA{2.5};
    std::string result = std::format("{}", kA);
    ASSERT_EQ(result, "2.5 kA");
}

TEST_F(SiCurrentFormattingTest, kiloampere_ascii_formatting_float)
{
    pkr::units::kiloampere_t<float> kA{2.5f};
    std::string result = std::format("{}", kA);
    ASSERT_EQ(result, "2.5 kA");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t - double
// ============================================================================

TEST_F(SiCurrentFormattingTest, ampere_wide_formatting_double)
{
    pkr::units::ampere_t<double> A{5.0};
    std::wstring result = std::format(L"{}", A);
    ASSERT_EQ(result, L"5 A");
}

TEST_F(SiCurrentFormattingTest, ampere_wide_formatting_float)
{
    pkr::units::ampere_t<float> A{5.0f};
    std::wstring result = std::format(L"{}", A);
    ASSERT_EQ(result, L"5 A");
}

TEST_F(SiCurrentFormattingTest, ampere_wide_precision_double)
{
    pkr::units::ampere_t<double> A{5.123456};
    std::wstring result = std::format(L"{:.2f}", A);
    ASSERT_EQ(result, L"5.12 A");
}

TEST_F(SiCurrentFormattingTest, ampere_wide_precision_float)
{
    pkr::units::ampere_t<float> A{5.123456f};
    std::wstring result = std::format(L"{:.2f}", A);
    ASSERT_EQ(result, L"5.12 A");
}

TEST_F(SiCurrentFormattingTest, milliampere_wide_formatting_double)
{
    pkr::units::milliampere_t<double> mA{1500.0};
    std::wstring result = std::format(L"{}", mA);
    ASSERT_EQ(result, L"1500 mA");
}

TEST_F(SiCurrentFormattingTest, milliampere_wide_formatting_float)
{
    pkr::units::milliampere_t<float> mA{1500.0f};
    std::wstring result = std::format(L"{}", mA);
    ASSERT_EQ(result, L"1500 mA");
}

TEST_F(SiCurrentFormattingTest, microampere_wide_formatting_double)
{
    pkr::units::microampere_t<double> uA{0.5};
    std::wstring result = std::format(L"{}", uA);
    ASSERT_EQ(result, L"0.5 \u00b5A");
}

TEST_F(SiCurrentFormattingTest, microampere_wide_formatting_float)
{
    pkr::units::microampere_t<float> uA{0.5f};
    std::wstring result = std::format(L"{}", uA);
    ASSERT_EQ(result, L"0.5 \u00b5A");
}

TEST_F(SiCurrentFormattingTest, nanoampere_wide_formatting_double)
{
    pkr::units::nanoampere_t<double> nA{100.0};
    std::wstring result = std::format(L"{}", nA);
    ASSERT_EQ(result, L"100 nA");
}

TEST_F(SiCurrentFormattingTest, nanoampere_wide_formatting_float)
{
    pkr::units::nanoampere_t<float> nA{100.0f};
    std::wstring result = std::format(L"{}", nA);
    ASSERT_EQ(result, L"100 nA");
}

TEST_F(SiCurrentFormattingTest, kiloampere_wide_formatting_double)
{
    pkr::units::kiloampere_t<double> kA{2.5};
    std::wstring result = std::format(L"{}", kA);
    ASSERT_EQ(result, L"2.5 kA");
}

TEST_F(SiCurrentFormattingTest, kiloampere_wide_formatting_float)
{
    pkr::units::kiloampere_t<float> kA{2.5f};
    std::wstring result = std::format(L"{}", kA);
    ASSERT_EQ(result, L"2.5 kA");
}
