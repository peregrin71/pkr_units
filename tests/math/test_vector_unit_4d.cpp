#include <gtest/gtest.h>

#include <pkr_units/si_units.h>
#include <pkr_units/units/unit_math_4d.h>

namespace test
{

using namespace ::testing;

class Vector4DUnitsTest : public Test
{
};

// ============================================================================
// Vector with Units Operations
// ============================================================================

TEST_F(Vector4DUnitsTest, construction)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    EXPECT_DOUBLE_EQ(v.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(v.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(v.z.value(), 3.0);
    EXPECT_DOUBLE_EQ(v.w.value(), 4.0);
}

TEST_F(Vector4DUnitsTest, addition)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v1{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v2{pkr::units::meter_t{0.5}, pkr::units::meter_t{1.5}, pkr::units::meter_t{2.5}, pkr::units::meter_t{3.5}};
    auto result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 3.5);
    EXPECT_DOUBLE_EQ(result.z.value(), 5.5);
    EXPECT_DOUBLE_EQ(result.w.value(), 7.5);
}

TEST_F(Vector4DUnitsTest, subtraction)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v1{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v2{pkr::units::meter_t{0.5}, pkr::units::meter_t{1.5}, pkr::units::meter_t{2.5}, pkr::units::meter_t{3.5}};
    auto result = v1 - v2;

    EXPECT_DOUBLE_EQ(result.x.value(), 0.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 0.5);
    EXPECT_DOUBLE_EQ(result.z.value(), 0.5);
    EXPECT_DOUBLE_EQ(result.w.value(), 0.5);
}

TEST_F(Vector4DUnitsTest, scalar_multiplication)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    auto result = v * 2.0;

    EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 6.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 8.0);
}

TEST_F(Vector4DUnitsTest, unit_scalar_multiplication)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    auto result = 2.0 * v;

    EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 6.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 8.0);
}

TEST_F(Vector4DUnitsTest, scalar_t_multiplication)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    auto s = pkr::units::scalar_t{2.0};
    auto result = s * v;

    EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 6.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 8.0);
}

TEST_F(Vector4DUnitsTest, float_scalar_multiplication)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    float s = 2.0f;
    auto result = s * v;

    EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 6.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 8.0);
}

TEST_F(Vector4DUnitsTest, scalar_division)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{2.0}, pkr::units::meter_t{4.0}, pkr::units::meter_t{6.0}, pkr::units::meter_t{8.0}};
    auto result = v / 2.0;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 4.0);
}

TEST_F(Vector4DUnitsTest, scalar_t_division)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{2.0}, pkr::units::meter_t{4.0}, pkr::units::meter_t{6.0}, pkr::units::meter_t{8.0}};
    auto s = pkr::units::scalar_t{2.0};
    auto result = v / s;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 4.0);
}

TEST_F(Vector4DUnitsTest, float_scalar_division)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{2.0}, pkr::units::meter_t{4.0}, pkr::units::meter_t{6.0}, pkr::units::meter_t{8.0}};
    float s = 2.0f;
    auto result = v / s;

    EXPECT_DOUBLE_EQ(result.x.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 4.0);
}

TEST_F(Vector4DUnitsTest, negation)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{1.0}, pkr::units::meter_t{-2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{-4.0}};
    auto result = -v;

    EXPECT_DOUBLE_EQ(result.x.value(), -1.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.z.value(), -3.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 4.0);
}

TEST_F(Vector4DUnitsTest, inplace_scalar_t_multiplication)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    v *= pkr::units::scalar_t{2.0};

    EXPECT_DOUBLE_EQ(v.x.value(), 2.0);
    EXPECT_DOUBLE_EQ(v.y.value(), 4.0);
    EXPECT_DOUBLE_EQ(v.z.value(), 6.0);
    EXPECT_DOUBLE_EQ(v.w.value(), 8.0);
}

