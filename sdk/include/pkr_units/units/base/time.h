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
    [[maybe_unused]] static constexpr std::string_view name{"second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"s"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"s"};
};

// Metric time prefixes (strong types)
struct attosecond_t final : public details::unit_t<double, std::atto, time_dimension>
{
    using _base = details::unit_t<double, std::atto, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"attosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"as"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"as"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"as"};
};

struct femtosecond_t final : public details::unit_t<double, std::femto, time_dimension>
{
    using _base = details::unit_t<double, std::femto, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"femtosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fs"};
};

struct picosecond_t final : public details::unit_t<double, std::pico, time_dimension>
{
    using _base = details::unit_t<double, std::pico, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ps"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ps"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ps"};
};

struct nanosecond_t final : public details::unit_t<double, std::nano, time_dimension>
{
    using _base = details::unit_t<double, std::nano, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ns"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ns"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ns"};
};

struct microsecond_t final : public details::unit_t<double, std::micro, time_dimension>
{
    using _base = details::unit_t<double, std::micro, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microsecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"us"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5s"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5s"};
};

struct millisecond_t final : public details::unit_t<double, std::milli, time_dimension>
{
    using _base = details::unit_t<double, std::milli, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millisecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ms"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ms"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ms"};
};

struct centisecond_t final : public details::unit_t<double, std::centi, time_dimension>
{
    using _base = details::unit_t<double, std::centi, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centisecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cs"};
};

struct decisecond_t final : public details::unit_t<double, std::deci, time_dimension>
{
    using _base = details::unit_t<double, std::deci, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decisecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ds"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ds"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ds"};
};

struct decasecond_t final : public details::unit_t<double, std::deca, time_dimension>
{
    using _base = details::unit_t<double, std::deca, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"das"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"das"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"das"};
};

struct hectosecond_t final : public details::unit_t<double, std::hecto, time_dimension>
{
    using _base = details::unit_t<double, std::hecto, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hs"};
};

struct kilosecond_t final : public details::unit_t<double, std::kilo, time_dimension>
{
    using _base = details::unit_t<double, std::kilo, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ks"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ks"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ks"};
};

struct megasecond_t final : public details::unit_t<double, std::mega, time_dimension>
{
    using _base = details::unit_t<double, std::mega, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ms"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ms"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ms"};
};

struct gigasecond_t final : public details::unit_t<double, std::giga, time_dimension>
{
    using _base = details::unit_t<double, std::giga, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gs"};
};

struct terasecond_t final : public details::unit_t<double, std::tera, time_dimension>
{
    using _base = details::unit_t<double, std::tera, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"terasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ts"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ts"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ts"};
};

struct petasecond_t final : public details::unit_t<double, std::peta, time_dimension>
{
    using _base = details::unit_t<double, std::peta, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"petasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ps"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ps"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ps"};
};

struct exasecond_t final : public details::unit_t<double, std::exa, time_dimension>
{
    using _base = details::unit_t<double, std::exa, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"exasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Es"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Es"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Es"};
};

struct minute_t final : public details::unit_t<double, std::ratio<60, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<60, 1>, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"minute"};
    [[maybe_unused]] static constexpr std::string_view symbol{"min"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"min"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"min"};
};

struct hour_t final : public details::unit_t<double, std::ratio<3600, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<3600, 1>, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hour"};
    [[maybe_unused]] static constexpr std::string_view symbol{"h"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"h"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"h"};
};

struct day_t final : public details::unit_t<double, std::ratio<86400, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<86400, 1>, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"day"};
    [[maybe_unused]] static constexpr std::string_view symbol{"d"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"d"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"d"};
};

struct week_t final : public details::unit_t<double, std::ratio<604800, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<604800, 1>, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"week"};
    [[maybe_unused]] static constexpr std::string_view symbol{"wk"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"wk"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"wk"};
};

// Month and year use the Julian year: 365.25 days.
struct month_t final : public details::unit_t<double, std::ratio<2629800, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<2629800, 1>, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"month"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mo"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mo"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mo"};
};

struct year_t final : public details::unit_t<double, std::ratio<31557600, 1>, time_dimension>
{
    using _base = details::unit_t<double, std::ratio<31557600, 1>, time_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"year"};
    [[maybe_unused]] static constexpr std::string_view symbol{"yr"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"yr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"yr"};
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
