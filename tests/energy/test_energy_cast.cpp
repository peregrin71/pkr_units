#include <gtest/gtest.h>
#include <pkr_units/units/derived/mechanical/energy.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;

class EnergyCastTest : public Test
{
};

// ============================================================================
// Unit Conversion via unit_cast
// ============================================================================

TEST_F(EnergyCastTest, cast_joule_to_kilojoule)
{
    pkr::units::joule j{5000.0};
    auto kj = pkr::units::unit_cast<pkr::units::kilojoule>(j);
    static_assert(std::is_same_v<decltype(kj), pkr::units::kilojoule>);
    ASSERT_DOUBLE_EQ(kj.value(), 5.0);
}

TEST_F(EnergyCastTest, cast_kilojoule_to_joule)
{
    pkr::units::kilojoule kj{2.5};
    auto j = pkr::units::unit_cast<pkr::units::joule>(kj);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 2500.0);
}

TEST_F(EnergyCastTest, cast_joule_to_megajoule)
{
    pkr::units::joule j{2000000.0};
    auto mj = pkr::units::unit_cast<pkr::units::megajoule>(j);
    static_assert(std::is_same_v<decltype(mj), pkr::units::megajoule>);
    ASSERT_DOUBLE_EQ(mj.value(), 2.0);
}

TEST_F(EnergyCastTest, cast_megajoule_to_joule)
{
    pkr::units::megajoule mj{2.0};
    auto j = pkr::units::unit_cast<pkr::units::joule>(mj);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 2000000.0);
}

TEST_F(EnergyCastTest, cast_joule_to_gigajoule)
{
    pkr::units::joule j{1500000000.0};
    auto gj = pkr::units::unit_cast<pkr::units::gigajoule>(j);
    static_assert(std::is_same_v<decltype(gj), pkr::units::gigajoule>);
    ASSERT_DOUBLE_EQ(gj.value(), 1.5);
}

TEST_F(EnergyCastTest, cast_gigajoule_to_joule)
{
    pkr::units::gigajoule gj{1.5};
    auto j = pkr::units::unit_cast<pkr::units::joule>(gj);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 1500000000.0);
}

TEST_F(EnergyCastTest, cast_joule_to_millijoule)
{
    pkr::units::joule j{5.0};
    auto mj = pkr::units::unit_cast<pkr::units::millijoule>(j);
    static_assert(std::is_same_v<decltype(mj), pkr::units::millijoule>);
    ASSERT_DOUBLE_EQ(mj.value(), 5000.0);
}

TEST_F(EnergyCastTest, cast_millijoule_to_joule)
{
    pkr::units::millijoule mj{5000.0};
    auto j = pkr::units::unit_cast<pkr::units::joule>(mj);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 5.0);
}

TEST_F(EnergyCastTest, cast_joule_to_microjoule)
{
    pkr::units::joule j{0.001};
    auto uj = pkr::units::unit_cast<pkr::units::microjoule>(j);
    static_assert(std::is_same_v<decltype(uj), pkr::units::microjoule>);
    ASSERT_DOUBLE_EQ(uj.value(), 1000.0);
}

TEST_F(EnergyCastTest, cast_microjoule_to_joule)
{
    pkr::units::microjoule uj{1000000.0};
    auto j = pkr::units::unit_cast<pkr::units::joule>(uj);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 1.0);
}

TEST_F(EnergyCastTest, cast_joule_to_calorie)
{
    pkr::units::joule j{4184.0};
    auto cal = pkr::units::unit_cast<pkr::units::calorie>(j);
    static_assert(std::is_same_v<decltype(cal), pkr::units::calorie>);
    ASSERT_DOUBLE_EQ(cal.value(), 1000.0);
}

TEST_F(EnergyCastTest, cast_calorie_to_joule)
{
    pkr::units::calorie cal{1000.0};
    auto j = pkr::units::unit_cast<pkr::units::joule>(cal);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 4184.0);
}

TEST_F(EnergyCastTest, cast_joule_to_kilocalorie)
{
    pkr::units::joule j{4184.0};
    auto kcal = pkr::units::unit_cast<pkr::units::kilocalorie>(j);
    static_assert(std::is_same_v<decltype(kcal), pkr::units::kilocalorie>);
    ASSERT_DOUBLE_EQ(kcal.value(), 1.0);
}

TEST_F(EnergyCastTest, cast_kilocalorie_to_joule)
{
    pkr::units::kilocalorie kcal{1.0};
    auto j = pkr::units::unit_cast<pkr::units::joule>(kcal);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 4184.0);
}

TEST_F(EnergyCastTest, cast_joule_to_watthour)
{
    pkr::units::joule j{3600.0};
    auto wh = pkr::units::unit_cast<pkr::units::watthour>(j);
    static_assert(std::is_same_v<decltype(wh), pkr::units::watthour>);
    ASSERT_DOUBLE_EQ(wh.value(), 1.0);
}

TEST_F(EnergyCastTest, cast_watthour_to_joule)
{
    pkr::units::watthour wh{1.0};
    auto j = pkr::units::unit_cast<pkr::units::joule>(wh);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 3600.0);
}

TEST_F(EnergyCastTest, cast_joule_to_kilowatthour)
{
    pkr::units::joule j{3600000.0};
    auto kwh = pkr::units::unit_cast<pkr::units::kilowatthour>(j);
    static_assert(std::is_same_v<decltype(kwh), pkr::units::kilowatthour>);
    ASSERT_DOUBLE_EQ(kwh.value(), 1.0);
}

TEST_F(EnergyCastTest, cast_kilowatthour_to_joule)
{
    pkr::units::kilowatthour kwh{1.0};
    auto j = pkr::units::unit_cast<pkr::units::joule>(kwh);
    static_assert(std::is_same_v<decltype(j), pkr::units::joule>);
    ASSERT_DOUBLE_EQ(j.value(), 3600000.0);
}

// ============================================================================
// Edge Cases and Precision Tests
// ============================================================================

TEST_F(EnergyCastTest, cast_zero_energy)
{
    pkr::units::joule j{0.0};
    auto kj = pkr::units::unit_cast<pkr::units::kilojoule>(j);
    ASSERT_DOUBLE_EQ(kj.value(), 0.0);
}

TEST_F(EnergyCastTest, cast_negative_energy)
{
    pkr::units::joule j{-1000.0};
    auto kj = pkr::units::unit_cast<pkr::units::kilojoule>(j);
    ASSERT_DOUBLE_EQ(kj.value(), -1.0);
}

TEST_F(EnergyCastTest, cast_very_small_energy)
{
    pkr::units::electronvolt ev{1e-20};
    auto j = pkr::units::unit_cast<pkr::units::joule>(ev);
    // Very small value, just check it's not zero
    ASSERT_LT(j.value(), 1e-30);
    ASSERT_GT(j.value(), 0.0);
}

TEST_F(EnergyCastTest, cast_very_large_energy)
{
    pkr::units::gigajoule gj{1e9};
    auto j = pkr::units::unit_cast<pkr::units::joule>(gj);
    ASSERT_DOUBLE_EQ(j.value(), 1e18);
}

TEST_F(EnergyCastTest, round_trip_conversion)
{
    pkr::units::joule original{1234.567};
    auto kj = pkr::units::unit_cast<pkr::units::kilojoule>(original);
    auto back = pkr::units::unit_cast<pkr::units::joule>(kj);
    ASSERT_DOUBLE_EQ(back.value(), original.value());
}
