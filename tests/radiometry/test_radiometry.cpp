#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace pkr::units;

class RadiometryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup code if needed
    }
};

// ============================================================================
// Radiant Intensity (W/sr) Construction Tests
// ============================================================================

TEST_F(RadiometryTest, watt_per_steradian_construction)
{
    watt_per_steradian_t intensity(100.0);
    EXPECT_EQ(intensity.value(), 100.0);
}

TEST_F(RadiometryTest, watt_per_steradian_dereference_operator)
{
    watt_per_steradian_t intensity(50.0);
    EXPECT_EQ(*intensity, 50.0);
}

TEST_F(RadiometryTest, watt_per_steradian_zero_value)
{
    watt_per_steradian_t intensity(0.0);
    EXPECT_EQ(intensity.value(), 0.0);
}

TEST_F(RadiometryTest, watt_per_steradian_copy_constructor)
{
    watt_per_steradian_t int1(75.0);
    watt_per_steradian_t int2 = int1;
    EXPECT_EQ(int2.value(), 75.0);
}

// ============================================================================
// Radiant Intensity Arithmetic Tests
// ============================================================================

TEST_F(RadiometryTest, watt_per_steradian_addition)
{
    watt_per_steradian_t int1(50.0);
    watt_per_steradian_t int2(75.0);
    watt_per_steradian_t result = int1 + int2;
    EXPECT_EQ(result.value(), 125.0);
}

TEST_F(RadiometryTest, watt_per_steradian_subtraction)
{
    watt_per_steradian_t int1(100.0);
    watt_per_steradian_t int2(40.0);
    watt_per_steradian_t result = int1 - int2;
    EXPECT_EQ(result.value(), 60.0);
}

TEST_F(RadiometryTest, watt_per_steradian_multiplication_by_scalar)
{
    watt_per_steradian_t intensity(50.0);
    watt_per_steradian_t result = intensity * 2.0;
    EXPECT_EQ(result.value(), 100.0);
}

// ============================================================================
// Radiant Intensity Comparison Tests
// ============================================================================

TEST_F(RadiometryTest, watt_per_steradian_equality)
{
    watt_per_steradian_t int1(100.0);
    watt_per_steradian_t int2(100.0);
    EXPECT_EQ(int1, int2);
}

TEST_F(RadiometryTest, watt_per_steradian_less_than)
{
    watt_per_steradian_t int1(50.0);
    watt_per_steradian_t int2(100.0);
    EXPECT_LT(int1, int2);
}

// ============================================================================
// Radiant Flux (Watts) Construction Tests
// ============================================================================

TEST_F(RadiometryTest, watt_construction)
{
    watt_t flux(1000.0);
    EXPECT_EQ(flux.value(), 1000.0);
}

TEST_F(RadiometryTest, watt_dereference_operator)
{
    watt_t flux(500.0);
    EXPECT_EQ(*flux, 500.0);
}

TEST_F(RadiometryTest, watt_zero_value)
{
    watt_t flux(0.0);
    EXPECT_EQ(flux.value(), 0.0);
}

TEST_F(RadiometryTest, watt_solar_constant)
{
    // Solar constant at Earth's orbit: ~1361 W/m²
    // For a 1 m² area
    watt_t solar_power(1361.0);
    EXPECT_EQ(solar_power.value(), 1361.0);
}

TEST_F(RadiometryTest, watt_human_thermal_radiation)
{
    // Human body radiates approximately 100W
    watt_t body_radiation(100.0);
    EXPECT_EQ(body_radiation.value(), 100.0);
}

TEST_F(RadiometryTest, watt_copy_constructor)
{
    watt_t flux1(750.0);
    watt_t flux2 = flux1;
    EXPECT_EQ(flux2.value(), 750.0);
}

// ============================================================================
// Radiant Flux Arithmetic Tests
// ============================================================================

TEST_F(RadiometryTest, watt_addition)
{
    watt_t flux1(400.0);
    watt_t flux2(600.0);
    watt_t result = flux1 + flux2;
    EXPECT_EQ(result.value(), 1000.0);
}

TEST_F(RadiometryTest, watt_subtraction)
{
    watt_t flux1(1200.0);
    watt_t flux2(500.0);
    watt_t result = flux1 - flux2;
    EXPECT_EQ(result.value(), 700.0);
}

