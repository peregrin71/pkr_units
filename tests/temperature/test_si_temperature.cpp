#include <gtest/gtest.h>
#include <pkr_units/units/base/temperature.h>
#include <pkr_units/units/temperature/celsius.h>
#include <pkr_units/units/temperature/fahrenheit.h>
#include <pkr_units/units/temperature/temperature_cast.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;

class SiTemperatureTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiTemperatureTest, kelvin_construction)
{
    pkr::units::kelvin_t<double> k{5.0};
    ASSERT_DOUBLE_EQ(k.value(), 5.0);
}

TEST_F(SiTemperatureTest, kelvin_dereference_operator)
{
    pkr::units::kelvin_t<double> k{5.0};
    ASSERT_DOUBLE_EQ(*k, 5.0);
}

TEST_F(SiTemperatureTest, kelvin_zero_value)
{
    pkr::units::kelvin_t<double> k{0.0};
    ASSERT_DOUBLE_EQ(k.value(), 0.0);
}

TEST_F(SiTemperatureTest, kelvin_negative_value)
{
    pkr::units::kelvin_t<double> k{-3.5};
    ASSERT_DOUBLE_EQ(k.value(), -3.5);
}

TEST_F(SiTemperatureTest, millikelvin_construction)
{
    pkr::units::millikelvin_t<double> mk{250.0};
    ASSERT_DOUBLE_EQ(mk.value(), 250.0);
}

TEST_F(SiTemperatureTest, microkelvin_construction)
{
    pkr::units::microkelvin_t<double> uk{1000.0};
    ASSERT_DOUBLE_EQ(uk.value(), 1000.0);
}

TEST_F(SiTemperatureTest, nanokelvin_construction)
{
    pkr::units::nanokelvin_t<double> nk{100.0};
    ASSERT_DOUBLE_EQ(nk.value(), 100.0);
}

TEST_F(SiTemperatureTest, kilokelvin_construction)
{
    pkr::units::kilokelvin_t<double> kk{2.5};
    ASSERT_DOUBLE_EQ(kk.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiTemperatureTest, copy_constructor)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2 = k1;
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

TEST_F(SiTemperatureTest, move_constructor)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2 = std::move(k1);
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

TEST_F(SiTemperatureTest, copy_assignment)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{0.0};
    k2 = k1;
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

TEST_F(SiTemperatureTest, move_assignment)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{0.0};
    k2 = std::move(k1);
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiTemperatureTest, add_kelvins)
{
    pkr::units::kelvin_t<double> k1{3.0};
    pkr::units::kelvin_t<double> k2{2.0};
    auto result = k1 + k2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTemperatureTest, subtract_kelvins)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{2.0};
    auto result = k1 - k2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTemperatureTest, add_millikelvins)
{
    pkr::units::millikelvin_t<double> mk1{500.0};
    pkr::units::millikelvin_t<double> mk2{250.0};
    auto result = mk1 + mk2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiTemperatureTest, subtract_millikelvins)
{
    pkr::units::millikelvin_t<double> mk1{750.0};
    pkr::units::millikelvin_t<double> mk2{250.0};
    auto result = mk1 - mk2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiTemperatureTest, add_kelvin_to_millikelvin)
{
    pkr::units::kelvin_t<double> k{1.0};
    pkr::units::millikelvin_t<double> mk{500.0};
    auto result = k + mk;
    // Result is in LHS type (kelvin)
    // 1K + 0.5K = 1.5K
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiTemperatureTest, add_millikelvin_to_kelvin)
{
    pkr::units::millikelvin_t<double> mk{500.0};
    pkr::units::kelvin_t<double> k{1.0};
    auto result = mk + k;
    // Result is in LHS type (millikelvin)
    // 500mK + 1000mK = 1500mK
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiTemperatureTest, subtract_kelvin_from_millikelvin)
{
    pkr::units::millikelvin_t<double> mk{1500.0};
    pkr::units::kelvin_t<double> k{1.0};
    auto result = mk - k;
    // Result is in LHS type (millikelvin)
    // 1500mK - 1000mK = 500mK
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiTemperatureTest, subtract_millikelvin_from_kelvin)
{
    pkr::units::kelvin_t<double> k{2.0};
    pkr::units::millikelvin_t<double> mk{500.0};
    auto result = k - mk;
    // Result is in LHS type (kelvin)
    // 2K - 0.5K = 1.5K
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication and Division
// ============================================================================

TEST_F(SiTemperatureTest, multiply_kelvin_by_scalar)
{
    pkr::units::kelvin_t<double> k{2.0};
    auto result = k * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiTemperatureTest, divide_kelvin_by_scalar)
{
    pkr::units::kelvin_t<double> k{6.0};
    auto result = k / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTemperatureTest, multiply_millikelvin_by_scalar)
{
    pkr::units::millikelvin_t<double> mk{100.0};
    auto result = mk * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiTemperatureTest, divide_millikelvin_by_scalar)
{
    pkr::units::millikelvin_t<double> mk{500.0};
    auto result = mk / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Temperature Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiTemperatureTest, multiply_kelvin_by_kelvin)
{
    pkr::units::kelvin_t<double> k1{2.0};
    pkr::units::kelvin_t<double> k2{3.0};
    auto result = k1 * k2;
    // Result has temperature dimension = 2 (K²)
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.temperature, 2);
}

