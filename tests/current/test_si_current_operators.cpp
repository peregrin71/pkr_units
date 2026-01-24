#include <gtest/gtest.h>
#include <pkr_units/units/base/current.h>

using namespace ::testing;

class SiCurrentOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiCurrentOperatorsTest, add_amperes)
{
    pkr::units::ampere_t a1{3.0};
    pkr::units::ampere_t a2{2.0};
    auto result = a1 + a2;
    static_assert(std::is_same_v<decltype(result), pkr::units::ampere_t>);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiCurrentOperatorsTest, add_milliampere_to_ampere)
{
    pkr::units::milliampere_t ma{500.0};
    pkr::units::ampere_t a{1.0};
    auto result = ma + a;
    static_assert(std::is_same_v<decltype(result), pkr::units::milliampere_t>);
    // Result is in canonical unit (milliampere), so 1A = 1000mA, result = 1500mA
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiCurrentOperatorsTest, add_ampere_to_milliampere)
{
    pkr::units::ampere_t a{1.0};
    pkr::units::milliampere_t ma{500.0};
    auto result = a + ma;
    static_assert(std::is_same_v<decltype(result), pkr::units::ampere_t>);
    // Result is in LHS unit (ampere), so 500mA = 0.5A, result = 1.5A
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiCurrentOperatorsTest, subtract_amperes)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{2.0};
    auto result = a1 - a2;
    static_assert(std::is_same_v<decltype(result), pkr::units::ampere_t>);
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiCurrentOperatorsTest, subtract_milliampere_from_ampere)
{
    pkr::units::ampere_t a{1.0};
    pkr::units::milliampere_t ma{500.0};
    auto result = a - ma;
    static_assert(std::is_same_v<decltype(result), pkr::units::ampere_t>);
    // 1A - 500mA = 1000mA - 500mA = 500mA = 0.5A
    ASSERT_DOUBLE_EQ(result.value(), 0.5);
}

TEST_F(SiCurrentOperatorsTest, subtract_ampere_from_milliampere)
{
    pkr::units::milliampere_t ma{1500.0};
    pkr::units::ampere_t a{1.0};
    auto result = ma - a;
    static_assert(std::is_same_v<decltype(result), pkr::units::milliampere_t>);
    // 1500mA - 1000mA = 500mA
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Multiplication/Division by Scalar
// ============================================================================

TEST_F(SiCurrentOperatorsTest, multiply_ampere_by_scalar)
{
    pkr::units::ampere_t a{5.0};
    auto result = a * 3.0;

    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiCurrentOperatorsTest, divide_ampere_by_scalar)
{
    pkr::units::ampere_t a{10.0};
    auto result = a / 2.0;

    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiCurrentOperatorsTest, divide_by_zero_scalar_throws)
{
    pkr::units::ampere_t a{10.0};
    ASSERT_THROW(a / 0.0, std::invalid_argument);
}

TEST_F(SiCurrentOperatorsTest, divide_by_zero_si_unit_throws)
{
    pkr::units::ampere_t a1{10.0};
    pkr::units::ampere_t a2{0.0};
    ASSERT_THROW(a1 / a2, std::invalid_argument);
}

TEST_F(SiCurrentOperatorsTest, multiply_ampere_by_zero)
{
    pkr::units::ampere_t a{5.0};
    auto result = a * 0.0;

    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiCurrentOperatorsTest, multiply_ampere_by_fraction)
{
    pkr::units::ampere_t a{6.0};
    auto result = a * 0.5;

    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Comparison Operators
// ============================================================================

TEST_F(SiCurrentOperatorsTest, equal_amperes)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{5.0};
    ASSERT_TRUE(a1 == a2);
}

TEST_F(SiCurrentOperatorsTest, not_equal_amperes)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{3.0};
    ASSERT_TRUE(a1 != a2);
}

TEST_F(SiCurrentOperatorsTest, less_than_amperes)
{
    pkr::units::ampere_t a1{3.0};
    pkr::units::ampere_t a2{5.0};
    ASSERT_TRUE(a1 < a2);
}

TEST_F(SiCurrentOperatorsTest, less_than_or_equal_amperes)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{5.0};
    ASSERT_TRUE(a1 <= a2);
}

TEST_F(SiCurrentOperatorsTest, greater_than_amperes)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{3.0};
    ASSERT_TRUE(a1 > a2);
}

TEST_F(SiCurrentOperatorsTest, greater_than_or_equal_amperes)
{
    pkr::units::ampere_t a1{5.0};
    pkr::units::ampere_t a2{5.0};
    ASSERT_TRUE(a1 >= a2);
}

// ============================================================================
// Constexpr Operations
// ============================================================================

TEST_F(SiCurrentOperatorsTest, constexpr_ampere_addition)
{
    constexpr pkr::units::ampere_t a1{3.0};
    constexpr pkr::units::ampere_t a2{2.0};
    constexpr auto result = a1 + a2;
    static_assert(result.value() == 5.0);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiCurrentOperatorsTest, constexpr_ampere_multiplication_and_division)
{
    constexpr pkr::units::ampere_t a{10.0};
    constexpr auto multiplied = a * 2.0;
    constexpr auto divided = multiplied / 5.0;
    static_assert(divided.value() == 4.0);
    ASSERT_DOUBLE_EQ(divided.value(), 4.0);
}



