#include <gtest/gtest.h>
#include <format>
#include <pkr_units/si.h>
#include <pkr_units/si_formatting.h>

using namespace pkr::units;

// Test basic length unit formatting
TEST(FormattingTest, BasicLengthUnit)
{
    meter_t length{5.0};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "5 m");
}

// Test derived unit (velocity) formatting
TEST(FormattingTest, VelocityDerivedUnit)
{
    meter_t distance{10.0};
    second_t time{2.0};
    auto velocity = distance / time;
    auto formatted = std::format("{}", velocity);
    EXPECT_EQ(formatted, "5 m·s-1");
}

// Test precision control with format
TEST(FormattingTest, PrecisionControl)
{
    meter_t length{5.123456};
    auto formatted = std::format("{:.2}", length);
    EXPECT_EQ(formatted, "5.12 m");
}

// Test dimensionless quantity formatting
TEST(FormattingTest, DimensionlessQuantity)
{
    kilogram_t mass1{10.0};
    kilogram_t mass2{2.0};
    auto dimensionless = mass1 / mass2;
    auto formatted = std::format("{}", dimensionless);
    EXPECT_EQ(formatted, "5 1");
}

// Test complex derived unit (Force: kg·m·s⁻²)
TEST(FormattingTest, ComplexDerivedUnit)
{
    kilogram_t mass{5.0};
    meter_t distance{2.0};
    second_t time{1.0};
    
    auto force = mass * distance / (time * time);
    auto formatted = std::format("{}", force);
    EXPECT_EQ(formatted, "10 kg·m·s-2");
}

// Test different scales of same unit
TEST(FormattingTest, DifferentUnitScales)
{
    kilometer_t distance{100.0};
    auto formatted = std::format("{}", distance);
    EXPECT_EQ(formatted, "100 km");
}

// Test mass unit formatting
TEST(FormattingTest, MassUnit)
{
    kilogram_t mass{10.0};
    auto formatted = std::format("{}", mass);
    EXPECT_EQ(formatted, "10 kg");
}

// Test time unit formatting
TEST(FormattingTest, TimeUnit)
{
    second_t duration{30.0};
    auto formatted = std::format("{}", duration);
    EXPECT_EQ(formatted, "30 s");
}

// Test current unit formatting
TEST(FormattingTest, CurrentUnit)
{
    ampere_t current{2.5};
    auto formatted = std::format("{}", current);
    EXPECT_EQ(formatted, "2.5 A");
}

// Test temperature unit formatting
TEST(FormattingTest, TemperatureUnit)
{
    kelvin_t temperature{273.15};
    auto formatted = std::format("{}", temperature);
    EXPECT_EQ(formatted, "273.15 K");
}

// Test format with default precision
TEST(FormattingTest, DefaultPrecision)
{
    meter_t length{3.141592653589793};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "3.14159 m");
}

// Test that formatting doesn't lose precision in the value
TEST(FormattingTest, ValuePreservation)
{
    meter_t length{123.456};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "123.456 m");
}


