#include <gtest/gtest.h>
#include <pkr_units/units/derived/mechanical/force.h>

using namespace ::testing;

class ForceTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(ForceTest, newton_construction)
{
    pkr::units::newton_t<double> force{100.0};
    ASSERT_DOUBLE_EQ(force.value(), 100.0);
}

TEST_F(ForceTest, newton_dereference_operator)
{
    pkr::units::newton_t<double> force{100.0};
    ASSERT_DOUBLE_EQ(*force, 100.0);
}

TEST_F(ForceTest, newton_zero_value)
{
    pkr::units::newton_t<double> force{0.0};
    ASSERT_DOUBLE_EQ(force.value(), 0.0);
}

TEST_F(ForceTest, newton_negative_value)
{
    pkr::units::newton_t<double> force{-50.0};
    ASSERT_DOUBLE_EQ(force.value(), -50.0);
}

TEST_F(ForceTest, kilonewton_construction)
{
    pkr::units::kilonewton_t<double> force{5.0};
    ASSERT_DOUBLE_EQ(force.value(), 5.0);
}

TEST_F(ForceTest, meganewton_construction)
{
    pkr::units::meganewton_t<double> force{2.0};
    ASSERT_DOUBLE_EQ(force.value(), 2.0);
}

TEST_F(ForceTest, millinewton_construction)
{
    pkr::units::millinewton_t<double> force{50000.0};
    ASSERT_DOUBLE_EQ(force.value(), 50000.0);
}

TEST_F(ForceTest, micronewton_construction)
{
    pkr::units::micronewton_t<double> force{100000000.0};
    ASSERT_DOUBLE_EQ(force.value(), 100000000.0);
}

TEST_F(ForceTest, nanonewton_construction)
{
    pkr::units::nanonewton_t<double> force{100000000000.0};
    ASSERT_DOUBLE_EQ(force.value(), 100000000000.0);
}

TEST_F(ForceTest, copy_constructor)
{
    pkr::units::newton_t<double> force1{100.0};
    pkr::units::newton_t<double> force2{force1};
    ASSERT_DOUBLE_EQ(force2.value(), 100.0);
}

TEST_F(ForceTest, move_constructor)
{
    pkr::units::newton_t<double> force1{100.0};
    pkr::units::newton_t<double> force2{std::move(force1)};
    ASSERT_DOUBLE_EQ(force2.value(), 100.0);
}

TEST_F(ForceTest, copy_assignment)
{
    pkr::units::newton_t<double> force1{100.0};
    pkr::units::newton_t<double> force2{0.0};
    force2 = force1;
    ASSERT_DOUBLE_EQ(force2.value(), 100.0);
}

TEST_F(ForceTest, move_assignment)
{
    pkr::units::newton_t<double> force1{100.0};
    pkr::units::newton_t<double> force2{0.0};
    force2 = std::move(force1);
    ASSERT_DOUBLE_EQ(force2.value(), 100.0);
}

TEST_F(ForceTest, force_has_correct_dimension)
{
    pkr::units::newton_t<double> force{1.0};
    using dimension = typename std::decay_t<decltype(force)>::dimension_type;
    static_assert(dimension::value == pkr::units::force_dimension);
    ASSERT_TRUE(true); // Compile-time check
}

TEST_F(ForceTest, very_small_values)
{
    pkr::units::nanonewton_t<double> force{1e-12};
    ASSERT_DOUBLE_EQ(force.value(), 1e-12);
}

TEST_F(ForceTest, very_large_values)
{
    pkr::units::meganewton_t<double> force{1e6};
    ASSERT_DOUBLE_EQ(force.value(), 1e6);
}
