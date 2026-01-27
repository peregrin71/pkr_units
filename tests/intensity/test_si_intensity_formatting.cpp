#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/intensity.h>

using namespace ::testing;

class SiIntensityFormattingTest : public Test
{
};

// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiIntensityFormattingTest, candela_ascii_formatting)
{
    pkr::units::candela_t cd{5.0};
    std::string result = std::format("{}", cd);
    ASSERT_EQ(result, "5 cd");
}

TEST_F(SiIntensityFormattingTest, candela_ascii_with_precision)
{
    pkr::units::candela_t cd{2.5};
    std::string result = std::format("{:.2f}", cd);
    ASSERT_EQ(result, "2.50 cd");
}

TEST_F(SiIntensityFormattingTest, millicandela_ascii_formatting)
{
    pkr::units::millicandela_t mcd{1500.0};
    std::string result = std::format("{}", mcd);
    ASSERT_EQ(result, "1500 mcd");
}

TEST_F(SiIntensityFormattingTest, microcandela_ascii_formatting)
{
    pkr::units::microcandela_t ucd{0.5};
    std::string result = std::format("{}", ucd);
    ASSERT_EQ(result, "0.5 ucd"); // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiIntensityFormattingTest, nanocandela_ascii_formatting)
{
    pkr::units::nanocandela_t ncd{100.0};
    std::string result = std::format("{}", ncd);
    ASSERT_EQ(result, "100 ncd");
}

TEST_F(SiIntensityFormattingTest, kilocandela_ascii_formatting)
{
    pkr::units::kilocandela_t kcd{2.5};
    std::string result = std::format("{}", kcd);
    ASSERT_EQ(result, "2.5 kcd");
}