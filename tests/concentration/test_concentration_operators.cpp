#include <gtest/gtest.h>
#include <pkr_units/units/derived/concentration.h>
#include <limits>

class SiConcentrationOperatorsTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Molar concentration operators
TEST_F(SiConcentrationOperatorsTest, add_molar)
{
    pkr::units::molar_concentration_t conc1(1.0);
    pkr::units::molar_concentration_t conc2(0.5);
    auto result = conc1 + conc2;
    EXPECT_DOUBLE_EQ(*result, 1.5);
}

TEST_F(SiConcentrationOperatorsTest, add_millimolar_to_molar)
{
    pkr::units::molar_concentration_t conc1(1.0);           // 1 M
    pkr::units::millimolar_concentration_t conc2(500.0);    // 500 mM = 0.5 M
    auto result = conc1 + conc2;
    EXPECT_DOUBLE_EQ(*result, 1.5);  // Result in M
}

TEST_F(SiConcentrationOperatorsTest, multiply_molar_by_scalar)
{
    pkr::units::molar_concentration_t conc(1.0);
    auto result = conc * 3.0;
    EXPECT_DOUBLE_EQ(*result, 3.0);
}

TEST_F(SiConcentrationOperatorsTest, equal_molar)
{
    pkr::units::molar_concentration_t conc1(1.0);
    pkr::units::molar_concentration_t conc2(1.0);
    EXPECT_TRUE(conc1 == conc2);
}

TEST_F(SiConcentrationOperatorsTest, not_equal_molar)
{
    pkr::units::molar_concentration_t conc1(1.0);
    pkr::units::molar_concentration_t conc2(0.5);
    EXPECT_TRUE(conc1 != conc2);
}