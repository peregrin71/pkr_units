#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

PKR_UNITS_BEGIN_NAMESPACE
{

// Inductance dimension
inline constexpr dimension_t inductance_dimension{2, 1, -2, -2, 0, 0, 0, 0};

// Strong type for henry (SI base unit)
struct henry final : public details::unit_t<double, std::ratio<1, 1>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1>, inductance_dimension>;
    using _base::_base;
    const std::string_view name{"henry"};
    const std::string_view symbol{"H"};
    const std::wstring_view w_symbol{L"H"};
    const std::u8string_view u8_symbol{u8"H"};
};

// Strong type for millihenry
struct millihenry final : public details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000>, inductance_dimension>;
    using _base::_base;
    const std::string_view name{"millihenry"};
    const std::string_view symbol{"mH"};
    const std::wstring_view w_symbol{L"mH"};
    const std::u8string_view u8_symbol{u8"mH"};
};

// Strong type for microhenry
struct microhenry final : public details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000>, inductance_dimension>;
    using _base::_base;
    const std::string_view name{"microhenry"};
    const std::string_view symbol{"µH"};
    const std::wstring_view w_symbol{L"µH"};
    const std::u8string_view u8_symbol{u8"µH"};
};

// Strong type for nanohenry
struct nanohenry final : public details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>
{
    using _base = details::unit_t<double, std::ratio<1, 1000000000>, inductance_dimension>;
    using _base::_base;
    const std::string_view name{"nanohenry"};
    const std::string_view symbol{"nH"};
    const std::wstring_view w_symbol{L"nH"};
    const std::u8string_view u8_symbol{u8"nH"};
};

} // PKR_UNITS_NAMESPACE








