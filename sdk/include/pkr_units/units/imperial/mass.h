#pragma once
#include <string_view>

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
    [[maybe_unused]] static constexpr std::string_view name{"grain"};
    [[maybe_unused]] static constexpr std::string_view symbol{"gr"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"gr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"gr"};
};

struct dram_t final : public details::unit_t<double, std::ratio<1771845, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1771845, 1000000000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"dram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dr"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dr"};
};

struct ounce_t final : public details::unit_t<double, std::ratio<28349523, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<28349523, 1000000000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"ounce"};
    [[maybe_unused]] static constexpr std::string_view symbol{"oz"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"oz"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"oz"};
};

struct pound_t final : public details::unit_t<double, std::ratio<453592370, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<453592370, 1000000000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"pound"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lb"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"lb"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"lb"};
};

struct stone_t final : public details::unit_t<double, std::ratio<6350293180, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<6350293180, 1000000000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"stone"};
    [[maybe_unused]] static constexpr std::string_view symbol{"st"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"st"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"st"};
};

struct hundredweight_t final : public details::unit_t<double, std::ratio<50802345, 1000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<50802345, 1000000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"hundredweight"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cwt"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cwt"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cwt"};
};

struct us_ton_t final : public details::unit_t<double, std::ratio<907184740, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<907184740, 1000000000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"us_ton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ton"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ton"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ton"};
};

struct long_ton_t final : public details::unit_t<double, std::ratio<1016046909, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<double, std::ratio<1016046909, 1000000000>, mass_dimension>;
    using _base::_base;
    [[maybe_unused]] static constexpr std::string_view name{"long_ton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"long ton"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"long ton"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"long ton"};
};

} // namespace PKR_UNITS_NAMESPACE
