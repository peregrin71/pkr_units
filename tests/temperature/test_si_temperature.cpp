#include <gtest/gtest.h>
#include <pkr_units/standard/temperature.h>

using namespace ::testing;

class SiTemperatureTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiTemperatureTest, kelvin_construction)
{
    pkr::units::kelvin_t k{5.0};
    ASSERT_DOUBLE_EQ(k.value(), 5.0);
}

TEST_F(SiTemperatureTest, kelvin_dereference_operator)
{
    pkr::units::kelvin_t k{5.0};
    ASSERT_DOUBLE_EQ(*k, 5.0);
}

TEST_F(SiTemperatureTest, kelvin_zero_value)
{
    pkr::units::kelvin_t k{0.0};
    ASSERT_DOUBLE_EQ(k.value(), 0.0);
}

TEST_F(SiTemperatureTest, kelvin_negative_value)
{
    pkr::units::kelvin_t k{-3.5};
    ASSERT_DOUBLE_EQ(k.value(), -3.5);
}

TEST_F(SiTemperatureTest, millikelvin_construction)
{
    pkr::units::millikelvin_t mk{250.0};
    ASSERT_DOUBLE_EQ(mk.value(), 250.0);
}

TEST_F(SiTemperatureTest, microkelvin_construction)
{
    pkr::units::microkelvin_t uk{1000.0};
    ASSERT_DOUBLE_EQ(uk.value(), 1000.0);
}

TEST_F(SiTemperatureTest, nanokelvin_construction)
{
    pkr::units::nanokelvin_t nk{100.0};
    ASSERT_DOUBLE_EQ(nk.value(), 100.0);
}

TEST_F(SiTemperatureTest, kilokelvin_construction)
{
    pkr::units::kilokelvin_t kk{2.5};
    ASSERT_DOUBLE_EQ(kk.value(), 2.5);
}

// ============================================================================
// Copy and Move Tests
// ============================================================================

