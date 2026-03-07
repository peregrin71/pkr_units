#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;
using namespace pkr::units;

static_assert(
    std::is_same_v<decltype(std::declval<meter_t<double>>() + std::declval<meter_t<double>>()), meter_t<double>>,
    "Length addition must return meter_t");
static_assert(
    std::is_same_v<decltype(std::declval<meter_t<double>>() * std::declval<meter_t<double>>()), square_meter_t<double>>,
    "Length × Length must return square_meter_t");
static_assert(
    std::is_same_v<decltype(std::declval<meter_t<double>>() * std::declval<meter_t<double>>() * std::declval<meter_t<double>>()), cubic_meter_t<double>>,
    "Length × Length × Length must return cubic_meter_t");
static_assert(
    std::is_same_v<decltype(unit_cast<centimeter_t<double>>(std::declval<meter_t<double>>())), centimeter_t<double>>,
    "unit_cast must return correct type");
static_assert(std::is_same_v<measurement_rss_t<meter_t<double>>::value_type, double>, "measurement_rss_t value_type must be double");

class EdgeCasesTest : public Test
{
};

TEST_F(EdgeCasesTest, extreme_large_values)
{
    double large_val = 1e150;
    meter_t<double> m{large_val};
    ASSERT_DOUBLE_EQ(m.value(), large_val);
}

TEST_F(EdgeCasesTest, extreme_small_values)
{
    double small_val = 1e-150;
    meter_t<double> m{small_val};
    ASSERT_DOUBLE_EQ(m.value(), small_val);
}

TEST_F(EdgeCasesTest, very_small_measurements)
{
    using meter_meas = measurement_rss_t<meter_t<double>>;
    meter_meas m{1e-10, 1e-11};
    ASSERT_NEAR(m.value(), 1e-10, 1e-15);
    ASSERT_NEAR(m.uncertainty(), 1e-11, 1e-16);
}

TEST_F(EdgeCasesTest, zero_value_operations)
{
    meter_t<double> zero{0.0};
    meter_t<double> nonzero{5.0};

    auto sum = zero + nonzero;
    auto diff = nonzero - zero;
    auto prod = zero * 2.0;

    ASSERT_DOUBLE_EQ(sum.value(), 5.0);
    ASSERT_DOUBLE_EQ(diff.value(), 5.0);
    ASSERT_DOUBLE_EQ(prod.value(), 0.0);
}

TEST_F(EdgeCasesTest, negative_value_operations)
{
    meter_t<double> neg{-10.0};
    meter_t<double> pos{10.0};

    auto sum = neg + pos;
    auto diff = pos - neg;
    auto neg_mult = neg * 2.0;

    ASSERT_DOUBLE_EQ(sum.value(), 0.0);
    ASSERT_DOUBLE_EQ(diff.value(), 20.0);
    ASSERT_DOUBLE_EQ(neg_mult.value(), -20.0);
}

TEST_F(EdgeCasesTest, mixed_float_double_precision)
{
    meter_t<float> m_float{3.14f};
    ASSERT_NEAR(m_float.value(), 3.14f, 1e-5f);

    meter_t<double> m_double{3.14159265359};
    ASSERT_NEAR(m_double.value(), 3.14159265359, 1e-10);
}

TEST_F(EdgeCasesTest, overflow_risk_multiplication)
{
    meter_t<double> large{1e200};
    auto result = large * 0.0001;
    ASSERT_DOUBLE_EQ(result.value(), 1e196);
}

TEST_F(EdgeCasesTest, underflow_risk_division)
{
    meter_t<double> small{1e-200};
    auto result = small / 1e100;
    ASSERT_DOUBLE_EQ(result.value(), 1e-300);
}

TEST_F(EdgeCasesTest, repeated_conversions)
{
    meter_t<double> m{100.0};
    auto cm = unit_cast<centimeter_t<double>>(m);
    auto km = unit_cast<kilometer_t<double>>(cm);
    auto m_back = unit_cast<meter_t<double>>(km);

    ASSERT_NEAR(m_back.value(), 100.0, 1e-10);
}

