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
    [[maybe_unused]] static constexpr std::string_view name{"kelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"K"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"K"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"K"};
};

// Metric temperature prefixes (strong types)
struct attokelvin_t final : public details::unit_t<double, std::atto, temperature_dimension>
{
    using _base = details::unit_t<double, std::atto, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"attokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"aK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"aK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"aK"};
};

struct femtokelvin_t final : public details::unit_t<double, std::femto, temperature_dimension>
{
    using _base = details::unit_t<double, std::femto, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"femtokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fK"};
};

struct picokelvin_t final : public details::unit_t<double, std::pico, temperature_dimension>
{
    using _base = details::unit_t<double, std::pico, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pK"};
};

struct nanokelvin_t final : public details::unit_t<double, std::nano, temperature_dimension>
{
    using _base = details::unit_t<double, std::nano, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nK"};
};

struct microkelvin_t final : public details::unit_t<double, std::micro, temperature_dimension>
{
    using _base = details::unit_t<double, std::micro, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microkelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5K"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5K"};
};

struct millikelvin_t final : public details::unit_t<double, std::milli, temperature_dimension>
{
    using _base = details::unit_t<double, std::milli, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millikelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mK"};
};

struct centikelvin_t final : public details::unit_t<double, std::centi, temperature_dimension>
{
    using _base = details::unit_t<double, std::centi, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centikelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cK"};
};

struct decikelvin_t final : public details::unit_t<double, std::deci, temperature_dimension>
{
    using _base = details::unit_t<double, std::deci, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decikelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dK"};
};

struct decakelvin_t final : public details::unit_t<double, std::deca, temperature_dimension>
{
    using _base = details::unit_t<double, std::deca, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"daK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"daK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"daK"};
};

struct hectokelvin_t final : public details::unit_t<double, std::hecto, temperature_dimension>
{
    using _base = details::unit_t<double, std::hecto, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hK"};
};

struct kilokelvin_t final : public details::unit_t<double, std::kilo, temperature_dimension>
{
    using _base = details::unit_t<double, std::kilo, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilokelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kK"};
};

struct megakelvin_t final : public details::unit_t<double, std::mega, temperature_dimension>
{
    using _base = details::unit_t<double, std::mega, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MK"};
};

struct gigakelvin_t final : public details::unit_t<double, std::giga, temperature_dimension>
{
    using _base = details::unit_t<double, std::giga, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GK"};
};

struct terakelvin_t final : public details::unit_t<double, std::tera, temperature_dimension>
{
    using _base = details::unit_t<double, std::tera, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"terakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"TK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"TK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"TK"};
};

struct petakelvin_t final : public details::unit_t<double, std::peta, temperature_dimension>
{
    using _base = details::unit_t<double, std::peta, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"petakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"PK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"PK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"PK"};
};

struct exakelvin_t final : public details::unit_t<double, std::exa, temperature_dimension>
{
    using _base = details::unit_t<double, std::exa, temperature_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"exakelvin"};
    [[maybe_unused]] static constexpr std::string_view symbol{"EK"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"EK"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"EK"};
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