// ============================================================================
// Temperature Division (Creates Dimensionless)
// ============================================================================

TEST_F(SiTemperatureTest, divide_kelvin_by_kelvin)
{
    pkr::units::kelvin_t<double> k1{10.0};
    pkr::units::kelvin_t<double> k2{2.0};
    auto result = k1 / k2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.temperature, 0);
}

TEST_F(SiTemperatureTest, divide_millikelvin_by_millikelvin)
{
    pkr::units::millikelvin_t<double> mk1{500.0};
    pkr::units::millikelvin_t<double> mk2{100.0};
    auto result = mk1 / mk2;
    // Result is dimensionless
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.temperature, 0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiTemperatureTest, constexpr_kelvin_addition)
{
    constexpr pkr::units::kelvin_t<double> k1{3.0};
    constexpr pkr::units::kelvin_t<double> k2{2.0};
    constexpr auto result = k1 + k2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTemperatureTest, constexpr_kelvin_multiplication)
{
    constexpr pkr::units::kelvin_t<double> k{2.0};
    constexpr auto result = k * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiTemperatureTest, very_small_temperature_values)
{
    pkr::units::nanokelvin_t<double> nk{0.001};
    ASSERT_DOUBLE_EQ(nk.value(), 0.001);
}

TEST_F(SiTemperatureTest, very_large_temperature_values)
{
    pkr::units::kilokelvin_t<double> kk{1000000.0};
    ASSERT_DOUBLE_EQ(kk.value(), 1000000.0);
}

TEST_F(SiTemperatureTest, add_very_different_scales)
{
    pkr::units::millikelvin_t<double> mk{1.0}; // 1 millikelvin
    pkr::units::kelvin_t<double> k{1.0};       // 1 kelvin = 1000 mK
    auto result = mk + k;
    // Result is in LHS type (millikelvin)
    // 1 mK + 1000 mK = 1001 mK
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiTemperatureTest, subtract_resulting_in_negative)
{
    pkr::units::kelvin_t<double> k1{1.0};
    pkr::units::kelvin_t<double> k2{3.0};
    auto result = k1 - k2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}

// ============================================================================
// Offset Temperature Types (Celsius and Fahrenheit)
// ============================================================================

TEST_F(SiTemperatureTest, celsius_construction)
{
    constexpr pkr::units::celsius_t<double> c{25.0};
    ASSERT_DOUBLE_EQ(c.value(), 25.0);
}

TEST_F(SiTemperatureTest, fahrenheit_construction)
{
    constexpr pkr::units::fahrenheit_t<double> f{77.0};
    ASSERT_DOUBLE_EQ(f.value(), 77.0);
}

TEST_F(SiTemperatureTest, celsius_zero_value)
{
    constexpr pkr::units::celsius_t<double> c{0.0};
    ASSERT_DOUBLE_EQ(c.value(), 0.0);
}

TEST_F(SiTemperatureTest, celsius_negative_value)
{
    constexpr pkr::units::celsius_t<double> c{-40.0};
    ASSERT_DOUBLE_EQ(c.value(), -40.0);
}

TEST_F(SiTemperatureTest, fahrenheit_negative_value)
{
    constexpr pkr::units::fahrenheit_t<double> f{-40.0};
    ASSERT_DOUBLE_EQ(f.value(), -40.0);
}

// ============================================================================
// Temperature Cast: Celsius <-> Fahrenheit Conversions (unit_cast overloads)
// ============================================================================

TEST_F(SiTemperatureTest, temperature_cast_celsius_to_fahrenheit_freezing)
{
    constexpr pkr::units::celsius_t<double> c_freezing{0.0};
    constexpr auto f_freezing = pkr::units::unit_cast<pkr::units::fahrenheit_t<double>>(c_freezing);
    ASSERT_NEAR(f_freezing.value(), 32.0, 1e-12);
}

