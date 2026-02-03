#pragma once
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>

namespace PKR_UNITS_NAMESPACE
{
// Electric charge dimension: A·s
inline constexpr dimension_t electric_charge_dimension{0, 0, 1, 1, 0, 0, 0, 0};

template <is_unit_value_type_c T>
struct coulomb_t final : public details::unit_t<T, std::ratio<1, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, electric_charge_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"coulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"C"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"C"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"C"};
};

template <is_unit_value_type_c T>
coulomb_t(T) -> coulomb_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_charge_dimension)
coulomb_t(const U&) -> coulomb_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct kilocoulomb_t final : public details::unit_t<T, std::ratio<1000, 1>, electric_charge_dimension>
{
    using _base = details::unit_t<T, std::ratio<1000, 1>, electric_charge_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"kilocoulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"kC"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"kC"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"kC"};
};

template <is_unit_value_type_c T>
kilocoulomb_t(T) -> kilocoulomb_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_charge_dimension)
kilocoulomb_t(const U&) -> kilocoulomb_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct millicoulomb_t final : public details::unit_t<T, std::ratio<1, 1000>, electric_charge_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, electric_charge_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millicoulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mC"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mC"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mC"};
};

template <is_unit_value_type_c T>
millicoulomb_t(T) -> millicoulomb_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_charge_dimension)
millicoulomb_t(const U&) -> millicoulomb_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct microcoulomb_t final : public details::unit_t<T, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, electric_charge_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microcoulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uC"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5C"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5C"};
};

template <is_unit_value_type_c T>
microcoulomb_t(T) -> microcoulomb_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_charge_dimension)
microcoulomb_t(const U&) -> microcoulomb_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct nanocoulomb_t final : public details::unit_t<T, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000>, electric_charge_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"nanocoulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"nC"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"nC"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"nC"};
};

template <is_unit_value_type_c T>
nanocoulomb_t(T) -> nanocoulomb_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_charge_dimension)
nanocoulomb_t(const U&) -> nanocoulomb_t<typename details::is_pkr_unit<U>::value_type>;

template <is_unit_value_type_c T>
struct picocoulomb_t final : public details::unit_t<T, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000000000>, electric_charge_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"picocoulomb"};
    [[maybe_unused]] static constexpr std::string_view symbol{"pC"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"pC"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"pC"};
};

template <is_unit_value_type_c T>
picocoulomb_t(T) -> picocoulomb_t<T>;

template <is_pkr_unit_c U>
    requires(details::is_pkr_unit<U>::value_dimension == electric_charge_dimension)
picocoulomb_t(const U&) -> picocoulomb_t<typename details::is_pkr_unit<U>::value_type>;

// ============================================================================
// Most derived unit type specializations for electric charge units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, electric_charge_dimension>
{
    using type = coulomb_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1000, 1>, electric_charge_dimension>
{
    using type = kilocoulomb_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, electric_charge_dimension>
{
    using type = millicoulomb_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, electric_charge_dimension>
{
    using type = microcoulomb_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000>, electric_charge_dimension>
{
    using type = nanocoulomb_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000000000>, electric_charge_dimension>
{
    using type = picocoulomb_t<T>;
};
} // namespace PKR_UNITS_NAMESPACE
