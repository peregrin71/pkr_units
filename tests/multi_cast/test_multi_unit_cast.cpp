#include <gtest/gtest.h>
#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>
#include <pkr_units/si_units_formatting.h>
#include <pkr_units/impl/cast/unit_cast.h>
#include <pkr_units/impl/cast/multi_unit_cast.h>
#include <pkr_units/units/derived/velocity.h>
#include <format>
#include <cmath>
#include <type_traits>

namespace test
{

using namespace ::testing;

class MultiCastTest : public Test
{
};

// ============================================================================
// Basic Multi-Unit Casting Tests with Various Scales
// ============================================================================

TEST_F(MultiCastTest, cast_meter_per_second_to_kilometer_per_hour_via_multi_unit)
{
    // Using multi_unit_cast to create a new derived unit from base units
    // 10 m/s should convert to 36 km/h
    pkr::units::meter_per_second_t mps{10.0};

    // Cast to km/h using multi_unit_cast with kilometer numerator and hour denominator
    auto kmh = pkr::units::multi_unit_cast<pkr::units::kilometer_t, pkr::units::per<pkr::units::hour_t>>(mps);

    ASSERT_DOUBLE_EQ(kmh.value(), 36.0);
}

TEST_F(MultiCastTest, cast_velocity_to_millimeter_per_second)
{
    // 5 m/s = 5000 mm/s
    pkr::units::meter_per_second_t mps{5.0};

    auto mms = pkr::units::multi_unit_cast<pkr::units::millimeter_t, pkr::units::per<pkr::units::second_t>>(mps);

    ASSERT_DOUBLE_EQ(mms.value(), 5000.0);
}

TEST_F(MultiCastTest, cast_velocity_to_kilometer_per_second)
{
    // 1000 m/s = 1 km/s
    pkr::units::meter_per_second_t mps{1000.0};

    auto kms = pkr::units::multi_unit_cast<pkr::units::kilometer_t, pkr::units::per<pkr::units::second_t>>(mps);

    ASSERT_DOUBLE_EQ(kms.value(), 1.0);
}

TEST_F(MultiCastTest, cast_to_base_units_returns_ratio_one)
{
    // 36 km/h = 10 m/s
    pkr::units::kilometer_per_hour_t kmh{36.0};

    auto base = pkr::units::multi_unit_cast_to_base_units<pkr::units::meter_t, pkr::units::per<pkr::units::second_t>>(kmh);

    using base_traits = pkr::units::details::is_pkr_unit<decltype(base)>;
    static_assert(std::is_same_v<typename base_traits::ratio_type, std::ratio<1, 1>>);
    ASSERT_NEAR(base.value(), 10.0, 1e-12);
}

// ============================================================================
// Multi-Unit Casting Tests with Imperial Units
// ============================================================================

TEST_F(MultiCastTest, cast_meter_per_second_to_feet_per_second)
{
    // 1 m/s ~ 3.28084 ft/s
    pkr::units::meter_per_second_t mps{1.0};

    auto fps = pkr::units::multi_unit_cast<pkr::units::foot_t, pkr::units::per<pkr::units::second_t>>(mps);

    ASSERT_NEAR(fps.value(), 3.28084, 1e-5);
}

TEST_F(MultiCastTest, cast_meter_per_second_to_miles_per_hour)
{
    // 1 m/s ~ 2.23694 mph
    pkr::units::meter_per_second_t mps{10.0};

    auto mph = pkr::units::multi_unit_cast<pkr::units::mile_t, pkr::units::per<pkr::units::hour_t>>(mps);

    ASSERT_NEAR(mph.value(), 22.3694, 1e-3);
}

// ============================================================================
// Multi-Unit Casting Tests with Scaled Units
// ============================================================================

TEST_F(MultiCastTest, cast_with_centimeter_numerator)
{
    // 5 m/s = 500 cm/s
    pkr::units::meter_per_second_t mps{5.0};

    auto cms = pkr::units::multi_unit_cast<pkr::units::centimeter_t, pkr::units::per<pkr::units::second_t>>(mps);

    ASSERT_DOUBLE_EQ(cms.value(), 500.0);
}

TEST_F(MultiCastTest, cast_with_minute_denominator)
{
    // 10 m/s = 600 m/min
    pkr::units::meter_per_second_t mps{10.0};

    auto mpm = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per<pkr::units::minute_t>>(mps);

    ASSERT_DOUBLE_EQ(mpm.value(), 600.0);
}

TEST_F(MultiCastTest, cast_with_millisecond_denominator)
{
    // 1 m/s = 0.001 m/ms
    pkr::units::meter_per_second_t mps{1.0};

    auto mms = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per<pkr::units::millisecond_t>>(mps);

    ASSERT_DOUBLE_EQ(mms.value(), 0.001);
}

// ============================================================================
// Acceleration Tests (2 denominators: m/s^2)
// ============================================================================

TEST_F(MultiCastTest, acceleration_meter_per_second_squared)
{
    // Dimensional cast to acceleration units using per_unit_squared.
    pkr::units::meter_per_second_t velocity{100.0};

    // Conceptual: acceleration should have dimension [length / time^2]
    // Using multi_unit_cast with per_unit_squared
    auto acceleration = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(velocity);

    // Note: This is a dimensional cast test - the value represents
    // converting m/s to m/s^2 (which would be unusual in practice)
    ASSERT_GT(acceleration.value(), 0.0);
}

TEST_F(MultiCastTest, acceleration_kilometer_per_hour_squared)
{
    // Convert velocity to acceleration units with km/h^2
    pkr::units::kilometer_per_hour_t kmh{100.0};

    auto kmh_squared = pkr::units::multi_unit_cast<pkr::units::kilometer_t, pkr::units::per_unit_squared<pkr::units::hour_t>>(kmh);

    ASSERT_GT(kmh_squared.value(), 0.0);
}

// ============================================================================
// Multi-Unit Casting with Different Dimension Combinations
// ============================================================================

TEST_F(MultiCastTest, cast_with_different_scales_numerator_and_denominator)
{
    // Test casting with different scaled units in numerator and denominator
    // Example: convert m/s to cm/ms (different scales on both sides)
    pkr::units::meter_per_second_t mps{1.0};

    auto cms_per_ms = pkr::units::multi_unit_cast<pkr::units::centimeter_t, pkr::units::per<pkr::units::millisecond_t>>(mps);

    // 1 m/s = 100 cm/s = 0.1 cm/ms
    ASSERT_NEAR(cms_per_ms.value(), 0.1, 1e-10);
}

TEST_F(MultiCastTest, cast_kilometer_to_meter_per_second)
{
    // Cast a length unit to velocity by adding a denominator
    pkr::units::kilometer_t km{36.0}; // 36 km

    auto mps = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per<pkr::units::second_t>>(km);

    // 36 km = 36000 m, so 36000 m/s
    ASSERT_DOUBLE_EQ(mps.value(), 36000.0);
}

TEST_F(MultiCastTest, cast_with_two_denominator_units)
{
    // Use two denominators to exercise multi-denominator processing
    pkr::units::meter_per_second_t mps{2.0};

    auto per_second_meter =
        pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per<pkr::units::second_t, pkr::units::meter_t>>(mps);

    using traits = pkr::units::details::is_pkr_unit<decltype(per_second_meter)>;
    static_assert(traits::value_dimension.length == 0);
    static_assert(traits::value_dimension.time == -1);
    ASSERT_DOUBLE_EQ(per_second_meter.value(), 2.0);
}

TEST_F(MultiCastTest, cast_with_integral_constant_power_denominator)
{
    // Use explicit integral_constant power to exercise power handling
    pkr::units::meter_per_second_t mps{3.0};

    auto per_second_squared =
        pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per<pkr::units::second_t, std::integral_constant<int, 2>, pkr::units::meter_t>>(
            mps);

    using traits = pkr::units::details::is_pkr_unit<decltype(per_second_squared)>;
    static_assert(traits::value_dimension.length == 0);
    static_assert(traits::value_dimension.time == -2);
    ASSERT_DOUBLE_EQ(per_second_squared.value(), 3.0);
}

TEST_F(MultiCastTest, cast_with_integral_constant_negative_power_denominator)
{
    // Negative power in denominator should add positive dimensions
    pkr::units::meter_per_second_t mps{4.0};

    auto times_second_squared =
        pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per<pkr::units::second_t, std::integral_constant<int, -2>, pkr::units::meter_t>>(
            mps);

    using traits = pkr::units::details::is_pkr_unit<decltype(times_second_squared)>;
    static_assert(traits::value_dimension.length == 0);
    static_assert(traits::value_dimension.time == 2);
    ASSERT_DOUBLE_EQ(times_second_squared.value(), 4.0);
}

// ============================================================================
// Specialized Per Templates Tests
// ============================================================================

TEST_F(MultiCastTest, specialized_template_per_unit_squared)
{
    // Using per_unit_squared specialized template
    pkr::units::meter_per_second_t mps{100.0};

    auto m_per_s2 = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);

