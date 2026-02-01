#include <gtest/gtest.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/base/mass.h>

using namespace ::testing;

class ArithmeticOptimizationsTest : public Test
{
};

// This file verifies *internal* arithmetic optimization behavior that isn't
// covered by the per-dimension operator tests. We keep only tests that assert
// non-trivial ratio math (std::ratio_multiply/std::ratio_divide) and special
// identity cases where product/division yields a non-obvious ratio.

TEST_F(ArithmeticOptimizationsTest, multiply_non_unit_ratios_kilometers)
{
    // k m * k m -> ratio multiplication: 1000/1 * 1000/1 = 1000000/1
    pkr::units::kilometer_t km1{2.0};
    pkr::units::kilometer_t km2{3.0};
    auto result = km1 * km2;

    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 2);
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, multiply_non_unit_ratios_millimeter_kilometer)
{
    // mm * km -> 1/1000 * 1000/1 = 1/1 (identity)
    pkr::units::millimeter_t mm{1000.0};
    pkr::units::kilometer_t km{1.0};
    auto result = mm * km;

    ASSERT_DOUBLE_EQ(result.value(), 1000.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 2);
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, divide_different_ratio_meter_by_kilometer)
{
    // m / km -> 1/1 / 1000/1 = 1/1000
    pkr::units::meter_t m{1000.0};
    pkr::units::kilometer_t km{1.0};
    auto result = m / km;

    ASSERT_DOUBLE_EQ(result.value(), 1000.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1000);
}

TEST_F(ArithmeticOptimizationsTest, divide_different_ratio_kilometer_by_millimeter)
{
    // km / mm -> 1000/1 / 1/1000 = 1000000/1
    pkr::units::kilometer_t km{1.0};
    pkr::units::millimeter_t mm{1.0};
    auto result = km / mm;

    ASSERT_DOUBLE_EQ(result.value(), 1.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

// End: keep tests focused on optimization math rather than duplicating
// per-dimension operator behavior.
