#include <gtest/gtest.h>
#include <pkr_units/math/measurements/vector_of_measurements_rss_4d.h>
#include <pkr_units/measurements/measurement_rss_t.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;

class Vector4DMeasurementsRSSTest : public Test
{
};

// ============================================================================
// Vector with Measurements RSS Operations
// ============================================================================

TEST_F(Vector4DMeasurementsRSSTest, construction)
{
    pkr::units::vec_measurement_rss_4d_t<pkr::units::meter_t> v{{1.0, 0.1}, {2.0, 0.2}, {3.0, 0.3}, {4.0, 0.4}};
    EXPECT_DOUBLE_EQ(v.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(v.x.uncertainty(), 0.1);
    EXPECT_DOUBLE_EQ(v.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(v.y.uncertainty(), 0.2);
    EXPECT_DOUBLE_EQ(v.z.value(), 3.0);
    EXPECT_DOUBLE_EQ(v.z.uncertainty(), 0.3);
    EXPECT_DOUBLE_EQ(v.w.value(), 4.0);
    EXPECT_DOUBLE_EQ(v.w.uncertainty(), 0.4);
}

// TEST_F(Vector4DMeasurementsRSSTest, addition)
// {
//     using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t>;
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v1{meter_meas{1.0, 0.1}, meter_meas{2.0, 0.2}, meter_meas{3.0, 0.3}, meter_meas{4.0, 0.4}};
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v2{meter_meas{0.5, 0.05}, meter_meas{1.5, 0.15}, meter_meas{2.5, 0.25}, meter_meas{3.5, 0.35}};
//     auto result = v1 + v2;

//     EXPECT_DOUBLE_EQ(result.x.value(), 1.5);
//     EXPECT_DOUBLE_EQ(result.x.uncertainty(), std::sqrt(0.1 * 0.1 + 0.05 * 0.05)); // RSS
//     EXPECT_DOUBLE_EQ(result.y.value(), 3.5);
//     EXPECT_DOUBLE_EQ(result.y.uncertainty(), std::sqrt(0.2 * 0.2 + 0.15 * 0.15));
//     EXPECT_DOUBLE_EQ(result.z.value(), 5.5);
//     EXPECT_DOUBLE_EQ(result.z.uncertainty(), std::sqrt(0.3 * 0.3 + 0.25 * 0.25));
//     EXPECT_DOUBLE_EQ(result.w.value(), 7.5);
//     EXPECT_DOUBLE_EQ(result.w.uncertainty(), std::sqrt(0.4 * 0.4 + 0.35 * 0.35));
// }

// TEST_F(Vector4DMeasurementsRSSTest, subtraction)
// {
//     using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t>;
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v1{meter_meas{1.0, 0.1}, meter_meas{2.0, 0.2}, meter_meas{3.0, 0.3}, meter_meas{4.0, 0.4}};
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v2{meter_meas{0.5, 0.05}, meter_meas{1.5, 0.15}, meter_meas{2.5, 0.25}, meter_meas{3.5, 0.35}};
//     auto result = v1 - v2;

//     EXPECT_DOUBLE_EQ(result.x.value(), 0.5);
//     EXPECT_DOUBLE_EQ(result.x.uncertainty(), std::sqrt(0.1 * 0.1 + 0.05 * 0.05)); // RSS
//     EXPECT_DOUBLE_EQ(result.y.value(), 0.5);
//     EXPECT_DOUBLE_EQ(result.y.uncertainty(), std::sqrt(0.2 * 0.2 + 0.15 * 0.15));
//     EXPECT_DOUBLE_EQ(result.z.value(), 0.5);
//     EXPECT_DOUBLE_EQ(result.z.uncertainty(), std::sqrt(0.3 * 0.3 + 0.25 * 0.25));
//     EXPECT_DOUBLE_EQ(result.w.value(), 0.5);
//     EXPECT_DOUBLE_EQ(result.w.uncertainty(), std::sqrt(0.4 * 0.4 + 0.35 * 0.35));
// }

// TEST_F(Vector4DMeasurementsRSSTest, scalar_multiplication)
// {
//     using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t>;
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v{meter_meas{1.0, 0.1}, meter_meas{2.0, 0.2}, meter_meas{3.0, 0.3}, meter_meas{4.0, 0.4}};
//     auto result = v * 2.0;

//     EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
//     EXPECT_DOUBLE_EQ(result.x.uncertainty(), 2.0 * 0.1); // Scaled uncertainty
//     EXPECT_DOUBLE_EQ(result.y.value(), 4.0);
//     EXPECT_DOUBLE_EQ(result.y.uncertainty(), 2.0 * 0.2);
//     EXPECT_DOUBLE_EQ(result.z.value(), 6.0);
//     EXPECT_DOUBLE_EQ(result.z.uncertainty(), 2.0 * 0.3);
//     EXPECT_DOUBLE_EQ(result.w.value(), 8.0);
//     EXPECT_DOUBLE_EQ(result.w.uncertainty(), 2.0 * 0.4);
// }

// TEST_F(Vector4DMeasurementsRSSTest, measurement_scalar_multiplication)
// {
//     using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t>;
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v{meter_meas{1.0, 0.1}, meter_meas{2.0, 0.2}, meter_meas{3.0, 0.3}, meter_meas{4.0, 0.4}};
//     auto scalar = pkr::units::measurement_rss_t<pkr::units::scalar_t>{2.0, 0.1};
//     auto result = v * scalar;

//     EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
//     // Uncertainty should be RSS of (value * scalar_uncertainty) and (scalar_value * v_uncertainty)
//     EXPECT_DOUBLE_EQ(result.x.uncertainty(), std::sqrt((1.0 * 0.1) * (1.0 * 0.1) + (2.0 * 0.1) * (2.0 * 0.1)));
// }

// TEST_F(Vector4DMeasurementsRSSTest, scalar_division)
// {
//     using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t>;
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v{meter_meas{2.0, 0.1}, meter_meas{4.0, 0.2}, meter_meas{6.0, 0.3}, meter_meas{8.0, 0.4}};
//     auto result = v / 2.0;

//     EXPECT_DOUBLE_EQ(result.x.value(), 1.0);
//     EXPECT_DOUBLE_EQ(result.x.uncertainty(), 0.1 / 2.0); // Scaled uncertainty
//     EXPECT_DOUBLE_EQ(result.y.value(), 2.0);
//     EXPECT_DOUBLE_EQ(result.y.uncertainty(), 0.2 / 2.0);
//     EXPECT_DOUBLE_EQ(result.z.value(), 3.0);
//     EXPECT_DOUBLE_EQ(result.z.uncertainty(), 0.3 / 2.0);
//     EXPECT_DOUBLE_EQ(result.w.value(), 4.0);
//     EXPECT_DOUBLE_EQ(result.w.uncertainty(), 0.4 / 2.0);
// }

// TEST_F(Vector4DMeasurementsRSSTest, negation)
// {
//     using meter_meas = pkr::units::measurement_rss_t<pkr::units::meter_t>;
//     pkr::units::vec_measurement_rss_4d_t<meter_meas> v{meter_meas{1.0, 0.1}, meter_meas{-2.0, 0.2}, meter_meas{3.0, 0.3}, meter_meas{-4.0, 0.4}};
//     auto result = -v;

//     EXPECT_DOUBLE_EQ(result.x.value(), -1.0);
//     EXPECT_DOUBLE_EQ(result.x.uncertainty(), 0.1); // Uncertainty unchanged
//     EXPECT_DOUBLE_EQ(result.y.value(), 2.0);
//     EXPECT_DOUBLE_EQ(result.y.uncertainty(), 0.2);
//     EXPECT_DOUBLE_EQ(result.z.value(), -3.0);
//     EXPECT_DOUBLE_EQ(result.z.uncertainty(), 0.3);
//     EXPECT_DOUBLE_EQ(result.w.value(), 4.0);
//     EXPECT_DOUBLE_EQ(result.w.uncertainty(), 0.4);
// }

} // namespace test
