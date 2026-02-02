#pragma once
#include <string_view>

#include <pkr_units/impl/decls/length_decl.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial length units
struct inch_t final : public details::unit_t<double, std::ratio<254, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<254, 10000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"inch"};

    [[maybe_unused]] static constexpr std::string_view symbol{"in"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"in"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"in"};
};

struct mil_t final : public details::unit_t<double, std::ratio<254, 10000000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<254, 10000000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"mil"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mil"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mil"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mil"};
};

struct foot_t final : public details::unit_t<double, std::ratio<3048, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<3048, 10000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"foot"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ft"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ft"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ft"};
};

struct yard_t final : public details::unit_t<double, std::ratio<9144, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<9144, 10000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"yard"};

    [[maybe_unused]] static constexpr std::string_view symbol{"yd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"yd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"yd"};
};

struct fathom_t final : public details::unit_t<double, std::ratio<18288, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<18288, 10000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"fathom"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ftm"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ftm"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ftm"};
};

struct rod_t final : public details::unit_t<double, std::ratio<50292, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<50292, 10000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"rod"};

    [[maybe_unused]] static constexpr std::string_view symbol{"rd"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"rd"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"rd"};
};

struct chain_t final : public details::unit_t<double, std::ratio<201168, 10000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<201168, 10000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"chain"};

    [[maybe_unused]] static constexpr std::string_view symbol{"ch"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ch"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ch"};
};

struct furlong_t final : public details::unit_t<double, std::ratio<201168, 1000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<201168, 1000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"furlong"};

    [[maybe_unused]] static constexpr std::string_view symbol{"fur"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fur"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fur"};
};

struct mile_t final : public details::unit_t<double, std::ratio<1609344, 1000>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1609344, 1000>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"mile"};

    [[maybe_unused]] static constexpr std::string_view symbol{"mi"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mi"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mi"};
};

struct nautical_mile_t final : public details::unit_t<double, std::ratio<1852, 1>, length_dimension>
{
    using _base = details::unit_t<double, std::ratio<1852, 1>, length_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"nautical_mile"};

    [[maybe_unused]] static constexpr std::string_view symbol{"nmi"};

    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nmi"};

    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nmi"};
};

} // namespace PKR_UNITS_NAMESPACE
