#include <gtest/gtest.h>
#include <format>
#include <si_units/derived/velocity.h>
#include <si_units/standard/length.h>
#include <si_units/standard/time.h>
#include <si_units/formatting/si_units_formatters.h>

using namespace ::testing;

class SiVelocityTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiVelocityTest, meter_per_second_construction)
{
    si::meter_per_second v{5.0};
    ASSERT_DOUBLE_EQ(v.value(), 5.0);
}

TEST_F(SiVelocityTest, meter_per_second_dereference_operator)
{
    si::meter_per_second v{5.0};
    ASSERT_DOUBLE_EQ(*v, 5.0);
}

TEST_F(SiVelocityTest, meter_per_second_zero_value)
{
    si::meter_per_second v{0.0};
    ASSERT_DOUBLE_EQ(v.value(), 0.0);
}

TEST_F(SiVelocityTest, meter_per_second_negative_value)
{
    si::meter_per_second v{-10.5};
    ASSERT_DOUBLE_EQ(v.value(), -10.5);
}

TEST_F(SiVelocityTest, kilometer_per_hour_construction)
{
    si::kilometer_per_hour v{100.0};
    ASSERT_DOUBLE_EQ(v.value(), 100.0);
}

TEST_F(SiVelocityTest, centimeter_per_second_construction)
{
    si::centimeter_per_second v{250.0};
    ASSERT_DOUBLE_EQ(v.value(), 250.0);
}

TEST_F(SiVelocityTest, millimeter_per_second_construction)
{
    si::millimeter_per_second v{1000.0};
    ASSERT_DOUBLE_EQ(v.value(), 1000.0);
}

TEST_F(SiVelocityTest, kilometers_per_second_construction)
{
    si::kilometer_per_second v{2.5};
    ASSERT_DOUBLE_EQ(v.value(), 2.5);
}

TEST_F(SiVelocityTest, miles_per_hour_construction)
{
    si::miles_per_hour v{60.0};
    ASSERT_DOUBLE_EQ(v.value(), 60.0);
}

TEST_F(SiVelocityTest, feet_per_second_construction)
{
    si::feet_per_second v{100.0};
    ASSERT_DOUBLE_EQ(v.value(), 100.0);
}

TEST_F(SiVelocityTest, knots_construction)
{
    si::knots v{20.0};
    ASSERT_DOUBLE_EQ(v.value(), 20.0);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiVelocityTest, copy_constructor)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, move_constructor)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2 = std::move(v1);
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, copy_assignment)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2{0.0};
    v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, move_assignment)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2{0.0};
    v2 = std::move(v1);
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

// ============================================================================
// Unit Conversion Tests (same-ratio units)
// ============================================================================

TEST_F(SiVelocityTest, meters_per_second_same_unit_identity)
{
    // Just verify we can create and use the same unit
    si::meter_per_second v1{10.0};
    si::meter_per_second v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 10.0);
}

// ============================================================================
// Arithmetic Operations - Addition and Subtraction
// ============================================================================

TEST_F(SiVelocityTest, add_same_units_meter_per_second)
{
    si::meter_per_second v1{10.0};
    si::meter_per_second v2{20.0};
    si::meter_per_second result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 30.0);
}

TEST_F(SiVelocityTest, subtract_same_units_meter_per_second)
{
    si::meter_per_second v1{30.0};
    si::meter_per_second v2{10.0};
    si::meter_per_second result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 20.0);
}

TEST_F(SiVelocityTest, add_different_ratio_units_returns_lhs_type)
{
    // kilometer_per_hour + meter_per_second -> kilometer_per_hour (LHS type)
    // 36 km/h + 10 m/s = 36 km/h + 36 km/h = 72 km/h
    si::kilometer_per_hour v1{36.0};
    si::meter_per_second v2{10.0};
    si::kilometer_per_hour result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 72.0);
}

TEST_F(SiVelocityTest, add_different_ratio_units_opposite_order)
{
    // meter_per_second + kilometer_per_hour -> meter_per_second (LHS type)
    // 10 m/s + 36 km/h = 10 m/s + 10 m/s = 20 m/s
    si::meter_per_second v1{10.0};
    si::kilometer_per_hour v2{36.0};
    si::meter_per_second result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 20.0);
}

