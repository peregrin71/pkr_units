#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/current_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for ampere (SI base unit)
struct ampere_t final : public details::unit_t<double, std::ratio<1, 1>, current_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"ampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"A"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"A"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"A"};
};

// Metric current prefixes (strong types)

struct attoampere_t final : public details::unit_t<double, std::atto, current_dimension>
{
    using _base = details::unit_t<double, std::atto, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"attoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"aA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"aA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"aA"};
};

struct femtoampere_t final : public details::unit_t<double, std::femto, current_dimension>
{
    using _base = details::unit_t<double, std::femto, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"femtoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fA"};
};

struct picoampere_t final : public details::unit_t<double, std::pico, current_dimension>
{
    using _base = details::unit_t<double, std::pico, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pA"};
};

struct nanoampere_t final : public details::unit_t<double, std::nano, current_dimension>
{
    using _base = details::unit_t<double, std::nano, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nA"};
};

struct microampere_t final : public details::unit_t<double, std::micro, current_dimension>
{
    using _base = details::unit_t<double, std::micro, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5A"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5A"};
};

struct milliampere_t final : public details::unit_t<double, std::milli, current_dimension>
{
    using _base = details::unit_t<double, std::milli, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"milliampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mA"};
};

struct centiampere_t final : public details::unit_t<double, std::centi, current_dimension>
{
    using _base = details::unit_t<double, std::centi, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centiampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cA"};
};

struct deciampere_t final : public details::unit_t<double, std::deci, current_dimension>
{
    using _base = details::unit_t<double, std::deci, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"deciampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dA"};
};

struct decaampere_t final : public details::unit_t<double, std::deca, current_dimension>
{
    using _base = details::unit_t<double, std::deca, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"daA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"daA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"daA"};
};

struct hectoampere_t final : public details::unit_t<double, std::hecto, current_dimension>
{
    using _base = details::unit_t<double, std::hecto, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectoampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"hA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hA"};
};

struct kiloampere_t final : public details::unit_t<double, std::kilo, current_dimension>
{
    using _base = details::unit_t<double, std::kilo, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kiloampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kA"};
};

struct megaampere_t final : public details::unit_t<double, std::mega, current_dimension>
{
    using _base = details::unit_t<double, std::mega, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MA"};
};

struct gigaampere_t final : public details::unit_t<double, std::giga, current_dimension>
{
    using _base = details::unit_t<double, std::giga, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"GA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"GA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"GA"};
};

struct teraampere_t final : public details::unit_t<double, std::tera, current_dimension>
{
    using _base = details::unit_t<double, std::tera, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"teraampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"TA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"TA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"TA"};
};

struct petaampere_t final : public details::unit_t<double, std::peta, current_dimension>
{
    using _base = details::unit_t<double, std::peta, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"petaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"PA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"PA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"PA"};
};

struct exaampere_t final : public details::unit_t<double, std::exa, current_dimension>
{
    using _base = details::unit_t<double, std::exa, current_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"exaampere"};
    [[maybe_unused]] static constexpr std::string_view symbol{"EA"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"EA"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"EA"};
};

// ============================================================================
// Most derived unit type specializations for current units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, current_dimension>
{
    using type = ampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::atto, current_dimension>
{
    using type = attoampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::femto, current_dimension>
{
    using type = femtoampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::pico, current_dimension>
{
    using type = picoampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, current_dimension>
{
    using type = nanoampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, current_dimension>
{
    using type = microampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, current_dimension>
{
    using type = milliampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::centi, current_dimension>
{
    using type = centiampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::deci, current_dimension>
{
    using type = deciampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::deca, current_dimension>
{
    using type = decaampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::hecto, current_dimension>
{
    using type = hectoampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, current_dimension>
{
    using type = kiloampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::mega, current_dimension>
{
    using type = megaampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::giga, current_dimension>
{
    using type = gigaampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::tera, current_dimension>
{
    using type = teraampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::peta, current_dimension>
{
    using type = petaampere_t;
};

template <>
struct details::derived_unit_type_t<double, std::exa, current_dimension>
{
    using type = exaampere_t;
};

} // namespace PKR_UNITS_NAMESPACE
