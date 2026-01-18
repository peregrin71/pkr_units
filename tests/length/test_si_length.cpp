#include <gtest/gtest.h>
#include <pkr_units/standard/length.h>
#include <pkr_units/imperial/length.h>
#include <pkr_units/astronomical/length.h>

namespace pkr::units
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
    pkr::units::meter_t m{5.0};
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
}

TEST_F(SiLengthTest, meter_dereference_operator)
{
    pkr::units::meter_t m{5.0};
    ASSERT_DOUBLE_EQ(*m, 5.0);
}

TEST_F(SiLengthTest, meter_zero_value)
{
    pkr::units::meter_t m{0.0};
    ASSERT_DOUBLE_EQ(m.value(), 0.0);
}

TEST_F(SiLengthTest, meter_negative_value)
{
    pkr::units::meter_t m{-3.5};
    ASSERT_DOUBLE_EQ(m.value(), -3.5);
}

TEST_F(SiLengthTest, kilometer_construction)
{
    pkr::units::kilometer_t km{2.5};
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthTest, millimeter_construction)
{
    pkr::units::millimeter_t mm{1500.0};
    ASSERT_DOUBLE_EQ(mm.value(), 1500.0);
}

// ============================================================================
// Copy and Move Semantics Tests
// ============================================================================

TEST_F(SiLengthTest, copy_constructor)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{m1};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_constructor)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{std::move(m1)};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, copy_assignment)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{0.0};
    m2 = m1;
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_assignment)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{0.0};
    m2 = std::move(m1);
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

// ============================================================================
// Dimension Tests
// ============================================================================

TEST_F(SiLengthTest, meter_has_length_dimension)
{
    pkr::units::meter_t m{5.0};
    ASSERT_EQ(decltype(m)::dimension::value.length, 1);
    ASSERT_EQ(decltype(m)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(m)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, area_has_correct_dimension)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{3.0};
    auto area = m1 * m2;
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
    ASSERT_EQ(decltype(area)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(area)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, volume_has_correct_dimension)
{
    pkr::units::meter_t m1{5.0};
    pkr::units::meter_t m2{3.0};
    pkr::units::meter_t m3{2.0};
    auto area = m1 * m2;
    auto volume = area * m3;
    ASSERT_EQ(decltype(volume)::dimension::value.length, 3);
}

// ============================================================================
// Template Parameter Tests
// ============================================================================

TEST_F(SiLengthTest, length_with_float)
{
    pkr::units::length_unit_t<float> m{5.0f};
    ASSERT_FLOAT_EQ(m.value(), 5.0f);
}

TEST_F(SiLengthTest, length_with_custom_ratio)
{
    pkr::units::length_unit_t<double, std::kilo> km{2.5};
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthTest, length_with_float_and_kilo)
{
    pkr::units::length_unit_t<float, std::kilo> km{2.5f};
    ASSERT_FLOAT_EQ(km.value(), 2.5f);
}

// ============================================================================
// Edge Case Tests
// ============================================================================

TEST_F(SiLengthTest, very_small_values)
{
    pkr::units::nanometer_t nm{0.001};
    ASSERT_DOUBLE_EQ(nm.value(), 0.001);
}

TEST_F(SiLengthTest, very_large_values)
{
    pkr::units::kilometer_t km{1e6};  // 1 million kilometers
    ASSERT_DOUBLE_EQ(km.value(), 1e6);
}