TEST_F(SiTemperatureTest, copy_constructor)
{
    pkr::units::kelvin_t k1{5.0};
    pkr::units::kelvin_t k2 = k1;
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

TEST_F(SiTemperatureTest, move_constructor)
{
    pkr::units::kelvin_t k1{5.0};
    pkr::units::kelvin_t k2 = std::move(k1);
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

TEST_F(SiTemperatureTest, copy_assignment)
{
    pkr::units::kelvin_t k1{5.0};
    pkr::units::kelvin_t k2{0.0};
    k2 = k1;
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

TEST_F(SiTemperatureTest, move_assignment)
{
    pkr::units::kelvin_t k1{5.0};
    pkr::units::kelvin_t k2{0.0};
    k2 = std::move(k1);
    ASSERT_DOUBLE_EQ(k2.value(), 5.0);
}

// ============================================================================
// Arithmetic Tests - Same Unit
// ============================================================================

TEST_F(SiTemperatureTest, add_kelvins)
{
    pkr::units::kelvin_t k1{3.0};
    pkr::units::kelvin_t k2{2.0};
    auto result = k1 + k2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTemperatureTest, subtract_kelvins)
{
    pkr::units::kelvin_t k1{5.0};
    pkr::units::kelvin_t k2{2.0};
    auto result = k1 - k2;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTemperatureTest, add_millikelvins)
{
    pkr::units::millikelvin_t mk1{500.0};
    pkr::units::millikelvin_t mk2{250.0};
    auto result = mk1 + mk2;
    ASSERT_DOUBLE_EQ(result.value(), 750.0);
}

TEST_F(SiTemperatureTest, subtract_millikelvins)
{
    pkr::units::millikelvin_t mk1{750.0};
    pkr::units::millikelvin_t mk2{250.0};
    auto result = mk1 - mk2;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

// ============================================================================
// Arithmetic Tests - Different Units (Same Dimension)
// ============================================================================

TEST_F(SiTemperatureTest, add_kelvin_to_millikelvin)
{
    pkr::units::kelvin_t k{1.0};
    pkr::units::millikelvin_t mk{500.0};
    auto result = k + mk;
    // Result is in LHS type (kelvin)
    // 1K + 0.5K = 1.5K
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

TEST_F(SiTemperatureTest, add_millikelvin_to_kelvin)
{
    pkr::units::millikelvin_t mk{500.0};
    pkr::units::kelvin_t k{1.0};
    auto result = mk + k;
    // Result is in LHS type (millikelvin)
    // 500mK + 1000mK = 1500mK
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

TEST_F(SiTemperatureTest, subtract_kelvin_from_millikelvin)
{
    pkr::units::millikelvin_t mk{1500.0};
    pkr::units::kelvin_t k{1.0};
    auto result = mk - k;
    // Result is in LHS type (millikelvin)
    // 1500mK - 1000mK = 500mK
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiTemperatureTest, subtract_millikelvin_from_kelvin)
{
    pkr::units::kelvin_t k{2.0};
    pkr::units::millikelvin_t mk{500.0};
    auto result = k - mk;
    // Result is in LHS type (kelvin)
    // 2K - 0.5K = 1.5K
    ASSERT_DOUBLE_EQ(result.value(), 1.5);
}

// ============================================================================
// Scalar Multiplication and Division
// ============================================================================

TEST_F(SiTemperatureTest, multiply_kelvin_by_scalar)
{
    pkr::units::kelvin_t k{2.0};
    auto result = k * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

TEST_F(SiTemperatureTest, divide_kelvin_by_scalar)
{
    pkr::units::kelvin_t k{6.0};
    auto result = k / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 3.0);
}

TEST_F(SiTemperatureTest, divide_by_zero_scalar_throws)
{
    pkr::units::kelvin_t k{5.0};
    ASSERT_THROW(k / 0.0, std::invalid_argument);
}

TEST_F(SiTemperatureTest, multiply_millikelvin_by_scalar)
{
    pkr::units::millikelvin_t mk{100.0};
    auto result = mk * 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 500.0);
}

TEST_F(SiTemperatureTest, divide_millikelvin_by_scalar)
{
    pkr::units::millikelvin_t mk{500.0};
    auto result = mk / 5.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

// ============================================================================
// Temperature Multiplication (Creates Derived Units)
// ============================================================================

TEST_F(SiTemperatureTest, multiply_kelvin_by_kelvin)
{
    pkr::units::kelvin_t k1{2.0};
    pkr::units::kelvin_t k2{3.0};
    auto result = k1 * k2;
    // Result has temperature dimension = 2 (K²)
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.temperature, 2);
}

// ============================================================================
// Temperature Division (Creates Dimensionless)
// ============================================================================

TEST_F(SiTemperatureTest, divide_kelvin_by_kelvin)
{
    pkr::units::kelvin_t k1{10.0};
    pkr::units::kelvin_t k2{2.0};
    auto result = k1 / k2;
    // Result is dimensionless (scalar)
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.temperature, 0);
}

TEST_F(SiTemperatureTest, divide_millikelvin_by_millikelvin)
{
    pkr::units::millikelvin_t mk1{500.0};
    pkr::units::millikelvin_t mk2{100.0};
    auto result = mk1 / mk2;
    // Result is dimensionless
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::dimension::value.temperature, 0);
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(SiTemperatureTest, constexpr_kelvin_addition)
{
    constexpr pkr::units::kelvin_t k1{3.0};
    constexpr pkr::units::kelvin_t k2{2.0};
    constexpr auto result = k1 + k2;
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
}

TEST_F(SiTemperatureTest, constexpr_kelvin_multiplication)
{
    constexpr pkr::units::kelvin_t k{2.0};
    constexpr auto result = k * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST_F(SiTemperatureTest, very_small_temperature_values)
{
    pkr::units::nanokelvin_t nk{0.001};
    ASSERT_DOUBLE_EQ(nk.value(), 0.001);
}

TEST_F(SiTemperatureTest, very_large_temperature_values)
{
    pkr::units::kilokelvin_t kk{1000000.0};
    ASSERT_DOUBLE_EQ(kk.value(), 1000000.0);
}

TEST_F(SiTemperatureTest, add_very_different_scales)
{
    pkr::units::millikelvin_t mk{1.0};   // 1 millikelvin
    pkr::units::kelvin_t k{1.0};         // 1 kelvin = 1000 mK
    auto result = mk + k;
    // Result is in LHS type (millikelvin)
    // 1 mK + 1000 mK = 1001 mK
    ASSERT_DOUBLE_EQ(result.value(), 1001.0);
}

TEST_F(SiTemperatureTest, subtract_resulting_in_negative)
{
    pkr::units::kelvin_t k1{1.0};
    pkr::units::kelvin_t k2{3.0};
    auto result = k1 - k2;
    ASSERT_DOUBLE_EQ(result.value(), -2.0);
}



