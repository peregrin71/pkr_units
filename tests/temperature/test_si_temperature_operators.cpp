#include <gtest/gtest.h>
#include <pkr_units/units/base/temperature.h>

using namespace ::testing;

class SiTemperatureOperatorsTest : public Test
{
};

// ============================================================================
// Arithmetic Operations: Addition/Subtraction (Same Dimension, Different Ratios)
// ============================================================================

TEST_F(SiTemperatureOperatorsTest, add_kelvins)
{
    pkr::units::kelvin_t<double> k1{3.0};
    pkr::units::kelvin_t<double> k2{2.0};
    auto result = k1 + k2;
    static_assert(std::is_same_v<decltype(result), pkr::units::kelvin_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTemperatureOperatorsTest, add_millikelvin_to_kelvin)
{
    pkr::units::millikelvin_t<double> mk{500.0};
    pkr::units::kelvin_t<double> k{1.0};
    auto result = mk + k; // preserves LHS (millikelvin)

    static_assert(std::is_same_v<decltype(result), pkr::units::millikelvin_t<double>>, "operator+ should preserve LHS type (millikelvin)");
    // 500 mK + 1000 mK = 1500 mK
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiTemperatureOperatorsTest, add_kelvin_to_millikelvin)
{
    pkr::units::kelvin_t<double> k{1.0};
    pkr::units::millikelvin_t<double> mk{500.0};
    auto result = k + mk;
    static_assert(std::is_same_v<decltype(result), pkr::units::kelvin_t<double>>);
    // Result is in LHS unit (kelvin), so 500mK = 0.5K, result = 1.5K
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiTemperatureOperatorsTest, subtract_kelvins)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{2.0};
    auto result = k1 - k2;
    static_assert(std::is_same_v<decltype(result), pkr::units::kelvin_t<double>>);
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTemperatureOperatorsTest, subtract_millikelvin_from_kelvin)
{
    pkr::units::kelvin_t<double> k{1.0};
    pkr::units::millikelvin_t<double> mk{500.0};
    auto result = k - mk;

    using res_ratio = typename pkr::units::details::is_pkr_unit<decltype(result)>::ratio_type;
    static_assert(std::ratio_equal_v<res_ratio, std::ratio<1, 1>>, "operator- should return canonical ratio<1,1>");
    ASSERT_DOUBLE_EQ(result.value(), 0.5);
}

TEST_F(SiTemperatureOperatorsTest, subtract_kelvin_from_millikelvin)
{
    pkr::units::millikelvin_t<double> mk{1500.0};
    pkr::units::kelvin_t<double> k{1.0};
    auto result = mk - k; // preserves LHS (millikelvin)

    static_assert(std::is_same_v<decltype(result), pkr::units::millikelvin_t<double>>, "operator- should preserve LHS type (millikelvin)");
    // 1500 mK - 1000 mK = 500 mK
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Multiplication/Division by Scalar
// ============================================================================

TEST_F(SiTemperatureOperatorsTest, multiply_kelvin_by_scalar)
{
    pkr::units::kelvin_t<double> k{5.0};
    auto result = k * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
}

TEST_F(SiTemperatureOperatorsTest, divide_kelvin_by_scalar)
{
    pkr::units::kelvin_t<double> k{10.0};
    auto result = k / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTemperatureOperatorsTest, multiply_kelvin_by_zero)
{
    pkr::units::kelvin_t<double> k{5.0};
    auto result = k * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

TEST_F(SiTemperatureOperatorsTest, multiply_kelvin_by_fraction)
{
    pkr::units::kelvin_t<double> k{6.0};
    auto result = k * 0.5;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

// ============================================================================
// Comparison Operators
// ============================================================================

TEST_F(SiTemperatureOperatorsTest, equal_kelvins)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{5.0};
    ASSERT_TRUE(k1 == k2);
}

TEST_F(SiTemperatureOperatorsTest, not_equal_kelvins)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{3.0};
    ASSERT_TRUE(k1 != k2);
}

TEST_F(SiTemperatureOperatorsTest, less_than_kelvins)
{
    pkr::units::kelvin_t<double> k1{3.0};
    pkr::units::kelvin_t<double> k2{5.0};
    ASSERT_TRUE(k1 < k2);
}

TEST_F(SiTemperatureOperatorsTest, less_than_or_equal_kelvins)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{5.0};
    ASSERT_TRUE(k1 <= k2);
}

TEST_F(SiTemperatureOperatorsTest, greater_than_kelvins)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{3.0};
    ASSERT_TRUE(k1 > k2);
}

TEST_F(SiTemperatureOperatorsTest, greater_than_or_equal_kelvins)
{
    pkr::units::kelvin_t<double> k1{5.0};
    pkr::units::kelvin_t<double> k2{5.0};
    ASSERT_TRUE(k1 >= k2);
}

// ============================================================================
// Constexpr Operations
// ============================================================================

TEST_F(SiTemperatureOperatorsTest, constexpr_kelvin_addition)
{
    constexpr pkr::units::kelvin_t<double> k1{3.0};
    constexpr pkr::units::kelvin_t<double> k2{2.0};
    constexpr auto result = k1 + k2;
    static_assert(result.value() == 5.0);
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTemperatureOperatorsTest, constexpr_kelvin_multiplication_and_division)
{
    constexpr pkr::units::kelvin_t<double> k{10.0};
    constexpr auto multiplied = k * 2.0;
    constexpr auto divided = multiplied / 5.0;
    static_assert(divided.value() == 4.0);
    ASSERT_DOUBLE_EQ(divided.value(), 4.0);
}
