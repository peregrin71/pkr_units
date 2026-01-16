// Copyright (c) 2026 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#include <gtest/gtest.h>
#include <units/impl/length.h>
#include <units/cast/si_cast.h>

namespace test
{

using namespace ::testing;

class SiLengthCastTest : public Test
{
};

// ============================================================================
// Unit Conversion via si_cast
// ============================================================================

TEST_F(SiLengthCastTest, cast_meter_to_kilometer)
{
    si::meter m{5000.0};
    auto km = si::si_cast<si::kilometer>(m);
    ASSERT_DOUBLE_EQ(km.value(), 5.0);
}

TEST_F(SiLengthCastTest, cast_kilometer_to_meter)
{
    si::kilometer km{2.5};
    auto m = si::si_cast<si::meter>(km);
    ASSERT_DOUBLE_EQ(m.value(), 2500.0);
}

TEST_F(SiLengthCastTest, cast_millimeter_to_meter)
{
    si::millimeter mm{5000.0};
    auto m = si::si_cast<si::meter>(mm);
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
}

TEST_F(SiLengthCastTest, cast_meter_to_millimeter)
{
    si::meter m{5.0};
    auto mm = si::si_cast<si::millimeter>(m);
    ASSERT_DOUBLE_EQ(mm.value(), 5000.0);
}

TEST_F(SiLengthCastTest, cast_kilometer_to_millimeter)
{
    si::kilometer km{1.0};
    auto mm = si::si_cast<si::millimeter>(km);
    ASSERT_DOUBLE_EQ(mm.value(), 1000000.0);
}

TEST_F(SiLengthCastTest, cast_kilometer_to_ratio_must_not_compile)
{
    si::kilometer km{1.0};
    MUST_NOT_COMPILE(si::si_cast<std::milli>(km));
}

TEST_F(SiLengthCastTest, foot_to_meter_conversion)
{
    // 1 foot = 0.3048 meter
    si::foot ft{1.0};
    ASSERT_NEAR(ft.value() * (3048.0 / 10000.0), 0.3048, 1e-10);

    auto meter = si::si_cast<si::meter>(ft);
    ASSERT_NEAR(meter.value(), 0.3048, 1e-10);
}

} // namespace test
