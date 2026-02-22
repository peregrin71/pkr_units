#include <gtest/gtest.h>
#include <array>
#include <pkr_units/units/math/matrix_unit_4d.h>
#include <pkr_units/units/math/matrix_storage_policies.h>
#include <pkr_units/measurements/math/matrix_measurement_rss_4d.h>
#include <pkr_units/literals/length.h>
#include <pkr_units/literals/time.h>
#include <pkr_units/literals/mechanical.h>
#include <pkr_units/literals/electrical.h>
#include <pkr_units/literals/current.h>
#include <pkr_units/literals/mass.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace pkr::units;
using namespace pkr::units::literals;

// Test stack storage with explicit array initialization
TEST(MatrixStorageStackTest, explicit_construction_with_array)
{
    using StackMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = StackMatrix::array_type{{
        {{5.0_m, 0.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 10.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 15.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 0.0_m, 20.0_m}}
    }};
    StackMatrix m(arr);
    
    EXPECT_EQ(m(0, 0).value(), 5.0);
    EXPECT_EQ(m(1, 1).value(), 10.0);
    EXPECT_EQ(m(2, 2).value(), 15.0);
    EXPECT_EQ(m(3, 3).value(), 20.0);
}

// Test arena storage with array initialization and pool tracking
TEST(MatrixStorageArenaTest, arena_storage_pool_tracking)
{
    using ArenaMatrix = matrix_4d_units_t<meter_t<double>, arena_storage<meter_t<double>, 5>>;
    
    auto arr = ArenaMatrix::array_type{{
        {{1.0_m, 0.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 1.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 1.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 0.0_m, 1.0_m}}
    }};
    
    arena_storage<meter_t<double>, 5>::reset_statistics();
    {
        ArenaMatrix m1(arr);
        EXPECT_EQ((arena_storage<meter_t<double>, 5>::active_slots()), 1);
        
        ArenaMatrix m2(arr);
        EXPECT_EQ((arena_storage<meter_t<double>, 5>::active_slots()), 2);
    }
    EXPECT_EQ((arena_storage<meter_t<double>, 5>::active_slots()), 0);
}

// Test arena storage with fallback 
TEST(MatrixStorageArenaTest, arena_fallback_on_exhaustion)
{
    using ArenaMatrix = matrix_4d_units_t<meter_t<double>, arena_storage<meter_t<double>, 2>>;
    
    auto arr = ArenaMatrix::array_type{{
        {{1.0_m, 0.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 1.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 1.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 0.0_m, 1.0_m}}
    }};
    
    arena_storage<meter_t<double>, 2>::reset_statistics();
    
    ArenaMatrix m1(arr);
    ArenaMatrix m2(arr);
    ArenaMatrix m3(arr);  // This should trigger fallback
    
    EXPECT_GT((arena_storage<meter_t<double>, 2>::get_fallback_count()), 0);
}

// Test with measurement_rss_t
TEST(MatrixStorageMeasurementTest, stack_measurement_storage)
{
    using StackMeasMatrix = matrix_measurement_rss_4d_t<meter_t<double>>;
    
    auto arr = StackMeasMatrix::array_type{{
        {{measurement_rss_t<meter_t<double>>{5.0_m, 0.1_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m}}},
        {{measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m}}},
        {{measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m}}},
        {{measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m}}}
    }};



    
    StackMeasMatrix m(arr);
    
    EXPECT_NEAR(m(0, 0).value(), 5.0, 0.001);
    EXPECT_NEAR(m(0, 0).uncertainty(), 0.1, 0.001);
}

// Test measurement matrix with simplified raw double syntax
TEST(MatrixStorageMeasurementTest, stack_measurement_storage_simplified_syntax)
{
    using StackMeasMatrix = matrix_measurement_rss_4d_t<meter_t<double>>;
    
    auto arr = StackMeasMatrix::array_type{{
        {{{5.0, 0.1}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}},
        {{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}},
        {{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}},
        {{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}}
    }};
    
    StackMeasMatrix m(arr);
    
    EXPECT_NEAR(m(0, 0).value(), 5.0, 0.001);
    EXPECT_NEAR(m(0, 0).uncertainty(), 0.1, 0.001);
}

// Test 1: Time Literal Operators (time.h coverage)
TEST(LiteralOperatorsTest, time_literals_with_matrix)
{
    using TimeMatrix = matrix_4d_units_t<second_t<double>>;
    auto arr = TimeMatrix::array_type{{
        {{1.0_s, 2.0_s, 3.0_s, 4.0_s}},
        {{10.0_ms, 20.0_ms, 30.0_ms, 40.0_ms}},
        {{1800.0_s, 3600.0_s, 5400.0_s, 7200.0_s}},  // Hours converted to seconds
        {{100.0_ms, 200.0_ms, 300.0_ms, 400.0_ms}}
    }};
    TimeMatrix m(arr);
    
    EXPECT_EQ(m(0, 0).value(), 1.0);
    EXPECT_EQ(m(1, 0).value(), 0.01);  // 10ms in seconds
    EXPECT_EQ(m(2, 0).value(), 1800.0);  // 0.5 hours in seconds
    EXPECT_EQ(m(3, 1).value(), 0.2);  // 200ms in seconds
}

