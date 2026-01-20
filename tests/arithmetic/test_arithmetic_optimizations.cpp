#include <gtest/gtest.h>
#include <pkr_units/standard/length.h>
#include <pkr_units/standard/mass.h>

using namespace ::testing;

class ArithmeticOptimizationsTest : public Test
{
};

// ============================================================================
// Addition Optimizations - Same Ratio Path
// ============================================================================
// When both operands have identical ratios, the result stays in the same
// unit type (no conversion to canonical form)

TEST_F(ArithmeticOptimizationsTest, add_same_ratio_meters)
{
    // Optimized path: both meter have ratio<1,1>
    // Result stays as meter (not converted to canonical)
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{3.0};
    auto result = m1 + m2;
    
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
    // Result is meter, not canonical meter
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
    ASSERT_EQ(decltype(result)::dimension::value.length, 1);
}

TEST_F(ArithmeticOptimizationsTest, add_same_ratio_kilometers)
{
    // Optimized path: both kilometer have ratio<1000,1>
    // Result stays as kilometer (not converted to meter)
    pkr::units::kilometer_t km1{2.0};
    pkr::units::kilometer_t km2{3.0};
    auto result = km1 + km2;
    
    ASSERT_DOUBLE_EQ(result.value(), 5.0);  // Still in kilometers
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, add_same_ratio_millimeters)
{
    // Optimized path: both millimeter have ratio<1,1000>
    // Result stays as millimeter
    pkr::units::millimeter_t mm1{1500.0};
    pkr::units::millimeter_t mm2{500.0};
    auto result = mm1 + mm2;
    
    ASSERT_DOUBLE_EQ(result.value(), 2000.0);  // Still in millimeters
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1000);
}

TEST_F(ArithmeticOptimizationsTest, add_different_ratio_meter_kilometer)
{
    // Non-optimized path: meter (ratio 1/1) + kilometer (ratio 1000/1)
    // Result is in LHS type (meter)
    pkr::units::meter_t m{500.0};
    pkr::units::kilometer_t km{1.0};
    auto result = m + km;
    
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);  // 500m + 1000m = 1500m
    // Result is meter (LHS type), not canonical meter
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, add_different_ratio_kilometer_meter)
{
    // Non-optimized path: kilometer (ratio 1000/1) + meter (ratio 1/1)
    // Result is in LHS type (kilometer)
    pkr::units::kilometer_t km{1.0};
    pkr::units::meter_t m{500.0};
    auto result = km + m;
    
    ASSERT_DOUBLE_EQ(result.value(), 1.5);  // 1km + 0.5km = 1.5km
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);  // LHS ratio (kilometer)
}

TEST_F(ArithmeticOptimizationsTest, add_different_ratio_millimeter_meter)
{
    // Non-optimized path: millimeter (ratio 1/1000) + meter (ratio 1/1)
    // Result is in LHS type (millimeter)
    pkr::units::millimeter_t mm{500.0};
    pkr::units::meter_t m{1.0};
    auto result = mm + m;
    
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);  // 500mm + 1000mm = 1500mm
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1000);  // LHS ratio (millimeter)
}

// ============================================================================
// Subtraction Optimizations - Same Ratio Path
// ============================================================================

TEST_F(ArithmeticOptimizationsTest, subtract_same_ratio_meters)
{
    // Optimized path: both meter have ratio<1,1>
    // Result stays as meter
    pkr::units::meter_t m1{8.0};
    pkr::units::meter_t m2{3.0};
    auto result = m1 - m2;
    
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, subtract_same_ratio_kilometers)
{
    // Optimized path: both kilometer have ratio<1000,1>
    // Result stays as kilometer
    pkr::units::kilometer_t km1{5.0};
    pkr::units::kilometer_t km2{2.0};
    auto result = km1 - km2;
    
    ASSERT_DOUBLE_EQ(result.value(), 3.0);  // Still in kilometers
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, subtract_same_ratio_millimeters)
{
    // Optimized path: both millimeter have ratio<1,1000>
    // Result stays as millimeter
    pkr::units::millimeter_t mm1{2000.0};
    pkr::units::millimeter_t mm2{500.0};
    auto result = mm1 - mm2;
    
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);  // Still in millimeters
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1000);
}

