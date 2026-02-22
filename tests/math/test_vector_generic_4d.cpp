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
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
    EXPECT_DOUBLE_EQ(v.w, 4.0);
}

TEST_F(Vector4DTest, addition)
{
    pkr::units::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::vec_4d_t<double> v2{0.5, 1.5, 2.5, 3.5};
    auto result = v1 + v2;

    EXPECT_DOUBLE_EQ(result.x, 1.5);
    EXPECT_DOUBLE_EQ(result.y, 3.5);
    EXPECT_DOUBLE_EQ(result.z, 5.5);
    EXPECT_DOUBLE_EQ(result.w, 7.5);
}

TEST_F(Vector4DTest, subtraction)
{
    pkr::units::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::vec_4d_t<double> v2{0.5, 1.5, 2.5, 3.5};
    auto result = v1 - v2;

    EXPECT_DOUBLE_EQ(result.x, 0.5);
    EXPECT_DOUBLE_EQ(result.y, 0.5);
    EXPECT_DOUBLE_EQ(result.z, 0.5);
    EXPECT_DOUBLE_EQ(result.w, 0.5);
}

TEST_F(Vector4DTest, scalar_multiplication)
{
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = v * 2.0;

    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
    EXPECT_DOUBLE_EQ(result.w, 8.0);
}

TEST_F(Vector4DTest, scalar_division)
{
    pkr::units::vec_4d_t<double> v{2.0, 4.0, 6.0, 8.0};
    auto result = v / 2.0;

    EXPECT_DOUBLE_EQ(result.x, 1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
    EXPECT_DOUBLE_EQ(result.w, 4.0);
}

TEST_F(Vector4DTest, negation)
{
    pkr::units::vec_4d_t<double> v{1.0, -2.0, 3.0, -4.0};
    auto result = -v;

    EXPECT_DOUBLE_EQ(result.x, -1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
    EXPECT_DOUBLE_EQ(result.w, 4.0);
}

TEST_F(Vector4DTest, equality)
{
    pkr::units::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::vec_4d_t<double> v2{1.0, 2.0, 3.0, 4.0};
    pkr::units::vec_4d_t<double> v3{1.1, 2.0, 3.0, 4.0};

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST_F(Vector4DTest, inequality)
{
    pkr::units::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::vec_4d_t<double> v2{1.1, 2.0, 3.0, 4.0};

    EXPECT_TRUE(v1 != v2);
}
TEST_F(Vector4DTest, scale_vector_positive)
{
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = v * 2.0;
    
    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
    EXPECT_DOUBLE_EQ(result.w, 8.0);
}

TEST_F(Vector4DTest, scale_vector_negative)
{
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = v * -2.0;
    
    EXPECT_DOUBLE_EQ(result.x, -2.0);
    EXPECT_DOUBLE_EQ(result.y, -4.0);
    EXPECT_DOUBLE_EQ(result.z, -6.0);
    EXPECT_DOUBLE_EQ(result.w, -8.0);
}

TEST_F(Vector4DTest, divide_vector_by_scalar)
{
    pkr::units::vec_4d_t<double> v{4.0, 8.0, 12.0, 16.0};
    auto result = v / 2.0;
    
    EXPECT_DOUBLE_EQ(result.x, 2.0);
    EXPECT_DOUBLE_EQ(result.y, 4.0);
    EXPECT_DOUBLE_EQ(result.z, 6.0);
    EXPECT_DOUBLE_EQ(result.w, 8.0);
}

TEST_F(Vector4DTest, scalar_times_vector)
{
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = 3.0 * v;
    
    EXPECT_DOUBLE_EQ(result.x, 3.0);
    EXPECT_DOUBLE_EQ(result.y, 6.0);
    EXPECT_DOUBLE_EQ(result.z, 9.0);
    EXPECT_DOUBLE_EQ(result.w, 12.0);
}

TEST_F(Vector4DTest, negation_operator)
{
    pkr::units::vec_4d_t<double> v{1.0, -2.0, 3.0, -4.0};
    auto result = -v;
    
    EXPECT_DOUBLE_EQ(result.x, -1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
    EXPECT_DOUBLE_EQ(result.w, 4.0);
}

TEST_F(Vector4DTest, equality_all_components_zero)
{
    pkr::units::vec_4d_t<double> v1{0.0, 0.0, 0.0, 0.0};
    pkr::units::vec_4d_t<double> v2{0.0, 0.0, 0.0, 0.0};
    
    EXPECT_TRUE(v1 == v2);
}

TEST_F(Vector4DTest, inequality_different_w_component)
{
    pkr::units::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::vec_4d_t<double> v2{1.0, 2.0, 3.0, 4.5};
    
    EXPECT_TRUE(v1 != v2);
}

TEST_F(Vector4DTest, add_zero_vector)
{
    pkr::units::vec_4d_t<double> v1{1.0, 2.0, 3.0, 4.0};
    pkr::units::vec_4d_t<double> v_zero{0.0, 0.0, 0.0, 0.0};
    auto result = v1 + v_zero;
    
    EXPECT_DOUBLE_EQ(result.x, 1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
    EXPECT_DOUBLE_EQ(result.w, 4.0);
}

TEST_F(Vector4DTest, subtract_from_zero_vector)
{
    pkr::units::vec_4d_t<double> v_zero{0.0, 0.0, 0.0, 0.0};
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = v_zero - v;
    
    EXPECT_DOUBLE_EQ(result.x, -1.0);
    EXPECT_DOUBLE_EQ(result.y, -2.0);
    EXPECT_DOUBLE_EQ(result.z, -3.0);
    EXPECT_DOUBLE_EQ(result.w, -4.0);
}

TEST_F(Vector4DTest, scale_by_zero)
{
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = v * 0.0;
    
    EXPECT_DOUBLE_EQ(result.x, 0.0);
    EXPECT_DOUBLE_EQ(result.y, 0.0);
    EXPECT_DOUBLE_EQ(result.z, 0.0);
    EXPECT_DOUBLE_EQ(result.w, 0.0);
}

TEST_F(Vector4DTest, scale_by_one)
{
    pkr::units::vec_4d_t<double> v{1.0, 2.0, 3.0, 4.0};
    auto result = v * 1.0;
    
    EXPECT_DOUBLE_EQ(result.x, 1.0);
    EXPECT_DOUBLE_EQ(result.y, 2.0);
    EXPECT_DOUBLE_EQ(result.z, 3.0);
    EXPECT_DOUBLE_EQ(result.w, 4.0);
}

TEST_F(Vector4DTest, divide_by_one)
{
    pkr::units::vec_4d_t<double> v{5.0, 10.0, 15.0, 20.0};
    auto result = v / 1.0;
    
    EXPECT_DOUBLE_EQ(result.x, 5.0);
    EXPECT_DOUBLE_EQ(result.y, 10.0);
    EXPECT_DOUBLE_EQ(result.z, 15.0);
    EXPECT_DOUBLE_EQ(result.w, 20.0);
}

TEST_F(Vector4DTest, equality_with_negative_values)
{
    pkr::units::vec_4d_t<double> v1{-1.5, -2.5, -3.5, -4.5};
    pkr::units::vec_4d_t<double> v2{-1.5, -2.5, -3.5, -4.5};
    
    EXPECT_TRUE(v1 == v2);
}

TEST_F(Vector4DTest, mixed_positive_negative_components)
{
    pkr::units::vec_4d_t<double> v1{1.0, -2.0, 3.0, -4.0};
    pkr::units::vec_4d_t<double> v2{1.0, -2.0, 3.0, -4.0};
    
    EXPECT_TRUE(v1 == v2);
}
} // namespace test