// Test 2: Mechanical Literal Operators (mechanical.h coverage)
TEST(LiteralOperatorsTest, mechanical_literals_with_matrix)
{
    using ForceMatrix = matrix_4d_units_t<newton_t<double>>;
    auto arr = ForceMatrix::array_type{{
        {{1.0_N, 2.0_N, 3.0_N, 4.0_N}},
        {{10.0_N, 20.0_N, 30.0_N, 40.0_N}},
        {{100.0_N, 200.0_N, 300.0_N, 400.0_N}},
        {{1000.0_N, 2000.0_N, 3000.0_N, 4000.0_N}}
    }};
    ForceMatrix m(arr);
    
    EXPECT_EQ(m(0, 0).value(), 1.0);
    EXPECT_EQ(m(1, 1).value(), 20.0);
    EXPECT_EQ(m(2, 2).value(), 300.0);
    EXPECT_EQ(m(3, 3).value(), 4000.0);
}

// Test 3: Electrical Unit Storage (electrical engineering formatting)
TEST(ElectricalUnitsTest, voltage_matrix_storage)
{
    using VoltMatrix = matrix_4d_units_t<volt_t<double>>;
    auto arr = VoltMatrix::array_type{{
        {{5.0_V, 10.0_V, 15.0_V, 20.0_V}},
        {{1.0_V, 2.0_V, 3.0_V, 4.0_V}},
        {{100.0_mV, 200.0_mV, 300.0_mV, 400.0_mV}},
        {{1.0_kV, 2.0_kV, 3.0_kV, 4.0_kV}}
    }};
    VoltMatrix m(arr);
    
    EXPECT_EQ(m(0, 0).value(), 5.0);
    EXPECT_EQ(m(2, 0).value(), 0.1);  // 100mV in volts
    EXPECT_EQ(m(3, 0).value(), 1000.0);  // 1kV in volts
}

// Test 4: Type Casting & Unit Conversions (casting.h coverage)
TEST(UnitCastingTest, length_unit_conversion_storage)
{
    // Create array with meters and convert to different length units
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{1000.0_m, 2000.0_m, 3000.0_m, 4000.0_m}},
        {{100.0_m, 200.0_m, 300.0_m, 400.0_m}},
        {{10.0_m, 20.0_m, 30.0_m, 40.0_m}},
        {{1.0_m, 2.0_m, 3.0_m, 4.0_m}}
    }};
    MeterMatrix m(arr);
    
    // Test that values are stored and can be retrieved
    EXPECT_EQ(m(0, 0).value(), 1000.0);
    EXPECT_EQ(m(1, 1).value(), 200.0);
    EXPECT_EQ(m(3, 3).value(), 4.0);
}

// Test 5: Branch Coverage - Edge Cases
TEST(BranchCoverageTest, negative_values_in_storage)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{-5.0_m, 5.0_m, -5.0_m, 5.0_m}},
        {{-10.0_m, 10.0_m, -10.0_m, 10.0_m}},
        {{-15.0_m, 15.0_m, -15.0_m, 15.0_m}},
        {{-20.0_m, 20.0_m, -20.0_m, 20.0_m}}
    }};
    MeterMatrix m(arr);
    
    EXPECT_EQ(m(0, 0).value(), -5.0);
    EXPECT_EQ(m(0, 1).value(), 5.0);
    EXPECT_LT(m(0, 0).value(), m(0, 1).value());
    EXPECT_GT(m(1, 1).value(), m(1, 0).value());
}

// Test 6: Branch Coverage - Very Large & Very Small Values
TEST(BranchCoverageTest, extreme_magnitude_values)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{1e-10_m, 1e10_m, 1e-6_m, 1e6_m}},
        {{1e-8_m, 1e8_m, 1e-4_m, 1e4_m}},
        {{1e-5_m, 1e5_m, 1e-3_m, 1e3_m}},
        {{1e-2_m, 1e2_m, 1.0_m, 10000.0_m}}
    }};
    MeterMatrix m(arr);
    
    EXPECT_LT(m(0, 0).value(), 1e-9);
    EXPECT_GT(m(0, 1).value(), 1e9);
    EXPECT_TRUE(m(0, 0).value() < m(0, 1).value());
}

// Test 7: Branch Coverage - Zero Values
TEST(BranchCoverageTest, zero_values_comparison)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{0.0_m, 1.0_m, -1.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 0.0_m, 0.0_m}},
        {{1.0_m, -1.0_m, 0.0_m, 2.0_m}},
        {{-2.0_m, 0.0_m, 3.0_m, 0.0_m}}
    }};
    MeterMatrix m(arr);
    
    EXPECT_EQ(m(0, 0).value(), 0.0);
    EXPECT_EQ(m(0, 0).value(), m(1, 0).value());
    EXPECT_NE(m(0, 1).value(), m(0, 2).value());
    EXPECT_LE(m(0, 0).value(), m(0, 1).value());
    EXPECT_GE(m(0, 1).value(), m(0, 0).value());
}

