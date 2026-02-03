#include <gtest/gtest.h>
#include <format>
#include <string>
#include <pkr_units/units/base/angle.h>
#include <pkr_units/astronomical_units.h>
#include <pkr_units/astronomical_units_formatting.h>

using namespace PKR_UNITS_NAMESPACE;

class AstronomicalAngleFormattingTest : public ::testing::Test
{
};

TEST_F(AstronomicalAngleFormattingTest, hms_angle_formatting)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_archour_t<double>{12.5});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "12h 30m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_negative_formatting)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_archour_t<double>{-1.25});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "-1h 15m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_from_degree)
{
    auto ra = unit_cast<hms_angle_t<double>>(degree_t<double>{15.0});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "1h 0m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_from_second)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_arcsecond_t<double>{1.0});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "0h 0m 1s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_from_second_roundup)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_arcsecond_t<double>{0.6});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "0h 0m 1s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_from_second_round_half)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_arcsecond_t<double>{0.5});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "0h 0m 1s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_from_second_rounddown)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_arcsecond_t<double>{0.4});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "0h 0m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_roundup_to_minute)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_arcsecond_t<double>{59.6});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "0h 1m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_roundup_to_hour)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_arcsecond_t<double>{3599.6});
    std::string result = std::format("{}", ra);
    EXPECT_EQ(result, "1h 0m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_angle_wide_formatting)
{
    auto ra = unit_cast<hms_angle_t<double>>(hms_archour_t<double>{12.5});
    std::wstring result = std::format(L"{}", ra);
    EXPECT_EQ(result, L"12ʰ30ᵐ0ˢ");
}

TEST_F(AstronomicalAngleFormattingTest, hms_archour_formatting)
{
    hms_archour_t<double> ha{2.0};
    std::string result = std::format("{}", ha);
    EXPECT_EQ(result, "2h");
}

TEST_F(AstronomicalAngleFormattingTest, hms_archour_wide_formatting)
{
    hms_archour_t<double> ha{2.0};
    std::wstring result = std::format(L"{}", ha);
    EXPECT_NE(result.find(hms_archour_t<double>::w_symbol), std::wstring::npos);
}

TEST_F(AstronomicalAngleFormattingTest, hms_arcminute_formatting)
{
    hms_arcminute_t<double> am{30.0};
    std::string result = std::format("{}", am);
    EXPECT_EQ(result, "30m");
}

TEST_F(AstronomicalAngleFormattingTest, hms_arcminute_wide_formatting)
{
    hms_arcminute_t<double> am{30.0};
    std::wstring result = std::format(L"{}", am);
    EXPECT_NE(result.find(hms_arcminute_t<double>::w_symbol), std::wstring::npos);
}

TEST_F(AstronomicalAngleFormattingTest, hms_arcsecond_formatting)
{
    hms_arcsecond_t<double> as{15.0};
    std::string result = std::format("{}", as);
    EXPECT_EQ(result, "15s");
}

TEST_F(AstronomicalAngleFormattingTest, hms_arcsecond_wide_formatting)
{
    hms_arcsecond_t<double> as{15.0};
    std::wstring result = std::format(L"{}", as);
    EXPECT_NE(result.find(hms_arcsecond_t<double>::w_symbol), std::wstring::npos);
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_formatting)
{
    auto dec = unit_cast<dms_angle_t<double>>(degree_t<double>{12.5});
    std::string result = std::format("{}", dec);
    EXPECT_EQ(result, "12deg 30m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, dms_degree_wide_formatting)
{
    dms_degree_t<double> deg{12.0};
    std::wstring result = std::format(L"{}", deg);
    EXPECT_NE(result.find(dms_degree_t<double>::w_symbol), std::wstring::npos);
}

TEST_F(AstronomicalAngleFormattingTest, dms_arcminute_wide_formatting)
{
    dms_arcminute_t<double> am{30.0};
    std::wstring result = std::format(L"{}", am);
    EXPECT_NE(result.find(dms_arcminute_t<double>::w_symbol), std::wstring::npos);
}

TEST_F(AstronomicalAngleFormattingTest, dms_arcsecond_wide_formatting)
{
    dms_arcsecond_t<double> as{15.0};
    std::wstring result = std::format(L"{}", as);
    EXPECT_NE(result.find(dms_arcsecond_t<double>::w_symbol), std::wstring::npos);
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_negative_formatting)
{
    auto dec = unit_cast<dms_angle_t<double>>(degree_t{-12.5});
    std::string result = std::format("{}", dec);
    EXPECT_EQ(result, "-12deg 30m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_from_second)
{
    auto dec = unit_cast<dms_angle_t<double>>(dms_arcsecond_t<double>{1.0});
    std::string result = std::format("{}", dec);
    EXPECT_EQ(result, "0deg 0m 1s");
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_from_second_roundup)
{
    auto dec = unit_cast<dms_angle_t<double>>(dms_arcsecond_t<double>{0.6});
    std::string result = std::format("{}", dec);
    EXPECT_EQ(result, "0deg 0m 1s");
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_from_second_round_half)
{
    auto dec = unit_cast<dms_angle_t<double>>(dms_arcsecond_t<double>{0.5});
    std::string result = std::format("{}", dec);
    EXPECT_EQ(result, "0deg 0m 1s");
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_from_second_rounddown)
{
    auto dec = unit_cast<dms_angle_t<double>>(dms_arcsecond_t<double>{0.4});
    std::string result = std::format("{}", dec);
    EXPECT_EQ(result, "0deg 0m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_roundup_to_degree)
{
    auto dec = unit_cast<dms_angle_t<double>>(dms_arcsecond_t<double>{3599.6});
    std::string result = std::format("{}", dec);
    EXPECT_EQ(result, "1deg 0m 0s");
}

TEST_F(AstronomicalAngleFormattingTest, dms_angle_wide_formatting)
{
    auto dec = unit_cast<dms_angle_t<double>>(degree_t<double>{12.5});
    std::wstring result = std::format(L"{}", dec);
    EXPECT_EQ(result, L"12°30ᵐ0ˢ");
}
