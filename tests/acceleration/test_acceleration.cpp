#include <gtest/gtest.h>
#include <pkr_units/units/derived/acceleration.h>

using namespace ::testing;

class AccelerationTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(AccelerationTest, meter_per_second_squared_construction)
{
    pkr::units::meter_per_second_squared_t accel{9.81};
    ASSERT_DOUBLE_EQ(accel.value(), 9.81);
}

TEST_F(AccelerationTest, meter_per_second_squared_dereference_operator)
{
    pkr::units::meter_per_second_squared_t accel{9.81};
    ASSERT_DOUBLE_EQ(*accel, 9.81);
}

TEST_F(AccelerationTest, meter_per_second_squared_zero_value)
{
    pkr::units::meter_per_second_squared_t accel{0.0};
    ASSERT_DOUBLE_EQ(accel.value(), 0.0);
}

TEST_F(AccelerationTest, meter_per_second_squared_negative_value)
{
    pkr::units::meter_per_second_squared_t accel{-5.0};
    ASSERT_DOUBLE_EQ(accel.value(), -5.0);
}

TEST_F(AccelerationTest, centimeter_per_second_squared_construction)
{
    pkr::units::centimeter_per_second_squared_t accel{981.0};
    ASSERT_DOUBLE_EQ(accel.value(), 981.0);
}

TEST_F(AccelerationTest, millimeter_per_second_squared_construction)
{
    pkr::units::millimeter_per_second_squared_t accel{9810.0};
    ASSERT_DOUBLE_EQ(accel.value(), 9810.0);
}

TEST_F(AccelerationTest, kilometer_per_second_squared_construction)
{
    pkr::units::kilometer_per_second_squared_t accel{0.00981};
    ASSERT_DOUBLE_EQ(accel.value(), 0.00981);
}

TEST_F(AccelerationTest, standard_gravity_construction)
{
    pkr::units::standard_gravity_t accel{1.0};
    ASSERT_DOUBLE_EQ(accel.value(), 1.0);
}

TEST_F(AccelerationTest, copy_constructor)
{
    pkr::units::meter_per_second_squared_t accel1{9.81};
    pkr::units::meter_per_second_squared_t accel2{accel1};
    ASSERT_DOUBLE_EQ(accel2.value(), 9.81);
}

TEST_F(AccelerationTest, move_constructor)
{
    pkr::units::meter_per_second_squared_t accel1{9.81};
    pkr::units::meter_per_second_squared_t accel2{std::move(accel1)};
    ASSERT_DOUBLE_EQ(accel2.value(), 9.81);
}

TEST_F(AccelerationTest, copy_assignment)
{
    pkr::units::meter_per_second_squared_t accel1{9.81};
    pkr::units::meter_per_second_squared_t accel2{0.0};
    accel2 = accel1;
    ASSERT_DOUBLE_EQ(accel2.value(), 9.81);
}

TEST_F(AccelerationTest, move_assignment)
{
    pkr::units::meter_per_second_squared_t accel1{9.81};
    pkr::units::meter_per_second_squared_t accel2{0.0};
    accel2 = std::move(accel1);
    ASSERT_DOUBLE_EQ(accel2.value(), 9.81);
}

TEST_F(AccelerationTest, acceleration_has_correct_dimension)
{
    pkr::units::meter_per_second_squared_t accel{1.0};
    using dimension = typename std::decay_t<decltype(accel)>::dimension_type;
    ASSERT_EQ(dimension::value, pkr::units::acceleration_v);
}

TEST_F(AccelerationTest, very_small_values)
{
    pkr::units::meter_per_second_squared_t accel{1e-10};
    ASSERT_DOUBLE_EQ(accel.value(), 1e-10);
}

TEST_F(AccelerationTest, very_large_values)
{
    pkr::units::meter_per_second_squared_t accel{1e10};
    ASSERT_DOUBLE_EQ(accel.value(), 1e10);
}
