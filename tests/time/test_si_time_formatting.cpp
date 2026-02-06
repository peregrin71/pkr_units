#include <gtest/gtest.h>
#include <pkr_units/format/si.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/time.h>

using namespace ::testing;

class SiTimeFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII) - double
// ============================================================================

TEST_F(SiTimeFormattingTest, second_ascii_formatting_double)
{
    pkr::units::second_t<double> s{5.0};
    std::string result = std::format("{}", s);
    ASSERT_EQ(result, "5 s");
}

TEST_F(SiTimeFormattingTest, second_ascii_formatting_float)
{
    pkr::units::second_t<float> s{5.0f};
    std::string result = std::format("{}", s);
    ASSERT_EQ(result, "5 s");
}

TEST_F(SiTimeFormattingTest, second_ascii_precision_double)
{
    pkr::units::second_t<double> s{5.123456};
    std::string result = std::format("{:.2f}", s);
    ASSERT_EQ(result, "5.12 s");
}

TEST_F(SiTimeFormattingTest, second_ascii_precision_float)
{
    pkr::units::second_t<float> s{5.123456f};
    std::string result = std::format("{:.2f}", s);
    ASSERT_EQ(result, "5.12 s");
}

TEST_F(SiTimeFormattingTest, millisecond_ascii_formatting_double)
{
    pkr::units::millisecond_t<double> ms{1500.0};
    std::string result = std::format("{}", ms);
    ASSERT_EQ(result, "1500 ms");
}

TEST_F(SiTimeFormattingTest, millisecond_ascii_formatting_float)
{
    pkr::units::millisecond_t<float> ms{1500.0f};
    std::string result = std::format("{}", ms);
    ASSERT_EQ(result, "1500 ms");
}

TEST_F(SiTimeFormattingTest, microsecond_ascii_formatting_double)
{
    pkr::units::microsecond_t<double> us{0.5};
    std::string result = std::format("{}", us);
    ASSERT_EQ(result, "0.5 us");
}

TEST_F(SiTimeFormattingTest, microsecond_ascii_formatting_float)
{
    pkr::units::microsecond_t<float> us{0.5f};
    std::string result = std::format("{}", us);
    ASSERT_EQ(result, "0.5 us");
}

TEST_F(SiTimeFormattingTest, nanosecond_ascii_formatting_double)
{
    pkr::units::nanosecond_t<double> ns{100.0};
    std::string result = std::format("{}", ns);
    ASSERT_EQ(result, "100 ns");
}

TEST_F(SiTimeFormattingTest, nanosecond_ascii_formatting_float)
{
    pkr::units::nanosecond_t<float> ns{100.0f};
    std::string result = std::format("{}", ns);
    ASSERT_EQ(result, "100 ns");
}

TEST_F(SiTimeFormattingTest, kilosecond_ascii_formatting_double)
{
    pkr::units::kilosecond_t<double> ks{2.5};
    std::string result = std::format("{}", ks);
    ASSERT_EQ(result, "2.5 ks");
}

TEST_F(SiTimeFormattingTest, kilosecond_ascii_formatting_float)
{
    pkr::units::kilosecond_t<float> ks{2.5f};
    std::string result = std::format("{}", ks);
    ASSERT_EQ(result, "2.5 ks");
}

// ============================================================================
// Wide Character Formatting Tests - wchar_t - double
// ============================================================================

TEST_F(SiTimeFormattingTest, second_wide_formatting_double)
{
    pkr::units::second_t<double> s{5.0};
    std::wstring result = std::format(L"{}", s);
    ASSERT_EQ(result, L"5 s");
}

TEST_F(SiTimeFormattingTest, second_wide_formatting_float)
{
    pkr::units::second_t<float> s{5.0f};
    std::wstring result = std::format(L"{}", s);
    ASSERT_EQ(result, L"5 s");
}

TEST_F(SiTimeFormattingTest, second_wide_precision_double)
{
    pkr::units::second_t<double> s{5.123456};
    std::wstring result = std::format(L"{:.2f}", s);
    ASSERT_EQ(result, L"5.12 s");
}

TEST_F(SiTimeFormattingTest, second_wide_precision_float)
{
    pkr::units::second_t<float> s{5.123456f};
    std::wstring result = std::format(L"{:.2f}", s);
    ASSERT_EQ(result, L"5.12 s");
}

TEST_F(SiTimeFormattingTest, millisecond_wide_formatting_double)
{
    pkr::units::millisecond_t<double> ms{1500.0};
    std::wstring result = std::format(L"{}", ms);
    ASSERT_EQ(result, L"1500 ms");
}

TEST_F(SiTimeFormattingTest, millisecond_wide_formatting_float)
{
    pkr::units::millisecond_t<float> ms{1500.0f};
    std::wstring result = std::format(L"{}", ms);
    ASSERT_EQ(result, L"1500 ms");
}

TEST_F(SiTimeFormattingTest, microsecond_wide_formatting_double)
{
    pkr::units::microsecond_t<double> us{0.5};
    std::wstring result = std::format(L"{}", us);
    ASSERT_EQ(result, L"0.5 \u00b5s");
}

TEST_F(SiTimeFormattingTest, microsecond_wide_formatting_float)
{
    pkr::units::microsecond_t<float> us{0.5f};
    std::wstring result = std::format(L"{}", us);
    ASSERT_EQ(result, L"0.5 \u00b5s");
}

TEST_F(SiTimeFormattingTest, nanosecond_wide_formatting_double)
{
    pkr::units::nanosecond_t<double> ns{100.0};
    std::wstring result = std::format(L"{}", ns);
    ASSERT_EQ(result, L"100 ns");
}

TEST_F(SiTimeFormattingTest, nanosecond_wide_formatting_float)
{
    pkr::units::nanosecond_t<float> ns{100.0f};
    std::wstring result = std::format(L"{}", ns);
    ASSERT_EQ(result, L"100 ns");
}

TEST_F(SiTimeFormattingTest, kilosecond_wide_formatting_double)
{
    pkr::units::kilosecond_t<double> ks{2.5};
    std::wstring result = std::format(L"{}", ks);
    ASSERT_EQ(result, L"2.5 ks");
}

TEST_F(SiTimeFormattingTest, kilosecond_wide_formatting_float)
{
    pkr::units::kilosecond_t<float> ks{2.5f};
    std::wstring result = std::format(L"{}", ks);
    ASSERT_EQ(result, L"2.5 ks");
}
