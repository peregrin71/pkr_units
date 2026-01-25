#include <gtest/gtest.h>
#include <pkr_units/units/derived/concentration.h>
#include <pkr_units/impl/cast/unit_cast.h>
#include <limits>

class SiConcentrationTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Molar concentration tests
TEST_F(SiConcentrationTest, mole_per_cubic_meter_construction)
{
    pkr::units::mole_per_cubic_meter_concentration_t conc(1000.0);
    EXPECT_DOUBLE_EQ(*conc, 1000.0);
}

TEST_F(SiConcentrationTest, mole_per_liter_construction)
{
    pkr::units::mole_per_liter_concentration_t conc(2.0);
    EXPECT_DOUBLE_EQ(*conc, 2.0);
}

TEST_F(SiConcentrationTest, molar_construction)
{
    pkr::units::molar_concentration_t conc(0.5);
    EXPECT_DOUBLE_EQ(*conc, 0.5);
}

TEST_F(SiConcentrationTest, millimolar_construction)
{
    pkr::units::millimolar_concentration_t conc(100.0);
    EXPECT_DOUBLE_EQ(*conc, 100.0);
}

TEST_F(SiConcentrationTest, micromolar_construction)
{
    pkr::units::micromolar_concentration_t conc(50.0);
    EXPECT_DOUBLE_EQ(*conc, 50.0);
}

TEST_F(SiConcentrationTest, nanomolar_construction)
{
    pkr::units::nanomolar_concentration_t conc(25.0);
    EXPECT_DOUBLE_EQ(*conc, 25.0);
}

TEST_F(SiConcentrationTest, picomolar_construction)
{
    pkr::units::picomolar_concentration_t conc(10.0);
    EXPECT_DOUBLE_EQ(*conc, 10.0);
}

TEST_F(SiConcentrationTest, osmole_per_liter_construction)
{
    pkr::units::osmole_per_liter_concentration_t conc(0.3);
    EXPECT_DOUBLE_EQ(*conc, 0.3);
}

TEST_F(SiConcentrationTest, milliosmole_per_liter_construction)
{
    pkr::units::milliosmole_per_liter_concentration_t conc(300.0);
    EXPECT_DOUBLE_EQ(*conc, 300.0);
}

TEST_F(SiConcentrationTest, copy_constructor)
{
    pkr::units::molar_concentration_t conc1(1.0);
    pkr::units::molar_concentration_t conc2(conc1);
    EXPECT_DOUBLE_EQ(*conc2, 1.0);
}

TEST_F(SiConcentrationTest, move_constructor)
{
    pkr::units::molar_concentration_t conc1(1.0);
    pkr::units::molar_concentration_t conc2(std::move(conc1));
    EXPECT_DOUBLE_EQ(*conc2, 1.0);
}

TEST_F(SiConcentrationTest, copy_assignment)
{
    pkr::units::molar_concentration_t conc1(1.0);
    pkr::units::molar_concentration_t conc2(0.0);
    conc2 = conc1;
    EXPECT_DOUBLE_EQ(*conc2, 1.0);
}

TEST_F(SiConcentrationTest, move_assignment)
{
    pkr::units::molar_concentration_t conc1(1.0);
    pkr::units::molar_concentration_t conc2(0.0);
    conc2 = std::move(conc1);
    EXPECT_DOUBLE_EQ(*conc2, 1.0);
}

TEST_F(SiConcentrationTest, molar_has_correct_dimension)
{
    pkr::units::molar_concentration_t conc(1.0);
    using dimension = typename std::decay_t<decltype(conc)>::dimension_type;
    ASSERT_EQ(dimension::value, pkr::units::molar_concentration_v);
}

