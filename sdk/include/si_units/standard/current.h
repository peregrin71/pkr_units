#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Current quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using current = unit_t<type_t, ratio_t, current_dimension>;

// Strong type for ampere (SI base unit)
struct ampere final : public unit_t<double, std::ratio<1, 1>, current_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ampere"};
    static constexpr std::string_view symbol{"A"};
    static constexpr std::wstring_view w_symbol{L"A"};
    static constexpr std::u8string_view u8_symbol{u8"A"};
};

// Metric current prefixes (strong types)
struct attoampere final : public unit_t<double, std::atto, current_dimension>
{
    using _base = unit_t<double, std::atto, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attoampere"};
    static constexpr std::string_view symbol{"aA"};
    static constexpr std::wstring_view w_symbol{L"aA"};
    static constexpr std::u8string_view u8_symbol{u8"aA"};
};

struct femtoampere final : public unit_t<double, std::femto, current_dimension>
{
    using _base = unit_t<double, std::femto, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtoampere"};
    static constexpr std::string_view symbol{"fA"};
    static constexpr std::wstring_view w_symbol{L"fA"};
    static constexpr std::u8string_view u8_symbol{u8"fA"};
};

struct picoampere final : public unit_t<double, std::pico, current_dimension>
{
    using _base = unit_t<double, std::pico, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picoampere"};
    static constexpr std::string_view symbol{"pA"};
    static constexpr std::wstring_view w_symbol{L"pA"};
    static constexpr std::u8string_view u8_symbol{u8"pA"};
};

struct nanoampere final : public unit_t<double, std::nano, current_dimension>
{
    using _base = unit_t<double, std::nano, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanoampere"};
    static constexpr std::string_view symbol{"nA"};
    static constexpr std::wstring_view w_symbol{L"nA"};
    static constexpr std::u8string_view u8_symbol{u8"nA"};
};

struct microampere final : public unit_t<double, std::micro, current_dimension>
{
    using _base = unit_t<double, std::micro, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microampere"};
    static constexpr std::string_view symbol{"uA"};
    static constexpr std::wstring_view w_symbol{L"µA"};
    static constexpr std::u8string_view u8_symbol{u8"µA"};
};

struct milliampere final : public unit_t<double, std::milli, current_dimension>
{
    using _base = unit_t<double, std::milli, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"milliampere"};
    static constexpr std::string_view symbol{"mA"};
    static constexpr std::wstring_view w_symbol{L"mA"};
    static constexpr std::u8string_view u8_symbol{u8"mA"};
};

struct centiampere final : public unit_t<double, std::centi, current_dimension>
{
    using _base = unit_t<double, std::centi, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centiampere"};
    static constexpr std::string_view symbol{"cA"};
    static constexpr std::wstring_view w_symbol{L"cA"};
    static constexpr std::u8string_view u8_symbol{u8"cA"};
};

struct deciampere final : public unit_t<double, std::deci, current_dimension>
{
    using _base = unit_t<double, std::deci, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"deciampere"};
    static constexpr std::string_view symbol{"dA"};
    static constexpr std::wstring_view w_symbol{L"dA"};
    static constexpr std::u8string_view u8_symbol{u8"dA"};
};

struct decaampere final : public unit_t<double, std::deca, current_dimension>
{
    using _base = unit_t<double, std::deca, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decaampere"};
    static constexpr std::string_view symbol{"daA"};
    static constexpr std::wstring_view w_symbol{L"daA"};
    static constexpr std::u8string_view u8_symbol{u8"daA"};
};

struct hectoampere final : public unit_t<double, std::hecto, current_dimension>
{
    using _base = unit_t<double, std::hecto, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectoampere"};
    static constexpr std::string_view symbol{"hA"};
    static constexpr std::wstring_view w_symbol{L"hA"};
    static constexpr std::u8string_view u8_symbol{u8"hA"};
};

struct kiloampere final : public unit_t<double, std::kilo, current_dimension>
{
    using _base = unit_t<double, std::kilo, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kiloampere"};
    static constexpr std::string_view symbol{"kA"};
    static constexpr std::wstring_view w_symbol{L"kA"};
    static constexpr std::u8string_view u8_symbol{u8"kA"};
};

struct megaampere final : public unit_t<double, std::mega, current_dimension>
{
    using _base = unit_t<double, std::mega, current_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megaampere"};
    static constexpr std::string_view symbol{"MA"};
    static constexpr std::wstring_view w_symbol{L"MA"};
    static constexpr std::u8string_view u8_symbol{u8"MA"};
};

PKR_SI_NAMESPACE_END


