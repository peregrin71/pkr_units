#include <gtest/gtest.h>
#include <pkr_units/units/imperial/velocity.h>

using namespace ::testing;

class ImperialVelocityTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(ImperialVelocityTest, miles_per_hour_construction)
{
    pkr::units::miles_per_hour_t<double> v{60.0};
    ASSERT_DOUBLE_EQ(v.value(), 60.0);
}

TEST_F(ImperialVelocityTest, feet_per_second_construction)
{
    pkr::units::feet_per_second_t<double> v{100.0};
    ASSERT_DOUBLE_EQ(v.value(), 100.0);
}

TEST_F(ImperialVelocityTest, knots_construction)
{
    pkr::units::knots_t<double> v{20.0};
    ASSERT_DOUBLE_EQ(v.value(), 20.0);
}
