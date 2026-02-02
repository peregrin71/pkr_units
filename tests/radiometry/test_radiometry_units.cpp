#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace PKR_UNITS_NAMESPACE;

// ============================================================================
// Radiometry Units Tests
// ============================================================================

class RadiantIntensityTest : public ::testing::Test
{
protected:
    static constexpr double TOLERANCE = 1e-10;
};

// Test watt_per_steradian type creation
TEST_F(RadiantIntensityTest, WattPerSteradianTypeCreation)
{
    watt_per_steradian_t intensity(100.0);
    EXPECT_DOUBLE_EQ(intensity.value(), 100.0);
}

// Test watt_per_steradian symbols
TEST_F(RadiantIntensityTest, WattPerSteradianSymbols)
{
    watt_per_steradian_t intensity(1.0);
    EXPECT_EQ(intensity.name(), "watt_per_steradian");
    EXPECT_EQ(intensity.symbol(), "W/sr");
}

// Test watt_per_steradian arithmetic
TEST_F(RadiantIntensityTest, WattPerSteradianArithmetic)
{
    watt_per_steradian_t intensity1(50.0);
    watt_per_steradian_t intensity2(30.0);

    watt_per_steradian_t sum = intensity1 + intensity2;
    EXPECT_DOUBLE_EQ(sum.value(), 80.0);

    watt_per_steradian_t diff = intensity1 - intensity2;
    EXPECT_DOUBLE_EQ(diff.value(), 20.0);
}

// Test watt_per_steradian comparison
TEST_F(RadiantIntensityTest, WattPerSteradianComparison)
{
    watt_per_steradian_t intensity1(100.0);
    watt_per_steradian_t intensity2(150.0);

    EXPECT_TRUE(intensity1 < intensity2);
    EXPECT_TRUE(intensity2 > intensity1);
}

// ============================================================================
// Radiance Tests
// ============================================================================

class RadianceTest : public ::testing::Test
{
protected:
    static constexpr double TOLERANCE = 1e-10;
};

// Test radiance type creation
TEST_F(RadianceTest, RadianceTypeCreation)
{
    radiance_t rad(5000.0);
    EXPECT_DOUBLE_EQ(rad.value(), 5000.0);
}

// Test radiance symbols
TEST_F(RadianceTest, RadianceSymbols)
{
    radiance_t rad(1.0);
    EXPECT_EQ(rad.name(), "radiance");
    EXPECT_EQ(rad.symbol(), "W/(m2·sr)");
}

// Test radiance arithmetic
TEST_F(RadianceTest, RadianceArithmetic)
{
    radiance_t rad1(1000000.0); // 1 MW/(m²·sr)
    radiance_t rad2(500000.0);

    radiance_t sum = rad1 + rad2;
    EXPECT_DOUBLE_EQ(sum.value(), 1500000.0);

    radiance_t diff = rad1 - rad2;
    EXPECT_DOUBLE_EQ(diff.value(), 500000.0);
}

// Test radiance comparison
TEST_F(RadianceTest, RadianceComparison)
{
    radiance_t rad1(1000000.0);
    radiance_t rad2(500000.0);

    EXPECT_TRUE(rad2 < rad1);
    EXPECT_TRUE(rad1 > rad2);
}

// Test watt_per_square_meter_per_steradian type creation
TEST_F(RadianceTest, WattPerSquareMeterPerSteradianTypeCreation)
{
    watt_per_square_meter_per_steradian_t rad(5000.0);
    EXPECT_DOUBLE_EQ(rad.value(), 5000.0);
}

// Test watt_per_square_meter_per_steradian symbols
TEST_F(RadianceTest, WattPerSquareMeterPerSteradianSymbols)
{
    watt_per_square_meter_per_steradian_t rad(1.0);
    EXPECT_EQ(rad.name(), "watt_per_square_meter_per_steradian");
    EXPECT_EQ(rad.symbol(), "W/(m2·sr)");
}

// ============================================================================
// Irradiance Tests
// ============================================================================

class IrradianceTest : public ::testing::Test
{
protected:
    static constexpr double TOLERANCE = 1e-10;
};

// Test irradiance type creation
TEST_F(IrradianceTest, IrradianceTypeCreation)
{
    irradiance_t irr(1000.0);
    EXPECT_DOUBLE_EQ(irr.value(), 1000.0);
}

// Test irradiance symbols
TEST_F(IrradianceTest, IrradianceSymbols)
{
    irradiance_t irr(1.0);
    EXPECT_EQ(irr.name(), "irradiance");
    EXPECT_EQ(irr.symbol(), "W/m2");
}

// Test irradiance arithmetic
TEST_F(IrradianceTest, IrradianceArithmetic)
{
    irradiance_t irr1(1361.0); // Solar constant at Earth orbit
    irradiance_t irr2(500.0);

    irradiance_t sum = irr1 + irr2;
    EXPECT_DOUBLE_EQ(sum.value(), 1861.0);

    irradiance_t diff = irr1 - irr2;
    EXPECT_DOUBLE_EQ(diff.value(), 861.0);
}

// Test irradiance comparison
TEST_F(IrradianceTest, IrradianceComparison)
{
    irradiance_t irr1(1361.0);
    irradiance_t irr2(1000.0);

    EXPECT_TRUE(irr2 < irr1);
    EXPECT_TRUE(irr1 > irr2);
}

// Test typical solar irradiance value
TEST_F(IrradianceTest, SolarConstant)
{
    // Solar constant: ~1361 W/m²
    irradiance_t solar(1361.0);
    EXPECT_NEAR(solar.value(), 1361.0, TOLERANCE);
}

// Test watt_per_square_meter type creation
TEST_F(IrradianceTest, WattPerSquareMeterTypeCreation)
{
    watt_per_square_meter_t irr(1000.0);
    EXPECT_DOUBLE_EQ(irr.value(), 1000.0);
}

// Test watt_per_square_meter symbols
TEST_F(IrradianceTest, WattPerSquareMeterSymbols)
{
    watt_per_square_meter_t irr(1.0);
    EXPECT_EQ(irr.name(), "watt_per_square_meter");
    EXPECT_EQ(irr.symbol(), "W/m2");
}
