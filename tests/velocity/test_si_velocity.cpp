#include <gtest/gtest.h>
#include <format>
#include <pkr_units/units/derived/velocity.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/base/time.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;

class SiVelocityTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiVelocityTest, meter_per_second_construction)
{
    pkr::units::meter_per_second_t<double> v{5.0};
    ASSERT_DOUBLE_EQ(v.value(), 5.0);
}

TEST_F(SiVelocityTest, meter_per_second_dereference_operator)
{
    pkr::units::meter_per_second_t<double> v{5.0};
    ASSERT_DOUBLE_EQ(*v, 5.0);
}

TEST_F(SiVelocityTest, meter_per_second_zero_value)
{
    pkr::units::meter_per_second_t<double> v{0.0};
    ASSERT_DOUBLE_EQ(v.value(), 0.0);
}

TEST_F(SiVelocityTest, meter_per_second_negative_value)
{
    pkr::units::meter_per_second_t<double> v{-10.5};
    ASSERT_DOUBLE_EQ(v.value(), -10.5);
}

TEST_F(SiVelocityTest, kilometer_per_hour_construction)
{
    pkr::units::kilometer_per_hour_t<double> v{100.0};
    ASSERT_DOUBLE_EQ(v.value(), 100.0);
}

TEST_F(SiVelocityTest, centimeter_per_second_construction)
{
    pkr::units::centimeter_per_second_t<double> v{250.0};
    ASSERT_DOUBLE_EQ(v.value(), 250.0);
}

TEST_F(SiVelocityTest, millimeter_per_second_construction)
{
    pkr::units::millimeter_per_second_t<double> v{1000.0};
    ASSERT_DOUBLE_EQ(v.value(), 1000.0);
}

TEST_F(SiVelocityTest, kilometers_per_second_construction)
{
    pkr::units::kilometer_per_second_t<double> v{2.5};
    ASSERT_DOUBLE_EQ(v.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiVelocityTest, copy_constructor)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, move_constructor)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2 = std::move(v1);
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, copy_assignment)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2{0.0};
    v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

TEST_F(SiVelocityTest, move_assignment)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2{0.0};
    v2 = std::move(v1);
    ASSERT_DOUBLE_EQ(v2.value(), 5.0);
}

// ============================================================================
// Unit Conversion Tests (same-ratio units)
// ============================================================================

TEST_F(SiVelocityTest, meters_per_second_same_unit_identity)
{
    // Just verify we can create and use the same unit
    pkr::units::meter_per_second_t<double> v1{10.0};
    pkr::units::meter_per_second_t<double> v2 = v1;
    ASSERT_DOUBLE_EQ(v2.value(), 10.0);
}

// ============================================================================
// Unit Casting Tests (SI units only)
// ============================================================================

TEST_F(SiVelocityTest, cast_meter_per_second_to_kilometer_per_hour)
{
    // 10 m/s = 36 km/h
    pkr::units::meter_per_second_t<double> mps{10.0};
    auto kmh = pkr::units::unit_cast<pkr::units::kilometer_per_hour_t<double>>(mps);
    static_assert(std::is_same_v<decltype(kmh), pkr::units::kilometer_per_hour_t<double>>);
    ASSERT_DOUBLE_EQ(kmh.value(), 36.0);
}

TEST_F(SiVelocityTest, cast_kilometer_per_hour_to_meter_per_second)
{
    // 36 km/h = 10 m/s
    pkr::units::kilometer_per_hour_t<double> kmh{36.0};
    auto mps = pkr::units::unit_cast<pkr::units::meter_per_second_t<double>>(kmh);
    static_assert(std::is_same_v<decltype(mps), pkr::units::meter_per_second_t<double>>);
    ASSERT_DOUBLE_EQ(mps.value(), 10.0);
}

TEST_F(SiVelocityTest, cast_meter_per_second_to_centimeter_per_second)
{
    // 5 m/s = 500 cm/s
    pkr::units::meter_per_second_t<double> mps{5.0};
    auto cms = pkr::units::unit_cast<pkr::units::centimeter_per_second_t<double>>(mps);
    static_assert(std::is_same_v<decltype(cms), pkr::units::centimeter_per_second_t<double>>);
    ASSERT_DOUBLE_EQ(cms.value(), 500.0);
}

TEST_F(SiVelocityTest, cast_centimeter_per_second_to_meter_per_second)
{
    // 250 cm/s = 2.5 m/s
    pkr::units::centimeter_per_second_t<double> cms{250.0};
    auto mps = pkr::units::unit_cast<pkr::units::meter_per_second_t<double>>(cms);
    static_assert(std::is_same_v<decltype(mps), pkr::units::meter_per_second_t<double>>);
    ASSERT_DOUBLE_EQ(mps.value(), 2.5);
}

TEST_F(SiVelocityTest, cast_meter_per_second_to_kilometer_per_second)
{
    // 1000 m/s = 1 km/s
    pkr::units::meter_per_second_t<double> mps{1000.0};
    auto kms = pkr::units::unit_cast<pkr::units::kilometer_per_second_t<double>>(mps);
    static_assert(std::is_same_v<decltype(kms), pkr::units::kilometer_per_second_t<double>>);
    ASSERT_DOUBLE_EQ(kms.value(), 1.0);
}

// ============================================================================
// Arithmetic Operations - Addition and Subtraction
// ============================================================================

TEST_F(SiVelocityTest, add_same_units_meter_per_second)
{
    pkr::units::meter_per_second_t<double> v1{10.0};
    pkr::units::meter_per_second_t<double> v2{20.0};
    pkr::units::meter_per_second_t<double> result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 30.0);
}