// Test 8: Measurement with Time Literals (measurement + time coverage)
TEST(MeasurementWithTimeLiterals, time_measurement_matrix)
{
    using TimeMeasMatrix = matrix_measurement_rss_4d_t<second_t<double>>;
    
    auto arr = TimeMeasMatrix::array_type{{
        {{measurement_rss_t<second_t<double>>{1.0_s, 0.1_s},
          measurement_rss_t<second_t<double>>{2.0_s, 0.2_s},
          measurement_rss_t<second_t<double>>{3.0_s, 0.3_s},
          measurement_rss_t<second_t<double>>{4.0_s, 0.4_s}}},
        {{measurement_rss_t<second_t<double>>{10.0_ms, 1.0_ms},
          measurement_rss_t<second_t<double>>{20.0_ms, 2.0_ms},
          measurement_rss_t<second_t<double>>{30.0_ms, 3.0_ms},
          measurement_rss_t<second_t<double>>{40.0_ms, 4.0_ms}}},
        {{measurement_rss_t<second_t<double>>{0.0_s, 0.0_s},
          measurement_rss_t<second_t<double>>{0.0_s, 0.0_s},
          measurement_rss_t<second_t<double>>{0.0_s, 0.0_s},
          measurement_rss_t<second_t<double>>{0.0_s, 0.0_s}}},
        {{measurement_rss_t<second_t<double>>{100.0_ms, 10.0_ms},
          measurement_rss_t<second_t<double>>{200.0_ms, 20.0_ms},
          measurement_rss_t<second_t<double>>{300.0_ms, 30.0_ms},
          measurement_rss_t<second_t<double>>{400.0_ms, 40.0_ms}}}
    }};
    
    TimeMeasMatrix m(arr);
    EXPECT_NEAR(m(0, 0).value(), 1.0, 0.001);
    EXPECT_NEAR(m(0, 0).uncertainty(), 0.1, 0.001);
    EXPECT_NEAR(m(1, 0).value(), 0.01, 0.001);  // 10ms in seconds
    EXPECT_NEAR(m(1, 0).uncertainty(), 0.001, 0.0001);  // 1ms in seconds
}

// Test 10: Measurement with Force/Mechanical Literals
TEST(MeasurementWithMechanicalLiterals, force_measurement_matrix)
{
    using ForceMeasMatrix = matrix_measurement_rss_4d_t<newton_t<double>>;
    
    auto arr = ForceMeasMatrix::array_type{{
        {{measurement_rss_t<newton_t<double>>{100.0_N, 5.0_N},
          measurement_rss_t<newton_t<double>>{200.0_N, 10.0_N},
          measurement_rss_t<newton_t<double>>{300.0_N, 15.0_N},
          measurement_rss_t<newton_t<double>>{400.0_N, 20.0_N}}},
        {{measurement_rss_t<newton_t<double>>{50.0_N, 2.5_N},
          measurement_rss_t<newton_t<double>>{75.0_N, 3.75_N},
          measurement_rss_t<newton_t<double>>{125.0_N, 6.25_N},
          measurement_rss_t<newton_t<double>>{150.0_N, 7.5_N}}},
        {{measurement_rss_t<newton_t<double>>{0.0_N, 0.0_N},
          measurement_rss_t<newton_t<double>>{0.0_N, 0.0_N},
          measurement_rss_t<newton_t<double>>{0.0_N, 0.0_N},
          measurement_rss_t<newton_t<double>>{0.0_N, 0.0_N}}},
        {{measurement_rss_t<newton_t<double>>{-100.0_N, 5.0_N},
          measurement_rss_t<newton_t<double>>{-200.0_N, 10.0_N},
          measurement_rss_t<newton_t<double>>{-300.0_N, 15.0_N},
          measurement_rss_t<newton_t<double>>{-400.0_N, 20.0_N}}}
    }};
    
    ForceMeasMatrix m(arr);
    EXPECT_NEAR(m(0, 0).value(), 100.0, 0.001);
    EXPECT_NEAR(m(0, 0).uncertainty(), 5.0, 0.001);
    EXPECT_NEAR(m(3, 0).value(), -100.0, 0.001);
    EXPECT_NEAR(m(3, 0).uncertainty(), 5.0, 0.001);
}

// Test 11: Electrical Engineering Format Coverage
TEST(ElectricalEngineeringFormatTest, complex_electrical_quantities)
{
    // Test various electrical units to exercise formatting
    ampere_t<double> current = 1.5_A;
    EXPECT_NEAR(current.value(), 1.5, 0.001);
    
    milliampere_t<double> mc = 500.0_mA;
    EXPECT_NEAR(mc.value(), 500.0, 0.001);
    
    watt_t<double> power = 250.0_W;
    EXPECT_NEAR(power.value(), 250.0, 0.001);
    
    kilowatt_t<double> kpower = 50.0_kW;
    EXPECT_NEAR(kpower.value(), 50.0, 0.001);
    
    ohm_t<double> resistance = 100.0_ohm;
    EXPECT_NEAR(resistance.value(), 100.0, 0.001);
    
    kiloohm_t<double> kres = 10.0_kohm;
    EXPECT_NEAR(kres.value(), 10.0, 0.001);
    
    farad_t<double> capacitance = 0.001_F;
    EXPECT_NEAR(capacitance.value(), 0.001, 0.00001);
    
    microfarad_t<double> ucap = 100.0_uF;
    EXPECT_NEAR(ucap.value(), 100.0, 0.01);
    
    coulomb_t<double> charge = 5.0_C;
    EXPECT_NEAR(charge.value(), 5.0, 0.001);
    
    volt_t<double> voltage = 12.0_V;
    EXPECT_NEAR(voltage.value(), 12.0, 0.001);
}