TEST_F(EdgeCasesTest, chain_multiplication_divisions)
{
    meter_t<double> m{100.0};
    auto result = (m * 2.0) / 2.0;
    static_assert(std::is_same_v<decltype(result), meter_t<double>>, "chain mult/div type check");
    ASSERT_NEAR(result.value(), 100.0, 1e-10);
}

TEST_F(EdgeCasesTest, zero_uncertainty_measurement)
{
    using meter_meas = measurement_rss_t<meter_t<double>>;
    meter_meas m{5.0, 0.0};
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
    ASSERT_DOUBLE_EQ(m.uncertainty(), 0.0);
}

TEST_F(EdgeCasesTest, large_uncertainty_measurement)
{
    using meter_meas = measurement_rss_t<meter_t<double>>;
    meter_meas m{10.0, 50.0};
    ASSERT_DOUBLE_EQ(m.value(), 10.0);
    ASSERT_DOUBLE_EQ(m.uncertainty(), 50.0);
}

TEST_F(EdgeCasesTest, measurement_uncertainty_larger_than_value)
{
    using meter_meas = measurement_rss_t<meter_t<double>>;
    meter_meas m{2.0, 10.0};
    ASSERT_DOUBLE_EQ(m.value(), 2.0);
    ASSERT_DOUBLE_EQ(m.uncertainty(), 10.0);
}

TEST_F(EdgeCasesTest, boundary_unit_casting)
{
    meter_t<double> m{1.0};

    auto mm = unit_cast<millimeter_t<double>>(m);
    auto km = unit_cast<kilometer_t<double>>(m);

    ASSERT_DOUBLE_EQ(mm.value(), 1000.0);
    ASSERT_DOUBLE_EQ(km.value(), 0.001);
}

TEST_F(EdgeCasesTest, comparison_with_precision_loss)
{
    meter_t<double> m1{0.1 + 0.2};
    meter_t<double> m2{0.3};

    ASSERT_NEAR(m1.value(), m2.value(), 1e-15);
}

TEST_F(EdgeCasesTest, constexpr_arithmetic)
{
    constexpr meter_t<double> m1{5.0};
    constexpr meter_t<double> m2{3.0};
    constexpr auto sum = m1 + m2;

    ASSERT_DOUBLE_EQ(sum.value(), 8.0);
}

TEST_F(EdgeCasesTest, very_large_area_volume)
{
    square_meter_t<double> area{1e100};
    cubic_meter_t<double> volume{1e150};

    ASSERT_DOUBLE_EQ(area.value(), 1e100);
    ASSERT_DOUBLE_EQ(volume.value(), 1e150);
}

TEST_F(EdgeCasesTest, fractional_scalar_multiplication)
{
    meter_t<double> m{10.0};
    auto quarter = m * 0.25;
    auto third = m * (1.0 / 3.0);

    ASSERT_DOUBLE_EQ(quarter.value(), 2.5);
    ASSERT_NEAR(third.value(), 3.333333333, 1e-9);
}

TEST_F(EdgeCasesTest, negative_zero)
{
    meter_t<double> pos_zero{0.0};
    meter_t<double> neg_zero{-0.0};

    ASSERT_DOUBLE_EQ(pos_zero.value(), 0.0);
    ASSERT_DOUBLE_EQ(neg_zero.value(), 0.0);
    ASSERT_TRUE(pos_zero == neg_zero);
}

TEST_F(EdgeCasesTest, addition_associativity)
{
    meter_t<double> m1{10.0};
    meter_t<double> m2{20.0};
    meter_t<double> m3{30.0};

    auto result1 = (m1 + m2) + m3;
    auto result2 = m1 + (m2 + m3);

    ASSERT_NEAR(result1.value(), result2.value(), 1e-10);
}

} // namespace test
