#pragma once

#include "../impl/common/length_def.h"
#include "../impl/namespace_config.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Imperial length units
using inch = details::unit_t<double, std::ratio<254, 10000>, length_dimension>;         // 1 inch = 0.0254 meter
using mil = details::unit_t<double, std::ratio<254, 10000000>, length_dimension>;       // 1 mil = 0.0000254 meter
using foot = details::unit_t<double, std::ratio<3048, 10000>, length_dimension>;        // 1 foot = 0.3048 meter
using yard = details::unit_t<double, std::ratio<9144, 10000>, length_dimension>;        // 1 yard = 0.9144 meter
using fathom = details::unit_t<double, std::ratio<18288, 10000>, length_dimension>;     // 1 fathom = 1.8288 meter
using rod = details::unit_t<double, std::ratio<50292, 10000>, length_dimension>;        // 1 rod = 5.0292 meter
using chain = details::unit_t<double, std::ratio<201168, 10000>, length_dimension>;     // 1 chain = 20.1168 meter
using furlong = details::unit_t<double, std::ratio<201168, 1000>, length_dimension>;    // 1 furlong = 201.168 meter
using mile = details::unit_t<double, std::ratio<1609344, 1000>, length_dimension>;      // 1 mile = 1609.344 meter
using nautical_mile = details::unit_t<double, std::ratio<1852, 1>, length_dimension>;   // 1 nautical mile = 1852 meter

} // PKR_UNITS_NAMESPACE


