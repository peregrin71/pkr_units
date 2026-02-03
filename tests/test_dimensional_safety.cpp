// ============================================================================
// Dimensional Type Safety Demonstration Tests
// ============================================================================
// This file demonstrates compile-time type safety by attempting invalid
// operations that mix incompatible dimensions. These operations should
// fail at compile-time with clear error messages from the C++ type system.
//
// To see the compilation errors, uncomment the test cases below and attempt
// to build. The compiler will reject the code with dimension mismatch errors.
//
// This file serves as documentation of what the library prevents.
// ============================================================================

#include <gtest/gtest.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/base/time.h>

class DimensionalSafetyTest : public ::testing::Test
{
};

// ============================================================================
// COMPILE-TIME TYPE SAFETY: Dimension Mismatch Detection
// ============================================================================

// Uncomment below to see compile-time error messages:
// The library prevents adding incompatible dimensions at compile-time.

/*
TEST_F(DimensionalSafetyTest, subtract_meter_from_second_should_not_compile)
{
    // This operation should fail at compile-time because meter [L] and second [T]
    // have different dimensions and cannot be subtracted.
    //
    // Expected compile error (shortened):
    // error: no viable overloaded operator-() found
    // 'operator-(const meter_t &, const second_t &)' requires 1 argument,
    // but 2 arguments of type 'meter_t' and 'second_t' are available
    //
    // The requires clause checks:
    // is_pkr_unit<T1>::value_dimension == is_pkr_unit<T2>::value_dimension
    // which evaluates to: length_dimension == time_dimension → FALSE

    pkr::units::meter_t length{5.0};
    pkr::units::second_t time_val{3.0};

    [[maybe_unused]] auto result = length - time_val; // ✗ COMPILE ERROR: dimension mismatch
}
*/

/*
TEST_F(DimensionalSafetyTest, add_meter_to_second_should_not_compile)
{
    // Similarly, adding a meter and second should fail at compile-time.
    //
    // Expected compile error:
    // error: no viable overloaded operator+() found
    // 'operator+(const meter_t &, const second_t &)' requires dimensions to match
    
    meter_t length{5.0};
    second_t time_val{3.0};
    
    auto result = length + time_val;  // ✗ COMPILE ERROR: dimension mismatch
    (void)result;
}
*/

// ============================================================================
// Reference: Valid Operations (These DO Compile)
// ============================================================================

// Adding same dimensions works:
TEST_F(DimensionalSafetyTest, add_meters_compiles)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{3.0};

    auto result = m1 + m2; // ✓ Valid: meter + meter = meter
    ASSERT_DOUBLE_EQ(result.value(), 8.0);
}

// Adding different ratios of same dimension works:
TEST_F(DimensionalSafetyTest, add_meters_and_kilometers_compiles)
{
    pkr::units::meter_t<double> m{500.0};
    pkr::units::kilometer_t<double> km{1.0};

    auto result = m + km; // ✓ Valid: meter + kilometer = meter (LHS type)
    ASSERT_DOUBLE_EQ(result.value(), 1500.0);
}

// Multiplying different dimensions works (produces new dimension):
TEST_F(DimensionalSafetyTest, multiply_meter_by_second_compiles)
{
    pkr::units::meter_t<double> length{5.0};
    pkr::units::second_t<double> time_val{3.0};

    auto result = length * time_val; // ✓ Valid: L × T creates new dimension
    ASSERT_DOUBLE_EQ(result.value(), 15.0);
    // Result type: unit_t<double, ratio<1,1>, {length:1, time:1}>
}

// ============================================================================
// Documentation: What Gets Prevented
// ============================================================================
//
// The following operations are PREVENTED at compile-time:
//
// 1. Dimension mismatch in addition/subtraction:
//    - meter + second         ✗ Different dimensions
//    - kilogram - ampere      ✗ Different dimensions
//    - kelvin + mole          ✗ Different dimensions
//
// 2. Type-level enforcement:
//    - The compiler checks the requires clause at template instantiation time
//    - Mismatched dimensions cause immediate compile-time rejection
//    - No runtime overhead, no dynamic checks needed
//
// 3. Benefits:
//    - Catches unit errors early in development
//    - Zero cost: checks happen only at compile-time
//    - Clear error messages (compiler output shows dimension mismatch)
//    - Prevents entire categories of physics errors
//
// ============================================================================
