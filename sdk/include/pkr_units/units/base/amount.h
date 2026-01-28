#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/amount_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for mole (SI base unit)
struct mole_t final : public details::unit_t<double, std::ratio<1, 1>, amount_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"mole"};
    static constexpr std::string_view symbol{"mol"};
    static constexpr std::wstring_view w_symbol{L"mol"};
    static constexpr std::u8string_view u8_symbol{u8"mol"};
};

// Metric amount prefixes (strong types)
struct attomole_t final : public details::unit_t<double, std::atto, amount_dimension>
{
    using _base = details::unit_t<double, std::atto, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attomole"};
    static constexpr std::string_view symbol{"amol"};
    static constexpr std::wstring_view w_symbol{L"amol"};
    static constexpr std::u8string_view u8_symbol{u8"amol"};
};

struct femtomole_t final : public details::unit_t<double, std::femto, amount_dimension>
{
    using _base = details::unit_t<double, std::femto, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtomole"};
    static constexpr std::string_view symbol{"fmol"};
    static constexpr std::wstring_view w_symbol{L"fmol"};
    static constexpr std::u8string_view u8_symbol{u8"fmol"};
};

struct picomole_t final : public details::unit_t<double, std::pico, amount_dimension>
{
    using _base = details::unit_t<double, std::pico, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picomole"};
    static constexpr std::string_view symbol{"pmol"};
    static constexpr std::wstring_view w_symbol{L"pmol"};
    static constexpr std::u8string_view u8_symbol{u8"pmol"};
};

struct nanomole_t final : public details::unit_t<double, std::nano, amount_dimension>
{
    using _base = details::unit_t<double, std::nano, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanomole"};
    static constexpr std::string_view symbol{"nmol"};
    static constexpr std::wstring_view w_symbol{L"nmol"};
    static constexpr std::u8string_view u8_symbol{u8"nmol"};
};

struct micromole_t final : public details::unit_t<double, std::micro, amount_dimension>
{
    using _base = details::unit_t<double, std::micro, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"micromole"};
    static constexpr std::string_view symbol{"umol"};
    static constexpr std::wstring_view w_symbol{L"\u00b5mol"};
    static constexpr std::u8string_view u8_symbol{u8"\u00b5mol"};
};

struct millimole_t final : public details::unit_t<double, std::milli, amount_dimension>
{
    using _base = details::unit_t<double, std::milli, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millimole"};
    static constexpr std::string_view symbol{"mmol"};
    static constexpr std::wstring_view w_symbol{L"mmol"};
    static constexpr std::u8string_view u8_symbol{u8"mmol"};
};

struct centimole_t final : public details::unit_t<double, std::centi, amount_dimension>
{
    using _base = details::unit_t<double, std::centi, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centimole"};
    static constexpr std::string_view symbol{"cmol"};
    static constexpr std::wstring_view w_symbol{L"cmol"};
    static constexpr std::u8string_view u8_symbol{u8"cmol"};
};

struct decimole_t final : public details::unit_t<double, std::deci, amount_dimension>
{
    using _base = details::unit_t<double, std::deci, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decimole"};
    static constexpr std::string_view symbol{"dmol"};
    static constexpr std::wstring_view w_symbol{L"dmol"};
    static constexpr std::u8string_view u8_symbol{u8"dmol"};
};

struct decamole_t final : public details::unit_t<double, std::deca, amount_dimension>
{
    using _base = details::unit_t<double, std::deca, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decamole"};
    static constexpr std::string_view symbol{"damol"};
    static constexpr std::wstring_view w_symbol{L"damol"};
    static constexpr std::u8string_view u8_symbol{u8"damol"};
};

struct hectomole_t final : public details::unit_t<double, std::hecto, amount_dimension>
{
    using _base = details::unit_t<double, std::hecto, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectomole"};
    static constexpr std::string_view symbol{"hmol"};
    static constexpr std::wstring_view w_symbol{L"hmol"};
    static constexpr std::u8string_view u8_symbol{u8"hmol"};
};

