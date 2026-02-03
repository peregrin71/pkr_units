#pragma once
#include <pkr_units/impl/unit_impl.h>
#include <pkr_units/impl/dimension.h>
#include <pkr_units/impl/namespace_config.h>
namespace PKR_UNITS_NAMESPACE
{
// Conductance dimension: S = A^2·s^3·kg^-1·m^-2
inline constexpr dimension_t conductance_dimension{-2, -1, 3, 2, 0, 0, 0, 0};
// Conductance units (Siemens and derived)
template <is_unit_value_type_c T>
struct siemens_t final : public details::unit_t<T, std::ratio<1, 1>, conductance_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1>, conductance_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"siemens"};
    [[maybe_unused]] static constexpr std::string_view symbol{"S"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"S"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"S"};
};

template <is_unit_value_type_c T>
siemens_t(T) -> siemens_t<T>;

template <is_unit_value_type_c T>
struct millisiemens_t final : public details::unit_t<T, std::ratio<1, 1000>, conductance_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000>, conductance_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"millisiemens"};
    [[maybe_unused]] static constexpr std::string_view symbol{"mS"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"mS"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"mS"};
};

template <is_unit_value_type_c T>
millisiemens_t(T) -> millisiemens_t<T>;

template <is_unit_value_type_c T>
struct microsiemens_t final : public details::unit_t<T, std::ratio<1, 1000000>, conductance_dimension>
{
    using _base = details::unit_t<T, std::ratio<1, 1000000>, conductance_dimension>;
    using _base::_base;

    [[maybe_unused]] static constexpr std::string_view name{"microsiemens"};
    [[maybe_unused]] static constexpr std::string_view symbol{"uS"};
    [[maybe_unused]] static constexpr std::wstring_view w_symbol{L"\u00b5S"};
    [[maybe_unused]] static constexpr std::u8string_view u8_symbol{u8"\u00b5S"};
};

template <is_unit_value_type_c T>
microsiemens_t(T) -> microsiemens_t<T>;

// ============================================================================
// Most derived unit type specializations for conductance units
// ============================================================================
template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1>, conductance_dimension>
{
    using type = siemens_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000>, conductance_dimension>
{
    using type = millisiemens_t<T>;
};

template <is_unit_value_type_c T>
struct details::derived_unit_type_t<T, std::ratio<1, 1000000>, conductance_dimension>
{
    using type = microsiemens_t<T>;
};

// Explicit double instantiations for ABI / UDL stability
template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1>, conductance_dimension>
{
    using type = siemens_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000>, conductance_dimension>
{
    using type = millisiemens_t<double>;
};

template <>
struct details::derived_unit_type_t<double, std::ratio<1, 1000000>, conductance_dimension>
{
    using type = microsiemens_t<double>;
};
} // namespace PKR_UNITS_NAMESPACE
