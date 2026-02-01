#include <gtest/gtest.h>
#include <pkr_units/units/base/time.h>
#include <pkr_units/impl/cast/chrono_cast.h>
#include <chrono>

using namespace ::testing;

class ChronoCastTest : public Test
{
};

// ============================================================================
// Chrono to PKR Units Conversion Tests
// ============================================================================

TEST_F(ChronoCastTest, chrono_seconds_to_second_t)
{
    auto chrono_secs = std::chrono::seconds(5);
    auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(chrono_secs);

    ASSERT_DOUBLE_EQ(pkr_secs.value(), 5.0);
}

TEST_F(ChronoCastTest, chrono_milliseconds_to_millisecond_t)
{
    auto chrono_ms = std::chrono::milliseconds(250);
    auto pkr_ms = pkr::units::unit_cast<pkr::units::millisecond_t>(chrono_ms);

    ASSERT_DOUBLE_EQ(pkr_ms.value(), 250.0);
}

TEST_F(ChronoCastTest, chrono_microseconds_to_microsecond_t)
{
    auto chrono_us = std::chrono::microseconds(1000);
    auto pkr_us = pkr::units::unit_cast<pkr::units::microsecond_t>(chrono_us);

    ASSERT_DOUBLE_EQ(pkr_us.value(), 1000.0);
}

TEST_F(ChronoCastTest, chrono_nanoseconds_to_nanosecond_t)
{
    auto chrono_ns = std::chrono::nanoseconds(5000);
    auto pkr_ns = pkr::units::unit_cast<pkr::units::nanosecond_t>(chrono_ns);

    ASSERT_DOUBLE_EQ(pkr_ns.value(), 5000.0);
}

TEST_F(ChronoCastTest, chrono_minutes_to_second_t)
{
    auto chrono_mins = std::chrono::minutes(2);
    auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(chrono_mins);

    ASSERT_DOUBLE_EQ(pkr_secs.value(), 120.0); // 2 minutes = 120 seconds
}

TEST_F(ChronoCastTest, chrono_hours_to_second_t)
{
    auto chrono_hours = std::chrono::hours(1);
    auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(chrono_hours);

    ASSERT_DOUBLE_EQ(pkr_secs.value(), 3600.0); // 1 hour = 3600 seconds
}

TEST_F(ChronoCastTest, chrono_custom_duration_to_second_t)
{
    // Custom duration: 10 seconds per tick
    using ten_second_duration = std::chrono::duration<long long, std::ratio<10, 1>>;
    auto chrono_custom = ten_second_duration(3); // 30 seconds
    auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(chrono_custom);

    ASSERT_DOUBLE_EQ(pkr_secs.value(), 30.0);
}

// ============================================================================
// PKR Units to Chrono - Different Scales
// ============================================================================

TEST_F(ChronoCastTest, second_t_to_chrono_hours)
{
    pkr::units::second_t pkr_secs{3600.0};
    auto chrono_hours = pkr::units::unit_cast<std::chrono::hours>(pkr_secs);

    ASSERT_EQ(chrono_hours.count(), 1);
}

TEST_F(ChronoCastTest, second_t_to_chrono_minutes)
{
    pkr::units::second_t pkr_secs{120.0};
    auto chrono_mins = pkr::units::unit_cast<std::chrono::minutes>(pkr_secs);

    ASSERT_EQ(chrono_mins.count(), 2);
}

TEST_F(ChronoCastTest, hour_t_to_chrono_hours)
{
    pkr::units::hour_t pkr_hours{3.0};
    auto chrono_hours = pkr::units::unit_cast<std::chrono::hours>(pkr_hours);

    ASSERT_EQ(chrono_hours.count(), 3);
}

TEST_F(ChronoCastTest, second_t_to_chrono_custom_duration)
{
    // Custom duration: 10 seconds per tick
    using ten_second_duration = std::chrono::duration<long long, std::ratio<10, 1>>;
    pkr::units::second_t pkr_secs{50.0}; // 5 ticks of 10 seconds
    auto chrono_custom = pkr::units::unit_cast<ten_second_duration>(pkr_secs);

    ASSERT_EQ(chrono_custom.count(), 5);
}

// ============================================================================
// Cross-Scale Round-trip Tests
// ============================================================================

TEST_F(ChronoCastTest, round_trip_chrono_hours_to_pkr_seconds)
{
    auto original_chrono = std::chrono::hours(5);

    auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(original_chrono);
    auto back_to_chrono = pkr::units::unit_cast<std::chrono::hours>(pkr_secs);

    ASSERT_EQ(back_to_chrono.count(), original_chrono.count());
}

TEST_F(ChronoCastTest, round_trip_pkr_hours_to_chrono_seconds)
{
    pkr::units::hour_t original_pkr{2.0};

    auto chrono_secs = pkr::units::unit_cast<std::chrono::seconds>(original_pkr);
    auto back_to_pkr = pkr::units::unit_cast<pkr::units::hour_t>(chrono_secs);

    ASSERT_DOUBLE_EQ(back_to_pkr.value(), original_pkr.value());
}

