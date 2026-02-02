#pragma once

#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/intensity_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Strong type for candela (SI base unit)
struct candela_t final : public details::unit_t<double, std::ratio<1, 1>, intensity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"candela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"cd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cd"};
};

// Metric intensity prefixes (strong types)

struct attocandela_t final : public details::unit_t<double, std::atto, intensity_dimension>
{
    using _base = details::unit_t<double, std::atto, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"attocandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"acd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"acd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"acd"};
};

struct femtocandela_t final : public details::unit_t<double, std::femto, intensity_dimension>
{
    using _base = details::unit_t<double, std::femto, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"femtocandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"fcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fcd"};
};

struct picocandela_t final : public details::unit_t<double, std::pico, intensity_dimension>
{
    using _base = details::unit_t<double, std::pico, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"picocandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"pcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pcd"};
};

struct nanocandela_t final : public details::unit_t<double, std::nano, intensity_dimension>
{
    using _base = details::unit_t<double, std::nano, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nanocandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ncd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ncd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ncd"};
};

struct microcandela_t final : public details::unit_t<double, std::micro, intensity_dimension>
{
    using _base = details::unit_t<double, std::micro, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"microcandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ucd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5cd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5cd"};
};

struct millicandela_t final : public details::unit_t<double, std::milli, intensity_dimension>
{
    using _base = details::unit_t<double, std::milli, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"millicandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mcd"};
};

struct centicandela_t final : public details::unit_t<double, std::centi, intensity_dimension>
{
    using _base = details::unit_t<double, std::centi, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"centicandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ccd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ccd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ccd"};
};

struct decicandela_t final : public details::unit_t<double, std::deci, intensity_dimension>
{
    using _base = details::unit_t<double, std::deci, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decicandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"dcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dcd"};
};

struct decacandela_t final : public details::unit_t<double, std::deca, intensity_dimension>
{
    using _base = details::unit_t<double, std::deca, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"decacandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"dacd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dacd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dacd"};
};

struct hectocandela_t final : public details::unit_t<double, std::hecto, intensity_dimension>
{
    using _base = details::unit_t<double, std::hecto, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hectocandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"hcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"hcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"hcd"};
};

struct kilocandela_t final : public details::unit_t<double, std::kilo, intensity_dimension>
{
    using _base = details::unit_t<double, std::kilo, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"kilocandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"kcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kcd"};
};

struct megacandela_t final : public details::unit_t<double, std::mega, intensity_dimension>
{
    using _base = details::unit_t<double, std::mega, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"megacandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Mcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Mcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Mcd"};
};

struct gigacandela_t final : public details::unit_t<double, std::giga, intensity_dimension>
{
    using _base = details::unit_t<double, std::giga, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"gigacandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Gcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Gcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Gcd"};
};

struct teracandela_t final : public details::unit_t<double, std::tera, intensity_dimension>
{
    using _base = details::unit_t<double, std::tera, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"teracandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Tcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Tcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Tcd"};
};

struct petacandela_t final : public details::unit_t<double, std::peta, intensity_dimension>
{
    using _base = details::unit_t<double, std::peta, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"petacandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Pcd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Pcd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Pcd"};
};

struct exacandela_t final : public details::unit_t<double, std::exa, intensity_dimension>
{
    using _base = details::unit_t<double, std::exa, intensity_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"exacandela"};

    [[maybe_unused]] static constexpr std::string_view symbol{"Ecd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"Ecd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"Ecd"};
};

// ============================================================================
// Most derived unit type specializations for intensity units
// ============================================================================

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, intensity_dimension>
{
    using type = candela_t;
};

template <>
struct details::derived_unit_type_t<double, std::atto, intensity_dimension>
{
    using type = attocandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::femto, intensity_dimension>
{
    using type = femtocandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::pico, intensity_dimension>
{
    using type = picocandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::nano, intensity_dimension>
{
    using type = nanocandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::micro, intensity_dimension>
{
    using type = microcandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::milli, intensity_dimension>
{
    using type = millicandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::centi, intensity_dimension>
{
    using type = centicandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::deci, intensity_dimension>
{
    using type = decicandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::deca, intensity_dimension>
{
    using type = decacandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::hecto, intensity_dimension>
{
    using type = hectocandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::kilo, intensity_dimension>
{
    using type = kilocandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::mega, intensity_dimension>
{
    using type = megacandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::giga, intensity_dimension>
{
    using type = gigacandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::tera, intensity_dimension>
{
    using type = teracandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::peta, intensity_dimension>
{
    using type = petacandela_t;
};

template <>
struct details::derived_unit_type_t<double, std::exa, intensity_dimension>
{
    using type = exacandela_t;
};

} // namespace PKR_UNITS_NAMESPACE
