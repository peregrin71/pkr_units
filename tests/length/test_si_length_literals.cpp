#include <gtest/gtest.h>
#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/literals/length.h>
#include <pkr_units/literals/imperial_length.h>

class SiLengthLiteralsTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// ============================================================================
// Metric Length Literals Tests
// ============================================================================

using namespace pkr::units::literals;

TEST_F(SiLengthLiteralsTest, meter_literal)
{
    auto meter = 5.0_m;
    ASSERT_DOUBLE_EQ(meter.value(), 5.0);
}

TEST_F(SiLengthLiteralsTest, kilometer_literal)
{
    auto km = 2.5_km;
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthLiteralsTest, centimeter_literal)
{
    auto cm = 100.0_cm;
    ASSERT_DOUBLE_EQ(cm.value(), 100.0);
}

TEST_F(SiLengthLiteralsTest, millimeter_literal)
{
    auto mm = 500.0_mm;
    ASSERT_DOUBLE_EQ(mm.value(), 500.0);
}

TEST_F(SiLengthLiteralsTest, micrometer_literal)
{
    auto um = 1000.0_um;
    ASSERT_DOUBLE_EQ(um.value(), 1000.0);
}

TEST_F(SiLengthLiteralsTest, nanometer_literal)
{
    auto nm = 1e6_nm;
    ASSERT_DOUBLE_EQ(nm.value(), 1e6);
}

TEST_F(SiLengthLiteralsTest, picometer_literal)
{
    auto pm = 1e9_pm;
    ASSERT_DOUBLE_EQ(pm.value(), 1e9);
}

TEST_F(SiLengthLiteralsTest, femtometer_literal)
{
    auto fm = 1e12_fm;
    ASSERT_DOUBLE_EQ(fm.value(), 1e12);
}

TEST_F(SiLengthLiteralsTest, attometer_literal)
{
    auto am = 1e15_am;
    ASSERT_DOUBLE_EQ(am.value(), 1e15);
}

TEST_F(SiLengthLiteralsTest, decimeter_literal)
{
    auto dm = 10.0_dm;
    ASSERT_DOUBLE_EQ(dm.value(), 10.0);
}

TEST_F(SiLengthLiteralsTest, megameter_literal)
{
    auto Mm = 1.0_Mm;
    ASSERT_DOUBLE_EQ(Mm.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, gigameter_literal)
{
    auto Gm = 1.0_Gm;
    ASSERT_DOUBLE_EQ(Gm.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, terameter_literal)
{
    auto Tm = 1.0_Tm;
    ASSERT_DOUBLE_EQ(Tm.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, petameter_literal)
{
    auto Pm = 1.0_Pm;
    ASSERT_DOUBLE_EQ(Pm.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, exameter_literal)
{
    auto Em = 1.0_Em;
    ASSERT_DOUBLE_EQ(Em.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, angstrom_literal)
{
    auto angstrom = 1.0_angstrom;
    ASSERT_DOUBLE_EQ(angstrom.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, au_literal)
{
    auto au = 1.0_au;
    ASSERT_DOUBLE_EQ(au.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, light_year_literal)
{
    auto ly = 1.0_ly;
    ASSERT_DOUBLE_EQ(ly.value(), 1.0);
}

TEST_F(SiLengthLiteralsTest, parsec_literal)
{
    auto pc = 1.0_pc;
    ASSERT_DOUBLE_EQ(pc.value(), 1.0);
}

// ============================================================================
// Imperial Length Literals Tests
// ============================================================================

TEST_F(SiLengthLiteralsTest, inch_literal)
{
    auto inch = 12.0_in;
    ASSERT_DOUBLE_EQ(inch.value(), 12.0);
}

TEST_F(SiLengthLiteralsTest, foot_literal)
{
    auto ft = 3.0_ft;
    ASSERT_DOUBLE_EQ(ft.value(), 3.0);
}

TEST_F(SiLengthLiteralsTest, yard_literal)
{
    auto yd = 2.0_yd;
    ASSERT_DOUBLE_EQ(yd.value(), 2.0);
}

TEST_F(SiLengthLiteralsTest, mil_literal)
{
    auto mil = 1000.0_mi;
    ASSERT_DOUBLE_EQ(mil.value(), 1000.0);
}