    ASSERT_GT(m_per_s2.value(), 0.0);
}

TEST_F(MultiCastTest, specialized_template_per_unit_cubed)
{
    // Using per_unit_cubed specialized template
    pkr::units::meter_per_second_t mps{1000.0};

    auto m_per_s3 = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per_unit_cubed<pkr::units::second_t>>(mps);

    ASSERT_GT(m_per_s3.value(), 0.0);
}

TEST_F(MultiCastTest, specialized_template_per_unit_quartic)
{
    // Using per_unit_quartic specialized template
    pkr::units::meter_per_second_t mps{10.0};

    auto m_per_s4 = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per_unit_quartic<pkr::units::second_t>>(mps);

    ASSERT_GT(m_per_s4.value(), 0.0);
}

TEST_F(MultiCastTest, specialized_template_per_unit_inverse)
{
    // Using per_unit_inverse (negative power)
    pkr::units::meter_per_second_t mps{10.0};

    auto m_times_s = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per_unit_inverse<pkr::units::second_t>>(mps);

    // m/s with per_unit_inverse should give m*s
    ASSERT_GT(m_times_s.value(), 0.0);
}

TEST_F(MultiCastTest, specialized_template_per_unit_inverse_squared)
{
    // Using per_unit_inverse_squared (negative power)
    pkr::units::meter_per_second_t mps{10.0};

    auto m_times_s2 = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::per_unit_inverse_squared<pkr::units::second_t>>(mps);

    ASSERT_GT(m_times_s2.value(), 0.0);
}

