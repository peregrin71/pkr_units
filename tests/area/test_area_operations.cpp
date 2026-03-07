#include <gtest/gtest.h>
#include <pkr_units/si_units.h>

namespace test
{

using namespace ::testing;
using namespace pkr::units;

static_assert(
    std::is_same_v<decltype(std::declval<square_meter_t<double>>() + std::declval<square_meter_t<double>>()), square_meter_t<double>>,
    "Area addition must return square_meter_t");
static_assert(
    std::is_same_v<decltype(std::declval<square_meter_t<double>>() * 2.0), square_meter_t<double>>,
    "Area scalar multiplication must return square_meter_t");
static_assert(
    std::is_same_v<decltype(std::declval<cubic_meter_t<double>>() + std::declval<cubic_meter_t<double>>()), cubic_meter_t<double>>,
    "Volume addition must return cubic_meter_t");
static_assert(std::is_same_v<decltype(std::declval<cubic_meter_t<double>>() / 2.0), cubic_meter_t<double>>, "Volume division must return cubic_meter_t");

class AreaOperationsTest : public Test
{
};

TEST_F(AreaOperationsTest, area_construction)
{
    square_meter_t<double> area{25.0};
    ASSERT_DOUBLE_EQ(area.value(), 25.0);
}

TEST_F(AreaOperationsTest, area_dereference)
{
    square_meter_t<double> area{100.0};
    ASSERT_DOUBLE_EQ(*area, 100.0);
}

TEST_F(AreaOperationsTest, area_addition)
{
    square_meter_t<double> a1{25.0};
    square_meter_t<double> a2{75.0};
    auto result = a1 + a2;
    static_assert(std::is_same_v<decltype(result), square_meter_t<double>>, "area addition type check");
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

TEST_F(AreaOperationsTest, area_subtraction)
{
    square_meter_t<double> a1{100.0};
    square_meter_t<double> a2{25.0};
    auto result = a1 - a2;
    ASSERT_DOUBLE_EQ(result.value(), 75.0);
}

TEST_F(AreaOperationsTest, area_scalar_multiplication)
{
    square_meter_t<double> area{50.0};
    auto result = area * 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

TEST_F(AreaOperationsTest, scalar_area_multiplication)
{
    square_meter_t<double> area{50.0};
    auto result = 2.0 * area;
    ASSERT_DOUBLE_EQ(result.value(), 100.0);
}

TEST_F(AreaOperationsTest, area_scalar_division)
{
    square_meter_t<double> area{100.0};
    auto result = area / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 50.0);
}

TEST_F(AreaOperationsTest, area_conversion_m2_to_cm2)
{
    square_meter_t<double> m2{1.0};
    auto cm2 = unit_cast<square_centimeter_t<double>>(m2);
    ASSERT_DOUBLE_EQ(cm2.value(), 10000.0);
}

TEST_F(AreaOperationsTest, area_conversion_cm2_to_m2)
{
    square_centimeter_t<double> cm2{10000.0};
    auto m2 = unit_cast<square_meter_t<double>>(cm2);
    ASSERT_DOUBLE_EQ(m2.value(), 1.0);
}

TEST_F(AreaOperationsTest, area_conversion_km2_to_m2)
{
    square_kilometer_t<double> km2{1.0};
    auto m2 = unit_cast<square_meter_t<double>>(km2);
    ASSERT_DOUBLE_EQ(m2.value(), 1000000.0);
}

TEST_F(AreaOperationsTest, derived_area_from_lengths)
{
    meter_t<double> length1{5.0};
    meter_t<double> length2{4.0};
    auto area = length1 * length2;
    static_assert(std::is_same_v<decltype(area), square_meter_t<double>>, "length product must be square_meter_t");
    ASSERT_DOUBLE_EQ(area.value(), 20.0);
}

TEST_F(AreaOperationsTest, area_comparison)
{
    square_meter_t<double> a1{50.0};
    square_meter_t<double> a2{50.0};
    square_meter_t<double> a3{100.0};

    ASSERT_TRUE(a1 == a2);
    ASSERT_FALSE(a1 == a3);
    ASSERT_TRUE(a1 != a3);
    ASSERT_TRUE(a1 < a3);
    ASSERT_TRUE(a3 > a1);
}

TEST_F(AreaOperationsTest, area_zero_value)
{
    square_meter_t<double> area{0.0};
    ASSERT_DOUBLE_EQ(area.value(), 0.0);
}

TEST_F(AreaOperationsTest, area_negative_value)
{
    square_meter_t<double> area{-10.0};
    ASSERT_DOUBLE_EQ(area.value(), -10.0);
}

TEST_F(AreaOperationsTest, area_multiplication_by_zero)
{
    square_meter_t<double> area{100.0};
    auto result = area * 0.0;
    ASSERT_DOUBLE_EQ(result.value(), 0.0);
}

class VolumeOperationsTest : public Test
{
};

TEST_F(VolumeOperationsTest, volume_construction)
{
    cubic_meter_t<double> volume{125.0};
    ASSERT_DOUBLE_EQ(volume.value(), 125.0);
}

TEST_F(VolumeOperationsTest, volume_addition)
{
    cubic_meter_t<double> v1{100.0};
    cubic_meter_t<double> v2{50.0};
    auto result = v1 + v2;
    ASSERT_DOUBLE_EQ(result.value(), 150.0);
}

TEST_F(VolumeOperationsTest, volume_subtraction)
{
    cubic_meter_t<double> v1{100.0};
    cubic_meter_t<double> v2{30.0};
    auto result = v1 - v2;
    ASSERT_DOUBLE_EQ(result.value(), 70.0);
}

TEST_F(VolumeOperationsTest, volume_scalar_multiplication)
{
    cubic_meter_t<double> volume{50.0};
    auto result = volume * 3.0;
    ASSERT_DOUBLE_EQ(result.value(), 150.0);
}

TEST_F(VolumeOperationsTest, volume_scalar_division)
{
    cubic_meter_t<double> volume{120.0};
    auto result = volume / 2.0;
    ASSERT_DOUBLE_EQ(result.value(), 60.0);
}

TEST_F(VolumeOperationsTest, volume_conversion_m3_to_cm3)
{
    cubic_meter_t<double> m3{1.0};
    auto cm3 = unit_cast<cubic_centimeter_t<double>>(m3);
    ASSERT_DOUBLE_EQ(cm3.value(), 1e6);
}

TEST_F(VolumeOperationsTest, volume_conversion_cm3_to_m3)
{
    cubic_centimeter_t<double> cm3{1e6};
    auto m3 = unit_cast<cubic_meter_t<double>>(cm3);
    ASSERT_DOUBLE_EQ(m3.value(), 1.0);
}

TEST_F(VolumeOperationsTest, derived_volume_from_lengths)
{
    meter_t<double> edge{3.0};
    auto volume = edge * edge * edge;
    static_assert(std::is_same_v<decltype(volume), cubic_meter_t<double>>, "length product (3x) must be cubic_meter_t");
    ASSERT_DOUBLE_EQ(volume.value(), 27.0);
}

TEST_F(VolumeOperationsTest, volume_comparison)
{
    cubic_meter_t<double> v1{100.0};
    cubic_meter_t<double> v2{100.0};
    cubic_meter_t<double> v3{200.0};

    ASSERT_TRUE(v1 == v2);
    ASSERT_TRUE(v1 < v3);
    ASSERT_TRUE(v3 > v1);
}

TEST_F(VolumeOperationsTest, volume_zero_and_negative)
{
    cubic_meter_t<double> zero{0.0};
    cubic_meter_t<double> negative{-50.0};

    ASSERT_DOUBLE_EQ(zero.value(), 0.0);
    ASSERT_DOUBLE_EQ(negative.value(), -50.0);
}

} // namespace test
