#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/time_decl.h>
namespace PKR_UNITS_NAMESPACE
{
// Strong type for second (SI base unit)
template <is_unit_value_type_c T>
struct second_t final : public details::unit_t<T, std::ratio<1, 1>, time_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"second"};
    [[maybe_unused]] static constexpr std::string_view symbol{"s"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"s"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"s"};
};

template <is_unit_value_type_c T>
second_t(T) -> second_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
second_t(const U&) -> second_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct attosecond_t final : public details::unit_t<T, std::atto, time_dimension>
{
    using _base = details::unit_t<T, std::atto, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"attosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"as"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"as"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"as"};
};

template <is_unit_value_type_c T>
attosecond_t(T) -> attosecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
attosecond_t(const U&) -> attosecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct femtosecond_t final : public details::unit_t<T, std::femto, time_dimension>
{
    using _base = details::unit_t<T, std::femto, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"femtosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fs"};
};

template <is_unit_value_type_c T>
femtosecond_t(T) -> femtosecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
femtosecond_t(const U&) -> femtosecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct picosecond_t final : public details::unit_t<T, std::pico, time_dimension>
{
    using _base = details::unit_t<T, std::pico, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ps"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ps"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ps"};
};

template <is_unit_value_type_c T>
picosecond_t(T) -> picosecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
picosecond_t(const U&) -> picosecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct nanosecond_t final : public details::unit_t<T, std::nano, time_dimension>
{
    using _base = details::unit_t<T, std::nano, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ns"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ns"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ns"};
};

template <is_unit_value_type_c T>
nanosecond_t(T) -> nanosecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
nanosecond_t(const U&) -> nanosecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct microsecond_t final : public details::unit_t<T, std::micro, time_dimension>
{
    using _base = details::unit_t<T, std::micro, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microsecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"us"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5s"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5s"};
};

template <is_unit_value_type_c T>
microsecond_t(T) -> microsecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
microsecond_t(const U&) -> microsecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct millisecond_t final : public details::unit_t<T, std::milli, time_dimension>
{
    using _base = details::unit_t<T, std::milli, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millisecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ms"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ms"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ms"};
};

template <is_unit_value_type_c T>
millisecond_t(T) -> millisecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
millisecond_t(const U&) -> millisecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct centisecond_t final : public details::unit_t<T, std::centi, time_dimension>
{
    using _base = details::unit_t<T, std::centi, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"centisecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cs"};
};

template <is_unit_value_type_c T>
centisecond_t(T) -> centisecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
centisecond_t(const U&) -> centisecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct decisecond_t final : public details::unit_t<T, std::deci, time_dimension>
{
    using _base = details::unit_t<T, std::deci, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decisecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ds"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ds"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ds"};
};

template <is_unit_value_type_c T>
decisecond_t(T) -> decisecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
decisecond_t(const U&) -> decisecond_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct decasecond_t final : public details::unit_t<T, std::deca, time_dimension>
{
    using _base = details::unit_t<T, std::deca, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"decasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"das"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"das"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"das"};
};

template <is_unit_value_type_c T>
decasecond_t(T) -> decasecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
decasecond_t(const U&) -> decasecond_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct hectosecond_t final : public details::unit_t<T, std::hecto, time_dimension>
{
    using _base = details::unit_t<T, std::hecto, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hectosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hs"};
};

template <is_unit_value_type_c T>
hectosecond_t(T) -> hectosecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
hectosecond_t(const U&) -> hectosecond_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilosecond_t final : public details::unit_t<T, std::kilo, time_dimension>
{
    using _base = details::unit_t<T, std::kilo, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilosecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ks"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ks"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ks"};
};

template <is_unit_value_type_c T>
kilosecond_t(T) -> kilosecond_t<T>; 

template <is_unit_value_type_c T>
struct megasecond_t final : public details::unit_t<T, std::mega, time_dimension>
{
    using _base = details::unit_t<T, std::mega, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"megasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ms"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ms"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ms"};
};

template <is_unit_value_type_c T>
megasecond_t(T) -> megasecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
megasecond_t(const U&) -> megasecond_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct gigasecond_t final : public details::unit_t<T, std::giga, time_dimension>
{
    using _base = details::unit_t<T, std::giga, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"gigasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gs"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gs"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gs"};
};

template <is_unit_value_type_c T>
gigasecond_t(T) -> gigasecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
gigasecond_t(const U&) -> gigasecond_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct terasecond_t final : public details::unit_t<T, std::tera, time_dimension>
{
    using _base = details::unit_t<T, std::tera, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"terasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ts"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ts"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ts"};
};

