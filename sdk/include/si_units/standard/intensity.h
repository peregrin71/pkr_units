#pragma once

#include "../impl/namespace_config.h"
#include "../impl/common/intensity_def.h"

PKR_SI_BEGIN_NAMESPACE
{

// Strong type for candela (SI base unit)
struct candela_t final : public details::unit_t<double, std::ratio<1, 1>, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"candela"};
    static constexpr std::string_view symbol{"cd"};
    static constexpr std::wstring_view w_symbol{L"cd"};
    static constexpr std::u8string_view u8_symbol{u8"cd"};
};

// Metric intensity prefixes (strong types)
struct attocandela_t final : public details::unit_t<double, std::atto, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::atto, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attocandela"};
    static constexpr std::string_view symbol{"acd"};
    static constexpr std::wstring_view w_symbol{L"acd"};
    static constexpr std::u8string_view u8_symbol{u8"acd"};
};

struct femtocandela_t final : public details::unit_t<double, std::femto, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::femto, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtocandela"};
    static constexpr std::string_view symbol{"fcd"};
    static constexpr std::wstring_view w_symbol{L"fcd"};
    static constexpr std::u8string_view u8_symbol{u8"fcd"};
};

struct picocandela_t final : public details::unit_t<double, std::pico, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::pico, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picocandela"};
    static constexpr std::string_view symbol{"pcd"};
    static constexpr std::wstring_view w_symbol{L"pcd"};
    static constexpr std::u8string_view u8_symbol{u8"pcd"};
};

struct nanocandela_t final : public details::unit_t<double, std::nano, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::nano, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanocandela"};
    static constexpr std::string_view symbol{"ncd"};
    static constexpr std::wstring_view w_symbol{L"ncd"};
    static constexpr std::u8string_view u8_symbol{u8"ncd"};
};

struct microcandela_t final : public details::unit_t<double, std::micro, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::micro, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microcandela"};
    static constexpr std::string_view symbol{"ucd"};
    static constexpr std::wstring_view w_symbol{L"µcd"};
    static constexpr std::u8string_view u8_symbol{u8"µcd"};
};

struct millicandela_t final : public details::unit_t<double, std::milli, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::milli, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millicandela"};
    static constexpr std::string_view symbol{"mcd"};
    static constexpr std::wstring_view w_symbol{L"mcd"};
    static constexpr std::u8string_view u8_symbol{u8"mcd"};
};

struct centicandela_t final : public details::unit_t<double, std::centi, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::centi, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centicandela"};
    static constexpr std::string_view symbol{"ccd"};
    static constexpr std::wstring_view w_symbol{L"ccd"};
    static constexpr std::u8string_view u8_symbol{u8"ccd"};
};

struct decicandela_t final : public details::unit_t<double, std::deci, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::deci, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decicandela"};
    static constexpr std::string_view symbol{"dcd"};
    static constexpr std::wstring_view w_symbol{L"dcd"};
    static constexpr std::u8string_view u8_symbol{u8"dcd"};
};

struct decacandela_t final : public details::unit_t<double, std::deca, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::deca, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decacandela"};
    static constexpr std::string_view symbol{"dacd"};
    static constexpr std::wstring_view w_symbol{L"dacd"};
    static constexpr std::u8string_view u8_symbol{u8"dacd"};
};

struct hectocandela_t final : public details::unit_t<double, std::hecto, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::hecto, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectocandela"};
    static constexpr std::string_view symbol{"hcd"};
    static constexpr std::wstring_view w_symbol{L"hcd"};
    static constexpr std::u8string_view u8_symbol{u8"hcd"};
};

struct kilocandela_t final : public details::unit_t<double, std::kilo, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::kilo, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilocandela"};
    static constexpr std::string_view symbol{"kcd"};
    static constexpr std::wstring_view w_symbol{L"kcd"};
    static constexpr std::u8string_view u8_symbol{u8"kcd"};
};

struct megacandela_t final : public details::unit_t<double, std::mega, details::intensity_dimension>
{
    using _base = details::unit_t<double, std::mega, details::intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megacandela"};
    static constexpr std::string_view symbol{"Mcd"};
    static constexpr std::wstring_view w_symbol{L"Mcd"};
    static constexpr std::u8string_view u8_symbol{u8"Mcd"};
};

PKR_SI_NAMESPACE_END