TEST_F(ChronoCastTest, complex_conversion_chain)
{
    // chrono minutes -> pkr milliseconds -> chrono microseconds -> pkr seconds
    auto chrono_mins = std::chrono::minutes(1);

    auto pkr_ms = pkr::units::unit_cast<pkr::units::millisecond_t>(chrono_mins);
    ASSERT_DOUBLE_EQ(pkr_ms.value(), 60000.0); // 1 minute = 60000 milliseconds

    auto chrono_us = pkr::units::unit_cast<std::chrono::microseconds>(pkr_ms);
    ASSERT_EQ(chrono_us.count(), 60000000); // 60000 ms = 60000000 microseconds

    auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(chrono_us);
    ASSERT_DOUBLE_EQ(pkr_secs.value(), 60.0); // 60000000 microseconds = 60 seconds
}

// ============================================================================
// Round-trip Conversion Tests
// ============================================================================

TEST_F(ChronoCastTest, round_trip_seconds)
{
    auto original_chrono = std::chrono::seconds(42);

    auto pkr_unit = pkr::units::unit_cast<pkr::units::second_t>(original_chrono);
    auto back_to_chrono = pkr::units::unit_cast<std::chrono::seconds>(pkr_unit);

    ASSERT_EQ(back_to_chrono.count(), original_chrono.count());
}

TEST_F(ChronoCastTest, round_trip_milliseconds)
{
    auto original_chrono = std::chrono::milliseconds(1500);

    auto pkr_unit = pkr::units::unit_cast<pkr::units::millisecond_t>(original_chrono);
    auto back_to_chrono = pkr::units::unit_cast<std::chrono::milliseconds>(pkr_unit);

    ASSERT_EQ(back_to_chrono.count(), original_chrono.count());
}

TEST_F(ChronoCastTest, round_trip_different_units)
{
    // Start with chrono seconds, convert to pkr milliseconds, then back to chrono milliseconds
    auto original_chrono = std::chrono::seconds(5);

    auto pkr_ms = pkr::units::unit_cast<pkr::units::millisecond_t>(original_chrono);
    ASSERT_DOUBLE_EQ(pkr_ms.value(), 5000.0); // 5 seconds = 5000 milliseconds

    auto back_to_chrono_ms = pkr::units::unit_cast<std::chrono::milliseconds>(pkr_ms);
    ASSERT_EQ(back_to_chrono_ms.count(), 5000);
}

// ============================================================================
// Fractional Value Tests
// ============================================================================

TEST_F(ChronoCastTest, fractional_seconds)
{
    auto chrono_secs = std::chrono::duration<double>(3.5);
    auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(chrono_secs);

    ASSERT_DOUBLE_EQ(pkr_secs.value(), 3.5);
}

TEST_F(ChronoCastTest, fractional_pkr_to_chrono)
{
    pkr::units::second_t pkr_secs{2.5};
    auto chrono_ms = pkr::units::unit_cast<std::chrono::milliseconds>(pkr_secs);

    ASSERT_EQ(chrono_ms.count(), 2500); // 2.5 seconds = 2500 milliseconds
}

// ============================================================================
// Constexpr Tests
// ============================================================================

TEST_F(ChronoCastTest, constexpr_chrono_seconds_to_second_t)
{
    constexpr auto chrono_secs = std::chrono::seconds(5);
    constexpr auto pkr_secs = pkr::units::unit_cast<pkr::units::second_t>(chrono_secs);

    static_assert(pkr_secs.value() == 5.0);
    ASSERT_DOUBLE_EQ(pkr_secs.value(), 5.0);
}

TEST_F(ChronoCastTest, constexpr_second_t_to_chrono_seconds)
{
    constexpr pkr::units::second_t pkr_secs{10.0};
    constexpr auto chrono_secs = pkr::units::unit_cast<std::chrono::seconds>(pkr_secs);

    static_assert(chrono_secs.count() == 10);
    ASSERT_EQ(chrono_secs.count(), 10);
}

TEST_F(ChronoCastTest, constexpr_chrono_hours_to_hour_t)
{
    constexpr auto chrono_hours = std::chrono::hours(3);
    constexpr auto pkr_hours = pkr::units::unit_cast<pkr::units::hour_t>(chrono_hours);

    static_assert(pkr_hours.value() == 3.0);
    ASSERT_DOUBLE_EQ(pkr_hours.value(), 3.0);
}

TEST_F(ChronoCastTest, constexpr_hour_t_to_chrono_hours)
{
    constexpr pkr::units::hour_t pkr_hours{2.0};
    constexpr auto chrono_hours = pkr::units::unit_cast<std::chrono::hours>(pkr_hours);

    static_assert(chrono_hours.count() == 2);
    ASSERT_EQ(chrono_hours.count(), 2);
}
