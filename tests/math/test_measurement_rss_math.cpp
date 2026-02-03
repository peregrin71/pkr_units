#include <gtest/gtest.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;

class MeasurementMathRSSTest : public Test
{
};

// ============================================================================
// Measurement RSS Math Functions
// ============================================================================

TEST_F(MeasurementMathRSSTest, add_rss)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    meter_meas m1{5.0, 0.1};
    meter_meas m2{3.0, 0.2};
    auto result = m1 + m2;

    EXPECT_DOUBLE_EQ(result.value(), 8.0);
    EXPECT_DOUBLE_EQ(result.uncertainty(), std::sqrt(0.1 * 0.1 + 0.2 * 0.2));
}

TEST_F(MeasurementMathRSSTest, subtract_rss)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    meter_meas m1{5.0, 0.1};
    meter_meas m2{3.0, 0.2};
    auto result = m1 - m2;

    EXPECT_DOUBLE_EQ(result.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.uncertainty(), std::sqrt(0.1 * 0.1 + 0.2 * 0.2));
}

TEST_F(MeasurementMathRSSTest, multiply_rss)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    using second_meas = pkr::units::measurement_rss_t<pkr::units::second_t<double>>;
    meter_meas m{5.0, 0.1};
    second_meas s{3.0, 0.2};
    auto result = m * s;

    EXPECT_DOUBLE_EQ(result.value(), 15.0);
    // Uncertainty calculation: sqrt((m.value*s.uncertainty)^2 + (s.value*m.uncertainty)^2)
    double expected_uncertainty = std::sqrt((5.0 * 0.2) * (5.0 * 0.2) + (3.0 * 0.1) * (3.0 * 0.1));
    EXPECT_DOUBLE_EQ(result.uncertainty(), expected_uncertainty);
}

TEST_F(MeasurementMathRSSTest, divide_rss)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    using second_meas = pkr::units::measurement_rss_t<pkr::units::second_t<double>>;
    meter_meas m{6.0, 0.1};
    second_meas s{3.0, 0.2};
    auto result = m / s;

    EXPECT_DOUBLE_EQ(result.value(), 2.0);
    // Uncertainty calculation for division is more complex
    // Relative uncertainty: sqrt((dm/m)^2 + (ds/s)^2) * result
    double rel_uncertainty = std::sqrt((0.1 / 6.0) * (0.1 / 6.0) + (0.2 / 3.0) * (0.2 / 3.0));
    double expected_uncertainty = rel_uncertainty * 2.0;
    EXPECT_DOUBLE_EQ(result.uncertainty(), expected_uncertainty);
}

// TEST_F(MeasurementMathRSSTest, sqrt_rss)
// {
//     using meter_squared_meas = pkr::units::measurement_t<pkr::units::meter_squared_t>;
//     meter_squared_meas m2{4.0, 0.4};
//     auto result = pkr::units::sqrt_rss(m2);

//     EXPECT_DOUBLE_EQ(result.value(), 2.0);
//     // For sqrt, uncertainty is (dm2/(2*sqrt(m2)))
//     EXPECT_DOUBLE_EQ(result.uncertainty(), 0.4 / (2.0 * 2.0));
// }

TEST_F(MeasurementMathRSSTest, multiply_rss_measurement_scalar)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    meter_meas m{5.0, 0.1};
    auto result = m * 2.0;

    EXPECT_DOUBLE_EQ(result.value(), 10.0);
    EXPECT_DOUBLE_EQ(result.uncertainty(), 2.0 * 0.1);
}

TEST_F(MeasurementMathRSSTest, multiply_rss_scalar_measurement)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    meter_meas m{5.0, 0.1};
    auto result = 2.0 * m;

    EXPECT_DOUBLE_EQ(result.value(), 10.0);
    EXPECT_DOUBLE_EQ(result.uncertainty(), 2.0 * 0.1);
}

TEST_F(MeasurementMathRSSTest, divide_rss_measurement_scalar)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    meter_meas m{6.0, 0.1};
    auto result = m / 2.0;

    EXPECT_DOUBLE_EQ(result.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.uncertainty(), 0.1 / 2.0);
}

TEST_F(MeasurementMathRSSTest, divide_rss_scalar_measurement)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;
    meter_meas m{2.0, 0.1};
    auto result = 6.0 / m;

    EXPECT_DOUBLE_EQ(result.value(), 3.0);
    // For 6.0 / m, uncertainty is |6.0| * |dm| / |m|^2
    EXPECT_DOUBLE_EQ(result.uncertainty(), 6.0 * 0.1 / (2.0 * 2.0));
}

TEST_F(MeasurementMathRSSTest, SumOfSquaresRSS)
{
    using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t<double>>;

    meter_meas x{1.0, 0.1};
    meter_meas y{2.0, 0.2};
    meter_meas z{3.0, 0.3};

    auto result = sum_of_squares_rss(x, y, z);

    // value should be x^2 + y^2 + z^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ(result.value(), 14.0);

    // uncertainties: 2*m*dm for each squared term, combined in quadrature
    double u1 = 2.0 * 1.0 * 0.1;         // 0.2
    double u2 = 2.0 * 4.0 * (0.2 / 2.0); // equals 0.8
    double u3 = 2.0 * 9.0 * (0.3 / 3.0); // equals 1.8
    double expected_unc = std::sqrt(u1 * u1 + u2 * u2 + u3 * u3);

    EXPECT_NEAR(result.uncertainty(), expected_unc, 1e-12);
}

} // namespace test
