#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/mass_def.h"

PKR_SI_BEGIN_NAMESPACE
{

// Strong type for kilogram (SI base unit for mass)
// NOTE: Kilogram is the base SI unit, not gram (unlike length where meter is base)
struct kilogram_t final : public details::unit_t<double, std::ratio<1, 1>, details::mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilogram"};
    static constexpr std::string_view symbol{"kg"};
    static constexpr std::wstring_view w_symbol{L"kg"};
    static constexpr std::u8string_view u8_symbol{u8"kg"};
};

// Metric mass prefixes (applied relative to kilogram)
// All mass units are defined relative to kilogram (ratio 1/1) as the base
// NOTE: attogram (10^-21) and femtogram (10^-18) exceed std::ratio limits
// and are omitted. The smallest representable is picogram (10^-12).

struct picogram_t final : public details::unit_t<double, std::pico, details::mass_dimension>
{
    using _base = details::unit_t<double, std::pico, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picogram"};
    static constexpr std::string_view symbol{"pg"};
    static constexpr std::wstring_view w_symbol{L"pg"};
    static constexpr std::u8string_view u8_symbol{u8"pg"};
};

struct nanogram_t final : public details::unit_t<double, std::nano, details::mass_dimension>
{
    using _base = details::unit_t<double, std::nano, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanogram"};
    static constexpr std::string_view symbol{"ng"};
    static constexpr std::wstring_view w_symbol{L"ng"};
    static constexpr std::u8string_view u8_symbol{u8"ng"};
};

struct microgram_t final : public details::unit_t<double, std::micro, details::mass_dimension>
{
    using _base = details::unit_t<double, std::micro, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microgram"};
    static constexpr std::string_view symbol{"ug"};
    static constexpr std::wstring_view w_symbol{L"µg"};
    static constexpr std::u8string_view u8_symbol{u8"µg"};
};

struct milligram_t final : public details::unit_t<double, std::milli, details::mass_dimension>
{
    using _base = details::unit_t<double, std::milli, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milligram"};
    static constexpr std::string_view symbol{"mg"};
    static constexpr std::wstring_view w_symbol{L"mg"};
    static constexpr std::u8string_view u8_symbol{u8"mg"};
};

struct centigram_t final : public details::unit_t<double, std::centi, details::mass_dimension>
{
    using _base = details::unit_t<double, std::centi, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centigram"};
    static constexpr std::string_view symbol{"cg"};
    static constexpr std::wstring_view w_symbol{L"cg"};
    static constexpr std::u8string_view u8_symbol{u8"cg"};
};

struct decigram_t final : public details::unit_t<double, std::deci, details::mass_dimension>
{
    using _base = details::unit_t<double, std::deci, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decigram"};
    static constexpr std::string_view symbol{"dg"};
    static constexpr std::wstring_view w_symbol{L"dg"};
    static constexpr std::u8string_view u8_symbol{u8"dg"};
};

// gram is 1/1000 of kilogram
struct gram_t final : public details::unit_t<double, std::milli, details::mass_dimension>
{
    using _base = details::unit_t<double, std::milli, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram"};
    static constexpr std::string_view symbol{"g"};
    static constexpr std::wstring_view w_symbol{L"g"};
    static constexpr std::u8string_view u8_symbol{u8"g"};
};

struct decagram_t final : public details::unit_t<double, std::deca, details::mass_dimension>
{
    using _base = details::unit_t<double, std::deca, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decagram"};
    static constexpr std::string_view symbol{"dag"};
    static constexpr std::wstring_view w_symbol{L"dag"};
    static constexpr std::u8string_view u8_symbol{u8"dag"};
};

struct hectogram_t final : public details::unit_t<double, std::hecto, details::mass_dimension>
{
    using _base = details::unit_t<double, std::hecto, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectogram"};
    static constexpr std::string_view symbol{"hg"};
    static constexpr std::wstring_view w_symbol{L"hg"};
    static constexpr std::u8string_view u8_symbol{u8"hg"};
};

// Larger mass units
struct megagram_t final : public details::unit_t<double, std::kilo, details::mass_dimension>
{
    using _base = details::unit_t<double, std::kilo, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megagram"};
    static constexpr std::string_view symbol{"Mg"};
    static constexpr std::wstring_view w_symbol{L"Mg"};
    static constexpr std::u8string_view u8_symbol{u8"Mg"};
};

struct gigagram_t final : public details::unit_t<double, std::mega, details::mass_dimension>
{
    using _base = details::unit_t<double, std::mega, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigagram"};
    static constexpr std::string_view symbol{"Gg"};
    static constexpr std::wstring_view w_symbol{L"Gg"};
    static constexpr std::u8string_view u8_symbol{u8"Gg"};
};

struct teragram_t final : public details::unit_t<double, std::giga, details::mass_dimension>
{
    using _base = details::unit_t<double, std::giga, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"teragram"};
    static constexpr std::string_view symbol{"Tg"};
    static constexpr std::wstring_view w_symbol{L"Tg"};
    static constexpr std::u8string_view u8_symbol{u8"Tg"};
};

struct petagram_t final : public details::unit_t<double, std::tera, details::mass_dimension>
{
    using _base = details::unit_t<double, std::tera, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"petagram"};
    static constexpr std::string_view symbol{"Pg"};
    static constexpr std::wstring_view w_symbol{L"Pg"};
    static constexpr std::u8string_view u8_symbol{u8"Pg"};
};

struct exagram_t final : public details::unit_t<double, std::peta, details::mass_dimension>
{
    using _base = details::unit_t<double, std::peta, details::mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"exagram"};
    static constexpr std::string_view symbol{"Eg"};
    static constexpr std::wstring_view w_symbol{L"Eg"};
    static constexpr std::u8string_view u8_symbol{u8"Eg"};
};

// Common aliases
using metric_ton = megagram_t;  // 1 metric ton = 1,000 kg (same as megagram)

PKR_SI_NAMESPACE_END









