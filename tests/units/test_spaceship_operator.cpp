//
// Test the new <=> operators for units and temperatures

#include <gtest/gtest.h>

#include <pkr_units/units/base/length.h>
#include <pkr_units/units/base/temperature.h>
#include <pkr_units/units/temperature/celsius.h>
#include <pkr_units/units/temperature/fahrenheit.h>
#include <pkr_units/units/temperature/temperature_cast.h>

namespace test
{

using namespace ::testing;

class SpaceshipOperatorTest : public Test
{
};

// Test <=> operator for regular units with same dimensions
TEST_F(SpaceshipOperatorTest, RegularUnitsComparison)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{5.0};
    pkr::units::meter_t<double> m3{3.0};
    pkr::units::kilometer_t<double> km{0.005}; // 5 meters

    // Test equality
    EXPECT_EQ(m1 <=> m2, std::strong_ordering::equal);
    EXPECT_EQ(m1 <=> km, std::strong_ordering::equal);

    // Test less than
    EXPECT_EQ(m3 <=> m1, std::strong_ordering::less);
    EXPECT_EQ(m1 <=> m3, std::strong_ordering::greater);
}

// Test <=> operator for temperature units with affine transformations
TEST_F(SpaceshipOperatorTest, TemperatureUnitsComparison)
{
    pkr::units::kelvin_t<double> k1{273.15};   // 0°C
    pkr::units::celsius_t<double> c1{0.0};     // 0°C
    pkr::units::fahrenheit_t<double> f1{32.0}; // 0°C

    // All should be equal (representing same temperature)
    EXPECT_EQ(k1 <=> c1, std::strong_ordering::equal);
    EXPECT_EQ(c1 <=> f1, std::strong_ordering::equal);
    EXPECT_EQ(k1 <=> f1, std::strong_ordering::equal);

    // Test different temperatures
    pkr::units::celsius_t<double> c2{10.0}; // 10°C = 283.15K = 50°F
    pkr::units::kelvin_t<double> k2{283.15};
    pkr::units::fahrenheit_t<double> f2{50.0};

    EXPECT_EQ(c2 <=> k2, std::strong_ordering::equal);
    EXPECT_EQ(c2 <=> f2, std::strong_ordering::equal);

    // Test ordering
    pkr::units::celsius_t<double> c3{-10.0}; // colder than c1
    EXPECT_EQ(c3 <=> c1, std::strong_ordering::less);
    EXPECT_EQ(c1 <=> c3, std::strong_ordering::greater);
}

} // namespace test