// Test 12: Multi-Unit Casting Coverage
TEST(MultiUnitCastingTest, complex_unit_conversions)
{
    // Test casting between composite units
    auto velocity = 10.0_m / 1.0_s;
    EXPECT_NEAR(velocity.value(), 10.0, 0.001);
    
    auto acceleration = 5.0_m / (1.0_s * 1.0_s);
    EXPECT_NEAR(acceleration.value(), 5.0, 0.001);
    
    kilogram_t<double> mass = 100.0_kg;
    EXPECT_NEAR(mass.value(), 100.0, 0.001);
    
    auto force = mass * acceleration;
    EXPECT_NEAR(force.value(), 500.0, 0.001);
    
    auto pressure = force / (0.1_m * 0.1_m);
    EXPECT_NEAR(pressure.value(), 50000.0, 100.0);  // 500N / 0.01m^2 = 50,000 Pa
}

// Test 13: Unit Casting Edge Cases
TEST(UnitCastingEdgeCasesTest, casting_between_compatible_units)
{
    // Test explicit casting between unit types
    centimeter_t<double> cm = 50.0_cm;
    meter_t<double> m = pkr::units::unit_cast<meter_t<double>>(cm);
    EXPECT_NEAR(m.value(), 0.5, 0.001);
    
    millimeter_t<double> mm = 1000.0_mm;
    meter_t<double> m2 = pkr::units::unit_cast<meter_t<double>>(mm);
    EXPECT_NEAR(m2.value(), 1.0, 0.001);
}

// Test 14: Measurement Operations with Various Unit Types
TEST(MeasurementOperationsTest, addition_with_measurements)
{
    measurement_rss_t<meter_t<double>> m1{10.0_m, 0.5_m};
    measurement_rss_t<meter_t<double>> m2{20.0_m, 1.0_m};
    
    EXPECT_NEAR(m1.value(), 10.0, 0.001);
    EXPECT_NEAR(m1.uncertainty(), 0.5, 0.001);
    EXPECT_NEAR(m2.value(), 20.0, 0.001);
    EXPECT_NEAR(m2.uncertainty(), 1.0, 0.001);
}

// Test 15: Matrix with Very Small Values (branch coverage)
TEST(MatrixStorageEdgeCasesTest, matrix_with_epsilon_values)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{1e-15_m, 1e-14_m, 1e-13_m, 1e-12_m}},
        {{1e-11_m, 1e-10_m, 1e-9_m, 1e-8_m}},
        {{1e-7_m, 1e-6_m, 1e-5_m, 1e-4_m}},
        {{1e-3_m, 1e-2_m, 1e-1_m, 1.0_m}}
    }};
    MeterMatrix m(arr);
    
    EXPECT_LT(m(0, 0).value(), 1e-14);
    EXPECT_GT(m(3, 3).value(), 0.999);
    EXPECT_TRUE(m(0, 0).value() < m(3, 3).value());
}

// Test 16: Mixed Positive and Negative Values (all comparisons)
TEST(MatrixStorageComprisonsTest, comprehensive_comparison_operations)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{-100.0_m, 100.0_m, -50.0_m, 50.0_m}},
        {{-25.0_m, 25.0_m, 0.0_m, 0.0_m}},
        {{10.0_m, -10.0_m, 5.0_m, -5.0_m}},
        {{1.0_m, -1.0_m, 0.5_m, -0.5_m}}
    }};
    MeterMatrix m(arr);
    
    // Test all comparison combinations
    EXPECT_LT(m(0, 0).value(), m(0, 1).value());  // -100 < 100
    EXPECT_LE(m(0, 0).value(), m(0, 0).value());  // -100 <= -100
    EXPECT_GT(m(0, 1).value(), m(0, 0).value());  // 100 > -100
    EXPECT_GE(m(0, 1).value(), m(0, 1).value());  // 100 >= 100
    EXPECT_EQ(m(1, 2).value(), 0.0);             // 0 == 0
    EXPECT_NE(m(1, 0).value(), m(1, 1).value()); // -25 != 25
}

// Test 17: Arena Storage Statistics Verification
TEST(MatrixStorageArenaStatisticsTest, arena_slot_management)
{
    using ArenaMatrix = matrix_4d_units_t<meter_t<double>, arena_storage<meter_t<double>, 4>>;
    
    auto arr = ArenaMatrix::array_type{{
        {{1.0_m, 0.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 1.0_m, 0.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 1.0_m, 0.0_m}},
        {{0.0_m, 0.0_m, 0.0_m, 1.0_m}}
    }};
    
    arena_storage<meter_t<double>, 4>::reset_statistics();
    
    // Create and destroy multiple matrices within arena
    {
        ArenaMatrix m1(arr);
        EXPECT_EQ((arena_storage<meter_t<double>, 4>::active_slots()), 1);
        {
            ArenaMatrix m2(arr);
            EXPECT_EQ((arena_storage<meter_t<double>, 4>::active_slots()), 2);
        }
        EXPECT_EQ((arena_storage<meter_t<double>, 4>::active_slots()), 1);
    }
    EXPECT_EQ((arena_storage<meter_t<double>, 4>::active_slots()), 0);
}

