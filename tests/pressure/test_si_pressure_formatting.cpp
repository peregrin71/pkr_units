#include <gtest/gtest.h>
#include <pkr_units/format/si.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/mechanical/pressure.h>

using namespace ::testing;

class SiPressureFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII) - double
// ============================================================================

TEST_F(SiPressureFormattingTest, pascal_ascii_formatting_double)
{
    pkr::units::pascal_t<double> Pa{101325.0};
    std::string result = std::format("{}", Pa);
    ASSERT_EQ(result, "101325 Pa");
}

TEST_F(SiPressureFormattingTest, pascal_ascii_formatting_float)
{
    pkr::units::pascal_t<float> Pa{101325.0f};
    std::string result = std::format("{}", Pa);
    ASSERT_EQ(result, "101325 Pa");
}

TEST_F(SiPressureFormattingTest, pascal_ascii_precision_double)
{
    pkr::units::pascal_t<double> Pa{1013.25789};
    std::string result = std::format("{:.2f}", Pa);
    ASSERT_EQ(result, "1013.26 Pa");
}

TEST_F(SiPressureFormattingTest, pascal_ascii_precision_float)
{
    pkr::units::pascal_t<float> Pa{1013.25789f};
    std::string result = std::format("{:.2f}", Pa);
    ASSERT_EQ(result, "1013.26 Pa");
}

TEST_F(SiPressureFormattingTest, hectopascal_ascii_formatting_double)
{
    pkr::units::hectopascal_t<double> hPa{1013.0};
    std::string result = std::format("{}", hPa);
    ASSERT_EQ(result, "1013 hPa");
}

TEST_F(SiPressureFormattingTest, hectopascal_ascii_formatting_float)
{
    pkr::units::hectopascal_t<float> hPa{1013.0f};
    std::string result = std::format("{}", hPa);
    ASSERT_EQ(result, "1013 hPa");
}

TEST_F(SiPressureFormattingTest, kilopascal_ascii_formatting_double)
{
    pkr::units::kilopascal_t<double> kPa{101.325};
    std::string result = std::format("{}", kPa);
    ASSERT_EQ(result, "101.325 kPa");
}

TEST_F(SiPressureFormattingTest, kilopascal_ascii_formatting_float)
{
    pkr::units::kilopascal_t<float> kPa{101.325f};
    std::string result = std::format("{}", kPa);
    ASSERT_EQ(result, "101.325 kPa");
}

TEST_F(SiPressureFormattingTest, megapascal_ascii_formatting_double)
{
    pkr::units::megapascal_t<double> MPa{0.101325};
    std::string result = std::format("{}", MPa);
    ASSERT_EQ(result, "0.101325 MPa");
}

TEST_F(SiPressureFormattingTest, megapascal_ascii_formatting_float)
{
    pkr::units::megapascal_t<float> MPa{0.101325f};
    std::string result = std::format("{}", MPa);
    ASSERT_EQ(result, "0.101325 MPa");
}

TEST_F(SiPressureFormattingTest, micropascal_ascii_formatting_double)
{
    pkr::units::micropascal_t<double> uPa{1000000.0};
    std::string result = std::format("{}", uPa);
    ASSERT_EQ(result, "1e+06 uPa");
}

TEST_F(SiPressureFormattingTest, micropascal_ascii_formatting_float)
{
    pkr::units::micropascal_t<float> uPa{1000000.0f};
    std::string result = std::format("{}", uPa);
    ASSERT_EQ(result, "1e+06 uPa");
}

TEST_F(SiPressureFormattingTest, millipascal_ascii_formatting_double)
{
    pkr::units::millipascal_t<double> mPa{500000.0};
    std::string result = std::format("{}", mPa);
    std::string expected = std::format("{}", 500000.0) + " mPa"; // To avoid hardcoding the formatting of the number
    ASSERT_EQ(result, expected);
}

TEST_F(SiPressureFormattingTest, millipascal_ascii_formatting_float)
{
    pkr::units::millipascal_t<float> mPa{500000.0f};
    std::string result = std::format("{}", mPa);
    std::string expected = std::format("{}", 500000.0f) + " mPa";
    ASSERT_EQ(result, expected);
}

TEST_F(SiPressureFormattingTest, bar_ascii_formatting_double)
{
    pkr::units::bar_t<double> bar{1.0};
    std::string result = std::format("{}", bar);
    ASSERT_EQ(result, "1 bar");
}

TEST_F(SiPressureFormattingTest, bar_ascii_formatting_float)
{
    pkr::units::bar_t<float> bar{1.0f};
    std::string result = std::format("{}", bar);
    ASSERT_EQ(result, "1 bar");
}

TEST_F(SiPressureFormattingTest, atmosphere_ascii_formatting_double)
{
    pkr::units::atmosphere_t<double> atm{1.0};
    std::string result = std::format("{}", atm);
    ASSERT_EQ(result, "1 atm");
}

