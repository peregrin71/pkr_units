#include <gtest/gtest.h>
#include <format>
#include <pkr_units/si.h>
#include <pkr_units/si_formatting.h>

// Test basic length unit formatting
TEST(FormattingTest, BasicLengthUnit)
{
    pkr::units::meter_t length{5.0};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "5 m");
}

// Test derived unit (velocity) formatting
TEST(FormattingTest, VelocityDerivedUnit)
{
    pkr::units::meter_t distance{10.0};
    pkr::units::second_t time{2.0};
    auto velocity = distance / time;
    auto formatted = std::format("{}", velocity);
    EXPECT_EQ(formatted, "5 m·s-1");
}

// Test precision control with format
TEST(FormattingTest, PrecisionControl)
{
    pkr::units::meter_t length{5.123456};
    auto formatted = std::format("{:.2}", length);
    EXPECT_EQ(formatted, "5.12 m");
}

// Test dimensionless quantity formatting
TEST(FormattingTest, DimensionlessQuantity)
{
    pkr::units::kilogram_t mass1{10.0};
    pkr::units::kilogram_t mass2{2.0};
    auto dimensionless = mass1 / mass2;
    auto formatted = std::format("{}", dimensionless);
    EXPECT_EQ(formatted, "5 1");
}

// Test complex derived unit (Force: kg·m·s⁻²)
TEST(FormattingTest, ComplexDerivedUnit)
{
    pkr::units::kilogram_t mass{5.0};
    pkr::units::meter_t distance{2.0};
    pkr::units::second_t time{1.0};

    auto force = mass * distance / (time * time);
    auto formatted = std::format("{}", force);
    EXPECT_EQ(formatted, "10 kg·m·s-2");
}

// Test different scales of same unit
TEST(FormattingTest, DifferentUnitScales)
{
    pkr::units::kilometer_t distance{100.0};
    auto formatted = std::format("{}", distance);
    EXPECT_EQ(formatted, "100 km");
}

// Test mass unit formatting
TEST(FormattingTest, MassUnit)
{
    pkr::units::kilogram_t mass{10.0};
    auto formatted = std::format("{}", mass);
    EXPECT_EQ(formatted, "10 kg");
}

// Test time unit formatting
TEST(FormattingTest, TimeUnit)
{
    pkr::units::second_t duration{30.0};
    auto formatted = std::format("{}", duration);
    EXPECT_EQ(formatted, "30 s");
}

// Test current unit formatting
TEST(FormattingTest, CurrentUnit)
{
    pkr::units::ampere_t current{2.5};
    auto formatted = std::format("{}", current);
    EXPECT_EQ(formatted, "2.5 A");
}

// Test temperature unit formatting
TEST(FormattingTest, TemperatureUnit)
{
    pkr::units::kelvin_t temperature{273.15};
    auto formatted = std::format("{}", temperature);
    EXPECT_EQ(formatted, "273.15 K");
}

// Test format with default precision
TEST(FormattingTest, DefaultPrecision)
{
    pkr::units::meter_t length{3.141592653589793};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "3.14159 m");
}

// Test that formatting doesn't lose precision in the value
TEST(FormattingTest, ValuePreservation)
{
    pkr::units::meter_t length{123.456};
    auto formatted = std::format("{}", length);
    EXPECT_EQ(formatted, "123.456 m");
}