TEST_F(SiTemperatureTest, temperature_cast_celsius_to_fahrenheit_boiling)
{
    constexpr pkr::units::celsius_t<double> c_boiling{100.0};
    constexpr auto f_boiling = pkr::units::unit_cast<pkr::units::fahrenheit_t<double>>(c_boiling);
    ASSERT_NEAR(f_boiling.value(), 212.0, 1e-12);
}

TEST_F(SiTemperatureTest, temperature_cast_celsius_to_fahrenheit_room_temperature)
{
    constexpr pkr::units::celsius_t<double> c_room{20.0};
    constexpr auto f_room = pkr::units::unit_cast<pkr::units::fahrenheit_t<double>>(c_room);
    ASSERT_NEAR(f_room.value(), 68.0, 1e-12);
}

TEST_F(SiTemperatureTest, temperature_cast_celsius_to_fahrenheit_negative_forty)
{
    // -40°C = -40°F (the point where they meet)
    constexpr pkr::units::celsius_t<double> c_neg_forty{-40.0};
    constexpr auto f_neg_forty = pkr::units::unit_cast<pkr::units::fahrenheit_t<double>>(c_neg_forty);
    ASSERT_NEAR(f_neg_forty.value(), -40.0, 1e-12);
}

TEST_F(SiTemperatureTest, temperature_cast_fahrenheit_to_celsius_freezing)
{
    constexpr pkr::units::fahrenheit_t<double> f_freezing{32.0};
    constexpr auto c_freezing = pkr::units::unit_cast<pkr::units::celsius_t<double>>(f_freezing);
    ASSERT_NEAR(c_freezing.value(), 0.0, 1e-12);
}

TEST_F(SiTemperatureTest, temperature_cast_fahrenheit_to_celsius_boiling)
{
    constexpr pkr::units::fahrenheit_t<double> f_boiling{212.0};
    constexpr auto c_boiling = pkr::units::unit_cast<pkr::units::celsius_t<double>>(f_boiling);
    ASSERT_NEAR(c_boiling.value(), 100.0, 1e-12);
}

TEST_F(SiTemperatureTest, temperature_cast_fahrenheit_to_celsius_body_temperature)
{
    // Body temperature: approximately 98.6°F = 37°C
    constexpr pkr::units::fahrenheit_t<double> f_body{98.6};
    constexpr auto c_body = pkr::units::unit_cast<pkr::units::celsius_t<double>>(f_body);
    ASSERT_NEAR(c_body.value(), 37.0, 1e-12);
}

TEST_F(SiTemperatureTest, temperature_cast_fahrenheit_to_celsius_absolute_zero)
{
    // Absolute zero: -459.67°F = -273.15°C
    constexpr pkr::units::fahrenheit_t<double> f_abs_zero{-459.67};
    constexpr auto c_abs_zero = pkr::units::unit_cast<pkr::units::celsius_t<double>>(f_abs_zero);
    ASSERT_NEAR(c_abs_zero.value(), -273.15, 1e-12);
}

// ============================================================================
// Kelvin Offset Conversions (unit_cast)
// ============================================================================

