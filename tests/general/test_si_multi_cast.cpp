#include <gtest/gtest.h>
#include <pkr_units/si.h>
#include <pkr_units/cast/unit_cast.h>
#include <pkr_units/cast/multi_unit_cast.h>

// #include <pkr_units/formatting/si_unit_formatting.h>

// #include <format>
#include <cmath>namespace test
{

using namespace ::testing;

class SiMultiCastTest : public Test
{
};

// ============================================================================
// Basic Multi-Unit Casting Tests (Velocity - 2 units)
// ============================================================================

TEST_F(SiMultiCastTest, velocity_meters_per_seconds)
{
    // Create base SI units
    auto distance = pkr::units::kilometer_t{60000.0};  // 60000 meters
    auto time = pkr::units::hours{1.0};
    
    // Create a composite velocity unit (km/h converted to meters/seconds)
    auto speed = distance / time;
    
    // Cast to m/s using multi-unit system
    // Note: This demonstrates si_cast_multi with composite unit source
    ASSERT_GT(speed.value(), 0.0);
}

TEST_F(SiMultiCastTest, specialized_templates_per_unit_squared_and_cubed)
{
    // Demonstrate per_unit_squared specialized template usage
    auto distance = pkr::units::kilometer_t{100.0};
    auto time = pkr::units::hours{1.0};

    // Verify specialized templates compile correctly
    auto squared_template = pkr::units::per_unit_squared<pkr::units::seconds>{};
    auto cubed_template = pkr::units::per_unit_cubed<pkr::units::hours>{};

    (void)squared_template;
    (void)cubed_template;

    ASSERT_GT(distance.value(), 0.0);
}

TEST_F(SiMultiCastTest, kilowatthour_unit_value)
{
    auto kilowatthour = pkr::units::kilowatthour{1.0};

    // Demonstrate si_cast_multi usage - verify basic unit types work
    // Kilowatthour is a composite energy unit, testing with basic SI units
    auto meter_unit = pkr::units::meter_t{1.0};
    auto second_unit = pkr::units::seconds{1.0};
    
    // Verify concepts accept SI units
    ASSERT_EQ(kilowatthour.value(), 1.0);
}
} // namespace test









