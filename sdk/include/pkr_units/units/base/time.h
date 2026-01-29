#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/time_decl.h>

namespace PKR_UNITS_NAMESPACE
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
struct attosecond_t final : public details::unit_t<double, std::atto, time_dimension>
{
    using _base = details::unit_t<double, std::atto, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attosecond"};
    static constexpr std::string_view symbol{"as"};
    static constexpr std::wstring_view w_symbol{L"as"};
    static constexpr std::u8string_view u8_symbol{u8"as"};
};

struct femtosecond_t final : public details::unit_t<double, std::femto, time_dimension>
{
    using _base = details::unit_t<double, std::femto, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtosecond"};
    static constexpr std::string_view symbol{"fs"};
    static constexpr std::wstring_view w_symbol{L"fs"};
    static constexpr std::u8string_view u8_symbol{u8"fs"};
};

struct picosecond_t final : public details::unit_t<double, std::pico, time_dimension>
{
    using _base = details::unit_t<double, std::pico, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picosecond"};
    static constexpr std::string_view symbol{"ps"};
    static constexpr std::wstring_view w_symbol{L"ps"};
    static constexpr std::u8string_view u8_symbol{u8"ps"};
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

struct microsecond_t final : public details::unit_t<double, std::micro, time_dimension>
{
    using _base = details::unit_t<double, std::micro, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microsecond"};
    static constexpr std::string_view symbol{"us"};
    static constexpr std::wstring_view w_symbol{L"\u00b5s"};
    static constexpr std::u8string_view u8_symbol{u8"\u00b5s"};
};

struct millisecond_t final : public details::unit_t<double, std::milli, time_dimension>
{
    using _base = details::unit_t<double, std::milli, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millisecond"};
    static constexpr std::string_view symbol{"ms"};
    static constexpr std::wstring_view w_symbol{L"ms"};
    static constexpr std::u8string_view u8_symbol{u8"ms"};
};

struct centisecond_t final : public details::unit_t<double, std::centi, time_dimension>
{
    using _base = details::unit_t<double, std::centi, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centisecond"};
    static constexpr std::string_view symbol{"cs"};
    static constexpr std::wstring_view w_symbol{L"cs"};
    static constexpr std::u8string_view u8_symbol{u8"cs"};
};

struct decisecond_t final : public details::unit_t<double, std::deci, time_dimension>
{
    using _base = details::unit_t<double, std::deci, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decisecond"};
    static constexpr std::string_view symbol{"ds"};
    static constexpr std::wstring_view w_symbol{L"ds"};
    static constexpr std::u8string_view u8_symbol{u8"ds"};
};

struct decasecond_t final : public details::unit_t<double, std::deca, time_dimension>
{
    using _base = details::unit_t<double, std::deca, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decasecond"};
    static constexpr std::string_view symbol{"das"};
    static constexpr std::wstring_view w_symbol{L"das"};
    static constexpr std::u8string_view u8_symbol{u8"das"};
};

struct hectosecond_t final : public details::unit_t<double, std::hecto, time_dimension>
{
    using _base = details::unit_t<double, std::hecto, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectosecond"};
    static constexpr std::string_view symbol{"hs"};
    static constexpr std::wstring_view w_symbol{L"hs"};
    static constexpr std::u8string_view u8_symbol{u8"hs"};
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

struct megasecond_t final : public details::unit_t<double, std::mega, time_dimension>
{
    using _base = details::unit_t<double, std::mega, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megasecond"};
    static constexpr std::string_view symbol{"Ms"};
    static constexpr std::wstring_view w_symbol{L"Ms"};
    static constexpr std::u8string_view u8_symbol{u8"Ms"};
};

struct gigasecond_t final : public details::unit_t<double, std::giga, time_dimension>
{
    using _base = details::unit_t<double, std::giga, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigasecond"};
    static constexpr std::string_view symbol{"Gs"};
    static constexpr std::wstring_view w_symbol{L"Gs"};
    static constexpr std::u8string_view u8_symbol{u8"Gs"};
};

struct terasecond_t final : public details::unit_t<double, std::tera, time_dimension>
{
    using _base = details::unit_t<double, std::tera, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"terasecond"};
    static constexpr std::string_view symbol{"Ts"};
    static constexpr std::wstring_view w_symbol{L"Ts"};
    static constexpr std::u8string_view u8_symbol{u8"Ts"};
};

struct petasecond_t final : public details::unit_t<double, std::peta, time_dimension>
{
    using _base = details::unit_t<double, std::peta, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"petasecond"};
    static constexpr std::string_view symbol{"Ps"};
    static constexpr std::wstring_view w_symbol{L"Ps"};
    static constexpr std::u8string_view u8_symbol{u8"Ps"};
};