TEST_F(SiVelocityTest, subtract_same_units_meter_per_second)
{
    pkr::units::meter_per_second_t<double> v1{30.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    pkr::units::meter_per_second_t<double> result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 20.0);
}

TEST_F(SiVelocityTest, add_different_ratio_units_returns_lhs_type)
{
    // kilometer_per_hour + meter_per_second -> kilometer_per_hour (LHS type)
    // 36 km/h + 10 m/s = 36 km/h + 36 km/h = 72 km/h
    pkr::units::kilometer_per_hour_t<double> v1{36.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    pkr::units::kilometer_per_hour_t<double> result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 72.0);
}

TEST_F(SiVelocityTest, add_different_ratio_units_opposite_order)
{
    // meter_per_second + kilometer_per_hour -> meter_per_second (LHS type)
    // 10 m/s + 36 km/h = 10 m/s + 10 m/s = 20 m/s
    pkr::units::meter_per_second_t<double> v1{10.0};
    pkr::units::kilometer_per_hour_t<double> v2{36.0};
    pkr::units::meter_per_second_t<double> result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 20.0);
}

TEST_F(SiVelocityTest, subtract_different_ratio_units_returns_lhs_type)
{
    // kilometer_per_hour - meter_per_second -> kilometer_per_hour (LHS type)
    // 72 km/h - 10 m/s = 72 km/h - 36 km/h = 36 km/h
    pkr::units::kilometer_per_hour_t<double> v1{72.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    pkr::units::kilometer_per_hour_t<double> result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 36.0);
}

TEST_F(SiVelocityTest, subtract_different_ratio_units_opposite_order)
{
    // meter_per_second - kilometer_per_hour -> meter_per_second (LHS type)
    // 20 m/s - 36 km/h = 20 m/s - 10 m/s = 10 m/s
    pkr::units::meter_per_second_t<double> v1{20.0};
    pkr::units::kilometer_per_hour_t<double> v2{36.0};
    pkr::units::meter_per_second_t<double> result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiVelocityTest, add_centimeter_and_meter_per_second)
{
    // 100 cm/s + 5 m/s = 1 m/s + 5 m/s = 6 m/s (result in m/s, LHS type)
    pkr::units::centimeter_per_second_t<double> v1{600.0}; // 6 m/s in cm/s
    pkr::units::meter_per_second_t<double> v2{5.0};
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
    pkr::units::meter_per_second_t<double> v{5.0};
    auto result = v * 2.0;
    static_assert(std::is_same_v<decltype(result), pkr::units::meter_per_second_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(SiVelocityTest, scalar_multiply_velocity)
{
    pkr::units::meter_per_second_t<double> v{5.0};
    auto result = v * 3.0;
    static_assert(std::is_same_v<decltype(result), pkr::units::meter_per_second_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiVelocityTest, scalar_lhs_multiply_velocity)
{
    pkr::units::meter_per_second_t<double> v{5.0};
    auto result = 3.0 * v;
    static_assert(std::is_same_v<decltype(result), pkr::units::meter_per_second_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiVelocityTest, divide_velocity_by_scalar)
{
    pkr::units::meter_per_second_t<double> v{20.0};
    auto result = v / 4.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

// ============================================================================
// Comparison Operations
// ============================================================================

TEST_F(SiVelocityTest, equal_same_units)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2{5.0};
    ASSERT_TRUE(v1 == v2);
}

TEST_F(SiVelocityTest, not_equal_same_units)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    ASSERT_TRUE(v1 != v2);
}

TEST_F(SiVelocityTest, less_than_same_units)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    ASSERT_TRUE(v1 < v2);
}

TEST_F(SiVelocityTest, greater_than_same_units)
{
    pkr::units::meter_per_second_t<double> v1{15.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    ASSERT_TRUE(v1 > v2);
}

TEST_F(SiVelocityTest, less_than_or_equal_same_units)
{
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    ASSERT_TRUE(v1 <= v2);

    pkr::units::meter_per_second_t<double> v3{10.0};
    ASSERT_TRUE(v2 <= v3);
}

TEST_F(SiVelocityTest, greater_than_or_equal_same_units)
{
    pkr::units::meter_per_second_t<double> v1{15.0};
    pkr::units::meter_per_second_t<double> v2{10.0};
    ASSERT_TRUE(v1 >= v2);

    pkr::units::meter_per_second_t<double> v3{10.0};
    ASSERT_TRUE(v2 >= v3);
}

TEST_F(SiVelocityTest, equal_different_units_same_value)
{
    // These have the same physical velocity but different stored values
    pkr::units::meter_per_second_t<double> v_mps{1.0};
    pkr::units::centimeter_per_second_t<double> v_cms{100.0};
    ASSERT_TRUE(v_mps == v_cms);
}

TEST_F(SiVelocityTest, less_than_different_units)
{
    // 5 m/s < 36 km/h (which is 10 m/s)
    pkr::units::meter_per_second_t<double> v1{5.0};
    pkr::units::kilometer_per_hour_t<double> v2{36.0};
    ASSERT_TRUE(v1 < v2);
}

TEST_F(SiVelocityTest, greater_than_different_units)
{
    // 20 m/s > 36 km/h (which is 10 m/s)
    pkr::units::meter_per_second_t<double> v1{20.0};
    pkr::units::kilometer_per_hour_t<double> v2{36.0};
    ASSERT_TRUE(v1 > v2);
}
