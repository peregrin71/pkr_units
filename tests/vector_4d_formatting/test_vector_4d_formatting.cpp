#include <gtest/gtest.h>
#include <format>
#include <pkr_units/units/si.h>
#include <pkr_units/format/vector_unit_4d.h>

using namespace pkr::units;

class Vector4DFormattingTest : public ::testing::Test
{
};

// Test basic vector formatting (homogeneous units)
TEST_F(Vector4DFormattingTest, BasicMetersFormatting)
{
    auto v = vec_4d_units_t<meter_t<double>>{1.5, 2.3, 3.1, 4.2};
    auto formatted = std::format("{}", v);
    EXPECT_EQ(formatted, "[1.5, 2.3, 3.1, 4.2] m");
}

// Test precision formatting forwarded to components
TEST_F(Vector4DFormattingTest, PrecisionFormatting)
{
    auto v = vec_4d_units_t<meter_t<double>>{1.234, 2.567, 3.891, 4.456};
    auto formatted = std::format("{:.2f}", v);
    // Should format each component with .2f precision
    EXPECT_EQ(formatted, "[1.23, 2.57, 3.89, 4.46] m");
}

// Test vector with custom unit type
TEST_F(Vector4DFormattingTest, SecondFormatting)
{
    auto v = vec_4d_units_t<second_t<double>>{0.5, 1.0, 1.5, 2.0};
    auto formatted = std::format("{}", v);
    EXPECT_EQ(formatted, "[0.5, 1, 1.5, 2] s");
}

// Test vector with velocity units
TEST_F(Vector4DFormattingTest, VelocityFormatting)
{
    meter_t<double> distance{10.0};
    second_t<double> time{2.0};
    auto velocity = distance / time;

    auto v = vec_4d_units_t<decltype(velocity)>{velocity, velocity, velocity, velocity};
    auto formatted = std::format("{}", v);
    EXPECT_EQ(formatted, "[5, 5, 5, 5] m/s");
}

// Test precision with various floating point values
TEST_F(Vector4DFormattingTest, PrecisionFormattingVarious)
{
    auto v = vec_4d_units_t<meter_t<double>>{1.0, 2.0, 3.0, 4.0};

    auto formatted_2 = std::format("{:.2f}", v);
    EXPECT_EQ(formatted_2, "[1.00, 2.00, 3.00, 4.00] m");

    auto formatted_1 = std::format("{:.1f}", v);
    EXPECT_EQ(formatted_1, "[1.0, 2.0, 3.0, 4.0] m");
}

// Test with scientific notation
TEST_F(Vector4DFormattingTest, ScientificNotationFormatting)
{
    auto v = vec_4d_units_t<meter_t<double>>{1000.0, 2000.0, 3000.0, 4000.0};
    auto formatted = std::format("{:e}", v);
    // Scientific notation should apply to each component
    EXPECT_EQ(formatted, "[1.000000e+03, 2.000000e+03, 3.000000e+03, 4.000000e+03] m");
}

// Test with small numbers
TEST_F(Vector4DFormattingTest, SmallNumbersFormatting)
{
    auto v = vec_4d_units_t<meter_t<double>>{0.001, 0.002, 0.003, 0.004};