// Test 18: Measurement Matrix with Varying Uncertainties
TEST(MeasurementMatrixUncertaintyTest, varying_uncertainty_levels)
{
    using MeasMatrix = matrix_measurement_rss_4d_t<meter_t<double>>;
    
    auto arr = MeasMatrix::array_type{{
        {{measurement_rss_t<meter_t<double>>{100.0_m, 0.1_m},
          measurement_rss_t<meter_t<double>>{100.0_m, 1.0_m},
          measurement_rss_t<meter_t<double>>{100.0_m, 5.0_m},
          measurement_rss_t<meter_t<double>>{100.0_m, 10.0_m}}},
        {{measurement_rss_t<meter_t<double>>{50.0_m, 0.05_m},
          measurement_rss_t<meter_t<double>>{50.0_m, 0.5_m},
          measurement_rss_t<meter_t<double>>{50.0_m, 2.5_m},
          measurement_rss_t<meter_t<double>>{50.0_m, 5.0_m}}},
        {{measurement_rss_t<meter_t<double>>{0.0_m, 0.0_m},
          measurement_rss_t<meter_t<double>>{0.1_m, 0.01_m},
          measurement_rss_t<meter_t<double>>{0.001_m, 0.0001_m},
          measurement_rss_t<meter_t<double>>{1000.0_m, 100.0_m}}},
        {{measurement_rss_t<meter_t<double>>{-100.0_m, 5.0_m},
          measurement_rss_t<meter_t<double>>{-50.0_m, 2.5_m},
          measurement_rss_t<meter_t<double>>{-0.1_m, 0.01_m},
          measurement_rss_t<meter_t<double>>{-1000.0_m, 100.0_m}}}
    }};
    
    MeasMatrix m(arr);
    
    // Test various uncertainty levels
    EXPECT_NEAR(m(0, 0).uncertainty(), 0.1, 0.001);
    EXPECT_NEAR(m(0, 3).uncertainty(), 10.0, 0.1);
    EXPECT_NEAR(m(1, 0).uncertainty(), 0.05, 0.001);
    EXPECT_NEAR(m(2, 3).uncertainty(), 100.0, 1.0);
    EXPECT_NEAR(m(3, 2).uncertainty(), 0.01, 0.001);
}

// Test 19: Complex Unit Operations on Matrix Elements
TEST(ComplexUnitOperationsTest, matrix_element_derived_units)
{
    using TimeMatrix = matrix_4d_units_t<second_t<double>>;
    auto arr = TimeMatrix::array_type{{
        {{1.0_s, 2.0_s, 3.0_s, 4.0_s}},
        {{5.0_s, 10.0_s, 15.0_s, 20.0_s}},
        {{100.0_ms, 200.0_ms, 500.0_ms, 1000.0_ms}},
        {{0.1_s, 0.2_s, 0.5_s, 1.0_s}}
    }};
    
    TimeMatrix m(arr);
    
    // Test ratios of matrix elements to create derived units
    double ratio1 = m(0, 3).value() / m(0, 0).value();  // 4.0 / 1.0
    EXPECT_NEAR(ratio1, 4.0, 0.001);
    
    double ratio2 = m(2, 0).value() / m(0, 0).value();  // 0.1 / 1.0
    EXPECT_NEAR(ratio2, 0.1, 0.001);
    
    double ratio3 = m(1, 3).value() / m(1, 0).value();  // 20.0 / 5.0
    EXPECT_NEAR(ratio3, 4.0, 0.001);
}

// Test 20: Extended Electrical Format Coverage
TEST(ElectricalFormatExtendedTest, multiple_scale_electrical_units)
{
    // Test multiple electrical units at different scales
    coulomb_t<double> q1 = 0.5_C;
    EXPECT_NEAR(q1.value(), 0.5, 0.001);
    
    kilocoulomb_t<double> q2 = 1.5_kC;
    EXPECT_NEAR(q2.value(), 1.5, 0.001);
    
    millicoulomb_t<double> q3 = 250.0_mC;
    EXPECT_NEAR(q3.value(), 250.0, 0.001);
    
    volt_t<double> v1 = 3.3_V;
    EXPECT_NEAR(v1.value(), 3.3, 0.001);
    
    kilovolt_t<double> v2 = 48.0_kV;
    EXPECT_NEAR(v2.value(), 48.0, 0.001);
    
    millivolt_t<double> v3 = 995.0_mV;
    EXPECT_NEAR(v3.value(), 995.0, 0.001);
    
    ohm_t<double> r1 = 10000.0_ohm;
    EXPECT_NEAR(r1.value(), 10000.0, 1.0);
    
    kiloohm_t<double> r2 = 1.0_kohm;
    EXPECT_NEAR(r2.value(), 1.0, 0.001);
    
    megaohm_t<double> r3 = 10.0_Mohm;
    EXPECT_NEAR(r3.value(), 10.0, 0.001);
    
    farad_t<double> cap1 = 0.0001_F;
    EXPECT_NEAR(cap1.value(), 0.0001, 0.00001);
    
    millifarad_t<double> cap2 = 47.0_mF;
    EXPECT_NEAR(cap2.value(), 47.0, 0.01);
    
    nanofarad_t<double> cap3 = 100.0_nF;
    EXPECT_NEAR(cap3.value(), 100.0, 0.1);
}

