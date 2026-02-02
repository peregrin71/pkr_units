#include <gtest/gtest.h>
#include <pkr_units/measurements/measurement_rss_3d.h>
#include <pkr_units/measurements/decl/measurement_rss_decl.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;

class Vector3DMeasurementsRSSTest : public Test
{
};

// ============================================================================
// Vector with Measurements RSS Operations
// ============================================================================

TEST_F(Vector3DMeasurementsRSSTest, construction)
{
    pkr::units::vec_measurement_rss_3d_t<pkr::units::meter_t> v{{1.0, 0.1}, {2.0, 0.2}, {3.0, 0.3}};
    EXPECT_DOUBLE_EQ(v.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(v.x.uncertainty(), 0.1);
    EXPECT_DOUBLE_EQ(v.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(v.y.uncertainty(), 0.2);
    EXPECT_DOUBLE_EQ(v.z.value(), 3.0);
    EXPECT_DOUBLE_EQ(v.z.uncertainty(), 0.3);
}

} // namespace test