TEST_F(ArithmeticOptimizationsTest, subtract_different_ratio_meter_kilometer)
{
    // Non-optimized path: meter (ratio 1/1) - kilometer (ratio 1000/1)
    // Result is in LHS type (meter)
    pkr::units::meter_t m{1500.0};
    pkr::units::kilometer_t km{1.0};
    auto result = m - km;
    
    ASSERT_DOUBLE_EQ(result.value(), 500.0);  // 1500m - 1000m = 500m
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);  // LHS ratio (meter)
}

TEST_F(ArithmeticOptimizationsTest, subtract_different_ratio_kilometer_meter)
{
    // Non-optimized path: kilometer (ratio 1000/1) - meter (ratio 1/1)
    // Result is in LHS type (kilometer)
    pkr::units::kilometer_t km{2.0};
    pkr::units::meter_t m{500.0};
    auto result = km - m;
    
    ASSERT_DOUBLE_EQ(result.value(), 1.5);  // 2km - 0.5km = 1.5km
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);  // LHS ratio (kilometer)
}

// ============================================================================
// Multiplication Optimizations - Identity Ratio Path
// ============================================================================
// When either operand has ratio<1,1>, the multiplication is optimized

TEST_F(ArithmeticOptimizationsTest, multiply_both_ratio_one_meters)
{
    // Optimized path: both meter have ratio<1,1>
    // Combined ratio should be ratio<1,1> directly (no std::ratio_multiply called)
    pkr::units::meter_t m1{2.0};
    pkr::units::meter_t m2{3.0};
    auto result = m1 * m2;
    
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 2);
    // Result ratio should be 1/1
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, multiply_one_ratio_one_meter_by_kilometer)
{
    // Optimized path: meter has ratio<1,1>, kilometer has ratio<1000,1>
    // Result ratio should be ratio<1000,1> directly (no multiplication needed)
    pkr::units::meter_t m{5.0};
    pkr::units::kilometer_t km{2.0};
    auto result = m * km;
    
    ASSERT_DOUBLE_EQ(result.value(), 10.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 2);
    // Result ratio should be 1000/1
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, multiply_ratio_one_by_millimeter)
{
    // Optimized path: meter has ratio<1,1>, millimeter has ratio<1,1000>
    // Result ratio should be ratio<1,1000> directly
    pkr::units::meter_t m{5.0};
    pkr::units::millimeter_t mm{2000.0};
    auto result = m * mm;
    
    ASSERT_DOUBLE_EQ(result.value(), 10000.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 2);
    // Result ratio should be 1/1000
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1000);
}

TEST_F(ArithmeticOptimizationsTest, multiply_non_unit_ratios_kilometers)
{
    // Non-optimized path: both kilometer have ratio<1000,1>
    // Must call std::ratio_multiply<ratio<1000,1>, ratio<1000,1>> = ratio<1000000,1>
    pkr::units::kilometer_t km1{2.0};
    pkr::units::kilometer_t km2{3.0};
    auto result = km1 * km2;
    
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 2);
    // Result ratio should be 1000000/1 (product of 1000/1 * 1000/1)
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, multiply_non_unit_ratios_millimeter_kilometer)
{
    // Non-optimized path: millimeter ratio<1,1000> * kilometer ratio<1000,1>
    // Must call std::ratio_multiply<ratio<1,1000>, ratio<1000,1>> = ratio<1,1>
    pkr::units::millimeter_t mm{1000.0};
    pkr::units::kilometer_t km{1.0};
    auto result = mm * km;
    
    ASSERT_DOUBLE_EQ(result.value(), 1000.0);
    ASSERT_EQ(decltype(result)::dimension::value.length, 2);
    // Result ratio should be 1/1 (product of 1/1000 * 1000/1 = 1/1)
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

// ============================================================================
// Division Optimizations - Same and Identity Ratio Paths
// ============================================================================

TEST_F(ArithmeticOptimizationsTest, divide_same_ratio_meters)
{
    // Optimized path: both have ratio<1,1>, same ratio detected
    // Result ratio should be ratio<1,1> without calling std::ratio_divide
    pkr::units::meter_t m1{10.0};
    pkr::units::meter_t m2{2.0};
    auto result = m1 / m2;
    
    ASSERT_DOUBLE_EQ(result.value(), 5.0);
    // Result dimensions should be scalar (dimensionless)
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    // Result ratio should be 1/1
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, divide_same_ratio_kilometers)
{
    // Optimized path: both have ratio<1000,1>, same ratio detected
    // Result ratio should be ratio<1,1> without calling std::ratio_divide
    pkr::units::kilometer_t km1{5.0};
    pkr::units::kilometer_t km2{2.0};
    auto result = km1 / km2;
    
    ASSERT_DOUBLE_EQ(result.value(), 2.5);
    // Result dimensions should be scalar
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    // Result ratio should be 1/1
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, divide_same_ratio_millimeters)
{
    // Optimized path: both have ratio<1,1000>, same ratio detected
    pkr::units::millimeter_t mm1{2000.0};
    pkr::units::millimeter_t mm2{500.0};
    auto result = mm1 / mm2;
    
    ASSERT_DOUBLE_EQ(result.value(), 4.0);
    // Result dimensions should be scalar
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    // Result ratio should be 1/1
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, divide_different_ratio_meter_by_kilometer)
{
    // Non-optimized path: different ratios (meter 1/1 vs kilometer 1000/1)
    // Must call std::ratio_divide<ratio<1,1>, ratio<1000,1>> = ratio<1,1000>
    pkr::units::meter_t m{1000.0};
    pkr::units::kilometer_t km{1.0};
    auto result = m / km;
    
    // 1000m / 1000m = 1.0, stored with ratio 1/1000
    ASSERT_DOUBLE_EQ(result.value(), 1000.0);  // Raw stored value
    // Result dimensions should be scalar
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    // Result ratio should be 1/1000
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1000);

    
}

