#include <gtest/gtest.h>
#include <pkr_units/units/derived/acceleration.h>

using namespace ::testing;

class AccelerationOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations Tests
// ============================================================================

TEST_F(AccelerationOperatorsTest, add_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{5.0};
    pkr::units::meter_per_second_squared_t accel2{3.0};
    auto result = accel1 + accel2;
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}

TEST_F(AccelerationOperatorsTest, subtract_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{10.0};
    pkr::units::meter_per_second_squared_t accel2{3.0};
    auto result = accel1 - accel2;
    ASSERT_DOUBLE_EQ(result.value(), 7.0);
}

TEST_F(AccelerationOperatorsTest, multiply_acceleration_by_scalar)
{
    pkr::units::meter_per_second_squared_t accel{5.0};
    auto result = accel * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(AccelerationOperatorsTest, divide_acceleration_by_scalar)
{
    pkr::units::meter_per_second_squared_t accel{10.0};
    auto result = accel / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(AccelerationOperatorsTest, multiply_acceleration_by_zero)
{
    pkr::units::meter_per_second_squared_t accel{5.0};
    auto result = accel * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(AccelerationOperatorsTest, multiply_acceleration_by_fraction)
{
    pkr::units::meter_per_second_squared_t accel{10.0};
    auto result = accel * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(AccelerationOperatorsTest, equal_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{9.81};
    pkr::units::meter_per_second_squared_t accel2{9.81};
    ASSERT_TRUE(accel1 == accel2);
}

TEST_F(AccelerationOperatorsTest, not_equal_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{9.81};
    pkr::units::meter_per_second_squared_t accel2{10.0};
    ASSERT_TRUE(accel1 != accel2);
}

TEST_F(AccelerationOperatorsTest, less_than_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{5.0};
    pkr::units::meter_per_second_squared_t accel2{10.0};
    ASSERT_TRUE(accel1 < accel2);
}

TEST_F(AccelerationOperatorsTest, less_than_or_equal_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{5.0};
    pkr::units::meter_per_second_squared_t accel2{5.0};
    ASSERT_TRUE(accel1 <= accel2);
    pkr::units::meter_per_second_squared_t accel3{3.0};
    ASSERT_TRUE(accel3 <= accel1);
}

TEST_F(AccelerationOperatorsTest, greater_than_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{10.0};
    pkr::units::meter_per_second_squared_t accel2{5.0};
    ASSERT_TRUE(accel1 > accel2);
}

TEST_F(AccelerationOperatorsTest, greater_than_or_equal_accelerations)
{
    pkr::units::meter_per_second_squared_t accel1{5.0};
    pkr::units::meter_per_second_squared_t accel2{5.0};
    ASSERT_TRUE(accel1 >= accel2);
    pkr::units::meter_per_second_squared_t accel3{7.0};
    ASSERT_TRUE(accel3 >= accel1);
}

TEST_F(AccelerationOperatorsTest, constexpr_acceleration_addition)
{
    constexpr pkr::units::meter_per_second_squared_t accel1{5.0};
    constexpr pkr::units::meter_per_second_squared_t accel2{3.0};
    constexpr auto result = accel1 + accel2;
    static_assert(result.value() == 8.0);
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}

TEST_F(AccelerationOperatorsTest, constexpr_acceleration_multiplication_and_division)
{
    constexpr pkr::units::meter_per_second_squared_t accel{10.0};
    constexpr auto result = accel * 2.0 / 4.0;
    static_assert(result.value() == 5.0);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(AccelerationOperatorsTest, scalar_rhs_multiply_acceleration)
{
    pkr::units::meter_per_second_squared_t accel{5.0};
    auto result = 2.0 * accel;
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
}

TEST_F(AccelerationOperatorsTest, scalar_rhs_divide_acceleration)
{
    pkr::units::meter_per_second_squared_t accel{10.0};
    auto result = 20.0 / accel;
    // This should result in 1/acceleration (per m/s²)
    ASSERT_DOUBLE_EQ(result.value(), 2.0);
}

TEST_F(AccelerationOperatorsTest, add_to)
{
    pkr::units::meter_per_second_squared_t accel{5.0};
    accel += pkr::units::meter_per_second_squared_t{3.0};
    ASSERT_DOUBLE_EQ(accel.value(), 8.0);
}

TEST_F(AccelerationOperatorsTest, constexpr_add_to)
{
    constexpr pkr::units::meter_per_second_squared_t accel1{5.0};
    constexpr pkr::units::meter_per_second_squared_t accel2{3.0};
    constexpr auto result = accel1 + accel2;
    static_assert(result.value() == 8.0);
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}