TEST_F(SiVelocityTest, subtract_different_ratio_units_returns_lhs_type)
{
    // kilometer_per_hour - meter_per_second -> kilometer_per_hour (LHS type)
    // 72 km/h - 10 m/s = 72 km/h - 36 km/h = 36 km/h
    si::kilometer_per_hour v1{72.0};
    si::meter_per_second v2{10.0};
    si::kilometer_per_hour result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 36.0);
}

TEST_F(SiVelocityTest, subtract_different_ratio_units_opposite_order)
{
    // meter_per_second - kilometer_per_hour -> meter_per_second (LHS type)
    // 20 m/s - 36 km/h = 20 m/s - 10 m/s = 10 m/s
    si::meter_per_second v1{20.0};
    si::kilometer_per_hour v2{36.0};
    si::meter_per_second result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiVelocityTest, add_centimeter_and_meter_per_second)
{
    // 100 cm/s + 5 m/s = 1 m/s + 5 m/s = 6 m/s (result in m/s, LHS type)
    si::centimeter_per_second v1{600.0};  // 6 m/s in cm/s
    si::meter_per_second v2{5.0};
    // This should compile but note: centimeter is LHS, so result is in cm/s
    auto result = v1 + v2;
    // 600 cm/s + 5 m/s (=500 cm/s) = 1100 cm/s
    ASSERT_DOUBLE_EQ(result.value(), 1100.0);
}

// ============================================================================
// Arithmetic Operations - Multiplication and Division
// ============================================================================

TEST_F(SiVelocityTest, multiply_velocity_by_scalar)
{
    si::meter_per_second v{5.0};
    auto result = v * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiVelocityTest, scalar_multiply_velocity)
{
    si::meter_per_second v{5.0};
    auto result = 3.0 * v;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiVelocityTest, divide_velocity_by_scalar)
{
    si::meter_per_second v{20.0};
    auto result = v / 4.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

// ============================================================================
// Comparison Operations
// ============================================================================

TEST_F(SiVelocityTest, equal_same_units)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2{5.0};
    ASSERT_TRUE(v1 == v2);
}

TEST_F(SiVelocityTest, not_equal_same_units)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2{10.0};
    ASSERT_TRUE(v1 != v2);
}

TEST_F(SiVelocityTest, less_than_same_units)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2{10.0};
    ASSERT_TRUE(v1 < v2);
}

TEST_F(SiVelocityTest, greater_than_same_units)
{
    si::meter_per_second v1{15.0};
    si::meter_per_second v2{10.0};
    ASSERT_TRUE(v1 > v2);
}

TEST_F(SiVelocityTest, less_than_or_equal_same_units)
{
    si::meter_per_second v1{5.0};
    si::meter_per_second v2{10.0};
    ASSERT_TRUE(v1 <= v2);
    
    si::meter_per_second v3{10.0};
    ASSERT_TRUE(v2 <= v3);
}

TEST_F(SiVelocityTest, greater_than_or_equal_same_units)
{
    si::meter_per_second v1{15.0};
    si::meter_per_second v2{10.0};
    ASSERT_TRUE(v1 >= v2);
    
    si::meter_per_second v3{10.0};
    ASSERT_TRUE(v2 >= v3);
}

TEST_F(SiVelocityTest, equal_different_units_same_value)
{
    // These have the same physical velocity but different stored values
    si::meter_per_second v_mps{1.0};
    si::centimeter_per_second v_cms{100.0};
    ASSERT_TRUE(v_mps == v_cms);
}

TEST_F(SiVelocityTest, less_than_different_units)
{
    // 5 m/s < 36 km/h (which is 10 m/s)
    si::meter_per_second v1{5.0};
    si::kilometer_per_hour v2{36.0};
    ASSERT_TRUE(v1 < v2);
}

TEST_F(SiVelocityTest, greater_than_different_units)
{
    // 20 m/s > 36 km/h (which is 10 m/s)
    si::meter_per_second v1{20.0};
    si::kilometer_per_hour v2{36.0};
    ASSERT_TRUE(v1 > v2);
}