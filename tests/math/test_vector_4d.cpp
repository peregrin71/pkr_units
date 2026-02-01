#include <gtest/gtest.h>
#include <pkr_units/math/4d/vector_4d.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;

class Vector4DTest : public Test
{
};

// ============================================================================
// Basic Vector Operations
// ============================================================================

TEST_F(Vector4DTest, construction)
{
    pkr::units::math::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
    EXPECT_DOUBLE_EQ(v.w, 4.0);
}

TEST_F(Vector4DTest, addition)
{
    pkr::units::math::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::math::vec_4d_t<double> v2{0.5, 1.5, 2.5, 3.5};
    auto result = v1 + v2;
    
    EXPECT_DOUBLE_EQ(result.x, 1.5);
    EXPECT_DOUBLE_EQ(result.y, 3.5);
    EXPECT_DOUBLE_EQ(result.z, 5.5);
    EXPECT_DOUBLE_EQ(result.w, 7.5);
}

TEST_F(Vector4DTest, subtraction)
{
    pkr::units::math::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::math::vec_4d_t<double> v2{0.5, 1.5, 2.5, 3.5};
    auto result = v1 - v2;
    
    EXPECT_DOUBLE_EQ(result.x, 0.5);
    EXPECT_DOUBLE_EQ(result.y, 0.5);
    EXPECT_DOUBLE_EQ(result.z, 0.5);
    EXPECT_DOUBLE_EQ(result.w, 0.5);
}

TEST_F(Vector4DTest, scalar_multiplication)
{
    pkr::units::math::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = v * 2.0;
    
    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
    EXPECT_DOUBLE_EQ(result.w, 8.0);
}

TEST_F(Vector4DTest, scalar_division)
{
    pkr::units::math::vec_4d_t<double> v{2.0, 4.0, 6.0, 8.0};
    auto result = v / 2.0;
    
    EXPECT_DOUBLE_EQ(result.x, 1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
    EXPECT_DOUBLE_EQ(result.w, 4.0);
}

TEST_F(Vector4DTest, negation)
{
    pkr::units::math::vec_4d_t<double> v{1.0, -2.0, 3.0, -4.0};
    auto result = -v;
    
    EXPECT_DOUBLE_EQ(result.x, -1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
    EXPECT_DOUBLE_EQ(result.w, 4.0);
}

TEST_F(Vector4DTest, equality)
{
    pkr::units::math::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::math::vec_4d_t<double> v2{1.0, 2.0, 3.0, 4.0};
    pkr::units::math::vec_4d_t<double> v3{1.1, 2.0, 3.0, 4.0};
    
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST_F(Vector4DTest, inequality)
{
    pkr::units::math::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::math::vec_4d_t<double> v2{1.1, 2.0, 3.0, 4.0};
    
    EXPECT_TRUE(v1 != v2);
}

} // namespace test