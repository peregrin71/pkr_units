#include <gtest/gtest.h>
#include <pkr_units/si_units.h>
#include <pkr_units/imperial_units.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/impl/literals/literals.h>

class SiLengthLiteralsTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Metric Length Literals Tests
// ============================================================================

using namespace si::si_literals;

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
    auto mil = 1000.0_mil;
    ASSERT_DOUBLE_EQ(mil.value(), 1000.0);
}