#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Mass quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using mass = unit_t<type_t, ratio_t, mass_dimension>;

// Strong type for kilogram (SI base unit for mass)
// NOTE: Kilogram is the base SI unit, not gram (unlike length where meter is base)
struct kilogram final : public unit_t<double, std::ratio<1, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilogram"};
    static constexpr std::string_view symbol{"kg"};
    static constexpr std::wstring_view w_symbol{L"kg"};
    static constexpr std::u8string_view u8_symbol{u8"kg"};
};

// Metric mass prefixes (applied relative to kilogram)
// All mass units are defined relative to kilogram (ratio 1/1) as the base
struct attogram final : public unit_t<double, std::ratio<1, 1000000000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attogram"};
    static constexpr std::string_view symbol{"ag"};
    static constexpr std::wstring_view w_symbol{L"ag"};
    static constexpr std::u8string_view u8_symbol{u8"ag"};
};

struct femtogram final : public unit_t<double, std::ratio<1, 1000000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtogram"};
    static constexpr std::string_view symbol{"fg"};
    static constexpr std::wstring_view w_symbol{L"fg"};
    static constexpr std::u8string_view u8_symbol{u8"fg"};
};

struct picogram final : public unit_t<double, std::ratio<1, 1000000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picogram"};
    static constexpr std::string_view symbol{"pg"};
    static constexpr std::wstring_view w_symbol{L"pg"};
    static constexpr std::u8string_view u8_symbol{u8"pg"};
};

struct nanogram final : public unit_t<double, std::ratio<1, 1000000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanogram"};
    static constexpr std::string_view symbol{"ng"};
    static constexpr std::wstring_view w_symbol{L"ng"};
    static constexpr std::u8string_view u8_symbol{u8"ng"};
};

struct microgram final : public unit_t<double, std::ratio<1, 1000000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microgram"};
    static constexpr std::string_view symbol{"ug"};
    static constexpr std::wstring_view w_symbol{L"µg"};
    static constexpr std::u8string_view u8_symbol{u8"µg"};
};

struct milligram final : public unit_t<double, std::ratio<1, 1000000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milligram"};
    static constexpr std::string_view symbol{"mg"};
    static constexpr std::wstring_view w_symbol{L"mg"};
    static constexpr std::u8string_view u8_symbol{u8"mg"};
};

struct centigram final : public unit_t<double, std::ratio<1, 100000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 100000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centigram"};
    static constexpr std::string_view symbol{"cg"};
    static constexpr std::wstring_view w_symbol{L"cg"};
    static constexpr std::u8string_view u8_symbol{u8"cg"};
};

struct decigram final : public unit_t<double, std::ratio<1, 10000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 10000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decigram"};
    static constexpr std::string_view symbol{"dg"};
    static constexpr std::wstring_view w_symbol{L"dg"};
    static constexpr std::u8string_view u8_symbol{u8"dg"};
};

// gram is 1/1000 of kilogram
struct gram final : public unit_t<double, std::ratio<1, 1000>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gram"};
    static constexpr std::string_view symbol{"g"};
    static constexpr std::wstring_view w_symbol{L"g"};
    static constexpr std::u8string_view u8_symbol{u8"g"};
};

struct decagram final : public unit_t<double, std::ratio<1, 100>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 100>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decagram"};
    static constexpr std::string_view symbol{"dag"};
    static constexpr std::wstring_view w_symbol{L"dag"};
    static constexpr std::u8string_view u8_symbol{u8"dag"};
};

struct hectogram final : public unit_t<double, std::ratio<1, 10>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1, 10>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectogram"};
    static constexpr std::string_view symbol{"hg"};
    static constexpr std::wstring_view w_symbol{L"hg"};
    static constexpr std::u8string_view u8_symbol{u8"hg"};
};

// Larger mass units
struct megagram final : public unit_t<double, std::ratio<1000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000, 1>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megagram"};
    static constexpr std::string_view symbol{"Mg"};
    static constexpr std::wstring_view w_symbol{L"Mg"};
    static constexpr std::u8string_view u8_symbol{u8"Mg"};
};

struct gigagram final : public unit_t<double, std::ratio<1000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000, 1>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigagram"};
    static constexpr std::string_view symbol{"Gg"};
    static constexpr std::wstring_view w_symbol{L"Gg"};
    static constexpr std::u8string_view u8_symbol{u8"Gg"};
};

struct teragram final : public unit_t<double, std::ratio<1000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000, 1>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"teragram"};
    static constexpr std::string_view symbol{"Tg"};
    static constexpr std::wstring_view w_symbol{L"Tg"};
    static constexpr std::u8string_view u8_symbol{u8"Tg"};
};

struct petagram final : public unit_t<double, std::ratio<1000000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000000, 1>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"petagram"};
    static constexpr std::string_view symbol{"Pg"};
    static constexpr std::wstring_view w_symbol{L"Pg"};
    static constexpr std::u8string_view u8_symbol{u8"Pg"};
};

struct exagram final : public unit_t<double, std::ratio<1000000000000000, 1>, mass_dimension>
{
    using _base = unit_t<double, std::ratio<1000000000000000, 1>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"exagram"};
    static constexpr std::string_view symbol{"Eg"};
    static constexpr std::wstring_view w_symbol{L"Eg"};
    static constexpr std::u8string_view u8_symbol{u8"Eg"};
};

// Common aliases
using metric_ton = megagram;  // 1 metric ton = 1,000 kg (same as megagram)

PKR_SI_NAMESPACE_END








