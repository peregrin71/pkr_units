#pragma once
#include <string_view>
#include <pkr_units/impl/unit_t.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{
// Imperial length units
template <is_unit_value_type_c T>
struct inch_t final : public unit_t<T, std::ratio<254, 10000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<254, 10000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"inch"};
    [[maybe_unused]] static constexpr std::string_view symbol{"in"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"in"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"in"};
};

template <is_unit_value_type_c T>
inch_t(T) -> inch_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
inch_t(const U&) -> inch_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct mil_t final : public unit_t<T, std::ratio<254, 10000000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<254, 10000000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"mil"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mil"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mil"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mil"};
};

template <is_unit_value_type_c T>
mil_t(T) -> mil_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
mil_t(const U&) -> mil_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct foot_t final : public unit_t<T, std::ratio<3048, 10000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<3048, 10000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"foot"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ft"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ft"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ft"};
};

template <is_unit_value_type_c T>
foot_t(T) -> foot_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
foot_t(const U&) -> foot_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct yard_t final : public unit_t<T, std::ratio<9144, 10000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<9144, 10000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"yard"};
    [[maybe_unused]] static constexpr std::string_view symbol{"yd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"yd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"yd"};
};

template <is_unit_value_type_c T>
yard_t(T) -> yard_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
yard_t(const U&) -> yard_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct fathom_t final : public unit_t<T, std::ratio<18288, 10000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<18288, 10000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"fathom"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ftm"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ftm"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ftm"};
};

template <is_unit_value_type_c T>
fathom_t(T) -> fathom_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
fathom_t(const U&) -> fathom_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct rod_t final : public unit_t<T, std::ratio<50292, 10000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<50292, 10000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"rod"};
    [[maybe_unused]] static constexpr std::string_view symbol{"rd"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"rd"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"rd"};
};

template <is_unit_value_type_c T>
rod_t(T) -> rod_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
rod_t(const U&) -> rod_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct chain_t final : public unit_t<T, std::ratio<201168, 10000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<201168, 10000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"chain"};
    [[maybe_unused]] static constexpr std::string_view symbol{"ch"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"ch"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"ch"};
};

template <is_unit_value_type_c T>
chain_t(T) -> chain_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
chain_t(const U&) -> chain_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct furlong_t final : public unit_t<T, std::ratio<201168, 1000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<201168, 1000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"furlong"};
    [[maybe_unused]] static constexpr std::string_view symbol{"fur"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"fur"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"fur"};
};

template <is_unit_value_type_c T>
furlong_t(T) -> furlong_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
furlong_t(const U&) -> furlong_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct mile_t final : public unit_t<T, std::ratio<1609344, 1000>, length_dimension>
{
    using _base = unit_t<T, std::ratio<1609344, 1000>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"mile"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mi"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mi"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mi"};
};

template <is_unit_value_type_c T>
mile_t(T) -> mile_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
mile_t(const U&) -> mile_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nautical_mile_t final : public unit_t<T, std::ratio<1852, 1>, length_dimension>
{
    using _base = unit_t<T, std::ratio<1852, 1>, length_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nautical_mile"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nmi"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nmi"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nmi"};
};

template <is_unit_value_type_c T>
nautical_mile_t(T) -> nautical_mile_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == length_dimension)
nautical_mile_t(const U&) -> nautical_mile_t<typename details::is_pkr_unit<U>::value_type>;
} // namespace PKR_UNITS_NAMESPACE
