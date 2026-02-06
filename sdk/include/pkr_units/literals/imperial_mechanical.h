#pragma once

#include <pkr_units/units/imperial/mechanical/pressure.h>
#include <pkr_units/units/imperial/mechanical/power.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Imperial mechanical literals
constexpr psi_t<double> operator""_psi(long double value) noexcept
{
    return psi_t<double>{static_cast<double>(value)};
}

constexpr horsepower_t<double> operator""_hp(long double value) noexcept
{
    return horsepower_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
