#include <gtest/gtest.h>
#include <format>
#include <pkr_units/units/derived/velocity.h>
#include <pkr_units/impl/cast/unit_cast.h>

using namespace ::testing;

class VelocityFormattingTest : public Test
{
};

// ============================================================================
// Velocity Formatting Tests
// ============================================================================

TEST_F(VelocityFormattingTest, meter_per_second_formatting)
{
    pkr::units::meter_per_second_t v{1.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "1 m/s");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_formatting)
{
    // km/h has ratio 5/18 (1 km/h = 5/18 m/s)
    pkr::units::kilometer_per_hour_t v{36.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "36 km/h");
}

TEST_F(VelocityFormattingTest, centimeter_per_second_formatting)
{
    // 100 cm/s at ratio 1/100
    pkr::units::centimeter_per_second_t v{100.0};
    std::string result = std::format("{}", v);
    ASSERT_EQ(result, "100 cm/s");
}

TEST_F(VelocityFormattingTest, centimeter_per_hour_should_fallback_to_m_per_s_formatting)
{
    // 100 cm/h is not a defined unit, should fallback to m/s formatting
    pkr::units::unit_t<double, std::ratio<1, 360000>, pkr::units::velocity_dimension> v{100.0}; // 100 cm/h = 100/360000 m/s
    std::string result = std::format("{:.6g}", v);                                              // Use general format with 6 significant digits
    ASSERT_EQ(result, "0.000277778 m/s");
}

TEST_F(VelocityFormattingTest, meter_per_second_with_precision_formatting)
{
    pkr::units::meter_per_second_t v{3.14159};
    std::string result = std::format("{:.2f}", v);
    ASSERT_EQ(result, "3.14 m/s");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_with_precision_formatting)
{
    pkr::units::kilometer_per_hour_t v{100.0};
    std::string result = std::format("{:.1f}", v);
    ASSERT_EQ(result, "100.0 km/h");
}

TEST_F(VelocityFormattingTest, velocity_table_alignment)
{
    // Test alignment for table output
    pkr::units::meter_per_second_t v1{1.5};
    pkr::units::meter_per_second_t v2{25.3};
    pkr::units::meter_per_second_t v3{0.8};

    // Right align with width 10
    std::string result1 = std::format("{:>10.1f}", v1);
    std::string result2 = std::format("{:>10.1f}", v2);
    std::string result3 = std::format("{:>10.1f}", v3);

    // Values should be right-aligned, units follow
    ASSERT_EQ(result1, "       1.5 m/s");
    ASSERT_EQ(result2, "      25.3 m/s");
    ASSERT_EQ(result3, "       0.8 m/s");
}

TEST_F(VelocityFormattingTest, kilometer_per_hour_cast_to_meter_per_second_formatting)
{
    // Start with 36 km/h, which should be 10 m/s
    pkr::units::kilometer_per_hour_t kmh{36.0};

    // Cast to meter_per_second_t
    auto mps = pkr::units::unit_cast<pkr::units::meter_per_second_t>(kmh);

    // Format the cast result and verify it uses m/s
    std::string result = std::format("{}", mps);
    ASSERT_EQ(result, "10 m/s");
}
