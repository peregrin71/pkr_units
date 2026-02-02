#pragma once
#include <string_view>

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
    [[maybe_unused]] static constexpr std::string_view name{"mole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mol"};
};

// Metric amount prefixes (strong types)
struct attomole_t final : public details::unit_t<double, std::atto, amount_dimension>
{
    using _base = details::unit_t<double, std::atto, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"attomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"amol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"amol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"amol"};
};

struct femtomole_t final : public details::unit_t<double, std::femto, amount_dimension>
{
    using _base = details::unit_t<double, std::femto, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"femtomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fmol"};
};

struct picomole_t final : public details::unit_t<double, std::pico, amount_dimension>
{
    using _base = details::unit_t<double, std::pico, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pmol"};
};

struct nanomole_t final : public details::unit_t<double, std::nano, amount_dimension>
{
    using _base = details::unit_t<double, std::nano, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nmol"};
};

struct micromole_t final : public details::unit_t<double, std::micro, amount_dimension>
{
    using _base = details::unit_t<double, std::micro, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"micromole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"umol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5mol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5mol"};
};

struct millimole_t final : public details::unit_t<double, std::milli, amount_dimension>
{
    using _base = details::unit_t<double, std::milli, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millimole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mmol"};
};

struct centimole_t final : public details::unit_t<double, std::centi, amount_dimension>
{
    using _base = details::unit_t<double, std::centi, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centimole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cmol"};
};

struct decimole_t final : public details::unit_t<double, std::deci, amount_dimension>
{
    using _base = details::unit_t<double, std::deci, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decimole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dmol"};
};

struct decamole_t final : public details::unit_t<double, std::deca, amount_dimension>
{
    using _base = details::unit_t<double, std::deca, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"damol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"damol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"damol"};
};

struct hectomole_t final : public details::unit_t<double, std::hecto, amount_dimension>
{
    using _base = details::unit_t<double, std::hecto, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hmol"};
};

struct kilomole_t final : public details::unit_t<double, std::kilo, amount_dimension>
{
    using _base = details::unit_t<double, std::kilo, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilomole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kmol"};
};

struct megamole_t final : public details::unit_t<double, std::mega, amount_dimension>
{
    using _base = details::unit_t<double, std::mega, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Mmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mmol"};
};

struct gigamole_t final : public details::unit_t<double, std::giga, amount_dimension>
{
    using _base = details::unit_t<double, std::giga, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gmol"};
};

struct teramole_t final : public details::unit_t<double, std::tera, amount_dimension>
{
    using _base = details::unit_t<double, std::tera, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"teramole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Tmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tmol"};
};

struct petamole_t final : public details::unit_t<double, std::peta, amount_dimension>
{
    using _base = details::unit_t<double, std::peta, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"petamole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pmol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pmol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pmol"};
};

struct examole_t final : public details::unit_t<double, std::exa, amount_dimension>
{
    using _base = details::unit_t<double, std::exa, amount_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"examole"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Emol"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Emol"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Emol"};
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
