#pragma once

#include <pkr_units/impl/decls/length_decl.h>
#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Imperial length units
struct inch_t final : public details::unit_t<double, std::ratio<254, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<254, 10000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"inch"};
    static constexpr std::string_view symbol{"in"};
    static constexpr std::wstring_view w_symbol{L"in"};
    static constexpr std::u8string_view u8_symbol{u8"in"};
};

struct mil_t final : public details::unit_t<double, std::ratio<254, 10000000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<254, 10000000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"mil"};
    static constexpr std::string_view symbol{"mil"};
    static constexpr std::wstring_view w_symbol{L"mil"};
    static constexpr std::u8string_view u8_symbol{u8"mil"};
};

struct foot_t final : public details::unit_t<double, std::ratio<3048, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<3048, 10000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"foot"};
    static constexpr std::string_view symbol{"ft"};
    static constexpr std::wstring_view w_symbol{L"ft"};
    static constexpr std::u8string_view u8_symbol{u8"ft"};
};

struct yard_t final : public details::unit_t<double, std::ratio<9144, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<9144, 10000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"yard"};
    static constexpr std::string_view symbol{"yd"};
    static constexpr std::wstring_view w_symbol{L"yd"};
    static constexpr std::u8string_view u8_symbol{u8"yd"};
};

struct fathom_t final : public details::unit_t<double, std::ratio<18288, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<18288, 10000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"fathom"};
    static constexpr std::string_view symbol{"ftm"};
    static constexpr std::wstring_view w_symbol{L"ftm"};
    static constexpr std::u8string_view u8_symbol{u8"ftm"};
};

struct rod_t final : public details::unit_t<double, std::ratio<50292, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<50292, 10000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"rod"};
    static constexpr std::string_view symbol{"rd"};
    static constexpr std::wstring_view w_symbol{L"rd"};
    static constexpr std::u8string_view u8_symbol{u8"rd"};
};

struct chain_t final : public details::unit_t<double, std::ratio<201168, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<201168, 10000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"chain"};
    static constexpr std::string_view symbol{"ch"};
    static constexpr std::wstring_view w_symbol{L"ch"};
    static constexpr std::u8string_view u8_symbol{u8"ch"};
};

struct furlong_t final : public details::unit_t<double, std::ratio<201168, 1000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<201168, 1000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"furlong"};
    static constexpr std::string_view symbol{"fur"};
    static constexpr std::wstring_view w_symbol{L"fur"};
    static constexpr std::u8string_view u8_symbol{u8"fur"};
};

struct mile_t final : public details::unit_t<double, std::ratio<1609344, 1000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1609344, 1000>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"mile"};
    static constexpr std::string_view symbol{"mi"};
    static constexpr std::wstring_view w_symbol{L"mi"};
    static constexpr std::u8string_view u8_symbol{u8"mi"};
};

struct nautical_mile_t final : public details::unit_t<double, std::ratio<1852, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1852, 1>, length_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"nautical_mile"};
    static constexpr std::string_view symbol{"nmi"};
    static constexpr std::wstring_view w_symbol{L"nmi"};
    static constexpr std::u8string_view u8_symbol{u8"nmi"};
};

} // PKR_UNITS_NAMESPACE








