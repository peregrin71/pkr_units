#include <gtest/gtest.h>
#include <format>
#include <sstream>
#include <pkr_units/units/derived/acceleration.h>

using namespace ::testing;

class AccelerationFormattingTest : public Test
{
};

/*
// ============================================================================
// Basic Formatting Tests - char (ASCII)
// ============================================================================

TEST_F(AccelerationFormattingTest, meter_per_second_squared_ascii_formatting)
{
    pkr::units::meter_per_second_squared_t accel{9.81};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "9.81 m/s^2");
}

TEST_F(AccelerationFormattingTest, meter_per_second_squared_ascii_with_precision)
{
    pkr::units::meter_per_second_squared_t accel{9.80665};
    std::string result = std::format("{:.2f}", accel);
    ASSERT_EQ(result, "9.81 m/s^2");
}

TEST_F(AccelerationFormattingTest, centimeter_per_second_squared_ascii_formatting)
{
    pkr::units::centimeter_per_second_squared_t accel{981.0};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "981 cm/s^2");
}

TEST_F(AccelerationFormattingTest, millimeter_per_second_squared_ascii_formatting)
{
    pkr::units::millimeter_per_second_squared_t accel{9810.0};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "9810 mm/s^2");
}

TEST_F(AccelerationFormattingTest, kilometer_per_second_squared_ascii_formatting)
{
    pkr::units::kilometer_per_second_squared_t accel{0.00981};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "0.00981 km/s^2");
}

TEST_F(AccelerationFormattingTest, standard_gravity_ascii_formatting)
{
    pkr::units::standard_gravity_t accel{1.0};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "1 g");
}

TEST_F(AccelerationFormattingTest, standard_gravity_with_precision)
{
    pkr::units::standard_gravity_t accel{2.5};
    std::string result = std::format("{:.1f}", accel);
    ASSERT_EQ(result, "2.5 g");
}

// ============================================================================
// Wide Character Formatting Tests
// ============================================================================

TEST_F(AccelerationFormattingTest, meter_per_second_squared_wide_formatting)
{
    pkr::units::meter_per_second_squared_t accel{9.81};
    std::wstring result = std::format(L"{}", accel);
    ASSERT_EQ(result, L"9.81 m/s²");
}

TEST_F(AccelerationFormattingTest, standard_gravity_wide_formatting)
{
    pkr::units::standard_gravity_t accel{1.0};
    std::wstring result = std::format(L"{}", accel);
    ASSERT_EQ(result, L"1 g");
}

// ============================================================================
// Edge Cases and Special Values
// ============================================================================

TEST_F(AccelerationFormattingTest, zero_acceleration_formatting)
{
    pkr::units::meter_per_second_squared_t accel{0.0};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "0 m/s^2");
}

TEST_F(AccelerationFormattingTest, negative_acceleration_formatting)
{
    pkr::units::meter_per_second_squared_t accel{-9.81};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "-9.81 m/s^2");
}

TEST_F(AccelerationFormattingTest, very_small_acceleration)
{
    pkr::units::meter_per_second_squared_t accel{1e-6};
    std::string result = std::format("{:.2e}", accel);
    ASSERT_EQ(result, "1.00e-06 m/s^2");
}

TEST_F(AccelerationFormattingTest, very_large_acceleration)
{
    pkr::units::meter_per_second_squared_t accel{1e6};
    std::string result = std::format("{:.1e}", accel);
    ASSERT_EQ(result, "1.0e+06 m/s^2");
}

TEST_F(AccelerationFormattingTest, default_precision)
{
    pkr::units::meter_per_second_squared_t accel{3.141592653589793};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "3.14159 m/s^2");
}

TEST_F(AccelerationFormattingTest, value_preservation)
{
    pkr::units::meter_per_second_squared_t accel{123.456};
    std::string result = std::format("{}", accel);
    ASSERT_EQ(result, "123.456 m/s^2");
}
*/