TEST_F(ArithmeticOptimizationsTest, divide_different_ratio_kilometer_by_millimeter)
{
    // Non-optimized path: different ratios (kilometer 1000/1 vs millimeter 1/1000)
    // Must call std::ratio_divide<ratio<1000,1>, ratio<1,1000>> = ratio<1000000,1>
    pkr::units::kilometer_t km{1.0};
    pkr::units::millimeter_t mm{1.0};
    auto result = km / mm;
    
    // 1000m / 0.001m = 1000000, stored with ratio 1000000/1
    ASSERT_DOUBLE_EQ(result.value(), 1.0);  // Raw stored value with ratio 1000000/1
    // Result dimensions should be scalar
    ASSERT_EQ(decltype(result)::dimension::value.length, 0);
    // Result ratio should be 1000000/1
    ASSERT_EQ(decltype(result)::ratio_type::num, 1000000);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

// ============================================================================
// Mass Arithmetic Optimizations (Same Tests on Different Dimension)
// ============================================================================

TEST_F(ArithmeticOptimizationsTest, add_same_ratio_grams)
{
    // Optimized path: both gram have ratio<1,1000>
    // Result stays as gram
    pkr::units::gram_t g1{500.0};
    pkr::units::gram_t g2{250.0};
    auto result = g1 + g2;
    
    ASSERT_DOUBLE_EQ(result.value(), 750.0);  // Still in grams
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1000);
}

TEST_F(ArithmeticOptimizationsTest, subtract_same_ratio_kilograms)
{
    // Optimized path: both kilogram have ratio<1,1> (kilogram is base SI unit)
    // Result stays as kilogram
    pkr::units::kilogram_t kg1{3.0};
    pkr::units::kilogram_t kg2{1.0};
    auto result = kg1 - kg2;
    
    ASSERT_DOUBLE_EQ(result.value(), 2.0);  // Still in kilograms
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, multiply_both_ratio_one_kilograms)
{
    // Optimized path: both kilogram have ratio<1,1> (kilogram is base SI unit)
    // Result ratio should be ratio<1,1> directly
    pkr::units::kilogram_t kg1{2.0};
    pkr::units::kilogram_t kg2{3.0};
    auto result = kg1 * kg2;
    
    ASSERT_DOUBLE_EQ(result.value(), 6.0);
    ASSERT_EQ(decltype(result)::dimension::value.mass, 2);
    // Result ratio should be 1/1 (1/1 * 1/1 = 1/1)
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}

TEST_F(ArithmeticOptimizationsTest, divide_same_ratio_grams)
{
    // Optimized path: both gram have ratio<1,1000>, same ratio detected
    pkr::units::gram_t g1{2000.0};
    pkr::units::gram_t g2{500.0};
    auto result = g1 / g2;
    
    ASSERT_DOUBLE_EQ(result.value(), 4.0);
    // Result dimensions should be scalar
    ASSERT_EQ(decltype(result)::dimension::value.mass, 0);
    // Result ratio should be 1/1
    ASSERT_EQ(decltype(result)::ratio_type::num, 1);
    ASSERT_EQ(decltype(result)::ratio_type::den, 1);
}



