#pragma once
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
namespace PKR_UNITS_NAMESPACE
{
// Force dimension: kg·m·s⁻² (M·L·T⁻²)
inline constexpr dimension_t force_dimension{1, 1, -2, 0, 0, 0, 0, 0};
// Base unit: Newton (N) = kg·m·s⁻²
using namespace_force_units_detail = int; // Force namespace detail
template <is_unit_value_type_c T>
struct newton_t final : public details::unit_t<T, std::ratio<1, 1>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"newton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"N"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"N"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"N"};
};

template <is_unit_value_type_c T>
newton_t(T) -> newton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
newton_t(const U&) -> newton_t<typename details::is_pkr_unit<U>::value_type>; 

template <is_unit_value_type_c T>
struct kilonewton_t final : public details::unit_t<T, std::ratio<1000, 1>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilonewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kN"};
};

template <is_unit_value_type_c T>
kilonewton_t(T) -> kilonewton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
kilonewton_t(const U&) -> kilonewton_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct meganewton_t final : public details::unit_t<T, std::ratio<1000000, 1>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000000, 1>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"meganewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"MN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"MN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"MN"};
};

template <is_unit_value_type_c T>
meganewton_t(T) -> meganewton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
meganewton_t(const U&) -> meganewton_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct micronewton_t final : public details::unit_t<T, std::ratio<1, 1000000>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"micronewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5N"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5N"};
};

template <is_unit_value_type_c T>
micronewton_t(T) -> micronewton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
micronewton_t(const U&) -> micronewton_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millinewton_t final : public details::unit_t<T, std::ratio<1, 1000>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millinewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mN"};
};

template <is_unit_value_type_c T>
millinewton_t(T) -> millinewton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
millinewton_t(const U&) -> millinewton_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanonewton_t final : public details::unit_t<T, std::ratio<1, 1000000000>, force_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, force_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanonewton"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nN"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nN"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nN"};
};

template <is_unit_value_type_c T>
nanonewton_t(T) -> nanonewton_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == force_dimension)
nanonewton_t(const U&) -> nanonewton_t<typename details::is_pkr_unit<U>::value_type>; 



// Force units
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, force_dimension>
{
    using type = newton_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, force_dimension>
{
    using type = kilonewton_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000000, 1>, force_dimension>
{
    using type = meganewton_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, force_dimension>
{
    using type = micronewton_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, force_dimension>
{
    using type = millinewton_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, force_dimension>
{
    using type = nanonewton_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
