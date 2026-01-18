#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/unit.h"
#include "../impl/common/time_def.h"

PKR_UNITS_BEGIN_NAMESPACE
{

// Strong type for second (SI base unit)
struct second_t final : public details::unit_t<double, std::ratio<1, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"second"};
    static constexpr std::string_view symbol{"s"};
    static constexpr std::wstring_view w_symbol{L"s"};
    static constexpr std::u8string_view u8_symbol{u8"s"};
};

// Metric time prefixes (strong types)
struct millisecond_t final : public details::unit_t<double, std::milli, time_dimension>
{
    using _base = details::unit_t<double, std::milli, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millisecond"};
    static constexpr std::string_view symbol{"ms"};
    static constexpr std::wstring_view w_symbol{L"ms"};
    static constexpr std::u8string_view u8_symbol{u8"ms"};
};

struct microsecond_t final : public details::unit_t<double, std::micro, time_dimension>
{
    using _base = details::unit_t<double, std::micro, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microsecond"};
    static constexpr std::string_view symbol{"us"};
    static constexpr std::wstring_view w_symbol{L"µs"};
    static constexpr std::u8string_view u8_symbol{u8"µs"};
};

struct nanosecond_t final : public details::unit_t<double, std::nano, time_dimension>
{
    using _base = details::unit_t<double, std::nano, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanosecond"};
    static constexpr std::string_view symbol{"ns"};
    static constexpr std::wstring_view w_symbol{L"ns"};
    static constexpr std::u8string_view u8_symbol{u8"ns"};
};

struct kilosecond_t final : public details::unit_t<double, std::kilo, time_dimension>
{
    using _base = details::unit_t<double, std::kilo, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilosecond"};
    static constexpr std::string_view symbol{"ks"};
    static constexpr std::wstring_view w_symbol{L"ks"};
    static constexpr std::u8string_view u8_symbol{u8"ks"};
};

}  // namespace PKR_UNITS_NAMESPACE