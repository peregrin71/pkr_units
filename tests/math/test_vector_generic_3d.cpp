#include <gtest/gtest.h>
#include <pkr_units/math/3d/vector_3d.h>

namespace test
{

using namespace ::testing;

class Vector3DTest : public Test
{
};

// ============================================================================
// Basic Vector Operations
// ============================================================================

TEST_F(Vector3DTest, construction)
{
    pkr::units::vec_3d_t<double> v{1.0, 2.0, 3.0};
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST_F(Vector3DTest, addition)
{
    pkr::units::vec_3d_t<double> v1{1.0, 2.0, 3.0};
    pkr::units::vec_3d_t<double> v2{0.5, 1.5, 2.5};
    auto result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x, 1.5);
    EXPECT_DOUBLE_EQ(result.y, 3.5);
    EXPECT_DOUBLE_EQ(result.z, 5.5);
}

TEST_F(Vector3DTest, subtraction)
{
    pkr::units::vec_3d_t<double> v1{1.0, 2.0, 3.0};
    pkr::units::vec_3d_t<double> v2{0.5, 1.5, 2.5};
    auto result = v1 - v2;

    EXPECT_DOUBLE_EQ(result.x, 0.5);
    EXPECT_DOUBLE_EQ(result.y, 0.5);
    EXPECT_DOUBLE_EQ(result.z, 0.5);
}

TEST_F(Vector3DTest, scalar_multiplication)
{
    pkr::units::vec_3d_t<double> v{1.0, 2.0, 3.0};
    auto result = v * 2.0;

    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
}

TEST_F(Vector3DTest, scalar_division_inplace)
{
    pkr::units::vec_3d_t<double> v{2.0, 4.0, 6.0};
    v /= 2.0;

    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST_F(Vector3DTest, dot_product)
{
    pkr::units::vec_3d_t<double> v1{1.0, 2.0, 3.0};
    pkr::units::vec_3d_t<double> v2{4.0, 5.0, 6.0};
    auto result = pkr::units::dot(v1, v2);

    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST_F(Vector3DTest, cross_product)
{
    pkr::units::vec_3d_t<double> v1{1.0, 2.0, 3.0};
    pkr::units::vec_3d_t<double> v2{4.0, 5.0, 6.0};
    auto result = pkr::units::cross(v1, v2);

    EXPECT_DOUBLE_EQ(result.x, -3.0);
    EXPECT_DOUBLE_EQ(result.y, 6.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
}

} // namespace test
