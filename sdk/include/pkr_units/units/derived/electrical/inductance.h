#pragma once
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{
// Inductance dimension
inline constexpr dimension_t inductance_dimension{2, 1, -2, -2, 0, 0, 0};

// Inductance units (Henry and derived)
template <is_unit_value_type_c T>
struct henry_t final : public details::unit_t<T, std::ratio<1, 1>, inductance_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, inductance_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"henry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"H"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"H"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"H"};
};

template <is_unit_value_type_c T>
henry_t(T) -> henry_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == inductance_dimension)
henry_t(const U&) -> henry_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millihenry_t final : public details::unit_t<T, std::ratio<1, 1000>, inductance_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, inductance_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millihenry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mH"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mH"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mH"};
};

template <is_unit_value_type_c T>
millihenry_t(T) -> millihenry_t<T>;

template <is_unit_value_type_c T>
struct microhenry_t final : public details::unit_t<T, std::ratio<1, 1000000>, inductance_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, inductance_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microhenry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uH"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5H"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5H"};
};

template <is_unit_value_type_c T>
microhenry_t(T) -> microhenry_t<T>;

template <is_unit_value_type_c T>
struct nanohenry_t final : public details::unit_t<T, std::ratio<1, 1000000000>, inductance_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, inductance_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanohenry"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nH"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nH"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nH"};
};

template <is_unit_value_type_c T>
nanohenry_t(T) -> nanohenry_t<T>;

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, inductance_dimension>
{
    using type = henry_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, inductance_dimension>
{
    using type = millihenry_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, inductance_dimension>
{
    using type = microhenry_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, inductance_dimension>
{
    using type = nanohenry_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
