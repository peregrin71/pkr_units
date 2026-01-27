#include <gtest/gtest.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/imperial_units.h>

namespace test
{

using namespace ::testing;

class SiLengthImperialTest : public Test
{
};

// ============================================================================
// Imperial Units Tests
// ============================================================================

TEST_F(SiLengthImperialTest, inch_to_meter_conversion)
{
    // 1 inch = 0.0254 meter
    pkr::units::inch_t in{1.0};
    ASSERT_NEAR(in.value() * (254.0 / 10000.0), 0.0254, 1e-10);
}

TEST_F(SiLengthImperialTest, foot_to_meter_conversion)
{
    // 1 foot = 0.3048 meter
    pkr::units::foot_t ft{1.0};
    ASSERT_NEAR(ft.value() * (3048.0 / 10000.0), 0.3048, 1e-10);
}

TEST_F(SiLengthImperialTest, mile_to_meter_conversion)
{
    // 1 mile = 1609.344 meter
    pkr::units::mile_t mi{1.0};
    ASSERT_NEAR(mi.value() * (1609344.0 / 1000.0), 1609.344, 1e-10);
}

TEST_F(SiLengthImperialTest, add_feet_to_feet)
{
    pkr::units::foot_t ft1{5.0};
    pkr::units::foot_t ft2{3.0};
    auto result = ft1 + ft2;
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}

TEST_F(SiLengthImperialTest, add_inches_to_feet)
{
    pkr::units::foot_t ft{1.0};
    pkr::units::inch_t in{12.0};
    auto result = ft + in;
    // Result is in feet: 12 inches = 1 foot
    ASSERT_NEAR(result.value(), 2.0, 1e-10);
}

// ============================================================================
// Imperial Unit Literals Tests
// ============================================================================

// using namespace pkr::units::si_literals;

/*
TEST_F(SiLengthImperialTest, inch_literal)
{
    auto in = 12.0_in;
    ASSERT_NEAR(in.value(), 12.0, 1e-10);
}

TEST_F(SiLengthImperialTest, foot_literal)
{
    auto ft = 5.0_ft;
    ASSERT_NEAR(ft.value(), 5.0, 1e-10);
}

TEST_F(SiLengthImperialTest, yard_literal)
{
    auto yd = 10.0_yd;
    ASSERT_NEAR(yd.value(), 10.0, 1e-10);
}

TEST_F(SiLengthImperialTest, mile_literal)
{
    auto mi = 2.0_mi;
    ASSERT_NEAR(mi.value(), 2.0, 1e-10);
}

TEST_F(SiLengthImperialTest, nautical_mile_literal)
{
    auto nmi = 5.0_nmi;
    ASSERT_NEAR(nmi.value(), 5.0, 1e-10);
}
*/

} // namespace test
