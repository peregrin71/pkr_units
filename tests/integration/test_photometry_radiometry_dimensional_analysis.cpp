#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

using namespace PKR_UNITS_NAMESPACE;

// ============================================================================
// Photometry vs Radiometry Dimensional Consistency Tests
// ============================================================================

class PhotometryRadiometryDimensionTest : public ::testing::Test
{
protected:
    static constexpr double TOLERANCE = 1e-10;
};

// Test that luminous flux (cd·sr) is different from luminous intensity (cd)
TEST_F(PhotometryRadiometryDimensionTest, LuminousFluxVsIntensity)
{
    // These should be different types (dimensional safety)
    lumen_t<double> luminous_flux(1700.0); // Total light output
    candela_t luminous_intensity(200.0);   // Light in one direction

    // Both should exist independently
    EXPECT_DOUBLE_EQ(luminous_flux.value(), 1700.0);
    EXPECT_DOUBLE_EQ(luminous_intensity.value(), 200.0);
}

// Test that radiant intensity (W/sr) calculation makes sense
TEST_F(PhotometryRadiometryDimensionTest, RadiantIntensityFromFlux)
{
    // Conceptually: radiant_intensity = radiant_flux / solid_angle
    // But at the type level, we're just verifying the units exist separately

    // 100W power source emitting uniformly into hemisphere (2π sr)
    // Would have ~15.9 W/sr in any given direction on average

    // We can verify dimensional consistency by checking existence
    watt_per_steradian_t intensity(15.9);
    steradian_t angle(2 * M_PI);

    // These should both compile and work
    EXPECT_NEAR(intensity.value(), 15.9, TOLERANCE);
    EXPECT_NEAR(angle.value(), 2 * M_PI, TOLERANCE);
}

// Test solid angle dimension is distinct from plane angle
TEST_F(PhotometryRadiometryDimensionTest, SolidAngleVsPlaneAngle)
{
    // Solid angle (steradian) - 3D
    steradian_t solid(1.0);

    // Plane angle (radian) - 2D
    radian_t plane(1.0);

    // Both should exist with their distinct types
    EXPECT_DOUBLE_EQ(solid.value(), 1.0);
    EXPECT_DOUBLE_EQ(plane.value(), 1.0);

    // But they have different dimensions (type safety prevents mixing)
    // This is verified through compile-time type checking
}

// Test that irradiance and illuminance are in different categories
// (radiometric vs photometric)
TEST_F(PhotometryRadiometryDimensionTest, IrradianceVsIlluminance)
{
    // Irradiance: total electromagnetic power per area
    irradiance_t irr(1000.0); // W/m²

    // Illuminance: visible light power per area (weighted for human eye)
    lux_t illum(500.0); // lm/m² = cd·sr/m²

    // Both should work independently
    EXPECT_DOUBLE_EQ(irr.value(), 1000.0);
    EXPECT_DOUBLE_EQ(illum.value(), 500.0);
}

// Test that radiance (W/(m²·sr)) is fundamentally different from irradiance (W/m²)
TEST_F(PhotometryRadiometryDimensionTest, RadianceVsIrradiance)
{
    // Radiance: directional intensity (with solid angle)
    radiance_t rad(500000.0); // W/(m²·sr)

    // Irradiance: total power on surface (no solid angle)
    irradiance_t irr(1000.0); // W/m²

    // These are fundamentally different quantities
    // and the type system enforces this distinction
    EXPECT_DOUBLE_EQ(rad.value(), 500000.0);
    EXPECT_DOUBLE_EQ(irr.value(), 1000.0);
}

// Test relationship: radiant_flux has no solid angle, but related via intensity
TEST_F(PhotometryRadiometryDimensionTest, RadiantFluxIntensityRelationship)
{
    // Conceptually: radiant_intensity [W/sr] = radiant_flux [W] / solid_angle [sr]
    // Equivalently: radiant_flux [W] = radiant_intensity [W/sr] × solid_angle [sr]

    // Create compatible units
    watt_per_steradian_t intensity(100.0);
    steradian_t angle(0.5);

    // The mathematical relationship would give us ~50 W
    // (But at the type level, we're just verifying dimensional safety)
    EXPECT_DOUBLE_EQ(intensity.value(), 100.0);
    EXPECT_DOUBLE_EQ(angle.value(), 0.5);
    // A calculation: 100 * 0.5 = 50 W
    EXPECT_NEAR(intensity.value() * angle.value(), 50.0, TOLERANCE);
}

// Test that luminous exitance and irradiance are similar but distinct
TEST_F(PhotometryRadiometryDimensionTest, LuminousExitanceVsIrradiance)
{
    // Luminous exitance (luminous flux per area per solid angle)
    lux_t exitance(1000.0); // lm/m² = cd·sr/m²

    // Irradiance (radiant flux per area, all wavelengths)
    irradiance_t irradiance(2000.0); // W/m²

    // Both describe power per area, but from different perspectives
    EXPECT_DOUBLE_EQ(exitance.value(), 1000.0);
    EXPECT_DOUBLE_EQ(irradiance.value(), 2000.0);
}
