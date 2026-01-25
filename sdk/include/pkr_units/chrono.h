#pragma once

/**
 * @file chrono.h
 * @brief Chrono integration for pkr_units
 *
 * This header provides bidirectional conversion between std::chrono durations
 * and pkr_units time types through unit_cast overloads.
 *
 * Usage:
 *   #include <pkr_units/chrono.h>
 *
 *   // Convert chrono to pkr_units
 *   auto chrono_time = std::chrono::seconds{30};
 *   auto pkr_time = unit_cast<second_t>(chrono_time);
 *
 *   // Convert pkr_units to chrono
 *   auto back_to_chrono = unit_cast<std::chrono::milliseconds>(pkr_time);
 */

#include <pkr_units/impl/cast/chrono_cast.h>