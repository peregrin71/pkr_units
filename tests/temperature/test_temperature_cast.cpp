//
// Test temperature conversions
// Tests unit_cast specializations for temperature scales

#include <gtest/gtest.h>

#include <pkr_units/units/base/temperature.h>
#include <pkr_units/units/temperature/celsius.h>
#include <pkr_units/units/temperature/fahrenheit.h>
#include <pkr_units/units/temperature/temperature_cast.h>
#include <pkr_units/impl/cast/unit_cast.h>

namespace test
{

using namespace ::testing;

class TemperatureCastTest : public Test
{
};

// Test Celsius to Kelvin conversions
TEST_F(TemperatureCastTest, CelsiusToKelvin)
{
    pkr::units::celsius_t c{20.0};
    pkr::units::kelvin_t k = pkr::units::unit_cast<pkr::units::kelvin_t>(c);
    EXPECT_DOUBLE_EQ(k.value(), 293.15);
}

TEST_F(TemperatureCastTest, CelsiusZeroToKelvin)
{
    pkr::units::celsius_t c{0.0};
    pkr::units::kelvin_t k = pkr::units::unit_cast<pkr::units::kelvin_t>(c);
    EXPECT_DOUBLE_EQ(k.value(), 273.15);
}

TEST_F(TemperatureCastTest, CelsiusNegativeToKelvin)
{
    pkr::units::celsius_t c{-10.0};
    pkr::units::kelvin_t k = pkr::units::unit_cast<pkr::units::kelvin_t>(c);
    EXPECT_DOUBLE_EQ(k.value(), 263.15);
}

// Test Kelvin to Celsius conversions
TEST_F(TemperatureCastTest, KelvinToCelsius)
{
    pkr::units::kelvin_t k{293.15};
    pkr::units::celsius_t c = pkr::units::unit_cast<pkr::units::celsius_t>(k);
    EXPECT_DOUBLE_EQ(c.value(), 20.0);
}

TEST_F(TemperatureCastTest, KelvinZeroToCelsius)
{
    pkr::units::kelvin_t k{273.15};
    pkr::units::celsius_t c = pkr::units::unit_cast<pkr::units::celsius_t>(k);
    EXPECT_DOUBLE_EQ(c.value(), 0.0);
}

TEST_F(TemperatureCastTest, KelvinAbsoluteZero)
{
    pkr::units::kelvin_t k{0.0};
    pkr::units::celsius_t c = pkr::units::unit_cast<pkr::units::celsius_t>(k);
    EXPECT_DOUBLE_EQ(c.value(), -273.15);
}

// Test Fahrenheit to Celsius conversions
TEST_F(TemperatureCastTest, FahrenheitToCelsius)
{
    pkr::units::fahrenheit_t f{32.0};
    pkr::units::celsius_t c = pkr::units::unit_cast<pkr::units::celsius_t>(f);
    EXPECT_DOUBLE_EQ(c.value(), 0.0);
}

TEST_F(TemperatureCastTest, FahrenheitToCelsius212)
{
    pkr::units::fahrenheit_t f{212.0};
    pkr::units::celsius_t c = pkr::units::unit_cast<pkr::units::celsius_t>(f);
    EXPECT_DOUBLE_EQ(c.value(), 100.0);
}

TEST_F(TemperatureCastTest, FahrenheitToCelsius98_6)
{
    pkr::units::fahrenheit_t f{98.6};
    pkr::units::celsius_t c = pkr::units::unit_cast<pkr::units::celsius_t>(f);
    EXPECT_NEAR(c.value(), 37.0, 1e-10);
}

// Test Celsius to Fahrenheit conversions
TEST_F(TemperatureCastTest, CelsiusToFahrenheit)
{
    pkr::units::celsius_t c{0.0};
    pkr::units::fahrenheit_t f = pkr::units::unit_cast<pkr::units::fahrenheit_t>(c);
    EXPECT_DOUBLE_EQ(f.value(), 32.0);
}

TEST_F(TemperatureCastTest, CelsiusToFahrenheit100)
{
    pkr::units::celsius_t c{100.0};
    pkr::units::fahrenheit_t f = pkr::units::unit_cast<pkr::units::fahrenheit_t>(c);
    EXPECT_DOUBLE_EQ(f.value(), 212.0);
}

TEST_F(TemperatureCastTest, CelsiusToFahrenheit37)
{
    pkr::units::celsius_t c{37.0};
    pkr::units::fahrenheit_t f = pkr::units::unit_cast<pkr::units::fahrenheit_t>(c);
    EXPECT_NEAR(f.value(), 98.6, 1e-10);
}

// Test Fahrenheit to Kelvin conversions
TEST_F(TemperatureCastTest, FahrenheitToKelvin)
{
    pkr::units::fahrenheit_t f{32.0};
    pkr::units::kelvin_t k = pkr::units::unit_cast<pkr::units::kelvin_t>(f);
    EXPECT_DOUBLE_EQ(k.value(), 273.15);
}

TEST_F(TemperatureCastTest, FahrenheitToKelvin212)
{
    pkr::units::fahrenheit_t f{212.0};
    pkr::units::kelvin_t k = pkr::units::unit_cast<pkr::units::kelvin_t>(f);
    EXPECT_DOUBLE_EQ(k.value(), 373.15);
}

// Test Kelvin to Fahrenheit conversions
TEST_F(TemperatureCastTest, KelvinToFahrenheit)
{
    pkr::units::kelvin_t k{273.15};
    pkr::units::fahrenheit_t f = pkr::units::unit_cast<pkr::units::fahrenheit_t>(k);
    EXPECT_DOUBLE_EQ(f.value(), 32.0);
}

TEST_F(TemperatureCastTest, KelvinToFahrenheit373_15)
{
    pkr::units::kelvin_t k{373.15};
    pkr::units::fahrenheit_t f = pkr::units::unit_cast<pkr::units::fahrenheit_t>(k);
    EXPECT_DOUBLE_EQ(f.value(), 212.0);
}

// Test round-trip conversions
TEST_F(TemperatureCastTest, RoundTripCelsiusKelvin)
{
    pkr::units::celsius_t original{25.5};
    pkr::units::kelvin_t k = pkr::units::unit_cast<pkr::units::kelvin_t>(original);
    pkr::units::celsius_t back = pkr::units::unit_cast<pkr::units::celsius_t>(k);
    EXPECT_DOUBLE_EQ(back.value(), original.value());
}

TEST_F(TemperatureCastTest, RoundTripFahrenheitCelsius)
{
    pkr::units::fahrenheit_t original{77.0};
    pkr::units::celsius_t c = pkr::units::unit_cast<pkr::units::celsius_t>(original);
    pkr::units::fahrenheit_t back = pkr::units::unit_cast<pkr::units::fahrenheit_t>(c);
    EXPECT_DOUBLE_EQ(back.value(), original.value());
}

TEST_F(TemperatureCastTest, RoundTripKelvinFahrenheit)
{
    pkr::units::kelvin_t original{300.0};
    pkr::units::fahrenheit_t f = pkr::units::unit_cast<pkr::units::fahrenheit_t>(original);
    pkr::units::kelvin_t back = pkr::units::unit_cast<pkr::units::kelvin_t>(f);
    EXPECT_DOUBLE_EQ(back.value(), original.value());
}

// Test edge cases
TEST_F(TemperatureCastTest, ExtremeTemperatures)
{
    // Very cold
    pkr::units::kelvin_t very_cold{1.0};
    pkr::units::celsius_t c_cold = pkr::units::unit_cast<pkr::units::celsius_t>(very_cold);
    EXPECT_DOUBLE_EQ(c_cold.value(), -272.15);

    // Very hot
    pkr::units::celsius_t very_hot{10000.0};
    pkr::units::kelvin_t k_hot = pkr::units::unit_cast<pkr::units::kelvin_t>(very_hot);
    EXPECT_DOUBLE_EQ(k_hot.value(), 10273.15);
}

} // namespace test