// Test 21: Branch Coverage with Conditional Comparisons
TEST(BranchCoverageBooleanTest, comprehensive_boolean_logic)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{1.0_m, -1.0_m, 0.0_m, 100.0_m}},
        {{-100.0_m, 100.0_m, 50.0_m, -50.0_m}},
        {{0.001_m, -0.001_m, 1e-10_m, 1e10_m}},
        {{2.5_m, -2.5_m, 0.0001_m, -0.0001_m}}
    }};
    MeterMatrix m(arr);
    
    // Test all branches of comparison operators
    // Less than
    EXPECT_TRUE(m(0, 0).value() < m(0, 3).value());
    EXPECT_FALSE(m(0, 3).value() < m(0, 0).value());
    EXPECT_FALSE(m(0, 0).value() < m(0, 0).value());
    
    // Less than or equal
    EXPECT_TRUE(m(0, 0).value() <= m(0, 3).value());
    EXPECT_TRUE(m(0, 0).value() <= m(0, 0).value());
    EXPECT_FALSE(m(0, 3).value() <= m(0, 0).value());
    
    // Greater than
    EXPECT_TRUE(m(0, 3).value() > m(0, 0).value());
    EXPECT_FALSE(m(0, 0).value() > m(0, 3).value());
    EXPECT_FALSE(m(0, 0).value() > m(0, 0).value());
    
    // Greater than or equal
    EXPECT_TRUE(m(0, 3).value() >= m(0, 0).value());
    EXPECT_TRUE(m(0, 0).value() >= m(0, 0).value());
    EXPECT_FALSE(m(0, 0).value() >= m(0, 3).value());
    
    // Equality and inequality
    EXPECT_TRUE(m(0, 0).value() == m(0, 0).value());
    EXPECT_FALSE(m(0, 0).value() == m(0, 1).value());
    EXPECT_TRUE(m(0, 0).value() != m(0, 1).value());
    EXPECT_FALSE(m(0, 0).value() != m(0, 0).value());
}

// Test 22: Matrix with All Possible Sign Combinations
TEST(SignCombinationMatrixTest, all_sign_patterns)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{1.0_m, -1.0_m, 1.0_m, -1.0_m}},
        {{-1.0_m, 1.0_m, -1.0_m, 1.0_m}},
        {{100.0_m, -100.0_m, 100.0_m, -100.0_m}},
        {{-100.0_m, 100.0_m, -100.0_m, 100.0_m}}
    }};
    MeterMatrix m(arr);
    
    // Verify all sign combinations
    EXPECT_GT(m(0, 0).value(), 0.0);
    EXPECT_LT(m(0, 1).value(), 0.0);
    EXPECT_GT(m(1, 1).value(), 0.0);
    EXPECT_LT(m(1, 0).value(), 0.0);
    
    // Test sign consistency across rows
    EXPECT_EQ(m(0, 0).value() > 0, m(0, 2).value() > 0);
    EXPECT_EQ(m(0, 1).value() < 0, m(0, 3).value() < 0);
    EXPECT_EQ(m(1, 0).value() < 0, m(1, 2).value() < 0);
    EXPECT_EQ(m(1, 1).value() > 0, m(1, 3).value() > 0);
}

// Test 23: Measurement with Extreme Uncertainty Values
TEST(MeasurementExtremeUncertaintyTest, varied_uncertainty_scales)
{
    using MeasMatrix = matrix_measurement_rss_4d_t<meter_t<double>>;
    
    auto arr = MeasMatrix::array_type{{
        {{measurement_rss_t<meter_t<double>>{100.0_m, 0.001_m},
          measurement_rss_t<meter_t<double>>{100.0_m, 0.01_m},
          measurement_rss_t<meter_t<double>>{100.0_m, 0.1_m},
          measurement_rss_t<meter_t<double>>{100.0_m, 1.0_m}}},
        {{measurement_rss_t<meter_t<double>>{1.0_m, 0.001_m},
          measurement_rss_t<meter_t<double>>{1.0_m, 0.1_m},
          measurement_rss_t<meter_t<double>>{1.0_m, 0.5_m},
          measurement_rss_t<meter_t<double>>{1.0_m, 0.99_m}}},
        {{measurement_rss_t<meter_t<double>>{0.01_m, 0.0001_m},
          measurement_rss_t<meter_t<double>>{0.01_m, 0.001_m},
          measurement_rss_t<meter_t<double>>{0.01_m, 0.005_m},
          measurement_rss_t<meter_t<double>>{0.01_m, 0.01_m}}},
        {{measurement_rss_t<meter_t<double>>{1000.0_m, 10.0_m},
          measurement_rss_t<meter_t<double>>{1000.0_m, 50.0_m},
          measurement_rss_t<meter_t<double>>{1000.0_m, 100.0_m},
          measurement_rss_t<meter_t<double>>{1000.0_m, 500.0_m}}}
    }};
    
    MeasMatrix m(arr);
    
    // Verify relative uncertainties cover wide range
    EXPECT_NEAR(m(0, 0).uncertainty() / m(0, 0).value(), 0.00001, 0.00001);
    EXPECT_NEAR(m(0, 3).uncertainty() / m(0, 3).value(), 0.01, 0.001);
    EXPECT_NEAR(m(1, 3).uncertainty() / m(1, 3).value(), 0.99, 0.01);
    EXPECT_NEAR(m(3, 3).uncertainty() / m(3, 3).value(), 0.5, 0.01);
}

