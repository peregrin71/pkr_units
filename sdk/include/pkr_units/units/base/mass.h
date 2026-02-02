#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/mass_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for kilogram (SI base unit for mass)
// NOTE: Kilogram is the base SI unit, not gram (unlike length where meter is base)
struct kilogram_t final : public details::unit_t<double, std::ratio<1, 1>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kg"};
};

// Metric mass prefixes (applied relative to kilogram)
// All mass units are defined relative to kilogram (ratio 1/1) as the base
// NOTE: attogram (10^-21) and femtogram (10^-18) exceed std::ratio limits
// and are omitted. The smallest representable is picogram (10^-15).

struct picogram_t final : public details::unit_t<double, std::femto, mass_dimension>
{
    using _base = details::unit_t<double, std::femto, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pg"};
};

struct nanogram_t final : public details::unit_t<double, std::pico, mass_dimension>
{
    using _base = details::unit_t<double, std::pico, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ng"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ng"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ng"};
};

struct microgram_t final : public details::unit_t<double, std::nano, mass_dimension>
{
    using _base = details::unit_t<double, std::nano, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microgram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ug"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5g"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5g"};
};

struct milligram_t final : public details::unit_t<double, std::micro, mass_dimension>
{
    using _base = details::unit_t<double, std::micro, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"milligram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mg"};
};

struct centigram_t final : public details::unit_t<double, std::ratio<1, 100000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 100000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centigram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cg"};
};

struct decigram_t final : public details::unit_t<double, std::ratio<1, 10000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 10000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decigram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dg"};
};

// gram is 1/1000 of kilogram
struct gram_t final : public details::unit_t<double, std::milli, mass_dimension>
{
    using _base = details::unit_t<double, std::milli, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"g"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"g"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"g"};
};

struct decagram_t final : public details::unit_t<double, std::centi, mass_dimension>
{
    using _base = details::unit_t<double, std::centi, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dag"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dag"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dag"};
};

struct hectogram_t final : public details::unit_t<double, std::deci, mass_dimension>
{
    using _base = details::unit_t<double, std::deci, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectogram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hg"};
};

// Larger mass units
struct gigagram_t final : public details::unit_t<double, std::mega, mass_dimension>
{
    using _base = details::unit_t<double, std::mega, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Gg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gg"};
};

struct teragram_t final : public details::unit_t<double, std::giga, mass_dimension>
{
    using _base = details::unit_t<double, std::giga, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"teragram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Tg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tg"};
};

struct petagram_t final : public details::unit_t<double, std::tera, mass_dimension>
{
    using _base = details::unit_t<double, std::tera, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"petagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Pg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pg"};
};

struct exagram_t final : public details::unit_t<double, std::peta, mass_dimension>
{
    using _base = details::unit_t<double, std::peta, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"exagram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"Eg"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Eg"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Eg"};
};

// Common mass units
struct metric_ton_t final : public details::unit_t<double, std::kilo, mass_dimension>
{
    using _base = details::unit_t<double, std::kilo, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"metric ton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"t"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"t"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"t"};
};

// ============================================================================
// Most derived unit type specializations for mass units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, mass_dimension>
{
    using type = kilogram_t;
};

template <>
struct details::derived_unit_type_t<double, std::femto, mass_dimension>
{
    using type = picogram_t;
};

template <>
struct details::derived_unit_type_t<double, std::pico, mass_dimension>
{
    using type = nanogram_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, mass_dimension>
{
    using type = microgram_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, mass_dimension>
{
    using type = milligram_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 100000>, mass_dimension>
{
    using type = centigram_t;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 10000>, mass_dimension>
{
    using type = decigram_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, mass_dimension>
{
    using type = gram_t;
};

template <>
struct details::derived_unit_type_t<double, std::centi, mass_dimension>
{
    using type = decagram_t;
};

template <>
struct details::derived_unit_type_t<double, std::deci, mass_dimension>
{
    using type = hectogram_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, mass_dimension>
{
    using type = metric_ton_t;
};

template <>
struct details::derived_unit_type_t<double, std::mega, mass_dimension>
{
    using type = gigagram_t;
};

template <>
struct details::derived_unit_type_t<double, std::giga, mass_dimension>
{
    using type = teragram_t;
};

template <>
struct details::derived_unit_type_t<double, std::tera, mass_dimension>
{
    using type = petagram_t;
};

template <>
struct details::derived_unit_type_t<double, std::peta, mass_dimension>
{
    using type = exagram_t;
};

} // namespace PKR_UNITS_NAMESPACE