TEST_F(RadiometryTest, watt_multiplication_by_scalar)
{
    watt_t flux(250.0);
    watt_t result = flux * 4.0;
    EXPECT_EQ(result.value(), 1000.0);
}

TEST_F(RadiometryTest, watt_division_by_scalar)
{
    watt_t flux(1000.0);
    watt_t result = flux / 5.0;
    EXPECT_EQ(result.value(), 200.0);
}

// ============================================================================
// Radiant Flux Comparison Tests
// ============================================================================

TEST_F(RadiometryTest, watt_equality)
{
    watt_t flux1(500.0);
    watt_t flux2(500.0);
    EXPECT_EQ(flux1, flux2);
}

TEST_F(RadiometryTest, watt_inequality)
{
    watt_t flux1(500.0);
    watt_t flux2(600.0);
    EXPECT_NE(flux1, flux2);
}

TEST_F(RadiometryTest, watt_greater_than)
{
    watt_t flux1(700.0);
    watt_t flux2(500.0);
    EXPECT_GT(flux1, flux2);
}

// ============================================================================
// Radiance (W/(m²·sr)) Construction Tests
// ============================================================================

TEST_F(RadiometryTest, radiance_construction)
{
    radiance_t radiance(500.0);
    EXPECT_EQ(radiance.value(), 500.0);
}

TEST_F(RadiometryTest, radiance_dereference_operator)
{
    radiance_t radiance(350.0);
    EXPECT_EQ(*radiance, 350.0);
}

TEST_F(RadiometryTest, radiance_zero_value)
{
    radiance_t radiance(0.0);
    EXPECT_EQ(radiance.value(), 0.0);
}

TEST_F(RadiometryTest, radiance_blackbody_typical)
{
    // Tungsten filament at 2000K: ~1 MW/(m²·sr) = 1e6 W/(m²·sr)
    radiance_t tungsten(1e6);
    EXPECT_EQ(tungsten.value(), 1e6);
}

TEST_F(RadiometryTest, radiance_copy_constructor)
{
    radiance_t rad1(600.0);
    radiance_t rad2 = rad1;
    EXPECT_EQ(rad2.value(), 600.0);
}

// ============================================================================
// Radiance Arithmetic Tests
// ============================================================================

TEST_F(RadiometryTest, radiance_addition)
{
    radiance_t rad1(300.0);
    radiance_t rad2(400.0);
    radiance_t result = rad1 + rad2;
    EXPECT_EQ(result.value(), 700.0);
}

TEST_F(RadiometryTest, radiance_subtraction)
{
    radiance_t rad1(800.0);
    radiance_t rad2(300.0);
    radiance_t result = rad1 - rad2;
    EXPECT_EQ(result.value(), 500.0);
}

TEST_F(RadiometryTest, radiance_multiplication_by_scalar)
{
    radiance_t rad(250.0);
    radiance_t result = rad * 2.0;
    EXPECT_EQ(result.value(), 500.0);
}

// ============================================================================
// Radiance Comparison Tests
// ============================================================================

TEST_F(RadiometryTest, radiance_equality)
{
    radiance_t rad1(500.0);
    radiance_t rad2(500.0);
    EXPECT_EQ(rad1, rad2);
}

TEST_F(RadiometryTest, radiance_less_than)
{
    radiance_t rad1(300.0);
    radiance_t rad2(600.0);
    EXPECT_LT(rad1, rad2);
}

// ============================================================================
// Irradiance (W/m²) Construction Tests
// ============================================================================

TEST_F(RadiometryTest, irradiance_construction)
{
    irradiance_t irradiance(500.0);
    EXPECT_EQ(irradiance.value(), 500.0);
}

TEST_F(RadiometryTest, irradiance_dereference_operator)
{
    irradiance_t irradiance(350.0);
    EXPECT_EQ(*irradiance, 350.0);
}

TEST_F(RadiometryTest, irradiance_zero_value)
{
    irradiance_t irradiance(0.0);
    EXPECT_EQ(irradiance.value(), 0.0);
}

TEST_F(RadiometryTest, irradiance_solar_constant)
{
    // Solar constant at Earth orbit: ~1361 W/m²
    irradiance_t solar(1361.0);
    EXPECT_NEAR(solar.value(), 1361.0, 0.1);
}

