#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;
using namespace pkr::units;

static_assert(
    std::is_same_v<decltype(std::declval<celsius_t<double>>() + std::declval<celsius_t<double>>()), celsius_t<double>>,
    "Temperature addition must preserve type");
static_assert(
    std::is_same_v<decltype(unit_cast<kelvin_t<double>>(std::declval<celsius_t<double>>())), kelvin_t<double>>,
    "unit_cast to kelvin_t must return kelvin_t");
static_assert(
    std::is_same_v<decltype(unit_cast<fahrenheit_t<double>>(std::declval<celsius_t<double>>())), fahrenheit_t<double>>,
    "unit_cast to fahrenheit_t must return fahrenheit_t");

class TemperatureAffineTest : public Test
{
};

TEST_F(TemperatureAffineTest, celsius_construction)
{
    celsius_t<double> temp{0.0};
    ASSERT_DOUBLE_EQ(temp.value(), 0.0);
}

TEST_F(TemperatureAffineTest, kelvin_construction)
{
    kelvin_t<double> temp{273.15};
    ASSERT_DOUBLE_EQ(temp.value(), 273.15);
}

TEST_F(TemperatureAffineTest, fahrenheit_construction)
{
    fahrenheit_t<double> temp{32.0};
    ASSERT_DOUBLE_EQ(temp.value(), 32.0);
}

TEST_F(TemperatureAffineTest, celsius_to_kelvin_zero_point)
{
    celsius_t<double> temp{0.0};
    auto kelvin = unit_cast<kelvin_t<double>>(temp);
    static_assert(std::is_same_v<decltype(kelvin), kelvin_t<double>>, "Celsius to Kelvin cast type check");
    ASSERT_DOUBLE_EQ(kelvin.value(), 273.15);
}

TEST_F(TemperatureAffineTest, kelvin_to_celsius_zero_point)
{
    kelvin_t<double> temp{273.15};
    auto celsius = unit_cast<celsius_t<double>>(temp);
    ASSERT_DOUBLE_EQ(celsius.value(), 0.0);
}

TEST_F(TemperatureAffineTest, celsius_to_fahrenheit_freezing_point)
{
    celsius_t<double> temp_c{0.0};
    auto temp_f = unit_cast<fahrenheit_t<double>>(temp_c);
    static_assert(std::is_same_v<decltype(temp_f), fahrenheit_t<double>>, "Celsius to Fahrenheit cast type check");
    ASSERT_DOUBLE_EQ(temp_f.value(), 32.0);
}

TEST_F(TemperatureAffineTest, fahrenheit_to_celsius_freezing_point)
{
    fahrenheit_t<double> temp_f{32.0};
    auto temp_c = unit_cast<celsius_t<double>>(temp_f);
    ASSERT_DOUBLE_EQ(temp_c.value(), 0.0);
}

TEST_F(TemperatureAffineTest, celsius_to_fahrenheit_boiling_point)
{
    celsius_t<double> temp_c{100.0};
    auto temp_f = unit_cast<fahrenheit_t<double>>(temp_c);
    ASSERT_NEAR(temp_f.value(), 212.0, 0.01);
}

TEST_F(TemperatureAffineTest, fahrenheit_to_celsius_body_temp)
{
    fahrenheit_t<double> temp_f{98.6};
    auto temp_c = unit_cast<celsius_t<double>>(temp_f);
    ASSERT_NEAR(temp_c.value(), 37.0, 0.01);
}

TEST_F(TemperatureAffineTest, temperature_addition_not_supported)
{
    celsius_t<double> t1{10.0};
    celsius_t<double> t2{20.0};

    auto result = t1 + t2;
    ASSERT_DOUBLE_EQ(result.value(), 30.0);
}

TEST_F(TemperatureAffineTest, temperature_comparison)
{
    celsius_t<double> t1{10.0};
    celsius_t<double> t2{10.0};
    celsius_t<double> t3{20.0};

    ASSERT_TRUE(t1 == t2);
    ASSERT_TRUE(t1 != t3);
    ASSERT_TRUE(t1 < t3);
    ASSERT_TRUE(t3 > t1);
    ASSERT_TRUE(t1 <= t2);
    ASSERT_TRUE(t3 >= t1);
}

TEST_F(TemperatureAffineTest, negative_celsius)
{
    celsius_t<double> temp{-40.0};
    auto kelvin = unit_cast<kelvin_t<double>>(temp);
    ASSERT_DOUBLE_EQ(kelvin.value(), 233.15);
}

TEST_F(TemperatureAffineTest, negative_celsius_to_fahrenheit)
{
    celsius_t<double> temp{-40.0};
    auto fahrenheit = unit_cast<fahrenheit_t<double>>(temp);
    ASSERT_DOUBLE_EQ(fahrenheit.value(), -40.0);
}

TEST_F(TemperatureAffineTest, absolute_zero_kelvin)
{
    kelvin_t<double> absolute_zero{0.0};
    auto celsius = unit_cast<celsius_t<double>>(absolute_zero);
    ASSERT_DOUBLE_EQ(celsius.value(), -273.15);
}

TEST_F(TemperatureAffineTest, room_temperature_conversions)
{
    celsius_t<double> room_c{20.0};
    auto room_k = unit_cast<kelvin_t<double>>(room_c);
    auto room_f = unit_cast<fahrenheit_t<double>>(room_c);

    ASSERT_DOUBLE_EQ(room_k.value(), 293.15);
    ASSERT_DOUBLE_EQ(room_f.value(), 68.0);
}

TEST_F(TemperatureAffineTest, temperature_scalar_multiplication)
{
    kelvin_t<double> temp{300.0};
    auto result = temp * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 150.0);
}

TEST_F(TemperatureAffineTest, temperature_scalar_division)
{
    kelvin_t<double> temp{300.0};
    auto result = temp / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 150.0);
}

TEST_F(TemperatureAffineTest, temperature_zero_value)
{
    kelvin_t<double> temp{0.0};
    ASSERT_DOUBLE_EQ(temp.value(), 0.0);
}

} // namespace test
