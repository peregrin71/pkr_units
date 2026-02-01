//
// Test measurement edge cases and uncovered functionality
// Tests edge cases in measurement.h that are not covered by existing tests

#include <gtest/gtest.h>

#include <pkr_units/measurements/measurement.h>
#include <pkr_units/si_units.h>
#include <limits>

namespace test
{

using namespace ::testing;

class MeasurementEdgeCasesTest : public Test
{
};

// Test measurements with zero uncertainty
TEST_F(MeasurementEdgeCasesTest, ZeroUncertainty)
{
    pkr::units::measurement_t<pkr::units::meter_t> m{5.0, 0.0};
    EXPECT_DOUBLE_EQ(m.value(), 5.0);
    EXPECT_DOUBLE_EQ(m.uncertainty(), 0.0);
    EXPECT_DOUBLE_EQ(m.relative_uncertainty().value(), 0.0);
}

// Test measurements with very small uncertainty
TEST_F(MeasurementEdgeCasesTest, VerySmallUncertainty)
{
    pkr::units::measurement_t<pkr::units::meter_t> m{1.0, 1e-15};
    EXPECT_DOUBLE_EQ(m.value(), 1.0);
    EXPECT_DOUBLE_EQ(m.uncertainty(), 1e-15);
    EXPECT_DOUBLE_EQ(m.relative_uncertainty().value(), 1e-15);
}

// Test measurements with very large uncertainty
TEST_F(MeasurementEdgeCasesTest, VeryLargeUncertainty)
{
    pkr::units::measurement_t<pkr::units::meter_t> m{1.0, 1000.0};
    EXPECT_DOUBLE_EQ(m.value(), 1.0);
    EXPECT_DOUBLE_EQ(m.uncertainty(), 1000.0);
    EXPECT_DOUBLE_EQ(m.relative_uncertainty().value(), 1000.0);
}

// Test measurements with negative values
TEST_F(MeasurementEdgeCasesTest, NegativeValues)
{
    pkr::units::measurement_t<pkr::units::meter_t> m{-5.0, 0.1};
    EXPECT_DOUBLE_EQ(m.value(), -5.0);
    EXPECT_DOUBLE_EQ(m.uncertainty(), 0.1);
    EXPECT_DOUBLE_EQ(m.relative_uncertainty().value(), -0.02); // negative relative uncertainty
}

// Test measurements with extreme values
TEST_F(MeasurementEdgeCasesTest, ExtremeValues)
{
    // Very large values
    pkr::units::measurement_t<pkr::units::meter_t> large{1e308, 1e300};
    EXPECT_DOUBLE_EQ(large.value(), 1e308);
    EXPECT_DOUBLE_EQ(large.uncertainty(), 1e300);

    // Very small values
    pkr::units::measurement_t<pkr::units::meter_t> small{1e-308, 1e-310};
    EXPECT_DOUBLE_EQ(small.value(), 1e-308);
    EXPECT_DOUBLE_EQ(small.uncertainty(), 1e-310);
}

// Test measurements with NaN and infinity
TEST_F(MeasurementEdgeCasesTest, SpecialValues)
{
    using std::numeric_limits;

    // NaN value
    pkr::units::measurement_t<pkr::units::meter_t> nan_val{numeric_limits<double>::quiet_NaN(), 1.0};
    EXPECT_TRUE(std::isnan(nan_val.value()));
    EXPECT_DOUBLE_EQ(nan_val.uncertainty(), 1.0);

    // Infinity value
    pkr::units::measurement_t<pkr::units::meter_t> inf_val{numeric_limits<double>::infinity(), 1.0};
    EXPECT_TRUE(std::isinf(inf_val.value()));
    EXPECT_DOUBLE_EQ(inf_val.uncertainty(), 1.0);

    // NaN uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> nan_unc{1.0, numeric_limits<double>::quiet_NaN()};
    EXPECT_DOUBLE_EQ(nan_unc.value(), 1.0);
    EXPECT_TRUE(std::isnan(nan_unc.uncertainty()));

    // Infinity uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> inf_unc{1.0, numeric_limits<double>::infinity()};
    EXPECT_DOUBLE_EQ(inf_unc.value(), 1.0);
    EXPECT_TRUE(std::isinf(inf_unc.uncertainty()));
}

// Test measurement arithmetic with edge cases
TEST_F(MeasurementEdgeCasesTest, ArithmeticWithEdgeCases)
{
    pkr::units::measurement_t<pkr::units::meter_t> zero_unc{5.0, 0.0};
    pkr::units::measurement_t<pkr::units::meter_t> normal{3.0, 0.1};

    // Addition with zero uncertainty
    auto result1 = zero_unc + normal;
    EXPECT_DOUBLE_EQ(result1.value(), 8.0);
    EXPECT_DOUBLE_EQ(result1.uncertainty(), 0.1);

    // Multiplication with zero uncertainty
    auto result2 = zero_unc * normal;
    EXPECT_DOUBLE_EQ(result2.value(), 15.0);
    EXPECT_DOUBLE_EQ(result2.uncertainty(), 0.5); // 5.0 * 0.1

    // Division with zero uncertainty
    auto result3 = zero_unc / normal;
    EXPECT_DOUBLE_EQ(result3.value(), 5.0 / 3.0);
    EXPECT_NEAR(result3.uncertainty(), 5.0 / 3.0 * 0.1 / 3.0, 1e-10);
}

// Test measurement comparisons with edge cases
TEST_F(MeasurementEdgeCasesTest, ComparisonsWithEdgeCases)
{
    pkr::units::measurement_t<pkr::units::meter_t> m1{5.0, 0.0};
    pkr::units::measurement_t<pkr::units::meter_t> m2{5.0, 0.1};
    pkr::units::measurement_t<pkr::units::meter_t> m3{5.1, 0.0};

    // Test that values can be compared (not measurements directly)
    EXPECT_DOUBLE_EQ(m1.value(), m2.value());
    EXPECT_NE(m1.value(), m3.value());
}

// Test measurement formatting with edge cases
TEST_F(MeasurementEdgeCasesTest, FormattingEdgeCases)
{
    // Test formatting with very small uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> small_unc{1.0, 1e-10};
    std::string formatted = std::format("{}", small_unc);
    EXPECT_FALSE(formatted.empty());

    // Test formatting with very large uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> large_unc{1.0, 1000.0};
    formatted = std::format("{}", large_unc);
    EXPECT_FALSE(formatted.empty());

    // Test formatting with zero uncertainty
    pkr::units::measurement_t<pkr::units::meter_t> zero_unc{5.0, 0.0};
    formatted = std::format("{}", zero_unc);
    EXPECT_FALSE(formatted.empty());
}

// Test measurement construction edge cases
TEST_F(MeasurementEdgeCasesTest, ConstructionEdgeCases)
{
    // Copy construction
    pkr::units::measurement_t<pkr::units::meter_t> original{10.0, 0.5};
    pkr::units::measurement_t<pkr::units::meter_t> copy = original;
    EXPECT_DOUBLE_EQ(copy.value(), 10.0);
    EXPECT_DOUBLE_EQ(copy.uncertainty(), 0.5);
}

} // namespace test
