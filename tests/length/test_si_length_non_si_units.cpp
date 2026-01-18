#include <gtest/gtest.h>
#include <pkr_units/standard/length.h>

namespace test
{

using namespace ::testing;

class SiLengthNonSiUnitsTest : public Test
{
};

// ============================================================================
// Imperial Units Tests
// ============================================================================

TEST_F(SiLengthNonSiUnitsTest, inch_to_meter_conversion)
{
    // 1 inch = 0.0254 meter
    pkr::units::inch_t in{1.0};
    ASSERT_NEAR(in.value() * (254.0 / 10000.0), 0.0254, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, foot_to_meter_conversion)
{
    // 1 foot = 0.3048 meter
    pkr::units::foot_t ft{1.0};
    ASSERT_NEAR(ft.value() * (3048.0 / 10000.0), 0.3048, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, mile_to_meter_conversion)
{
    // 1 mile = 1609.344 meter
    pkr::units::mile_t mi{1.0};
    ASSERT_NEAR(mi.value() * (1609344.0 / 1000.0), 1609.344, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, add_feet_to_feet)
{
    pkr::units::foot_t ft1{5.0};
    pkr::units::foot_t ft2{3.0};
    auto result = ft1 + ft2;
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}

TEST_F(SiLengthNonSiUnitsTest, add_inches_to_feet)
{
    pkr::units::foot_t ft{1.0};
    pkr::units::inch_t in{12.0};
    auto result = ft + in;
    // Result is in feet: 12 inches = 1 foot
    ASSERT_NEAR(result.value(), 2.0, 1e-10);
}

// ============================================================================
// Astronomical Units Tests
// ============================================================================

TEST_F(SiLengthNonSiUnitsTest, astronomical_unit_construction)
{
    pkr::units::au_t au_dist{1.0};
    ASSERT_DOUBLE_EQ(au_dist.value(), 1.0);
}

TEST_F(SiLengthNonSiUnitsTest, light_year_construction)
{
    pkr::units::light_year_t ly{2.0};
    ASSERT_DOUBLE_EQ(ly.value(), 2.0);
}

TEST_F(SiLengthNonSiUnitsTest, parsec_construction)
{
    pkr::units::parsec_t pc{10.0};
    ASSERT_DOUBLE_EQ(pc.value(), 10.0);
}

// ============================================================================
// Non-SI Unit Literals Tests
// ============================================================================

using namespace pkr::units::si_literals;

TEST_F(SiLengthNonSiUnitsTest, inch_literal)
{
    auto in = 12.0_in;
    ASSERT_NEAR(in.value(), 12.0, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, foot_literal)
{
    auto ft = 5.0_ft;
    ASSERT_NEAR(ft.value(), 5.0, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, yard_literal)
{
    auto yd = 10.0_yd;
    ASSERT_NEAR(yd.value(), 10.0, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, mile_literal)
{
    auto mi = 2.0_mi;
    ASSERT_NEAR(mi.value(), 2.0, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, nautical_mile_literal)
{
    auto nmi = 5.0_nmi;
    ASSERT_NEAR(nmi.value(), 5.0, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, angstrom_literal)
{
    auto angstrom = 1.0_angstrom;
    ASSERT_NEAR(angstrom.value(), 1.0, 1e-10);
}

TEST_F(SiLengthNonSiUnitsTest, astronomical_unit_literal)
{
    auto au = 1.5_au;
    ASSERT_NEAR(au.value(), 1.5, 1e-10);
}

} // namespace test



