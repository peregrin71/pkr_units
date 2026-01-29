#include <gtest/gtest.h>
#include <stdexcept>

#include <pkr_units/impl/cast/unit_cast.h>
#include <pkr_units/units/dimensionless/ratio.h>
#include <pkr_units/units/dimensionless/decibel_cast.h>

using namespace ::testing;

class DimensionlessCastTest : public Test
{
};

TEST_F(DimensionlessCastTest, RatioToPercentage)
{
    pkr::units::ratio_t ratio{0.5};
    auto percent = pkr::units::unit_cast<pkr::units::percentage_t>(ratio);
    EXPECT_DOUBLE_EQ(percent.value(), 50.0);
}

TEST_F(DimensionlessCastTest, PercentageToRatio)
{
    pkr::units::percentage_t percent{25.0};
    auto ratio = pkr::units::unit_cast<pkr::units::ratio_t>(percent);
    EXPECT_DOUBLE_EQ(ratio.value(), 0.25);
}

TEST_F(DimensionlessCastTest, RatioToDecibelPower)
{
    pkr::units::ratio_t ratio{10.0};
    auto db = pkr::units::unit_cast<pkr::units::decibel_power_t>(ratio);
    EXPECT_DOUBLE_EQ(db.value(), 10.0);
}

TEST_F(DimensionlessCastTest, RatioToDecibelAmplitude)
{
    pkr::units::ratio_t ratio{10.0};
    auto db = pkr::units::unit_cast<pkr::units::decibel_amplitude_t>(ratio);
    EXPECT_DOUBLE_EQ(db.value(), 20.0);
}

TEST_F(DimensionlessCastTest, DecibelPowerToRatio)
{
    pkr::units::decibel_power_t db{10.0};
    auto ratio = pkr::units::unit_cast<pkr::units::ratio_t>(db);
    EXPECT_NEAR(ratio.value(), 10.0, 1e-12);
}

TEST_F(DimensionlessCastTest, DecibelAmplitudeToRatio)
{
    pkr::units::decibel_amplitude_t db{20.0};
    auto ratio = pkr::units::unit_cast<pkr::units::ratio_t>(db);
    EXPECT_NEAR(ratio.value(), 10.0, 1e-12);
}

TEST_F(DimensionlessCastTest, PercentageToDecibelPower)
{
    pkr::units::percentage_t percent{50.0};
    auto db = pkr::units::unit_cast<pkr::units::decibel_power_t>(percent);
    EXPECT_NEAR(db.value(), -3.010299956, 1e-9);
}

TEST_F(DimensionlessCastTest, DecibelRejectsNonPositive)
{
    pkr::units::ratio_t ratio{0.0};
    EXPECT_THROW((pkr::units::unit_cast<pkr::units::decibel_power_t>(ratio)), std::invalid_argument);
    EXPECT_THROW((pkr::units::unit_cast<pkr::units::decibel_amplitude_t>(ratio)), std::invalid_argument);
}
