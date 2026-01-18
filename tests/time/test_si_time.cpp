#include <gtest/gtest.h>
#include <pkr_units/standard/time.h>

using namespace ::testing;

class SiTimeTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiTimeTest, second_construction)
{
    pkr::units::second_t s{5.0};
    ASSERT_DOUBLE_EQ(s.value(), 5.0);
}

TEST_F(SiTimeTest, second_dereference_operator)
{
    pkr::units::second_t s{5.0};
    ASSERT_DOUBLE_EQ(*s, 5.0);
}

TEST_F(SiTimeTest, second_zero_value)
{
    pkr::units::second_t s{0.0};
    ASSERT_DOUBLE_EQ(s.value(), 0.0);
}

TEST_F(SiTimeTest, second_negative_value)
{
    pkr::units::second_t s{-3.5};
    ASSERT_DOUBLE_EQ(s.value(), -3.5);
}

TEST_F(SiTimeTest, millisecond_construction)
{
    pkr::units::millisecond_t ms{250.0};
    ASSERT_DOUBLE_EQ(ms.value(), 250.0);
}

TEST_F(SiTimeTest, microsecond_construction)
{
    pkr::units::microsecond_t us{1000.0};
    ASSERT_DOUBLE_EQ(us.value(), 1000.0);
}

TEST_F(SiTimeTest, nanosecond_construction)
{
    pkr::units::nanosecond_t ns{100.0};
    ASSERT_DOUBLE_EQ(ns.value(), 100.0);
}

TEST_F(SiTimeTest, kilosecond_construction)
{
    pkr::units::kilosecond_t ks{2.5};
    ASSERT_DOUBLE_EQ(ks.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiTimeTest, copy_constructor)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2 = s1;
    ASSERT_DOUBLE_EQ(s2.value(), 5.0);
}

TEST_F(SiTimeTest, move_constructor)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2 = std::move(s1);
    ASSERT_DOUBLE_EQ(s2.value(), 5.0);
}

TEST_F(SiTimeTest, copy_assignment)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{0.0};
    s2 = s1;
    ASSERT_DOUBLE_EQ(s2.value(), 5.0);
}

TEST_F(SiTimeTest, move_assignment)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{0.0};
    s2 = std::move(s1);
    ASSERT_DOUBLE_EQ(s2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiTimeTest, add_seconds)
{
    pkr::units::second_t s1{3.0};
    pkr::units::second_t s2{2.0};
    auto result = s1 + s2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTimeTest, subtract_seconds)
{
    pkr::units::second_t s1{5.0};
    pkr::units::second_t s2{2.0};
    auto result = s1 - s2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTimeTest, add_milliseconds)
{
    pkr::units::millisecond_t ms1{500.0};
    pkr::units::millisecond_t ms2{250.0};
    auto result = ms1 + ms2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiTimeTest, subtract_milliseconds)
{
    pkr::units::millisecond_t ms1{750.0};
    pkr::units::millisecond_t ms2{250.0};
    auto result = ms1 - ms2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiTimeTest, add_second_to_millisecond)
{
    pkr::units::second_t s{1.0};
    pkr::units::millisecond_t ms{500.0};
    auto result = s + ms;
    // Result is in LHS type (second)
    // 1s + 0.5s = 1.5s
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiTimeTest, add_millisecond_to_second)
{
    pkr::units::millisecond_t ms{500.0};
    pkr::units::second_t s{1.0};
    auto result = ms + s;
    // Result is in LHS type (millisecond)
    // 500ms + 1000ms = 1500ms
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiTimeTest, subtract_second_from_millisecond)
{
    pkr::units::millisecond_t ms{1500.0};
    pkr::units::second_t s{1.0};
    auto result = ms - s;
    // Result is in LHS type (millisecond)
    // 1500ms - 1000ms = 500ms
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiTimeTest, subtract_millisecond_from_second)
{
    pkr::units::second_t s{2.0};
    pkr::units::millisecond_t ms{500.0};
    auto result = s - ms;
    // Result is in LHS type (second)
    // 2s - 0.5s = 1.5s
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication and Division
// ============================================================================

TEST_F(SiTimeTest, multiply_second_by_scalar)
{
    pkr::units::second_t s{2.0};
    auto result = s * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiTimeTest, divide_second_by_scalar)
{
    pkr::units::second_t s{6.0};
    auto result = s / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTimeTest, divide_by_zero_scalar_throws)
{
    pkr::units::second_t s{5.0};
    ASSERT_THROW(s / 0.0, std::invalid_argument);
}

TEST_F(SiTimeTest, multiply_millisecond_by_scalar)
{
    pkr::units::millisecond_t ms{100.0};
    auto result = ms * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiTimeTest, divide_millisecond_by_scalar)
{
    pkr::units::millisecond_t ms{500.0};
    auto result = ms / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Time Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiTimeTest, multiply_second_by_second)
{
    pkr::units::second_t s1{2.0};
    pkr::units::second_t s2{3.0};
    auto result = s1 * s2;
    // Result has time dimension = 2 (s²)
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.time, 2);
}

// ============================================================================
// Time Division (Creates Dimensionless)
// ============================================================================

TEST_F(SiTimeTest, divide_second_by_second)
{
    pkr::units::second_t s1{10.0};
    pkr::units::second_t s2{2.0};
    auto result = s1 / s2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.time, 0);
}

TEST_F(SiTimeTest, divide_millisecond_by_millisecond)
{
    pkr::units::millisecond_t ms1{500.0};
    pkr::units::millisecond_t ms2{100.0};
    auto result = ms1 / ms2;
    // Result is dimensionless
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.time, 0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiTimeTest, constexpr_second_addition)
{
    constexpr pkr::units::second_t s1{3.0};
    constexpr pkr::units::second_t s2{2.0};
    constexpr auto result = s1 + s2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTimeTest, constexpr_second_multiplication)
{
    constexpr pkr::units::second_t s{2.0};
    constexpr auto result = s * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiTimeTest, very_small_time_values)
{
    pkr::units::nanosecond_t ns{0.001};
    ASSERT_DOUBLE_EQ(ns.value(), 0.001);
}

TEST_F(SiTimeTest, very_large_time_values)
{
    pkr::units::kilosecond_t ks{1000000.0};
    ASSERT_DOUBLE_EQ(ks.value(), 1000000.0);
}

TEST_F(SiTimeTest, add_very_different_scales)
{
    pkr::units::millisecond_t ms{1.0};    // 1 millisecond
    pkr::units::second_t s{1.0};          // 1 second = 1000 ms
    auto result = ms + s;
    // Result is in LHS type (millisecond)
    // 1 ms + 1000 ms = 1001 ms
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiTimeTest, subtract_resulting_in_negative)
{
    pkr::units::second_t s1{1.0};
    pkr::units::second_t s2{3.0};
    auto result = s1 - s2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}



