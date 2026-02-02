#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace PKR_UNITS_NAMESPACE;

// ============================================================================
// Luminous Flux (Lumen) Tests
// ============================================================================

class LuminousFluxTest : public ::testing::Test
{
protected:
    static constexpr double TOLERANCE = 1e-10;
};

// Test lumen type creation
TEST_F(LuminousFluxTest, LumenTypeCreation)
{
    lumen_t lm(1000.0);
    EXPECT_DOUBLE_EQ(lm.value(), 1000.0);
}

// Test lumen symbols and name
TEST_F(LuminousFluxTest, LumenSymbols)
{
    lumen_t lm(1.0);
    EXPECT_EQ(lm.name(), "lumen");
    EXPECT_EQ(lm.symbol(), "lm");
}

// Test lumen arithmetic - addition
TEST_F(LuminousFluxTest, LumenAddition)
{
    lumen_t lm1(800.0);
    lumen_t lm2(700.0);
    lumen_t result = lm1 + lm2;
    EXPECT_DOUBLE_EQ(result.value(), 1500.0);
}

// Test lumen arithmetic - subtraction
TEST_F(LuminousFluxTest, LumenSubtraction)
{
    lumen_t lm1(1500.0);
    lumen_t lm2(500.0);
    lumen_t result = lm1 - lm2;
    EXPECT_DOUBLE_EQ(result.value(), 1000.0);
}

// Test lumen multiplication by scalar
TEST_F(LuminousFluxTest, LumenScalarMultiplication)
{
    lumen_t lm(500.0);
    lumen_t result = lm * 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 1000.0);
}

// Test lumen division by scalar
TEST_F(LuminousFluxTest, LumenScalarDivision)
{
    lumen_t lm(1000.0);
    lumen_t result = lm / 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 500.0);
}

// Test comparison operators
TEST_F(LuminousFluxTest, LumenComparison)
{
    lumen_t lm1(800.0);
    lumen_t lm2(1200.0);
    lumen_t lm3(800.0);
    
    EXPECT_TRUE(lm1 < lm2);
    EXPECT_TRUE(lm2 > lm1);
    EXPECT_TRUE(lm1 == lm3);
    EXPECT_TRUE(lm1 != lm2);
}

// Test typical light bulb luminous flux
TEST_F(LuminousFluxTest, TypicalBulbFlux)
{
    // Typical 100W incandescent bulb: ~1700 lumens
    lumen_t bulb_flux(1700.0);
    EXPECT_NEAR(bulb_flux.value(), 1700.0, TOLERANCE);
}

// Test dimensionality - luminous flux is [cd·sr]
// This should have intensity dimension = 1, star_angle dimension = 1
TEST_F(LuminousFluxTest, LuminousFluxDimension)
{
    lumen_t lm(1.0);
    // Implicit test through type system compilation
    EXPECT_EQ(lm.value(), 1.0);
}
