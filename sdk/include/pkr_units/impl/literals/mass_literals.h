#pragma once

#include <pkr_units/units/base/mass.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric mass prefix literals
constexpr picogram_t<double> operator""_pg(long double value) noexcept
{
    return picogram_t<double>{static_cast<double>(value)};
}

constexpr nanogram_t<double> operator""_ng(long double value) noexcept
{
    return nanogram_t<double>{static_cast<double>(value)};
}

constexpr microgram_t<double> operator""_ug(long double value) noexcept
{
    return microgram_t<double>{static_cast<double>(value)};
}

constexpr milligram_t<double> operator""_mg(long double value) noexcept
{
    return milligram_t<double>{static_cast<double>(value)};
}

constexpr centigram_t<double> operator""_cg(long double value) noexcept
{
    return centigram_t<double>{static_cast<double>(value)};
}

constexpr decigram_t<double> operator""_dg(long double value) noexcept
{
    return decigram_t<double>{static_cast<double>(value)};
}

constexpr gram_t<double> operator""_g(long double value) noexcept
{
    return gram_t<double>{static_cast<double>(value)};
}

constexpr decagram_t<double> operator""_dag(long double value) noexcept
{
    return decagram_t<double>{static_cast<double>(value)};
}

constexpr hectogram_t<double> operator""_hg(long double value) noexcept
{
    return hectogram_t<double>{static_cast<double>(value)};
}

constexpr kilogram_t<double> operator""_kg(long double value) noexcept
{
    return kilogram_t<double>{static_cast<double>(value)};
}

constexpr gigagram_t<double> operator""_Gg(long double value) noexcept
{
    return gigagram_t<double>{static_cast<double>(value)};
}

constexpr teragram_t<double> operator""_Tg(long double value) noexcept
{
    return teragram_t<double>{static_cast<double>(value)};
}

constexpr petagram_t<double> operator""_Pg(long double value) noexcept
{
    return petagram_t<double>{static_cast<double>(value)};
}

constexpr exagram_t<double> operator""_Eg(long double value) noexcept
{
    return exagram_t<double>{static_cast<double>(value)};
}

// Common metric mass units
constexpr metric_ton_t<double> operator""_t(long double value) noexcept
{
    return metric_ton_t<double>{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
