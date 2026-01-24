#pragma once

#include "mass.h"
#include "../../namespace_config.h"

namespace si::si_literals
{
    // Metric mass prefix literals
    constexpr si::mass<double, std::ratio<1, 1000000000000000000>> operator"" _ag(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 1000000000000000000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 1000000000000000>> operator"" _fg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 1000000000000000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 1000000000000>> operator"" _pg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 1000000000000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 1000000000>> operator"" _ng(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 1000000000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 1000000>> operator"" _ug(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 1000000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 1000000>> operator"" _mg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 1000000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 100000>> operator"" _cg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 100000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 10000>> operator"" _dg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 10000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 1000>> operator"" _g(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 1000>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 100>> operator"" _dag(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 100>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1, 10>> operator"" _hg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1, 10>>(static_cast<double>(value});
    }

    constexpr si::kilogram operator"" _kg(long double value) noexcept
    {
        return si::kilogram{static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1000, 1>> operator"" _Mg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1000, 1>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1000000, 1>> operator"" _Gg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1000000, 1>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1000000000, 1>> operator"" _Tg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1000000000, 1>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1000000000000, 1>> operator"" _Pg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1000000000000, 1>>(static_cast<double>(value});
    }

    constexpr si::mass<double, std::ratio<1000000000000000, 1>> operator"" _Eg(long double value) noexcept
    {
        return si::mass<double, std::ratio<1000000000000000, 1>>(static_cast<double>(value});
    }

    // Common metric mass units
    constexpr si::metric_ton operator"" _t(long double value) noexcept
    {
        return si::metric_ton{static_cast<double>(value});
    }

    // Imperial mass literals
    constexpr si::grain operator"" _gr(long double value) noexcept
    {
        return si::grain{static_cast<double>(value});
    }

    constexpr si::ounce operator"" _oz(long double value) noexcept
    {
        return si::ounce{static_cast<double>(value});
    }

    constexpr si::pound operator"" _lb(long double value) noexcept
    {
        return si::pound{static_cast<double>(value});
    }

    constexpr si::stone operator"" _st(long double value) noexcept
    {
        return si::stone{static_cast<double>(value});
    }

    constexpr si::us_ton operator"" _short_ton(long double value) noexcept
    {
        return si::us_ton{static_cast<double>(value});
    }

    constexpr si::long_ton operator"" _long_ton(long double value) noexcept
    {
        return si::long_ton{static_cast<double>(value});
    }

}  // namespace PKR_UNITS_NAMESPACE::si_literals
















