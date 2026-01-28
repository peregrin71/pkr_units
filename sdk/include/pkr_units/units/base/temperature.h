#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/temperature_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for kelvin (SI base unit)
struct kelvin_t final : public details::unit_t<double, std::ratio<1, 1>, temperature_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kelvin"};
    static constexpr std::string_view symbol{"K"};
    static constexpr std::wstring_view w_symbol{L"K"};
    static constexpr std::u8string_view u8_symbol{u8"K"};
};

// Metric temperature prefixes (strong types)
struct attokelvin_t final : public details::unit_t<double, std::atto, temperature_dimension>
{
    using _base = details::unit_t<double, std::atto, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attokelvin"};
    static constexpr std::string_view symbol{"aK"};
    static constexpr std::wstring_view w_symbol{L"aK"};
    static constexpr std::u8string_view u8_symbol{u8"aK"};
};

struct femtokelvin_t final : public details::unit_t<double, std::femto, temperature_dimension>
{
    using _base = details::unit_t<double, std::femto, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtokelvin"};
    static constexpr std::string_view symbol{"fK"};
    static constexpr std::wstring_view w_symbol{L"fK"};
    static constexpr std::u8string_view u8_symbol{u8"fK"};
};

struct picokelvin_t final : public details::unit_t<double, std::pico, temperature_dimension>
{
    using _base = details::unit_t<double, std::pico, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picokelvin"};
    static constexpr std::string_view symbol{"pK"};
    static constexpr std::wstring_view w_symbol{L"pK"};
    static constexpr std::u8string_view u8_symbol{u8"pK"};
};

struct nanokelvin_t final : public details::unit_t<double, std::nano, temperature_dimension>
{
    using _base = details::unit_t<double, std::nano, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanokelvin"};
    static constexpr std::string_view symbol{"nK"};
    static constexpr std::wstring_view w_symbol{L"nK"};
    static constexpr std::u8string_view u8_symbol{u8"nK"};
};

struct microkelvin_t final : public details::unit_t<double, std::micro, temperature_dimension>
{
    using _base = details::unit_t<double, std::micro, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microkelvin"};
    static constexpr std::string_view symbol{"uK"};
    static constexpr std::wstring_view w_symbol{L"\u00b5K"};
    static constexpr std::u8string_view u8_symbol{u8"\u00b5K"};
};

struct millikelvin_t final : public details::unit_t<double, std::milli, temperature_dimension>
{
    using _base = details::unit_t<double, std::milli, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millikelvin"};
    static constexpr std::string_view symbol{"mK"};
    static constexpr std::wstring_view w_symbol{L"mK"};
    static constexpr std::u8string_view u8_symbol{u8"mK"};
};

struct centikelvin_t final : public details::unit_t<double, std::centi, temperature_dimension>
{
    using _base = details::unit_t<double, std::centi, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centikelvin"};
    static constexpr std::string_view symbol{"cK"};
    static constexpr std::wstring_view w_symbol{L"cK"};
    static constexpr std::u8string_view u8_symbol{u8"cK"};
};

struct decikelvin_t final : public details::unit_t<double, std::deci, temperature_dimension>
{
    using _base = details::unit_t<double, std::deci, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decikelvin"};
    static constexpr std::string_view symbol{"dK"};
    static constexpr std::wstring_view w_symbol{L"dK"};
    static constexpr std::u8string_view u8_symbol{u8"dK"};
};

struct decakelvin_t final : public details::unit_t<double, std::deca, temperature_dimension>
{
    using _base = details::unit_t<double, std::deca, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decakelvin"};
    static constexpr std::string_view symbol{"daK"};
    static constexpr std::wstring_view w_symbol{L"daK"};
    static constexpr std::u8string_view u8_symbol{u8"daK"};
};

struct hectokelvin_t final : public details::unit_t<double, std::hecto, temperature_dimension>
{
    using _base = details::unit_t<double, std::hecto, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectokelvin"};
    static constexpr std::string_view symbol{"hK"};
    static constexpr std::wstring_view w_symbol{L"hK"};
    static constexpr std::u8string_view u8_symbol{u8"hK"};
};

struct kilokelvin_t final : public details::unit_t<double, std::kilo, temperature_dimension>
{
    using _base = details::unit_t<double, std::kilo, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilokelvin"};
    static constexpr std::string_view symbol{"kK"};
    static constexpr std::wstring_view w_symbol{L"kK"};
    static constexpr std::u8string_view u8_symbol{u8"kK"};
};

struct megakelvin_t final : public details::unit_t<double, std::mega, temperature_dimension>
{
    using _base = details::unit_t<double, std::mega, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megakelvin"};
    static constexpr std::string_view symbol{"MK"};
    static constexpr std::wstring_view w_symbol{L"MK"};
    static constexpr std::u8string_view u8_symbol{u8"MK"};
};

struct gigakelvin_t final : public details::unit_t<double, std::giga, temperature_dimension>
{
    using _base = details::unit_t<double, std::giga, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigakelvin"};
    static constexpr std::string_view symbol{"GK"};
    static constexpr std::wstring_view w_symbol{L"GK"};
    static constexpr std::u8string_view u8_symbol{u8"GK"};
};

struct terakelvin_t final : public details::unit_t<double, std::tera, temperature_dimension>
{
    using _base = details::unit_t<double, std::tera, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"terakelvin"};
    static constexpr std::string_view symbol{"TK"};
    static constexpr std::wstring_view w_symbol{L"TK"};
    static constexpr std::u8string_view u8_symbol{u8"TK"};
};

struct petakelvin_t final : public details::unit_t<double, std::peta, temperature_dimension>
{
    using _base = details::unit_t<double, std::peta, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"petakelvin"};
    static constexpr std::string_view symbol{"PK"};
    static constexpr std::wstring_view w_symbol{L"PK"};
    static constexpr std::u8string_view u8_symbol{u8"PK"};
};

struct exakelvin_t final : public details::unit_t<double, std::exa, temperature_dimension>
{
    using _base = details::unit_t<double, std::exa, temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"exakelvin"};
    static constexpr std::string_view symbol{"EK"};
    static constexpr std::wstring_view w_symbol{L"EK"};
    static constexpr std::u8string_view u8_symbol{u8"EK"};
};

// ============================================================================
// Most derived unit type specializations for temperature units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, temperature_dimension>
{
    using type = kelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::atto, temperature_dimension>
{
    using type = attokelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::femto, temperature_dimension>
{
    using type = femtokelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::pico, temperature_dimension>
{
    using type = picokelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, temperature_dimension>
{
    using type = nanokelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, temperature_dimension>
{
    using type = microkelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, temperature_dimension>
{
    using type = millikelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::centi, temperature_dimension>
{
    using type = centikelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::deci, temperature_dimension>
{
    using type = decikelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::deca, temperature_dimension>
{
    using type = decakelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::hecto, temperature_dimension>
{
    using type = hectokelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, temperature_dimension>
{
    using type = kilokelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::mega, temperature_dimension>
{
    using type = megakelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::giga, temperature_dimension>
{
    using type = gigakelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::tera, temperature_dimension>
{
    using type = terakelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::peta, temperature_dimension>
{
    using type = petakelvin_t;
};

template <>
struct details::derived_unit_type_t<double, std::exa, temperature_dimension>
{
    using type = exakelvin_t;
};

} // namespace PKR_UNITS_NAMESPACE