TEST_F(RadiometryTest, irradiance_bright_sunlight)
{
    // Bright sunlight at sea level: ~1000 W/m²
    irradiance_t sunlight(1000.0);
    EXPECT_EQ(sunlight.value(), 1000.0);
}

TEST_F(RadiometryTest, irradiance_cloudy_day)
{
    // Cloudy day: ~100 W/m²
    irradiance_t clouds(100.0);
    EXPECT_EQ(clouds.value(), 100.0);
}

TEST_F(RadiometryTest, irradiance_copy_constructor)
{
    irradiance_t irr1(450.0);
    irradiance_t irr2 = irr1;
    EXPECT_EQ(irr2.value(), 450.0);
}

// ============================================================================
// Irradiance Arithmetic Tests
// ============================================================================

TEST_F(RadiometryTest, irradiance_addition)
{
    irradiance_t irr1(200.0);
    irradiance_t irr2(300.0);
    irradiance_t result = irr1 + irr2;
    EXPECT_EQ(result.value(), 500.0);
}

TEST_F(RadiometryTest, irradiance_subtraction)
{
    irradiance_t irr1(600.0);
    irradiance_t irr2(200.0);
    irradiance_t result = irr1 - irr2;
    EXPECT_EQ(result.value(), 400.0);
}

TEST_F(RadiometryTest, irradiance_multiplication_by_scalar)
{
    irradiance_t irr(200.0);
    irradiance_t result = irr * 2.5;
    EXPECT_EQ(result.value(), 500.0);
}

// ============================================================================
// Irradiance Comparison Tests
// ============================================================================

TEST_F(RadiometryTest, irradiance_equality)
{
    irradiance_t irr1(500.0);
    irradiance_t irr2(500.0);
    EXPECT_EQ(irr1, irr2);
}

TEST_F(RadiometryTest, irradiance_greater_than)
{
    irradiance_t irr1(800.0);
    irradiance_t irr2(500.0);
    EXPECT_GT(irr1, irr2);
}

// ============================================================================
// Type Safety Tests
// ============================================================================

TEST_F(RadiometryTest, radiant_flux_distinct_from_luminous_flux)
{
    // Radiant flux [M·L²·T⁻³] should be distinct from luminous flux [cd·sr]
    static_assert(!std::is_same_v<watt_t, lumen_t>, 
                  "watt_t and lumen_t should be distinct types");
}

TEST_F(RadiometryTest, radiant_intensity_distinct_from_candela)
{
    // Radiant intensity [M·L²·T⁻³·sr⁻¹] should be distinct from candela [cd]
    static_assert(!std::is_same_v<watt_per_steradian_t, candela_t>, 
                  "watt_per_steradian_t and candela_t should be distinct types");
}

TEST_F(RadiometryTest, radiance_distinct_from_luminance)
{
    // While there's no luminance type in this library, radiance should be 
    // distinct from photometric quantities
    static_assert(!std::is_same_v<radiance_t, lux_t>, 
                  "radiance_t and lux_t should be distinct types");
}

TEST_F(RadiometryTest, irradiance_distinct_from_illuminance)
{
    // Irradiance [M·L⁻²·T⁻³] should be distinct from illuminance [cd·sr·m⁻²]
    static_assert(!std::is_same_v<irradiance_t, lux_t>, 
                  "irradiance_t and lux_t should be distinct types");
}

// ============================================================================
// Radiometry Dimensional Relationships
// ============================================================================

TEST_F(RadiometryTest, steradian_in_radiometry)
{
    // Verify steradian_t is available for radiometric calculations
    steradian_t solid_angle(1.5);
    watt_per_steradian_t intensity(100.0);
    
    EXPECT_EQ(solid_angle.value(), 1.5);
    EXPECT_EQ(intensity.value(), 100.0);
}

TEST_F(RadiometryTest, radiometric_quantities_consistency)
{
    // Verify all radiometric types are available and constructible
    watt_t flux(1000.0);
    watt_per_steradian_t intensity(100.0);
    radiance_t radiance(50.0);
    irradiance_t irradiance(500.0);
    
    EXPECT_GT(flux.value(), 0.0);
    EXPECT_GT(intensity.value(), 0.0);
    EXPECT_GT(radiance.value(), 0.0);
    EXPECT_GT(irradiance.value(), 0.0);
}
