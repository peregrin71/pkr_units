#include <gtest/gtest.h>
#include <pkr_units/units/derived/concentration.h>
#include <pkr_units/impl/cast/unit_cast.h>

class SiConcentrationCastTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Molar concentration casting tests
TEST_F(SiConcentrationCastTest, cast_mole_per_cubic_meter_to_mole_per_liter)
{
    pkr::units::mole_per_cubic_meter_concentration_t conc(1000.0);
    pkr::units::mole_per_liter_concentration_t result = unit_cast<pkr::units::mole_per_liter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_mole_per_liter_to_mole_per_cubic_meter)
{
    pkr::units::mole_per_liter_concentration_t conc(1.0);
    pkr::units::mole_per_cubic_meter_concentration_t result = unit_cast<pkr::units::mole_per_cubic_meter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1000.0);
}

TEST_F(SiConcentrationCastTest, cast_molar_to_millimolar)
{
    pkr::units::molar_concentration_t conc(1.0);
    pkr::units::millimolar_concentration_t result = pkr::units::unit_cast<pkr::units::millimolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1000.0);
}

TEST_F(SiConcentrationCastTest, cast_millimolar_to_molar)
{
    pkr::units::millimolar_concentration_t conc(1000.0);
    pkr::units::molar_concentration_t result = pkr::units::unit_cast<pkr::units::molar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_molar_to_micromolar)
{
    pkr::units::molar_concentration_t conc(1.0);
    pkr::units::micromolar_concentration_t result = pkr::units::unit_cast<pkr::units::micromolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1000000.0);
}

TEST_F(SiConcentrationCastTest, cast_micromolar_to_molar)
{
    pkr::units::micromolar_concentration_t conc(1000000.0);
    pkr::units::molar_concentration_t result = pkr::units::unit_cast<pkr::units::molar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_millimolar_to_micromolar)
{
    pkr::units::millimolar_concentration_t conc(1.0);
    pkr::units::micromolar_concentration_t result = pkr::units::unit_cast<pkr::units::micromolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1000.0);
}

TEST_F(SiConcentrationCastTest, cast_micromolar_to_millimolar)
{
    pkr::units::micromolar_concentration_t conc(1000.0);
    pkr::units::millimolar_concentration_t result = pkr::units::unit_cast<pkr::units::millimolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_micromolar_to_nanomolar)
{
    pkr::units::micromolar_concentration_t conc(1.0);
    pkr::units::nanomolar_concentration_t result = pkr::units::unit_cast<pkr::units::nanomolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1000.0);
}

TEST_F(SiConcentrationCastTest, cast_nanomolar_to_micromolar)
{
    pkr::units::nanomolar_concentration_t conc(1000.0);
    pkr::units::micromolar_concentration_t result = pkr::units::unit_cast<pkr::units::micromolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_nanomolar_to_picomolar)
{
    pkr::units::nanomolar_concentration_t conc(1.0);
    pkr::units::picomolar_concentration_t result = pkr::units::unit_cast<pkr::units::picomolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1000.0);
}

TEST_F(SiConcentrationCastTest, cast_picomolar_to_nanomolar)
{
    pkr::units::picomolar_concentration_t conc(1000.0);
    pkr::units::nanomolar_concentration_t result = pkr::units::unit_cast<pkr::units::nanomolar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_mole_per_liter_to_mole_per_cubic_centimeter)
{
    pkr::units::mole_per_liter_concentration_t conc(1.0);
    pkr::units::mole_per_cubic_centimeter_concentration_t result = pkr::units::unit_cast<pkr::units::mole_per_cubic_centimeter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 0.001);
}

TEST_F(SiConcentrationCastTest, cast_mole_per_cubic_centimeter_to_mole_per_liter)
{
    pkr::units::mole_per_cubic_centimeter_concentration_t conc(0.001);
    pkr::units::mole_per_liter_concentration_t result = pkr::units::unit_cast<pkr::units::mole_per_liter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_mole_per_cubic_centimeter_to_mole_per_milliliter)
{
    pkr::units::mole_per_cubic_centimeter_concentration_t conc(1.0);
    pkr::units::mole_per_milliliter_concentration_t result = pkr::units::unit_cast<pkr::units::mole_per_milliliter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_mole_per_milliliter_to_mole_per_cubic_centimeter)
{
    pkr::units::mole_per_milliliter_concentration_t conc(1.0);
    pkr::units::mole_per_cubic_centimeter_concentration_t result = pkr::units::unit_cast<pkr::units::mole_per_cubic_centimeter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

// Osmolarity casting tests
TEST_F(SiConcentrationCastTest, cast_osmole_per_liter_to_milliosmole_per_liter)
{
    pkr::units::osmole_per_liter_concentration_t conc(1.0);
    pkr::units::milliosmole_per_liter_concentration_t result = pkr::units::unit_cast<pkr::units::milliosmole_per_liter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1000.0);
}

TEST_F(SiConcentrationCastTest, cast_milliosmole_per_liter_to_osmole_per_liter)
{
    pkr::units::milliosmole_per_liter_concentration_t conc(1000.0);
    pkr::units::osmole_per_liter_concentration_t result = pkr::units::unit_cast<pkr::units::osmole_per_liter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_molar_to_osmole_per_liter)
{
    pkr::units::molar_concentration_t conc(1.0);
    pkr::units::osmole_per_liter_concentration_t result = pkr::units::unit_cast<pkr::units::osmole_per_liter_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}

TEST_F(SiConcentrationCastTest, cast_osmole_per_liter_to_molar)
{
    pkr::units::osmole_per_liter_concentration_t conc(1.0);
    pkr::units::molar_concentration_t result = pkr::units::unit_cast<pkr::units::molar_concentration_t>(conc);
    EXPECT_DOUBLE_EQ(*result, 1.0);
}
