#include <gtest/gtest.h>
#include <pkr_units/units/base/length.h>
#include <pkr_units/units/imperial/length.h>
#include <pkr_units/units/astronomical/length.h>
#include <pkr_units/impl/parsing/parse.h>

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
    pkr::units::meter_t<double> m{5.0};
    ASSERT_DOUBLE_EQ(m.value(), 5.0);
}

TEST_F(SiLengthTest, meter_dereference_operator)
{
    pkr::units::meter_t<double> m{5.0};
    ASSERT_DOUBLE_EQ(*m, 5.0);
}

TEST_F(SiLengthTest, meter_zero_value)
{
    pkr::units::meter_t<double> m{0.0};
    ASSERT_DOUBLE_EQ(m.value(), 0.0);
}

TEST_F(SiLengthTest, meter_negative_value)
{
    pkr::units::meter_t<double> m{-3.5};
    ASSERT_DOUBLE_EQ(m.value(), -3.5);
}

TEST_F(SiLengthTest, kilometer_construction)
{
    pkr::units::kilometer_t<double> km{2.5};
    ASSERT_DOUBLE_EQ(km.value(), 2.5);
}

TEST_F(SiLengthTest, millimeter_construction)
{
    pkr::units::millimeter_t<double> mm{1500.0};
    ASSERT_DOUBLE_EQ(mm.value(), 1500.0);
}

// ============================================================================
// Copy and Move Semantics Tests
// ============================================================================

TEST_F(SiLengthTest, copy_constructor)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{m1};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_constructor)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{std::move(m1)};
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, copy_assignment)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{0.0};
    m2 = m1;
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

TEST_F(SiLengthTest, move_assignment)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{0.0};
    m2 = std::move(m1);
    ASSERT_DOUBLE_EQ(m2.value(), 5.0);
}

// ============================================================================
// Dimension Tests
// ============================================================================

TEST_F(SiLengthTest, meter_has_length_dimension)
{
    pkr::units::meter_t<double> m{5.0};
    ASSERT_EQ(decltype(m)::dimension::value.length, 1);
    ASSERT_EQ(decltype(m)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(m)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, area_has_correct_dimension)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{3.0};
    auto area = m1 * m2;
    ASSERT_EQ(decltype(area)::dimension::value.length, 2);
    ASSERT_EQ(decltype(area)::dimension::value.mass, 0);
    ASSERT_EQ(decltype(area)::dimension::value.time, 0);
}

TEST_F(SiLengthTest, volume_has_correct_dimension)
{
    pkr::units::meter_t<double> m1{5.0};
    pkr::units::meter_t<double> m2{3.0};
    pkr::units::meter_t<double> m3{2.0};
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
    pkr::units::nanometer_t<double> nm{0.001};
    ASSERT_DOUBLE_EQ(nm.value(), 0.001);
}

TEST_F(SiLengthTest, very_large_values)
{
    pkr::units::kilometer_t<double> km{1e6}; // 1 million kilometers
    ASSERT_DOUBLE_EQ(km.value(), 1e6);
}

// ============================================================================
// Alternative constructors

TEST_F(SiLengthTest, construct_meter_from_centimeter)
{
    pkr::units::centimeter_t<double> cm{150.0}; // 150 cm
    pkr::units::meter_t<double> m{cm};          // Convert to meters
    ASSERT_DOUBLE_EQ(m.value(), 1.5);
}

// ============================================================================
// Parsing Tests
// ============================================================================

TEST_F(SiLengthTest, parse_meter_basic)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("5.0 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 5.0);
}

TEST_F(SiLengthTest, parse_meter_integer)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("10 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 10.0);
}

TEST_F(SiLengthTest, parse_kilometer)
{
    auto result = pkr::units::parse<pkr::units::kilometer_t<double>>("2.5 km");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 2.5);
}

TEST_F(SiLengthTest, parse_centimeter)
{
    auto result = pkr::units::parse<pkr::units::centimeter_t<double>>("150 cm");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 150.0);
}

TEST_F(SiLengthTest, parse_millimeter)
{
    auto result = pkr::units::parse<pkr::units::millimeter_t<double>>("1000 mm");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 1000.0);
}

TEST_F(SiLengthTest, parse_meter_no_spaces)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("5m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 5.0);
}

TEST_F(SiLengthTest, parse_meter_extra_spaces)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("  5.0  m  ");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 5.0);
}

TEST_F(SiLengthTest, parse_meter_scientific_notation)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("1.5e-3 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), 0.0015);
}

TEST_F(SiLengthTest, parse_meter_negative)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("-5.5 m");
    ASSERT_TRUE(result);
    ASSERT_DOUBLE_EQ(result.value().value(), -5.5);
}

TEST_F(SiLengthTest, parse_meter_wrong_symbol)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("5.0 s");
    ASSERT_FALSE(result);
}

TEST_F(SiLengthTest, parse_meter_invalid_number)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("abc m");
    ASSERT_FALSE(result);
}

TEST_F(SiLengthTest, parse_meter_missing_symbol)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("5.0");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result.value().value(), 5.0);
}

TEST_F(SiLengthTest, parse_meter_empty_string)
{
    auto result = pkr::units::parse<pkr::units::meter_t<double>>("");
    ASSERT_FALSE(result);
}

TEST_F(SiLengthTest, parse_meter_float_type)
{
    auto result = pkr::units::parse<pkr::units::meter_t<float>>("3.14 m");
    ASSERT_TRUE(result);
    ASSERT_FLOAT_EQ(result.value().value(), 3.14f);
}
