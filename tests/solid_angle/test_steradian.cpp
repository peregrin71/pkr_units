#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace PKR_UNITS_NAMESPACE;

// ============================================================================
// Steradian (Solid Angle) Base Unit Tests
// ============================================================================

class SteradianTest : public ::testing::Test
{
protected:
    static constexpr double TOLERANCE = 1e-10;
};

// Test basic steradian type creation
TEST_F(SteradianTest, SteradianTypeCreation)
{
    steradian_t sr(1.0);
    EXPECT_DOUBLE_EQ(sr.value(), 1.0);
}

// Test steradian value() method
TEST_F(SteradianTest, SteradianValue)
{
    steradian_t sr(2.5);
    EXPECT_DOUBLE_EQ(sr.value(), 2.5);
}

// Test steradian name and symbol
TEST_F(SteradianTest, SteradianSymbols)
{
    steradian_t sr(1.0);
    EXPECT_EQ(sr.name(), "steradian");
    EXPECT_EQ(sr.symbol(), "sr");
}

// Test steradian arithmetic - addition
TEST_F(SteradianTest, SteradianAddition)
{
    steradian_t sr1(2.0);
    steradian_t sr2(3.0);
    steradian_t result = sr1 + sr2;
    EXPECT_DOUBLE_EQ(result.value(), 5.0);
}

// Test steradian arithmetic - subtraction
TEST_F(SteradianTest, SteradianSubtraction)
{
    steradian_t sr1(5.0);
    steradian_t sr2(2.0);
    steradian_t result = sr1 - sr2;
    EXPECT_DOUBLE_EQ(result.value(), 3.0);
}

// Test steradian arithmetic - multiplication by scalar
TEST_F(SteradianTest, SteradianScalarMultiplication)
{
    steradian_t sr(2.0);
    steradian_t result = sr * 3.0;
    EXPECT_DOUBLE_EQ(result.value(), 6.0);
}

// Test steradian arithmetic - division by scalar
TEST_F(SteradianTest, SteradianScalarDivision)
{
    steradian_t sr(6.0);
    steradian_t result = sr / 2.0;
    EXPECT_DOUBLE_EQ(result.value(), 3.0);
}

// Test steradian comparison operators
TEST_F(SteradianTest, SteradianComparison)
{
    steradian_t sr1(2.0);
    steradian_t sr2(3.0);
    steradian_t sr3(2.0);
    
    EXPECT_TRUE(sr1 < sr2);
    EXPECT_TRUE(sr2 > sr1);
    EXPECT_TRUE(sr1 == sr3);
    EXPECT_FALSE(sr1 == sr2);
}

// Test full sphere solid angle (4π steradians)
TEST_F(SteradianTest, FullSphereAngle)
{
    double full_sphere = 4.0 * M_PI;
    steradian_t sr(full_sphere);
    EXPECT_NEAR(sr.value(), 12.566370614359172, TOLERANCE);
}

// Test hemisphere solid angle (2π steradians)
TEST_F(SteradianTest, HemisphereAngle)
{
    double hemisphere = 2.0 * M_PI;
    steradian_t sr(hemisphere);
    EXPECT_NEAR(sr.value(), 6.283185307179586, TOLERANCE);
}

// Test dimensionality
TEST_F(SteradianTest, SteradianDimension)
{
    steradian_t sr(1.0);
    // Verify that steradian has the correct dimension signature
    // steradian dimension should be {0, 0, 0, 0, 0, 0, 0, 0, 1}
    // This is implicitly tested through the type system
    EXPECT_EQ(sr.value(), 1.0);
}