struct exasecond_t final : public details::unit_t<double, std::exa, time_dimension>
{
    using _base = details::unit_t<double, std::exa, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"exasecond"};
    static constexpr std::string_view symbol{"Es"};
    static constexpr std::wstring_view w_symbol{L"Es"};
    static constexpr std::u8string_view u8_symbol{u8"Es"};
};

struct minute_t final : public details::unit_t<double, std::ratio<60, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<60, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"minute"};
    static constexpr std::string_view symbol{"min"};
    static constexpr std::wstring_view w_symbol{L"min"};
    static constexpr std::u8string_view u8_symbol{u8"min"};
};

struct hour_t final : public details::unit_t<double, std::ratio<3600, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hour"};
    static constexpr std::string_view symbol{"h"};
    static constexpr std::wstring_view w_symbol{L"h"};
    static constexpr std::u8string_view u8_symbol{u8"h"};
};

struct day_t final : public details::unit_t<double, std::ratio<86400, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<86400, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"day"};
    static constexpr std::string_view symbol{"d"};
    static constexpr std::wstring_view w_symbol{L"d"};
    static constexpr std::u8string_view u8_symbol{u8"d"};
};

struct week_t final : public details::unit_t<double, std::ratio<604800, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<604800, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"week"};
    static constexpr std::string_view symbol{"wk"};
    static constexpr std::wstring_view w_symbol{L"wk"};
    static constexpr std::u8string_view u8_symbol{u8"wk"};
};

// Month and year use the Julian year: 365.25 days.
struct month_t final : public details::unit_t<double, std::ratio<2629800, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<2629800, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"month"};
    static constexpr std::string_view symbol{"mo"};
    static constexpr std::wstring_view w_symbol{L"mo"};
    static constexpr std::u8string_view u8_symbol{u8"mo"};
};

struct year_t final : public details::unit_t<double, std::ratio<31557600, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<31557600, 1>, time_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"year"};
    static constexpr std::string_view symbol{"yr"};
    static constexpr std::wstring_view w_symbol{L"yr"};
    static constexpr std::u8string_view u8_symbol{u8"yr"};
};

// ============================================================================
// Most derived unit type specializations for time units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, time_dimension>
{
    using type = second_t;
};

template <>
struct details::derived_unit_type_t<double, std::atto, time_dimension>
{
    using type = attosecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::femto, time_dimension>
{
    using type = femtosecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::pico, time_dimension>
{
    using type = picosecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, time_dimension>
{
    using type = nanosecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, time_dimension>
{
    using type = microsecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, time_dimension>
{
    using type = millisecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::centi, time_dimension>
{
    using type = centisecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::deci, time_dimension>
{
    using type = decisecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::deca, time_dimension>
{
    using type = decasecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::hecto, time_dimension>
{
    using type = hectosecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, time_dimension>
{
    using type = kilosecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::mega, time_dimension>
{
    using type = megasecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::giga, time_dimension>
{
    using type = gigasecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::tera, time_dimension>
{
    using type = terasecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::peta, time_dimension>
{
    using type = petasecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::exa, time_dimension>
{
    using type = exasecond_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<60, 1>, time_dimension>
{
    using type = minute_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<3600, 1>, time_dimension>
{
    using type = hour_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<86400, 1>, time_dimension>
{
    using type = day_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<604800, 1>, time_dimension>
{
    using type = week_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<2629800, 1>, time_dimension>
{
    using type = month_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<31557600, 1>, time_dimension>
{
    using type = year_t;
};

} // namespace PKR_UNITS_NAMESPACE