TEST_F(Vector4DUnitsTest, equality)
{
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v1{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v2{pkr::units::meter_t{1.0}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v3{pkr::units::meter_t{1.1}, pkr::units::meter_t{2.0}, pkr::units::meter_t{3.0}, pkr::units::meter_t{4.0}};

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

// ============================================================================
// Ratio Preservation Tests
// ============================================================================

TEST_F(Vector4DUnitsTest, ratio_preservation_km_addition)
{
    // km + km should result in km, not converted to m
    pkr::units::vec_4d_units_t<pkr::units::kilometer_t> v1{
        pkr::units::kilometer_t{1.0}, pkr::units::kilometer_t{2.0}, pkr::units::kilometer_t{3.0}, pkr::units::kilometer_t{4.0}};
    pkr::units::vec_4d_units_t<pkr::units::kilometer_t> v2{
        pkr::units::kilometer_t{0.5}, pkr::units::kilometer_t{1.5}, pkr::units::kilometer_t{2.5}, pkr::units::kilometer_t{3.5}};
    auto result = v1 + v2;

    // Result should be kilometer_t with preserved ratio
    EXPECT_DOUBLE_EQ(result.x.value(), 1.5); // 1.5 km (not 1500 m)
    EXPECT_DOUBLE_EQ(result.y.value(), 3.5); // 3.5 km (not 3500 m)
    EXPECT_DOUBLE_EQ(result.z.value(), 5.5);
    EXPECT_DOUBLE_EQ(result.w.value(), 7.5);
}

TEST_F(Vector4DUnitsTest, ratio_preservation_km_times_second)
{
    // km * s should result in km*s with km ratio preserved (not m*s)
    pkr::units::vec_4d_units_t<pkr::units::kilometer_t> v{
        pkr::units::kilometer_t{1.0}, pkr::units::kilometer_t{2.0}, pkr::units::kilometer_t{3.0}, pkr::units::kilometer_t{4.0}};
    auto second = pkr::units::second_t{2.0};
    auto result = v * second;

    // result.x should be km*s with value 2.0 (not 2000 m*s)
    // Result type: decltype(kilometer_t * second_t) = derived unit with km*s ratio
    EXPECT_DOUBLE_EQ(result.x.value(), 2.0);
    EXPECT_DOUBLE_EQ(result.y.value(), 4.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 6.0);
    EXPECT_DOUBLE_EQ(result.w.value(), 8.0);
}

TEST_F(Vector4DUnitsTest, ratio_preservation_km_per_second)
{
    // km / s should result in km/s (not m/s)
    pkr::units::vec_4d_units_t<pkr::units::kilometer_t> v{
        pkr::units::kilometer_t{1.0}, pkr::units::kilometer_t{2.0}, pkr::units::kilometer_t{3.0}, pkr::units::kilometer_t{4.0}};
    auto second = pkr::units::second_t{2.0};
    auto result = v / second;

    // result should be km/s with value 0.5, 1.0, 1.5, 2.0 (not 500, 1000, 1500, 2000 m/s)
    // Result type: decltype(kilometer_t / second_t) = derived unit with km/s ratio
    EXPECT_DOUBLE_EQ(result.x.value(), 0.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 1.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 1.5);
    EXPECT_DOUBLE_EQ(result.w.value(), 2.0);
}

TEST_F(Vector4DUnitsTest, ratio_preservation_km_add_meter)
{
    // km + m should result in km (preserving LHS unit/ratio)
    pkr::units::vec_4d_units_t<pkr::units::kilometer_t> v_km{
        pkr::units::kilometer_t{1.0}, pkr::units::kilometer_t{2.0}, pkr::units::kilometer_t{3.0}, pkr::units::kilometer_t{4.0}};
    pkr::units::vec_4d_units_t<pkr::units::meter_t> v_m{
        pkr::units::meter_t{500.0}, pkr::units::meter_t{1000.0}, pkr::units::meter_t{1500.0}, pkr::units::meter_t{2000.0}};
    auto result = v_km + v_m;

    // Result should be kilometer_t: 1.0 + 0.5 = 1.5 km
    EXPECT_DOUBLE_EQ(result.x.value(), 1.5);
    EXPECT_DOUBLE_EQ(result.y.value(), 3.0);
    EXPECT_DOUBLE_EQ(result.z.value(), 4.5);
    EXPECT_DOUBLE_EQ(result.w.value(), 6.0);
}

} // namespace test
