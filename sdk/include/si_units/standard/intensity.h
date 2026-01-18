#pragma once

#include "../impl/details/si_unit.h"
#include "../impl/details/dimension.h"
#include "../namespace_config.h"

PKR_SI_BEGIN_NAMESPACE
{
// Intensity quantity template
template<typename type_t = double, typename ratio_t = std::ratio<1, 1>>
using intensity = unit_t<type_t, ratio_t, intensity_dimension>;

// Strong type for candela (SI base unit)
struct candela final : public unit_t<double, std::ratio<1, 1>, intensity_dimension>
{
    using _base = unit_t<double, std::ratio<1, 1>, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"candela"};
    static constexpr std::string_view symbol{"cd"};
    static constexpr std::wstring_view w_symbol{L"cd"};
    static constexpr std::u8string_view u8_symbol{u8"cd"};
};

// Metric intensity prefixes (strong types)
struct attocandela final : public unit_t<double, std::atto, intensity_dimension>
{
    using _base = unit_t<double, std::atto, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"attocandela"};
    static constexpr std::string_view symbol{"acd"};
    static constexpr std::wstring_view w_symbol{L"acd"};
    static constexpr std::u8string_view u8_symbol{u8"acd"};
};

struct femtocandela final : public unit_t<double, std::femto, intensity_dimension>
{
    using _base = unit_t<double, std::femto, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"femtocandela"};
    static constexpr std::string_view symbol{"fcd"};
    static constexpr std::wstring_view w_symbol{L"fcd"};
    static constexpr std::u8string_view u8_symbol{u8"fcd"};
};

struct picocandela final : public unit_t<double, std::pico, intensity_dimension>
{
    using _base = unit_t<double, std::pico, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"picocandela"};
    static constexpr std::string_view symbol{"pcd"};
    static constexpr std::wstring_view w_symbol{L"pcd"};
    static constexpr std::u8string_view u8_symbol{u8"pcd"};
};

struct nanocandela final : public unit_t<double, std::nano, intensity_dimension>
{
    using _base = unit_t<double, std::nano, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nanocandela"};
    static constexpr std::string_view symbol{"ncd"};
    static constexpr std::wstring_view w_symbol{L"ncd"};
    static constexpr std::u8string_view u8_symbol{u8"ncd"};
};

struct microcandela final : public unit_t<double, std::micro, intensity_dimension>
{
    using _base = unit_t<double, std::micro, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"microcandela"};
    static constexpr std::string_view symbol{"ucd"};
    static constexpr std::wstring_view w_symbol{L"µcd"};
    static constexpr std::u8string_view u8_symbol{u8"µcd"};
};

struct millicandela final : public unit_t<double, std::milli, intensity_dimension>
{
    using _base = unit_t<double, std::milli, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"millicandela"};
    static constexpr std::string_view symbol{"mcd"};
    static constexpr std::wstring_view w_symbol{L"mcd"};
    static constexpr std::u8string_view u8_symbol{u8"mcd"};
};

struct centicandela final : public unit_t<double, std::centi, intensity_dimension>
{
    using _base = unit_t<double, std::centi, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"centicandela"};
    static constexpr std::string_view symbol{"ccd"};
    static constexpr std::wstring_view w_symbol{L"ccd"};
    static constexpr std::u8string_view u8_symbol{u8"ccd"};
};

struct decicandela final : public unit_t<double, std::deci, intensity_dimension>
{
    using _base = unit_t<double, std::deci, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decicandela"};
    static constexpr std::string_view symbol{"dcd"};
    static constexpr std::wstring_view w_symbol{L"dcd"};
    static constexpr std::u8string_view u8_symbol{u8"dcd"};
};

struct decacandela final : public unit_t<double, std::deca, intensity_dimension>
{
    using _base = unit_t<double, std::deca, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"decacandela"};
    static constexpr std::string_view symbol{"dacd"};
    static constexpr std::wstring_view w_symbol{L"dacd"};
    static constexpr std::u8string_view u8_symbol{u8"dacd"};
};

struct hectocandela final : public unit_t<double, std::hecto, intensity_dimension>
{
    using _base = unit_t<double, std::hecto, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hectocandela"};
    static constexpr std::string_view symbol{"hcd"};
    static constexpr std::wstring_view w_symbol{L"hcd"};
    static constexpr std::u8string_view u8_symbol{u8"hcd"};
};

struct kilocandela final : public unit_t<double, std::kilo, intensity_dimension>
{
    using _base = unit_t<double, std::kilo, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"kilocandela"};
    static constexpr std::string_view symbol{"kcd"};
    static constexpr std::wstring_view w_symbol{L"kcd"};
    static constexpr std::u8string_view u8_symbol{u8"kcd"};
};

struct megacandela final : public unit_t<double, std::mega, intensity_dimension>
{
    using _base = unit_t<double, std::mega, intensity_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"megacandela"};
    static constexpr std::string_view symbol{"Mcd"};
    static constexpr std::wstring_view w_symbol{L"Mcd"};
    static constexpr std::u8string_view u8_symbol{u8"Mcd"};
};

PKR_SI_NAMESPACE_END


