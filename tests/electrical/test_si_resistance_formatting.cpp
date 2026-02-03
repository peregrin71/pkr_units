#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/electrical/resistance.h>

using namespace ::testing;

class SiResistanceFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiResistanceFormattingTest, ohm_ascii_formatting)
{
    pkr::units::ohm_t<double> ohm{1000.0};
    std::string result = std::format("{}", ohm);
    ASSERT_EQ(result, "1000 ohm");
}

TEST_F(SiResistanceFormattingTest, ohm_ascii_with_precision)
{
    pkr::units::ohm_t<double> ohm{123.456};
    std::string result = std::format("{:.2f}", ohm);
    ASSERT_EQ(result, "123.46 ohm");
}

TEST_F(SiResistanceFormattingTest, kilohm_ascii_formatting)
{
    pkr::units::kiloohm_t<double> kohm{1.5};
    std::string result = std::format("{}", kohm);
    ASSERT_EQ(result, "1.5 kohm");
}

TEST_F(SiResistanceFormattingTest, megohm_ascii_formatting)
{
    pkr::units::megaohm_t<double> Mohm{0.5};
    std::string result = std::format("{}", Mohm);
    ASSERT_EQ(result, "0.5 Mohm");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t
// ============================================================================

TEST_F(SiResistanceFormattingTest, ohm_wide_formatting)
{
    pkr::units::ohm_t<double> ohm{1000.0};
    std::wstring result = std::format(L"{}", ohm);
    std::wstring expected = std::wstring(L"1000 ") + std::wstring(pkr::units::ohm_t<double>::w_symbol);
    ASSERT_EQ(result, expected);
}

TEST_F(SiResistanceFormattingTest, kiloohm_wide_formatting)
{
    pkr::units::kiloohm_t<double> kohm{1.5};
    std::wstring result = std::format(L"{}", kohm);
    std::wstring expected = std::wstring(L"1.5 ") + std::wstring(pkr::units::kiloohm_t<double>::w_symbol);
    ASSERT_EQ(result, expected);
}

TEST_F(SiResistanceFormattingTest, megaohm_wide_formatting)
{
    pkr::units::megaohm_t<double> Mohm{0.5};
    std::wstring result = std::format(L"{}", Mohm);
    std::wstring expected = std::wstring(L"0.5 ") + std::wstring(pkr::units::megaohm_t<double>::w_symbol);
    ASSERT_EQ(result, expected);
}
