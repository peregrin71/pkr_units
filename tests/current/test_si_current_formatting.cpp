#include <gtest/gtest.h>
#include <pkr_units/si_units_formatting.h>
#include <format>
#include <sstream>
#include <pkr_units/units/base/current.h>

using namespace ::testing;

class SiCurrentFormattingTest : public Test
{
};

/*
// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(SiCurrentFormattingTest, ampere_ascii_formatting)
{
    pkr::units::ampere_t A{5.0};
    std::string result = std::format("{}", A);
    ASSERT_EQ(result, "5 A");
}

TEST_F(SiCurrentFormattingTest, ampere_ascii_with_precision)
{
    pkr::units::ampere_t A{5.123456};
    std::string result = std::format("{:.2f}", A);
    ASSERT_EQ(result, "5.12 A");
}

TEST_F(SiCurrentFormattingTest, milliampere_ascii_formatting)
{
    pkr::units::milliampere_t mA{1500.0};
    std::string result = std::format("{}", mA);
    ASSERT_EQ(result, "1500 mA");
}

TEST_F(SiCurrentFormattingTest, microampere_ascii_formatting)
{
    pkr::units::microampere_t uA{0.5};
    std::string result = std::format("{}", uA);
    ASSERT_EQ(result, "0.5 uA"); // ASCII fallback: "u" instead of "μ"
}

TEST_F(SiCurrentFormattingTest, nanoampere_ascii_formatting)
{
    pkr::units::nanoampere_t nA{100.0};
    std::string result = std::format("{}", nA);
    ASSERT_EQ(result, "100 nA");
}

TEST_F(SiCurrentFormattingTest, kiloampere_ascii_formatting)
{
    pkr::units::kiloampere_t kA{2.5};
    std::string result = std::format("{}", kA);
    ASSERT_EQ(result, "2.5 kA");
}
*/
