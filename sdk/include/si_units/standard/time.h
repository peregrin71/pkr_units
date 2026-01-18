#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/time_def.h"

PKR_SI_BEGIN_NAMESPACE
{

// Strong type for second (SI base unit)
struct second_t final : public details::unit_t<double, std::ratio<1, 1>, details::time_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"second"};
    static constexpr std::string_view symbol{"s"};
    static constexpr std::wstring_view w_symbol{L"s"};
    static constexpr std::u8string_view u8_symbol{u8"s"};
};

// Metric time prefixes (strong types)
struct attosecond_t final : public details::unit_t<double, std::atto, details::time_dimension>
{
    using _base = details::unit_t<double, std::atto, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attosecond"};
    static constexpr std::string_view symbol{"as"};
    static constexpr std::wstring_view w_symbol{L"as"};
    static constexpr std::u8string_view u8_symbol{u8"as"};
};

struct femtosecond_t final : public details::unit_t<double, std::femto, details::time_dimension>
{
    using _base = details::unit_t<double, std::femto, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtosecond"};
    static constexpr std::string_view symbol{"fs"};
    static constexpr std::wstring_view w_symbol{L"fs"};
    static constexpr std::u8string_view u8_symbol{u8"fs"};
};

struct picosecond_t final : public details::unit_t<double, std::pico, details::time_dimension>
{
    using _base = details::unit_t<double, std::pico, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picosecond"};
    static constexpr std::string_view symbol{"ps"};
    static constexpr std::wstring_view w_symbol{L"ps"};
    static constexpr std::u8string_view u8_symbol{u8"ps"};
};

struct nanosecond_t final : public details::unit_t<double, std::nano, details::time_dimension>
{
    using _base = details::unit_t<double, std::nano, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanosecond"};
    static constexpr std::string_view symbol{"ns"};
    static constexpr std::wstring_view w_symbol{L"ns"};
    static constexpr std::u8string_view u8_symbol{u8"ns"};
};

struct microsecond_t final : public details::unit_t<double, std::micro, details::time_dimension>
{
    using _base = details::unit_t<double, std::micro, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microsecond"};
    static constexpr std::string_view symbol{"us"};
    static constexpr std::wstring_view w_symbol{L"µs"};
    static constexpr std::u8string_view u8_symbol{u8"µs"};
};

struct millisecond_t final : public details::unit_t<double, std::milli, details::time_dimension>
{
    using _base = details::unit_t<double, std::milli, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millisecond"};
    static constexpr std::string_view symbol{"ms"};
    static constexpr std::wstring_view w_symbol{L"ms"};
    static constexpr std::u8string_view u8_symbol{u8"ms"};
};

struct centisecond_t final : public details::unit_t<double, std::centi, details::time_dimension>
{
    using _base = details::unit_t<double, std::centi, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centisecond"};
    static constexpr std::string_view symbol{"cs"};
    static constexpr std::wstring_view w_symbol{L"cs"};
    static constexpr std::u8string_view u8_symbol{u8"cs"};
};

struct decisecond_t final : public details::unit_t<double, std::deci, details::time_dimension>
{
    using _base = details::unit_t<double, std::deci, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decisecond"};
    static constexpr std::string_view symbol{"ds"};
    static constexpr std::wstring_view w_symbol{L"ds"};
    static constexpr std::u8string_view u8_symbol{u8"ds"};
};

struct decasecond_t final : public details::unit_t<double, std::deca, details::time_dimension>
{
    using _base = details::unit_t<double, std::deca, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decasecond"};
    static constexpr std::string_view symbol{"das"};
    static constexpr std::wstring_view w_symbol{L"das"};
    static constexpr std::u8string_view u8_symbol{u8"das"};
};

struct hectosecond_t final : public details::unit_t<double, std::hecto, details::time_dimension>
{
    using _base = details::unit_t<double, std::hecto, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectosecond"};
    static constexpr std::string_view symbol{"hs"};
    static constexpr std::wstring_view w_symbol{L"hs"};
    static constexpr std::u8string_view u8_symbol{u8"hs"};
};

struct kilosecond_t final : public details::unit_t<double, std::kilo, details::time_dimension>
{
    using _base = details::unit_t<double, std::kilo, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilosecond"};
    static constexpr std::string_view symbol{"ks"};
    static constexpr std::wstring_view w_symbol{L"ks"};
    static constexpr std::u8string_view u8_symbol{u8"ks"};
};

struct megasecond_t final : public details::unit_t<double, std::mega, details::time_dimension>
{
    using _base = details::unit_t<double, std::mega, details::time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megasecond"};
    static constexpr std::string_view symbol{"Ms"};
    static constexpr std::wstring_view w_symbol{L"Ms"};
    static constexpr std::u8string_view u8_symbol{u8"Ms"};
};

PKR_SI_NAMESPACE_END








