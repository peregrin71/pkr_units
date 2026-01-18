#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Time quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using time = unit_t<type_t, ratio_t, time_dimension>;

// Strong type for second (SI base unit)
struct second final : public unit_t<double, std::ratio<1, 1>, time_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"second"};
    static constexpr std::string_view symbol{"s"};
    static constexpr std::wstring_view w_symbol{L"s"};
    static constexpr std::u8string_view u8_symbol{u8"s"};
};

// Metric time prefixes (strong types)
struct attosecond final : public unit_t<double, std::atto, time_dimension>
{
    using _base = unit_t<double, std::atto, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attosecond"};
    static constexpr std::string_view symbol{"as"};
    static constexpr std::wstring_view w_symbol{L"as"};
    static constexpr std::u8string_view u8_symbol{u8"as"};
};

struct femtosecond final : public unit_t<double, std::femto, time_dimension>
{
    using _base = unit_t<double, std::femto, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtosecond"};
    static constexpr std::string_view symbol{"fs"};
    static constexpr std::wstring_view w_symbol{L"fs"};
    static constexpr std::u8string_view u8_symbol{u8"fs"};
};

struct picosecond final : public unit_t<double, std::pico, time_dimension>
{
    using _base = unit_t<double, std::pico, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picosecond"};
    static constexpr std::string_view symbol{"ps"};
    static constexpr std::wstring_view w_symbol{L"ps"};
    static constexpr std::u8string_view u8_symbol{u8"ps"};
};

struct nanosecond final : public unit_t<double, std::nano, time_dimension>
{
    using _base = unit_t<double, std::nano, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanosecond"};
    static constexpr std::string_view symbol{"ns"};
    static constexpr std::wstring_view w_symbol{L"ns"};
    static constexpr std::u8string_view u8_symbol{u8"ns"};
};

struct microsecond final : public unit_t<double, std::micro, time_dimension>
{
    using _base = unit_t<double, std::micro, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microsecond"};
    static constexpr std::string_view symbol{"us"};
    static constexpr std::wstring_view w_symbol{L"µs"};
    static constexpr std::u8string_view u8_symbol{u8"µs"};
};

struct millisecond final : public unit_t<double, std::milli, time_dimension>
{
    using _base = unit_t<double, std::milli, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millisecond"};
    static constexpr std::string_view symbol{"ms"};
    static constexpr std::wstring_view w_symbol{L"ms"};
    static constexpr std::u8string_view u8_symbol{u8"ms"};
};

struct centisecond final : public unit_t<double, std::centi, time_dimension>
{
    using _base = unit_t<double, std::centi, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centisecond"};
    static constexpr std::string_view symbol{"cs"};
    static constexpr std::wstring_view w_symbol{L"cs"};
    static constexpr std::u8string_view u8_symbol{u8"cs"};
};

struct decisecond final : public unit_t<double, std::deci, time_dimension>
{
    using _base = unit_t<double, std::deci, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decisecond"};
    static constexpr std::string_view symbol{"ds"};
    static constexpr std::wstring_view w_symbol{L"ds"};
    static constexpr std::u8string_view u8_symbol{u8"ds"};
};

struct decasecond final : public unit_t<double, std::deca, time_dimension>
{
    using _base = unit_t<double, std::deca, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decasecond"};
    static constexpr std::string_view symbol{"das"};
    static constexpr std::wstring_view w_symbol{L"das"};
    static constexpr std::u8string_view u8_symbol{u8"das"};
};

struct hectosecond final : public unit_t<double, std::hecto, time_dimension>
{
    using _base = unit_t<double, std::hecto, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectosecond"};
    static constexpr std::string_view symbol{"hs"};
    static constexpr std::wstring_view w_symbol{L"hs"};
    static constexpr std::u8string_view u8_symbol{u8"hs"};
};

struct kilosecond final : public unit_t<double, std::kilo, time_dimension>
{
    using _base = unit_t<double, std::kilo, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilosecond"};
    static constexpr std::string_view symbol{"ks"};
    static constexpr std::wstring_view w_symbol{L"ks"};
    static constexpr std::u8string_view u8_symbol{u8"ks"};
};

struct megasecond final : public unit_t<double, std::mega, time_dimension>
{
    using _base = unit_t<double, std::mega, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megasecond"};
    static constexpr std::string_view symbol{"Ms"};
    static constexpr std::wstring_view w_symbol{L"Ms"};
    static constexpr std::u8string_view u8_symbol{u8"Ms"};
};

PKR_SI_NAMESPACE_END








