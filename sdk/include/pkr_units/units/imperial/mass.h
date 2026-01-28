#pragma once

#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/mass_decl.h>

namespace PKR_UNITS_NAMESPACE
{

// Imperial mass units
struct grain_t final : public details::unit_t<double, std::ratio<64799, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<64799, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"grain"};
    static constexpr std::string_view symbol{"gr"};
    static constexpr std::wstring_view w_symbol{L"gr"};
    static constexpr std::u8string_view u8_symbol{u8"gr"};
};

struct dram_t final : public details::unit_t<double, std::ratio<1771845, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1771845, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"dram"};
    static constexpr std::string_view symbol{"dr"};
    static constexpr std::wstring_view w_symbol{L"dr"};
    static constexpr std::u8string_view u8_symbol{u8"dr"};
};

struct ounce_t final : public details::unit_t<double, std::ratio<28349523, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<28349523, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"ounce"};
    static constexpr std::string_view symbol{"oz"};
    static constexpr std::wstring_view w_symbol{L"oz"};
    static constexpr std::u8string_view u8_symbol{u8"oz"};
};

struct pound_t final : public details::unit_t<double, std::ratio<453592370, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<453592370, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"pound"};
    static constexpr std::string_view symbol{"lb"};
    static constexpr std::wstring_view w_symbol{L"lb"};
    static constexpr std::u8string_view u8_symbol{u8"lb"};
};

struct stone_t final : public details::unit_t<double, std::ratio<6350293180, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<6350293180, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"stone"};
    static constexpr std::string_view symbol{"st"};
    static constexpr std::wstring_view w_symbol{L"st"};
    static constexpr std::u8string_view u8_symbol{u8"st"};
};

struct hundredweight_t final : public details::unit_t<double, std::ratio<50802345, 1000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<50802345, 1000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"hundredweight"};
    static constexpr std::string_view symbol{"cwt"};
    static constexpr std::wstring_view w_symbol{L"cwt"};
    static constexpr std::u8string_view u8_symbol{u8"cwt"};
};

struct us_ton_t final : public details::unit_t<double, std::ratio<907184740, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<907184740, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"us_ton"};
    static constexpr std::string_view symbol{"ton"};
    static constexpr std::wstring_view w_symbol{L"ton"};
    static constexpr std::u8string_view u8_symbol{u8"ton"};
};

struct long_ton_t final : public details::unit_t<double, std::ratio<1016046909, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1016046909, 1000000000>, mass_dimension>;
    using _base::_base;
    static constexpr std::string_view name{"long_ton"};
    static constexpr std::string_view symbol{"long ton"};
    static constexpr std::wstring_view w_symbol{L"long ton"};
    static constexpr std::u8string_view u8_symbol{u8"long ton"};
};

} // namespace PKR_UNITS_NAMESPACE
