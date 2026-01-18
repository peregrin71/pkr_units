#include <gtest/gtest.h>
#include <pkr_units/standard/intensity.h>

using namespace ::testing;

class SiIntensityOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiIntensityOperatorsTest, add_candelas)
{
    pkr::units::candela_t cd1{3.0};
    pkr::units::candela_t cd2{2.0};
    auto result = cd1 + cd2;
    static_assert(std::is_same_v<decltype(result), pkr::units::candela_t>);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiIntensityOperatorsTest, add_millicandela_to_candela)
{
    pkr::units::millicandela_t mcd{500.0};
    pkr::units::candela_t cd{1.0};
    auto result = mcd + cd;
    static_assert(std::is_same_v<decltype(result), pkr::units::millicandela_t>);
    // Result is in canonical unit (millicandela), so 1cd = 1000mcd, result = 1500mcd
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiIntensityOperatorsTest, add_candela_to_millicandela)
{
    pkr::units::candela_t cd{1.0};
    pkr::units::millicandela_t mcd{500.0};
    auto result = cd + mcd;
    static_assert(std::is_same_v<decltype(result), pkr::units::candela_t>);
    // Result is in LHS unit (candela), so 500mcd = 0.5cd, result = 1.5cd
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiIntensityOperatorsTest, subtract_candelas)
{
    pkr::units::candela_t cd1{5.0};
    pkr::units::candela_t cd2{2.0};
    auto result = cd1 - cd2;
    static_assert(std::is_same_v<decltype(result), pkr::units::candela_t>);
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiIntensityOperatorsTest, subtract_millicandela_from_candela)
{
    pkr::units::candela_t cd{1.0};
    pkr::units::millicandela_t mcd{500.0};
    auto result = cd - mcd;
    static_assert(std::is_same_v<decltype(result), pkr::units::candela_t>);
    // 1cd - 500mcd = 1000mcd - 500mcd = 500mcd = 0.5cd
    ASSERT_DOUBLE_EQ(result.value(), 0.5);
}

TEST_F(SiIntensityOperatorsTest, subtract_candela_from_millicandela)
{
    pkr::units::millicandela_t mcd{1500.0};
    pkr::units::candela_t cd{1.0};
    auto result = mcd - cd;
    static_assert(std::is_same_v<decltype(result), pkr::units::millicandela_t>);
    // 1500mcd - 1000mcd = 500mcd
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Multiplication/Division by Scalar
// ============================================================================

TEST_F(SiIntensityOperatorsTest, multiply_candela_by_scalar)
{
    pkr::units::candela_t cd{5.0};
    auto result = cd * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiIntensityOperatorsTest, divide_candela_by_scalar)
{
    pkr::units::candela_t cd{10.0};
    auto result = cd / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiIntensityOperatorsTest, divide_by_zero_scalar_throws)
{
    pkr::units::candela_t cd{10.0};
    ASSERT_THROW(cd / 0.0, std::invalid_argument);
}

TEST_F(SiIntensityOperatorsTest, divide_by_zero_si_unit_throws)
{
    pkr::units::candela_t cd1{10.0};
    pkr::units::candela_t cd2{0.0};
    ASSERT_THROW(cd1 / cd2, std::invalid_argument);
}

TEST_F(SiIntensityOperatorsTest, multiply_candela_by_zero)
{
    pkr::units::candela_t cd{5.0};
    auto result = cd * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiIntensityOperatorsTest, multiply_candela_by_fraction)
{
    pkr::units::candela_t cd{6.0};
    auto result = cd * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Comparison Operators
// ============================================================================

TEST_F(SiIntensityOperatorsTest, equal_candelas)
{
    pkr::units::candela_t cd1{5.0};
    pkr::units::candela_t cd2{5.0};
    ASSERT_TRUE(cd1 == cd2);
}

TEST_F(SiIntensityOperatorsTest, not_equal_candelas)
{
    pkr::units::candela_t cd1{5.0};
    pkr::units::candela_t cd2{3.0};
    ASSERT_TRUE(cd1 != cd2);
}

TEST_F(SiIntensityOperatorsTest, less_than_candelas)
{
    pkr::units::candela_t cd1{3.0};
    pkr::units::candela_t cd2{5.0};
    ASSERT_TRUE(cd1 < cd2);
}

TEST_F(SiIntensityOperatorsTest, less_than_or_equal_candelas)
{
    pkr::units::candela_t cd1{5.0};
    pkr::units::candela_t cd2{5.0};
    ASSERT_TRUE(cd1 <= cd2);
}

TEST_F(SiIntensityOperatorsTest, greater_than_candelas)
{
    pkr::units::candela_t cd1{5.0};
    pkr::units::candela_t cd2{3.0};
    ASSERT_TRUE(cd1 > cd2);
}

TEST_F(SiIntensityOperatorsTest, greater_than_or_equal_candelas)
{
    pkr::units::candela_t cd1{5.0};
    pkr::units::candela_t cd2{5.0};
    ASSERT_TRUE(cd1 >= cd2);
}

// ============================================================================
// Constexpr Operations
// ============================================================================

TEST_F(SiIntensityOperatorsTest, constexpr_candela_addition)
{
    constexpr pkr::units::candela_t cd1{3.0};
    constexpr pkr::units::candela_t cd2{2.0};
    constexpr auto result = cd1 + cd2;
    static_assert(result.value() == 5.0);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiIntensityOperatorsTest, constexpr_candela_multiplication_and_division)
{
    constexpr pkr::units::candela_t cd{10.0};
    constexpr auto multiplied = cd * 2.0;
    constexpr auto divided = multiplied / 5.0;
    static_assert(divided.value() == 4.0);
    ASSERT_DOUBLE_EQ(divided.value(), 4.0);
}

