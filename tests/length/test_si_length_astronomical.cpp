#include <gtest/gtest.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/astronomical_units.h>

namespace test
{

using namespace ::testing;

class SiLengthAstronomicalTest : public Test
{
};

// ============================================================================
// Astronomical Units Tests
// ============================================================================

TEST_F(SiLengthAstronomicalTest, astronomical_unit_construction)
{
    pkr::units::au_t au_dist{1.0};
    ASSERT_DOUBLE_EQ(au_dist.value(), 1.0);
}

TEST_F(SiLengthAstronomicalTest, light_year_construction)
{
    pkr::units::light_year_t ly{2.0};
    ASSERT_DOUBLE_EQ(ly.value(), 2.0);
}

TEST_F(SiLengthAstronomicalTest, parsec_construction)
{
    pkr::units::parsec_t pc{10.0};
    ASSERT_DOUBLE_EQ(pc.value(), 10.0);
}

// ============================================================================
// Astronomical Unit Literals Tests
// ============================================================================

// using namespace pkr::units::si_literals;

/*
TEST_F(SiLengthAstronomicalTest, angstrom_literal)
{
    auto angstrom = 1.0_angstrom;
    ASSERT_NEAR(angstrom.value(), 1.0, 1e-10);
}

TEST_F(SiLengthAstronomicalTest, astronomical_unit_literal)
{
    auto au = 1.5_au;
    ASSERT_NEAR(au.value(), 1.5, 1e-10);
}
*/

} // namespace test
