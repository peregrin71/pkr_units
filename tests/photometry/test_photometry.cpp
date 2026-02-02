#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace pkr::units;

class PhotometryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup code if needed
    }
};

// ============================================================================
// Luminous Flux (Lumen) Construction Tests
// ============================================================================

TEST_F(PhotometryTest, lumen_construction)
{
    lumen_t flux(1000.0);
    EXPECT_EQ(flux.value(), 1000.0);
}

TEST_F(PhotometryTest, lumen_dereference_operator)
{
    lumen_t flux(500.0);
    EXPECT_EQ(*flux, 500.0);
}

TEST_F(PhotometryTest, lumen_zero_value)
{
    lumen_t flux(0.0);
    EXPECT_EQ(flux.value(), 0.0);
}

TEST_F(PhotometryTest, lumen_typical_light_bulb)
{
    // 100W incandescent bulb ≈ 1700 lumens
    lumen_t bulb_flux(1700.0);
    EXPECT_EQ(bulb_flux.value(), 1700.0);
}

TEST_F(PhotometryTest, lumen_copy_constructor)
{
    lumen_t flux1(1500.0);
    lumen_t flux2 = flux1;
    EXPECT_EQ(flux2.value(), 1500.0);
}

TEST_F(PhotometryTest, lumen_move_constructor)
{
    lumen_t flux1(1500.0);
    lumen_t flux2 = std::move(flux1);
    EXPECT_EQ(flux2.value(), 1500.0);
}

// ============================================================================
// Luminous Flux Arithmetic Tests
// ============================================================================

TEST_F(PhotometryTest, lumen_addition)
{
    lumen_t flux1(500.0);
    lumen_t flux2(800.0);
    lumen_t result = flux1 + flux2;
    EXPECT_EQ(result.value(), 1300.0);
}

TEST_F(PhotometryTest, lumen_subtraction)
{
    lumen_t flux1(1500.0);
    lumen_t flux2(600.0);
    lumen_t result = flux1 - flux2;
    EXPECT_EQ(result.value(), 900.0);
}

TEST_F(PhotometryTest, lumen_multiplication_by_scalar)
{
    lumen_t flux(500.0);
    lumen_t result = flux * 2.0;
    EXPECT_EQ(result.value(), 1000.0);
}

TEST_F(PhotometryTest, lumen_division_by_scalar)
{
    lumen_t flux(1000.0);
    lumen_t result = flux / 2.0;
    EXPECT_EQ(result.value(), 500.0);
}

// ============================================================================
// Luminous Flux Comparison Tests
// ============================================================================

TEST_F(PhotometryTest, lumen_equality)
{
    lumen_t flux1(1000.0);
    lumen_t flux2(1000.0);
    EXPECT_EQ(flux1, flux2);
}

TEST_F(PhotometryTest, lumen_inequality)
{
    lumen_t flux1(1000.0);
    lumen_t flux2(800.0);
    EXPECT_NE(flux1, flux2);
}

TEST_F(PhotometryTest, lumen_less_than)
{
    lumen_t flux1(500.0);
    lumen_t flux2(1000.0);
    EXPECT_LT(flux1, flux2);
}

TEST_F(PhotometryTest, lumen_greater_than)
{
    lumen_t flux1(1500.0);
    lumen_t flux2(1000.0);
    EXPECT_GT(flux1, flux2);
}

// ============================================================================
// Illuminance (Lux) Construction Tests
// ============================================================================

TEST_F(PhotometryTest, lux_construction)
{
    lux_t illuminance(500.0);
    EXPECT_EQ(illuminance.value(), 500.0);
}

TEST_F(PhotometryTest, lux_dereference_operator)
{
    lux_t illuminance(400.0);
    EXPECT_EQ(*illuminance, 400.0);
}

TEST_F(PhotometryTest, lux_zero_value)
{
    lux_t illuminance(0.0);
    EXPECT_EQ(illuminance.value(), 0.0);
}

TEST_F(PhotometryTest, lux_office_lighting)
{
    // Office/classroom lighting: ~400 lux
    lux_t office_light(400.0);
    EXPECT_EQ(office_light.value(), 400.0);
}

TEST_F(PhotometryTest, lux_bright_sunlight)
{
    // Bright sunlight: ~100,000 lux
    lux_t sunlight(100000.0);
    EXPECT_EQ(sunlight.value(), 100000.0);
}

TEST_F(PhotometryTest, lux_full_moon_night)
{
    // Full moon clear night: ~0.25 lux
    lux_t moonlight(0.25);
    EXPECT_NEAR(moonlight.value(), 0.25, 0.001);
}

// ============================================================================
// Illuminance Arithmetic Tests
// ============================================================================

TEST_F(PhotometryTest, lux_addition)
{
    lux_t ill1(200.0);
    lux_t ill2(300.0);
    lux_t result = ill1 + ill2;
    EXPECT_EQ(result.value(), 500.0);
}

TEST_F(PhotometryTest, lux_subtraction)
{
    lux_t ill1(500.0);
    lux_t ill2(200.0);
    lux_t result = ill1 - ill2;
    EXPECT_EQ(result.value(), 300.0);
}

TEST_F(PhotometryTest, lux_multiplication_by_scalar)
{
    lux_t ill(200.0);
    lux_t result = ill * 2.5;
    EXPECT_EQ(result.value(), 500.0);
}

TEST_F(PhotometryTest, lux_division_by_scalar)
{
    lux_t ill(600.0);
    lux_t result = ill / 3.0;
    EXPECT_EQ(result.value(), 200.0);
}

// ============================================================================
// Illuminance Comparison Tests
// ============================================================================

TEST_F(PhotometryTest, lux_equality)
{
    lux_t ill1(500.0);
    lux_t ill2(500.0);
    EXPECT_EQ(ill1, ill2);
}

TEST_F(PhotometryTest, lux_less_than)
{
    lux_t ill1(300.0);
    lux_t ill2(500.0);
    EXPECT_LT(ill1, ill2);
}

TEST_F(PhotometryTest, lux_greater_than)
{
    lux_t ill1(800.0);
    lux_t ill2(500.0);
    EXPECT_GT(ill1, ill2);
}

// ============================================================================
// Type Safety Tests
// ============================================================================

TEST_F(PhotometryTest, lumen_distinct_from_watt)
{
    // Luminous flux [cd·sr] should be distinct from radiant flux [M·L²·T⁻³]
    static_assert(!std::is_same_v<lumen_t, watt_t>, "lumen_t and watt_t should be distinct types");
}

TEST_F(PhotometryTest, lux_distinct_from_watt_per_square_meter)
{
    // Illuminance [cd·sr·m⁻²] should be distinct from irradiance [M·L⁻²·T⁻³]
    static_assert(!std::is_same_v<lux_t, watt_per_square_meter_t>, "lux_t and watt_per_square_meter_t should be distinct types");
}

// ============================================================================
// Photometry Dimensional Relationships
// ============================================================================

TEST_F(PhotometryTest, candela_as_luminous_intensity)
{
    // Verify candela_t is available and distinct from lumen_t
    candela_t intensity(100.0);
    EXPECT_EQ(intensity.value(), 100.0);

    static_assert(!std::is_same_v<candela_t, lumen_t>, "candela_t and lumen_t should be distinct types");
}

TEST_F(PhotometryTest, steradian_in_photometry)
{
    // Verify steradian_t is available for photometric calculations
    steradian_t solid_angle(2.0);
    candela_t intensity(100.0);

    EXPECT_EQ(solid_angle.value(), 2.0);
    EXPECT_EQ(intensity.value(), 100.0);
}
