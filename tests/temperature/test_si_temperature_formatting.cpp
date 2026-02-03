#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/temperature.h>

using namespace ::testing;

class SiTemperatureFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiTemperatureFormattingTest, kelvin_ascii_formatting)
{
    pkr::units::kelvin_t<double> K{300.0};
    std::string result = std::format("{}", K);
    ASSERT_EQ(result, "300 K");
}

TEST_F(SiTemperatureFormattingTest, kelvin_ascii_with_precision)
{
    pkr::units::kelvin_t<double> K{273.15};
    std::string result = std::format("{:.2f}", K);
    ASSERT_EQ(result, "273.15 K");
}

TEST_F(SiTemperatureFormattingTest, millikelvin_ascii_formatting)
{
    pkr::units::millikelvin_t<double> mK{1500.0};
    std::string result = std::format("{}", mK);
    ASSERT_EQ(result, "1500 mK");
}

TEST_F(SiTemperatureFormattingTest, microkelvin_ascii_formatting)
{
    pkr::units::microkelvin_t<double> uK{0.5};
    std::string result = std::format("{}", uK);
    ASSERT_EQ(result, "0.5 uK"); // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiTemperatureFormattingTest, nanokelvin_ascii_formatting)
{
    pkr::units::nanokelvin_t<double> nK{100.0};
    std::string result = std::format("{}", nK);
    ASSERT_EQ(result, "100 nK");
}

TEST_F(SiTemperatureFormattingTest, kilokelvin_ascii_formatting)
{
    pkr::units::kilokelvin_t<double> kK{2.5};
    std::string result = std::format("{}", kK);
    ASSERT_EQ(result, "2.5 kK");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t
// ============================================================================

TEST_F(SiTemperatureFormattingTest, kelvin_wide_formatting)
{
    pkr::units::kelvin_t<double> K{300.0};
    std::wstring result = std::format(L"{}", K);
    std::wstring expected = std::wstring(L"300 ") + std::wstring(pkr::units::kelvin_t<double>::w_symbol);
    ASSERT_EQ(result, expected);
}

TEST_F(SiTemperatureFormattingTest, microkelvin_wide_formatting)
{
    pkr::units::microkelvin_t<double> uK{0.5};
    std::wstring result = std::format(L"{}", uK);
    std::wstring expected = std::wstring(L"0.5 ") + std::wstring(pkr::units::microkelvin_t<double>::w_symbol);
    ASSERT_EQ(result, expected);
}
