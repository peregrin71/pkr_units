#pragma once

#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/units/base/mass.h"
#include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/namespace_config.h"

namespace PKR_UNITS_NAMESPACE
{

namespace literals
{
// Metric mass prefix literals
constexpr picogram_t operator""_pg(long double value) noexcept
{
    return picogram_t{static_cast<double>(value)};
}

constexpr nanogram_t operator""_ng(long double value) noexcept
{
    return nanogram_t{static_cast<double>(value)};
}

constexpr microgram_t operator""_ug(long double value) noexcept
{
    return microgram_t{static_cast<double>(value)};
}

constexpr milligram_t operator""_mg(long double value) noexcept
{
    return milligram_t{static_cast<double>(value)};
}

constexpr centigram_t operator""_cg(long double value) noexcept
{
    return centigram_t{static_cast<double>(value)};
}

constexpr decigram_t operator""_dg(long double value) noexcept
{
    return decigram_t{static_cast<double>(value)};
}

constexpr gram_t operator""_g(long double value) noexcept
{
    return gram_t{static_cast<double>(value)};
}

constexpr decagram_t operator""_dag(long double value) noexcept
{
    return decagram_t{static_cast<double>(value)};
}

constexpr hectogram_t operator""_hg(long double value) noexcept
{
    return hectogram_t{static_cast<double>(value)};
}

constexpr kilogram_t operator""_kg(long double value) noexcept
{
    return kilogram_t{static_cast<double>(value)};
}

constexpr gigagram_t operator""_Gg(long double value) noexcept
{
    return gigagram_t{static_cast<double>(value)};
}

constexpr teragram_t operator""_Tg(long double value) noexcept
{
    return teragram_t{static_cast<double>(value)};
}

constexpr petagram_t operator""_Pg(long double value) noexcept
{
    return petagram_t{static_cast<double>(value)};
}

constexpr exagram_t operator""_Eg(long double value) noexcept
{
    return exagram_t{static_cast<double>(value)};
}

// Common metric mass units
constexpr metric_ton_t operator""_t(long double value) noexcept
{
    return metric_ton_t{static_cast<double>(value)};
}

} // namespace literals

} // namespace PKR_UNITS_NAMESPACE
