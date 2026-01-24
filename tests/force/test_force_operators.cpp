#include <gtest/gtest.h>
#include <pkr_units/units/derived/mechanical/force.h>

using namespace ::testing;

class ForceOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations Tests
// ============================================================================

TEST_F(ForceOperatorsTest, add_forces)
{
    pkr::units::newton force1{50.0};
    pkr::units::newton force2{30.0};
    auto result = force1 + force2;
    ASSERT_DOUBLE_EQ(result.value(), 80.0);
}

TEST_F(ForceOperatorsTest, subtract_forces)
{
    pkr::units::newton force1{100.0};
    pkr::units::newton force2{30.0};
    auto result = force1 - force2;
    ASSERT_DOUBLE_EQ(result.value(), 70.0);
}

TEST_F(ForceOperatorsTest, multiply_force_by_scalar)
{
    pkr::units::newton force{50.0};
    auto result = force * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

TEST_F(ForceOperatorsTest, divide_force_by_scalar)
{
    pkr::units::newton force{100.0};
    auto result = force / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 50.0);
}

TEST_F(ForceOperatorsTest, divide_by_zero_scalar_throws)
{
    pkr::units::newton force{100.0};
    EXPECT_THROW(force / 0.0, std::runtime_error);
}

TEST_F(ForceOperatorsTest, multiply_force_by_zero)
{
    pkr::units::newton force{50.0};
    auto result = force * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(ForceOperatorsTest, multiply_force_by_fraction)
{
    pkr::units::newton force{100.0};
    auto result = force * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 50.0);
}

TEST_F(ForceOperatorsTest, equal_forces)
{
    pkr::units::newton force1{100.0};
    pkr::units::newton force2{100.0};
    ASSERT_TRUE(force1 == force2);
}

TEST_F(ForceOperatorsTest, not_equal_forces)
{
    pkr::units::newton force1{100.0};
    pkr::units::newton force2{50.0};
    ASSERT_TRUE(force1 != force2);
}

TEST_F(ForceOperatorsTest, less_than_forces)
{
    pkr::units::newton force1{50.0};
    pkr::units::newton force2{100.0};
    ASSERT_TRUE(force1 < force2);
}

TEST_F(ForceOperatorsTest, less_than_or_equal_forces)
{
    pkr::units::newton force1{50.0};
    pkr::units::newton force2{50.0};
    ASSERT_TRUE(force1 <= force2);
    pkr::units::newton force3{30.0};
    ASSERT_TRUE(force3 <= force1);
}

TEST_F(ForceOperatorsTest, greater_than_forces)
{
    pkr::units::newton force1{100.0};
    pkr::units::newton force2{50.0};
    ASSERT_TRUE(force1 > force2);
}

TEST_F(ForceOperatorsTest, greater_than_or_equal_forces)
{
    pkr::units::newton force1{50.0};
    pkr::units::newton force2{50.0};
    ASSERT_TRUE(force1 >= force2);
    pkr::units::newton force3{70.0};
    ASSERT_TRUE(force3 >= force1);
}

TEST_F(ForceOperatorsTest, constexpr_force_addition)
{
    constexpr pkr::units::newton force1{50.0};
    constexpr pkr::units::newton force2{30.0};
    constexpr auto result = force1 + force2;
    static_assert(result.value() == 80.0);
    ASSERT_DOUBLE_EQ(result.value(), 80.0);
}

TEST_F(ForceOperatorsTest, constexpr_force_multiplication_and_division)
{
    constexpr pkr::units::newton force{100.0};
    constexpr auto result = force * 2.0 / 4.0;
    static_assert(result.value() == 50.0);
    ASSERT_DOUBLE_EQ(result.value(), 50.0);
}

TEST_F(ForceOperatorsTest, scalar_rhs_multiply_force)
{
    pkr::units::newton force{50.0};
    auto result = 2.0 * force;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

TEST_F(ForceOperatorsTest, scalar_rhs_divide_force)
{
    pkr::units::newton force{100.0};
    auto result = 200.0 / force;
    // This should result in 1/force (per newton)
    ASSERT_DOUBLE_EQ(result.value(), 2.0);
}

TEST_F(ForceOperatorsTest, add_to)
{
    pkr::units::newton force{50.0};
    force += pkr::units::newton{30.0};
    ASSERT_DOUBLE_EQ(force.value(), 80.0);
}

TEST_F(ForceOperatorsTest, constexpr_add_to)
{
    constexpr pkr::units::newton force1{50.0};
    constexpr pkr::units::newton force2{30.0};
    constexpr auto result = force1 + force2;
    static_assert(result.value() == 80.0);
    ASSERT_DOUBLE_EQ(result.value(), 80.0);
}