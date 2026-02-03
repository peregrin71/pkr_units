#pragma once
#include <string_view>
#include <pkr_units/impl/namespace_config.h>
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/decls/density_decl.h>

namespace PKR_UNITS_NAMESPACE
{
// Imperial density units
template <is_unit_value_type_c T>
struct pound_per_cubic_inch_t final : public details::unit_t<T, std::ratio<27679904, 1000000>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<27679904, 1000000>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"pound_per_cubic_inch"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lb/in^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"lb\u00b7in\u207b\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"lb\u00b7in\u207b\u00b3"};
};

template <is_unit_value_type_c T>
pound_per_cubic_inch_t(T) -> pound_per_cubic_inch_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
pound_per_cubic_inch_t(const U&) -> pound_per_cubic_inch_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct pound_per_cubic_foot_t final : public details::unit_t<T, std::ratio<16018, 1000000>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<16018, 1000000>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"pound_per_cubic_foot"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lb/ft^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"lb\u00b7ft\u207b\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"lb\u00b7ft\u207b\u00b3"};
};

template <is_unit_value_type_c T>
pound_per_cubic_foot_t(T) -> pound_per_cubic_foot_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
pound_per_cubic_foot_t(const U&) -> pound_per_cubic_foot_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct pound_per_gallon_t final : public details::unit_t<T, std::ratio<119826, 1000000>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<119826, 1000000>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"pound_per_gallon"};
    [[maybe_unused]] static constexpr std::string_view symbol{"lb/gal"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"lb\u00b7gal\u207b\u00b9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"lb\u00b7gal\u207b\u00b9"};
};

template <is_unit_value_type_c T>
pound_per_gallon_t(T) -> pound_per_gallon_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
pound_per_gallon_t(const U&) -> pound_per_gallon_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct ounce_per_cubic_inch_t final : public details::unit_t<T, std::ratio<1729994, 1000000>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<1729994, 1000000>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"ounce_per_cubic_inch"};
    [[maybe_unused]] static constexpr std::string_view symbol{"oz/in^3"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"oz\u00b7in\u207b\u00b3"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"oz\u00b7in\u207b\u00b3"};
};

template <is_unit_value_type_c T>
ounce_per_cubic_inch_t(T) -> ounce_per_cubic_inch_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
ounce_per_cubic_inch_t(const U&) -> ounce_per_cubic_inch_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct ounce_per_fluid_ounce_t final : public details::unit_t<T, std::ratio<33814, 1000>, density_dimension>
{
    using _base = details::unit_t<T, std::ratio<33814, 1000>, density_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"ounce_per_fluid_ounce"};
    [[maybe_unused]] static constexpr std::string_view symbol{"oz/fl oz"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"oz\u00b7fl oz\u207b\u00b9"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"oz\u00b7fl oz\u207b\u00b9"};
};

template <is_unit_value_type_c T>
ounce_per_fluid_ounce_t(T) -> ounce_per_fluid_ounce_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == density_dimension)
ounce_per_fluid_ounce_t(const U&) -> ounce_per_fluid_ounce_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for imperial density units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<27679904, 1000000>, density_dimension>
{
    using type = pound_per_cubic_inch_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<16018, 1000000>, density_dimension>
{
    using type = pound_per_cubic_foot_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<119826, 1000000>, density_dimension>
{
    using type = pound_per_gallon_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1729994, 1000000>, density_dimension>
{
    using type = ounce_per_cubic_inch_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<33814, 1000>, density_dimension>
{
    using type = ounce_per_fluid_ounce_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