TEST_F(SiTemperatureTest, unit_cast_kelvin_to_celsius_freezing)
{
    constexpr pkr::units::kelvin_t<double> k_freezing{273.15};
    constexpr auto c_freezing = pkr::units::unit_cast<pkr::units::celsius_t<double>>(k_freezing);
    ASSERT_NEAR(c_freezing.value(), 0.0, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_kelvin_to_fahrenheit_freezing)
{
    constexpr pkr::units::kelvin_t<double> k_freezing{273.15};
    constexpr auto f_freezing = pkr::units::unit_cast<pkr::units::fahrenheit_t<double>>(k_freezing);
    ASSERT_NEAR(f_freezing.value(), 32.0, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_celsius_to_kelvin_room_temperature)
{
    constexpr pkr::units::celsius_t<double> c_room{20.0};
    constexpr auto k_room = pkr::units::unit_cast<pkr::units::kelvin_t<double>>(c_room);
    ASSERT_NEAR(k_room.value(), 293.15, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_fahrenheit_to_kelvin_freezing)
{
    constexpr pkr::units::fahrenheit_t<double> f_freezing{32.0};
    constexpr auto k_freezing = pkr::units::unit_cast<pkr::units::kelvin_t<double>>(f_freezing);
    ASSERT_NEAR(k_freezing.value(), 273.15, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_celsius_to_kelvin_negative_forty)
{
    constexpr pkr::units::celsius_t<double> c_neg_forty{-40.0};
    constexpr auto k_neg_forty = pkr::units::unit_cast<pkr::units::kelvin_t<double>>(c_neg_forty);
    ASSERT_NEAR(k_neg_forty.value(), 233.15, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_fahrenheit_to_kelvin_negative_forty)
{
    constexpr pkr::units::fahrenheit_t<double> f_neg_forty{-40.0};
    constexpr auto k_neg_forty = pkr::units::unit_cast<pkr::units::kelvin_t<double>>(f_neg_forty);
    ASSERT_NEAR(k_neg_forty.value(), 233.15, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_kelvin_to_fahrenheit_negative_forty)
{
    constexpr pkr::units::kelvin_t<double> k_neg_forty{233.15};
    constexpr auto f_neg_forty = pkr::units::unit_cast<pkr::units::fahrenheit_t<double>>(k_neg_forty);
    ASSERT_NEAR(f_neg_forty.value(), -40.0, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_millikelvin_to_celsius)
{
    constexpr pkr::units::millikelvin_t<double> mk{300150.0}; // 300.15 K
    constexpr auto c = pkr::units::unit_cast<pkr::units::celsius_t<double>>(mk);
    ASSERT_NEAR(c.value(), 27.0, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_celsius_to_millikelvin)
{
    constexpr pkr::units::celsius_t<double> c{25.0};
    constexpr auto mk = pkr::units::unit_cast<pkr::units::millikelvin_t<double>>(c);
    ASSERT_NEAR(mk.value(), 298150.0, 1e-6);
}

TEST_F(SiTemperatureTest, unit_cast_millikelvin_to_fahrenheit)
{
    constexpr pkr::units::millikelvin_t<double> mk{300150.0}; // 300.15 K
    constexpr auto f = pkr::units::unit_cast<pkr::units::fahrenheit_t<double>>(mk);
    ASSERT_NEAR(f.value(), 80.6, 1e-12);
}

TEST_F(SiTemperatureTest, unit_cast_fahrenheit_to_millikelvin)
{
    constexpr pkr::units::fahrenheit_t<double> f{68.0};
    constexpr auto mk = pkr::units::unit_cast<pkr::units::millikelvin_t<double>>(f);
    ASSERT_NEAR(mk.value(), 293150.0, 1e-6);
}

TEST_F(SiTemperatureTest, unit_cast_kilokelvin_to_celsius)
{
    constexpr pkr::units::kilokelvin_t<double> kk{1.2};
    constexpr auto c = pkr::units::unit_cast<pkr::units::celsius_t<double>>(kk);
    ASSERT_NEAR(c.value(), 926.85, 1e-12);
}

// ============================================================================
// Kelvin Ratio-Based Conversions (unit_cast)
// ============================================================================

TEST_F(SiTemperatureTest, cast_kelvin_to_kilokelvin)
{
    constexpr pkr::units::kelvin_t<double> k{1000.0};
    constexpr auto kk = pkr::units::unit_cast<pkr::units::kilokelvin_t<double>>(k);
    ASSERT_DOUBLE_EQ(kk.value(), 1.0);
}

TEST_F(SiTemperatureTest, cast_kilokelvin_to_kelvin)
{
    constexpr pkr::units::kilokelvin_t<double> kk{1.0};
    constexpr auto k = pkr::units::unit_cast<pkr::units::kelvin_t<double>>(kk);
    ASSERT_DOUBLE_EQ(k.value(), 1000.0);
}

TEST_F(SiTemperatureTest, cast_kelvin_to_millikelvin)
{
    constexpr pkr::units::kelvin_t<double> k{1.0};
    constexpr auto mk = pkr::units::unit_cast<pkr::units::millikelvin_t<double>>(k);
    ASSERT_DOUBLE_EQ(mk.value(), 1000.0);
}

TEST_F(SiTemperatureTest, cast_millikelvin_to_kelvin)
{
    constexpr pkr::units::millikelvin_t<double> mk{1000.0};
    constexpr auto k = pkr::units::unit_cast<pkr::units::kelvin_t<double>>(mk);
    ASSERT_DOUBLE_EQ(k.value(), 1.0);
}

TEST_F(SiTemperatureTest, cast_kilokelvin_to_millikelvin)
{
    constexpr pkr::units::kilokelvin_t<double> kk{1.0};
    constexpr auto mk = pkr::units::unit_cast<pkr::units::millikelvin_t<double>>(kk);
    ASSERT_DOUBLE_EQ(mk.value(), 1000000.0);
}
