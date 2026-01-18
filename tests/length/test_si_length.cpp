#include <gtest/gtest.h>
#include <si_units/standard/length.h>
#include <si_units/imperial/length.h>
#include <si_units/astronomical/length.h>

namespace si
{
// Test support namespace
}

using namespace ::testing;

class SiLengthTest : public Test
{
};

// ============================================================================
// Basic Construction and Value Access Tests
// ============================================================================

TEST_F(SiLengthTest, meter_construction)
{
    si::meter m{5.0};
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
}

TEST_F(SiLengthTest, meter_dereference_operator)
{
    si::meter m{5.0};
    ASSERT_DOUBLE_EQ(*m, 5.0);
}

TEST_F(SiLengthTest, meter_zero_value)
{
    si::meter m{0.0};
    ASSERT_DOUBLE_EQ(m.value(), 0.0);
}

TEST_F(SiLengthTest, meter_negative_value)
{
    si::meter m{-3.5};
    ASSERT_DOUBLE_EQ(m.value(), -3.5);
}

TEST_F(SiLengthTest, kilometer_construction)
{
    si::kilometer km{2.5};
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthTest, millimeter_construction)
{
    si::millimeter mm{1500.0};
    ASSERT_DOUBLE_EQ(mm.value(), 1500.0);
}

// ============================================================================
// Copy and Move Semantics Tests
// ============================================================================

TEST_F(SiLengthTest, copy_constructor)
{
    si::meter m1{5.0};
    si::meter m2{m1};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_constructor)
{
    si::meter m1{5.0};
    si::meter m2{std::move(m1)};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, copy_assignment)
{
    si::meter m1{5.0};
    si::meter m2{0.0};
    m2 = m1;
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_assignment)
{
    si::meter m1{5.0};
    si::meter m2{0.0};
    m2 = std::move(m1);
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

// ============================================================================
// Dimension Tests
// ============================================================================

TEST_F(SiLengthTest, meter_has_length_dimension)
{
    si::meter m{5.0};
    ASSERT_EQ(decltype(m)::dimension::value.length, 1);
    ASSERT_EQ(decltype(m)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(m)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, area_has_correct_dimension)
{
    si::meter m1{5.0};
    si::meter m2{3.0};
    auto area = m1 * m2;
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
    ASSERT_EQ(decltype(area)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(area)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, volume_has_correct_dimension)
{
    si::meter m1{5.0};
    si::meter m2{3.0};
    si::meter m3{2.0};
    auto area = m1 * m2;
    auto volume = area * m3;
    ASSERT_EQ(decltype(volume)::dimension::value.length, 3);
}

// ============================================================================
// Template Parameter Tests
// ============================================================================

TEST_F(SiLengthTest, length_with_float)
{
    si::length<float> m{5.0f};
    ASSERT_FLOAT_EQ(m.value(), 5.0f);
}

TEST_F(SiLengthTest, length_with_custom_ratio)
{
    si::length<double, std::kilo> km{2.5};
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthTest, length_with_float_and_kilo)
{
    si::length<float, std::kilo> km{2.5f};
    ASSERT_FLOAT_EQ(km.value(), 2.5f);
}

// ============================================================================
// Edge Case Tests
// ============================================================================

TEST_F(SiLengthTest, very_small_values)
{
    si::nanometer nm{0.001};
    ASSERT_DOUBLE_EQ(nm.value(), 0.001);
}

TEST_F(SiLengthTest, very_large_values)
{
    si::kilometer km{1e6};  // 1 million kilometers
    ASSERT_DOUBLE_EQ(km.value(), 1e6);
}













