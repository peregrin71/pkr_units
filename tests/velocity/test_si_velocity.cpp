#include <gtest/gtest.h>
#include <format>
#include <pkr_units/derived/velocity.h>
#include <pkr_units/standard/length.h>
#include <pkr_units/standard/time.h>

using namespace ::testing;

class SiVelocityTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiVelocityTest, meter_per_second_construction)
{
    pkr::units::meter_per_second_t v{5.0};
    ASSERT_DOUBLE_EQ(v.value(), 5.0);
}

TEST_F(SiVelocityTest, meter_per_second_dereference_operator)
{
    pkr::units::meter_per_second_t v{5.0};
    ASSERT_DOUBLE_EQ(*v, 5.0);
}

TEST_F(SiVelocityTest, meter_per_second_zero_value)
{
    pkr::units::meter_per_second_t v{0.0};
    ASSERT_DOUBLE_EQ(v.value(), 0.0);
}

TEST_F(SiVelocityTest, meter_per_second_negative_value)
{
    pkr::units::meter_per_second_t v{-10.5};
    ASSERT_DOUBLE_EQ(v.value(), -10.5);
}

TEST_F(SiVelocityTest, kilometer_per_hour_construction)
{
    pkr::units::kilometer_per_hour v{100.0};
    ASSERT_DOUBLE_EQ(v.value(), 100.0);
}

TEST_F(SiVelocityTest, centimeter_per_second_construction)
{
    pkr::units::centimeter_per_second v{250.0};
    ASSERT_DOUBLE_EQ(v.value(), 250.0);
}

TEST_F(SiVelocityTest, millimeter_per_second_construction)
{
    pkr::units::millimeter_per_second v{1000.0};
    ASSERT_DOUBLE_EQ(v.value(), 1000.0);
}

TEST_F(SiVelocityTest, kilometers_per_second_construction)
{
    pkr::units::kilometer_per_second v{2.5};
    ASSERT_DOUBLE_EQ(v.value(), 2.5);
}

TEST_F(SiVelocityTest, miles_per_hour_construction)
{
    pkr::units::miles_per_hour v{60.0};
    ASSERT_DOUBLE_EQ(v.value(), 60.0);
}

TEST_F(SiVelocityTest, feet_per_second_construction)
{
    pkr::units::feet_per_second v{100.0};
    ASSERT_DOUBLE_EQ(v.value(), 100.0);
}

TEST_F(SiVelocityTest, knots_construction)
{
    pkr::units::knots v{20.0};
    ASSERT_DOUBLE_EQ(v.value(), 20.0);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiVelocityTest, copy_constructor)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, move_constructor)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2 = std::move(v1);
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, copy_assignment)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2{0.0};
    v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, move_assignment)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2{0.0};
    v2 = std::move(v1);
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

// ============================================================================
// Unit Conversion Tests (same-ratio units)
// ============================================================================

TEST_F(SiVelocityTest, meters_per_second_same_unit_identity)
{
    // Just verify we can create and use the same unit
    pkr::units::meter_per_second_t v1{10.0};
    pkr::units::meter_per_second_t v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 10.0);
}

// ============================================================================
// Arithmetic Operations - Addition and Subtraction
// ============================================================================

TEST_F(SiVelocityTest, add_same_units_meter_per_second)
{
    pkr::units::meter_per_second_t v1{10.0};
    pkr::units::meter_per_second_t v2{20.0};
    pkr::units::meter_per_second_t result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 30.0);
}

TEST_F(SiVelocityTest, subtract_same_units_meter_per_second)
{
    pkr::units::meter_per_second_t v1{30.0};
    pkr::units::meter_per_second_t v2{10.0};
    pkr::units::meter_per_second_t result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 20.0);
}

TEST_F(SiVelocityTest, add_different_ratio_units_returns_lhs_type)
{
    // kilometer_per_hour + meter_per_second -> kilometer_per_hour (LHS type)
    // 36 km/h + 10 m/s = 36 km/h + 36 km/h = 72 km/h
    pkr::units::kilometer_per_hour v1{36.0};
    pkr::units::meter_per_second_t v2{10.0};
    pkr::units::kilometer_per_hour result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 72.0);
}