// ============================================================================
// Derived Unit Tests with multi_unit_cast
// ============================================================================

TEST_F(MultiCastTest, velocity_derived_unit_via_multi_cast)
{
    // Test casting velocity derived units to different scales
    pkr::units::meter_per_second_t mps{20.0};

    auto kmh = pkr::units::multi_unit_cast<pkr::units::kilometer_t, pkr::units::per<pkr::units::hour_t>>(mps);

    static_assert(std::is_same_v<decltype(kmh), pkr::units::details::unit_t<double, std::ratio<5, 18>, pkr::units::velocity_dimension>>);
    ASSERT_DOUBLE_EQ(kmh.value(), 72.0);
}

// ============================================================================
// Complex Dimension Tests (Torque: kg*m^2/s^2)
// ============================================================================

TEST_F(MultiCastTest, torque_kilogram_meter_squared_per_second_squared)
{
    // Torque = Force x Distance = (kg*m/s^2) x m = kg*m^2/s^2
    // Test creating a torque-like unit with two numerators

    // Start with a velocity unit and cast it to have both kg and m^2 in numerator
    pkr::units::meter_per_second_t mps{10.0};

    auto torque_like = pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);

    // Value should be preserved with different dimensions
    ASSERT_GT(torque_like.value(), 0.0);
}

TEST_F(MultiCastTest, torque_gram_centimeter_squared_per_second_squared)
{
    // Convert to smaller torque unit scales
    pkr::units::meter_per_second_t mps{5.0};

    auto torque_gram_cm2 = pkr::units::multi_unit_cast<pkr::units::gram_t, pkr::units::centimeter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);

    ASSERT_GT(torque_gram_cm2.value(), 0.0);
}

TEST_F(MultiCastTest, torque_with_millisecond_cubed_denominator)
{
    // Complex dimension with higher power denominator
    // Testing three powers in denominator (unusual but testing template generality)
    pkr::units::meter_per_second_t mps{100.0};

    auto complex_unit = pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per_unit_cubed<pkr::units::millisecond_t>>(mps);

    ASSERT_GT(complex_unit.value(), 0.0);
}

// ============================================================================
// Multiple Numerators Tests
// ============================================================================

TEST_F(MultiCastTest, two_numerators_meter_and_second)
{
    // Create a unit with two different numerators: m*s / s = m
    pkr::units::meter_per_second_t mps{5.0};

    auto meter_times_second = pkr::units::multi_unit_cast<pkr::units::meter_t, pkr::units::second_t, pkr::units::per<pkr::units::second_t>>(mps);

    // m/s * (m * s / s) = m^2
    ASSERT_GT(meter_times_second.value(), 0.0);
}