template <is_unit_value_type_c T>
terasecond_t(T) -> terasecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
terasecond_t(const U&) -> terasecond_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct petasecond_t final : public details::unit_t<T, std::peta, time_dimension>
{
    using _base = details::unit_t<T, std::peta, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"petasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Ps"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ps"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ps"};
};

template <is_unit_value_type_c T>
petasecond_t(T) -> petasecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
petasecond_t(const U&) -> petasecond_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct exasecond_t final : public details::unit_t<T, std::exa, time_dimension>
{
    using _base = details::unit_t<T, std::exa, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"exasecond"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Es"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Es"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Es"};
};

template <is_unit_value_type_c T>
exasecond_t(T) -> exasecond_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
exasecond_t(const U&) -> exasecond_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct minute_t final : public details::unit_t<T, std::ratio<60, 1>, time_dimension>
{
    using _base = details::unit_t<T, std::ratio<60, 1>, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"minute"};
    [[maybe_unused]] static constexpr std::string_view symbol{"min"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"min"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"min"};
};

template <is_unit_value_type_c T>
minute_t(T) -> minute_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
minute_t(const U&) -> minute_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct hour_t final : public details::unit_t<T, std::ratio<3600, 1>, time_dimension>
{
    using _base = details::unit_t<T, std::ratio<3600, 1>, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hour"};
    [[maybe_unused]] static constexpr std::string_view symbol{"h"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"h"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"h"};
};

template <is_unit_value_type_c T>
hour_t(T) -> hour_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
hour_t(const U&) -> hour_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct day_t final : public details::unit_t<T, std::ratio<86400, 1>, time_dimension>
{
    using _base = details::unit_t<T, std::ratio<86400, 1>, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"day"};
    [[maybe_unused]] static constexpr std::string_view symbol{"d"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"d"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"d"};
};

template <is_unit_value_type_c T>
day_t(T) -> day_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
day_t(const U&) -> day_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct week_t final : public details::unit_t<T, std::ratio<604800, 1>, time_dimension>
{
    using _base = details::unit_t<T, std::ratio<604800, 1>, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"week"};
    [[maybe_unused]] static constexpr std::string_view symbol{"wk"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"wk"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"wk"};
};

template <is_unit_value_type_c T>
week_t(T) -> week_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
week_t(const U&) -> week_t<typename details::is_pkr_unit<U>::value_type>;

// Month and year use the Julian year: 365.25 days.
template <is_unit_value_type_c T>
struct month_t final : public details::unit_t<T, std::ratio<2629800, 1>, time_dimension>
{
    using _base = details::unit_t<T, std::ratio<2629800, 1>, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"month"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mo"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mo"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mo"};
};

template <is_unit_value_type_c T>
month_t(T) -> month_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == time_dimension)
month_t(const U&) -> month_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct year_t final : public details::unit_t<T, std::ratio<31557600, 1>, time_dimension>
{
    using _base = details::unit_t<T, std::ratio<31557600, 1>, time_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"year"};
    [[maybe_unused]] static constexpr std::string_view symbol{"yr"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"yr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"yr"};
};

template <is_unit_value_type_c T>
year_t(T) -> year_t<T>;

// ============================================================================
// Most derived unit type specializations for time units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, time_dimension>
{
    using type = second_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::atto, time_dimension>
{
    using type = attosecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::femto, time_dimension>
{
    using type = femtosecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::pico, time_dimension>
{
    using type = picosecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::nano, time_dimension>
{
    using type = nanosecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::micro, time_dimension>
{
    using type = microsecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::milli, time_dimension>
{
    using type = millisecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::centi, time_dimension>
{
    using type = centisecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deci, time_dimension>
{
    using type = decisecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::deca, time_dimension>
{
    using type = decasecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::hecto, time_dimension>
{
    using type = hectosecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::kilo, time_dimension>
{
    using type = kilosecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::mega, time_dimension>
{
    using type = megasecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::giga, time_dimension>
{
    using type = gigasecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::tera, time_dimension>
{
    using type = terasecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::peta, time_dimension>
{
    using type = petasecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::exa, time_dimension>
{
    using type = exasecond_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<60, 1>, time_dimension>
{
    using type = minute_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<3600, 1>, time_dimension>
{
    using type = hour_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<86400, 1>, time_dimension>
{
    using type = day_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<604800, 1>, time_dimension>
{
    using type = week_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<2629800, 1>, time_dimension>
{
    using type = month_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<31557600, 1>, time_dimension>
{
    using type = year_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