TEST_F(SiVelocityTest, add_different_ratio_units_opposite_order)
{
    // meter_per_second + kilometer_per_hour -> meter_per_second (LHS type)
    // 10 m/s + 36 km/h = 10 m/s + 10 m/s = 20 m/s
    pkr::units::meter_per_second_t v1{10.0};
    pkr::units::kilometer_per_hour v2{36.0};
    pkr::units::meter_per_second_t result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 20.0);
}

TEST_F(SiVelocityTest, subtract_different_ratio_units_returns_lhs_type)
{
    // kilometer_per_hour - meter_per_second -> kilometer_per_hour (LHS type)
    // 72 km/h - 10 m/s = 72 km/h - 36 km/h = 36 km/h
    pkr::units::kilometer_per_hour v1{72.0};
    pkr::units::meter_per_second_t v2{10.0};
    pkr::units::kilometer_per_hour result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 36.0);
}

TEST_F(SiVelocityTest, subtract_different_ratio_units_opposite_order)
{
    // meter_per_second - kilometer_per_hour -> meter_per_second (LHS type)
    // 20 m/s - 36 km/h = 20 m/s - 10 m/s = 10 m/s
    pkr::units::meter_per_second_t v1{20.0};
    pkr::units::kilometer_per_hour v2{36.0};
    pkr::units::meter_per_second_t result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiVelocityTest, add_centimeter_and_meter_per_second)
{
    // 100 cm/s + 5 m/s = 1 m/s + 5 m/s = 6 m/s (result in m/s, LHS type)
    pkr::units::centimeter_per_second v1{600.0};  // 6 m/s in cm/s
    pkr::units::meter_per_second_t v2{5.0};
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
    pkr::units::meter_per_second_t v{5.0};
    auto result = v * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiVelocityTest, scalar_multiply_velocity)
{
    pkr::units::meter_per_second_t v{5.0};
    auto result = 3.0 * v;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiVelocityTest, divide_velocity_by_scalar)
{
    pkr::units::meter_per_second_t v{20.0};
    auto result = v / 4.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

// ============================================================================
// Comparison Operations
// ============================================================================

TEST_F(SiVelocityTest, equal_same_units)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2{5.0};
    ASSERT_TRUE(v1 == v2);
}

TEST_F(SiVelocityTest, not_equal_same_units)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2{10.0};
    ASSERT_TRUE(v1 != v2);
}

TEST_F(SiVelocityTest, less_than_same_units)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2{10.0};
    ASSERT_TRUE(v1 < v2);
}

TEST_F(SiVelocityTest, greater_than_same_units)
{
    pkr::units::meter_per_second_t v1{15.0};
    pkr::units::meter_per_second_t v2{10.0};
    ASSERT_TRUE(v1 > v2);
}

TEST_F(SiVelocityTest, less_than_or_equal_same_units)
{
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::meter_per_second_t v2{10.0};
    ASSERT_TRUE(v1 <= v2);
    
    pkr::units::meter_per_second_t v3{10.0};
    ASSERT_TRUE(v2 <= v3);
}

TEST_F(SiVelocityTest, greater_than_or_equal_same_units)
{
    pkr::units::meter_per_second_t v1{15.0};
    pkr::units::meter_per_second_t v2{10.0};
    ASSERT_TRUE(v1 >= v2);
    
    pkr::units::meter_per_second_t v3{10.0};
    ASSERT_TRUE(v2 >= v3);
}

TEST_F(SiVelocityTest, equal_different_units_same_value)
{
    // These have the same physical velocity but different stored values
    pkr::units::meter_per_second_t v_mps{1.0};
    pkr::units::centimeter_per_second v_cms{100.0};
    ASSERT_TRUE(v_mps == v_cms);
}

TEST_F(SiVelocityTest, less_than_different_units)
{
    // 5 m/s < 36 km/h (which is 10 m/s)
    pkr::units::meter_per_second_t v1{5.0};
    pkr::units::kilometer_per_hour v2{36.0};
    ASSERT_TRUE(v1 < v2);
}

TEST_F(SiVelocityTest, greater_than_different_units)
{
    // 20 m/s > 36 km/h (which is 10 m/s)
    pkr::units::meter_per_second_t v1{20.0};
    pkr::units::kilometer_per_hour v2{36.0};
    ASSERT_TRUE(v1 > v2);
}