struct kilomole_t final : public details::unit_t<double, std::kilo, amount_dimension>
{
    using _base = details::unit_t<double, std::kilo, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilomole"};
    static constexpr std::string_view symbol{"kmol"};
    static constexpr std::wstring_view w_symbol{L"kmol"};
    static constexpr std::u8string_view u8_symbol{u8"kmol"};
};

struct megamole_t final : public details::unit_t<double, std::mega, amount_dimension>
{
    using _base = details::unit_t<double, std::mega, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megamole"};
    static constexpr std::string_view symbol{"Mmol"};
    static constexpr std::wstring_view w_symbol{L"Mmol"};
    static constexpr std::u8string_view u8_symbol{u8"Mmol"};
};

struct gigamole_t final : public details::unit_t<double, std::giga, amount_dimension>
{
    using _base = details::unit_t<double, std::giga, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"gigamole"};
    static constexpr std::string_view symbol{"Gmol"};
    static constexpr std::wstring_view w_symbol{L"Gmol"};
    static constexpr std::u8string_view u8_symbol{u8"Gmol"};
};

struct teramole_t final : public details::unit_t<double, std::tera, amount_dimension>
{
    using _base = details::unit_t<double, std::tera, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"teramole"};
    static constexpr std::string_view symbol{"Tmol"};
    static constexpr std::wstring_view w_symbol{L"Tmol"};
    static constexpr std::u8string_view u8_symbol{u8"Tmol"};
};

struct petamole_t final : public details::unit_t<double, std::peta, amount_dimension>
{
    using _base = details::unit_t<double, std::peta, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"petamole"};
    static constexpr std::string_view symbol{"Pmol"};
    static constexpr std::wstring_view w_symbol{L"Pmol"};
    static constexpr std::u8string_view u8_symbol{u8"Pmol"};
};

struct examole_t final : public details::unit_t<double, std::exa, amount_dimension>
{
    using _base = details::unit_t<double, std::exa, amount_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"examole"};
    static constexpr std::string_view symbol{"Emol"};
    static constexpr std::wstring_view w_symbol{L"Emol"};
    static constexpr std::u8string_view u8_symbol{u8"Emol"};
};
// ============================================================================
// Most derived unit type specializations for amount units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, amount_dimension>
{
    using type = mole_t;
};

template <>
struct details::derived_unit_type_t<double, std::atto, amount_dimension>
{
    using type = attomole_t;
};

template <>
struct details::derived_unit_type_t<double, std::femto, amount_dimension>
{
    using type = femtomole_t;
};

template <>
struct details::derived_unit_type_t<double, std::pico, amount_dimension>
{
    using type = picomole_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, amount_dimension>
{
    using type = nanomole_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, amount_dimension>
{
    using type = micromole_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, amount_dimension>
{
    using type = millimole_t;
};

template <>
struct details::derived_unit_type_t<double, std::centi, amount_dimension>
{
    using type = centimole_t;
};

template <>
struct details::derived_unit_type_t<double, std::deci, amount_dimension>
{
    using type = decimole_t;
};

template <>
struct details::derived_unit_type_t<double, std::deca, amount_dimension>
{
    using type = decamole_t;
};

template <>
struct details::derived_unit_type_t<double, std::hecto, amount_dimension>
{
    using type = hectomole_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, amount_dimension>
{
    using type = kilomole_t;
};

template <>
struct details::derived_unit_type_t<double, std::mega, amount_dimension>
{
    using type = megamole_t;
};

template <>
struct details::derived_unit_type_t<double, std::giga, amount_dimension>
{
    using type = gigamole_t;
};

template <>
struct details::derived_unit_type_t<double, std::tera, amount_dimension>
{
    using type = teramole_t;
};

template <>
struct details::derived_unit_type_t<double, std::peta, amount_dimension>
{
    using type = petamole_t;
};

template <>
struct details::derived_unit_type_t<double, std::exa, amount_dimension>
{
    using type = examole_t;
};

} // namespace PKR_UNITS_NAMESPACE