TEST_F(SiPressureFormattingTest, atmosphere_ascii_formatting_float)
{
    pkr::units::atmosphere_t<float> atm{1.0f};
    std::string result = std::format("{}", atm);
    ASSERT_EQ(result, "1 atm");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t - double
// ============================================================================

TEST_F(SiPressureFormattingTest, pascal_wide_formatting_double)
{
    pkr::units::pascal_t<double> Pa{101325.0};
    std::wstring result = std::format(L"{}", Pa);
    ASSERT_EQ(result, L"101325 Pa");
}

TEST_F(SiPressureFormattingTest, pascal_wide_formatting_float)
{
    pkr::units::pascal_t<float> Pa{101325.0f};
    std::wstring result = std::format(L"{}", Pa);
    ASSERT_EQ(result, L"101325 Pa");
}

TEST_F(SiPressureFormattingTest, pascal_wide_precision_double)
{
    pkr::units::pascal_t<double> Pa{1013.25789};
    std::wstring result = std::format(L"{:.2f}", Pa);
    ASSERT_EQ(result, L"1013.26 Pa");
}

TEST_F(SiPressureFormattingTest, pascal_wide_precision_float)
{
    pkr::units::pascal_t<float> Pa{1013.25789f};
    std::wstring result = std::format(L"{:.2f}", Pa);
    ASSERT_EQ(result, L"1013.26 Pa");
}

TEST_F(SiPressureFormattingTest, hectopascal_wide_formatting_double)
{
    pkr::units::hectopascal_t<double> hPa{1013.0};
    std::wstring result = std::format(L"{}", hPa);
    ASSERT_EQ(result, L"1013 hPa");
}

TEST_F(SiPressureFormattingTest, hectopascal_wide_formatting_float)
{
    pkr::units::hectopascal_t<float> hPa{1013.0f};
    std::wstring result = std::format(L"{}", hPa);
    ASSERT_EQ(result, L"1013 hPa");
}

TEST_F(SiPressureFormattingTest, kilopascal_wide_formatting_double)
{
    pkr::units::kilopascal_t<double> kPa{101.325};
    std::wstring result = std::format(L"{}", kPa);
    ASSERT_EQ(result, L"101.325 kPa");
}

TEST_F(SiPressureFormattingTest, kilopascal_wide_formatting_float)
{
    pkr::units::kilopascal_t<float> kPa{101.325f};
    std::wstring result = std::format(L"{}", kPa);
    ASSERT_EQ(result, L"101.325 kPa");
}

TEST_F(SiPressureFormattingTest, megapascal_wide_formatting_double)
{
    pkr::units::megapascal_t<double> MPa{0.101325};
    std::wstring result = std::format(L"{}", MPa);
    ASSERT_EQ(result, L"0.101325 MPa");
}

TEST_F(SiPressureFormattingTest, megapascal_wide_formatting_float)
{
    pkr::units::megapascal_t<float> MPa{0.101325f};
    std::wstring result = std::format(L"{}", MPa);
    ASSERT_EQ(result, L"0.101325 MPa");
}

TEST_F(SiPressureFormattingTest, micropascal_wide_formatting_double)
{
    pkr::units::micropascal_t<double> uPa{1000000.0};
    std::wstring result = std::format(L"{}", uPa);
    ASSERT_EQ(result, L"1e+06 \u00b5Pa");
}

TEST_F(SiPressureFormattingTest, micropascal_wide_formatting_float)
{
    pkr::units::micropascal_t<float> uPa{1000000.0f};
    std::wstring result = std::format(L"{}", uPa);
    ASSERT_EQ(result, L"1e+06 \u00b5Pa");
}

TEST_F(SiPressureFormattingTest, millipascal_wide_formatting_double)
{
    pkr::units::millipascal_t<double> mPa{500000.0};
    std::wstring result = std::format(L"{}", mPa);
    std::wstring expected = std::format(L"{}", 500000.0) + L" mPa";
    ASSERT_EQ(result, expected);
}

TEST_F(SiPressureFormattingTest, millipascal_wide_formatting_float)
{
    pkr::units::millipascal_t<float> mPa{500000.0f};
    std::wstring result = std::format(L"{}", mPa);
    std::wstring expected = std::format(L"{}", 500000.0f) + L" mPa";
    ASSERT_EQ(result, expected);
}

TEST_F(SiPressureFormattingTest, bar_wide_formatting_double)
{
    pkr::units::bar_t<double> bar{1.0};
    std::wstring result = std::format(L"{}", bar);
    ASSERT_EQ(result, L"1 bar");
}

TEST_F(SiPressureFormattingTest, bar_wide_formatting_float)
{
    pkr::units::bar_t<float> bar{1.0f};
    std::wstring result = std::format(L"{}", bar);
    ASSERT_EQ(result, L"1 bar");
}

TEST_F(SiPressureFormattingTest, atmosphere_wide_formatting_double)
{
    pkr::units::atmosphere_t<double> atm{1.0};
    std::wstring result = std::format(L"{}", atm);
    ASSERT_EQ(result, L"1 atm");
}

TEST_F(SiPressureFormattingTest, atmosphere_wide_formatting_float)
{
    pkr::units::atmosphere_t<float> atm{1.0f};
    std::wstring result = std::format(L"{}", atm);
    ASSERT_EQ(result, L"1 atm");
}
