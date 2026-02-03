#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace pkr::units;

class SiAngleTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup code if needed
    }
};

// ============================================================================
// Radian Construction Tests
// ============================================================================

TEST_F(SiAngleTest, radian_construction)
{
    radian_t angle(3.14159);
    EXPECT_EQ(angle.value(), 3.14159);
}

TEST_F(SiAngleTest, radian_dereference_operator)
{
    radian_t angle(2.5);
    EXPECT_EQ(*angle, 2.5);
}

TEST_F(SiAngleTest, radian_zero_value)
{
    radian_t angle(0.0);
    EXPECT_EQ(angle.value(), 0.0);
}

TEST_F(SiAngleTest, radian_negative_value)
{
    radian_t angle(-1.57);
    EXPECT_EQ(angle.value(), -1.57);
}

// ============================================================================
// Degree Construction Tests
// ============================================================================

TEST_F(SiAngleTest, degree_construction)
{
    degree_t angle(180.0);
    EXPECT_EQ(angle.value(), 180.0);
}

TEST_F(SiAngleTest, degree_zero_value)
{
    degree_t angle(0.0);
    EXPECT_EQ(angle.value(), 0.0);
}

TEST_F(SiAngleTest, degree_negative_value)
{
    degree_t angle(-90.0);
    EXPECT_EQ(angle.value(), -90.0);
}

// ============================================================================
// Gradian Construction Tests
// ============================================================================

TEST_F(SiAngleTest, gradian_construction)
{
    gradian_t angle(200.0);
    EXPECT_EQ(angle.value(), 200.0);
}

TEST_F(SiAngleTest, gradian_zero_value)
{
    gradian_t angle(0.0);
    EXPECT_EQ(angle.value(), 0.0);
}

// ============================================================================
// Copy and Move Semantics
// ============================================================================

TEST_F(SiAngleTest, copy_constructor)
{
    radian_t angle1(1.5);
    radian_t angle2 = angle1;
    EXPECT_EQ(angle2.value(), 1.5);
}

TEST_F(SiAngleTest, move_constructor)
{
    radian_t angle1(2.0);
    radian_t angle2 = std::move(angle1);
    EXPECT_EQ(angle2.value(), 2.0);
}

TEST_F(SiAngleTest, copy_assignment)
{
    radian_t angle1(1.5);
    radian_t angle2(0.0);
    angle2 = angle1;
    EXPECT_EQ(angle2.value(), 1.5);
}

TEST_F(SiAngleTest, move_assignment)
{
    radian_t angle1(2.0);
    radian_t angle2(0.0);
    angle2 = std::move(angle1);
    EXPECT_EQ(angle2.value(), 2.0);
}

// ============================================================================
// Dimension Tests
// ============================================================================

TEST_F(SiAngleTest, radian_has_angle_dimension)
{
    radian_t angle(1.0);
    static_assert(decltype(angle)::dimension_type::value == angle_dimension);
    ASSERT_TRUE(true); // Compile-time check
}

// ============================================================================
// Scalar Operations
// ============================================================================

TEST_F(SiAngleTest, multiply_radian_by_scalar)
{
    radian_t angle(3.14159);
    auto result = angle * 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 6.28318);
}

TEST_F(SiAngleTest, divide_radian_by_scalar)
{
    radian_t angle(6.28318);
    auto result = angle / 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 3.14159);
}

TEST_F(SiAngleTest, multiply_degree_by_scalar)
{
    degree_t angle(180.0);
    auto result = angle * 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 360.0);
}

TEST_F(SiAngleTest, divide_degree_by_scalar)
{
    degree_t angle(360.0);
    auto result = angle / 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 180.0);
}

TEST_F(SiAngleTest, scalar_lhs_multiply_radian)
{
    radian_t angle(1.5);
    auto result = 2.0 * angle;
    EXPECT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Unit Angle Operations
// ============================================================================

TEST_F(SiAngleTest, multiply_radian_by_radian)
{
    radian_t angle1(2.0);
    radian_t angle2(3.0);
    // Multiplying two angles gives a dimensionless quantity with angle^2
    auto result = angle1 * angle2;
    EXPECT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiAngleTest, divide_radian_by_radian)
{
    radian_t angle1(6.0);
    radian_t angle2(2.0);
    // Dividing two angles gives a dimensionless quantity
    auto result = angle1 / angle2;
    EXPECT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiAngleTest, constexpr_radian_multiplication)
{
    constexpr radian_t angle(2.0);
    constexpr auto result = angle * 3.0;
    static_assert(result.value() == 6.0, "Constexpr multiplication failed");
}

// ============================================================================
// Large and Small Values
// ============================================================================

TEST_F(SiAngleTest, very_small_angle_values)
{
    radian_t angle(1e-10);
    EXPECT_EQ(angle.value(), 1e-10);
}

TEST_F(SiAngleTest, very_large_angle_values)
{
    radian_t angle(1e10);
    EXPECT_EQ(angle.value(), 1e10);
}

// ============================================================================
// Type Preservation Tests
// ============================================================================

TEST_F(SiAngleTest, scalar_multiply_radian_preserves_type)
{
    radian_t angle(3.14159);
    auto result = angle * 2.0;
    static_assert(std::is_same_v<decltype(result), radian_t<double>>, "Scalar multiplication should preserve radian_t type");
    EXPECT_DOUBLE_EQ(result.value(), 6.28318);
}

TEST_F(SiAngleTest, scalar_multiply_degree_preserves_type)
{
    degree_t angle(180.0);
    auto result = angle * 2.0;
    static_assert(std::is_same_v<decltype(result), degree_t<double>>, "Scalar multiplication should preserve degree_t type");
    EXPECT_DOUBLE_EQ(result.value(), 360.0);
}

TEST_F(SiAngleTest, scalar_multiply_gradian_preserves_type)
{
    gradian_t angle(200.0);
    auto result = angle * 2.0;
    static_assert(std::is_same_v<decltype(result), gradian_t<double>>, "Scalar multiplication should preserve gradian_t type");
    EXPECT_DOUBLE_EQ(result.value(), 400.0);
}
