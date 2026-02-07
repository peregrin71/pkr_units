#include <gtest/gtest.h>

#include <pkr_units/si_units.h>
#include <pkr_units/units/unit_math_3d.h>

namespace test
{

using namespace ::testing;

class Vector3DUnitsTest : public Test
{
};

// ============================================================================
// Vector with Units Operations
// ============================================================================

TEST_F(Vector3DUnitsTest, construction)
{
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v{
        pkr::units::meter_t<double>{1.0}, pkr::units::meter_t<double>{2.0}, pkr::units::meter_t<double>{3.0}};
    EXPECT_DOUBLE_EQ(v.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(v.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(v.z.value(), 3.0);
}

TEST_F(Vector3DUnitsTest, addition)
{
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v1{
        pkr::units::meter_t<double>{1.0}, pkr::units::meter_t<double>{2.0}, pkr::units::meter_t<double>{3.0}};
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v2{
        pkr::units::meter_t<double>{0.5}, pkr::units::meter_t<double>{1.5}, pkr::units::meter_t<double>{2.5}};
    auto result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 3.5);
    EXPECT_DOUBLE_EQ(result.z.value(), 5.5);
}

TEST_F(Vector3DUnitsTest, subtraction)
{
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v1{
        pkr::units::meter_t<double>{1.0}, pkr::units::meter_t<double>{2.0}, pkr::units::meter_t<double>{3.0}};
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v2{
        pkr::units::meter_t<double>{0.5}, pkr::units::meter_t<double>{1.5}, pkr::units::meter_t<double>{2.5}};
    auto result = v1 - v2;

    EXPECT_DOUBLE_EQ(result.x.value(), 0.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 0.5);
    EXPECT_DOUBLE_EQ(result.z.value(), 0.5);
}

TEST_F(Vector3DUnitsTest, scalar_multiplication)
{
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v{
        pkr::units::meter_t<double>{1.0}, pkr::units::meter_t<double>{2.0}, pkr::units::meter_t<double>{3.0}};
    auto result = v * 2.0;

    EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 6.0);
}

TEST_F(Vector3DUnitsTest, scalar_division_inplace)
{
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v{
        pkr::units::meter_t<double>{2.0}, pkr::units::meter_t<double>{4.0}, pkr::units::meter_t<double>{6.0}};
    v /= 2.0;

    EXPECT_DOUBLE_EQ(v.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(v.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(v.z.value(), 3.0);
}

TEST_F(Vector3DUnitsTest, ratio_preservation_km_addition)
{
    pkr::units::vec_3d_units_t<pkr::units::kilometer_t<double>> v1{
        pkr::units::kilometer_t<double>{1.0}, pkr::units::kilometer_t<double>{2.0}, pkr::units::kilometer_t<double>{3.0}};
    pkr::units::vec_3d_units_t<pkr::units::kilometer_t<double>> v2{
        pkr::units::kilometer_t<double>{0.5}, pkr::units::kilometer_t<double>{1.5}, pkr::units::kilometer_t<double>{2.5}};
    auto result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 3.5);
    EXPECT_DOUBLE_EQ(result.z.value(), 5.5);
}

TEST_F(Vector3DUnitsTest, ratio_preservation_km_add_meter)
{
    pkr::units::vec_3d_units_t<pkr::units::kilometer_t<double>> v_km{
        pkr::units::kilometer_t<double>{1.0}, pkr::units::kilometer_t<double>{2.0}, pkr::units::kilometer_t<double>{3.0}};
    pkr::units::vec_3d_units_t<pkr::units::meter_t<double>> v_m{
        pkr::units::meter_t<double>{500.0}, pkr::units::meter_t<double>{1000.0}, pkr::units::meter_t<double>{1500.0}};
    auto result = v_km + v_m;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 4.5);
}

} // namespace test
