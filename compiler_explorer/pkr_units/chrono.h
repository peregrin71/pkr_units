#pragma once

/**
 * @file chrono.h
 * @brief std::chrono conversion overloads for pkr_units time types
 *
 * Usage:
 *   #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/chrono.h"
 *
 *   auto secs = pkr::units::unit_cast<pkr::units::second_t>(std::chrono::seconds(5));
 *   auto chrono_hours = pkr::units::unit_cast<std::chrono::hours>(pkr::units::hour_t{2.0});
 */

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/cast/chrono_cast.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/time.h"
