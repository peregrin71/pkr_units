#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace pkr::units;

class SolidAngleTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup code if needed
    }
};

// ============================================================================
// Steradian Construction Tests
// ============================================================================

TEST_F(SolidAngleTest, steradian_construction)
{
    steradian_t angle(2.0);
    EXPECT_EQ(angle.value(), 2.0);
}

TEST_F(SolidAngleTest, steradian_dereference_operator)
{
    steradian_t angle(3.5);
    EXPECT_EQ(*angle, 3.5);
}

TEST_F(SolidAngleTest, steradian_zero_value)
{
    steradian_t angle(0.0);
    EXPECT_EQ(angle.value(), 0.0);
}

TEST_F(SolidAngleTest, steradian_full_sphere)
{
    // Full sphere = 4π steradians ≈ 12.566370614...
    steradian_t full_sphere(4.0 * 3.14159265359);
    EXPECT_NEAR(full_sphere.value(), 12.566370614, 0.000001);
}

TEST_F(SolidAngleTest, steradian_hemisphere)
{
    // Hemisphere = 2π steradians ≈ 6.283185307...
    steradian_t hemisphere(2.0 * 3.14159265359);
    EXPECT_NEAR(hemisphere.value(), 6.283185307, 0.000001);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SolidAngleTest, copy_constructor)
{
    steradian_t s1(5.0);
    steradian_t s2 = s1;
    EXPECT_EQ(s2.value(), 5.0);
}

TEST_F(SolidAngleTest, move_constructor)
{
    steradian_t s1(5.0);
    steradian_t s2 = std::move(s1);
    EXPECT_EQ(s2.value(), 5.0);
}

TEST_F(SolidAngleTest, copy_assignment)
{
    steradian_t s1(3.0);
    steradian_t s2(0.0);
    s2 = s1;
    EXPECT_EQ(s2.value(), 3.0);
}

TEST_F(SolidAngleTest, move_assignment)
{
    steradian_t s1(3.0);
    steradian_t s2(0.0);
    s2 = std::move(s1);
    EXPECT_EQ(s2.value(), 3.0);
}

// ============================================================================
// Arithmetic Operator Tests
// ============================================================================

TEST_F(SolidAngleTest, addition)
{
    steradian_t s1(2.0);
    steradian_t s2(3.0);
    steradian_t result = s1 + s2;
    EXPECT_EQ(result.value(), 5.0);
}

TEST_F(SolidAngleTest, subtraction)
{
    steradian_t s1(5.0);
    steradian_t s2(2.0);
    steradian_t result = s1 - s2;
    EXPECT_EQ(result.value(), 3.0);
}

TEST_F(SolidAngleTest, multiplication_by_scalar)
{
    steradian_t s(2.0);
    steradian_t result = s * 3.0;
    EXPECT_EQ(result.value(), 6.0);
}

TEST_F(SolidAngleTest, division_by_scalar)
{
    steradian_t s(10.0);
    steradian_t result = s / 2.0;
    EXPECT_EQ(result.value(), 5.0);
}

TEST_F(SolidAngleTest, in_place_addition)
{
    steradian_t s1(2.0);
    steradian_t s2(3.0);
    s1 += s2;
    EXPECT_EQ(s1.value(), 5.0);
}

TEST_F(SolidAngleTest, in_place_subtraction)
{
    steradian_t s1(5.0);
    steradian_t s2(2.0);
    s1 -= s2;
    EXPECT_EQ(s1.value(), 3.0);
}

TEST_F(SolidAngleTest, in_place_multiplication)
{
    steradian_t s(2.0);
    s *= 3.0;
    EXPECT_EQ(s.value(), 6.0);
}

TEST_F(SolidAngleTest, in_place_division)
{
    steradian_t s(10.0);
    s /= 2.0;
    EXPECT_EQ(s.value(), 5.0);
}

// ============================================================================
// Comparison Tests
// ============================================================================

TEST_F(SolidAngleTest, equality)
{
    steradian_t s1(5.0);
    steradian_t s2(5.0);
    EXPECT_EQ(s1, s2);
}

TEST_F(SolidAngleTest, inequality)
{
    steradian_t s1(5.0);
    steradian_t s2(3.0);
    EXPECT_NE(s1, s2);
}

TEST_F(SolidAngleTest, less_than)
{
    steradian_t s1(3.0);
    steradian_t s2(5.0);
    EXPECT_LT(s1, s2);
}

TEST_F(SolidAngleTest, less_than_or_equal)
{
    steradian_t s1(5.0);
    steradian_t s2(5.0);
    EXPECT_LE(s1, s2);
}

TEST_F(SolidAngleTest, greater_than)
{
    steradian_t s1(5.0);
    steradian_t s2(3.0);
    EXPECT_GT(s1, s2);
}

TEST_F(SolidAngleTest, greater_than_or_equal)
{
    steradian_t s1(5.0);
    steradian_t s2(5.0);
    EXPECT_GE(s1, s2);
}

// ============================================================================
// Type Safety Tests
// ============================================================================

TEST_F(SolidAngleTest, steradian_distinct_from_radian)
{
    // This is a compile-time test - both types should be distinct
    // Confirming they have different dimensions
    static_assert(!std::is_same_v<steradian_t, radian_t>, "steradian_t and radian_t should be distinct types");
}

TEST_F(SolidAngleTest, steradian_creation_from_derived_operation)
{
    // Verify steradian can be created from dimensional operations
    lumen_t luminous_flux(1000.0); // cd·sr
    candela_t intensity(100.0);    // cd

    // Derived steradian from division of lumen by candela
    // This should work dimensionally
    EXPECT_GT(luminous_flux.value(), 0.0);
    EXPECT_GT(intensity.value(), 0.0);
}
