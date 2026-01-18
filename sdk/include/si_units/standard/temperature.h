#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/temperature_def.h"

PKR_SI_BEGIN_NAMESPACE
{

// Strong type for kelvin (SI base unit)
struct kelvin_t final : public details::unit_t<double, std::ratio<1, 1>, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kelvin"};
    static constexpr std::string_view symbol{"K"};
    static constexpr std::wstring_view w_symbol{L"K"};
    static constexpr std::u8string_view u8_symbol{u8"K"};
};

// Metric temperature prefixes (strong types)
struct attokelvin_t final : public details::unit_t<double, std::atto, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::atto, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attokelvin"};
    static constexpr std::string_view symbol{"aK"};
    static constexpr std::wstring_view w_symbol{L"aK"};
    static constexpr std::u8string_view u8_symbol{u8"aK"};
};

struct femtokelvin_t final : public details::unit_t<double, std::femto, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::femto, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtokelvin"};
    static constexpr std::string_view symbol{"fK"};
    static constexpr std::wstring_view w_symbol{L"fK"};
    static constexpr std::u8string_view u8_symbol{u8"fK"};
};

struct picokelvin_t final : public details::unit_t<double, std::pico, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::pico, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picokelvin"};
    static constexpr std::string_view symbol{"pK"};
    static constexpr std::wstring_view w_symbol{L"pK"};
    static constexpr std::u8string_view u8_symbol{u8"pK"};
};

struct nanokelvin_t final : public details::unit_t<double, std::nano, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::nano, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanokelvin"};
    static constexpr std::string_view symbol{"nK"};
    static constexpr std::wstring_view w_symbol{L"nK"};
    static constexpr std::u8string_view u8_symbol{u8"nK"};
};

struct microkelvin_t final : public details::unit_t<double, std::micro, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::micro, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microkelvin"};
    static constexpr std::string_view symbol{"uK"};
    static constexpr std::wstring_view w_symbol{L"µK"};
    static constexpr std::u8string_view u8_symbol{u8"µK"};
};

struct millikelvin_t final : public details::unit_t<double, std::milli, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::milli, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millikelvin"};
    static constexpr std::string_view symbol{"mK"};
    static constexpr std::wstring_view w_symbol{L"mK"};
    static constexpr std::u8string_view u8_symbol{u8"mK"};
};

struct centikelvin_t final : public details::unit_t<double, std::centi, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::centi, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centikelvin"};
    static constexpr std::string_view symbol{"cK"};
    static constexpr std::wstring_view w_symbol{L"cK"};
    static constexpr std::u8string_view u8_symbol{u8"cK"};
};

struct decikelvin_t final : public details::unit_t<double, std::deci, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::deci, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decikelvin"};
    static constexpr std::string_view symbol{"dK"};
    static constexpr std::wstring_view w_symbol{L"dK"};
    static constexpr std::u8string_view u8_symbol{u8"dK"};
};

struct decakelvin_t final : public details::unit_t<double, std::deca, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::deca, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decakelvin"};
    static constexpr std::string_view symbol{"daK"};
    static constexpr std::wstring_view w_symbol{L"daK"};
    static constexpr std::u8string_view u8_symbol{u8"daK"};
};

struct hectokelvin_t final : public details::unit_t<double, std::hecto, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::hecto, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectokelvin"};
    static constexpr std::string_view symbol{"hK"};
    static constexpr std::wstring_view w_symbol{L"hK"};
    static constexpr std::u8string_view u8_symbol{u8"hK"};
};

struct kilokelvin_t final : public details::unit_t<double, std::kilo, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::kilo, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilokelvin"};
    static constexpr std::string_view symbol{"kK"};
    static constexpr std::wstring_view w_symbol{L"kK"};
    static constexpr std::u8string_view u8_symbol{u8"kK"};
};

struct megakelvin_t final : public details::unit_t<double, std::mega, details::temperature_dimension>
{
    using _base = details::unit_t<double, std::mega, details::temperature_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megakelvin"};
    static constexpr std::string_view symbol{"MK"};
    static constexpr std::wstring_view w_symbol{L"MK"};
    static constexpr std::u8string_view u8_symbol{u8"MK"};
};

PKR_SI_NAMESPACE_END


