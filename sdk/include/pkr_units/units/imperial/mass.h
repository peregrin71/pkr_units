#pragma once
#include <string_view>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/decls/mass_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Imperial mass units
template <is_unit_value_type_c T>
struct grain_t final : public details::unit_t<T, std::ratio<64799, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<64799, 1000000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"grain"};
    [[maybe_unused]] static constexpr std::string_view symbol{"gr"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"gr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"gr"};
};

template <is_unit_value_type_c T>
grain_t(T) -> grain_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
grain_t(const U&) -> grain_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct dram_t final : public details::unit_t<T, std::ratio<1771845, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<1771845, 1000000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"dram"};
    [[maybe_unused]] static constexpr std::string_view symbol{"dr"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"dr"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"dr"};
};

template <is_unit_value_type_c T>
dram_t(T) -> dram_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
dram_t(const U&) -> dram_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct ounce_t final : public details::unit_t<T, std::ratio<28349523, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<28349523, 1000000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"ounce"};
    [[maybe_unused]] static constexpr std::string_view symbol{"oz"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"oz"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"oz"};
};

template <is_unit_value_type_c T>
ounce_t(T) -> ounce_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
ounce_t(const U&) -> ounce_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct pound_t final : public details::unit_t<T, std::ratio<453592370, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<453592370, 1000000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"pound"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lb"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"lb"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"lb"};
};

template <is_unit_value_type_c T>
pound_t(T) -> pound_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
pound_t(const U&) -> pound_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct stone_t final : public details::unit_t<T, std::ratio<6350293180, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<6350293180, 1000000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"stone"};
    [[maybe_unused]] static constexpr std::string_view symbol{"st"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"st"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"st"};
};

template <is_unit_value_type_c T>
stone_t(T) -> stone_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
stone_t(const U&) -> stone_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct hundredweight_t final : public details::unit_t<T, std::ratio<50802345, 1000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<50802345, 1000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"hundredweight"};
    [[maybe_unused]] static constexpr std::string_view symbol{"cwt"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"cwt"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"cwt"};
};

template <is_unit_value_type_c T>
hundredweight_t(T) -> hundredweight_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
hundredweight_t(const U&) -> hundredweight_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct us_ton_t final : public details::unit_t<T, std::ratio<907184740, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<907184740, 1000000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"us_ton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ton"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ton"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ton"};
};

template <is_unit_value_type_c T>
us_ton_t(T) -> us_ton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
us_ton_t(const U&) -> us_ton_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct long_ton_t final : public details::unit_t<T, std::ratio<1016046909, 1000000000>, mass_dimension>
{
    using _base = details::unit_t<T, std::ratio<1016046909, 1000000000>, mass_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"long_ton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"long ton"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"long ton"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"long ton"};
};

template <is_unit_value_type_c T>
long_ton_t(T) -> long_ton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == mass_dimension)
long_ton_t(const U&) -> long_ton_t<typename details::is_pkr_unit<U>::value_type>;
} // namespace PKR_UNITS_NAMESPACE