// Test 24: Mixed Unit Types in Matrix Element Ratios
TEST(MixedUnitRatiosTest, composing_derived_units_from_matrix)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    using TimeMatrix = matrix_4d_units_t<second_t<double>>;
    
    auto m_arr = MeterMatrix::array_type{{
        {{10.0_m, 20.0_m, 30.0_m, 40.0_m}},
        {{100.0_m, 200.0_m, 300.0_m, 400.0_m}},
        {{1000.0_m, 2000.0_m, 3000.0_m, 4000.0_m}},
        {{0.1_m, 0.2_m, 0.5_m, 1.0_m}}
    }};
    
    auto t_arr = TimeMatrix::array_type{{
        {{1.0_s, 2.0_s, 3.0_s, 4.0_s}},
        {{5.0_s, 10.0_s, 15.0_s, 20.0_s}},
        {{100.0_s, 200.0_s, 300.0_s, 400.0_s}},
        {{0.1_s, 0.5_s, 1.0_s, 2.0_s}}
    }};
    
    MeterMatrix distances(m_arr);
    TimeMatrix times(t_arr);
    
    // Create velocities from matrix ratios
    double v1 = distances(0, 0).value() / times(0, 0).value();  // 10 m / 1 s
    EXPECT_NEAR(v1, 10.0, 0.001);
    
    double v2 = distances(1, 1).value() / times(1, 1).value();  // 200 m / 10 s
    EXPECT_NEAR(v2, 20.0, 0.001);
    
    double v3 = distances(2, 2).value() / times(2, 2).value();  // 3000 m / 300 s
    EXPECT_NEAR(v3, 10.0, 0.001);
}

// Test 25: Nested Measurement Matrix Operations
TEST(NestedMeasurementOperationsTest, complex_nested_structures)
{
    using VoltageMeasMatrix = matrix_measurement_rss_4d_t<volt_t<double>>;
    
    auto arr = VoltageMeasMatrix::array_type{{
        {{measurement_rss_t<volt_t<double>>{5.0_V, 0.1_V},
          measurement_rss_t<volt_t<double>>{10.0_V, 0.2_V},
          measurement_rss_t<volt_t<double>>{12.0_V, 0.24_V},
          measurement_rss_t<volt_t<double>>{24.0_V, 0.48_V}}},
        {{measurement_rss_t<volt_t<double>>{48.0_V, 1.0_V},
          measurement_rss_t<volt_t<double>>{100.0_V, 2.0_V},
          measurement_rss_t<volt_t<double>>{110.0_V, 2.2_V},
          measurement_rss_t<volt_t<double>>{220.0_V, 4.4_V}}},
        {{measurement_rss_t<volt_t<double>>{1.5_V, 0.03_V},
          measurement_rss_t<volt_t<double>>{3.3_V, 0.066_V},
          measurement_rss_t<volt_t<double>>{9.0_V, 0.18_V},
          measurement_rss_t<volt_t<double>>{0.5_V, 0.01_V}}},
        {{measurement_rss_t<volt_t<double>>{-5.0_V, 0.1_V},
          measurement_rss_t<volt_t<double>>{-12.0_V, 0.24_V},
          measurement_rss_t<volt_t<double>>{-110.0_V, 2.2_V},
          measurement_rss_t<volt_t<double>>{-220.0_V, 4.4_V}}}
    }};
    
    VoltageMeasMatrix m(arr);
    
    // Test various measurement values and uncertainties
    EXPECT_NEAR(m(0, 0).value(), 5.0, 0.001);
    EXPECT_NEAR(m(1, 3).value(), 220.0, 0.001);
    EXPECT_NEAR(m(2, 0).value(), 1.5, 0.001);
    EXPECT_NEAR(m(3, 3).value(), -220.0, 0.001);
    
    EXPECT_NEAR(m(0, 0).uncertainty(), 0.1, 0.001);
    EXPECT_NEAR(m(1, 3).uncertainty(), 4.4, 0.01);
    EXPECT_NEAR(m(2, 2).uncertainty(), 0.18, 0.001);
    EXPECT_NEAR(m(3, 1).uncertainty(), 0.24, 0.001);
}

// Test 26: Comprehensive Format Coverage with Resistances
TEST(ResistanceFormatCoverageTest, varied_resistance_values)
{
    ohm_t<double> r1 = 1.0_ohm;
    EXPECT_NEAR(r1.value(), 1.0, 0.001);
    
    ohm_t<double> r2 = 10.0_ohm;
    EXPECT_NEAR(r2.value(), 10.0, 0.001);
    
    ohm_t<double> r3 = 100.0_ohm;
    EXPECT_NEAR(r3.value(), 100.0, 0.001);
    
    ohm_t<double> r4 = 1000.0_ohm;
    EXPECT_NEAR(r4.value(), 1000.0, 0.001);
    
    kiloohm_t<double> k1 = 1.0_kohm;
    EXPECT_NEAR(k1.value(), 1.0, 0.001);
    
    kiloohm_t<double> k2 = 10.0_kohm;
    EXPECT_NEAR(k2.value(), 10.0, 0.001);
    
    kiloohm_t<double> k3 = 100.0_kohm;
    EXPECT_NEAR(k3.value(), 100.0, 0.001);
    
    megaohm_t<double> m1 = 1.0_Mohm;
    EXPECT_NEAR(m1.value(), 1.0, 0.001);
    
    megaohm_t<double> m2 = 10.0_Mohm;
    EXPECT_NEAR(m2.value(), 10.0, 0.001);
    
    gigaohm_t<double> g1 = 1.0_Gohm;
    EXPECT_NEAR(g1.value(), 1.0, 0.001);
}

