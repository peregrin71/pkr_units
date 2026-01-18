#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/amount_def.h"

PKR_SI_BEGIN_NAMESPACE
{

// Strong type for mole (SI base unit)
struct mole_t final : public details::unit_t<double, std::ratio<1, 1>, details::amount_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"mole"};
    static constexpr std::string_view symbol{"mol"};
    static constexpr std::wstring_view w_symbol{L"mol"};
    static constexpr std::u8string_view u8_symbol{u8"mol"};
};

// Metric amount prefixes (strong types)
struct attomole_t final : public details::unit_t<double, std::atto, details::amount_dimension>
{
    using _base = details::unit_t<double, std::atto, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attomole"};
    static constexpr std::string_view symbol{"amol"};
    static constexpr std::wstring_view w_symbol{L"amol"};
    static constexpr std::u8string_view u8_symbol{u8"amol"};
};

struct femtomole_t final : public details::unit_t<double, std::femto, details::amount_dimension>
{
    using _base = details::unit_t<double, std::femto, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtomole"};
    static constexpr std::string_view symbol{"fmol"};
    static constexpr std::wstring_view w_symbol{L"fmol"};
    static constexpr std::u8string_view u8_symbol{u8"fmol"};
};

struct picomole_t final : public details::unit_t<double, std::pico, details::amount_dimension>
{
    using _base = details::unit_t<double, std::pico, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picomole"};
    static constexpr std::string_view symbol{"pmol"};
    static constexpr std::wstring_view w_symbol{L"pmol"};
    static constexpr std::u8string_view u8_symbol{u8"pmol"};
};

struct nanomole_t final : public details::unit_t<double, std::nano, details::amount_dimension>
{
    using _base = details::unit_t<double, std::nano, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanomole"};
    static constexpr std::string_view symbol{"nmol"};
    static constexpr std::wstring_view w_symbol{L"nmol"};
    static constexpr std::u8string_view u8_symbol{u8"nmol"};
};

struct micromole_t final : public details::unit_t<double, std::micro, details::amount_dimension>
{
    using _base = details::unit_t<double, std::micro, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micromole"};
    static constexpr std::string_view symbol{"umol"};
    static constexpr std::wstring_view w_symbol{L"µmol"};
    static constexpr std::u8string_view u8_symbol{u8"µmol"};
};

struct millimole_t final : public details::unit_t<double, std::milli, details::amount_dimension>
{
    using _base = details::unit_t<double, std::milli, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millimole"};
    static constexpr std::string_view symbol{"mmol"};
    static constexpr std::wstring_view w_symbol{L"mmol"};
    static constexpr std::u8string_view u8_symbol{u8"mmol"};
};

struct centimole_t final : public details::unit_t<double, std::centi, details::amount_dimension>
{
    using _base = details::unit_t<double, std::centi, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centimole"};
    static constexpr std::string_view symbol{"cmol"};
    static constexpr std::wstring_view w_symbol{L"cmol"};
    static constexpr std::u8string_view u8_symbol{u8"cmol"};
};

struct decimole_t final : public details::unit_t<double, std::deci, details::amount_dimension>
{
    using _base = details::unit_t<double, std::deci, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decimole"};
    static constexpr std::string_view symbol{"dmol"};
    static constexpr std::wstring_view w_symbol{L"dmol"};
    static constexpr std::u8string_view u8_symbol{u8"dmol"};
};

struct decamole_t final : public details::unit_t<double, std::deca, details::amount_dimension>
{
    using _base = details::unit_t<double, std::deca, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decamole"};
    static constexpr std::string_view symbol{"damol"};
    static constexpr std::wstring_view w_symbol{L"damol"};
    static constexpr std::u8string_view u8_symbol{u8"damol"};
};

struct hectomole_t final : public details::unit_t<double, std::hecto, details::amount_dimension>
{
    using _base = details::unit_t<double, std::hecto, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectomole"};
    static constexpr std::string_view symbol{"hmol"};
    static constexpr std::wstring_view w_symbol{L"hmol"};
    static constexpr std::u8string_view u8_symbol{u8"hmol"};
};

struct kilomole_t final : public details::unit_t<double, std::kilo, details::amount_dimension>
{
    using _base = details::unit_t<double, std::kilo, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilomole"};
    static constexpr std::string_view symbol{"kmol"};
    static constexpr std::wstring_view w_symbol{L"kmol"};
    static constexpr std::u8string_view u8_symbol{u8"kmol"};
};

struct megamole_t final : public details::unit_t<double, std::mega, details::amount_dimension>
{
    using _base = details::unit_t<double, std::mega, details::amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megamole"};
    static constexpr std::string_view symbol{"Mmol"};
    static constexpr std::wstring_view w_symbol{L"Mmol"};
    static constexpr std::u8string_view u8_symbol{u8"Mmol"};
};

PKR_SI_NAMESPACE_END


