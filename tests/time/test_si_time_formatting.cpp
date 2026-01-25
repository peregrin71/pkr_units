#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/time.h>

using namespace ::testing;

class SiTimeFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiTimeFormattingTest, second_ascii_formatting)
{
    pkr::units::second_t s{5.0};
    std::string result = std::format("{}", s);
    ASSERT_EQ(result, "5 s");
}

TEST_F(SiTimeFormattingTest, second_ascii_with_precision)
{
    pkr::units::second_t s{5.123456};
    std::string result = std::format("{:.2f}", s);
    ASSERT_EQ(result, "5.12 s");
}

TEST_F(SiTimeFormattingTest, millisecond_ascii_formatting)
{
    pkr::units::millisecond_t ms{1500.0};
    std::string result = std::format("{}", ms);
    ASSERT_EQ(result, "1500 ms");
}

TEST_F(SiTimeFormattingTest, microsecond_ascii_formatting)
{
    pkr::units::microsecond_t us{0.5};
    std::string result = std::format("{}", us);
    ASSERT_EQ(result, "0.5 us");  // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiTimeFormattingTest, nanosecond_ascii_formatting)
{
    pkr::units::nanosecond_t ns{100.0};
    std::string result = std::format("{}", ns);
    ASSERT_EQ(result, "100 ns");
}

TEST_F(SiTimeFormattingTest, kilosecond_ascii_formatting)
{
    pkr::units::kilosecond_t ks{2.5};
    std::string result = std::format("{}", ks);
    ASSERT_EQ(result, "2.5 ks");
}