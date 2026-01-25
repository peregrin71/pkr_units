#include <gtest/gtest.h>
#include <pkr_units/units/derived/acceleration.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;

class AccelerationCastTest : public Test
{
};

// ============================================================================
// Unit Conversion via unit_cast
// ============================================================================

TEST_F(AccelerationCastTest, cast_meter_per_second_squared_to_centimeter_per_second_squared)
{
    pkr::units::meter_per_second_squared_t mps2{9.81};
    auto cmps2 = pkr::units::unit_cast<pkr::units::centimeter_per_second_squared_t>(mps2);
    static_assert(std::is_same_v<decltype(cmps2), pkr::units::centimeter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(cmps2.value(), 981.0);
}

TEST_F(AccelerationCastTest, cast_centimeter_per_second_squared_to_meter_per_second_squared)
{
    pkr::units::centimeter_per_second_squared_t cmps2{981.0};
    auto mps2 = pkr::units::unit_cast<pkr::units::meter_per_second_squared_t>(cmps2);
    static_assert(std::is_same_v<decltype(mps2), pkr::units::meter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(mps2.value(), 9.81);
}

TEST_F(AccelerationCastTest, cast_meter_per_second_squared_to_millimeter_per_second_squared)
{
    pkr::units::meter_per_second_squared_t mps2{9.81};
    auto mmps2 = pkr::units::unit_cast<pkr::units::millimeter_per_second_squared_t>(mps2);
    static_assert(std::is_same_v<decltype(mmps2), pkr::units::millimeter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(mmps2.value(), 9810.0);
}

TEST_F(AccelerationCastTest, cast_millimeter_per_second_squared_to_meter_per_second_squared)
{
    pkr::units::millimeter_per_second_squared_t mmps2{9810.0};
    auto mps2 = pkr::units::unit_cast<pkr::units::meter_per_second_squared_t>(mmps2);
    static_assert(std::is_same_v<decltype(mps2), pkr::units::meter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(mps2.value(), 9.81);
}

TEST_F(AccelerationCastTest, cast_meter_per_second_squared_to_kilometer_per_second_squared)
{
    pkr::units::meter_per_second_squared_t mps2{9.81};
    auto kmps2 = pkr::units::unit_cast<pkr::units::kilometer_per_second_squared_t>(mps2);
    static_assert(std::is_same_v<decltype(kmps2), pkr::units::kilometer_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(kmps2.value(), 0.00981);
}

TEST_F(AccelerationCastTest, cast_kilometer_per_second_squared_to_meter_per_second_squared)
{
    pkr::units::kilometer_per_second_squared_t kmps2{0.00981};
    auto mps2 = pkr::units::unit_cast<pkr::units::meter_per_second_squared_t>(kmps2);
    static_assert(std::is_same_v<decltype(mps2), pkr::units::meter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(mps2.value(), 9.81);
}

TEST_F(AccelerationCastTest, cast_meter_per_second_squared_to_standard_gravity)
{
    pkr::units::meter_per_second_squared_t mps2{9.80665};
    auto g = pkr::units::unit_cast<pkr::units::standard_gravity_t>(mps2);
    static_assert(std::is_same_v<decltype(g), pkr::units::standard_gravity_t>);
    ASSERT_DOUBLE_EQ(g.value(), 1.0);
}

TEST_F(AccelerationCastTest, cast_standard_gravity_to_meter_per_second_squared)
{
    pkr::units::standard_gravity_t g{1.0};
    auto mps2 = pkr::units::unit_cast<pkr::units::meter_per_second_squared_t>(g);
    static_assert(std::is_same_v<decltype(mps2), pkr::units::meter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(mps2.value(), 9.80665);
}

TEST_F(AccelerationCastTest, cast_centimeter_per_second_squared_to_millimeter_per_second_squared)
{
    pkr::units::centimeter_per_second_squared_t cmps2{50.0};
    auto mmps2 = pkr::units::unit_cast<pkr::units::millimeter_per_second_squared_t>(cmps2);
    static_assert(std::is_same_v<decltype(mmps2), pkr::units::millimeter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(mmps2.value(), 500.0);
}

TEST_F(AccelerationCastTest, cast_millimeter_per_second_squared_to_centimeter_per_second_squared)
{
    pkr::units::millimeter_per_second_squared_t mmps2{500.0};
    auto cmps2 = pkr::units::unit_cast<pkr::units::centimeter_per_second_squared_t>(mmps2);
    static_assert(std::is_same_v<decltype(cmps2), pkr::units::centimeter_per_second_squared_t>);
    ASSERT_DOUBLE_EQ(cmps2.value(), 50.0);
}

// ============================================================================
// Edge Cases and Precision Tests
// ============================================================================

TEST_F(AccelerationCastTest, cast_zero_acceleration)
{
    pkr::units::meter_per_second_squared_t mps2{0.0};
    auto cmps2 = pkr::units::unit_cast<pkr::units::centimeter_per_second_squared_t>(mps2);
    ASSERT_DOUBLE_EQ(cmps2.value(), 0.0);
}

TEST_F(AccelerationCastTest, cast_negative_acceleration)
{
    pkr::units::meter_per_second_squared_t mps2{-9.81};
    auto cmps2 = pkr::units::unit_cast<pkr::units::centimeter_per_second_squared_t>(mps2);
    ASSERT_DOUBLE_EQ(cmps2.value(), -981.0);
}

TEST_F(AccelerationCastTest, cast_very_small_acceleration)
{
    pkr::units::meter_per_second_squared_t mps2{1e-9};
    auto cmps2 = pkr::units::unit_cast<pkr::units::centimeter_per_second_squared_t>(mps2);
    ASSERT_DOUBLE_EQ(cmps2.value(), 1e-7);
}

TEST_F(AccelerationCastTest, cast_very_large_acceleration)
{
    pkr::units::meter_per_second_squared_t mps2{1e9};
    auto cmps2 = pkr::units::unit_cast<pkr::units::centimeter_per_second_squared_t>(mps2);
    ASSERT_DOUBLE_EQ(cmps2.value(), 1e11);
}

TEST_F(AccelerationCastTest, round_trip_conversion)
{
    pkr::units::meter_per_second_squared_t original{123.456};
    auto cmps2 = pkr::units::unit_cast<pkr::units::centimeter_per_second_squared_t>(original);
    auto back = pkr::units::unit_cast<pkr::units::meter_per_second_squared_t>(cmps2);
    ASSERT_DOUBLE_EQ(back.value(), original.value());
}