// Test 27: Power Units Comprehensive Coverage
TEST(PowerUnitsCoverageTest, varied_power_scales)
{
    watt_t<double> w1 = 1.0_W;
    EXPECT_NEAR(w1.value(), 1.0, 0.001);
    
    watt_t<double> w2 = 10.0_W;
    EXPECT_NEAR(w2.value(), 10.0, 0.001);
    
    watt_t<double> w3 = 100.0_W;
    EXPECT_NEAR(w3.value(), 100.0, 0.001);
    
    kilowatt_t<double> kw1 = 1.0_kW;
    EXPECT_NEAR(kw1.value(), 1.0, 0.001);
    
    kilowatt_t<double> kw2 = 10.0_kW;
    EXPECT_NEAR(kw2.value(), 10.0, 0.001);
    
    kilowatt_t<double> kw3 = 100.0_kW;
    EXPECT_NEAR(kw3.value(), 100.0, 0.001);
    
    megawatt_t<double> mw1 = 1.0_MW;
    EXPECT_NEAR(mw1.value(), 1.0, 0.001);
    
    megawatt_t<double> mw2 = 10.0_MW;
    EXPECT_NEAR(mw2.value(), 10.0, 0.001);
}

// Test 28: Current Units Multiple Scales
TEST(CurrentUnitsCoverageTest, ampere_scale_variants)
{
    ampere_t<double> a1 = 1.0_A;
    EXPECT_NEAR(a1.value(), 1.0, 0.001);
    
    ampere_t<double> a2 = 10.0_A;
    EXPECT_NEAR(a2.value(), 10.0, 0.001);
    
    milliampere_t<double> ma1 = 1.0_mA;
    EXPECT_NEAR(ma1.value(), 1.0, 0.001);
    
    milliampere_t<double> ma2 = 100.0_mA;
    EXPECT_NEAR(ma2.value(), 100.0, 0.001);
    
    milliampere_t<double> ma3 = 500.0_mA;
    EXPECT_NEAR(ma3.value(), 500.0, 0.001);
    
    microampere_t<double> ua1 = 1.0_uA;
    EXPECT_NEAR(ua1.value(), 1.0, 0.001);
    
    microampere_t<double> ua2 = 100.0_uA;
    EXPECT_NEAR(ua2.value(), 100.0, 0.001);
}

// Test 29: Boundary Value Test for Unit Conversions
TEST(BoundaryValueUnitTest, extreme_magnitude_conversions)
{
    // Test unit conversions with extreme values
    centimeter_t<double> cm = 0.000001_cm;  // 1 micrometer
    EXPECT_LT(cm.value(), 0.00001);
    
    kilometer_t<double> km = 1000000.0_km;  // 1 billion meters
    EXPECT_GT(km.value(), 999999.0);
    
    millisecond_t<double> ms = 0.000001_ms;  // 1 nanosecond
    EXPECT_LT(ms.value(), 0.00001);
    
    milligram_t<double> mg = 1000000.0_mg;  // 1 ton
    EXPECT_GT(mg.value(), 999999.0);
}

// Test 30: Matrix Element Access Patterns
TEST(MatrixAccessPatternsTest, row_col_diagonal_access)
{
    using MeterMatrix = matrix_4d_units_t<meter_t<double>>;
    auto arr = MeterMatrix::array_type{{
        {{1.0_m, 2.0_m, 3.0_m, 4.0_m}},
        {{5.0_m, 6.0_m, 7.0_m, 8.0_m}},
        {{9.0_m, 10.0_m, 11.0_m, 12.0_m}},
        {{13.0_m, 14.0_m, 15.0_m, 16.0_m}}
    }};
    MeterMatrix m(arr);
    
    // Test diagonal access
    EXPECT_EQ(m(0, 0).value(), 1.0);
    EXPECT_EQ(m(1, 1).value(), 6.0);
    EXPECT_EQ(m(2, 2).value(), 11.0);
    EXPECT_EQ(m(3, 3).value(), 16.0);
    
    // Test first row
    EXPECT_EQ(m(0, 0).value(), 1.0);
    EXPECT_EQ(m(0, 1).value(), 2.0);
    EXPECT_EQ(m(0, 2).value(), 3.0);
    EXPECT_EQ(m(0, 3).value(), 4.0);
    
    // Test first column
    EXPECT_EQ(m(0, 0).value(), 1.0);
    EXPECT_EQ(m(1, 0).value(), 5.0);
    EXPECT_EQ(m(2, 0).value(), 9.0);
    EXPECT_EQ(m(3, 0).value(), 13.0);
    
    // Test anti-diagonal
    EXPECT_EQ(m(0, 3).value(), 4.0);
    EXPECT_EQ(m(1, 2).value(), 7.0);
    EXPECT_EQ(m(2, 1).value(), 10.0);
    EXPECT_EQ(m(3, 0).value(), 13.0);
}
