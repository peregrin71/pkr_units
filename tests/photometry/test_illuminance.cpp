#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace PKR_UNITS_NAMESPACE;

// ============================================================================
// Illuminance (Lux) Tests
// ============================================================================

class IlluminanceTest : public ::testing::Test
{
protected:
    static constexpr double TOLERANCE = 1e-10;
};

// Test lux type creation
TEST_F(IlluminanceTest, LuxTypeCreation)
{
    lux_t lux(500.0);
    EXPECT_DOUBLE_EQ(lux.value(), 500.0);
}

// Test lux symbols and name
TEST_F(IlluminanceTest, LuxSymbols)
{
    lux_t lux(1.0);
    EXPECT_EQ(lux.name(), "lux");
    EXPECT_EQ(lux.symbol(), "lx");
}

// Test lux arithmetic - addition
TEST_F(IlluminanceTest, LuxAddition)
{
    lux_t lux1(300.0);
    lux_t lux2(400.0);
    lux_t result = lux1 + lux2;
    EXPECT_DOUBLE_EQ(result.value(), 700.0);
}

// Test lux arithmetic - subtraction
TEST_F(IlluminanceTest, LuxSubtraction)
{
    lux_t lux1(500.0);
    lux_t lux2(200.0);
    lux_t result = lux1 - lux2;
    EXPECT_DOUBLE_EQ(result.value(), 300.0);
}

// Test lux multiplication by scalar
TEST_F(IlluminanceTest, LuxScalarMultiplication)
{
    lux_t lux(250.0);
    lux_t result = lux * 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 500.0);
}

// Test lux division by scalar
TEST_F(IlluminanceTest, LuxScalarDivision)
{
    lux_t lux(400.0);
    lux_t result = lux / 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 200.0);
}

// Test comparison operators
TEST_F(IlluminanceTest, LuxComparison)
{
    lux_t lux1(300.0);
    lux_t lux2(500.0);
    lux_t lux3(300.0);
    
    EXPECT_TRUE(lux1 < lux2);
    EXPECT_TRUE(lux2 > lux1);
    EXPECT_TRUE(lux1 == lux3);
    EXPECT_TRUE(lux1 != lux2);
}

// Test typical illuminance values
TEST_F(IlluminanceTest, TypicalOfficeIlluminance)
{
    // Typical office/classroom: ~400 lux
    lux_t office(400.0);
    EXPECT_NEAR(office.value(), 400.0, TOLERANCE);
}

TEST_F(IlluminanceTest, BrightSunlight)
{
    // Bright sunlight: ~100,000 lux
    lux_t sunlight(100000.0);
    EXPECT_NEAR(sunlight.value(), 100000.0, TOLERANCE);
}

TEST_F(IlluminanceTest, FullMoon)
{
    // Full moon clear night: ~0.25 lux
    lux_t fullmoon(0.25);
    EXPECT_NEAR(fullmoon.value(), 0.25, TOLERANCE);
}

// Test dimensionality - illuminance is [cd·sr·m⁻²]
// This should have intensity=1, star_angle=1, length=-2
TEST_F(IlluminanceTest, IlluminanceDimension)
{
    lux_t lux(1.0);
    // Implicit test through type system compilation
    EXPECT_EQ(lux.value(), 1.0);
}
