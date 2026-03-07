#include <gtest/gtest.h>
#include <pkr_units/measurements/decl/measurement_lin_decl.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>
#include <pkr_units/impl/parsing/parse.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;
using namespace pkr::units;

static_assert(std::is_same_v<measurement_lin_t<meter_t<double>>::unit_type, meter_t<double>>, "measurement_lin_t must have meter_t unit_type");
static_assert(std::is_same_v<measurement_rss_t<meter_t<double>>::unit_type, meter_t<double>>, "measurement_rss_t must have meter_t unit_type");
static_assert(
    std::is_invocable_v<decltype(parse_linear<measurement_lin_t<meter_t<double>>>), std::string_view>,
    "parse_linear must be invocable with string_view");

class MeasurementParsingTest : public Test
{
};

TEST_F(MeasurementParsingTest, parse_measurement_lin_basic)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("5.0 m");
    static_assert(std::is_same_v<decltype(result)::value_type, measurement_lin_t<meter_t<double>>>, "parse_linear return type check");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 5.0);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 0.0);
}

TEST_F(MeasurementParsingTest, parse_measurement_lin_with_uncertainty_plus_minus)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("5.0 +/- 0.1 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 5.0);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 0.1);
}

TEST_F(MeasurementParsingTest, parse_measurement_lin_with_uncertainty_pm_symbol)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("5.0 ± 0.1 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 5.0);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 0.1);
}

TEST_F(MeasurementParsingTest, parse_measurement_lin_negative_value)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("-3.5 +/- 0.2 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), -3.5);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 0.2);
}

TEST_F(MeasurementParsingTest, parse_measurement_lin_zero)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("0.0 +/- 0.001 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 0.0);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 0.001);
}

TEST_F(MeasurementParsingTest, parse_measurement_lin_large_values)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("1250.5 +/- 50.2 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 1250.5);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 50.2);
}

TEST_F(MeasurementParsingTest, parse_measurement_lin_small_values)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("0.0025 +/- 0.0001 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 0.0025);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 0.0001);
}

TEST_F(MeasurementParsingTest, parse_measurement_different_units)
{
    auto meter_result = parse_linear<measurement_lin_t<meter_t<double>>>("5.0 +/- 0.1 m");
    auto km_result = parse_linear<measurement_lin_t<kilometer_t<double>>>("5.0 +/- 0.1 km");

    ASSERT_TRUE(meter_result);
    ASSERT_TRUE(km_result);
    ASSERT_DOUBLE_EQ(meter_result->value(), 5.0);
    ASSERT_DOUBLE_EQ(km_result->value(), 5.0);
}

TEST_F(MeasurementParsingTest, parse_measurement_scientific_notation)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("1.5e-3 +/- 1e-4 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 0.0015);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 0.0001);
}

TEST_F(MeasurementParsingTest, parse_measurement_invalid_format_missing_uncertainty)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("5.0 +/- m");
    ASSERT_FALSE(result);
}

TEST_F(MeasurementParsingTest, parse_measurement_whitespace_handling)
{
    auto result1 = parse_linear<measurement_lin_t<meter_t<double>>>("5.0+/-0.1 m");
    auto result2 = parse_linear<measurement_lin_t<meter_t<double>>>("5.0  +/-  0.1 m");
    auto result3 = parse_linear<measurement_lin_t<meter_t<double>>>("5.0   +/-   0.1  m");

    if (result1)
    {
        EXPECT_DOUBLE_EQ(result1->value(), 5.0);
    }
    if (result2)
    {
        EXPECT_DOUBLE_EQ(result2->value(), 5.0);
    }
    if (result3)
    {
        EXPECT_DOUBLE_EQ(result3->value(), 5.0);
    }
}

TEST_F(MeasurementParsingTest, parse_measurement_very_large_uncertainty)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("100.0 +/- 50.0 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result->value(), 100.0);
    ASSERT_DOUBLE_EQ(result->uncertainty(), 50.0);
}

TEST_F(MeasurementParsingTest, parse_measurement_very_small_uncertainty)
{
    auto result = parse_linear<measurement_lin_t<meter_t<double>>>("1.0 +/- 1e-10 m");
    ASSERT_TRUE(result);

} // namespace test