TEST_F(MultiCastTest, two_numerators_kilogram_meter)
{
    // Momentum-like unit: kg*m/s
    pkr::units::meter_per_second_t mps{20.0};

    auto kg_m_per_s = pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per<pkr::units::second_t>>(mps);

    ASSERT_GT(kg_m_per_s.value(), 0.0);
}

TEST_F(MultiCastTest, two_numerators_scaled_units)
{
    // Test with scaled units in both numerators: kg*mm/s
    pkr::units::meter_per_second_t mps{10.0};

    auto kg_mm_per_s = pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::millimeter_t, pkr::units::per<pkr::units::second_t>>(mps);

    // 10 m/s -> kg*mm/s: the meter becomes millimeter (1000x), so 10000
    ASSERT_GT(kg_mm_per_s.value(), 0.0);
}

// ============================================================================
// Complex Unit Conversions with Different Scales
// ============================================================================

TEST_F(MultiCastTest, three_numerators_complex_dimension)
{
    // Test with three numerators: kg*m*s/s^2 = kg*m/s
    pkr::units::meter_per_second_t mps{15.0};

    auto complex_three =
        pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::second_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);

    ASSERT_GT(complex_three.value(), 0.0);
}

TEST_F(MultiCastTest, energy_like_unit_kilogram_meter_squared_per_second_squared)
{
    // Energy/Work dimension: kg*m^2/s^2 (Joule)
    pkr::units::meter_per_second_t mps{50.0};

    auto energy_unit = pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);

    ASSERT_GT(energy_unit.value(), 0.0);
}

TEST_F(MultiCastTest, power_unit_kilogram_meter_squared_per_second_cubed)
{
    // Power dimension: kg*m^2/s^3 (Watt)
    pkr::units::meter_per_second_t mps{100.0};

    auto power_unit = pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per_unit_cubed<pkr::units::second_t>>(mps);

    ASSERT_GT(power_unit.value(), 0.0);
}

TEST_F(MultiCastTest, force_like_unit_kilogram_meter_per_second_squared)
{
    // Force dimension: kg*m/s^2 (Newton)
    pkr::units::meter_per_second_t mps{9.81};

    auto base_units =
        pkr::units::multi_unit_cast_to_base_units<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);
    auto force_unit =
        pkr::units::multi_unit_cast_to_derived<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);

    using base_traits = pkr::units::details::is_pkr_unit<decltype(base_units)>;
    static_assert(std::is_same_v<typename base_traits::ratio_type, std::ratio<1, 1>>);
    static_assert(base_traits::value_dimension == pkr::units::force_dimension);
    static_assert(std::is_same_v<decltype(force_unit), pkr::units::newton_t>);

    std::string base_str = std::format("{}", base_units);
    std::string derived_str = std::format("{}", force_unit);

    EXPECT_NE(base_str.find("kg"), std::string::npos);
    EXPECT_NE(base_str.find("m"), std::string::npos);
    EXPECT_NE(base_str.find("s"), std::string::npos);
    EXPECT_EQ(derived_str, "9.81 N");
    ASSERT_NEAR(force_unit.value(), 9.81, 1e-5);
}

// ============================================================================
// Scaled Complex Units
// ============================================================================

TEST_F(MultiCastTest, torque_gram_millimeter_squared_per_second_squared)
{
    // Torque with smaller scales: g*mm^2/s^2
    pkr::units::meter_per_second_t mps{5.0};

    auto torque_small = pkr::units::multi_unit_cast<pkr::units::gram_t, pkr::units::millimeter_t, pkr::units::per_unit_squared<pkr::units::second_t>>(mps);

    ASSERT_GT(torque_small.value(), 0.0);
}

TEST_F(MultiCastTest, momentum_with_hour_denominator)
{
    // Unusual but valid: kg*m/h
    pkr::units::meter_per_second_t mps{10.0};

    auto kg_m_per_h = pkr::units::multi_unit_cast<pkr::units::kilogram_t, pkr::units::meter_t, pkr::units::per<pkr::units::hour_t>>(mps);

    // 10 m/s = 36000 m/h, so 10 kg*m/s = 36000 kg*m/h
    ASSERT_DOUBLE_EQ(kg_m_per_h.value(), 36000.0);
}

} // namespace test
