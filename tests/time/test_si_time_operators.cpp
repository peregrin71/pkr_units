#include <gtest/gtest.h>
#include <pkr_units/standard/time.h>

using namespace ::testing;

class SiTimeOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiTimeOperatorsTest, add_seconds)
{
    pkr::units::second_t s1{3.0};
    pkr::units::second_t s2{2.0};
    auto result = s1 + s2;
    static_assert(std::is_same_v<decltype(result), pkr::units::second_t>);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTimeOperatorsTest, add_millisecond_to_second)
{
    pkr::units::millisecond_t ms{500.0};
    pkr::units::second_t s{1.0};
    auto result = ms + s;
    static_assert(std::is_same_v<decltype(result), pkr::units::millisecond_t>);
    // Result is in canonical unit (millisecond), so 1s = 1000ms, result = 1500ms
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiTimeOperatorsTest, add_second_to_millisecond)
{
    pkr::units::second_t s{1.0};
    pkr::units::millisecond_t ms{500.0};
    auto result = s + ms;
    static_assert(std::is_same_v<decltype(result), pkr::units::second_t>);
    // Result is in LHS unit (second), so 500ms = 0.5s, result = 1.5s
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiTimeOperatorsTest, subtract_seconds)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{2.0};
    auto result = s1 - s2;
    static_assert(std::is_same_v<decltype(result), pkr::units::second_t>);
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTimeOperatorsTest, subtract_millisecond_from_second)
{
    pkr::units::second_t s{1.0};
    pkr::units::millisecond_t ms{500.0};
    auto result = s - ms;
    static_assert(std::is_same_v<decltype(result), pkr::units::second_t>);
    // 1s - 500ms = 1000ms - 500ms = 500ms = 0.5s
    ASSERT_DOUBLE_EQ(result.value(), 0.5);
}

TEST_F(SiTimeOperatorsTest, subtract_second_from_millisecond)
{
    pkr::units::millisecond_t ms{1500.0};
    pkr::units::second_t s{1.0};
    auto result = ms - s;
    static_assert(std::is_same_v<decltype(result), pkr::units::millisecond_t>);
    // 1500ms - 1000ms = 500ms
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Multiplication/Division by Scalar
// ============================================================================

TEST_F(SiTimeOperatorsTest, multiply_second_by_scalar)
{
    pkr::units::second_t s{5.0};
    auto result = s * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiTimeOperatorsTest, divide_second_by_scalar)
{
    pkr::units::second_t s{10.0};
    auto result = s / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTimeOperatorsTest, divide_by_zero_scalar_throws)
{
    pkr::units::second_t s{10.0};
    ASSERT_THROW(s / 0.0, std::invalid_argument);
}

TEST_F(SiTimeOperatorsTest, divide_by_zero_si_unit_throws)
{
    pkr::units::second_t s1{10.0};
    pkr::units::second_t s2{0.0};
    ASSERT_THROW(s1 / s2, std::invalid_argument);
}

TEST_F(SiTimeOperatorsTest, multiply_second_by_zero)
{
    pkr::units::second_t s{5.0};
    auto result = s * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiTimeOperatorsTest, multiply_second_by_fraction)
{
    pkr::units::second_t s{6.0};
    auto result = s * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Comparison Operators
// ============================================================================

TEST_F(SiTimeOperatorsTest, equal_seconds)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{5.0};
    ASSERT_TRUE(s1 == s2);
}

TEST_F(SiTimeOperatorsTest, not_equal_seconds)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{3.0};
    ASSERT_TRUE(s1 != s2);
}

TEST_F(SiTimeOperatorsTest, less_than_seconds)
{
    pkr::units::second_t s1{3.0};
    pkr::units::second_t s2{5.0};
    ASSERT_TRUE(s1 < s2);
}

TEST_F(SiTimeOperatorsTest, less_than_or_equal_seconds)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{5.0};
    ASSERT_TRUE(s1 <= s2);
}

TEST_F(SiTimeOperatorsTest, greater_than_seconds)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{3.0};
    ASSERT_TRUE(s1 > s2);
}

TEST_F(SiTimeOperatorsTest, greater_than_or_equal_seconds)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{5.0};
    ASSERT_TRUE(s1 >= s2);
}

// ============================================================================
// Constexpr Operations
// ============================================================================

TEST_F(SiTimeOperatorsTest, constexpr_second_addition)
{
    constexpr pkr::units::second_t s1{3.0};
    constexpr pkr::units::second_t s2{2.0};
    constexpr auto result = s1 + s2;
    static_assert(result.value() == 5.0);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTimeOperatorsTest, constexpr_second_multiplication_and_division)
{
    constexpr pkr::units::second_t s{10.0};
    constexpr auto multiplied = s * 2.0;
    constexpr auto divided = multiplied / 5.0;
    static_assert(divided.value() == 4.0);
    ASSERT_DOUBLE_EQ(divided.value(), 4.0);
}

